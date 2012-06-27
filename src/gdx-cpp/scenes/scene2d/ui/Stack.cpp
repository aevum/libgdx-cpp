
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

#include "Stack.hpp"

using namespace gdx::ui;

void Stack::layout () {
    if (!needsLayout) return;
    needsLayout = false;
    for (int i = 0, n = children.size(); i < n; i++) {
        Actor actor = children.get(i);
        actor.x = 0;
        actor.y = 0;
        actor.width = width;
        actor.height = height;
        if (actor instanceof Layout) {
            Layout layout = (Layout)actor;
            layout.invalidate();
            layout.layout();
        }
    }
}

void Stack::draw (const gdx::SpriteBatch& batch,float parentAlpha) {
    if (needsLayout) layout();
    super.draw(batch, parentAlpha);
}

void Stack::invalidate () {
    needsLayout = true;
}

float Stack::getPrefWidth () {
    float width = 0;
    for (int i = 0, n = children.size(); i < n; i++)
        width = Math.max(width, LibgdxToolkit.instance.getPrefWidth(children.get(i)));
    return width * scaleX;
}

float Stack::getPrefHeight () {
    float height = 0;
    for (int i = 0, n = children.size(); i < n; i++)
        height = Math.max(height, LibgdxToolkit.instance.getPrefHeight(children.get(i)));
    return height * scaleY;
}

float Stack::getMaxWidth () {
    float width = 0;
    for (int i = 0, n = children.size(); i < n; i++)
        width = Math.max(width, LibgdxToolkit.instance.getMaxWidth(children.get(i)));
    return width * scaleX;
}

float Stack::getMaxHeight () {
    float height = 0;
    for (int i = 0, n = children.size(); i < n; i++)
        height = Math.max(height, LibgdxToolkit.instance.getMaxHeight(children.get(i)));
    return height * scaleY;
}

float Stack::getMinWidth () {
    float width = 0;
    for (int i = 0, n = children.size(); i < n; i++)
        width = Math.max(width, LibgdxToolkit.instance.getMinWidth(children.get(i)));
    return width * scaleX;
}

float Stack::getMinHeight () {
    float height = 0;
    for (int i = 0, n = children.size(); i < n; i++)
        height = Math.max(height, LibgdxToolkit.instance.getMinHeight(children.get(i)));
    return height * scaleY;
}

Stack::Stack () {
    this(null);
}

Stack::Stack (const std::string& name) {
    super(name);
    transform = false;
}

