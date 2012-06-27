
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

#include "Label.hpp"

using namespace gdx::ui;

void Label::setStyle (const LabelStyle& style) {
    this.style = style;
    cache = new BitmapFontCache(style.font);
    cache.setColor(style.fontColor);
    setText(text);
}

void Label::setText (const std::string& text) {
    this.text = text;
    TextBounds bounds = style.font.getMultiLineBounds(text);
    cache.setMultiLineText(text, 0, bounds.height);
    prefWidth = bounds.width;
    prefHeight = bounds.height - style.font.getDescent() * 2;
}

std::string& Label::getText () {
    return text;
}

void Label::setColor (float color) {
    cache.setColor(color);
}

void Label::setColor (const gdx::Color& tint) {
    cache.setColor(tint);
}

void Label::setColor (float r,float g,float b,float a) {
    cache.setColor(r, g, b, a);
}

gdx::Color& Label::getColor () {
    return cache.getColor();
}

void Label::layout () {
}

void Label::draw (const gdx::SpriteBatch& batch,float parentAlpha) {
    cache.setColor(color);
    cache.setPosition(x, y - style.font.getDescent());
    cache.draw(batch, parentAlpha);
}

bool Label::touchDown (float x,float y,int pointer) {
    return false;
}

void Label::touchUp (float x,float y,int pointer) {
}

void Label::touchDragged (float x,float y,int pointer) {
}

gdx::Actor& Label::hit (float x,float y) {
    return null;
}

float Label::getPrefWidth () {
    return prefWidth;
}

float Label::getPrefHeight () {
    return prefHeight;
}

Label::Label (const std::string& text,const Skin& skin) {
    this(text, skin.getStyle(LabelStyle.class), null);
}

Label::Label (const std::string& text,const LabelStyle& style) {
    this(text, style, null);
}

Label::Label (const std::string& text,const LabelStyle& style,const std::string& name) {
    super(name);
    this.text = text;
    setStyle(style);

    touchable = false;
}

