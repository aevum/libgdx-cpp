
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

using namespace gdx_cpp::scenes::scene2d::actors;

void Label::setText (const std::string& text) {
    this.text = text;
    wrapType = WrapType.singleLine;
    bounds.set(cache.setText(text, 0, cache.getFont().isFlipped() ? 0 : cache.getFont().getCapHeight()));
    width = bounds.width;
    height = bounds.height;
}

void Label::setMultiLineText (const std::string& text) {
    this.text = text;
    wrapType = WrapType.multiLine;
    bounds.set(cache.getFont().getMultiLineBounds(text));
    cache.setMultiLineText(text, 0, cache.getFont().isFlipped() ? 0 : bounds.height);
    width = bounds.width;
    height = bounds.height;
}

void Label::setWrappedText (const std::string& text,const gdx_cpp::graphics::g2d::BitmapFont::HAlignment& halign) {
    this.text = text;
    this.halign = halign;
    wrapType = WrapType.wrapped;
    bounds.set(cache.getFont().getWrappedBounds(text, width));
    cache.setWrappedText(text, 0, cache.getFont().isFlipped() ? 0 : bounds.height, width, halign);
}

void Label::setFont (const gdx_cpp::graphics::g2d::BitmapFont& font) {
    cache = new BitmapFontCache(font);
    switch (wrapType) {
    case singleLine:
        setText(text);
        break;
    case multiLine:
        setMultiLineText(text);
        break;
    case wrapped:
        setWrappedText(text, halign);
        break;
    }
}

void Label::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    cache.setColor(color.r, color.g, color.b, color.a * parentAlpha);
    switch (valign) {
    case TOP:
        if (cache.getFont().isFlipped())
            cache.setPosition(x, y);
        else
            cache.setPosition(x, y + height - bounds.height);
        break;
    case CENTER:
        cache.setPosition(x, y + (height - bounds.height) / 2);
        break;
    case BOTTOM:
        if (cache.getFont().isFlipped())
            cache.setPosition(x, y + height - bounds.height);
        else
            cache.setPosition(x, y);
        break;
    }
    cache.draw(batch);
}

bool Label::touchDown (float x,float y,int pointer) {
    if (!touchable) return false;
    return x > 0 && y > 0 && x < width && y < height;
}

bool Label::touchUp (float x,float y,int pointer) {
    if (!touchable) return false;
    return x > 0 && y > 0 && x < width && y < height;
}

bool Label::touchDragged (float x,float y,int pointer) {
    if (!touchable) return false;
    return x > 0 && y > 0 && x < width && y < height;
}

gdx_cpp::scenes::scene2d::Actor& Label::hit (float x,float y) {
    return x > 0 && y > 0 && x < width && y < height ? this : null;
}

void Label::layout () {
    if (wrapType == WrapType.wrapped && lastWidth != width) setWrappedText(text, halign);
    lastWidth = width;
}

void Label::invalidate () {
    lastWidth = -1;
}

float Label::getPrefWidth () {
    switch (wrapType) {
    case singleLine:
        return cache.getFont().getBounds(text).width * scaleX;
    case multiLine:
        return cache.getFont().getMultiLineBounds(text).width * scaleX;
    case wrapped:
    }
    return 0;
}

float Label::getPrefHeight () {
    switch (wrapType) {
    case singleLine:
        return cache.getFont().getBounds(text).height * scaleY;
    case multiLine:
        return cache.getFont().getMultiLineBounds(text).height * scaleY;
    case wrapped:
    }
    return 0;
}

