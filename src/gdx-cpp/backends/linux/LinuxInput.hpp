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

#ifndef GDX_CPP_BACKENDS_LINUX_LINUXINPUT_HPP
#define GDX_CPP_BACKENDS_LINUX_LINUXINPUT_HPP

#include <SDL/SDL_events.h>
#include <gdx-cpp/Input.hpp>
#include <string>

namespace gdx {
class InputProcessor;
}  // namespace gdx

namespace gdx {

namespace nix {

class LinuxInput : public gdx::Input
{
public:
    LinuxInput();
    float getAccelerometerX () override;
    float getAccelerometerY () override;
    float getAccelerometerZ () override;
    int getX () override;
    int getX (int pointer) override;

    int getDeltaX () override ;

    int getDeltaX (int pointer) override ;

    int getY () override ;

    int getY (int pointer) override ;

    int getDeltaY () override ;

    int getDeltaY (int pointer) override ;

    bool isTouched () override ;

    bool justTouched () override ;

    bool isTouched (int pointer) override ;

    bool isButtonPressed (int button) override ;

    bool isKeyPressed (int key) override ;

    void getTextInput (const TextInputListener& listener, const std::string& title, const std::string& text) override ;

    void setOnscreenKeyboardVisible (bool visible) override ;

    void vibrate (int milliseconds) override ;

    void vibrate (long* pattern, int repeat) override ;

    void cancelVibrate () override ;

    float getAzimuth () override ;

    float getPitch () override ;

    float getRoll () override ;

    long getCurrentEventTime() override ;

    void setCatchBackKey (bool catchBack) override ;

    void setCatchMenuKey (bool catchMenu) override ;

    void setInputProcessor (gdx::InputProcessor* processor) override ;

    bool isPeripheralAvailable (int peripheral) override ;

    int getRotation () override ;

    Orientation getNativeOrientation () override ;


    void setCursorCatched (bool catched) override ;

    bool isCursorCatched () override ;

    void setCursorPosition (int x, int y) override ;

    void processEvents(SDL_Event& evt);
    void reset();

    int getGdxEventKey(SDL_Event& eventkey);

    void setKeyboardRepeat(int delay, int repeatInterval) override;
    
protected:
    gdx::InputProcessor* processor;

    bool _justTouched;
    bool touching;
    int touchX, deltaX;
    int touchY, deltaY;
    
};

}

}

#endif // GDX_CPP_BACKENDS_LINUX_LINUXINPUT_HPP
