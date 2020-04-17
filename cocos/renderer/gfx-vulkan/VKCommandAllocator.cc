#include "VKStd.h"
#include "VKCommandAllocator.h"

NS_CC_BEGIN

CCVKCommandAllocator::CCVKCommandAllocator(GFXDevice* device)
    : GFXCommandAllocator(device) {
}

CCVKCommandAllocator::~CCVKCommandAllocator() {
}

bool CCVKCommandAllocator::initialize(const GFXCommandAllocatorInfo& info) {
    _status = GFXStatus::SUCCESS;
  return true;
}

void CCVKCommandAllocator::destroy() {
    _status = GFXStatus::UNREADY;
}

void CCVKCommandAllocator::clearCmds(CCVKCmdPackage* cmd_package) {
  if (cmd_package->beginRenderPassCmds.size()) {
    beginRenderPassCmdPool.freeCmds(cmd_package->beginRenderPassCmds);
  }
  if (cmd_package->bindStatesCmds.size()) {
    bindStatesCmdPool.freeCmds(cmd_package->bindStatesCmds);
  }
  if (cmd_package->drawCmds.size()) {
    drawCmdPool.freeCmds(cmd_package->drawCmds);
  }
  if (cmd_package->updateBufferCmds.size()) {
    updateBufferCmdPool.freeCmds(cmd_package->updateBufferCmds);
  }
  if (cmd_package->copyBufferToTextureCmds.size()) {
    copyBufferToTextureCmdPool.freeCmds(cmd_package->copyBufferToTextureCmds);
  }

  cmd_package->cmds.clear();
}

NS_CC_END
