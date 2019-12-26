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

#include "Effect.h"
#include "Config.h"

RENDERER_BEGIN

Effect::Effect()
{}

void Effect::init(const Vector<Technique*>& techniques)
{
    _techniques = techniques;
    switchTechnique(0);
}

Effect::~Effect()
{
//    RENDERER_LOGD("Effect destruction: %p", this);
    clear();
}

void Effect::clear()
{
    _techniques.clear();
}

void Effect::copy(const Effect* effect)
{
    auto& otherTech = effect->_techniques;
    for (auto it = otherTech.begin(); it != otherTech.end(); it ++)
    {
        auto tech = new Technique();
        tech->autorelease();
        tech->copy(**it);
        _techniques.pushBack(tech);
    }
    
    switchTechnique(0);
}

void Effect::switchTechnique(int techniqueIndex)
{
    if (techniqueIndex >= _techniques.size())
    {
        CCLOGINFO("Can not switch to technique with index [%d]", techniqueIndex);
        return;
    }
    _technique = _techniques.at(techniqueIndex);
}

RENDERER_END
