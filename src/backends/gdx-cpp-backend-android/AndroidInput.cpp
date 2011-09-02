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

#include "AndroidInput.hpp"
#include <gdx-cpp/InputProcessor.hpp>

using namespace gdx_cpp::backends::nix;


gdx_cpp::backends::nix::AndroidInput::AndroidInput()
 :
 touching(false)
 ,touchX(0)
 ,touchY(0)
 ,_justTouched(false)
 ,processor(0)
 ,deltaX(0)
 ,deltaY(0)
{
}

void gdx_cpp::backends::nix::AndroidInput::cancelVibrate()
{
}

float gdx_cpp::backends::nix::AndroidInput::getAccelerometerX()
{
    return 0;
}

float gdx_cpp::backends::nix::AndroidInput::getAccelerometerY()
{
    return 0;
}

float gdx_cpp::backends::nix::AndroidInput::getAccelerometerZ()
{
    return 0;
}

float gdx_cpp::backends::nix::AndroidInput::getAzimuth()
{
    return 0;
}

long int gdx_cpp::backends::nix::AndroidInput::getCurrentEventTime()
{
    return 0;
}

int gdx_cpp::backends::nix::AndroidInput::getDeltaX()
{
    return deltaX;
}

int gdx_cpp::backends::nix::AndroidInput::getDeltaX(int pointer)
{       
    if (pointer == 0) {
        return deltaX;
    }
    return 0;
}

int gdx_cpp::backends::nix::AndroidInput::getDeltaY()
{
    return deltaY;
}

int gdx_cpp::backends::nix::AndroidInput::getDeltaY(int pointer)
{
    if (pointer == 0) {
        return deltaY;
    }
    return 0;
}

gdx_cpp::Input::Orientation gdx_cpp::backends::nix::AndroidInput::getNativeOrientation()
{
    return gdx_cpp::Input::Landscape;
}

float gdx_cpp::backends::nix::AndroidInput::getPitch()
{
    0;
}

float gdx_cpp::backends::nix::AndroidInput::getRoll()
{
    0;
}

int gdx_cpp::backends::nix::AndroidInput::getRotation()
{
    0;
}

void gdx_cpp::backends::nix::AndroidInput::getTextInput(const gdx_cpp::Input::TextInputListener& listener,
                                                      const std::string& title, const std::string& text)
{

}

int gdx_cpp::backends::nix::AndroidInput::getX()
{
    return touchX;
}

int gdx_cpp::backends::nix::AndroidInput::getX(int pointer)
{

}

int gdx_cpp::backends::nix::AndroidInput::getY()
{
    return touchY;
}

int gdx_cpp::backends::nix::AndroidInput::getY(int pointer)
{

}

bool gdx_cpp::backends::nix::AndroidInput::isButtonPressed(int button)
{

}

bool gdx_cpp::backends::nix::AndroidInput::isCursorCatched()
{

}

bool gdx_cpp::backends::nix::AndroidInput::isKeyPressed(int key)
{

}

bool gdx_cpp::backends::nix::AndroidInput::isPeripheralAvailable(int peripheral)
{
    return peripheral == Peripheral::HardwareKeyboard;
}

bool gdx_cpp::backends::nix::AndroidInput::isTouched()
{
    return touching;
}

bool gdx_cpp::backends::nix::AndroidInput::isTouched(int pointer)
{
    return pointer == 0 && touching;
}

bool gdx_cpp::backends::nix::AndroidInput::justTouched()
{
    return _justTouched;
}

void gdx_cpp::backends::nix::AndroidInput::setCatchBackKey(bool catchBack)
{

}

void gdx_cpp::backends::nix::AndroidInput::setCatchMenuKey(bool catchMenu)
{

}

void gdx_cpp::backends::nix::AndroidInput::setCursorCatched(bool catched)
{

}

void gdx_cpp::backends::nix::AndroidInput::setCursorPosition(int x, int y)
{

}

void gdx_cpp::backends::nix::AndroidInput::setInputProcessor(gdx_cpp::InputProcessor* processor)
{
    this->processor = processor;
}

void gdx_cpp::backends::nix::AndroidInput::setOnscreenKeyboardVisible(bool visible)
{
}

void gdx_cpp::backends::nix::AndroidInput::vibrate(int milliseconds)
{
}

void gdx_cpp::backends::nix::AndroidInput::vibrate(long int* pattern, int repeat)
{
}

// void gdx_cpp::backends::nix::AndroidInput::processEvents(SDL_Event& evt)
// {
//     if (evt.type == SDL_MOUSEMOTION) {
//         if (processor) {
//             deltaX = evt.motion.xrel;
//             deltaY = evt.motion.yrel;
//             
//             if (this->touching) {
//                 this->processor->touchDragged(evt.motion.x, evt.motion.y, evt.button.button);
//             } else {
//                 this->processor->touchMoved(evt.motion.x, evt.motion.y);
//             }
//         }
//     } else if (evt.type == SDL_MOUSEBUTTONDOWN) {
//         this->touching = true;
//         touchX = evt.motion.x;
//         touchY = evt.motion.y;
//         deltaX = evt.motion.xrel;
//         deltaY = evt.motion.yrel;
//         this->_justTouched = true;
//         
//         if (this->processor) {
//             this->processor->touchDown(evt.motion.x, evt.motion.y, 0, evt.button.button);
//         }
//         
//     } else if (evt.type == SDL_MOUSEBUTTONUP) {
//         this->touching = false;
//         touchY =touchX = 0;
//         
//         if (this->processor) {
//             this->processor->touchUp(evt.motion.x, evt.motion.y, 0, evt.button.button);
//         }
//     }   
// 
// }

void gdx_cpp::backends::nix::AndroidInput::reset()
{
    this->_justTouched = false;
}


