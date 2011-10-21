
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

#include "Table.hpp"

using namespace gdx_cpp::scenes::scene2d::ui::tablelayout;

void Table::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    if (!visible) return;
    if (layout.needsLayout) layout.layout();

    batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);
    if (backgroundPatch != null) backgroundPatch.draw(batch, x, y, width, height);

    if (stage != null) {
        applyTransform(batch);
        calculateScissors(batch.getTransformMatrix());
        ScissorStack.pushScissors(scissors);
        super.drawChildren(batch, parentAlpha);
        resetTransform(batch);
        ScissorStack.popScissors();
    } else
        super.draw(batch, parentAlpha);
}

void Table::calculateScissors (const gdx_cpp::math::Matrix4& transform) {
    tableBounds.x = 0;
    tableBounds.y = 0;
    tableBounds.width = width;
    tableBounds.height = height;
    if (backgroundPatch != null) {
        tableBounds.x += backgroundPatch.getLeftWidth();
        tableBounds.y += backgroundPatch.getBottomHeight();
        tableBounds.width -= backgroundPatch.getLeftWidth() + backgroundPatch.getRightWidth();
        tableBounds.height -= backgroundPatch.getTopHeight() + backgroundPatch.getBottomHeight();
    }
    ScissorStack.calculateScissors(stage.getCamera(), transform, tableBounds, scissors);
}

void Table::computeSize () {
    if (!sizeInvalid) return;
    layout.setLayoutSize(0, 0, 0, 0);
    layout.invalidate();
    layout.layout();
    layout.invalidate();
    sizeInvalid = false;
}

float Table::getPrefWidth () {
    if (sizeInvalid) computeSize();
    return layout.getPrefWidth();
}

float Table::getPrefHeight () {
    if (sizeInvalid) computeSize();
    return layout.getPrefHeight();
}

float Table::getMinWidth () {
    if (sizeInvalid) computeSize();
    return layout.getMinWidth();
}

float Table::getMinHeight () {
    if (sizeInvalid) computeSize();
    return layout.getMinHeight();
}

float Table::getMaxWidth () {
    return 0;
}

float Table::getMaxHeight () {
    return 0;
}

void Table::setBackground (const gdx_cpp::graphics::g2d::NinePatch& background) {
    this.backgroundPatch = background;
    if (background != null) {
        padBottom((int)background.getBottomHeight() + 1);
        padTop((int)background.getTopHeight() + 1);
        padLeft((int)background.getLeftWidth() + 1);
        padRight((int)background.getRightWidth() + 1);
    }
}

void Table::enableClipping (const gdx_cpp::scenes::scene2d::Stage& stage) {
    this.stage = stage;
    transform = true;
    invalidate();
}

void Table::setClickListener (const gdx_cpp::scenes::scene2d::ui::ClickListener& listener) {
    this.listener = listener;
}

bool Table::touchDown (float x,float y,int pointer) {
    if (super.touchDown(x, y, pointer)) return true;
    if (pointer != 0) return false;
    if (listener == null) return false;
    isPressed = true;
    return true;
}

void Table::touchUp (float x,float y,int pointer) {
    if (hit(x, y) != null) click();
    isPressed = false;
}

void Table::click () {
    if (listener != null) listener.click(this);
}

gdx_cpp::scenes::scene2d::Actor& Table::hit (float x,float y) {
    Actor child = super.hit(x, y);
    if (child != null) return child;
    return x > 0 && x < width && y > 0 && y < height ? this : null;
}

TableLayout& Table::getTableLayout () {
    return layout;
}

void Table::clear () {
    super.clear();
    layout.clear();
}

gdx_cpp::scenes::scene2d::Actor& Table::register (const std::string& name,const gdx_cpp::scenes::scene2d::Actor& widget) {
    return layout.register(name, widget);
}

Cell& Table::add (const gdx_cpp::scenes::scene2d::Actor& actor) {
    return layout.add(actor);
}

Cell& Table::stack () {
    return layout.stack(actor);
}

Cell& Table::row () {
    return layout.row();
}

void Table::parse (const gdx_cpp::files::FileHandle& tableDescriptionFile) {
    layout.parse(tableDescriptionFile.readString());
}

void Table::parse (const std::string& tableDescription) {
    layout.parse(tableDescription);
}

Cell& Table::columnDefaults (int column) {
    return layout.columnDefaults(column);
}

Cell& Table::defaults () {
    return layout.defaults();
}

void Table::layout () {
    layout.layout();
}

void Table::invalidate () {
    layout.invalidate();
}

void Table::invalidateHierarchy () {
    layout.invalidateHierarchy();
}

void Table::reset () {
    layout.reset();
}

gdx_cpp::scenes::scene2d::Actor& Table::getWidget (const std::string& name) {
    return layout.getWidget(name);
}

std::list<Actor>& Table::getWidgets () {
    return layout.getWidgets();
}

std::list<Actor>& Table::getWidgets (const std::string& namePrefix) {
    return layout.getWidgets(namePrefix);
}

Cell& Table::getCell (const gdx_cpp::scenes::scene2d::Actor& actor) {
    return layout.getCell(actor);
}

Cell& Table::getCell (const std::string& name) {
    return layout.getCell(name);
}

std::list<Cell>& Table::getAllCells () {
    return layout.getAllCells();
}

std::list<Cell>& Table::getAllCells (const std::string& namePrefix) {
    return layout.getAllCells(namePrefix);
}

std::list<Cell>& Table::getCells () {
    return layout.getCells();
}

void Table::setActor (const std::string& name,const gdx_cpp::scenes::scene2d::Actor& actor) {
    layout.setWidget(name, actor);
}

Table& Table::size (const std::string& width,const std::string& height) {
    layout.size(width, height);
    return this;
}

Table& Table::width (const std::string& width) {
    layout.width(width);
    return this;
}

Table& Table::height (const std::string& height) {
    layout.height(height);
    return this;
}

Table& Table::size (int width,int height) {
    layout.size(width, height);
    return this;
}

Table& Table::width (int width) {
    layout.width(width);
    return this;
}

Table& Table::height (int height) {
    layout.height(height);
    return this;
}

Table& Table::pad (const std::string& pad) {
    layout.pad(pad);
    return this;
}

Table& Table::pad (const std::string& top,const std::string& left,const std::string& bottom,const std::string& right) {
    layout.pad(top, left, bottom, right);
    return this;
}

Table& Table::padTop (const std::string& padTop) {
    layout.padTop(padTop);
    return this;
}

Table& Table::padLeft (const std::string& padLeft) {
    layout.padLeft(padLeft);
    return this;
}

Table& Table::padBottom (const std::string& padBottom) {
    layout.padBottom(padBottom);
    return this;
}

Table& Table::padRight (const std::string& padRight) {
    layout.padRight(padRight);
    return this;
}

Table& Table::pad (int pad) {
    layout.pad(pad);
    return this;
}

Table& Table::pad (int top,int left,int bottom,int right) {
    layout.pad(top, left, bottom, right);
    return this;
}

Table& Table::padTop (int padTop) {
    layout.padTop(padTop);
    return this;
}

Table& Table::padLeft (int padLeft) {
    layout.padLeft(padLeft);
    return this;
}

Table& Table::padBottom (int padBottom) {
    layout.padBottom(padBottom);
    return this;
}

Table& Table::padRight (int padRight) {
    layout.padRight(padRight);
    return this;
}

Table& Table::align (int align) {
    layout.align(align);
    return this;
}

Table& Table::align (const std::string& value) {
    layout.align(value);
    return this;
}

Table& Table::center () {
    layout.center();
    return this;
}

Table& Table::top () {
    layout.top();
    return this;
}

Table& Table::left () {
    layout.left();
    return this;
}

Table& Table::bottom () {
    layout.bottom();
    return this;
}

Table& Table::right () {
    layout.right();
    return this;
}

Table& Table::debug () {
    layout.debug();
    return this;
}

Table& Table::debug (int debug) {
    layout.debug(debug);
    return this;
}

Table& Table::debug (const std::string& value) {
    layout.debug(value);
    return this;
}

int Table::getDebug () {
    return layout.getDebug();
}

std::string& Table::getHeight () {
    return layout.getHeight();
}

std::string& Table::getPadTop () {
    return layout.getPadTop();
}

std::string& Table::getPadLeft () {
    return layout.getPadLeft();
}

std::string& Table::getPadBottom () {
    return layout.getPadBottom();
}

std::string& Table::getPadRight () {
    return layout.getPadRight();
}

int Table::getAlign () {
    return layout.getAlign();
}

void Table::drawDebug (const gdx_cpp::scenes::scene2d::Stage& stage) {
    drawDebug(stage.getActors(), stage.getSpriteBatch());
}

void Table::drawDebug (std::list<Actor>& actors,const gdx_cpp::graphics::g2d::SpriteBatch& batch) {
    for (int i = 0, n = actors.size(); i < n; i++) {
        Actor actor = actors.get(i);
        if (actor instanceof Table) ((Table)actor).layout.drawDebug(batch);
        if (actor instanceof Group) drawDebug(((Group)actor).getActors(), batch);
    }
}

Table::Table () {
    this(new TableLayout(), null);
}

Table::Table (const TableLayout& layout) {
    this(layout, null);
}

Table::Table (const std::string& name) {
    this(new TableLayout(), name);
}

Table::Table (const TableLayout& layout,const std::string& name) {
    super(name);
    transform = false;
    this.layout = layout;
    layout.setTable(this);
}

