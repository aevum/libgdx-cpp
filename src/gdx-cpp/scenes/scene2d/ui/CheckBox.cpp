
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

#include "CheckBox.hpp"

using namespace gdx_cpp::scenes::scene2d::ui;

void CheckBox::layout () {
    final BitmapFont font = style.font;
    final TextureRegion checkedRegion = style.checked;
    final TextureRegion uncheckedRegion = style.unchecked;

    textBounds.set(font.getBounds(label));
    textBounds.height -= font.getDescent();
    checkWidth = Math.max(checkedRegion.getRegionWidth(), uncheckedRegion.getRegionWidth());
    checkHeight = Math.max(checkedRegion.getRegionHeight(), uncheckedRegion.getRegionHeight());
    if (textBounds.height > checkHeight) {
        prefHeight = textBounds.height;
        boxPos.y = (int)((textBounds.height - checkedRegion.getRegionHeight()) / 2);
        textPos.y = textBounds.height;
    } else {
        prefHeight = checkHeight;
        boxPos.y = 0;
        textPos.y = (int)((checkHeight - textBounds.height) / 2) + textBounds.height;
    }

    boxPos.x = 0;
    textPos.x = checkWidth + 5;
    prefWidth = checkWidth + 5 + textBounds.width;
    invalidated = false;
}

void CheckBox::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    final BitmapFont font = style.font;
    final TextureRegion checkedRegion = style.checked;
    final TextureRegion uncheckedRegion = style.unchecked;
    final Color fontColor = style.fontColor;

    if (invalidated) layout();

    batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);
    if (isChecked)
        batch.draw(checkedRegion, x + boxPos.x, y + boxPos.y);
    else
        batch.draw(uncheckedRegion, x + boxPos.x, y + boxPos.y);

    font.setColor(fontColor.r, fontColor.g, fontColor.b, fontColor.a * parentAlpha);
    font.draw(batch, label, x + textPos.x, y + textPos.y);
}

bool CheckBox::touchDown (float x,float y,int pointer) {
    return false;
}

bool CheckBox::touchUp (float x,float y,int pointer) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        isChecked = !isChecked;
        if (listener != null) listener.checked(this, isChecked);
    }
    return false;
}

bool CheckBox::touchDragged (float x,float y,int pointer) {
    return false;
}

gdx_cpp::scenes::scene2d::Actor& CheckBox::hit (float x,float y) {
    return x > 0 && x < width && y > 0 && y < height ? this : null;
}

void CheckBox::checked (const CheckBox& checkBox,bool isChecked);
}

/** Sets the {@link CheckedListener}
 * @param listener the listener or null
 * @return this CheckBox for chaining */
public CheckBox setCheckedListener (CheckedListener listener) {
    this.listener = listener;
    return this;
}

/** Defines a check box style, see {@link CheckBox}
 * @author mzechner */
public static class CheckBoxStyle {
    public final BitmapFont font;
    public final Color fontColor;
    public final TextureRegion checked;
    public final TextureRegion unchecked;

    public CheckBoxStyle (BitmapFont font, Color fontColor, TextureRegion checked, TextureRegion unchecked) {
        this.font = font;
        this.fontColor = fontColor;
        this.checked = checked;
        this.unchecked = unchecked;
    }

    CheckBox& CheckBox::setCheckedListener (const CheckedListener& listener) {
        this.listener = listener;
        return this;
    }

    void CheckBox::setChecked (bool isChecked) {
        this.isChecked = isChecked;
        invalidateHierarchy();
    }

    bool CheckBox::isChecked () {
        return isChecked;
    }

