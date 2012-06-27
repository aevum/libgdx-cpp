
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_SPLITPANE_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_SPLITPANE_HPP_

namespace gdx {
namespace scenes {
namespace scene2d {
namespace ui {

class SplitPane {
public:
    void setStyle (const SplitPaneStyle& style);
    void layout ();
    void invalidate ();
    float getPrefWidth ();
    float getPrefHeight ();
    float getMinWidth ();
    float getMinHeight ();
    float getMaxWidth ();
    float getMaxHeight ();
    void draw (const gdx::SpriteBatch& batch,float parentAlpha);
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    void touchDragged (float x,float y,int pointer);
    gdx::Actor& hit (float x,float y);
    void setSplitAmount (float split);
    float getSplit ();
    void setMinSplitAmount (float minAmount);
    void setMaxSplitAmount (float maxAmount);
    void setWidgets (const gdx::Actor& firstWidget,const gdx::Actor& secondWidget);
    SplitPane (const gdx::Actor& firstWidget,const gdx::Actor& secondWidget,bool vertical,const gdx::Stage& stage,const Skin& skin);
    SplitPane (const gdx::Actor& firstWidget,const gdx::Actor& secondWidget,bool vertical,const gdx::Stage& stage,const SplitPaneStyle& style);
    SplitPane (const gdx::Actor& firstWidget,const gdx::Actor& secondWidget,bool vertical,const gdx::Stage& stage,const SplitPaneStyle& style,const std::string& name);

protected:
    SplitPaneStyle style ;
    boolean invalidated = false;
    boolean vertical ;
    float splitAmount = 0.5f;
    float minAmount = 0;
    float maxAmount = 1;
    float oldSplitAmount = 0;
    Stage stage ;
    Actor firstWidget ;
    Actor secondWidget ;
    Rectangle firstWidgetBounds = new Rectangle();
    Rectangle secondWidgetBounds = new Rectangle();
    Rectangle handleBounds = new Rectangle();
    Rectangle[] scissors = new Rectangle[] {new Rectangle(), new Rectangle()};
    boolean touchDrag = false;

private:
    void calculateBoundsAndPositions (const gdx::Matrix4& transform);
    void calculateHorizBoundsAndPositions ();
    void calculateVertBoundsAndPositions ();
};

} // namespace gdx
} // namespace scenes
} // namespace scene2d
} // namespace ui

#endif // GDX_CPP_SCENES_SCENE2D_UI_SPLITPANE_HPP_
