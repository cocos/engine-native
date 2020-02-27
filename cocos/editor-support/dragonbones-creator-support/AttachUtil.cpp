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

#include "dragonbones-creator-support/AttachUtil.h"

USING_NS_CC;
using namespace cocos2d::renderer;

DRAGONBONES_NAMESPACE_BEGIN

void AttachUtilBase::releaseAttachedNode()
{
    _attachedBones.clear();
    _armatureRootNodes.clear();
    
    for (std::size_t i = 0, n = _attachedNodes.size(); i < n; i++)
    {
        auto node = _attachedNodes[i];
        if (node)
        {
            node->release();
        }
    }
    _attachedNodes.clear();
    
    if (_attachedRootNode)
    {
        _attachedRootNode->release();
        _attachedRootNode = nullptr;
    }
}

void AttachUtilBase::associateAttachedNode(Armature* rootArmature, NodeProxy* armatureNode)
{
    static std::map<dragonBones::Bone*, NodeProxy*> _findBoneNode;
    releaseAttachedNode();
    if (!armatureNode) return;
    
    auto rootNode = armatureNode->getChildByName("ATTACHED_NODE_TREE");
    if (!rootNode || !rootNode->isValid()) return;
    _attachedRootNode = rootNode;
    _attachedRootNode->retain();
    _attachedRootNode->enableUpdateWorldMatrix(false);
    _attachedRootNode->switchTraverseToVisit();
    _findBoneNode.clear();
    
    std::function<void(Armature*)> traverse = [&](Armature* armature) {
        if (!armature) return;
        
        NodeProxy* subArmatureParentNode = nullptr;
        if (armature->getParent())
        {
            auto parentSlot = armature->getParent();
            auto parentBone = parentSlot->getParent();
            
            auto it = _findBoneNode.find(parentBone);
            if (it != _findBoneNode.end())
            {
                subArmatureParentNode = it->second;
            }
        }
        else
        {
            subArmatureParentNode = rootNode;
        }
        
        auto& bones = armature->getBones();
        for (auto& bone : bones)
        {
            _attachedBones.push_back(bone);
            std::string boneName = "ATTACHED_NODE:";
            boneName.append(bone->getName());
            
            NodeProxy* parentNode = nullptr;
            if (bone->getParent())
            {
                auto it = _findBoneNode.find(bone->getParent());
                if (it != _findBoneNode.end())
                {
                    parentNode = it->second;
                }
            }
            else
            {
                parentNode = subArmatureParentNode;
            }
            
            NodeProxy* boneNode = nullptr;
            if (parentNode)
            {
                boneNode = parentNode->getChildByName(boneName);
                if (boneNode && boneNode->isValid())
                {
                    boneNode->enableUpdateWorldMatrix(false);
                    boneNode->retain();
                    _findBoneNode[bone] = boneNode;
                }
            }
            _attachedNodes.push_back(boneNode);
            _armatureRootNodes.push_back(subArmatureParentNode);
        }
        
        auto& slots = armature->getSlots();
        for(auto slot : slots)
        {
            CCSlot* ccSlot = (CCSlot*)slot;
            Armature* childArmature = ccSlot->getChildArmature();
            if (childArmature != nullptr)
            {
                traverse(childArmature);
            }
        }
    };
    traverse(rootArmature);
}

void RealTimeAttachUtil::syncAttachedNode(NodeProxy* armatureNode)
{
    static cocos2d::Mat4 boneMat;
    static cocos2d::Mat4 nodeWorldMat;
    if (!armatureNode || !_attachedRootNode) return;
    if (!_attachedRootNode->isValid())
    {
        _attachedRootNode->release();
        _attachedRootNode = nullptr;
        return;
    }
    
    auto& rootMatrix = armatureNode->getWorldMatrix();
    _attachedRootNode->updateWorldMatrix(rootMatrix);
    
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
        auto bone = _attachedBones[i];
        if (!bone || bone->isInPool())
        {
            boneNode->enableVisit(false);
            boneNode->release();
            _attachedNodes[i] = nullptr;
            _attachedBones[i] = nullptr;
            continue;
        }
        boneNode->enableVisit(true);
        
        auto armatureRootNode = _armatureRootNodes[i];
        auto& boneOriginMat = bone->globalTransformMatrix;
        auto& matm = boneMat.m;
        matm[0] = boneOriginMat.a;
        matm[1] = boneOriginMat.b;
        matm[4] = -boneOriginMat.c;
        matm[5] = -boneOriginMat.d;
        matm[12] = boneOriginMat.tx;
        matm[13] = boneOriginMat.ty;
        cocos2d::Mat4::multiply(armatureRootNode->getWorldMatrix(), boneMat, &nodeWorldMat);
        
        boneNode->updateWorldMatrix(nodeWorldMat);
        lastValidIdx = i;
    }
    _attachedNodes.resize(lastValidIdx + 1);
}

void CacheModeAttachUtil::syncAttachedNode(NodeProxy* armatureNode, ArmatureCache::FrameData* frameData)
{
    static cocos2d::Mat4 nodeWorldMat;
    if (!armatureNode || !_attachedRootNode) return;
    if (!_attachedRootNode->isValid())
    {
        _attachedRootNode->release();
        _attachedRootNode = nullptr;
        return;
    }
    
    auto& rootMatrix = armatureNode->getWorldMatrix();
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
        
        auto armatureRootNode = _armatureRootNodes[i];
        cocos2d::Mat4::multiply(armatureRootNode->getWorldMatrix(), bone->globalTransformMatrix, &nodeWorldMat);
        boneNode->updateWorldMatrix(nodeWorldMat);
        lastValidIdx = i;
    }
    _attachedNodes.resize(lastValidIdx + 1);
}

DRAGONBONES_NAMESPACE_END
