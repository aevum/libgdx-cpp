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
 */

#ifndef GDX_CPP_BACKENDS_IOS_IOSINPUT_HPP
#define GDX_CPP_BACKENDS_IOS_IOSINPUT_HPP

#include <gdx-cpp/Input.hpp>

namespace gdx {

namespace ios {

class IosInput : public gdx::Input
{
public:
    IosInput();
    float getAccelerometerX ();
    float getAccelerometerY ();
    float getAccelerometerZ ();
    int getX ();
    int getX (int pointer);

    int getDeltaX () ;

    int getDeltaX (int pointer) ;

    int getY () ;

    int getY (int pointer) ;

    int getDeltaY () ;

    int getDeltaY (int pointer) ;

    bool isTouched () ;

    bool justTouched () ;

    bool isTouched (int pointer) ;

    bool isButtonPressed (int button) ;

    bool isKeyPressed (int key) ;

    void getTextInput (const TextInputListener& listener, const std::string& title, const std::string& text) ;

    void setOnscreenKeyboardVisible (bool visible) ;

    void vibrate (int milliseconds) ;

    void vibrate (long* pattern, int repeat) ;

    void cancelVibrate () ;

    float getAzimuth () ;

    float getPitch () ;

    float getRoll () ;

    long getCurrentEventTime() ;

    void setCatchBackKey (bool catchBack) ;

    void setCatchMenuKey (bool catchMenu) ;

    void setInputProcessor (gdx::InputProcessor* processor) ;

    bool isPeripheralAvailable (int peripheral) ;

    int getRotation () ;

    Orientation getNativeOrientation () ;


    void setCursorCatched (bool catched) ;

    bool isCursorCatched () ;

    void setCursorPosition (int x, int y) ;
    
   virtual void setKeyboardRepeat(int delay, int repeatInterval);

//     void processEvents(SDL_Event& evt);
    void reset();
    void handleTouchDrag(float x, float y, int button);
    void handleTouchDown(float arg1, float arg2, int button);
    void handleTouchUp(float arg1, float arg2, int button);
    
protected:
    gdx::InputProcessor* processor;

    bool _justTouched;
    bool touching;
    int touchX, deltaX;
    int touchY, deltaY;
    
};

}

}

#endif // GDX_CPP_BACKENDS_IOS_IOSINPUT_HPP
