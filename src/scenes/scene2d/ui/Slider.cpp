
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

#include "Slider.hpp"

using namespace gdx_cpp::scenes::scene2d::ui;

void Slider::layout () {
    prefHeight = Math.max(style.knob.getRegionHeight(), style.slider.getTotalHeight());
    invalidated = false;
}

void Slider::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    final TextureRegion knob = style.knob;
    final NinePatch slider = style.slider;

    if (invalidated) layout();

    batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);
    sliderPos = (value - min) / (max - min) * (width - knob.getRegionWidth());
    sliderPos = Math.max(0, sliderPos);
    sliderPos = Math.min(width - knob.getRegionWidth(), sliderPos);

    float maxHeight = Math.max(knob.getRegionHeight(), slider.getTotalHeight());
    slider.draw(batch, x, y + (int)((maxHeight - slider.getTotalHeight()) * 0.5f), width, slider.getTotalHeight());
    batch.draw(knob, x + sliderPos, y + (int)((maxHeight - knob.getRegionHeight()) * 0.5f));
}

bool Slider::touchDown (float x,float y,int pointer) {
    if (pointer != 0) return false;
    if (hit(x, y) != null) {
        calculateSliderPosAndValue(x);
        parent.focus(this, pointer);
        return true;
    }
    return false;
}

bool Slider::touchUp (float x,float y,int pointer) {
    if (pointer != 0) return false;
    if (parent.focusedActor[0] == this) {
        calculateSliderPosAndValue(x);
        parent.focus(null, pointer);
        return true;
    }
    return false;
}

bool Slider::touchDragged (float x,float y,int pointer) {
    if (pointer != 0) return false;
    if (parent.focusedActor[0] == this) {
        calculateSliderPosAndValue(x);
        return true;
    }
    return false;
}

void Slider::calculateSliderPosAndValue (float x) {
    final TextureRegion knob = style.knob;

    sliderPos = x - knob.getRegionWidth() / 2;
    sliderPos = Math.max(0, sliderPos);
    sliderPos = Math.min(width - knob.getRegionWidth(), sliderPos);
    value = min + (max - min) * (sliderPos / (width - knob.getRegionWidth()));
    if (listener != null) listener.changed(this, getValue());
}

gdx_cpp::scenes::scene2d::Actor& Slider::hit (float x,float y) {
    return x > 0 && x < width && y > 0 && y < height ? this : null;
}

Slider& Slider::setValueChangedListener (const ValueChangedListener& listener) {
    this.listener = listener;
    return this;
}

float Slider::getValue () {
    return (float)Math.floor(value / steps) * steps;
}

void Slider::setValue (float value) {
    if (value < min || value > max) throw new IllegalArgumentException("value must be >= min && <= max");
    this.value = value;
    if (listener != null) listener.changed(this, getValue());
}

void Slider::setRange (float min,float max) {
    if (min >= max) throw new IllegalArgumentException("min must be < max");
    this.min = min;
    this.max = max;
    this.value = min;
    if (listener != null) listener.changed(this, getValue());
}

