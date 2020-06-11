#pragma once

#include "core/CoreStd.h"

NS_PP_BEGIN

class RenderStage;
class RenderFlow;

struct CC_DLL RenderObject {
    //TODO
};
typedef cocos2d::vector<struct RenderObject>::type RenderObjectList;

struct CC_DLL RenderPipelineInfo {
    //TODO
};

struct CC_DLL RenderStageInfo {
    cocos2d::String name;
    int priority = 0;
    cocos2d::String framebuffer;
    // renderQueues?: RenderQueueDesc[];
};

struct CC_DLL RenderFlowInfo {
    //TODO
};

typedef cocos2d::vector<RenderStage *>::type RenderStageList;
typedef cocos2d::vector<RenderFlow *>::type RenderFlowList;

NS_PP_END
