#ifndef CC_GFXCCVK_CCVK_COMMAND_ALLOCATOR_H_
#define CC_GFXCCVK_CCVK_COMMAND_ALLOCATOR_H_

#include "gfx/GFXCommandPool.h"
#include "VKCommands.h"

NS_CC_BEGIN

class CC_VULKAN_API CCVKCommandAllocator : public GFXCommandAllocator {
public:
  CCVKCommandAllocator(GFXDevice* device);
  ~CCVKCommandAllocator();
  
  GFXCommandPool<CCVKCmdBeginRenderPass> beginRenderPassCmdPool;
  GFXCommandPool<CCVKCmdBindStates> bindStatesCmdPool;
  GFXCommandPool<CCVKCmdDraw> drawCmdPool;
  GFXCommandPool<CCVKCmdUpdateBuffer> updateBufferCmdPool;
  GFXCommandPool<CCVKCmdCopyBufferToTexture> copyBufferToTextureCmdPool;
  
public:
  bool initialize(const GFXCommandAllocatorInfo& info);
  void destroy();
  
  void clearCmds(CCVKCmdPackage* cmd_package);
  
  CC_INLINE void releaseCmds() {
    beginRenderPassCmdPool.release();
    bindStatesCmdPool.release();
    drawCmdPool.release();
    updateBufferCmdPool.release();
    copyBufferToTextureCmdPool.release();
  }
};

NS_CC_END

#endif
