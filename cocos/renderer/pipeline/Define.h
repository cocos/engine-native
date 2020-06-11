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

struct CC_DLL RenderViewInfo {
    //TODO
};

struct CC_DLL RenderTargetInfo {
    uint width = 0;
    uint height = 0;
};

typedef cocos2d::vector<RenderStage *>::type RenderStageList;
typedef cocos2d::vector<RenderFlow *>::type RenderFlowList;

//TODO
const uint CAMERA_DEFAULT_MASK = 1;
//constexpr CAMERA_DEFAULT_MASK = Layers.makeMaskExclude([Layers.BitMask.UI_2D, Layers.BitMask.GIZMOS, Layers.BitMask.EDITOR,
//                                                           Layers.BitMask.SCENE_GIZMO, Layers.BitMask.PROFILER]);

NS_PP_END
