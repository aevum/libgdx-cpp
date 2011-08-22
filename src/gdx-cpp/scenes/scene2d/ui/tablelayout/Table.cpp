
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

Cell& Table::add (const gdx_cpp::scenes::scene2d::Actor& actor) {
    return layout.add(actor);
}

Cell& Table::row () {
    return layout.row();
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

void Table::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    if (!visible) return;
    if (layout.needsLayout) layout.layout();
    super.draw(batch, parentAlpha);
}

void Table::layout () {
    layout.layout();
}

void Table::invalidate () {
    layout.invalidate();
}

float Table::getPrefWidth () {
    layout.setLayoutSize(0, 0, 0, 0);
    layout.layout();
    return layout.getMinWidth();
}

float Table::getPrefHeight () {
    layout.setLayoutSize(0, 0, 0, 0);
    layout.layout();
    return layout.getMinHeight();
}

void Table::clear () {
    super.clear();
    layout.clear();
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

TableLayout& Table::getTableLayout () {
    return layout;
}

