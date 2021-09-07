/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "Game.h"
#include "cocos/bindings/event/CustomEventTypes.h"
#include "cocos/bindings/event/EventDispatcher.h"
#include "cocos/bindings/jswrapper/SeApi.h"
#include "cocos/bindings/manual/jsb_classtype.h"
#include "cocos/bindings/manual/jsb_global.h"
#include "cocos/bindings/manual/jsb_module_register.h"

#if (CC_PLATFORM == CC_PLATFORM_MAC_IOS)
#include "platform/Device.h"
#endif

Game::Game() : cc::CocosApplication() {}

int Game::init() {
  CreateWindow("My game", 0, 0, 800, 600,
               cc::ISystemWindow::CC_WINDOW_SHOWN |
                   cc::ISystemWindow::CC_WINDOW_RESIZABLE |
                   cc::ISystemWindow::CC_WINDOW_INPUT_FOCUS);
  int ret = cc::CocosApplication::init();
  if (ret != 0) {
    return ret;
  }

  SetXXTeaKey("");
  SetDebugIpAndPort("0.0.0.0", 6086, false);

  JsRunScript("jsb-adapter/jsb-builtin.js");
  JsRunScript("main.js");
  return 0;
}

void Game::onPause() {
  //    //cc::Application::onPause();
  //    cc::EventDispatcher::dispatchEnterBackgroundEvent();
}
//
void Game::onResume() {
  //    //cc::Application::onResume();
  //    cc::EventDispatcher::dispatchEnterForegroundEvent();
}
//
void Game::onClose() {
  //    //cc::Application::onClose();
  //    cc::EventDispatcher::dispatchCloseEvent();
}
