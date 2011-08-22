
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

#include "TableLayout.hpp"

using namespace gdx_cpp::scenes::scene2d::ui::tablelayout;

void TableLayout::parse (const gdx_cpp::files::FileHandle& file) {
    super.parse(file.readString());
}

gdx_cpp::scenes::scene2d::Actor& TableLayout::register (const gdx_cpp::scenes::scene2d::Actor& actor) {
    if (actor.name == null) throw new IllegalArgumentException("Actor must have a name: " + actor.getClass());
    return register(actor.name, actor);
}

gdx_cpp::scenes::scene2d::Actor& TableLayout::registerImage (const std::string& name) {
    return register(new Image(name, atlas.findRegion(name)));
}

gdx_cpp::scenes::scene2d::Actor& TableLayout::getWidget (const std::string& name) {
    Actor actor = super.getWidget(name);
    if (actor == null) actor = getTable().findActor(name);
    return actor;
}

void TableLayout::layout () {
    if (!needsLayout) return;
    needsLayout = false;

    setLayoutSize(0, 0, (int)table.width, (int)table.height);
    Table table = getTable();

    super.layout();

    List<Cell> cells = getCells();
    for (int i = 0, n = cells.size(); i < n; i++) {
        Cell c = cells.get(i);
        if (c.getIgnore()) continue;
        Actor actor = (Actor)c.getWidget();
        actor.x = c.getWidgetX();
        int widgetHeight = c.getWidgetHeight();
        actor.y = table.height - c.getWidgetY() - widgetHeight;
        actor.width = c.getWidgetWidth();
        actor.height = widgetHeight;
        if (actor instanceof Layout) {
            Layout layout = (Layout)actor;
            layout.invalidate();
            layout.layout();
        }
    }
}

void TableLayout::invalidate () {
    needsLayout = true;
}

void TableLayout::invalidateHierarchy () {
    invalidate();
    Actor parent = getTable().parent;
    while (parent != null) {
        if (parent instanceof Layout) ((Layout)parent).invalidate();
        parent = parent.parent;
    }
}

void TableLayout::drawDebug (const gdx_cpp::graphics::g2d::SpriteBatch& batch) {
    if (getDebug() == DEBUG_NONE || debugRects == null) return;
    if (debugRenderer == null) {
        if (Gdx.graphics.isGL20Available())
            debugRenderer = new ImmediateModeRenderer20(64, false, true, 0);
        else
            debugRenderer = new ImmediateModeRenderer10(64);
    }

    Table table = getTable();
    Actor parent = table.parent;
    float x = 0, y = 0;
    while (parent != null) {
        if (parent instanceof Group) {
            x += parent.x;
            y += parent.y;
        }
        parent = parent.parent;
    }
    y = table.y + table.height - y;

    int viewHeight = Gdx.graphics.getHeight();

    debugRenderer.begin(batch.getProjectionMatrix(), GL10.GL_LINES);
    for (int i = 0, n = debugRects.size; i < n; i++) {
        DebugRect rect = debugRects.get(i);
        float x1 = x + rect.x;
        float y1 = y - rect.y - rect.height;
        float x2 = x1 + rect.width;
        float y2 = y1 + rect.height;
        float r = (rect.type & DEBUG_CELL) != 0 ? 1 : 0;
        float g = (rect.type & DEBUG_WIDGET) != 0 ? 1 : 0;
        float b = (rect.type & DEBUG_TABLE) != 0 ? 1 : 0;

        debugRenderer.color(r, g, b, 1);
        debugRenderer.vertex(x1, y1, 0);
        debugRenderer.color(r, g, b, 1);
        debugRenderer.vertex(x1, y2, 0);

        debugRenderer.color(r, g, b, 1);
        debugRenderer.vertex(x1, y2, 0);
        debugRenderer.color(r, g, b, 1);
        debugRenderer.vertex(x2, y2, 0);

        debugRenderer.color(r, g, b, 1);
        debugRenderer.vertex(x2, y2, 0);
        debugRenderer.color(r, g, b, 1);
        debugRenderer.vertex(x2, y1, 0);

        debugRenderer.color(r, g, b, 1);
        debugRenderer.vertex(x2, y1, 0);
        debugRenderer.color(r, g, b, 1);
        debugRenderer.vertex(x1, y1, 0);

        if (debugRenderer.getNumVertices() == 64) {
            debugRenderer.end();
            debugRenderer.begin(batch.getProjectionMatrix(), GL10.GL_LINES);
        }
    }
    debugRenderer.end();
}

