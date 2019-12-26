/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#pragma once

#include "spine/spine.h"
#include "renderer/scene/NodeProxy.hpp"
#include "spine-creator-support/SkeletonCache.h"
#include "base/CCRef.h"
#include <vector>
#include <string>

namespace spine {
    class AttachUtilBase : public cocos2d::Ref
    {
    public:
        AttachUtilBase () {}
        virtual ~AttachUtilBase()
        {
            releaseAttachedNode();
        }
        
        /**
         * @brief Associate node with slot.
         */
        virtual void associateAttachedNode(spine::Skeleton* skeleton, cocos2d::renderer::NodeProxy* skeletonNode);
        
        /**
         * @brief release attached node.
         */
        void releaseAttachedNode();
    protected:
        std::vector<cocos2d::renderer::NodeProxy*> _attachedNodes;
        cocos2d::renderer::NodeProxy* _attachedRootNode = nullptr;
    };
    
    class RealTimeAttachUtil : public AttachUtilBase
    {
    public:
        RealTimeAttachUtil() {}
        virtual ~RealTimeAttachUtil() {}
        void syncAttachedNode(cocos2d::renderer::NodeProxy* skeletonNode, spine::Skeleton* skeleton);
    };
    
    class CacheModeAttachUtil : public AttachUtilBase
    {
    public:
        CacheModeAttachUtil() {}
        virtual ~CacheModeAttachUtil() {}
        void syncAttachedNode(cocos2d::renderer::NodeProxy* skeletonNode, SkeletonCache::FrameData* frameData);
    };
}
