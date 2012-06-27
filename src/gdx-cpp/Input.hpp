/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 *  @author aevum team
 */
#ifndef GDXCPP_INPUT_H_
#define GDXCPP_INPUT_H_
#include <string>

namespace gdx {
    
class InputProcessor;

class Input {
public:

    class TextInputListener {
    public:
        virtual void input(const std::string& text) = 0;
    };

    struct Button {
        enum {
            LEFT = 0,
            RIGHT = 1,
            MIDDLE = 2
        };
    };

    struct Keys {
        enum  {
            ANY_KEY = -1,
            NUM_0 = 7,
            NUM_1 = 8,
            NUM_2 = 9,
            NUM_3 = 10,
            NUM_4 = 11,
            NUM_5 = 12,
            NUM_6 = 13,
            NUM_7 = 14,
            NUM_8 = 15,
            NUM_9 = 16,
            A = 29,
            ALT_LEFT = 57,
            ALT_RIGHT = 58,
            APOSTROPHE = 75,
            AT = 77,
            B = 30,
            BACK = 4,
            BACKSLASH = 73,
            C = 31,
            CALL = 5,
            CAMERA = 27,
            CLEAR = 28,
            COMMA = 55,
            D = 32,
            DEL = 67,
            BACKSPACE = 67,
            FORWARD_DEL = 112,
            DPAD_CENTER = 23,
            DPAD_DOWN = 20,
            DPAD_LEFT = 21,
            DPAD_RIGHT = 22,
            DPAD_UP = 19,
            CENTER = 23,
            DOWN = 20,
            LEFT = 21,
            RIGHT = 22,
            UP = 19,
            E = 33,
            ENDCALL = 6,
            ENTER = 66,
            ENVELOPE = 65,
            EQUALS = 70,
            EXPLORER = 64,
            F = 34,
            FOCUS = 80,
            G = 35,
            GRAVE = 68,
            H = 36,
            HEADSETHOOK = 79,
            HOME = 3,
            I = 37,
            J = 38,
            K = 39,
            L = 40,
            LEFT_BRACKET = 71,
            M = 41,
            MEDIA_FAST_FORWARD = 90,
            MEDIA_NEXT = 87,
            MEDIA_PLAY_PAUSE = 85,
            MEDIA_PREVIOUS = 88,
            MEDIA_REWIND = 89,
            MEDIA_STOP = 86,
            MENU = 82,
            MINUS = 69,
            MUTE = 91,
            N = 42,
            NOTIFICATION = 83,
            NUM = 78,
            O = 43,
            P = 44,
            PERIOD = 56,
            PLUS = 81,
            POUND = 18,
            POWER = 26,
            Q = 45,
            R = 46,
            RIGHT_BRACKET = 72,
            S = 47,
            SEARCH = 84,
            SEMICOLON = 74,
            SHIFT_LEFT = 59,
            SHIFT_RIGHT = 60,
            SLASH = 76,
            SOFT_LEFT = 1,
            SOFT_RIGHT = 2,
            SPACE = 62,
            STAR = 17,
            SYM = 63,
            T = 48,
            TAB = 61,
            U = 49,
            UNKNOWN = 0,
            V = 50,
            VOLUME_DOWN = 25,
            VOLUME_UP = 24,
            W = 51,
            X = 52,
            Y = 53,
            Z = 54,
            META_ALT_LEFT_ON = 16,
            META_ALT_ON = 2,
            META_ALT_RIGHT_ON = 32,
            META_SHIFT_LEFT_ON = 64,
            META_SHIFT_ON = 1,
            META_SHIFT_RIGHT_ON = 128,
            META_SYM_ON = 4,
            CONTROL_LEFT = 129,
            CONTROL_RIGHT = 130,
            ESCAPE = 131,
            END = 132,
            INSERT = 133,
            PAGE_UP = 92,
            PAGE_DOWN = 93,
            PICTSYMBOLS = 94,
            SWITCH_CHARSET = 95,
            BUTTON_CIRCLE = 255,
            BUTTON_A = 96,
            BUTTON_B = 97,
            BUTTON_C = 98,
            BUTTON_X = 99,
            BUTTON_Y = 100,
            BUTTON_Z = 101,
            BUTTON_L1 = 102,
            BUTTON_R1 = 103,
            BUTTON_L2 = 104,
            BUTTON_R2 = 105,
            BUTTON_THUMBL = 106,
            BUTTON_THUMBR = 107,
            BUTTON_START = 108,
            BUTTON_SELECT = 109,
            BUTTON_MODE = 110,
            COLON = 243,
            F1 = 244,
            F2 = 245,
            F3 = 246,
            F4 = 247,
            F5 = 248,
            F6 = 249,
            F7 = 250,
            F8 = 251,
            F9 = 252,
            F10 = 253,
            F11 = 254,
            F12 = 255,
        };
    };

    struct Peripheral {
        enum {
            HardwareKeyboard, OnscreenKeyboard, MultitouchScreen, Accelerometer, Compass, Vibrator
        };
    };

    virtual float getAccelerometerX () = 0;

    virtual float getAccelerometerY () = 0;

    virtual float getAccelerometerZ () = 0;

    virtual int getX () = 0;

    virtual int getX (int pointer) = 0;

    virtual int getDeltaX () = 0;

    virtual int getDeltaX (int pointer) = 0;

    virtual int getY () = 0;

    virtual int getY (int pointer) = 0;

    virtual int getDeltaY () = 0;

    virtual int getDeltaY (int pointer) = 0;

    virtual bool isTouched () = 0;

    virtual bool justTouched () = 0;

    virtual bool isTouched (int pointer) = 0;

    virtual bool isButtonPressed (int button) = 0;

    virtual bool isKeyPressed (int key) = 0;

    virtual void getTextInput (const TextInputListener& listener, const std::string& title, const std::string& text) = 0;

    virtual void setOnscreenKeyboardVisible (bool visible) = 0;

    virtual void vibrate (int milliseconds) = 0;

    virtual void vibrate (long* pattern, int repeat) = 0;

    virtual void cancelVibrate () = 0;

    virtual float getAzimuth () = 0;

    virtual float getPitch () = 0;

    virtual float getRoll () = 0;

    virtual long getCurrentEventTime() = 0;

    virtual void setCatchBackKey (bool catchBack) = 0;

    virtual void setCatchMenuKey (bool catchMenu) = 0;

    virtual void setInputProcessor (InputProcessor* processor) = 0;

    virtual bool isPeripheralAvailable (int peripheral) = 0;

    virtual int getRotation () = 0;

    enum Orientation {
      Landscape, Portrait
    };

    virtual Orientation getNativeOrientation () = 0;

    /**Sets up the keyboard repeat interval
      * @param delay: the delay, in msecs, before the repeat triggers
      * @param repeatInterval: after the repeat triggers, the interval in wich it will happen
      */
    virtual void setKeyboardRepeat(int delay, int repeatInterval) = 0;

    virtual void setCursorCatched (bool catched) = 0;

    virtual bool isCursorCatched () = 0;

    virtual void setCursorPosition (int x, int y) = 0;
};

}

#endif /* GDXCPP_INPUT_H_ */
