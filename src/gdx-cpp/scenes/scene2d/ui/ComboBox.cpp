
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

#include "ComboBox.hpp"

using namespace gdx::ui;

void ComboBox::setStyle (const ComboBoxStyle& style) {
    this.style = style;
    if (items != null) setItems(items);
}

void ComboBox::setItems () {
    if (items == null) throw new IllegalArgumentException("items cannot be null.");
    this.items = items;

    NinePatch background = style.background;
    BitmapFont font = style.font;

    prefHeight = Math.max(background.getTopHeight() + background.getBottomHeight() + font.getCapHeight() - font.getDescent()
                          * 2, background.getTotalHeight());

    float max = 0;
    for (int i = 0; i < items.length; i++)
        max = Math.max(font.getBounds(items[i]).width, max);
    prefWidth = background.getLeftWidth() + background.getRightWidth() + max;

    width = prefWidth;
    height = prefHeight;
}

void ComboBox::layout () {
}

void ComboBox::draw (const gdx::SpriteBatch& batch,float parentAlpha) {
    final NinePatch background = style.background;
    final BitmapFont font = style.font;
    final Color fontColor = style.fontColor;

    batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);
    background.draw(batch, x, y, width, height);
    if (items.length > 0) {
        float availableWidth = width - background.getLeftWidth() - background.getRightWidth();
        int numGlyphs = font.computeVisibleGlyphs(items[selection], 0, items[selection].length(), availableWidth);
        bounds.set(font.getBounds(items[selection]));
        float textY = (int)(height / 2) + (int)(bounds.height / 2);
        font.setColor(fontColor.r, fontColor.g, fontColor.b, fontColor.a * parentAlpha);
        font.draw(batch, items[selection], x + background.getLeftWidth(), y + textY, 0, numGlyphs);
    }

    // calculate screen coords where list should be displayed
    ScissorStack.toWindowCoordinates(stage.getCamera(), batch.getTransformMatrix(), screenCoords.set(x, y));
}

bool ComboBox::touchDown (float x,float y,int pointer) {
    if (pointer != 0) return false;
    if (list != null) stage.removeActor(list);
    stage.toStageCoordinates((int)screenCoords.x, (int)screenCoords.y, stageCoords);
    list = new ComboList(this.name + "-list", stageCoords.x, stageCoords.y);
    stage.addActor(list);
    return true;
}

void ComboBox::touchUp (float x,float y,int pointer) {
    stage.getRoot().focus(list, pointer);
}

void ComboBox::touchDragged (float x,float y,int pointer) {
}

void ComboBox::selected (const ComboBox& comboBox,int selectionIndex,const std::string& selection);
}

/** Sets the {@link SelectionListener}.
 * @param listener the listener or null */
public void setSelectionListener (SelectionListener listener) {
    this.listener = listener;
}

protected class ComboList extends Actor {
    Vector2 oldScreenCoords = new Vector2();
    float itemHeight = 0;
    float textOffsetX = 0;
    float textOffsetY = 0;
    int selected = ComboBox.this.selection;

    public ComboList (String name, float x, float y) {
        super(name);
        this.x = x;
        this.y = y;
        this.width = ComboBox.this.width;
        this.height = 100;
        this.oldScreenCoords.set(screenCoords);
        stage.getRoot().focus(this, 0);
        layout();
    }

    void ComboBox::setSelectionListener (const SelectionListener& listener) {
        this.listener = listener;
    }

    void ComboBox::layout () {
        final BitmapFont font = style.font;
        final NinePatch listSelection = style.listSelection;

        float prefWidth = 0;
        float prefHeight = 0;

        for (int i = 0; i < items.length; i++) {
            String item = items[i];
            TextBounds bounds = font.getBounds(item);
            prefWidth = Math.max(bounds.width, prefWidth);

        }

        itemHeight = font.getCapHeight() + -font.getDescent() * 2;
        itemHeight += listSelection.getTopHeight() + listSelection.getBottomHeight();
        itemHeight *= ComboBox.this.parent.scaleY;
        prefWidth += listSelection.getLeftWidth() + listSelection.getRightWidth();
        prefHeight = items.length * itemHeight;
        textOffsetX = listSelection.getLeftWidth();
        textOffsetY = listSelection.getTopHeight() + -font.getDescent();

        width = Math.max(prefWidth, ComboBox.this.width);
        width *= ComboBox.this.parent.scaleX;
        height = prefHeight;
        y -= height;
    }

    void ComboBox::draw (const gdx::SpriteBatch& batch,float parentAlpha) {
        final NinePatch listBackground = style.listBackground;
        final NinePatch listSelection = style.listSelection;
        final BitmapFont font = style.font;
        final Color fontColor = style.fontColor;

        batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);
        listBackground.draw(batch, x, y, width, height);
        float posY = height;
        for (int i = 0; i < items.length; i++) {
            if (selected == i) {
                listSelection.draw(batch, x, y + posY - itemHeight, width, itemHeight);
            }
            font.setColor(fontColor.r, fontColor.g, fontColor.b, fontColor.a * parentAlpha);
            font.setScale(ComboBox.this.parent.scaleX, ComboBox.this.parent.scaleY);
            font.draw(batch, items[i], x + textOffsetX, y + posY - textOffsetY);
            font.setScale(1, 1);
            posY -= itemHeight;
        }
    }

    bool ComboBox::touchDown (float x,float y,int pointer) {
        if (pointer != 0 || hit(x, y) == null) return false;
        selected = (int)((height - y) / itemHeight);
        selected = Math.max(0, selected);
        selected = Math.min(items.length - 1, selected);
        selection = selected;
        if (items.length > 0 && listener != null) listener.selected(ComboBox.this, selected, items[selected]);
        return true;
    }

    void ComboBox::touchUp (float x,float y,int pointer) {
        stage.removeActor(this);
    }

    void ComboBox::touchDragged (float x,float y,int pointer) {
    }

    bool ComboBox::touchMoved (float x,float y) {
        if (hit(x, y) != null) {
            selected = (int)((height - y) / itemHeight);
            selected = Math.max(0, selected);
            selected = Math.min(items.length - 1, selected);
        }
        return true;
    }

    gdx::Actor& ComboBox::hit (float x,float y) {
        return x > 0 && x < width && y > 0 && y < height ? this : null;
    }

    void ComboBox::act (float delta) {
        if (screenCoords.x != oldScreenCoords.x || screenCoords.y != oldScreenCoords.y) {
            stage.removeActor(this);
        }
    }

    void ComboBox::setSelection (int selection) {
        this.selection = selection;
    }

    int ComboBox::getSelectionIndex () {
        return selection;
    }

    std::string& ComboBox::getSelection () {
        return items[selection];
    }

    float ComboBox::getPrefWidth () {
        return prefWidth;
    }

    float ComboBox::getPrefHeight () {
        return prefHeight;
    }

    ComboBox::ComboBox (const gdx::Stage& stage,const Skin& skin) {
        this(items, stage, skin.getStyle(ComboBoxStyle.class), null);
    }

    ComboBox::ComboBox (const gdx::Stage& stage,const ComboBoxStyle& style) {
        this(items, stage, style, null);
    }

    ComboBox::ComboBox (const gdx::Stage& stage,const ComboBoxStyle& style,const std::string& name) {
        super(name);
        setStyle(style);
        setItems(items);
        this.stage = stage;
        layout();
    }

