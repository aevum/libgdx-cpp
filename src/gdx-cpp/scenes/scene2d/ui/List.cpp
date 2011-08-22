
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

#include "List.hpp"

using namespace gdx_cpp::scenes::scene2d::ui;

void List::layout () {
    final BitmapFont font = style.font;
    final NinePatch selectedPatch = style.selectedPatch;
    prefWidth = 0;
    prefHeight = 0;

    for (int i = 0; i < entries.length; i++) {
        String entry = entries[i];
        TextBounds bounds = font.getBounds(entry);
        prefWidth = Math.max(bounds.width, prefWidth);

    }

    entryHeight = font.getLineHeight() - font.getDescent();
    entryHeight += selectedPatch.getTopHeight() + selectedPatch.getBottomHeight();
    prefWidth += selectedPatch.getLeftWidth() + selectedPatch.getRightWidth();
    prefHeight = entries.length * entryHeight;
    textOffsetX = selectedPatch.getLeftWidth();
    textOffsetY = selectedPatch.getTopHeight() - font.getDescent();
    invalidated = false;
}

void List::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    final BitmapFont font = style.font;
    final NinePatch selectedPatch = style.selectedPatch;
    final Color fontColorSelected = style.fontColorSelected;
    final Color fontColorUnselected = style.fontColorUnselected;

    if (invalidated) layout();
    batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);

    float posY = height;
    for (int i = 0; i < entries.length; i++) {
        if (selected == i) {
            selectedPatch.draw(batch, x, y + posY - entryHeight, Math.max(prefWidth, width), entryHeight);
            font.setColor(fontColorSelected.r, fontColorSelected.g, fontColorSelected.b, fontColorSelected.a * parentAlpha);
        } else {
            font.setColor(fontColorUnselected.r, fontColorUnselected.g, fontColorUnselected.b, fontColorUnselected.a
                          * parentAlpha);
        }
        font.draw(batch, entries[i], x + textOffsetX, y + posY - textOffsetY);
        posY -= entryHeight;
    }
}

bool List::touchDown (float x,float y,int pointer) {
    if (pointer != 0) return false;
    if (hit(x, y) != null) {
        selected = (int)((height - y) / entryHeight);
        selected = Math.max(0, selected);
        selected = Math.min(entries.length - 1, selected);
        if (listener != null) listener.selected(this, selected, entries[selected]);
        return true;
    }
    return false;
}

bool List::touchUp (float x,float y,int pointer) {
    return false;
}

bool List::touchDragged (float x,float y,int pointer) {
    return false;
}

gdx_cpp::scenes::scene2d::Actor& List::hit (float x,float y) {
    return x >= 0 && x < Math.max(prefWidth, width) && y >= 0 && y < prefHeight ? this : null;
}

int List::getSelectedIndex () {
    return selected;
}

std::string& List::getSelection () {
    return entries[selected];
}

void List::setEntries () {
    if (entries == null) throw new IllegalArgumentException("entries must not be null");
    this.entries = entries;
    selected = 0;
    invalidateHierarchy();
}

void List::setSelectionListener (const SelectionListener& listener) {
    this.listener = listener;
}

