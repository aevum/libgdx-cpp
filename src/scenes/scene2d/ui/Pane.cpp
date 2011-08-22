
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

#include "Pane.hpp"

using namespace gdx_cpp::scenes::scene2d::ui;

void Pane::calculateScissors (const gdx_cpp::math::Matrix4& transform) {
    final NinePatch background = style.background;

    widgetBounds.x = background.getLeftWidth();
    widgetBounds.y = background.getBottomHeight();
    widgetBounds.width = width - background.getLeftWidth() - background.getRightWidth();
    widgetBounds.height = height - background.getTopHeight() - background.getBottomHeight();
    ScissorStack.calculateScissors(stage.getCamera(), transform, widgetBounds, scissors);
}

void Pane::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    final NinePatch background = style.background;

    batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);
    background.draw(batch, x, y, width, height);
    setupTransform(batch);
    layout();
    calculateScissors(batch.getTransformMatrix());
    ScissorStack.pushScissors(scissors);
    super.drawChildren(batch, parentAlpha);
    resetTransform(batch);
    ScissorStack.popScissors();
}

