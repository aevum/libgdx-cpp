
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_BUTTON_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_BUTTON_HPP_

namespace gdx {
namespace scenes {
namespace scene2d {
namespace ui {

class Button: public gdx::ui::tablelayout::Table {
public:
    void click (const gdx::Actor& actor);
    void setStyle (const ButtonStyle& style);
    void setClickListener (const ClickListener& listener);
    void setText (const std::string& text);
    std::string& getText ();
    void draw (const gdx::SpriteBatch& batch,float parentAlpha);
    Button (const Skin& skin);
    Button (const ButtonStyle& style);
    Button (const gdx::Actor& child,const Skin& skin);
    Button (const gdx::Actor& child,const ButtonStyle& style);
    Button (const std::string& text,const Skin& skin);
    Button (const std::string& text,const ButtonStyle& style);
    Button (const std::string& text,const ButtonStyle& style,const std::string& name);
    Button (const ButtonStyle& style,const std::string& name);
    ButtonStyle style ;
    boolean isChecked ;

protected:
    ClickListener listener ;

private:

};

} // namespace gdx
} // namespace scenes
} // namespace scene2d
} // namespace ui

#endif // GDX_CPP_SCENES_SCENE2D_UI_BUTTON_HPP_
