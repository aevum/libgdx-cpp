
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

#include "Button.hpp"

using namespace gdx_cpp::scenes::scene2d::ui;

void Button::layout () {
    final BitmapFont font = style.font;
    final NinePatch downPatch = style.down;
    bounds.set(font.getMultiLineBounds(text));

    prefHeight = downPatch.getBottomHeight() + downPatch.getTopHeight() + bounds.height + -font.getDescent() * 2;
    prefWidth = downPatch.getLeftWidth() + downPatch.getRightWidth() + bounds.width;
    invalidated = false;
}

void Button::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    final BitmapFont font = style.font;
    final Color fontColor = style.fontColor;
    final NinePatch downPatch = style.down;
    final NinePatch upPatch = style.up;

    if (invalidated) layout();

    batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);
    if (isPressed)
        downPatch.draw(batch, x, y, width, height);
    else
        upPatch.draw(batch, x, y, width, height);

    float textY = (int)(height * 0.5f) + (int)(bounds.height * 0.5f);
    font.setColor(fontColor.r, fontColor.g, fontColor.b, fontColor.a * parentAlpha);
    font.drawMultiLine(batch, text, x + (int)(width * 0.5f), y + textY, 0, HAlignment.CENTER);
}

bool Button::touchDown (float x,float y,int pointer) {
    if (pointer != 0) return false;
    if (hit(x, y) != null) {
        isPressed = true;
        parent.focus(this, pointer);
        return true;
    }
    return false;
}

bool Button::touchUp (float x,float y,int pointer) {
    if (pointer != 0) return false;
    if (hit(x, y) != null) {
        if (listener != null) listener.click(this);
        parent.focus(null, pointer);
        isPressed = false;
        return true;
    }
    isPressed = false;
    parent.focus(null, pointer);
    return false;
}

bool Button::touchDragged (float x,float y,int pointer) {
    if (pointer != 0) return false;
    return isPressed;
}

void Button::setText (const std::string& text) {
    this.text = text;
    invalidateHierarchy();
}

std::string& Button::getText () {
    return text;
}

Button& Button::setClickListener (const ClickListener& listener) {
    this.listener = listener;
    return this;
}

