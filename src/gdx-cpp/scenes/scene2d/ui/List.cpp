
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

void List::setStyle (const ListStyle& style) {
    this.style = style;
    if (items != null) setItems(items);
}

void List::layout () {
}

void List::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    final BitmapFont font = style.font;
    final NinePatch selectedPatch = style.selectedPatch;
    final Color fontColorSelected = style.fontColorSelected;
    final Color fontColorUnselected = style.fontColorUnselected;

    batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);

    float posY = height;
    for (int i = 0; i < items.length; i++) {
        if (selected == i) {
            selectedPatch.draw(batch, x, y + posY - itemHeight, Math.max(prefWidth, width), itemHeight);
            font.setColor(fontColorSelected.r, fontColorSelected.g, fontColorSelected.b, fontColorSelected.a * parentAlpha);
        } else {
            font.setColor(fontColorUnselected.r, fontColorUnselected.g, fontColorUnselected.b, fontColorUnselected.a
                          * parentAlpha);
        }
        font.draw(batch, items[i], x + textOffsetX, y + posY - textOffsetY);
        posY -= itemHeight;
    }
}

bool List::touchDown (float x,float y,int pointer) {
    if (pointer != 0) return false;
    selected = (int)((height - y) / itemHeight);
    selected = Math.max(0, selected);
    selected = Math.min(items.length - 1, selected);
    if (listener != null) listener.selected(this, selected, items[selected]);
    return true;
}

void List::touchUp (float x,float y,int pointer) {
}

void List::touchDragged (float x,float y,int pointer) {
}

gdx_cpp::scenes::scene2d::Actor& List::hit (float x,float y) {
    return x >= 0 && x < width && y >= 0 && y < height ? this : null;
}

void List::selected (const std::list<& list,int selectedIndex,const std::string& selection);
}

/** @return the index of the currently selected item. The top item has an index of 0. */
public int getSelectedIndex () {
    return selected;
}

public void setSelectedIndex (int index) {
    selected = index;
}

/** @return the text of the currently selected item or null if the list is empty */
public String getSelection () {
    if (items.length == 0) return null;
    return items[selected];
}

/** @param index sets the selected item */
public void setSelection (int index) {
    if (index < 0 || index >= items.length) throw new GdxRuntimeException("Index must be > 0 and < #items");
    selected = index;
}

public int setSelection (String item) {
    selected = -1;
    for (int i = 0, n = items.length; i < n; i++) {
        if (items[i].equals(item)) {
            selected = i;
            break;
        }
    }

    int List::getSelectedIndex () {
        return selected;
    }

    void List::setSelectedIndex (int index) {
        selected = index;
    }

    std::string& List::getSelection () {
        if (items.length == 0) return null;
        return items[selected];
    }

    void List::setSelection (int index) {
        if (index < 0 || index >= items.length) throw new GdxRuntimeException("Index must be > 0 and < #items");
        selected = index;
    }

    int List::setSelection (const std::string& item) {
        selected = -1;
        for (int i = 0, n = items.length; i < n; i++) {
            if (items[i].equals(item)) {
                selected = i;
                break;
            }
        }
        return selected;
    }

    void List::setItems () {
        if (items == null) throw new IllegalArgumentException("items cannot be null.");
        this.items = items;
        selected = 0;

        final BitmapFont font = style.font;
        final NinePatch selectedPatch = style.selectedPatch;
        prefWidth = 0;
        prefHeight = 0;

        for (int i = 0; i < items.length; i++) {
            String item = items[i];
            TextBounds bounds = font.getBounds(item);
            prefWidth = Math.max(bounds.width, prefWidth);
        }

        itemHeight = font.getCapHeight() - font.getDescent() * 2;
        itemHeight += selectedPatch.getTopHeight() + selectedPatch.getBottomHeight();
        prefWidth += selectedPatch.getLeftWidth() + selectedPatch.getRightWidth();
        prefHeight = items.length * itemHeight;
        textOffsetX = selectedPatch.getLeftWidth();
        textOffsetY = selectedPatch.getTopHeight() - font.getDescent();
    }

    std::string* List::getItems () {
        return items;
    }

    float List::getPrefWidth () {
        return prefWidth;
    }

    float List::getPrefHeight () {
        return prefHeight;
    }

    void List::setSelectionListener (const SelectionListener& listener) {
        this.listener = listener;
    }

    List::List (const Skin& skin) {
        this(items, skin.getStyle(ListStyle.class), null);
    }

    List::List (const ListStyle& style) {
        this(items, style, null);
    }

    List::List (const ListStyle& style,const std::string& name) {
        super(name);
        setStyle(style);
        setItems(items);
        layout();
    }

