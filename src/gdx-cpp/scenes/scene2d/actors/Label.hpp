
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

#ifndef GDX_CPP_SCENES_SCENE2D_ACTORS_LABEL_HPP_
#define GDX_CPP_SCENES_SCENE2D_ACTORS_LABEL_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace actors {

class Label {
public:
    void setText (const std::string& text);
    void setMultiLineText (const std::string& text);
    void setWrappedText (const std::string& text,const gdx_cpp::graphics::g2d::BitmapFont::HAlignment& halign);
    void setFont (const gdx_cpp::graphics::g2d::BitmapFont& font);
    void draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha);
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    void touchDragged (float x,float y,int pointer);
    gdx_cpp::scenes::scene2d::Actor& hit (float x,float y);
    void layout ();
    void invalidate ();
    float getPrefWidth ();
    float getPrefHeight ();
    float getMinWidth ();
    float getMinHeight ();
    float getMaxWidth ();
    float getMaxHeight ();
    Label (const std::string& name,const gdx_cpp::graphics::g2d::BitmapFont& font);
    Label (const std::string& name,const gdx_cpp::graphics::g2d::BitmapFont& font,const std::string& text);
    BitmapFontCache cache ;
    VAlignment valign = VAlignment.BOTTOM;
    String text ;
    TextBounds bounds = new TextBounds();

protected:


private:
    WrapType wrapType ;
    HAlignment halign ;
    float lastWidth = -1;
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace actors

#endif // GDX_CPP_SCENES_SCENE2D_ACTORS_LABEL_HPP_
