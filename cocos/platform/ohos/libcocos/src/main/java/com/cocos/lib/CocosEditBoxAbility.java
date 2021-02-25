/****************************************************************************
 Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.

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
package com.cocos.lib;


import ohos.aafwk.ability.AbilitySlice;
import ohos.aafwk.content.Intent;
import ohos.accessibility.ability.AccessibleAbility;
import ohos.accessibility.ability.SoftKeyBoardController;
import ohos.agp.components.*;
import ohos.agp.render.Paint;
import ohos.agp.utils.Color;
import ohos.agp.window.service.DisplayAttributes;
import ohos.agp.window.service.DisplayManager;
import ohos.agp.window.service.WindowManager;
import ohos.hiviewdfx.HiLog;
import ohos.hiviewdfx.HiLogLabel;
import ohos.multimodalinput.event.TouchEvent;


public class CocosEditBoxAbility extends AbilitySlice {

    // a color of dark green, was used for confirm button background
    private static final Color DARK_GREEN = new Color(Color.getIntColor("#1fa014"));
    private static final Color DARK_GREEN_PRESS = new Color(Color.getIntColor("#008e26"));

    private static CocosEditBoxAbility sThis = null;
    private Cocos2dxEditText mEditText = null;
    private Button mButton = null;
    private String mButtonTitle = null;
    private boolean mConfirmHold = true;

    /***************************************************************************************
     Inner class.
     **************************************************************************************/
    class Cocos2dxEditText extends TextField {
        private final HiLogLabel TAG = new HiLogLabel(HiLog.LOG_APP, 0, "Cocos2dxEditBox");
        private boolean mIsMultiLine = false;
        private Text.TextObserver mTextWatcher = null;
        private Paint mPaint;
        private Color mLineColor = DARK_GREEN;
        private float mLineWidth = 2f;
        private boolean keyboardVisible = false;
        private int mScreenHeight;

        public Cocos2dxEditText(AbilitySlice context) {
            super(context);
            //remove focus border
//            this.setBackground(null);
            this.setTextColor(Color.BLACK);

            DisplayAttributes displayAttrib = DisplayManager.getInstance().getDefaultDisplay(context).get().getRealAttributes();

            mScreenHeight = displayAttrib.width;
            mPaint = new Paint();
            mPaint.setStrokeWidth(mLineWidth);
            mPaint.setStyle(Paint.Style.FILL_STYLE);
            mPaint.setColor(mLineColor);

            mTextWatcher = new Text.TextObserver() {
                @Override
                public void onTextUpdated(String s, int i, int i1, int i2) {
                    CocosEditBoxAbility.this.onKeyboardInput(s.toString());
                }
            };
            registKeyboardVisible();
        }

        /***************************************************************************************
         Override functions.
         **************************************************************************************/

//        @Override
//        protected void onDraw(Canvas canvas) {
//            // draw the underline
//            int padB = this.getPaddingBottom();
//            canvas.drawLine(getScrollX(), this.getHeight() - padB / 2 - mLineWidth,
//                    getScrollX() + this.getWidth(),
//                    this.getHeight() - padB / 2 - mLineWidth, mPaint);
//            super.onDraw(canvas);
//        }

        /***************************************************************************************
         Public functions.
         **************************************************************************************/

        public void show(String defaultValue, int maxLength, boolean isMultiline, boolean confirmHold, String confirmType, String inputType) {
            mIsMultiLine = isMultiline;
            // TODO: max text
//            this.setFilters(new InputFilter[]{new InputFilter.LengthFilter(maxLength)});

            this.setText(defaultValue);
            setSelected(true);
            this.setConfirmType(confirmType);
            this.setInputType(inputType, mIsMultiLine);
            this.setVisibility(Component.VISIBLE);

            // Open soft keyboard manually. Should request focus to open soft keyboard.
            this.requestFocus();

            this.addListeners();
        }

        public void hide() {
            mEditText.setVisibility(Component.INVISIBLE);
            this.removeListeners();
        }

        /***************************************************************************************
         Private functions.
         **************************************************************************************/

        private void setConfirmType(final String confirmType) {
            if (confirmType.contentEquals("done")) {
                setInputMethodOption(InputAttribute.ENTER_KEY_TYPE_UNSPECIFIED);
                mButtonTitle = "Done"; //TODO: read from ResourceTable
            } else if (confirmType.contentEquals("next")) {
                setInputMethodOption(InputAttribute.ENTER_KEY_TYPE_UNSPECIFIED);
                mButtonTitle = "Done"; //TODO: read from ResourceTable
            } else if (confirmType.contentEquals("search")) {
                setInputMethodOption(InputAttribute.ENTER_KEY_TYPE_SEARCH);
                mButtonTitle = "Search"; //TODO: read from ResourceTable
            } else if (confirmType.contentEquals("go")) {
                setInputMethodOption(InputAttribute.ENTER_KEY_TYPE_GO);
                mButtonTitle = "Go"; //TODO: read from ResourceTable
            } else if (confirmType.contentEquals("send")) {
                setInputMethodOption(InputAttribute.ENTER_KEY_TYPE_SEND);
                mButtonTitle = "Send"; //TODO: read from ResourceTable
            } else {
                mButtonTitle = null;
                HiLog.error(TAG, "unknown confirm type " + confirmType);
            }
        }

        private void setInputType(final String inputType, boolean isMultiLine) {
            if (inputType.contentEquals("text")) {
                if (isMultiLine) {
//                    this.setInputType(InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_FLAG_MULTI_LINE);
                    setTextInputType(InputAttribute.PATTERN_TEXT);
                    setMultipleLine(true);
                } else {
                    setTextInputType(InputAttribute.PATTERN_TEXT);
                    setMultipleLine(false);
                }
            } else if (inputType.contentEquals("email")) {
//                this.setInputType(InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS);
                this.setTextInputType(InputAttribute.PATTERN_TEXT);
            } else if (inputType.contentEquals("number")) {
//                this.setInputType(InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_DECIMAL | InputType.TYPE_NUMBER_FLAG_SIGNED);
                this.setTextInputType(InputAttribute.PATTERN_NUMBER);
            } else if (inputType.contentEquals("phone")) {
//                this.setInputType(InputType.TYPE_CLASS_PHONE);
                this.setTextInputType(InputAttribute.PATTERN_TEXT);
            } else if (inputType.contentEquals("password")) {
//                this.setInputType(InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_PASSWORD);
                this.setTextInputType(InputAttribute.PATTERN_PASSWORD);
            } else {
                HiLog.error(TAG, "unknown input type " + inputType);
            }
        }

        private void addListeners() {
// TODO: ??
//            this.setOnEditorActionListener(new TextView.OnEditorActionListener() {
//                @Override
//                public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
//                    if (!mIsMultiLine) {
//                        CocosEditBoxActivity.this.hide();
//                    }
//
//                    return false; // pass on to other listeners.
//                }
//            });

            this.addTextObserver(mTextWatcher);
        }

        private void removeListeners() {
//            this.setOnEditorActionListener(null);
            this.removeTextObserver(mTextWatcher);
        }

        private void registKeyboardVisible() {
//            getViewTreeObserver().addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener() {
//                @Override
//                public void onGlobalLayout() {
//                    Rect r = new Rect();
//                    getWindowVisibleDisplayFrame(r);
//                    int heightDiff = getRootView().getHeight() - (r.bottom - r.top);
//                    // if more than a quarter of the screen, its probably a keyboard
//                    if (heightDiff > mScreenHeight / 4) {
//                        if (!keyboardVisible) {
//                            keyboardVisible = true;
//                        }
//                    } else {
//                        if (keyboardVisible) {
//                            keyboardVisible = false;
//                            CocosEditBoxActivity.this.hide();
//                        }
//                    }
//                }
//            });
        }
    }

    @Override
    protected void onStart(Intent intent) {
        super.onStart(intent);

        getAbility().setAbilitySliceAnimator(null); // remove animation

        //FIXME: todo
//        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_ADJUST_RESIZE); // android
//        getWindow().setInputPanelDisplayType(Dis); // ohos
        sThis = this;
        getWindow().setInputPanelDisplayType(WindowManager.LayoutConfig.INPUT_ADJUST_PAN);

        setUIContent(ResourceTable.Layout_editbox_layout);

        this.addItems();

        show(intent.getStringParam("defaultValue"),
                intent.getIntParam("maxLength", 60),
                intent.getBooleanParam("isMultiline", false),
                intent.getBooleanParam("confirmHold", true),
                intent.getStringParam("confirmType"),
                intent.getStringParam("inputType"));

    }

    /***************************************************************************************
     Public functions.
     **************************************************************************************/

    /***************************************************************************************
     Private functions.
     **************************************************************************************/
    private void addItems() {
        this.addEditText();
        this.addButton();
        //FXI ME: Is it needed?
        // When touch area outside EditText and soft keyboard, then hide.
//        layout.setOnTouchListener(new View.OnTouchListener() {
//            @Override
//            public boolean onTouch(View v, MotionEvent event) {
//                Cocos2dxEditBox.this.hide();
//                return true;
//            }
//
//        });
    }

    private void addEditText() {
        mEditText = (Cocos2dxEditText)findComponentById(ResourceTable.Id_textField);
        mEditText.setVisibility(Component.INVISIBLE);
    }

    private void addButton() {
        mButton = (Button) findComponentById(ResourceTable.Id_enterBtn);

        mButton.setTouchEventListener(new Component.TouchEventListener() {
            @Override
            public boolean onTouchEvent(Component component, TouchEvent touchEvent) {
                CocosEditBoxAbility.this.onKeyboardConfirm(mEditText.getText().toString());

                if (!CocosEditBoxAbility.this.mConfirmHold)
                    CocosEditBoxAbility.this.hide();
                return true;
            }
        });
    }

    private void hide() {
//        Utils.hideVirtualButton(); // TODO: hide virtual button
        this.closeKeyboard();
        this.terminate();
    }

    public void show(String defaultValue, int maxLength, boolean isMultiline, boolean confirmHold, String confirmType, String inputType) {
        mConfirmHold = confirmHold;
        mEditText.show(defaultValue, maxLength, isMultiline, confirmHold, confirmType, inputType);
        int editPaddingBottom = mEditText.getPaddingBottom();
        int editPadding = mEditText.getPaddingTop();
        mEditText.setPadding(editPadding, editPadding, editPadding, editPaddingBottom);

        mEditText.setTextColor(Color.WHITE);

        mButton.setText(mButtonTitle);
//        if (mButtonTitle == null || mButton.length() == 0) {
//            mButton.setPadding(0, 0, 0, 0);
//            mButtonParams.setMargins(0, 0, 0, 0);
//            mButtonLayout.setVisibility(Component.INVISIBLE);
//        } else {
//            int buttonTextPadding = mEditText.getPaddingBottom() / 2;
//            mButton.setPadding(editPadding, buttonTextPadding, editPadding, buttonTextPadding);
//            mButtonParams.setMargins(0, buttonTextPadding, 2, 0);
//            mButtonLayout.setVisibility(Component.VISIBLE);
//        }

        this.openKeyboard();
    }

    private void closeKeyboard() {
        getKeyBoard().setShowMode(AccessibleAbility.SHOW_MODE_HIDE);
        CocosHelper.runOnUIThread(new Runnable() {
            @Override
            public void run() {
                mEditText.clearFocus();
            }
        });
        this.onKeyboardComplete(mEditText.getText().toString());

    }

    private void openKeyboard() {
        getKeyBoard().setShowMode(AccessibleAbility.SHOW_MODE_AUTO);
        CocosHelper.runOnUIThread(new Runnable() {
            @Override
            public void run() {
                mEditText.requestFocus();
                mEditText.simulateClick();
            }
        });
    }

    private SoftKeyBoardController getKeyBoard() {
        return ((AccessibleAbility)getAbility()).getSoftKeyBoardController();
    }

    /***************************************************************************************
     Functions invoked by CPP.
     **************************************************************************************/

    private static void showNative(String defaultValue, int maxLength, boolean isMultiline, boolean confirmHold, String confirmType, String inputType) {

        CocosHelper.runOnUIThread(new Runnable() {
            @Override
            public void run() {
                Intent i = new Intent();
                i.setParam("defaultValue", defaultValue);
                i.setParam("maxLength", maxLength);
                i.setParam("isMultiline", isMultiline);
                i.setParam("confirmHold", confirmHold);
                i.setParam("confirmType", confirmType);
                i.setParam("inputType", inputType);
                CocosEditBoxAbility ability = new CocosEditBoxAbility();
                GlobalObject.getAbilitySlice().present(ability, i);
            }
        });
    }

    private static void hideNative() {
        if (null != CocosEditBoxAbility.sThis) {
            CocosHelper.runOnUIThread(new Runnable() {
                @Override
                public void run() {
                    CocosEditBoxAbility.sThis.hide();
                }
            });
        }
    }

    /***************************************************************************************
     Native functions invoked by UI.
     **************************************************************************************/
    private void onKeyboardInput(String text) {
        CocosHelper.runOnGameThread(new Runnable() {
            @Override
            public void run() {
                CocosEditBoxAbility.onKeyboardInputNative(text);
            }
        });
    }

    private void onKeyboardComplete(String text) {
        CocosHelper.runOnGameThread(new Runnable() {
            @Override
            public void run() {
                CocosEditBoxAbility.onKeyboardCompleteNative(text);
            }
        });
    }

    private void onKeyboardConfirm(String text) {
        CocosHelper.runOnGameThread(new Runnable() {
            @Override
            public void run() {
                CocosEditBoxAbility.onKeyboardConfirmNative(text);
            }
        });
    }

    private static native void onKeyboardInputNative(String text);

    private static native void onKeyboardCompleteNative(String text);

    private static native void onKeyboardConfirmNative(String text);
}
