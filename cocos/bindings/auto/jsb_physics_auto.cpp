#include "cocos/bindings/auto/jsb_physics_auto.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/manual/jsb_global.h"
#include "physics/PhysicsSDK.h"

#ifndef JSB_ALLOC
#define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
#define JSB_FREE(ptr) delete ptr
#endif
se::Object* __jsb_cc_physics_World_proto = nullptr;
se::Class* __jsb_cc_physics_World_class = nullptr;

static bool js_physics_World_destroy(se::State& s)
{
    cc::physics::World* cobj = SE_THIS_OBJECT<cc::physics::World>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_World_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_World_destroy)

static bool js_physics_World_emitEvents(se::State& s)
{
    cc::physics::World* cobj = SE_THIS_OBJECT<cc::physics::World>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_World_emitEvents : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->emitEvents();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_World_emitEvents)

static bool js_physics_World_setAllowSleep(se::State& s)
{
    cc::physics::World* cobj = SE_THIS_OBJECT<cc::physics::World>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_World_setAllowSleep : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_World_setAllowSleep : Error processing arguments");
        cobj->setAllowSleep(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_World_setAllowSleep)

static bool js_physics_World_setDefaultMaterial(se::State& s)
{
    cc::physics::World* cobj = SE_THIS_OBJECT<cc::physics::World>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_World_setDefaultMaterial : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_World_setDefaultMaterial : Error processing arguments");
        cobj->setDefaultMaterial(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_World_setDefaultMaterial)

static bool js_physics_World_setGravity(se::State& s)
{
    cc::physics::World* cobj = SE_THIS_OBJECT<cc::physics::World>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_World_setGravity : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_World_setGravity : Error processing arguments");
        cobj->setGravity(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_World_setGravity)

static bool js_physics_World_step(se::State& s)
{
    cc::physics::World* cobj = SE_THIS_OBJECT<cc::physics::World>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_World_step : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_World_step : Error processing arguments");
        cobj->step(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_World_step)

static bool js_physics_World_syncSceneToPhysics(se::State& s)
{
    cc::physics::World* cobj = SE_THIS_OBJECT<cc::physics::World>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_World_syncSceneToPhysics : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->syncSceneToPhysics();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_World_syncSceneToPhysics)

static bool js_physics_World_syncSceneWithCheck(se::State& s)
{
    cc::physics::World* cobj = SE_THIS_OBJECT<cc::physics::World>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_World_syncSceneWithCheck : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->syncSceneWithCheck();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_World_syncSceneWithCheck)

SE_DECLARE_FINALIZE_FUNC(js_cc_physics_World_finalize)

static bool js_physics_World_constructor(se::State& s) // constructor.c
{
    cc::physics::World* cobj = JSB_ALLOC(cc::physics::World);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_physics_World_constructor, __jsb_cc_physics_World_class, js_cc_physics_World_finalize)




static bool js_cc_physics_World_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::physics::World>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::physics::World* cobj = SE_THIS_OBJECT<cc::physics::World>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_physics_World_finalize)

bool js_register_physics_World(se::Object* obj)
{
    auto cls = se::Class::create("World", obj, nullptr, _SE(js_physics_World_constructor));

    cls->defineFunction("destroy", _SE(js_physics_World_destroy));
    cls->defineFunction("emitEvents", _SE(js_physics_World_emitEvents));
    cls->defineFunction("setAllowSleep", _SE(js_physics_World_setAllowSleep));
    cls->defineFunction("setDefaultMaterial", _SE(js_physics_World_setDefaultMaterial));
    cls->defineFunction("setGravity", _SE(js_physics_World_setGravity));
    cls->defineFunction("step", _SE(js_physics_World_step));
    cls->defineFunction("syncSceneToPhysics", _SE(js_physics_World_syncSceneToPhysics));
    cls->defineFunction("syncSceneWithCheck", _SE(js_physics_World_syncSceneWithCheck));
    cls->defineFinalizeFunction(_SE(js_cc_physics_World_finalize));
    cls->install();
    JSBClassType::registerClass<cc::physics::World>(cls);

    __jsb_cc_physics_World_proto = cls->getProto();
    __jsb_cc_physics_World_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cc_physics_RigidBody_proto = nullptr;
se::Class* __jsb_cc_physics_RigidBody_class = nullptr;

static bool js_physics_RigidBody_applyForce(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_applyForce : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 6) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        HolderType<float, false> arg3 = {};
        HolderType<float, false> arg4 = {};
        HolderType<float, false> arg5 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        ok &= sevalue_to_native(args[3], &arg3, s.thisObject());
        ok &= sevalue_to_native(args[4], &arg4, s.thisObject());
        ok &= sevalue_to_native(args[5], &arg5, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_applyForce : Error processing arguments");
        cobj->applyForce(arg0.value(), arg1.value(), arg2.value(), arg3.value(), arg4.value(), arg5.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 6);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_applyForce)

static bool js_physics_RigidBody_applyImpulse(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_applyImpulse : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 6) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        HolderType<float, false> arg3 = {};
        HolderType<float, false> arg4 = {};
        HolderType<float, false> arg5 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        ok &= sevalue_to_native(args[3], &arg3, s.thisObject());
        ok &= sevalue_to_native(args[4], &arg4, s.thisObject());
        ok &= sevalue_to_native(args[5], &arg5, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_applyImpulse : Error processing arguments");
        cobj->applyImpulse(arg0.value(), arg1.value(), arg2.value(), arg3.value(), arg4.value(), arg5.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 6);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_applyImpulse)

static bool js_physics_RigidBody_applyLocalForce(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_applyLocalForce : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 6) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        HolderType<float, false> arg3 = {};
        HolderType<float, false> arg4 = {};
        HolderType<float, false> arg5 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        ok &= sevalue_to_native(args[3], &arg3, s.thisObject());
        ok &= sevalue_to_native(args[4], &arg4, s.thisObject());
        ok &= sevalue_to_native(args[5], &arg5, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_applyLocalForce : Error processing arguments");
        cobj->applyLocalForce(arg0.value(), arg1.value(), arg2.value(), arg3.value(), arg4.value(), arg5.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 6);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_applyLocalForce)

static bool js_physics_RigidBody_applyLocalImpulse(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_applyLocalImpulse : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 6) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        HolderType<float, false> arg3 = {};
        HolderType<float, false> arg4 = {};
        HolderType<float, false> arg5 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        ok &= sevalue_to_native(args[3], &arg3, s.thisObject());
        ok &= sevalue_to_native(args[4], &arg4, s.thisObject());
        ok &= sevalue_to_native(args[5], &arg5, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_applyLocalImpulse : Error processing arguments");
        cobj->applyLocalImpulse(arg0.value(), arg1.value(), arg2.value(), arg3.value(), arg4.value(), arg5.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 6);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_applyLocalImpulse)

static bool js_physics_RigidBody_applyLocalTorque(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_applyLocalTorque : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_applyLocalTorque : Error processing arguments");
        cobj->applyLocalTorque(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_applyLocalTorque)

static bool js_physics_RigidBody_applyTorque(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_applyTorque : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_applyTorque : Error processing arguments");
        cobj->applyTorque(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_applyTorque)

static bool js_physics_RigidBody_clearForces(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_clearForces : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->clearForces();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_clearForces)

static bool js_physics_RigidBody_clearState(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_clearState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->clearState();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_clearState)

static bool js_physics_RigidBody_clearVelocity(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_clearVelocity : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->clearVelocity();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_clearVelocity)

static bool js_physics_RigidBody_getAngularVelocity(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_getAngularVelocity : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::Vec3 result = cobj->getAngularVelocity();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_getAngularVelocity : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_getAngularVelocity)

static bool js_physics_RigidBody_getLinearVelocity(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_getLinearVelocity : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::Vec3 result = cobj->getLinearVelocity();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_getLinearVelocity : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_getLinearVelocity)

static bool js_physics_RigidBody_getSleepThreshold(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_getSleepThreshold : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getSleepThreshold();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_getSleepThreshold : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_getSleepThreshold)

static bool js_physics_RigidBody_initialize(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_initialize : Error processing arguments");
        cobj->initialize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_initialize)

static bool js_physics_RigidBody_isAwake(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_isAwake : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isAwake();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_isAwake : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_isAwake)

static bool js_physics_RigidBody_isSleeping(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_isSleeping : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isSleeping();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_isSleeping : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_isSleeping)

static bool js_physics_RigidBody_isSleepy(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_isSleepy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isSleepy();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_isSleepy : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_isSleepy)

static bool js_physics_RigidBody_onDestroy(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_onDestroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onDestroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_onDestroy)

static bool js_physics_RigidBody_onDisable(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_onDisable : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onDisable();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_onDisable)

static bool js_physics_RigidBody_onEnable(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_onEnable : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onEnable();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_onEnable)

static bool js_physics_RigidBody_setAllowSleep(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_setAllowSleep : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_setAllowSleep : Error processing arguments");
        cobj->setAllowSleep(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_setAllowSleep)

static bool js_physics_RigidBody_setAngularDamping(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_setAngularDamping : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_setAngularDamping : Error processing arguments");
        cobj->setAngularDamping(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_setAngularDamping)

static bool js_physics_RigidBody_setAngularFactor(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_setAngularFactor : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_setAngularFactor : Error processing arguments");
        cobj->setAngularFactor(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_setAngularFactor)

static bool js_physics_RigidBody_setAngularVelocity(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_setAngularVelocity : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_setAngularVelocity : Error processing arguments");
        cobj->setAngularVelocity(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_setAngularVelocity)

static bool js_physics_RigidBody_setCollisionFilter(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_setCollisionFilter : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<int, false> arg0 = {};
        HolderType<int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_setCollisionFilter : Error processing arguments");
        cobj->setCollisionFilter(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_setCollisionFilter)

static bool js_physics_RigidBody_setLinearDamping(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_setLinearDamping : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_setLinearDamping : Error processing arguments");
        cobj->setLinearDamping(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_setLinearDamping)

static bool js_physics_RigidBody_setLinearFactor(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_setLinearFactor : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_setLinearFactor : Error processing arguments");
        cobj->setLinearFactor(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_setLinearFactor)

static bool js_physics_RigidBody_setLinearVelocity(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_setLinearVelocity : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_setLinearVelocity : Error processing arguments");
        cobj->setLinearVelocity(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_setLinearVelocity)

static bool js_physics_RigidBody_setMass(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_setMass : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_setMass : Error processing arguments");
        cobj->setMass(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_setMass)

static bool js_physics_RigidBody_setSleepThreshold(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_setSleepThreshold : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_setSleepThreshold : Error processing arguments");
        cobj->setSleepThreshold(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_setSleepThreshold)

static bool js_physics_RigidBody_setType(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_setType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::physics::ERigidBodyType, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_setType : Error processing arguments");
        cobj->setType(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_setType)

static bool js_physics_RigidBody_sleep(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_sleep : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->sleep();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_sleep)

static bool js_physics_RigidBody_useGravity(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_useGravity : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_RigidBody_useGravity : Error processing arguments");
        cobj->useGravity(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_useGravity)

static bool js_physics_RigidBody_wakeUp(se::State& s)
{
    cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_RigidBody_wakeUp : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->wakeUp();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_RigidBody_wakeUp)

SE_DECLARE_FINALIZE_FUNC(js_cc_physics_RigidBody_finalize)

static bool js_physics_RigidBody_constructor(se::State& s) // constructor.c
{
    cc::physics::RigidBody* cobj = JSB_ALLOC(cc::physics::RigidBody);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_physics_RigidBody_constructor, __jsb_cc_physics_RigidBody_class, js_cc_physics_RigidBody_finalize)




static bool js_cc_physics_RigidBody_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::physics::RigidBody>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::physics::RigidBody* cobj = SE_THIS_OBJECT<cc::physics::RigidBody>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_physics_RigidBody_finalize)

bool js_register_physics_RigidBody(se::Object* obj)
{
    auto cls = se::Class::create("RigidBody", obj, nullptr, _SE(js_physics_RigidBody_constructor));

    cls->defineFunction("applyForce", _SE(js_physics_RigidBody_applyForce));
    cls->defineFunction("applyImpulse", _SE(js_physics_RigidBody_applyImpulse));
    cls->defineFunction("applyLocalForce", _SE(js_physics_RigidBody_applyLocalForce));
    cls->defineFunction("applyLocalImpulse", _SE(js_physics_RigidBody_applyLocalImpulse));
    cls->defineFunction("applyLocalTorque", _SE(js_physics_RigidBody_applyLocalTorque));
    cls->defineFunction("applyTorque", _SE(js_physics_RigidBody_applyTorque));
    cls->defineFunction("clearForces", _SE(js_physics_RigidBody_clearForces));
    cls->defineFunction("clearState", _SE(js_physics_RigidBody_clearState));
    cls->defineFunction("clearVelocity", _SE(js_physics_RigidBody_clearVelocity));
    cls->defineFunction("getAngularVelocity", _SE(js_physics_RigidBody_getAngularVelocity));
    cls->defineFunction("getLinearVelocity", _SE(js_physics_RigidBody_getLinearVelocity));
    cls->defineFunction("getSleepThreshold", _SE(js_physics_RigidBody_getSleepThreshold));
    cls->defineFunction("initialize", _SE(js_physics_RigidBody_initialize));
    cls->defineFunction("isAwake", _SE(js_physics_RigidBody_isAwake));
    cls->defineFunction("isSleeping", _SE(js_physics_RigidBody_isSleeping));
    cls->defineFunction("isSleepy", _SE(js_physics_RigidBody_isSleepy));
    cls->defineFunction("onDestroy", _SE(js_physics_RigidBody_onDestroy));
    cls->defineFunction("onDisable", _SE(js_physics_RigidBody_onDisable));
    cls->defineFunction("onEnable", _SE(js_physics_RigidBody_onEnable));
    cls->defineFunction("setAllowSleep", _SE(js_physics_RigidBody_setAllowSleep));
    cls->defineFunction("setAngularDamping", _SE(js_physics_RigidBody_setAngularDamping));
    cls->defineFunction("setAngularFactor", _SE(js_physics_RigidBody_setAngularFactor));
    cls->defineFunction("setAngularVelocity", _SE(js_physics_RigidBody_setAngularVelocity));
    cls->defineFunction("setCollisionFilter", _SE(js_physics_RigidBody_setCollisionFilter));
    cls->defineFunction("setLinearDamping", _SE(js_physics_RigidBody_setLinearDamping));
    cls->defineFunction("setLinearFactor", _SE(js_physics_RigidBody_setLinearFactor));
    cls->defineFunction("setLinearVelocity", _SE(js_physics_RigidBody_setLinearVelocity));
    cls->defineFunction("setMass", _SE(js_physics_RigidBody_setMass));
    cls->defineFunction("setSleepThreshold", _SE(js_physics_RigidBody_setSleepThreshold));
    cls->defineFunction("setType", _SE(js_physics_RigidBody_setType));
    cls->defineFunction("sleep", _SE(js_physics_RigidBody_sleep));
    cls->defineFunction("useGravity", _SE(js_physics_RigidBody_useGravity));
    cls->defineFunction("wakeUp", _SE(js_physics_RigidBody_wakeUp));
    cls->defineFinalizeFunction(_SE(js_cc_physics_RigidBody_finalize));
    cls->install();
    JSBClassType::registerClass<cc::physics::RigidBody>(cls);

    __jsb_cc_physics_RigidBody_proto = cls->getProto();
    __jsb_cc_physics_RigidBody_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cc_physics_SphereShape_proto = nullptr;
se::Class* __jsb_cc_physics_SphereShape_class = nullptr;

static bool js_physics_SphereShape_getAABB(se::State& s)
{
    cc::physics::SphereShape* cobj = SE_THIS_OBJECT<cc::physics::SphereShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_SphereShape_getAABB : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::pipeline::AABB result = cobj->getAABB();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_SphereShape_getAABB : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_SphereShape_getAABB)

static bool js_physics_SphereShape_getBoundingSphere(se::State& s)
{
    cc::physics::SphereShape* cobj = SE_THIS_OBJECT<cc::physics::SphereShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_SphereShape_getBoundingSphere : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::pipeline::Sphere result = cobj->getBoundingSphere();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_SphereShape_getBoundingSphere : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_SphereShape_getBoundingSphere)

static bool js_physics_SphereShape_getImpl(se::State& s)
{
    cc::physics::SphereShape* cobj = SE_THIS_OBJECT<cc::physics::SphereShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_SphereShape_getImpl : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getImpl();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_SphereShape_getImpl : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_SphereShape_getImpl)

static bool js_physics_SphereShape_initialize(se::State& s)
{
    cc::physics::SphereShape* cobj = SE_THIS_OBJECT<cc::physics::SphereShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_SphereShape_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_SphereShape_initialize : Error processing arguments");
        cobj->initialize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_SphereShape_initialize)

static bool js_physics_SphereShape_onDestroy(se::State& s)
{
    cc::physics::SphereShape* cobj = SE_THIS_OBJECT<cc::physics::SphereShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_SphereShape_onDestroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onDestroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_SphereShape_onDestroy)

static bool js_physics_SphereShape_onDisable(se::State& s)
{
    cc::physics::SphereShape* cobj = SE_THIS_OBJECT<cc::physics::SphereShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_SphereShape_onDisable : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onDisable();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_SphereShape_onDisable)

static bool js_physics_SphereShape_onEnable(se::State& s)
{
    cc::physics::SphereShape* cobj = SE_THIS_OBJECT<cc::physics::SphereShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_SphereShape_onEnable : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onEnable();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_SphereShape_onEnable)

static bool js_physics_SphereShape_setAsTrigger(se::State& s)
{
    cc::physics::SphereShape* cobj = SE_THIS_OBJECT<cc::physics::SphereShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_SphereShape_setAsTrigger : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_SphereShape_setAsTrigger : Error processing arguments");
        cobj->setAsTrigger(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_SphereShape_setAsTrigger)

static bool js_physics_SphereShape_setCenter(se::State& s)
{
    cc::physics::SphereShape* cobj = SE_THIS_OBJECT<cc::physics::SphereShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_SphereShape_setCenter : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_SphereShape_setCenter : Error processing arguments");
        cobj->setCenter(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_SphereShape_setCenter)

static bool js_physics_SphereShape_setCollisionFilter(se::State& s)
{
    cc::physics::SphereShape* cobj = SE_THIS_OBJECT<cc::physics::SphereShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_SphereShape_setCollisionFilter : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<int, false> arg0 = {};
        HolderType<int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_SphereShape_setCollisionFilter : Error processing arguments");
        cobj->setCollisionFilter(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_physics_SphereShape_setCollisionFilter)

static bool js_physics_SphereShape_setMaterial(se::State& s)
{
    cc::physics::SphereShape* cobj = SE_THIS_OBJECT<cc::physics::SphereShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_SphereShape_setMaterial : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_SphereShape_setMaterial : Error processing arguments");
        cobj->setMaterial(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_SphereShape_setMaterial)

static bool js_physics_SphereShape_setRadius(se::State& s)
{
    cc::physics::SphereShape* cobj = SE_THIS_OBJECT<cc::physics::SphereShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_SphereShape_setRadius : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_SphereShape_setRadius : Error processing arguments");
        cobj->setRadius(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_SphereShape_setRadius)

static bool js_physics_SphereShape_updateEventListener(se::State& s)
{
    cc::physics::SphereShape* cobj = SE_THIS_OBJECT<cc::physics::SphereShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_SphereShape_updateEventListener : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::physics::EShapeFilterFlag, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_SphereShape_updateEventListener : Error processing arguments");
        cobj->updateEventListener(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_SphereShape_updateEventListener)

SE_DECLARE_FINALIZE_FUNC(js_cc_physics_SphereShape_finalize)

static bool js_physics_SphereShape_constructor(se::State& s) // constructor.c
{
    cc::physics::SphereShape* cobj = JSB_ALLOC(cc::physics::SphereShape);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_physics_SphereShape_constructor, __jsb_cc_physics_SphereShape_class, js_cc_physics_SphereShape_finalize)




static bool js_cc_physics_SphereShape_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::physics::SphereShape>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::physics::SphereShape* cobj = SE_THIS_OBJECT<cc::physics::SphereShape>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_physics_SphereShape_finalize)

bool js_register_physics_SphereShape(se::Object* obj)
{
    auto cls = se::Class::create("SphereShape", obj, nullptr, _SE(js_physics_SphereShape_constructor));

    cls->defineFunction("getAABB", _SE(js_physics_SphereShape_getAABB));
    cls->defineFunction("getBoundingSphere", _SE(js_physics_SphereShape_getBoundingSphere));
    cls->defineFunction("getImpl", _SE(js_physics_SphereShape_getImpl));
    cls->defineFunction("initialize", _SE(js_physics_SphereShape_initialize));
    cls->defineFunction("onDestroy", _SE(js_physics_SphereShape_onDestroy));
    cls->defineFunction("onDisable", _SE(js_physics_SphereShape_onDisable));
    cls->defineFunction("onEnable", _SE(js_physics_SphereShape_onEnable));
    cls->defineFunction("setAsTrigger", _SE(js_physics_SphereShape_setAsTrigger));
    cls->defineFunction("setCenter", _SE(js_physics_SphereShape_setCenter));
    cls->defineFunction("setCollisionFilter", _SE(js_physics_SphereShape_setCollisionFilter));
    cls->defineFunction("setMaterial", _SE(js_physics_SphereShape_setMaterial));
    cls->defineFunction("setRadius", _SE(js_physics_SphereShape_setRadius));
    cls->defineFunction("updateEventListener", _SE(js_physics_SphereShape_updateEventListener));
    cls->defineFinalizeFunction(_SE(js_cc_physics_SphereShape_finalize));
    cls->install();
    JSBClassType::registerClass<cc::physics::SphereShape>(cls);

    __jsb_cc_physics_SphereShape_proto = cls->getProto();
    __jsb_cc_physics_SphereShape_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cc_physics_BoxShape_proto = nullptr;
se::Class* __jsb_cc_physics_BoxShape_class = nullptr;

static bool js_physics_BoxShape_getAABB(se::State& s)
{
    cc::physics::BoxShape* cobj = SE_THIS_OBJECT<cc::physics::BoxShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_BoxShape_getAABB : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::pipeline::AABB result = cobj->getAABB();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_BoxShape_getAABB : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_BoxShape_getAABB)

static bool js_physics_BoxShape_getBoundingSphere(se::State& s)
{
    cc::physics::BoxShape* cobj = SE_THIS_OBJECT<cc::physics::BoxShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_BoxShape_getBoundingSphere : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::pipeline::Sphere result = cobj->getBoundingSphere();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_BoxShape_getBoundingSphere : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_BoxShape_getBoundingSphere)

static bool js_physics_BoxShape_getImpl(se::State& s)
{
    cc::physics::BoxShape* cobj = SE_THIS_OBJECT<cc::physics::BoxShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_BoxShape_getImpl : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getImpl();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_BoxShape_getImpl : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_BoxShape_getImpl)

static bool js_physics_BoxShape_initialize(se::State& s)
{
    cc::physics::BoxShape* cobj = SE_THIS_OBJECT<cc::physics::BoxShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_BoxShape_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_BoxShape_initialize : Error processing arguments");
        cobj->initialize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_BoxShape_initialize)

static bool js_physics_BoxShape_onDestroy(se::State& s)
{
    cc::physics::BoxShape* cobj = SE_THIS_OBJECT<cc::physics::BoxShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_BoxShape_onDestroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onDestroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_BoxShape_onDestroy)

static bool js_physics_BoxShape_onDisable(se::State& s)
{
    cc::physics::BoxShape* cobj = SE_THIS_OBJECT<cc::physics::BoxShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_BoxShape_onDisable : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onDisable();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_BoxShape_onDisable)

static bool js_physics_BoxShape_onEnable(se::State& s)
{
    cc::physics::BoxShape* cobj = SE_THIS_OBJECT<cc::physics::BoxShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_BoxShape_onEnable : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onEnable();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_BoxShape_onEnable)

static bool js_physics_BoxShape_setAsTrigger(se::State& s)
{
    cc::physics::BoxShape* cobj = SE_THIS_OBJECT<cc::physics::BoxShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_BoxShape_setAsTrigger : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_BoxShape_setAsTrigger : Error processing arguments");
        cobj->setAsTrigger(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_BoxShape_setAsTrigger)

static bool js_physics_BoxShape_setCenter(se::State& s)
{
    cc::physics::BoxShape* cobj = SE_THIS_OBJECT<cc::physics::BoxShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_BoxShape_setCenter : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_BoxShape_setCenter : Error processing arguments");
        cobj->setCenter(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_BoxShape_setCenter)

static bool js_physics_BoxShape_setCollisionFilter(se::State& s)
{
    cc::physics::BoxShape* cobj = SE_THIS_OBJECT<cc::physics::BoxShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_BoxShape_setCollisionFilter : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<int, false> arg0 = {};
        HolderType<int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_BoxShape_setCollisionFilter : Error processing arguments");
        cobj->setCollisionFilter(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_physics_BoxShape_setCollisionFilter)

static bool js_physics_BoxShape_setMaterial(se::State& s)
{
    cc::physics::BoxShape* cobj = SE_THIS_OBJECT<cc::physics::BoxShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_BoxShape_setMaterial : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_BoxShape_setMaterial : Error processing arguments");
        cobj->setMaterial(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_BoxShape_setMaterial)

static bool js_physics_BoxShape_setSize(se::State& s)
{
    cc::physics::BoxShape* cobj = SE_THIS_OBJECT<cc::physics::BoxShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_BoxShape_setSize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_BoxShape_setSize : Error processing arguments");
        cobj->setSize(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_BoxShape_setSize)

static bool js_physics_BoxShape_updateEventListener(se::State& s)
{
    cc::physics::BoxShape* cobj = SE_THIS_OBJECT<cc::physics::BoxShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_BoxShape_updateEventListener : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::physics::EShapeFilterFlag, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_BoxShape_updateEventListener : Error processing arguments");
        cobj->updateEventListener(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_BoxShape_updateEventListener)

SE_DECLARE_FINALIZE_FUNC(js_cc_physics_BoxShape_finalize)

static bool js_physics_BoxShape_constructor(se::State& s) // constructor.c
{
    cc::physics::BoxShape* cobj = JSB_ALLOC(cc::physics::BoxShape);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_physics_BoxShape_constructor, __jsb_cc_physics_BoxShape_class, js_cc_physics_BoxShape_finalize)




static bool js_cc_physics_BoxShape_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::physics::BoxShape>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::physics::BoxShape* cobj = SE_THIS_OBJECT<cc::physics::BoxShape>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_physics_BoxShape_finalize)

bool js_register_physics_BoxShape(se::Object* obj)
{
    auto cls = se::Class::create("BoxShape", obj, nullptr, _SE(js_physics_BoxShape_constructor));

    cls->defineFunction("getAABB", _SE(js_physics_BoxShape_getAABB));
    cls->defineFunction("getBoundingSphere", _SE(js_physics_BoxShape_getBoundingSphere));
    cls->defineFunction("getImpl", _SE(js_physics_BoxShape_getImpl));
    cls->defineFunction("initialize", _SE(js_physics_BoxShape_initialize));
    cls->defineFunction("onDestroy", _SE(js_physics_BoxShape_onDestroy));
    cls->defineFunction("onDisable", _SE(js_physics_BoxShape_onDisable));
    cls->defineFunction("onEnable", _SE(js_physics_BoxShape_onEnable));
    cls->defineFunction("setAsTrigger", _SE(js_physics_BoxShape_setAsTrigger));
    cls->defineFunction("setCenter", _SE(js_physics_BoxShape_setCenter));
    cls->defineFunction("setCollisionFilter", _SE(js_physics_BoxShape_setCollisionFilter));
    cls->defineFunction("setMaterial", _SE(js_physics_BoxShape_setMaterial));
    cls->defineFunction("setSize", _SE(js_physics_BoxShape_setSize));
    cls->defineFunction("updateEventListener", _SE(js_physics_BoxShape_updateEventListener));
    cls->defineFinalizeFunction(_SE(js_cc_physics_BoxShape_finalize));
    cls->install();
    JSBClassType::registerClass<cc::physics::BoxShape>(cls);

    __jsb_cc_physics_BoxShape_proto = cls->getProto();
    __jsb_cc_physics_BoxShape_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cc_physics_CapsuleShape_proto = nullptr;
se::Class* __jsb_cc_physics_CapsuleShape_class = nullptr;

static bool js_physics_CapsuleShape_getAABB(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_getAABB : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::pipeline::AABB result = cobj->getAABB();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_CapsuleShape_getAABB : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_getAABB)

static bool js_physics_CapsuleShape_getBoundingSphere(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_getBoundingSphere : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::pipeline::Sphere result = cobj->getBoundingSphere();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_CapsuleShape_getBoundingSphere : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_getBoundingSphere)

static bool js_physics_CapsuleShape_getImpl(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_getImpl : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getImpl();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_CapsuleShape_getImpl : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_getImpl)

static bool js_physics_CapsuleShape_initialize(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_CapsuleShape_initialize : Error processing arguments");
        cobj->initialize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_initialize)

static bool js_physics_CapsuleShape_onDestroy(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_onDestroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onDestroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_onDestroy)

static bool js_physics_CapsuleShape_onDisable(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_onDisable : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onDisable();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_onDisable)

static bool js_physics_CapsuleShape_onEnable(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_onEnable : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onEnable();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_onEnable)

static bool js_physics_CapsuleShape_setAsTrigger(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_setAsTrigger : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_CapsuleShape_setAsTrigger : Error processing arguments");
        cobj->setAsTrigger(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_setAsTrigger)

static bool js_physics_CapsuleShape_setCenter(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_setCenter : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_CapsuleShape_setCenter : Error processing arguments");
        cobj->setCenter(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_setCenter)

static bool js_physics_CapsuleShape_setCollisionFilter(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_setCollisionFilter : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<int, false> arg0 = {};
        HolderType<int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_CapsuleShape_setCollisionFilter : Error processing arguments");
        cobj->setCollisionFilter(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_setCollisionFilter)

static bool js_physics_CapsuleShape_setCylinderHeight(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_setCylinderHeight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_CapsuleShape_setCylinderHeight : Error processing arguments");
        cobj->setCylinderHeight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_setCylinderHeight)

static bool js_physics_CapsuleShape_setDirection(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_setDirection : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::physics::EAxisDirection, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_CapsuleShape_setDirection : Error processing arguments");
        cobj->setDirection(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_setDirection)

static bool js_physics_CapsuleShape_setMaterial(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_setMaterial : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_CapsuleShape_setMaterial : Error processing arguments");
        cobj->setMaterial(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_setMaterial)

static bool js_physics_CapsuleShape_setRadius(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_setRadius : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_CapsuleShape_setRadius : Error processing arguments");
        cobj->setRadius(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_setRadius)

static bool js_physics_CapsuleShape_updateEventListener(se::State& s)
{
    cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_CapsuleShape_updateEventListener : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::physics::EShapeFilterFlag, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_CapsuleShape_updateEventListener : Error processing arguments");
        cobj->updateEventListener(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_CapsuleShape_updateEventListener)

SE_DECLARE_FINALIZE_FUNC(js_cc_physics_CapsuleShape_finalize)

static bool js_physics_CapsuleShape_constructor(se::State& s) // constructor.c
{
    cc::physics::CapsuleShape* cobj = JSB_ALLOC(cc::physics::CapsuleShape);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_physics_CapsuleShape_constructor, __jsb_cc_physics_CapsuleShape_class, js_cc_physics_CapsuleShape_finalize)




static bool js_cc_physics_CapsuleShape_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::physics::CapsuleShape>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::physics::CapsuleShape* cobj = SE_THIS_OBJECT<cc::physics::CapsuleShape>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_physics_CapsuleShape_finalize)

bool js_register_physics_CapsuleShape(se::Object* obj)
{
    auto cls = se::Class::create("CapsuleShape", obj, nullptr, _SE(js_physics_CapsuleShape_constructor));

    cls->defineFunction("getAABB", _SE(js_physics_CapsuleShape_getAABB));
    cls->defineFunction("getBoundingSphere", _SE(js_physics_CapsuleShape_getBoundingSphere));
    cls->defineFunction("getImpl", _SE(js_physics_CapsuleShape_getImpl));
    cls->defineFunction("initialize", _SE(js_physics_CapsuleShape_initialize));
    cls->defineFunction("onDestroy", _SE(js_physics_CapsuleShape_onDestroy));
    cls->defineFunction("onDisable", _SE(js_physics_CapsuleShape_onDisable));
    cls->defineFunction("onEnable", _SE(js_physics_CapsuleShape_onEnable));
    cls->defineFunction("setAsTrigger", _SE(js_physics_CapsuleShape_setAsTrigger));
    cls->defineFunction("setCenter", _SE(js_physics_CapsuleShape_setCenter));
    cls->defineFunction("setCollisionFilter", _SE(js_physics_CapsuleShape_setCollisionFilter));
    cls->defineFunction("setCylinderHeight", _SE(js_physics_CapsuleShape_setCylinderHeight));
    cls->defineFunction("setDirection", _SE(js_physics_CapsuleShape_setDirection));
    cls->defineFunction("setMaterial", _SE(js_physics_CapsuleShape_setMaterial));
    cls->defineFunction("setRadius", _SE(js_physics_CapsuleShape_setRadius));
    cls->defineFunction("updateEventListener", _SE(js_physics_CapsuleShape_updateEventListener));
    cls->defineFinalizeFunction(_SE(js_cc_physics_CapsuleShape_finalize));
    cls->install();
    JSBClassType::registerClass<cc::physics::CapsuleShape>(cls);

    __jsb_cc_physics_CapsuleShape_proto = cls->getProto();
    __jsb_cc_physics_CapsuleShape_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cc_physics_PlaneShape_proto = nullptr;
se::Class* __jsb_cc_physics_PlaneShape_class = nullptr;

static bool js_physics_PlaneShape_getAABB(se::State& s)
{
    cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PlaneShape_getAABB : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::pipeline::AABB result = cobj->getAABB();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_PlaneShape_getAABB : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_PlaneShape_getAABB)

static bool js_physics_PlaneShape_getBoundingSphere(se::State& s)
{
    cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PlaneShape_getBoundingSphere : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::pipeline::Sphere result = cobj->getBoundingSphere();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_PlaneShape_getBoundingSphere : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_PlaneShape_getBoundingSphere)

static bool js_physics_PlaneShape_getImpl(se::State& s)
{
    cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PlaneShape_getImpl : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getImpl();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_PlaneShape_getImpl : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_PlaneShape_getImpl)

static bool js_physics_PlaneShape_initialize(se::State& s)
{
    cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PlaneShape_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_PlaneShape_initialize : Error processing arguments");
        cobj->initialize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_PlaneShape_initialize)

static bool js_physics_PlaneShape_onDestroy(se::State& s)
{
    cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PlaneShape_onDestroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onDestroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_PlaneShape_onDestroy)

static bool js_physics_PlaneShape_onDisable(se::State& s)
{
    cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PlaneShape_onDisable : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onDisable();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_PlaneShape_onDisable)

static bool js_physics_PlaneShape_onEnable(se::State& s)
{
    cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PlaneShape_onEnable : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onEnable();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_PlaneShape_onEnable)

static bool js_physics_PlaneShape_setAsTrigger(se::State& s)
{
    cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PlaneShape_setAsTrigger : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_PlaneShape_setAsTrigger : Error processing arguments");
        cobj->setAsTrigger(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_PlaneShape_setAsTrigger)

static bool js_physics_PlaneShape_setCenter(se::State& s)
{
    cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PlaneShape_setCenter : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_PlaneShape_setCenter : Error processing arguments");
        cobj->setCenter(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_PlaneShape_setCenter)

static bool js_physics_PlaneShape_setCollisionFilter(se::State& s)
{
    cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PlaneShape_setCollisionFilter : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<int, false> arg0 = {};
        HolderType<int, false> arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_PlaneShape_setCollisionFilter : Error processing arguments");
        cobj->setCollisionFilter(arg0.value(), arg1.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_physics_PlaneShape_setCollisionFilter)

static bool js_physics_PlaneShape_setConstant(se::State& s)
{
    cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PlaneShape_setConstant : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_PlaneShape_setConstant : Error processing arguments");
        cobj->setConstant(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_PlaneShape_setConstant)

static bool js_physics_PlaneShape_setMaterial(se::State& s)
{
    cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PlaneShape_setMaterial : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_PlaneShape_setMaterial : Error processing arguments");
        cobj->setMaterial(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_PlaneShape_setMaterial)

static bool js_physics_PlaneShape_setNormal(se::State& s)
{
    cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PlaneShape_setNormal : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_PlaneShape_setNormal : Error processing arguments");
        cobj->setNormal(arg0.value(), arg1.value(), arg2.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_physics_PlaneShape_setNormal)

static bool js_physics_PlaneShape_updateEventListener(se::State& s)
{
    cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PlaneShape_updateEventListener : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::physics::EShapeFilterFlag, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_physics_PlaneShape_updateEventListener : Error processing arguments");
        cobj->updateEventListener(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_physics_PlaneShape_updateEventListener)

SE_DECLARE_FINALIZE_FUNC(js_cc_physics_PlaneShape_finalize)

static bool js_physics_PlaneShape_constructor(se::State& s) // constructor.c
{
    cc::physics::PlaneShape* cobj = JSB_ALLOC(cc::physics::PlaneShape);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_physics_PlaneShape_constructor, __jsb_cc_physics_PlaneShape_class, js_cc_physics_PlaneShape_finalize)




static bool js_cc_physics_PlaneShape_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::physics::PlaneShape>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::physics::PlaneShape* cobj = SE_THIS_OBJECT<cc::physics::PlaneShape>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_physics_PlaneShape_finalize)

bool js_register_physics_PlaneShape(se::Object* obj)
{
    auto cls = se::Class::create("PlaneShape", obj, nullptr, _SE(js_physics_PlaneShape_constructor));

    cls->defineFunction("getAABB", _SE(js_physics_PlaneShape_getAABB));
    cls->defineFunction("getBoundingSphere", _SE(js_physics_PlaneShape_getBoundingSphere));
    cls->defineFunction("getImpl", _SE(js_physics_PlaneShape_getImpl));
    cls->defineFunction("initialize", _SE(js_physics_PlaneShape_initialize));
    cls->defineFunction("onDestroy", _SE(js_physics_PlaneShape_onDestroy));
    cls->defineFunction("onDisable", _SE(js_physics_PlaneShape_onDisable));
    cls->defineFunction("onEnable", _SE(js_physics_PlaneShape_onEnable));
    cls->defineFunction("setAsTrigger", _SE(js_physics_PlaneShape_setAsTrigger));
    cls->defineFunction("setCenter", _SE(js_physics_PlaneShape_setCenter));
    cls->defineFunction("setCollisionFilter", _SE(js_physics_PlaneShape_setCollisionFilter));
    cls->defineFunction("setConstant", _SE(js_physics_PlaneShape_setConstant));
    cls->defineFunction("setMaterial", _SE(js_physics_PlaneShape_setMaterial));
    cls->defineFunction("setNormal", _SE(js_physics_PlaneShape_setNormal));
    cls->defineFunction("updateEventListener", _SE(js_physics_PlaneShape_updateEventListener));
    cls->defineFinalizeFunction(_SE(js_cc_physics_PlaneShape_finalize));
    cls->install();
    JSBClassType::registerClass<cc::physics::PlaneShape>(cls);

    __jsb_cc_physics_PlaneShape_proto = cls->getProto();
    __jsb_cc_physics_PlaneShape_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cc_physics_PhysXBindings_proto = nullptr;
se::Class* __jsb_cc_physics_PhysXBindings_class = nullptr;

static bool js_physics_PhysXBindings_testAPI(se::State& s)
{
    cc::physics::PhysXBindings* cobj = SE_THIS_OBJECT<cc::physics::PhysXBindings>(s);
    SE_PRECONDITION2(cobj, false, "js_physics_PhysXBindings_testAPI : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->testAPI();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_PhysXBindings_testAPI : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_PhysXBindings_testAPI)

static bool js_physics_PhysXBindings_getLength(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cc::physics::PhysXBindings::getLength();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_PhysXBindings_getLength : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_PhysXBindings_getLength)

static bool js_physics_PhysXBindings_modifyByPtr(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        HolderType<int, false> arg0 = {};
        HolderType<float, false> arg1 = {};
        HolderType<float, false> arg2 = {};
        HolderType<float, false> arg3 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        ok &= sevalue_to_native(args[1], &arg1, nullptr);
        ok &= sevalue_to_native(args[2], &arg2, nullptr);
        ok &= sevalue_to_native(args[3], &arg3, nullptr);
        SE_PRECONDITION2(ok, false, "js_physics_PhysXBindings_modifyByPtr : Error processing arguments");
        cc::physics::PhysXBindings::modifyByPtr(arg0.value(), arg1.value(), arg2.value(), arg3.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_physics_PhysXBindings_modifyByPtr)

static bool js_physics_PhysXBindings_getPtr(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const int result = cc::physics::PhysXBindings::getPtr();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_physics_PhysXBindings_getPtr : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_physics_PhysXBindings_getPtr)



static bool js_cc_physics_PhysXBindings_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::physics::PhysXBindings>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::physics::PhysXBindings* cobj = SE_THIS_OBJECT<cc::physics::PhysXBindings>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_physics_PhysXBindings_finalize)

bool js_register_physics_PhysXBindings(se::Object* obj)
{
    auto cls = se::Class::create("PhysXBindings", obj, nullptr, nullptr);

    cls->defineFunction("testAPI", _SE(js_physics_PhysXBindings_testAPI));
    cls->defineStaticFunction("getLength", _SE(js_physics_PhysXBindings_getLength));
    cls->defineStaticFunction("modifyByPtr", _SE(js_physics_PhysXBindings_modifyByPtr));
    cls->defineStaticFunction("getPtr", _SE(js_physics_PhysXBindings_getPtr));
    cls->defineFinalizeFunction(_SE(js_cc_physics_PhysXBindings_finalize));
    cls->install();
    JSBClassType::registerClass<cc::physics::PhysXBindings>(cls);

    __jsb_cc_physics_PhysXBindings_proto = cls->getProto();
    __jsb_cc_physics_PhysXBindings_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_physics(se::Object* obj)
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("jsb.physics", &nsVal))
    {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("jsb.physics", nsVal);
    }
    se::Object* ns = nsVal.toObject();

    js_register_physics_RigidBody(ns);
    js_register_physics_PhysXBindings(ns);
    js_register_physics_SphereShape(ns);
    js_register_physics_PlaneShape(ns);
    js_register_physics_CapsuleShape(ns);
    js_register_physics_BoxShape(ns);
    js_register_physics_World(ns);
    return true;
}

#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
