
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_SCROLLPANE_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_SCROLLPANE_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace ui {

class ScrollPane {
public:
    void draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha);
    void layout ();
    void invalidate ();
    float getPrefWidth ();
    float getPrefHeight ();
    float getMinWidth ();
    float getMinHeight ();
    float getMaxWidth ();
    float getMaxHeight ();
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    void touchDragged (float x,float y,int pointer);
    gdx_cpp::scenes::scene2d::Actor& hit (float x,float y);
    void setVScrollAmount (float vScrollAmount);
    void setHScrollAmount (float hScrollAmount);
    void setWidget (const gdx_cpp::scenes::scene2d::Actor& widget);
    ScrollPane (const gdx_cpp::scenes::scene2d::Actor& widget,const gdx_cpp::scenes::scene2d::Stage& stage,const Skin& skin);
    ScrollPane (const gdx_cpp::scenes::scene2d::Actor& widget,const gdx_cpp::scenes::scene2d::Stage& stage,const ScrollPaneStyle& style);
    ScrollPane (const gdx_cpp::scenes::scene2d::Actor& widget,const gdx_cpp::scenes::scene2d::Stage& stage,const ScrollPaneStyle& style,const std::string& name);

protected:
    ScrollPaneStyle style ;
    Actor widget ;
    Stage stage ;
    Rectangle hScrollBounds = new Rectangle();
    Rectangle vScrollBounds = new Rectangle();
    Rectangle hScrollKnobBounds = new Rectangle();
    Rectangle vScrollKnobBounds = new Rectangle();
    Rectangle widgetAreaBounds = new Rectangle();
    Rectangle scissorBounds = new Rectangle();
    float hScrollAmount = 0;
    float vScrollAmount = 0;
    boolean hasHScroll = false;
    boolean hasVScroll = false;
    boolean touchScrollH = false;
    boolean touchScrollV = false;
    Vector2 lastPoint = new Vector2();
    Vector3 tmp = new Vector3();

private:
    void calculateBoundsAndPositions (const gdx_cpp::math::Matrix4& batchTransform);
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace ui

#endif // GDX_CPP_SCENES_SCENE2D_UI_SCROLLPANE_HPP_
