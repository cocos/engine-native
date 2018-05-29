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
#include "EditBox.h"
#import <UIKit/UITextField.h>
#import <UIKit/UITextView.h>
#include "platform/CCApplication.h"

#define TEXT_LINE_HEIGHT  30

#define TO_TEXT_VIEW(textinput)   ((UITextView*)textinput)
#define TO_TEXT_FIELD(textinput)  ((UITextField*)textinput)

@class KeyboardEventHandler;

static UIView* textInput = nil; // used for multiline
static KeyboardEventHandler* keyboardHandler = nil;

/*************************************************************************
 Keyboard event handler.
 ************************************************************************/

// MARK: KeyboardEventHandler

@interface KeyboardEventHandler : NSObject
-(void)keyboardWillShow: (NSNotification*) notification;
-(void)keyboardDidHide: (NSNotification*) notification;
@end

@implementation KeyboardEventHandler
-(void)keyboardWillShow: (NSNotification*) notification
{
    if (!textInput)
        return;
    
    NSDictionary* keyboardInfo = [notification userInfo];
    NSValue* keyboardFrameBegin = [keyboardInfo valueForKey:UIKeyboardFrameBeginUserInfoKey];
    CGRect keyboardFrameBeginRect = [keyboardFrameBegin CGRectValue];
    CGRect oldFrame = textInput.frame;
    textInput.frame = CGRectMake(oldFrame.origin.x,
                                oldFrame.origin.y - keyboardFrameBeginRect.size.height,
                                oldFrame.size.width,
                                oldFrame.size.height - keyboardFrameBeginRect.size.height);
}

-(void)keyboardDidHide: (NSNotification*) notification
{
    
}
@end

/*************************************************************************
 TextView delegator.
 ************************************************************************/

@interface TextViewDelegator : NSObject<UITextViewDelegate>
@end

@implementation TextViewDelegator
- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    return TRUE;
}
@end

/*************************************************************************
 Helper functions.
 ************************************************************************/

// MARK: Helper functions

namespace
{
    void addText(const std::string& defaultValue,
                     int maxLength,
                     bool isMultiLine,
                     bool confirmHold,
                     const std::string& confirmType,
                     const std::string& inputType)
    {
        UIView* view = (UIView*)cocos2d::Application::getInstance()->getView();
        CGRect viewRect = view.frame;
        CGRect rect = CGRectMake(viewRect.origin.x,
                                 viewRect.size.height - TEXT_LINE_HEIGHT,
                                 viewRect.size.width,
                                 viewRect.size.height);
        if (isMultiLine)
            textInput = [[UITextView alloc] initWithFrame:rect];
        else
            textInput = [[UITextField alloc] initWithFrame:rect];
            
        [view addSubview:textInput];
        
        [textInput becomeFirstResponder];
        if (isMultiLine)
            TO_TEXT_VIEW(textInput).text = [NSString stringWithUTF8String: defaultValue.c_str()];
        else
            TO_TEXT_FIELD(textInput).text = [NSString stringWithUTF8String: defaultValue.c_str()];
    }
    
    void listenKeyboradEvent()
    {
        if (!keyboardHandler)
            keyboardHandler = [[KeyboardEventHandler alloc] init];
        
        [[NSNotificationCenter defaultCenter] addObserver:keyboardHandler
                                              selector:@selector(keyboardWillShow:)
                                              name:UIKeyboardWillShowNotification
                                              object:nil];
    }
}

/*************************************************************************
 Implementation of EditBox.
 ************************************************************************/

// MARK: EditBox

NS_CC_BEGIN

void EditBox::show(const std::string& defaultValue,
                   int maxLength,
                   bool isMultiLine,
                   bool confirmHold,
                   const std::string& confirmType,
                   const std::string& inputType)
{
    listenKeyboradEvent();
    addText(defaultValue, maxLength, isMultiLine, confirmHold, confirmType, inputType);
}


void EditBox::hide()
{
    [textInput removeFromSuperview];
    [textInput release];
    textInput = nil;
}

NS_CC_END
