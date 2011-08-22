
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

using namespace gdx_cpp::scenes::scene2d::ui;

void Label::layout () {
    final BitmapFont font = style.font;

    bounds.set(font.getMultiLineBounds(label));
    bounds.height -= font.getDescent();
    prefWidth = bounds.width;
    prefHeight = bounds.height;
    textPos.x = 0;
    textPos.y = prefHeight;
    invalidated = false;
}

void Label::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    final BitmapFont font = style.font;
    final Color fontColor = style.fontColor;

    if (invalidated) layout();
    font.setColor(fontColor.r, fontColor.g, fontColor.b, fontColor.a * parentAlpha);
    font.drawMultiLine(batch, label, x + textPos.x, y + height);
}

bool Label::touchDown (float x,float y,int pointer) {
    return false;
}

bool Label::touchUp (float x,float y,int pointer) {
    return false;
}

bool Label::touchDragged (float x,float y,int pointer) {
    return false;
}

gdx_cpp::scenes::scene2d::Actor& Label::hit (float x,float y) {
    return null;
}

void Label::setText (const std::string& text) {
    this.label = text;
    layout();
    invalidateHierarchy();
}

