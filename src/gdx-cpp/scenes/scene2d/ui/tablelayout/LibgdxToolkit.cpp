
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

#include "LibgdxToolkit.hpp"

using namespace gdx::ui::tablelayout;

gdx::Actor& LibgdxToolkit::wrap (const Object& object) {
    if (object instanceof String) {
        if (defaultFont == null) throw new IllegalStateException("No default font has been set.");
        return new Label(null, defaultFont, (String)object);
    }
    if (object == null) {
        Group group = new Group();
        group.transform = false;
        return group;
    }
    return super.wrap(object);
}

gdx::Actor& LibgdxToolkit::newWidget (const TableLayout& layout,const std::string& className) {
    if (layout.atlas != null) {
        AtlasRegion region = layout.atlas.findRegion(className);
        if (region != null) return new Image(className, region);
    }
    return super.newWidget(layout, className);
}

TableLayout& LibgdxToolkit::getLayout (const Table& table) {
    return table.getTableLayout();
}

gdx::Actor& LibgdxToolkit::newStack () {
    return new Stack();
}

void LibgdxToolkit::setProperty (const TableLayout& layout,const gdx::Actor& object,const std::string& name,std::list<String>& values) {
    if (object instanceof Label) {
        Label label = ((Label)object);
        String value = values.get(0);
        if (name.equals("font")) {
            label.setFont(getFont(value));
            return;
        }
    }

    super.setProperty(layout, object, name, values);
}

void LibgdxToolkit::addChild (const gdx::Actor& parent,const gdx::Actor& child,const std::string& layoutString) {
    if (child.parent != null) child.remove();
    ((Group)parent).addActor(child);
}

void LibgdxToolkit::removeChild (const gdx::Actor& parent,const gdx::Actor& child) {
    ((Group)parent).removeActor(child);
}

int LibgdxToolkit::getMinWidth (const gdx::Actor& actor) {
    if (actor instanceof Layout) return (int)((Layout)actor).getMinWidth();
    return (int)actor.width;
}

int LibgdxToolkit::getMinHeight (const gdx::Actor& actor) {
    if (actor instanceof Layout) return (int)((Layout)actor).getMinHeight();
    return (int)actor.height;
}

int LibgdxToolkit::getPrefWidth (const gdx::Actor& actor) {
    if (actor instanceof Layout) return (int)((Layout)actor).getPrefWidth();
    return (int)actor.width;
}

int LibgdxToolkit::getPrefHeight (const gdx::Actor& actor) {
    if (actor instanceof Layout) return (int)((Layout)actor).getPrefHeight();
    return (int)actor.height;
}

int LibgdxToolkit::getMaxWidth (const gdx::Actor& actor) {
    if (actor instanceof Layout) return (int)((Layout)actor).getMaxWidth();
    return 0;
}

int LibgdxToolkit::getMaxHeight (const gdx::Actor& actor) {
    if (actor instanceof Layout) return (int)((Layout)actor).getMaxHeight();
    return 0;
}

void LibgdxToolkit::clearDebugRectangles (const TableLayout& layout) {
    if (layout.debugRects != null) layout.debugRects.clear();
}

void LibgdxToolkit::addDebugRectangle (const TableLayout& layout,int type,int x,int y,int w,int h) {
    if (layout.debugRects == null) layout.debugRects = new Array();
    layout.debugRects.add(new DebugRect(type, x, y, w, h));
}

void LibgdxToolkit::registerFont (const std::string& name,const gdx::BitmapFont& font) {
    fonts.put(name, font);
    if (defaultFont == null) defaultFont = font;
}

gdx::BitmapFont& LibgdxToolkit::getFont (const std::string& name) {
    BitmapFont font = fonts.get(name);
    if (font == null) throw new IllegalArgumentException("Font not found: " + name);
    return font;
}

