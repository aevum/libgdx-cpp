
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_SLIDER_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_SLIDER_HPP_

namespace gdx {
namespace scenes {
namespace scene2d {
namespace ui {

class Slider {
public:
    void setStyle (const SliderStyle& style);
    void layout ();
    void draw (const gdx::SpriteBatch& batch,float parentAlpha);
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    void touchDragged (float x,float y,int pointer);
    gdx::Actor& hit (float x,float y);
    void changed (const Slider& slider,float value);
    Slider& setValueChangedListener (const ValueChangedListener& listener);
    float getValue ();
    void setValue (float value);
    void setRange (float min,float max);
    float getPrefWidth ();
    float getPrefHeight ();
    Slider (float min,float max,float steps,const Skin& skin);
    Slider (float min,float max,float steps,const SliderStyle& style);
    Slider (float min,float max,float steps,const SliderStyle& style,const std::string& name);

protected:
    SliderStyle style ;
    float min ;
    float max ;
    float steps ;
    float value ;
    float sliderPos ;
    ValueChangedListener listener = null;

private:
    void calculateSliderPosAndValue (float x);
};

} // namespace gdx
} // namespace scenes
} // namespace scene2d
} // namespace ui

#endif // GDX_CPP_SCENES_SCENE2D_UI_SLIDER_HPP_
