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

#include "CustomProperties.hpp"

RENDERER_BEGIN
CustomProperties::CustomProperties(Effect* effect)
{
    setEffect(effect);
}

CustomProperties::~CustomProperties()
{
    _properties.clear();
    _defines.clear();
}

void CustomProperties::generateDefinesKey()
{
    _definesKey = "";
    for (auto& def : _defines) {
        _definesKey += def.first + def.second.asString();
    }
}

void CustomProperties::setEffect(Effect *effect)
{
    _effect = effect;
    
    _defines.clear();
    _properties.clear();
    _dirty = true;
    
    auto& passes = effect->getPasses();
    _passes.clear();
    for (size_t i = 0, l = passes.size(); i < l; i++) {
        Pass* pass = passes.at(i);
        _passes.pushBack(new Pass(pass->getProgramName(), pass));
    }
}

RENDERER_END
