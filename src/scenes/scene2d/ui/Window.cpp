
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

#include "Window.hpp"

using namespace gdx_cpp::scenes::scene2d::ui;

void Window::calculateBoundsAndScissors (const gdx_cpp::math::Matrix4& transform) {
    final NinePatch background = style.background;
    final BitmapFont titleFont = style.titleFont;

    widgetBounds.x = background.getLeftWidth();
    widgetBounds.y = background.getBottomHeight();
    widgetBounds.width = width - background.getLeftWidth() - background.getRightWidth();
    widgetBounds.height = height - background.getTopHeight() - background.getBottomHeight();
    ScissorStack.calculateScissors(stage.getCamera(), transform, widgetBounds, scissors);
    titleBounds.x = 0;
    titleBounds.y = height - background.getTopHeight();
    titleBounds.width = width;
    titleBounds.height = background.getTopHeight();
    textBounds.set(titleFont.getBounds(title));
    textBounds.height -= titleFont.getDescent();
}

void Window::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    final NinePatch backgroundPatch = style.background;
    final BitmapFont titleFont = style.titleFont;
    final Color titleFontColor = style.titleFontColor;

    setupTransform(batch);
    layout();
    calculateBoundsAndScissors(batch.getTransformMatrix());

    batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);
    backgroundPatch.draw(batch, 0, 0, width, height);
    float textY = height - (int)(backgroundPatch.getTopHeight() / 2) + (int)(textBounds.height / 2);
    titleFont.setColor(titleFontColor.r, titleFontColor.g, titleFontColor.b, titleFontColor.a * parentAlpha);
    titleFont.drawMultiLine(batch, title, (int)(width / 2), textY, 0, HAlignment.CENTER);
    batch.flush();

    ScissorStack.pushScissors(scissors);
    super.drawChildren(batch, parentAlpha);
    ScissorStack.popScissors();

    resetTransform(batch);

}

bool Window::touchDown (float x,float y,int pointer) {
    if (pointer != 0) return false;
    if (hit(x, y) != null) {
        if (parent.getActors().size() > 1) parent.swapActor(this, parent.getActors().get(parent.getActors().size() - 1));
        if (titleBounds.contains(x, y)) {
            focus(this, 0);
            if (isMovable) {
                move = true;
            }
            initial.set(x, y);
        } else if (!super.touchDown(x, y, pointer)) {
            focus(this, 0);
        }
        return true;
    } else {
        if (isModal && parent.getActors().size() > 1)
            parent.swapActor(this, parent.getActors().get(parent.getActors().size() - 1));
        return isModal;
    }
}

bool Window::touchUp (float x,float y,int pointer) {
    if (pointer != 0) return false;
    if (parent.focusedActor[0] == this) focus(null, 0);
    move = false;
    return super.touchUp(x, y, pointer) || isModal;
}

bool Window::touchDragged (float x,float y,int pointer) {
    if (move) {
        this.x += (x - initial.x);
        this.y += (y - initial.y);
        return true;
    }
    if (parent.focusedActor[0] == this) return true;
    return super.touchDragged(x, y, pointer) || isModal;
}

gdx_cpp::scenes::scene2d::Actor& Window::hit (float x,float y) {
    return (x > 0 && x < width && y > 0 && y < height) || isModal ? this : null;
}

void Window::setTitle (const std::string& title) {
    this.title = title;
}

std::string& Window::getTitle () {
    return title;
}

void Window::setMovable (bool isMovable) {
    this.isMovable = isMovable;
}

bool Window::isMovable () {
    return isMovable;
}

void Window::setModal (bool isModal) {
    this.isModal = isModal;
}

bool Window::isModal () {
    return isModal;
}

