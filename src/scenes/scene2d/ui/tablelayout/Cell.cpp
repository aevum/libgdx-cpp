
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

#include "Cell<C>.hpp"

using namespace gdx_cpp::scenes::scene2d::ui::tablelayout;

Cell& Cell<C>::setWidget (const C& widget) {
    layout.toolkit.setWidget(layout, this, widget);
    return this;
}

std::string& Cell<C>::getName () {
    return name;
}

C& Cell<C>::getWidget () {
    return widget;
}

Cell& Cell<C>::minSize (const std::string& size) {
    minWidth = size;
    minHeight = size;
    return this;
}

Cell& Cell<C>::minWidth (const std::string& minWidth) {
    this.minWidth = minWidth;
    return this;
}

Cell& Cell<C>::minHeight (const std::string& minHeight) {
    this.minHeight = minHeight;
    return this;
}

Cell& Cell<C>::minSize (int size) {
    minWidth = String.valueOf(size);
    minHeight = String.valueOf(size);
    return this;
}

Cell& Cell<C>::minWidth (int minWidth) {
    this.minWidth = String.valueOf(minWidth);
    return this;
}

Cell& Cell<C>::minHeight (int minHeight) {
    this.minHeight = String.valueOf(minHeight);
    return this;
}

Cell& Cell<C>::prefSize (const std::string& size) {
    prefWidth = size;
    prefHeight = size;
    return this;
}

Cell& Cell<C>::prefWidth (const std::string& prefWidth) {
    this.prefWidth = prefWidth;
    return this;
}

Cell& Cell<C>::prefHeight (const std::string& prefHeight) {
    this.prefHeight = prefHeight;
    return this;
}

Cell& Cell<C>::prefSize (int size) {
    prefWidth = String.valueOf(size);
    prefHeight = String.valueOf(size);
    return this;
}

Cell& Cell<C>::prefWidth (int prefWidth) {
    this.prefWidth = String.valueOf(prefWidth);
    return this;
}

Cell& Cell<C>::prefHeight (int prefHeight) {
    this.prefHeight = String.valueOf(prefHeight);
    return this;
}

Cell& Cell<C>::maxSize (const std::string& size) {
    maxWidth = size;
    maxHeight = size;
    return this;
}

Cell& Cell<C>::maxWidth (const std::string& maxWidth) {
    this.maxWidth = maxWidth;
    return this;
}

Cell& Cell<C>::maxHeight (const std::string& maxHeight) {
    this.maxHeight = maxHeight;
    return this;
}

Cell& Cell<C>::maxSize (int size) {
    maxWidth = String.valueOf(size);
    maxHeight = String.valueOf(size);
    return this;
}

Cell& Cell<C>::maxWidth (int maxWidth) {
    this.maxWidth = String.valueOf(maxWidth);
    return this;
}

Cell& Cell<C>::maxHeight (int maxHeight) {
    this.maxHeight = String.valueOf(maxHeight);
    return this;
}

Cell& Cell<C>::space (const std::string& space) {
    spaceTop = space;
    spaceLeft = space;
    spaceBottom = space;
    spaceRight = space;
    return this;
}

Cell& Cell<C>::space (const std::string& top,const std::string& left,const std::string& bottom,const std::string& right) {
    spaceTop = top;
    spaceLeft = left;
    spaceBottom = bottom;
    spaceRight = right;
    return this;
}

Cell& Cell<C>::spaceTop (const std::string& spaceTop) {
    this.spaceTop = spaceTop;
    return this;
}

Cell& Cell<C>::spaceLeft (const std::string& spaceLeft) {
    this.spaceLeft = spaceLeft;
    return this;
}

Cell& Cell<C>::spaceBottom (const std::string& spaceBottom) {
    this.spaceBottom = spaceBottom;
    return this;
}

Cell& Cell<C>::spaceRight (const std::string& spaceRight) {
    this.spaceRight = spaceRight;
    return this;
}

Cell& Cell<C>::space (int space) {
    String value = String.valueOf(space);
    spaceTop = value;
    spaceLeft = value;
    spaceBottom = value;
    spaceRight = value;
    return this;
}

Cell& Cell<C>::space (int top,int left,int bottom,int right) {
    spaceTop = String.valueOf(top);
    spaceLeft = String.valueOf(left);
    spaceBottom = String.valueOf(bottom);
    spaceRight = String.valueOf(right);
    return this;
}

Cell& Cell<C>::spaceTop (int spaceTop) {
    this.spaceTop = String.valueOf(spaceTop);
    return this;
}

Cell& Cell<C>::spaceLeft (int spaceLeft) {
    this.spaceLeft = String.valueOf(spaceLeft);
    return this;
}

Cell& Cell<C>::spaceBottom (int spaceBottom) {
    this.spaceBottom = String.valueOf(spaceBottom);
    return this;
}

Cell& Cell<C>::spaceRight (int spaceRight) {
    this.spaceRight = String.valueOf(spaceRight);
    return this;
}

Cell& Cell<C>::pad (const std::string& pad) {
    padTop = pad;
    padLeft = pad;
    padBottom = pad;
    padRight = pad;
    return this;
}

Cell& Cell<C>::pad (const std::string& top,const std::string& left,const std::string& bottom,const std::string& right) {
    padTop = top;
    padLeft = left;
    padBottom = bottom;
    padRight = right;
    return this;
}

Cell& Cell<C>::padTop (const std::string& padTop) {
    this.padTop = padTop;
    return this;
}

Cell& Cell<C>::padLeft (const std::string& padLeft) {
    this.padLeft = padLeft;
    return this;
}

Cell& Cell<C>::padBottom (const std::string& padBottom) {
    this.padBottom = padBottom;
    return this;
}

Cell& Cell<C>::padRight (const std::string& padRight) {
    this.padRight = padRight;
    return this;
}

Cell& Cell<C>::pad (int pad) {
    String value = String.valueOf(pad);
    padTop = value;
    padLeft = value;
    padBottom = value;
    padRight = value;
    return this;
}

Cell& Cell<C>::pad (int top,int left,int bottom,int right) {
    padTop = String.valueOf(top);
    padLeft = String.valueOf(left);
    padBottom = String.valueOf(bottom);
    padRight = String.valueOf(right);
    return this;
}

Cell& Cell<C>::padTop (int padTop) {
    this.padTop = String.valueOf(padTop);
    return this;
}

Cell& Cell<C>::padLeft (int padLeft) {
    this.padLeft = String.valueOf(padLeft);
    return this;
}

Cell& Cell<C>::padBottom (int padBottom) {
    this.padBottom = String.valueOf(padBottom);
    return this;
}

Cell& Cell<C>::padRight (int padRight) {
    this.padRight = String.valueOf(padRight);
    return this;
}

Cell& Cell<C>::fill () {
    fillX = 1f;
    fillY = 1f;
    return this;
}

Cell& Cell<C>::fillX () {
    fillX = 1f;
    return this;
}

Cell& Cell<C>::fillY () {
    fillY = 1f;
    return this;
}

Cell& Cell<C>::fill (float x,float y) {
    fillX = x;
    fillY = y;
    return this;
}

Cell& Cell<C>::fill (bool x,bool y) {
    fillX = x ? 1f : 0;
    fillY = y ? 1f : 0;
    return this;
}

Cell& Cell<C>::align (int align) {
    this.align = align;
    return this;
}

Cell& Cell<C>::align (const std::string& value) {
    align = 0;
    if (value.contains("center")) align |= CENTER;
    if (value.contains("left")) align |= LEFT;
    if (value.contains("right")) align |= RIGHT;
    if (value.contains("top")) align |= TOP;
    if (value.contains("bottom")) align |= BOTTOM;
    return this;
}

Cell& Cell<C>::center () {
    if (align == null)
        align = CENTER;
    else
        align |= CENTER;
    return this;
}

Cell& Cell<C>::top () {
    if (align == null)
        align = TOP;
    else {
        align |= TOP;
        align &= ~BOTTOM;
    }
    return this;
}

Cell& Cell<C>::left () {
    if (align == null)
        align = LEFT;
    else {
        align |= LEFT;
        align &= ~RIGHT;
    }
    return this;
}

Cell& Cell<C>::bottom () {
    if (align == null)
        align = BOTTOM;
    else {
        align |= BOTTOM;
        align &= ~TOP;
    }
    return this;
}

Cell& Cell<C>::right () {
    if (align == null)
        align = RIGHT;
    else {
        align |= RIGHT;
        align &= ~LEFT;
    }
    return this;
}

Cell& Cell<C>::expand () {
    expandX = 1;
    expandY = 1;
    return this;
}

Cell& Cell<C>::expandX () {
    expandX = 1;
    return this;
}

Cell& Cell<C>::expandY () {
    expandY = 1;
    return this;
}

Cell& Cell<C>::expand (int x,int y) {
    expandX = x;
    expandY = y;
    return this;
}

Cell& Cell<C>::expand (bool x,bool y) {
    expandX = x ? 1 : 0;
    expandY = y ? 1 : 0;
    return this;
}

Cell& Cell<C>::ignore (bool ignore) {
    this.ignore = ignore;
    return this;
}

Cell& Cell<C>::ignore () {
    this.ignore = true;
    return this;
}

bool Cell<C>::getIgnore () {
    return ignore != null && ignore == true;
}

Cell& Cell<C>::colspan (int colspan) {
    this.colspan = colspan;
    return this;
}

Cell& Cell<C>::uniform () {
    uniformX = true;
    uniformY = true;
    return this;
}

Cell& Cell<C>::uniformX () {
    uniformX = true;
    return this;
}

Cell& Cell<C>::uniformY () {
    uniformY = true;
    return this;
}

Cell& Cell<C>::uniform (bool x,bool y) {
    uniformX = x;
    uniformY = y;
    return this;
}

int Cell<C>::getWidgetX () {
    return widgetX;
}

int Cell<C>::getWidgetY () {
    return widgetY;
}

int Cell<C>::getWidgetWidth () {
    return widgetWidth;
}

int Cell<C>::getWidgetHeight () {
    return widgetHeight;
}

int Cell<C>::getColumn () {
    return column;
}

int Cell<C>::getRow () {
    return row;
}

std::string& Cell<C>::getMinWidth () {
    return minWidth;
}

std::string& Cell<C>::getMinHeight () {
    return minHeight;
}

std::string& Cell<C>::getPrefWidth () {
    return prefWidth;
}

std::string& Cell<C>::getPrefHeight () {
    return prefHeight;
}

std::string& Cell<C>::getMaxWidth () {
    return maxWidth;
}

std::string& Cell<C>::getMaxHeight () {
    return maxHeight;
}

std::string& Cell<C>::getSpaceTop () {
    return spaceTop;
}

std::string& Cell<C>::getSpaceLeft () {
    return spaceLeft;
}

std::string& Cell<C>::getSpaceBottom () {
    return spaceBottom;
}

std::string& Cell<C>::getSpaceRight () {
    return spaceRight;
}

std::string& Cell<C>::getPadTop () {
    return padTop;
}

std::string& Cell<C>::getPadLeft () {
    return padLeft;
}

std::string& Cell<C>::getPadBottom () {
    return padBottom;
}

std::string& Cell<C>::getPadRight () {
    return padRight;
}

float Cell<C>::getFillX () {
    return fillX;
}

float Cell<C>::getFillY () {
    return fillY;
}

int Cell<C>::getAlign () {
    return align;
}

int Cell<C>::getExpandX () {
    return expandX;
}

int Cell<C>::getExpandY () {
    return expandY;
}

int Cell<C>::getColspan () {
    return colspan;
}

bool Cell<C>::getUniformX () {
    return uniformX;
}

bool Cell<C>::getUniformY () {
    return uniformY;
}

bool Cell<C>::isEndRow () {
    return endRow;
}

