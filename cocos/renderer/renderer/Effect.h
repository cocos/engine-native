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

#include <vector>
#include <unordered_map>
#include <map>
#include "base/CCRef.h"
#include "base/CCValue.h"
#include "../Macro.h"
#include "Technique.h"
#include "Pass.h"
#include "EffectBase.h"

RENDERER_BEGIN

/**
 * @addtogroup renderer
 * @{
 */

/**
 * @brief Fundamental class of material system, contains techniques, shader template define settings and uniform properties.\n
 * JS API: renderer.Effect
 * @code
 * let pass = new renderer.Pass('sprite');
 * pass.setDepth(false, false);
 * pass.setCullMode(gfx.CULL_NONE);
 * let mainTech = new renderer.Technique(
 *     ['transparent'],
 *     [
 *         { name: 'texture', type: renderer.PARAM_TEXTURE_2D },
 *         { name: 'color', type: renderer.PARAM_COLOR4 }
 *     ],
 *     [
 *         pass
 *     ]
 * );
 * let effect = new renderer.Effect(
 *     [
 *         mainTech
 *     ],
 *     {
 *         'color': {r: 1, g: 1, b: 1, a: 1}
 *     },
 *     [
 *         { name: 'useTexture', value: true },
 *         { name: 'useModel', value: false },
 *         { name: 'alphaTest', value: false },
 *         { name: 'useColor', value: true }
 *     ]
 * );
 * @endcode
 */
class Effect : public EffectBase
{
public:
    using Property = Technique::Parameter;
    
    /*
     * @brief The default constructor.
     */
    Effect();
    /*
     *  @brief The default destructor.
     */
    ~Effect();
    
    /*
     * @brief Initialize with techniques, properties and define settings.
     * @param[in] techniques All techniques in an array
     * @param[in] properties All properties in a map
     * @param[in] defineTemplates All defines and their value in a map
     */
    void init(const Vector<Technique*>& techniques);
    /**
     *  @brief Clears techniques and define list.
     */
    void clear();

    /**
     *  @brief Deep copy from other effect.
     */
    void copy(const Effect* effect);
    
    Vector<Pass*>& getPasses() { return _technique->getPasses(); }
    const Vector<Pass*>& getPasses() const { return _technique->getPasses(); }
    
    void switchTechnique(int techniqueIndex);
private:
    Vector<Technique*> _techniques;
    Technique* _technique;
    
};

// end of renderer group
/// @}

RENDERER_END
