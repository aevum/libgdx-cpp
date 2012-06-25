
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_LABEL_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_LABEL_HPP_

namespace gdx {
namespace scenes {
namespace scene2d {
namespace ui {

class Label {
public:
    void setStyle (const LabelStyle& style);
    void setText (const std::string& text);
    std::string& getText ();
    void setColor (float color);
    void setColor (const gdx::Color& tint);
    void setColor (float r,float g,float b,float a);
    gdx::Color& getColor ();
    void layout ();
    void draw (const gdx::SpriteBatch& batch,float parentAlpha);
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    void touchDragged (float x,float y,int pointer);
    gdx::Actor& hit (float x,float y);
    float getPrefWidth ();
    float getPrefHeight ();
    Label (const std::string& text,const Skin& skin);
    Label (const std::string& text,const LabelStyle& style);
    Label (const std::string& text,const LabelStyle& style,const std::string& name);

protected:
    LabelStyle style ;
    BitmapFontCache cache ;
    String text ;

private:

};

} // namespace gdx
} // namespace scenes
} // namespace scene2d
} // namespace ui

#endif // GDX_CPP_SCENES_SCENE2D_UI_LABEL_HPP_
