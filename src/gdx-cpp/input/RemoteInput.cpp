
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#include "RemoteInput.hpp"

using namespace gdx;

void RemoteInput::run () {
    justTouched = false;
    if (processor != null) {
        if (touchEvent != null) {
            touchX[touchEvent.pointer] = touchEvent.x;
            touchY[touchEvent.pointer] = touchEvent.y;
            switch (touchEvent.type) {
            case TouchEvent.TOUCH_DOWN:
                processor.touchDown(touchEvent.x, touchEvent.y, touchEvent.pointer, Input.Buttons.LEFT);
                isTouched[touchEvent.pointer] = true;
                justTouched = true;
                break;
            case TouchEvent.TOUCH_UP:
                processor.touchUp(touchEvent.x, touchEvent.y, touchEvent.pointer, Input.Buttons.LEFT);
                isTouched[touchEvent.pointer] = false;
                break;
            case TouchEvent.TOUCH_DRAGGED:
                processor.touchDragged(touchEvent.x, touchEvent.y, touchEvent.pointer);
                break;
            }
        }
        if (keyEvent != null) {
            switch (keyEvent.type) {
            case KeyEvent.KEY_DOWN:
                processor.keyDown(keyEvent.keyCode);
                keys.add(keyEvent.keyCode);
                break;
            case KeyEvent.KEY_UP:
                processor.keyUp(keyEvent.keyCode);
                keys.remove(keyEvent.keyCode);
                break;
            case KeyEvent.KEY_TYPED:
                processor.keyTyped(keyEvent.keyChar);
                break;
            }
        }
    } else {
        if (touchEvent != null) {
            touchX[touchEvent.pointer] = touchEvent.x;
            touchY[touchEvent.pointer] = touchEvent.y;
            if (touchEvent.type == TouchEvent.TOUCH_DOWN) {
                isTouched[touchEvent.pointer] = true;
                justTouched = true;
            }
            if (touchEvent.type == TouchEvent.TOUCH_UP) {
                isTouched[touchEvent.pointer] = false;
            }
        }
        if (keyEvent != null) {
            if (keyEvent.type == KeyEvent.KEY_DOWN) keys.add(keyEvent.keyCode);
            if (keyEvent.type == KeyEvent.KEY_UP) keys.remove(keyEvent.keyCode);
        }
    }
}

void RemoteInput::run () {
    while (true) {
        try {
            System.out.println("listening, port " + port);
            Socket socket = null;
            while (true) {
                socket = serverSocket.accept();
                break;
            }
            socket.setTcpNoDelay(true);
            socket.setSoTimeout(3000);

            DataInputStream in = new DataInputStream(socket.getInputStream());
            multiTouch = in.readBoolean();
            while (true) {
                int event = in.readInt();
                KeyEvent keyEvent = null;
                TouchEvent touchEvent = null;
                switch (event) {
                case RemoteSender.ACCEL:
                    accel[0] = in.readFloat();
                    accel[1] = in.readFloat();
                    accel[2] = in.readFloat();
                    break;
                case RemoteSender.COMPASS:
                    compass[0] = in.readFloat();
                    compass[1] = in.readFloat();
                    compass[2] = in.readFloat();
                    break;
                case RemoteSender.SIZE:
                    remoteWidth = in.readFloat();
                    remoteHeight = in.readFloat();
                    break;
                case RemoteSender.KEY_DOWN:
                    keyEvent = new KeyEvent();
                    keyEvent.keyCode = in.readInt();
                    keyEvent.type = KeyEvent.KEY_DOWN;
                    break;
                case RemoteSender.KEY_UP:
                    keyEvent = new KeyEvent();
                    keyEvent.keyCode = in.readInt();
                    keyEvent.type = KeyEvent.KEY_UP;
                    break;
                case RemoteSender.KEY_TYPED:
                    keyEvent = new KeyEvent();
                    keyEvent.keyChar = in.readChar();
                    keyEvent.type = KeyEvent.KEY_TYPED;
                    break;
                case RemoteSender.TOUCH_DOWN:
                    touchEvent = new TouchEvent();
                    touchEvent.x = (int)((in.readInt() / remoteWidth) * Gdx.graphics.getWidth());
                    touchEvent.y = (int)((in.readInt() / remoteHeight) * Gdx.graphics.getHeight());
                    touchEvent.pointer = in.readInt();
                    touchEvent.type = TouchEvent.TOUCH_DOWN;
                    break;
                case RemoteSender.TOUCH_UP:
                    touchEvent = new TouchEvent();
                    touchEvent.x = (int)((in.readInt() / remoteWidth) * Gdx.graphics.getWidth());
                    touchEvent.y = (int)((in.readInt() / remoteHeight) * Gdx.graphics.getHeight());
                    touchEvent.pointer = in.readInt();
                    touchEvent.type = TouchEvent.TOUCH_UP;
                    break;
                case RemoteSender.TOUCH_DRAGGED:
                    touchEvent = new TouchEvent();
                    touchEvent.x = (int)((in.readInt() / remoteWidth) * Gdx.graphics.getWidth());
                    touchEvent.y = (int)((in.readInt() / remoteHeight) * Gdx.graphics.getHeight());
                    touchEvent.pointer = in.readInt();
                    touchEvent.type = TouchEvent.TOUCH_DRAGGED;
                    break;
                }

                Gdx.app.postRunnable(new EventTrigger(touchEvent, keyEvent));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

float RemoteInput::getAccelerometerX () {
    return accel[0];
}

float RemoteInput::getAccelerometerY () {
    return accel[1];
}

float RemoteInput::getAccelerometerZ () {
    return accel[2];
}

int RemoteInput::getX () {
    return touchX[0];
}

int RemoteInput::getX (int pointer) {
    return touchX[pointer];
}

int RemoteInput::getY () {
    return touchY[0];
}

int RemoteInput::getY (int pointer) {
    return touchY[pointer];
}

bool RemoteInput::isTouched () {
    return isTouched[0];
}

bool RemoteInput::justTouched () {
    return justTouched;
}

bool RemoteInput::isTouched (int pointer) {
    return isTouched[pointer];
}

bool RemoteInput::isButtonPressed (int button) {
    if (button != Buttons.LEFT) return false;
    for (int i = 0; i < isTouched.length; i++)
        if (isTouched[i]) return true;
    return false;
}

bool RemoteInput::isKeyPressed (int key) {
    return keys.contains(key);
}

void RemoteInput::getTextInput (const TextInputListener& listener,const std::string& title,const std::string& text) {
    Gdx.app.getInput().getTextInput(listener, title, text);
}

void RemoteInput::setOnscreenKeyboardVisible (bool visible) {
}

void RemoteInput::vibrate (int milliseconds) {

}

void RemoteInput::vibrate (int repeat) {

}

void RemoteInput::cancelVibrate () {

}

float RemoteInput::getAzimuth () {
    return compass[0];
}

float RemoteInput::getPitch () {
    return compass[1];
}

float RemoteInput::getRoll () {
    return compass[2];
}

void RemoteInput::setCatchBackKey (bool catchBack) {

}

void RemoteInput::setInputProcessor (const InputProcessor& processor) {
    this.processor = processor;
}

InputProcessor& RemoteInput::getInputProcessor () {
    return this.processor;
}

std::string* RemoteInput::getIPs () {
    return ips;
}

bool RemoteInput::isPeripheralAvailable (const Peripheral& peripheral) {
    if (peripheral == Peripheral.Accelerometer) return true;
    if (peripheral == Peripheral.Compass) return true;
    if (peripheral == Peripheral.MultitouchScreen) return multiTouch;
    return false;
}

int RemoteInput::getRotation () {
    return 0;
}

Orientation& RemoteInput::getNativeOrientation () {
    return Orientation.Landscape;
}

void RemoteInput::setCursorCatched (bool catched) {

}

bool RemoteInput::isCursorCatched () {
    return false;
}

int RemoteInput::getDeltaX () {
    // TODO Auto-generated method stub
    return 0;
}

int RemoteInput::getDeltaX (int pointer) {
    return 0;
}

int RemoteInput::getDeltaY () {
    return 0;
}

int RemoteInput::getDeltaY (int pointer) {
    return 0;
}

void RemoteInput::setCursorPosition (int x,int y) {
}

void RemoteInput::setCatchMenuKey (bool catchMenu) {
    // TODO Auto-generated method stub

}

long RemoteInput::getCurrentEventTime () {
    // TODO Auto-generated method stub
    return 0;
}

