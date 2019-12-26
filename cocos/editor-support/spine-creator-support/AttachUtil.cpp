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

#include "spine-creator-support/AttachUtil.h"

USING_NS_CC;
using namespace cocos2d::renderer;

namespace spine {
    void AttachUtilBase::releaseAttachedNode() {
        for (std::size_t i = 0, n = _attachedNodes.size(); i < n; i++) {
            auto node = _attachedNodes[i];
            if (node) {
                node->release();
            }
        }
        _attachedNodes.clear();
        
        if (_attachedRootNode) {
            _attachedRootNode->release();
            _attachedRootNode = nullptr;
        }
    }
    
    void AttachUtilBase::associateAttachedNode(spine::Skeleton* skeleton, cocos2d::renderer::NodeProxy* skeletonNode) {
        releaseAttachedNode();
        if (!skeletonNode || !skeleton) return;
        
        auto rootNode = skeletonNode->getChildByName("ATTACHED_NODE_TREE");
        if (!rootNode || !rootNode->isValid()) return;
        _attachedRootNode = rootNode;
        _attachedRootNode->retain();
        _attachedRootNode->enableUpdateWorldMatrix(false);
        _attachedRootNode->switchTraverseToVisit();
        
        auto& bones = skeleton->getBones();
        for (std::size_t i = 0, n = bones.size(); i < n; i++) {
            auto bone = bones[i];
            auto& boneData = bone->getData();
            std::string boneName = "ATTACHED_NODE:";
            boneName.append(boneData.getName().buffer());
            
            NodeProxy* parentNode = nullptr;
            if (bone->getParent()) {
                auto parentIndex = bone->getParent()->getData().getIndex();
                if (parentIndex < _attachedNodes.size()) {
                    parentNode = _attachedNodes[parentIndex];
                }
            } else {
                parentNode = rootNode;
            }
            
            NodeProxy* boneNode = nullptr;
            if (parentNode)
            {
                boneNode = parentNode->getChildByName(boneName);
                if (boneNode && boneNode->isValid())
                {
                    boneNode->enableUpdateWorldMatrix(false);
                    boneNode->retain();
                }
            }
            _attachedNodes.push_back(boneNode);
        }
    }
    
    void RealTimeAttachUtil::syncAttachedNode(cocos2d::renderer::NodeProxy* skeletonNode, spine::Skeleton* skeleton)
    {
        static cocos2d::Mat4 boneMat;
        static cocos2d::Mat4 nodeWorldMat;
        if (!skeletonNode || !_attachedRootNode || !skeleton) return;
        if (!_attachedRootNode->isValid())
        {
            _attachedRootNode->release();
            _attachedRootNode = nullptr;
            return;
        }
        
        auto& rootMatrix = skeletonNode->getWorldMatrix();
        _attachedRootNode->updateWorldMatrix(rootMatrix);
        
        int lastValidIdx = -1;
        auto& bones = skeleton->getBones();
        for (int i = 0, n = (int)_attachedNodes.size(); i < n; i++)
        {
            auto boneNode = _attachedNodes[i];
            if (!boneNode)
            {
                continue;
            }
            if (!boneNode->isValid())
            {
                boneNode->release();
                _attachedNodes[i] = nullptr;
                continue;
            }
            auto bone = bones[i];
            if (!bone)
            {
                boneNode->enableVisit(false);
                boneNode->release();
                _attachedNodes[i] = nullptr;
                continue;
            }
            boneNode->enableVisit(true);
            
            auto& matm = boneMat.m;
            matm[0] = bone->getA();
            matm[1] = bone->getC();
            matm[4] = bone->getB();
            matm[5] = bone->getD();
            matm[12] = bone->getWorldX();
            matm[13] = bone->getWorldY();
            cocos2d::Mat4::multiply(_attachedRootNode->getWorldMatrix(), boneMat, &nodeWorldMat);
            
            boneNode->updateWorldMatrix(nodeWorldMat);
            lastValidIdx = i;
        }
        _attachedNodes.resize(lastValidIdx + 1);
    }
    
    void CacheModeAttachUtil::syncAttachedNode(cocos2d::renderer::NodeProxy* skeletonNode, SkeletonCache::FrameData* frameData)
    {
        static cocos2d::Mat4 nodeWorldMat;
        if (!skeletonNode || !_attachedRootNode) return;
        if (!_attachedRootNode->isValid())
        {
            _attachedRootNode->release();
            _attachedRootNode = nullptr;
            return;
        }
        
        auto& rootMatrix = skeletonNode->getWorldMatrix();
        _attachedRootNode->updateWorldMatrix(rootMatrix);
        
        auto& bonesData = frameData->getBones();
        auto boneCount = frameData->getBoneCount();
        int lastValidIdx = -1;
        for (int i = 0, n = (int)_attachedNodes.size(); i < n; i++)
        {
            auto boneNode = _attachedNodes[i];
            if (!boneNode)
            {
                continue;
            }
            if (!boneNode->isValid())
            {
                boneNode->release();
                _attachedNodes[i] = nullptr;
                continue;
            }
            if (i >= boneCount)
            {
                boneNode->enableVisit(false);
                lastValidIdx = i;
                continue;
            }
            auto bone = bonesData[i];
            boneNode->enableVisit(true);
            
            cocos2d::Mat4::multiply(_attachedRootNode->getWorldMatrix(), bone->globalTransformMatrix, &nodeWorldMat);
            boneNode->updateWorldMatrix(nodeWorldMat);
            lastValidIdx = i;
        }
        _attachedNodes.resize(lastValidIdx + 1);
    }
}
