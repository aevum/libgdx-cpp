/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License") = 0;
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
#ifndef GDXCPP_INPUT_H_
#define GDXCPP_INPUT_H_

#include <string>

namespace gdx_ccp {
namespace input {

class Input {
public:

    class TextInputListener {
    public:
        virtual void input(const stlport::string& text) = 0;
    };

    enum Button {
        LEFT = 0,
        RIGHT = 1,
        MIDDLE = 2
    };

    enum Keys {
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
    
    /** Enumeration of potentially available peripherals. Use with {@link Input#isPeripheralAvailable(Peripheral)}.
     * @author mzechner */
    enum Peripheral {
      HardwareKeyboard, OnscreenKeyboard, MultitouchScreen, Accelerometer, Compass, Vibrator
    };
    
    /** @return The value of the accelerometer on its x-axis. ranges between [-10,10]. */
    virtual float getAccelerometerX () = 0;
    
    /** @return The value of the accelerometer on its y-axis. ranges between [-10,10]. */
    virtual getAccelerometerY () = 0;
    
    /** @return The value of the accelerometer on its y-axis. ranges between [-10,10]. */
    virtual float getAccelerometerZ () = 0;
    
    /** @return the last touch x coordinate in screen coordinates. The screen origin is the top left corner. */
    virtual int getX () = 0;
    
    /** Returns the x coordinate in screen coordinates of the given pointer. Pointers are indexed from 0 to n. The pointer id
     * identifies the order in which the fingers went down on the screen, e.g. 0 is the first finger, 1 is the second and so on.
     * When two fingers are touched down and the first one is lifted the second one keeps its index. If another finger is placed on
     * the touch screen the first free index will be used.
     *
     * @param pointer the pointer id.
     * @return the x coordinate */
    virtual int getX (int pointer) = 0;
    
    /** @return the different between the current pointer location and the last pointer location on the x-axis. */
    virtual int getDeltaX () = 0;
    
    /** @return the different between the current pointer location and the last pointer location on the x-axis. */
    virtual int getDeltaX (int pointer) = 0;
    
    /** @return the last touch y coordinate in screen coordinates. The screen origin is the top left corner. */
    virtual int getY () = 0;
    
    /** Returns the y coordinate in screen coordinates of the given pointer. Pointers are indexed from 0 to n. The pointer id
     * identifies the order in which the fingers went down on the screen, e.g. 0 is the first finger, 1 is the second and so on.
     * When two fingers are touched down and the first one is lifted the second one keeps its index. If another finger is placed on
     * the touch screen the first free index will be used.
     *
     * @param pointer the pointer id.
     * @return the y coordinate */
    virtual int getY (int pointer) = 0;
    
    /** @return the different between the current pointer location and the last pointer location on the y-axis. */
    virtual int getDeltaY () = 0;
    
    /** @return the different between the current pointer location and the last pointer location on the y-axis. */
    virtual int getDeltaY (int pointer) = 0;
    
    /** @return whether the screen is currently touched. */
    virtual bool isTouched () = 0;
    
    /** @return whether a new touch down event just occured. */
    virtual bool justTouched () = 0;
    
    /** Whether the screen is currently touched by the pointer with the given index. Pointers are indexed from 0 to n. The pointer
     * id identifies the order in which the fingers went down on the screen, e.g. 0 is the first finger, 1 is the second and so on.
     * When two fingers are touched down and the first one is lifted the second one keeps its index. If another finger is placed on
     * the touch screen the first free index will be used.
     *
     * @param pointer the pointer
     * @return whether the screen is touched by the pointer */
    virtual bool isTouched (int pointer) = 0;
    
    /** Whether a given button is pressed or not. Button constants can be found in {@link Buttons}. On Android only the Button#LEFT
     * constant is meaningful.
     * @param button the button to check.
     * @return whether the button is down or not. */
    virtual bool isButtonPressed (int button) = 0;
    
    /** Returns whether the key is pressed.
     * 
     * @param key The key code as found in {@link Input.Keys}.
     * @return true or false. */
    virtual bool isKeyPressed (int key) = 0;
    
    /** System dependent method to input a string of text. A dialog box will be created with the given title and the given text as a
     * message for the user. Once the dialog has been closed the provided {@link TextInputListener} will be called but not
     * necessarily in the rendering thread in which all the {@link ApplicationListener} methods are called. You have to synchronize
     * this yourself.
     *
     * @param listener The TextInputListener.
     * @param title The title of the text input dialog.
     * @param text The message presented to the user. */
    virtual void getTextInput (const TextInputListener& listener, String title, String text) = 0;
    
    /** Sets the on-screen keyboard visible if available.
     * 
     * @param visible visible or not */
    virtual void setOnscreenKeyboardVisible (bool visible) = 0;
    
    /** Vibrates for the given amount of time. Note that you'll need the permission
     * <code> <uses-permission android:name="android.permission.VIBRATE" /></code> in your manifest file in order for this to work.
     *
     * @param milliseconds the number of milliseconds to vibrate. */
    virtual void vibrate (int milliseconds) = 0;
    
    /** Vibrate with a given pattern. Pass in an array of ints that are the times at which to turn on or off the vibrator. The first
     * one is how long to wait before turning it on, and then after that it alternates. If you want to repeat, pass the index into
     * the pattern at which to start the repeat.
     * @param pattern an array of longs of times to turn the vibrator on or off.
     * @param repeat the index into pattern at which to repeat, or -1 if you don't want to repeat. */
    virtual void vibrate (long* pattern, int repeat) = 0;
    
    /** Stops the vibrator */
    virtual void cancelVibrate () = 0;
    
    /** The azimuth is the angle of the device's orientation around the z-axis. The positive z-axis points towards the earths
     * center.
     *
     * @see <a
     *      href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])</a>
     * @return the azimuth in degrees */
    virtual float getAzimuth () = 0;
    
    /** The pitch is the angle of the device's orientation around the x-axis. The positive x-axis roughly points to the west and is
     * orthogonal to the z- and y-axis.
     * @see <a
     *      href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])</a>
     * @return the pitch in degrees */
    virtual float getPitch () = 0;
    
    /** The roll is the angle of the device's orientation around the y-axis. The positive y-axis points to the magnetic north pole
     * of the earth.
     * @see <a
     *      href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])</a>
     * @return the roll in degrees */
    virtual float getRoll () = 0;
    
    /**
     * @return the time of the event currently reported to the {@link InputProcessor}.
     */
    virtual long getCurrentEventTime() = 0;
    
    /** Sets whether the BACK button on Android should be caught. This will prevent the app from being paused. Will have no effect
     * on the desktop.
     *
     * @param catchBack whether to catch the back button */
    virtual void setCatchBackKey (bool catchBack) = 0;
    
    /** Sets whether the MENU button on Android should be caught. This will prevent the onscreen keyboard to show up. Will have no
     * effect on the desktop.
     *
     * @param catchMenu whether to catch the back button */
    virtual void setCatchMenuKey (bool catchMenu) = 0;
    
    /** Sets the {@link InputProcessor} that will receive all touch and key input events. It will be called before the
     * {@link ApplicationListener#render()} method each frame.
     *
     * @param processor the InputProcessor */
    virtual void setInputProcessor (InputProcessor processor) = 0;
    
    /** @return the currently set {@link InputProcessor} or null. */
    virtual InputProcessor getInputProcessor () = 0;
    
    /** Queries whether a {@link Peripheral} is currently available. In case of Android and the {@link Peripheral#HardwareKeyboard}
     * this returns the whether the keyboard is currently slid out or not.
     *
     * @param peripheral the {@link Peripheral}
     * @return whether the peripheral is available or not. */
    virtual bool isPeripheralAvailable (Peripheral& peripheral) = 0;
    
    /** @return the rotation of the device with respect to its native orientation. */
    virtual int getRotation () = 0;
    
    /** @return the native orientation of the device. */
    virtual Orientation getNativeOrientation () = 0;
    
    enum Orientation {
      Landscape, Portrait
    };
    
    /** Only viable on the desktop. Will confine the mouse cursor location to the window and hide the mouse cursor.
     * @param catched whether to catch or not to catch the mouse cursor */
    virtual void setCursorCatched (bool catched) = 0;
    
    /** @return whether the mouse cursor is catched. */
    virtual bool isCursorCatched () = 0;
    
    /** Only viable on the desktop. Will set the mouse cursor location to the given window coordinates (origin top-left corner).
     * @param x the x-position
     * @param y the y-position */
    virtual void setCursorPosition (int x, int y) = 0;

};

}

#endif /* GDXCPP_INPUT_H_ */
