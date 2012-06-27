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

#include "IosInput.hpp"
#include <gdx-cpp/InputProcessor.hpp>
#include <cassert>

using namespace gdx_cpp::backends::ios;

gdx_cpp::backends::ios::IosInput::IosInput()
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

void gdx_cpp::backends::ios::IosInput::cancelVibrate()
{
}

float gdx_cpp::backends::ios::IosInput::getAccelerometerX()
{
    return 0;
}

float gdx_cpp::backends::ios::IosInput::getAccelerometerY()
{
    return 0;
}

float gdx_cpp::backends::ios::IosInput::getAccelerometerZ()
{
    return 0;
}

float gdx_cpp::backends::ios::IosInput::getAzimuth()
{
    return 0;
}

long int gdx_cpp::backends::ios::IosInput::getCurrentEventTime()
{
    return 0;
}

int gdx_cpp::backends::ios::IosInput::getDeltaX()
{
    return deltaX;
}

int gdx_cpp::backends::ios::IosInput::getDeltaX(int pointer)
{       
    if (pointer == 0) {
        return deltaX;
    }
    return 0;
}

int gdx_cpp::backends::ios::IosInput::getDeltaY()
{
    return deltaY;
}

int gdx_cpp::backends::ios::IosInput::getDeltaY(int pointer)
{
    if (pointer == 0) {
        return deltaY;
    }
    return 0;
}

gdx_cpp::Input::Orientation gdx_cpp::backends::ios::IosInput::getNativeOrientation()
{
    return gdx_cpp::Input::Landscape;
}

float gdx_cpp::backends::ios::IosInput::getPitch()
{
    return 0;
}

float gdx_cpp::backends::ios::IosInput::getRoll()
{
    return 0;
}

int gdx_cpp::backends::ios::IosInput::getRotation()
{
    return 0;
}

void gdx_cpp::backends::ios::IosInput::getTextInput(const gdx_cpp::Input::TextInputListener& listener,
                                                      const std::string& title, const std::string& text)
{
}

int gdx_cpp::backends::ios::IosInput::getX()
{
    return touchX;
}

int gdx_cpp::backends::ios::IosInput::getX(int pointer)
{
    return 0;
}

int gdx_cpp::backends::ios::IosInput::getY()
{
    return touchY;
}

int gdx_cpp::backends::ios::IosInput::getY(int pointer)
{
    return 0;
}

bool gdx_cpp::backends::ios::IosInput::isButtonPressed(int button)
{
    return false;
}

bool gdx_cpp::backends::ios::IosInput::isCursorCatched()
{
    return false;
}

bool gdx_cpp::backends::ios::IosInput::isKeyPressed(int key)
{
    return false;
}

bool gdx_cpp::backends::ios::IosInput::isPeripheralAvailable(int peripheral)
{
    return peripheral == Peripheral::HardwareKeyboard;
}

bool gdx_cpp::backends::ios::IosInput::isTouched()
{
    return touching;
}

bool gdx_cpp::backends::ios::IosInput::isTouched(int pointer)
{
    return pointer == 0 && touching;
}

bool gdx_cpp::backends::ios::IosInput::justTouched()
{
    return _justTouched;
}

void gdx_cpp::backends::ios::IosInput::setCatchBackKey(bool catchBack)
{
}

void gdx_cpp::backends::ios::IosInput::setCatchMenuKey(bool catchMenu)
{
}

void gdx_cpp::backends::ios::IosInput::setCursorCatched(bool catched)
{
}

void gdx_cpp::backends::ios::IosInput::setCursorPosition(int x, int y)
{
}

void gdx_cpp::backends::ios::IosInput::setInputProcessor(gdx_cpp::InputProcessor* processor)
{
    this->processor = processor;
}

void gdx_cpp::backends::ios::IosInput::setOnscreenKeyboardVisible(bool visible)
{
}

void gdx_cpp::backends::ios::IosInput::vibrate(int milliseconds)
{
}

void gdx_cpp::backends::ios::IosInput::vibrate(long int* pattern, int repeat)
{
}

void gdx_cpp::backends::ios::IosInput::reset()
{
    this->_justTouched = false;
}

void gdx_cpp::backends::ios::IosInput::handleTouchDrag(float x, float y, int button)
{
    if (this->processor) {
        this->processor->touchDragged(x, y, button);
    }
}

void gdx_cpp::backends::ios::IosInput::handleTouchDown(float x, float y, int button)
{
    touchX = x;
    touchY = y;
    touching = true;
    
    if (this->processor) {
        this->processor->touchDown(x, y, button, 0);
    }
}

void gdx_cpp::backends::ios::IosInput::handleTouchUp(float x, float y, int button)
{
    touching = false;
    if (this->processor) {
        this->processor->touchUp(x, y, button, 0);
    }
}


void IosInput::setKeyboardRepeat(int delay, int repeatInterval) {
    
}