
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

#include "Widget.hpp"

using namespace gdx_cpp::scenes::scene2d::ui;

float Widget::getMinWidth () {
    return getPrefWidth();
}

float Widget::getMinHeight () {
    return getPrefHeight();
}

float Widget::getMaxWidth () {
    return 0;
}

float Widget::getMaxHeight () {
    return 0;
}

void Widget::invalidate () {
    this.invalidated = true;
}

void Widget::invalidateHierarchy () {
    invalidate();
    Group parent = this.parent;
    while (parent != null) {
        if (parent instanceof Layout) ((Layout)parent).invalidate();
        parent = parent.parent;
    }
}

gdx_cpp::scenes::scene2d::Actor& Widget::hit (float x,float y) {
    return x > 0 && x < width && y > 0 && y < height ? this : null;
}

Widget::Widget () {
    super(null);
}

Widget::Widget (const std::string& name) {
    super(name);
}

