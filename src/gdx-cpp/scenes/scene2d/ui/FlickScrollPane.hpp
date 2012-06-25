
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_FLICKSCROLLPANE_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_FLICKSCROLLPANE_HPP_

namespace gdx {
namespace scenes {
namespace scene2d {
namespace ui {

class FlickScrollPane {
public:
    bool pan (int x,int y,int deltaX,int deltaY);
    bool fling (float x,float y);
    bool touchDown (int x,int y,int pointer);
    bool zoom (float originalDistance,float currentDistance);
    bool tap (int x,int y,int count);
    bool longPress (int x,int y);
    void toLocalCoordinates (const gdx::Actor& actor,const gdx::Vector2& point);
    void act (float delta);
    void draw (const gdx::SpriteBatch& batch,float parentAlpha);
    void layout ();
    void invalidate ();
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    void touchDragged (float x,float y,int pointer);
    gdx::Actor& hit (float x,float y);
    void setScrollX (float pixels);
    float getScrollX ();
    void setScrollY (float pixels);
    float getScrollY ();
    void setWidget (const gdx::Actor& widget);
    gdx::Actor& getWidget ();
    bool isPanning ();
    float getVelocityX ();
    float getVelocityY ();
    float getPrefWidth ();
    float getPrefHeight ();
    float getMinWidth ();
    float getMinHeight ();
    float getMaxWidth ();
    float getMaxHeight ();
    FlickScrollPane (const gdx::Actor& widget,const gdx::Stage& stage);
    FlickScrollPane (const gdx::Actor& widget,const gdx::Stage& stage,const std::string& name);
    boolean bounces = true;
    float flingTime = 1f;
    float bounceDistance = 50, bounceSpeedMin = 30, bounceSpeedMax = 200;
    boolean emptySpaceOnlyScroll ;
    boolean clamp = true;

protected:
    boolean needsLayout ;
    float flingTimer ;

private:
    void calculateBoundsAndPositions (const gdx::Matrix4& batchTransform);
    Stage stage ;
    Actor widget ;
    Rectangle widgetAreaBounds = new Rectangle();
    Rectangle scissorBounds = new Rectangle();
    GestureDetector gestureDetector ;
};

} // namespace gdx
} // namespace scenes
} // namespace scene2d
} // namespace ui

#endif // GDX_CPP_SCENES_SCENE2D_UI_FLICKSCROLLPANE_HPP_
