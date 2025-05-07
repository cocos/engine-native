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
#include <functional>
#include <string>

namespace cocos2d
{
    
// Touch event related
    
struct TouchInfo
{
    float x = 0;
    float y = 0;
    int index = 0;
};

struct TouchEvent
{
    enum class Type : uint8_t
    {
        BEGAN,
        MOVED,
        ENDED,
        CANCELLED,
        UNKNOWN
    };
    
    std::vector<TouchInfo> touches;
    Type type = Type::UNKNOWN;
};

struct MouseEvent
{
    enum class Type : uint8_t
    {
        DOWN,
        UP,
        MOVE,
        WHEEL,
        UNKNOWN
    };

    float x = 0.0f;
    float y = 0.0f;
    // The button number that was pressed when the mouse event was fired: Left button=0, middle button=1 (if present), right button=2.
    // For mice configured for left handed use in which the button actions are reversed the values are instead read from right to left.
    unsigned short button = 0;
    Type type = Type::UNKNOWN;
};

enum class KeyCode {
    /**
     * @en The back key on mobile phone
     * @zh 移动端返回键
     */
    MOBILE_BACK = 6,
    BACKSPACE = 8,
    TAB = 9,
    NUM_LOCK = 12,
    NUMPAD_ENTER = 20013,
    ENTER = 13,
    SHIFT_RIGHT = 20016,
    SHIFT_LEFT = 16,
    CONTROL_LEFT = 17,
    CONTROL_RIGHT = 20017,
    ALT_RIGHT = 20018,
    ALT_LEFT = 18,
    PAUSE = 19,
    CAPS_LOCK = 20,
    ESCAPE = 27,
    SPACE = 32,
    PAGE_UP = 33,
    PAGE_DOWN = 34,
    END = 35,
    HOME = 36,
    ARROW_LEFT = 37,
    ARROW_UP = 38,
    ARROW_RIGHT = 39,
    ARROW_DOWN = 40,
    INSERT = 45,
    DELETE_KEY = 46, // DELETE has conflict
    META_LEFT = 91,
    CONTEXT_MENU = 20093,
    PRINT_SCREEN = 20094,
    META_RIGHT = 93,
    NUMPAD_MULTIPLY = 106,
    NUMPAD_PLUS = 107,
    NUMPAD_MINUS = 109,
    NUMPAD_DECIMAL = 110,
    NUMPAD_DIVIDE = 111,
    SCROLLLOCK = 145,
    SEMICOLON = 186,
    EQUAL = 187,
    COMMA = 188,
    MINUS = 189,
    PERIOD = 190,
    SLASH = 191,
    BACKQUOTE = 192,
    BRACKET_LEFT = 219,
    BACKSLASH = 220,
    BRACKET_RIGHT = 221,
    QUOTE = 222,
    NUMPAD_0 = 10048,
    NUMPAD_1 = 10049,
    NUMPAD_2 = 10050,
    NUMPAD_3 = 10051,
    NUMPAD_4 = 10052,
    NUMPAD_5 = 10053,
    NUMPAD_6 = 10054,
    NUMPAD_7 = 10055,
    NUMPAD_8 = 10056,
    NUMPAD_9 = 10057,
    DPAD_UP = 1003,
    DPAD_LEFT = 1000,
    DPAD_DOWN = 1004,
    DPAD_RIGHT = 1001,
    DPAD_CENTER = 1005
};

struct KeyboardEvent
{
    enum class Action : uint8_t {
        PRESS,
        RELEASE,
        REPEAT,
        UNKNOWN
    };

    int key = -1;
    Action action = Action::UNKNOWN;
    bool altKeyActive = false;
    bool ctrlKeyActive = false;
    bool metaKeyActive = false;
    bool shiftKeyActive = false;
};

class CustomEvent
{
public:
    std::string name;
    union {
        void* ptrVal;
        long longVal;
        int intVal;
        short shortVal;
        char charVal;
        bool boolVal;
    } args[10];

    CustomEvent(){};
    virtual ~CustomEvent(){};
};

class EventDispatcher
{
public:
    static void init();
    static void destroy();

    static void dispatchTouchEvent(const struct TouchEvent& touchEvent);
    static void dispatchMouseEvent(const struct MouseEvent& mouseEvent);
    static void dispatchKeyboardEvent(const struct KeyboardEvent& keyboardEvent);
    static void dispatchTickEvent(float dt);
    static void dispatchResizeEvent(int width, int height);
    static void dispatchOrientationChangeEvent(int rotation);
    static void dispatchOnPauseEvent();
    static void dispatchOnResumeEvent();

    using CustomEventListener = std::function<void(const CustomEvent&)>;
    static uint32_t addCustomEventListener(const std::string& eventName, const CustomEventListener& listener);
    static void removeCustomEventListener(const std::string& eventName, uint32_t listenerID);
    static void removeAllCustomEventListeners(const std::string& eventName);
    static void dispatchCustomEvent(const CustomEvent& event);

private:
    struct Node
    {
        CustomEventListener listener;
        uint32_t listenerID;
        struct Node* next;
    };
    static std::unordered_map<std::string, Node*> _listeners;
};
    
} // end of namespace cocos2d
