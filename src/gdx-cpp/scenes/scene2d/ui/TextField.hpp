
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_TEXTFIELD_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_TEXTFIELD_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace ui {

class TextField {
public:
    void setStyle (const TextFieldStyle& style);
    void layout ();
    void draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha);
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    void touchDragged (float x,float y,int pointer);
    bool keyDown (int keycode);
    bool keyTyped (char character);
    gdx_cpp::scenes::scene2d::Actor& hit (float x,float y);
    void keyTyped (const TextField& textField,char key);
    void setTextFieldListener (const TextFieldListener& listener);
    void setText (const std::string& text);
    std::string& getText ();
    float getPrefWidth ();
    float getPrefHeight ();
    OnscreenKeyboard& getOnscreenKeyboard ();
    void setOnscreenKeyboard (const OnscreenKeyboard& keyboard);
    void show (bool visible);
    void show (bool visible);
    void setClipboard (const gdx_cpp::scenes::scene2d::ui::utils::Clipboard& clipboard);
    TextField (const Skin& skin);
    TextField (const std::string& text,const Skin& skin);
    TextField (const TextFieldStyle& style);
    TextField (const std::string& text,const TextFieldStyle& style);
    TextField (const std::string& text,const TextFieldStyle& style,const std::string& name);

protected:
    TextFieldStyle style ;
    Clipboard clipboard ;
    Rectangle fieldBounds = new Rectangle();
    TextBounds textBounds = new TextBounds();
    Rectangle scissor = new Rectangle();
    TextFieldListener listener ;
    String text = "";
    int cursor = 0;
    float renderOffset = 0;
    float textOffset = 0;
    int visibleTextStart = 0;
    int visibleTextEnd = 0;
    StringBuilder builder = new StringBuilder();
    FloatArray glyphAdvances = new FloatArray();
    FloatArray glyphPositions = new FloatArray();
    float blinkTime = 0.42f;
    long lastBlink = System.nanoTime();
    boolean cursorOn = true;
    boolean hasSelection = false;
    int selectionStart = 0;
    float selectionX = 0;
    float selectionWidth = 0;
    OnscreenKeyboard keyboard = new DefaultOnscreenKeyboard();

private:
    void blink ();
    void calculateOffsets ();
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace ui

#endif // GDX_CPP_SCENES_SCENE2D_UI_TEXTFIELD_HPP_
