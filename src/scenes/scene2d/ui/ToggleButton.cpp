
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

#include "ToggleButton.hpp"

using namespace gdx_cpp::scenes::scene2d::ui;

void ToggleButton::layout () {
    final BitmapFont font = style.font;
    final NinePatch downPatch = style.down;

    bounds.set(font.getMultiLineBounds(text));
    bounds.height -= font.getDescent();

    prefHeight = downPatch.getBottomHeight() + downPatch.getTopHeight() + bounds.height;
    prefWidth = downPatch.getLeftWidth() + downPatch.getRightWidth() + bounds.width;
    invalidated = false;
}

void ToggleButton::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
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

    float textY = (int)(height / 2) + (int)(bounds.height / 2);
    font.setColor(fontColor.r, fontColor.g, fontColor.b, fontColor.a * parentAlpha);
    font.drawMultiLine(batch, text, x + (int)(width / 2), y + textY, 0, HAlignment.CENTER);
}

bool ToggleButton::touchDown (float x,float y,int pointer) {
    if (pointer != 0) return false;
    if (hit(x, y) != null) {
        isPressed = !isPressed;
        if (listener != null) listener.click(this, isPressed);
        return true;
    }
    return false;
}

bool ToggleButton::touchUp (float x,float y,int pointer) {
    return false;
}

bool ToggleButton::touchDragged (float x,float y,int pointer) {
    return false;
}

gdx_cpp::scenes::scene2d::Actor& ToggleButton::hit (float x,float y) {
    return x > 0 && x < width && y > 0 && y < height ? this : null;
}

void ToggleButton::setText (const std::string& text) {
    this.text = text;
    invalidateHierarchy();
}

std::string& ToggleButton::getText () {
    return text;
}

ToggleButton& ToggleButton::setClickListener (const ClickListener& listener) {
    this.listener = listener;
    return this;
}

bool ToggleButton::isPressed () {
    return isPressed;
}

void ToggleButton::setPressed (bool isPressed) {
    this.isPressed = isPressed;
}

