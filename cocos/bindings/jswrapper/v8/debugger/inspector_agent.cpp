#include "inspector_agent.h"

#if (SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_V8) && SE_ENABLE_INSPECTOR

    #include "env.h"
    #include "inspector_io.h"
    #include "node.h"
    #include "util.h"
    #include "v8-inspector.h"
    #include "v8-platform.h"
    #include "zlib.h"

    #include "libplatform/libplatform.h"

    #include <cstring>
    #include <memory>
    #include <unordered_map>
    #include <vector>

    #ifdef __POSIX__
        #include <unistd.h> // setuid, getuid
    #endif                  // __POSIX__

namespace node {
namespace inspector {
namespace {
using v8::Context;
using v8::External;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::HandleScope;
using v8::Isolate;
using v8::Local;
using v8::Maybe;
using v8::MaybeLocal;
using v8::NewStringType;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;

using v8_inspector::StringBuffer;
using v8_inspector::StringView;
using v8_inspector::V8Inspector;
using v8_inspector::V8InspectorClient;

uv_sem_t   startIoThreadSemaphore;
uv_async_t startIoThreadAsync;

class StartIoTask : public v8::Task {
public:
    explicit StartIoTask(Agent *agent) : _agent(agent) {}

    void Run() override {
        _agent->StartIoThread(false);
    }

private:
    Agent *_agent;
};

std::unique_ptr<StringBuffer> toProtocolString(Isolate *    isolate,
                                               Local<Value> value) {
    TwoByteValue buffer(isolate, value);
    return StringBuffer::create(StringView(*buffer, buffer.length()));
}

// Called on the main thread.
void startIoThreadAsyncCallback(uv_async_t *handle) {
    static_cast<Agent *>(handle->data)->StartIoThread(false);
}

void startIoInterrupt(Isolate * /*isolate*/, void *agent) {
    static_cast<Agent *>(agent)->StartIoThread(false);
}

    #ifdef __POSIX__

void startIoThreadWakeup(int /*signo*/) {
    uv_sem_post(&startIoThreadSemaphore);
}

inline void *startIoThreadMain(void * /*unused*/) {
    for (;;) {
        uv_sem_wait(&startIoThreadSemaphore);
        auto *agent = static_cast<Agent *>(startIoThreadAsync.data);
        if (agent != nullptr) {
            agent->RequestIoThreadStart();
        }
    }
    return nullptr;
}

int startDebugSignalHandler() {
    // Start a watchdog thread for calling v8::Debug::DebugBreak() because
    // it's not safe to call directly from the signal handler, it can
    // deadlock with the thread it interrupts.
    CHECK_EQ(0, uv_sem_init(&startIoThreadSemaphore, 0));
    pthread_attr_t attr;
    CHECK_EQ(0, pthread_attr_init(&attr));
        // Don't shrink the thread's stack on FreeBSD.  Said platform decided to
        // follow the pthreads specification to the letter rather than in spirit:
        // https://lists.freebsd.org/pipermail/freebsd-current/2014-March/048885.html
        #ifndef __FreeBSD__
    CHECK_EQ(0, pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN));
        #endif // __FreeBSD__
    CHECK_EQ(0, pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED));
    sigset_t sigmask;
    // Mask all signals.
    sigfillset(&sigmask);
    CHECK_EQ(0, pthread_sigmask(SIG_SETMASK, &sigmask, &sigmask));
    pthread_t thread;
    const int err = pthread_create(&thread, &attr,
                                   startIoThreadMain, nullptr);
    // Restore original mask
    CHECK_EQ(0, pthread_sigmask(SIG_SETMASK, &sigmask, nullptr));
    CHECK_EQ(0, pthread_attr_destroy(&attr));
    if (err != 0) {
        SE_LOGE("node[%d]: pthread_create: %s\n", getpid(), strerror(err));

        // Leave SIGUSR1 blocked.  We don't install a signal handler,
        // receiving the signal would terminate the process.
        return -err;
    }
    RegisterSignalHandler(SIGUSR1, startIoThreadWakeup);
    // Unblock SIGUSR1.  A pending SIGUSR1 signal will now be delivered.
    sigemptyset(&sigmask);
    sigaddset(&sigmask, SIGUSR1);
    CHECK_EQ(0, pthread_sigmask(SIG_UNBLOCK, &sigmask, nullptr));
    return 0;
}
    #endif // __POSIX__

    #ifdef _WIN32
DWORD WINAPI StartIoThreadProc(void *arg) {
    Agent *agent = static_cast<Agent *>(start_io_thread_async.data);
    if (agent != nullptr)
        agent->RequestIoThreadStart();
    return 0;
}

static int GetDebugSignalHandlerMappingName(DWORD pid, wchar_t *buf,
                                            size_t buf_len) {
    return _snwprintf(buf, buf_len, L"node-debug-handler-%u", pid);
}

static int StartDebugSignalHandler() {
    wchar_t                 mapping_name[32];
    HANDLE                  mapping_handle;
    DWORD                   pid;
    LPTHREAD_START_ROUTINE *handler;

    pid = GetCurrentProcessId();

    if (GetDebugSignalHandlerMappingName(pid,
                                         mapping_name,
                                         arraysize(mapping_name)) < 0) {
        return -1;
    }

    mapping_handle = CreateFileMappingW(INVALID_HANDLE_VALUE,
                                        nullptr,
                                        PAGE_READWRITE,
                                        0,
                                        sizeof *handler,
                                        mapping_name);
    if (mapping_handle == nullptr) {
        return -1;
    }

    handler = reinterpret_cast<LPTHREAD_START_ROUTINE *>(
        MapViewOfFile(mapping_handle,
                      FILE_MAP_ALL_ACCESS,
                      0,
                      0,
                      sizeof *handler));
    if (handler == nullptr) {
        CloseHandle(mapping_handle);
        return -1;
    }

    *handler = StartIoThreadProc;

    UnmapViewOfFile(static_cast<void *>(handler));

    return 0;
}
    #endif // _WIN32

class JsBindingsSessionDelegate : public InspectorSessionDelegate {
public:
    JsBindingsSessionDelegate(Environment *   env,
                              Local<Object>   session,
                              Local<Object>   receiver,
                              Local<Function> callback)
    : _env(env),
      _session(env->isolate(), session),
      _receiver(env->isolate(), receiver),
      _callback(env->isolate(), callback) {
        _session.SetWeak(this, JsBindingsSessionDelegate::release,
                         v8::WeakCallbackType::kParameter);
    }

    ~JsBindingsSessionDelegate() override {
        _session.Reset();
        _receiver.Reset();
        _callback.Reset();
    }

    bool WaitForFrontendMessageWhilePaused() override {
        return false;
    }

    void SendMessageToFrontend(const v8_inspector::StringView &message) override {
        Isolate *          isolate = _env->isolate();
        v8::HandleScope    handleScope(isolate);
        Context::Scope     contextScope(_env->context());
        MaybeLocal<String> v8string =
            String::NewFromTwoByte(isolate, message.characters16(),
                                   NewStringType::kNormal, static_cast<int>(message.length()));
        Local<Value>    argument = v8string.ToLocalChecked().As<Value>();
        Local<Function> callback = _callback.Get(isolate);
        Local<Object>   receiver = _receiver.Get(isolate);
        callback->Call(_env->context(), receiver, 1, &argument)
            .FromMaybe(Local<Value>());
    }

    void disconnect() {
        Agent *agent = _env->inspector_agent();
        if (agent->delegate() == this) {
            agent->Disconnect();
        }
    }

private:
    static void release(
        const v8::WeakCallbackInfo<JsBindingsSessionDelegate> &info) {
        info.SetSecondPassCallback(releaseSecondPass);
        info.GetParameter()->_session.Reset();
    }

    static void releaseSecondPass(
        const v8::WeakCallbackInfo<JsBindingsSessionDelegate> &info) {
        JsBindingsSessionDelegate *delegate = info.GetParameter();
        delegate->disconnect();
        delete delegate;
    }

    Environment *        _env;
    Persistent<Object>   _session;
    Persistent<Object>   _receiver;
    Persistent<Function> _callback;
};

void setDelegate(Environment *env, Local<Object> inspector,
                 JsBindingsSessionDelegate *delegate) {
    inspector->SetPrivate(env->context(),
                          env->inspector_delegate_private_symbol(),
                          v8::External::New(env->isolate(), delegate));
}

Maybe<JsBindingsSessionDelegate *> getDelegate(
    const FunctionCallbackInfo<Value> &info) {
    Environment *     env = Environment::GetCurrent(info);
    Local<Value>      delegate;
    MaybeLocal<Value> maybeDelegate =
        info.This()->GetPrivate(env->context(),
                                env->inspector_delegate_private_symbol());

    if (maybeDelegate.ToLocal(&delegate)) {
        CHECK(delegate->IsExternal());
        void *value = delegate.As<External>()->Value();
        if (value != nullptr) {
            return v8::Just(static_cast<JsBindingsSessionDelegate *>(value));
        }
    }
    env->ThrowError("Inspector is not connected");
    return v8::Nothing<JsBindingsSessionDelegate *>();
}

void dispatch(const FunctionCallbackInfo<Value> &info) {
    Environment *env = Environment::GetCurrent(info);
    if (!info[0]->IsString()) {
        env->ThrowError("Inspector message must be a string");
        return;
    }
    Maybe<JsBindingsSessionDelegate *> maybeDelegate = getDelegate(info);
    if (maybeDelegate.IsNothing()) {
        return;
    }
    Agent *inspector = env->inspector_agent();
    CHECK_EQ(maybeDelegate.ToChecked(), inspector->delegate());
    inspector->Dispatch(toProtocolString(env->isolate(), info[0])->string());
}

void disconnect(const FunctionCallbackInfo<Value> &info) {
    Environment *                      env      = Environment::GetCurrent(info);
    Maybe<JsBindingsSessionDelegate *> delegate = getDelegate(info);
    if (delegate.IsNothing()) {
        return;
    }
    delegate.ToChecked()->disconnect();
    setDelegate(env, info.This(), nullptr);
    delete delegate.ToChecked();
}

void connectJsBindingsSession(const FunctionCallbackInfo<Value> &info) {
    Environment *env = Environment::GetCurrent(info);
    if (!info[0]->IsFunction()) {
        env->ThrowError("Message callback is required");
        return;
    }
    Agent *inspector = env->inspector_agent();
    if (inspector->delegate() != nullptr) {
        env->ThrowError("Session is already attached");
        return;
    }
    Local<Object> session = Object::New(env->isolate());
    env->SetMethod(session, "dispatch", dispatch);
    env->SetMethod(session, "disconnect", disconnect);
    info.GetReturnValue().Set(session);

    auto *delegate =
        new JsBindingsSessionDelegate(env, session, info.Holder(),
                                      info[0].As<Function>());
    inspector->Connect(delegate);
    setDelegate(env, session, delegate);
}

void inspectorConsoleCall(const v8::FunctionCallbackInfo<Value> &info) {
    Isolate *      isolate = info.GetIsolate();
    HandleScope    handleScope(isolate);
    Local<Context> context = isolate->GetCurrentContext();
    CHECK_LT(2, info.Length());
    std::vector<Local<Value>> callArgs;
    for (int i = 3; i < info.Length(); ++i) {
        callArgs.push_back(info[i]);
    }
    Environment *env = Environment::GetCurrent(isolate);
    if (env->inspector_agent()->enabled()) {
        Local<Value> inspectorMethod = info[0];
        CHECK(inspectorMethod->IsFunction());
        Local<Value> configValue = info[2];
        CHECK(configValue->IsObject());
        Local<Object> configObject = configValue.As<Object>();
        Local<String> inCallKey    = FIXED_ONE_BYTE_STRING(isolate, "in_call");
        if (!configObject->Has(context, inCallKey).FromMaybe(false)) {
            CHECK(configObject->Set(context,
                                    inCallKey,
                                    v8::True(isolate))
                      .FromJust());
            CHECK(!inspectorMethod.As<Function>()->Call(context,
                                                        info.Holder(),
                                                        static_cast<int>(callArgs.size()),
                                                        callArgs.data())
                       .IsEmpty());
        }
        CHECK(configObject->Delete(context, inCallKey).FromJust());
    }

    Local<Value> nodeMethod = info[1];
    CHECK(nodeMethod->IsFunction());
    nodeMethod.As<Function>()->Call(context,
                                    info.Holder(),
                                    static_cast<int>(callArgs.size()),
                                    callArgs.data())
        .FromMaybe(Local<Value>());
}

void callAndPauseOnStart(
    const v8::FunctionCallbackInfo<v8::Value> &args) {
    Environment *env = Environment::GetCurrent(args);
    CHECK_GT(args.Length(), 1);
    CHECK(args[0]->IsFunction());
    std::vector<v8::Local<v8::Value>> callArgs;
    for (int i = 2; i < args.Length(); i++) {
        callArgs.push_back(args[i]);
    }

    env->inspector_agent()->PauseOnNextJavascriptStatement("Break on start");
    v8::MaybeLocal<v8::Value> retval =
        args[0].As<v8::Function>()->Call(env->context(), args[1],
                                         static_cast<int>(callArgs.size()), callArgs.data());
    if (!retval.IsEmpty()) {
        args.GetReturnValue().Set(retval.ToLocalChecked());
    }
}

// Used in NodeInspectorClient::currentTimeMS() below.
const int NANOS_PER_MSEC   = 1000000;
const int CONTEXT_GROUP_ID = 1;

class ChannelImpl final : public v8_inspector::V8Inspector::Channel {
public:
    explicit ChannelImpl(V8Inspector *             inspector,
                         InspectorSessionDelegate *delegate)
    : _delegate(delegate) {
        _session = inspector->connect(1, this, StringView());
    }

    ~ChannelImpl() override = default;

    void dispatchProtocolMessage(const StringView &message) {
        _session->dispatchProtocolMessage(message);
    }

    bool waitForFrontendMessage() {
        return _delegate->WaitForFrontendMessageWhilePaused();
    }

    void schedulePauseOnNextStatement(const std::string &reason) {
        std::unique_ptr<StringBuffer> buffer = Utf8ToStringView(reason);
        _session->schedulePauseOnNextStatement(buffer->string(), buffer->string());
    }

    InspectorSessionDelegate *delegate() {
        return _delegate;
    }

private:
    void sendResponse(
        int /*callId*/,
        std::unique_ptr<v8_inspector::StringBuffer> message) override {
        sendMessageToFrontend(message->string());
    }

    void sendNotification(
        std::unique_ptr<v8_inspector::StringBuffer> message) override {
        sendMessageToFrontend(message->string());
    }

    void flushProtocolNotifications() override {}

    void sendMessageToFrontend(const StringView &message) {
        _delegate->SendMessageToFrontend(message);
    }

    InspectorSessionDelegate *const                   _delegate;
    std::unique_ptr<v8_inspector::V8InspectorSession> _session;
};

class InspectorTimer {
public:
    InspectorTimer(uv_loop_t *                      loop,
                   double                           intervalS,
                   V8InspectorClient::TimerCallback callback,
                   void *                           data) : _timer(),
                                 _callback(callback),
                                 _data(data) {
        uv_timer_init(loop, &_timer);
        auto intervalMs = static_cast<int64_t>(1000 * intervalS);
        uv_timer_start(&_timer, onTimer, intervalMs, intervalMs);
    }

    InspectorTimer(const InspectorTimer &) = delete;

    void stop() {
        uv_timer_stop(&_timer);
        uv_close(reinterpret_cast<uv_handle_t *>(&_timer), timerClosedCb);
    }

private:
    static void onTimer(uv_timer_t *uvtimer) {
        InspectorTimer *timer = node::ContainerOf(&InspectorTimer::_timer, uvtimer);
        timer->_callback(timer->_data);
    }

    static void timerClosedCb(uv_handle_t *uvtimer) {
        InspectorTimer *timer =
            node::ContainerOf(&InspectorTimer::_timer,
                              reinterpret_cast<uv_timer_t *>(uvtimer));
        delete timer;
    }

    ~InspectorTimer() = default;

    uv_timer_t                       _timer;
    V8InspectorClient::TimerCallback _callback;
    void *                           _data;
};

class InspectorTimerHandle {
public:
    InspectorTimerHandle(uv_loop_t *loop, double intervalS,
                         V8InspectorClient::TimerCallback callback, void *data) {
        _timer = new InspectorTimer(loop, intervalS, callback, data);
    }

    InspectorTimerHandle(const InspectorTimerHandle &) = delete;

    ~InspectorTimerHandle() {
        CHECK_NE(_timer, nullptr);
        _timer->stop();
        _timer = nullptr;
    }

private:
    InspectorTimer *_timer;
};
} // namespace

class NodeInspectorClient : public V8InspectorClient {
public:
    NodeInspectorClient(node::Environment *env,
                        v8::Platform *     platform) : _env(env),
                                                  _platform(platform),
                                                  _terminated(false),
                                                  _running_nested_loop(false) {
        _client = V8Inspector::create(env->isolate(), this);
    }

    void runMessageLoopOnPause(int context_group_id) override {
        CHECK_NE(_channel, nullptr);
        if (_running_nested_loop) {
            return;
        }
        _terminated          = false;
        _running_nested_loop = true;
        while (!_terminated && _channel->waitForFrontendMessage()) {
            while (v8::platform::PumpMessageLoop(_platform, _env->isolate())) {
            }
        }
        _terminated          = false;
        _running_nested_loop = false;
    }

    double currentTimeMS() override {
        return uv_hrtime() * 1.0 / NANOS_PER_MSEC;
    }

    void contextCreated(Local<Context> context, const std::string &name) {
        std::unique_ptr<StringBuffer> nameBuffer = Utf8ToStringView(name);
        v8_inspector::V8ContextInfo   info(context, CONTEXT_GROUP_ID,
                                         nameBuffer->string());
        _client->contextCreated(info);
    }

    void contextDestroyed(Local<Context> context) {
        _client->contextDestroyed(context);
    }

    void quitMessageLoopOnPause() override {
        _terminated = true;
    }

    void connectFrontend(InspectorSessionDelegate *delegate) {
        CHECK_EQ(_channel, nullptr);
        _channel = std::make_unique<ChannelImpl>(
            _client.get(), delegate);
    }

    void disconnectFrontend() {
        quitMessageLoopOnPause();
        _channel.reset();
    }

    void dispatchMessageFromFrontend(const StringView &message) {
        if (_channel == nullptr) return;
        CHECK_NE(_channel, nullptr);
        _channel->dispatchProtocolMessage(message);
    }

    Local<Context> ensureDefaultContextInGroup(int /*contextGroupId*/) override {
        return _env->context();
    }

    void fatalException(Local<Value> error, Local<v8::Message> message) {
        Local<Context> context = _env->context();

        int scriptId = static_cast<int>(message->GetScriptOrigin().ScriptID()->Value());

        Local<v8::StackTrace> stackTrace = message->GetStackTrace();

        if (!stackTrace.IsEmpty() &&
            stackTrace->GetFrameCount() > 0 &&
            scriptId == stackTrace->GetFrame(_env->isolate(), 0)->GetScriptId()) {
            scriptId = 0;
        }

        const uint8_t details[] = "Uncaught";

        Isolate *isolate = context->GetIsolate();

        _client->exceptionThrown(
            context,
            StringView(details, sizeof(details) - 1),
            error,
            toProtocolString(isolate, message->Get())->string(),
            toProtocolString(isolate, message->GetScriptResourceName())->string(),
            message->GetLineNumber(context).FromMaybe(0),
            message->GetStartColumn(context).FromMaybe(0),
            _client->createStackTrace(stackTrace),
            scriptId);
    }

    ChannelImpl *channel() {
        return _channel.get();
    }

    void startRepeatingTimer(double        intervalS,
                             TimerCallback callback,
                             void *        data) override {
        _timers.emplace(std::piecewise_construct, std::make_tuple(data),
                        std::make_tuple(_env->event_loop(), intervalS, callback,
                                        data));
    }

    void cancelTimer(void *data) override {
        _timers.erase(data);
    }

private:
    node::Environment *                              _env;
    v8::Platform *                                   _platform;
    bool                                             _terminated;
    bool                                             _running_nested_loop;
    std::unique_ptr<V8Inspector>                     _client;
    std::unique_ptr<ChannelImpl>                     _channel;
    std::unordered_map<void *, InspectorTimerHandle> _timers;
};

Agent::Agent(Environment *env) : parent_env_(env),
                                 client_(nullptr),
                                 platform_(nullptr),
                                 enabled_(false) {}

// Destructor needs to be defined here in implementation file as the header
// does not have full definition of some classes.
Agent::~Agent() = default;

bool Agent::Start(v8::Platform *platform, const char *path,
                  const DebugOptions &options) {
    path_          = path == nullptr ? "" : path;
    debug_options_ = options;
    client_ =
        std::make_unique<NodeInspectorClient>(
            parent_env_, platform);
    client_->contextCreated(parent_env_->context(), "Node.js Main Context");
    platform_ = platform;
    CHECK_EQ(0, uv_async_init(uv_default_loop(),
                              &startIoThreadAsync,
                              startIoThreadAsyncCallback));
    startIoThreadAsync.data = this;
    uv_unref(reinterpret_cast<uv_handle_t *>(&startIoThreadAsync));

    // Ignore failure, SIGUSR1 won't work, but that should not block node start.
    startDebugSignalHandler();
    if (options.inspector_enabled()) {
        // This will return false if listen failed on the inspector port.
        return StartIoThread(options.wait_for_connect());
    }
    return true;
}

bool Agent::StartIoThread(bool waitForConnect) {
    if (io_ != nullptr) {
        return true;
    }

    CHECK_NE(client_, nullptr);

    enabled_ = true;
    io_      = std::make_unique<InspectorIo>(
        parent_env_, platform_, path_, debug_options_,
        waitForConnect);
    if (!io_->Start()) {
        client_.reset();
        return false;
    }

    v8::Isolate *isolate = parent_env_->isolate();

    // Send message to enable debug in workers
    HandleScope   handleScope(isolate);
    Local<Object> processObject = parent_env_->process_object();
    Local<Value>  emitFn =
        processObject->Get(parent_env_->context(), FIXED_ONE_BYTE_STRING(isolate, "emit")).ToLocalChecked();
    // In case the thread started early during the startup
    if (!emitFn->IsFunction()) {
        return true;
    }

    Local<Object> message = Object::New(isolate);
    message->Set(parent_env_->context(), FIXED_ONE_BYTE_STRING(isolate, "cmd"),
                 FIXED_ONE_BYTE_STRING(isolate, "NODE_DEBUG_ENABLED"))
        .Check();
    Local<Value> argv[] = {
        FIXED_ONE_BYTE_STRING(isolate, "internalMessage"),
        message};
    MakeCallback(parent_env_->isolate(), processObject, emitFn.As<Function>(),
                 arraysize(argv), argv, {0, 0});

    return true;
}

void Agent::Stop() {
    if (io_ != nullptr) {
        io_->Stop();
        io_.reset();
    }
}

void Agent::Connect(InspectorSessionDelegate *delegate) {
    enabled_ = true;
    client_->connectFrontend(delegate);
}

bool Agent::IsConnected() {
    return io_ && io_->IsConnected();
}

void Agent::WaitForDisconnect() {
    CHECK_NE(client_, nullptr);
    client_->contextDestroyed(parent_env_->context());
    if (io_ != nullptr) {
        io_->WaitForDisconnect();
    }
}

void Agent::FatalException(Local<Value> error, Local<v8::Message> message) {
    if (!IsStarted()) {
        return;
    }
    client_->fatalException(error, message);
    WaitForDisconnect();
}

void Agent::Dispatch(const StringView &message) {
    if (client_ == nullptr) return;
    CHECK_NE(client_, nullptr);
    client_->dispatchMessageFromFrontend(message);
}

void Agent::Disconnect() {
    CHECK_NE(client_, nullptr);
    client_->disconnectFrontend();
}

void Agent::RunMessageLoop() {
    CHECK_NE(client_, nullptr);
    client_->runMessageLoopOnPause(CONTEXT_GROUP_ID);
}

InspectorSessionDelegate *Agent::delegate() {
    CHECK_NE(client_, nullptr);
    ChannelImpl *channel = client_->channel();
    if (channel == nullptr) {
        return nullptr;
    }
    return channel->delegate();
}

void Agent::PauseOnNextJavascriptStatement(const std::string &reason) {
    ChannelImpl *channel = client_->channel();
    if (channel != nullptr) {
        channel->schedulePauseOnNextStatement(reason);
    }
}

void open(const FunctionCallbackInfo<Value> &args) {
    Environment *     env            = Environment::GetCurrent(args);
    inspector::Agent *agent          = env->inspector_agent();
    bool              waitForConnect = false;

    if (args.Length() > 0 && args[0]->IsUint32()) {
        uint32_t port = args[0]->Uint32Value(env->context()).ToChecked();
        agent->options().set_port(static_cast<int>(port));
    }

    if (args.Length() > 1 && args[1]->IsString()) {
        node::Utf8Value host(env->isolate(), args[1].As<String>());
        agent->options().set_host_name(*host);
    }

    if (args.Length() > 2 && args[2]->IsBoolean()) {
        waitForConnect = args[2]->BooleanValue(env->isolate());
    }

    agent->StartIoThread(waitForConnect);
}

void url(const FunctionCallbackInfo<Value> &args) {
    Environment *           env   = Environment::GetCurrent(args);
    inspector::Agent *      agent = env->inspector_agent();
    inspector::InspectorIo *io    = agent->io();

    if (!io) return;

    std::vector<std::string> ids = io->GetTargetIds();

    if (ids.empty()) return;

    std::string url = FormatWsAddress(io->host(), io->port(), ids[0], true);
    args.GetReturnValue().Set(OneByteString(env->isolate(), url.c_str()));
}

// static
void Agent::InitInspector(Local<Object>  target, Local<Value> /*unused*/,
                          Local<Context> context, void * /*priv*/) {
    Environment *env   = Environment::GetCurrent(context);
    Agent *      agent = env->inspector_agent();
    env->SetMethod(target, "consoleCall", inspectorConsoleCall);
    if (agent->debug_options_.wait_for_connect()) {
        env->SetMethod(target, "callAndPauseOnStart", callAndPauseOnStart);
    }
    env->SetMethod(target, "connect", connectJsBindingsSession);
    env->SetMethod(target, "open", open);
    env->SetMethod(target, "url", url);
}

void Agent::RequestIoThreadStart() {
    // We need to attempt to interrupt V8 flow (in case Node is running
    // continuous JS code) and to wake up libuv thread (in case Node is waiting
    // for IO events)
    uv_async_send(&startIoThreadAsync);
    v8::Isolate *isolate = parent_env_->isolate();
    platform_->GetForegroundTaskRunner(isolate)->PostTask(std::make_unique<StartIoTask>(this));
    isolate->RequestInterrupt(startIoInterrupt, this);
    uv_async_send(&startIoThreadAsync);
}

} // namespace inspector
} // namespace node

//cjh NODE_MODULE_CONTEXT_AWARE_BUILTIN(inspector,
//                                  node::inspector::Agent::InitInspector);

#endif // #if (SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_V8) && SE_ENABLE_INSPECTOR
