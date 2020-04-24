#include "VKStd.h"
#include "VKQueue.h"
#include "VKCommands.h"

NS_CC_BEGIN

CCVKQueue::CCVKQueue(GFXDevice* device)
    : GFXQueue(device)
{
}

CCVKQueue::~CCVKQueue()
{
}

bool CCVKQueue::initialize(const GFXQueueInfo &info)
{
    _type = info.type;

    _gpuQueue = CC_NEW(CCVKGPUQueue);
    _gpuQueue->type = _type;
    CCVKCmdFuncGetDeviceQueue((CCVKDevice*)_device, _gpuQueue);

    _status = GFXStatus::SUCCESS;
    return true;
}

void CCVKQueue::destroy()
{
    if (_gpuQueue)
    {
        _gpuQueue->vkQueue = VK_NULL_HANDLE;
        CC_DELETE(_gpuQueue);
        _gpuQueue = nullptr;
    }
    _status = GFXStatus::UNREADY;
}

void CCVKQueue::submit(const std::vector<GFXCommandBuffer*>& cmd_buffs)
{
    if (!_isAsync) {
        uint count = static_cast<uint>(cmd_buffs.size());
        for (uint i = 0; i < count; ++i) {
            //CCVKCommandBuffer* cmd_buff = (CCVKCommandBuffer*)cmd_buffs[i];
            //CCVKCmdFuncExecuteCmds((CCVKDevice*)_device, cmd_buff->_cmdPackage);
            //_numDrawCalls += cmd_buff->_numDrawCalls;
            //_numInstances += cmd_buff->_numInstances;
            //_numTriangles += cmd_buff->_numTriangles;
        }
    }
}

NS_CC_END
