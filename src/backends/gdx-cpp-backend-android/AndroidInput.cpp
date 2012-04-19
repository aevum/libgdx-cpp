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
#include <cassert>

using namespace gdx_cpp::backends::android;

gdx_cpp::backends::android::AndroidInput::AndroidInput()
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

void gdx_cpp::backends::android::AndroidInput::cancelVibrate()
{
}

float gdx_cpp::backends::android::AndroidInput::getAccelerometerX()
{
    return 0;
}

float gdx_cpp::backends::android::AndroidInput::getAccelerometerY()
{
    return 0;
}

float gdx_cpp::backends::android::AndroidInput::getAccelerometerZ()
{
    return 0;
}

float gdx_cpp::backends::android::AndroidInput::getAzimuth()
{
    return 0;
}

long int gdx_cpp::backends::android::AndroidInput::getCurrentEventTime()
{
    return 0;
}

int gdx_cpp::backends::android::AndroidInput::getDeltaX()
{
    return deltaX;
}

int gdx_cpp::backends::android::AndroidInput::getDeltaX(int pointer)
{       
    if (pointer == 0) {
        return deltaX;
    }
    return 0;
}

int gdx_cpp::backends::android::AndroidInput::getDeltaY()
{
    return deltaY;
}

int gdx_cpp::backends::android::AndroidInput::getDeltaY(int pointer)
{
    if (pointer == 0) {
        return deltaY;
    }
    return 0;
}

gdx_cpp::Input::Orientation gdx_cpp::backends::android::AndroidInput::getNativeOrientation()
{
    return gdx_cpp::Input::Landscape;
}

float gdx_cpp::backends::android::AndroidInput::getPitch()
{
    return 0;
}

float gdx_cpp::backends::android::AndroidInput::getRoll()
{
    return 0;
}

int gdx_cpp::backends::android::AndroidInput::getRotation()
{
    return 0;
}

void gdx_cpp::backends::android::AndroidInput::getTextInput(const gdx_cpp::Input::TextInputListener& listener,
                                                      const std::string& title, const std::string& text)
{
}

int gdx_cpp::backends::android::AndroidInput::getX()
{
    return touchX;
}

int gdx_cpp::backends::android::AndroidInput::getX(int pointer)
{
    return 0;
}

int gdx_cpp::backends::android::AndroidInput::getY()
{
    return touchY;
}

int gdx_cpp::backends::android::AndroidInput::getY(int pointer)
{
    return 0;
}

bool gdx_cpp::backends::android::AndroidInput::isButtonPressed(int button)
{
    return false;
}

bool gdx_cpp::backends::android::AndroidInput::isCursorCatched()
{
    return false;
}

bool gdx_cpp::backends::android::AndroidInput::isKeyPressed(int key)
{
    return false;
}

bool gdx_cpp::backends::android::AndroidInput::isPeripheralAvailable(int peripheral)
{
    return peripheral == Peripheral::HardwareKeyboard;
}

bool gdx_cpp::backends::android::AndroidInput::isTouched()
{
    return touching;
}

bool gdx_cpp::backends::android::AndroidInput::isTouched(int pointer)
{
    //TODO 
    return pointer == 0 && touching;
}

bool gdx_cpp::backends::android::AndroidInput::justTouched()
{
    return _justTouched;
}

void gdx_cpp::backends::android::AndroidInput::setCatchBackKey(bool catchBack)
{
}

void gdx_cpp::backends::android::AndroidInput::setCatchMenuKey(bool catchMenu)
{
}

void gdx_cpp::backends::android::AndroidInput::setCursorCatched(bool catched)
{
}

void gdx_cpp::backends::android::AndroidInput::setCursorPosition(int x, int y)
{
}

void gdx_cpp::backends::android::AndroidInput::setInputProcessor(gdx_cpp::InputProcessor* processor)
{
    this->processor = processor;
}

void gdx_cpp::backends::android::AndroidInput::setOnscreenKeyboardVisible(bool visible)
{
}

void gdx_cpp::backends::android::AndroidInput::vibrate(int milliseconds)
{
}

void gdx_cpp::backends::android::AndroidInput::vibrate(long int* pattern, int repeat)
{
}

void gdx_cpp::backends::android::AndroidInput::reset()
{
    this->_justTouched = false;
}

void gdx_cpp::backends::android::AndroidInput::handleTouchDrag(float x, float y, int pointer)
{
    deltaX = x - touchX;
    deltaY = y - touchY;
    touchX = x;
    touchY = y;
    if (this->processor) {
        this->processor->touchDragged(x, y, pointer);
    }
}

void gdx_cpp::backends::android::AndroidInput::handleTouchDown(float x, float y, int pointer)
{
    touchX = x;
    touchY = y;
    touching = true;
    
    if (this->processor) {
        this->processor->touchDown(x, y, pointer, 0);
    }
}

void gdx_cpp::backends::android::AndroidInput::handleTouchUp(float x, float y, int pointer)
{
    touching = false;
    deltaX = 0;
    deltaY = 0;
    if (this->processor) {
        this->processor->touchUp(x, y, pointer , 0);
    }
}

void gdx_cpp::backends::android::AndroidInput::setKeyboardRepeat(int delay, int repeatInterval)
{

}

