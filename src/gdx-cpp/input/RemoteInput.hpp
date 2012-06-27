
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

#ifndef GDX_CPP_INPUT_REMOTEINPUT_HPP_
#define GDX_CPP_INPUT_REMOTEINPUT_HPP_

namespace gdx {

class RemoteInput: public Input {
public:
    void run ();
    void run ();
    float getAccelerometerX ();
    float getAccelerometerY ();
    float getAccelerometerZ ();
    int getX ();
    int getX (int pointer);
    int getY ();
    int getY (int pointer);
    bool isTouched ();
    bool justTouched ();
    bool isTouched (int pointer);
    bool isButtonPressed (int button);
    bool isKeyPressed (int key);
    void getTextInput (const TextInputListener& listener,const std::string& title,const std::string& text);
    void setOnscreenKeyboardVisible (bool visible);
    void vibrate (int milliseconds);
    void vibrate (int repeat);
    void cancelVibrate ();
    float getAzimuth ();
    float getPitch ();
    float getRoll ();
    void setCatchBackKey (bool catchBack);
    void setInputProcessor (const InputProcessor& processor);
    InputProcessor& getInputProcessor ();
    std::string* getIPs ();
    bool isPeripheralAvailable (const Peripheral& peripheral);
    int getRotation ();
    Orientation& getNativeOrientation ();
    void setCursorCatched (bool catched);
    bool isCursorCatched ();
    int getDeltaX ();
    int getDeltaX (int pointer);
    int getDeltaY ();
    int getDeltaY (int pointer);
    void setCursorPosition (int x,int y);
    void setCatchMenuKey (bool catchMenu);
    long getCurrentEventTime ();
    String[] ips;

protected:


private:
    int port;
};

} // namespace gdx

#endif // GDX_CPP_INPUT_REMOTEINPUT_HPP_
