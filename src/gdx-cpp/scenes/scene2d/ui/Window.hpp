
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_WINDOW_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_WINDOW_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace ui {

class Window: public gdx_cpp::scenes::scene2d::ui::tablelayout::Table {
public:
    void setStyle (const WindowStyle& style);
    void draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha);
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    void touchDragged (float x,float y,int pointer);
    gdx_cpp::scenes::scene2d::Actor& hit (float x,float y);
    void setTitle (const std::string& title);
    std::string& getTitle ();
    void setMovable (bool isMovable);
    bool isMovable ();
    void setModal (bool isModal);
    bool isModal ();
    Window (const std::string& title,const gdx_cpp::scenes::scene2d::Stage& stage,const Skin& skin);
    Window (const std::string& title,const gdx_cpp::scenes::scene2d::Stage& stage,const WindowStyle& style);
    Window (const std::string& name,const std::string& title,const gdx_cpp::scenes::scene2d::Stage& stage,const WindowStyle& style,int prefWidth,int prefHeight);

protected:
    WindowStyle style ;
    String title ;
    Stage stage ;
    Rectangle widgetBounds = new Rectangle();
    Rectangle titleBounds = new Rectangle();
    TextBounds textBounds = new TextBounds();
    Rectangle scissors = new Rectangle();
    boolean move = false;
    boolean isMovable = true;
    Vector2 initial = new Vector2();
    boolean isModal = false;
    NinePatch background = style.background;
    TableLayout layout = getTableLayout();

private:
    void calculateBoundsAndScissors (const gdx_cpp::math::Matrix4& transform);
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace ui

#endif // GDX_CPP_SCENES_SCENE2D_UI_WINDOW_HPP_
