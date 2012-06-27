
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

using namespace gdx::ui;

void Slider::setStyle (const SliderStyle& style) {
    this.style = style;
}

void Slider::layout () {
}

void Slider::draw (const gdx::SpriteBatch& batch,float parentAlpha) {
    final TextureRegion knob = style.knob;
    final NinePatch slider = style.slider;

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
    calculateSliderPosAndValue(x);
    return true;
}

void Slider::touchUp (float x,float y,int pointer) {
    calculateSliderPosAndValue(x);
}

void Slider::touchDragged (float x,float y,int pointer) {
    calculateSliderPosAndValue(x);
}

void Slider::calculateSliderPosAndValue (float x) {
    final TextureRegion knob = style.knob;

    sliderPos = x - knob.getRegionWidth() / 2;
    sliderPos = Math.max(0, sliderPos);
    sliderPos = Math.min(width - knob.getRegionWidth(), sliderPos);
    value = min + (max - min) * (sliderPos / (width - knob.getRegionWidth()));
    if (listener != null) listener.changed(this, getValue());
}

gdx::Actor& Slider::hit (float x,float y) {
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

float Slider::getPrefWidth () {
    return 140;
}

float Slider::getPrefHeight () {
    return Math.max(style.knob.getRegionHeight(), style.slider.getTotalHeight());
}

Slider::Slider (float min,float max,float steps,const Skin& skin) {
    this(min, max, steps, skin.getStyle(SliderStyle.class), null);
}

Slider::Slider (float min,float max,float steps,const SliderStyle& style) {
    this(min, max, steps, style, null);
}

Slider::Slider (float min,float max,float steps,const SliderStyle& style,const std::string& name) {
    super(name);
    setStyle(style);
    if (min > max) throw new IllegalArgumentException("min must be > max");
    if (steps < 0) throw new IllegalArgumentException("unit must be > 0");
    this.min = min;
    this.max = max;
    this.steps = steps;
    this.value = min;
}

