/****************************************************************************
Copyright (c) 2020 Xiamen Yaji Software Co., Ltd.

http://www.cocos.com

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


#include "base/ccMacros.h"
#include "2d/CCTTFTypes.h"
#include "base/ccConfig.h"
#include <memory>

#if CC_ENABLE_TTF_LABEL_RENDERER

namespace se {
    class Object;
}

namespace cocos2d {

    namespace renderer {
        class Texture2D;
        class Effect;
        class EffectVariant;
        class NodeProxy;
    }
    class LabelLayout;

    class LabelRenderer : public cocos2d::Ref {

    private:
        enum UpdateFlags {
            UPDATE_CONTENT = 1 << 0,
            UPDATE_FONT = 1 << 1,
            UPDATE_EFFECT = 1 << 2
        };

        
    public:

        struct LabelRendererConfig {
            uint32_t updateFlags = 0xFFFFFFFF;
            float fontSize = 20.0f;
            float fontSizeRetina = 0.0f;
        };
        
        LabelRenderer();

        virtual ~LabelRenderer();

        void bindNodeProxy(cocos2d::renderer::NodeProxy* node);

        void setEffect(cocos2d::renderer::EffectVariant* effect);

        void render();
 
        void bindSharedBlock(se::Object *selfObj, void *cfg, void *layout);
        
    private:

        void genStringLayout();

        void renderIfChange();
        void doRender();

        std::string getString();
        std::string getFontPath();
        
        std::unique_ptr<LabelLayout> _stringLayout;
        se::Object *_selfObj = nullptr;
        //export arraybuffer to js
        LabelRendererConfig *_cfg =  nullptr;
        LabelLayoutInfo *_layoutInfo = nullptr;

        cocos2d::renderer::NodeProxy* _nodeProxy = nullptr;
        cocos2d::renderer::EffectVariant * _effect = nullptr;

    };
}

#endif
