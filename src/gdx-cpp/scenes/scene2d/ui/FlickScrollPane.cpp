
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

#include "FlickScrollPane.hpp"

using namespace gdx::ui;

bool FlickScrollPane::pan (int x,int y,int deltaX,int deltaY) {
    amountX -= deltaX;
    amountY += deltaY;
    clamp();
    return false;
}

bool FlickScrollPane::fling (float x,float y) {
    if (Math.abs(x) > 150) {
        flingTimer = flingTime;
        velocityX = x;
    }
    if (Math.abs(y) > 150) {
        flingTimer = flingTime;
        velocityY = -y;
    }
    return flingTimer > 0;
}

bool FlickScrollPane::touchDown (int x,int y,int pointer) {
    flingTimer = 0;
    return true;
}

bool FlickScrollPane::zoom (float originalDistance,float currentDistance) {
    return false;
}

bool FlickScrollPane::tap (int x,int y,int count) {
    return FlickScrollPane.this.tap(x, y);
}

bool FlickScrollPane::longPress (int x,int y) {
    return false;
}

void FlickScrollPane::toLocalCoordinates (const gdx::Actor& actor,const gdx::Vector2& point) {
    if (actor.parent == this) return;
    toLocalCoordinates(actor.parent, point);
    Group.toChildCoordinates(actor, point.x, point.y, point);
}

void FlickScrollPane::act (float delta) {
    if (flingTimer > 0) {
        float alpha = flingTimer / flingTime;
        alpha = alpha * alpha * alpha;
        amountX -= velocityX * alpha * delta;
        amountY -= velocityY * alpha * delta;
        clamp();

        // Stop fling if hit bounce distance.
        if (amountX == -bounceDistance) velocityX = 0;
        if (amountX >= maxX + bounceDistance) velocityX = 0;
        if (amountY == -bounceDistance) velocityY = 0;
        if (amountY >= maxY + bounceDistance) velocityY = 0;

        flingTimer -= delta;
    }

    if (bounces && !gestureDetector.isPanning()) {
        if (amountX < 0) {
            amountX += (bounceSpeedMin + (bounceSpeedMax - bounceSpeedMin) * -amountX / bounceDistance) * delta;
            if (amountX > 0) amountX = 0;
        } else if (amountX > maxX) {
            amountX -= (bounceSpeedMin + (bounceSpeedMax - bounceSpeedMin) * -(maxX - amountX) / bounceDistance) * delta;
            if (amountX < maxX) amountX = maxX;
        }
        if (amountY < 0) {
            amountY += (bounceSpeedMin + (bounceSpeedMax - bounceSpeedMin) * -amountY / bounceDistance) * delta;
            if (amountY > 0) amountY = 0;
        } else if (amountY > maxY) {
            amountY -= (bounceSpeedMin + (bounceSpeedMax - bounceSpeedMin) * -(maxY - amountY) / bounceDistance) * delta;
            if (amountY < maxY) amountY = maxY;
        }
    }
}

void FlickScrollPane::calculateBoundsAndPositions (const gdx::Matrix4& batchTransform) {
    // Get widget's desired width.
    float widgetWidth, widgetHeight;
    if (widget instanceof Layout) {
        Layout layout = (Layout)widget;
        widgetWidth = layout.getPrefWidth();
        widgetHeight = layout.getPrefHeight();
    } else {
        widgetWidth = widget.width;
        widgetHeight = widget.height;
    }

    // Figure out if we need horizontal/vertical scrollbars,
    scrollX = widgetWidth > width || forceScrollX;
    scrollY = widgetHeight > height || forceScrollY;

    // If the widget is smaller than the available space, make it take up the available space.
    widgetWidth = Math.max(width, widgetWidth);
    widgetHeight = Math.max(height, widgetHeight);
    if (widget.width != widgetWidth || widget.height != widgetHeight) {
        widget.width = widgetWidth;
        widget.height = widgetHeight;
        needsLayout = true;
    }

    // Set the widget area bounds.
    widgetAreaBounds.set(0, 0, width, height);

    // Calculate the widgets offset depending on the scroll state and available widget area.
    maxX = widget.width - width;
    maxY = widget.height - height;
    widget.y = (int)(scrollY ? amountY : maxY) - widget.height + height;
    widget.x = -(int)(scrollX ? amountX : 0);

    // Caculate the scissor bounds based on the batch transform, the available widget area and the camera transform. We need to
    // project those to screen coordinates for OpenGL ES to consume.
    ScissorStack.calculateScissors(stage.getCamera(), batchTransform, widgetAreaBounds, scissorBounds);
}

void FlickScrollPane::draw (const gdx::SpriteBatch& batch,float parentAlpha) {
    if (widget == null) return;

    // Setup transform for this group.
    applyTransform(batch);

    // Calculate the bounds for the scrollbars, the widget area and the scissor area.
    calculateBoundsAndPositions(batch.getTransformMatrix()); // BOZO - Call every frame?

    if (needsLayout) layout();

    // Enable scissors for widget area and draw the widget.
    ScissorStack.pushScissors(scissorBounds);
    drawChildren(batch, parentAlpha);
    ScissorStack.popScissors();

    resetTransform(batch);
}

void FlickScrollPane::layout () {
    if (!needsLayout) return;
    needsLayout = false;
    if (widget instanceof Layout) {
        Layout layout = (Layout)widget;
        layout.invalidate();
        layout.layout();
    }
}

void FlickScrollPane::invalidate () {
    needsLayout = true;
}

bool FlickScrollPane::touchDown (float x,float y,int pointer) {
    if (pointer != 0) return false;
    if (emptySpaceOnlyScroll && super.touchDown(x, y, pointer)) return true;
    return gestureDetector.touchDown((int)x, (int)y, pointer, 0);
}

void FlickScrollPane::touchUp (float x,float y,int pointer) {
    clamp();
    gestureDetector.touchUp((int)x, (int)y, pointer, 0);
    if (focusedActor[pointer] != null) super.touchUp(x, y, pointer);
}

void FlickScrollPane::touchDragged (float x,float y,int pointer) {
    gestureDetector.touchDragged((int)x, (int)y, pointer);
    super.touchDragged(x, y, pointer);
}

gdx::Actor& FlickScrollPane::hit (float x,float y) {
    return x > 0 && x < width && y > 0 && y < height ? this : null;
}

void FlickScrollPane::setScrollX (float pixels) {
    this.amountX = pixels;
}

float FlickScrollPane::getScrollX () {
    return amountX;
}

void FlickScrollPane::setScrollY (float pixels) {
    amountY = pixels;
}

float FlickScrollPane::getScrollY () {
    return amountY;
}

void FlickScrollPane::setWidget (const gdx::Actor& widget) {
    if (this.widget != null) removeActor(this.widget);
    this.widget = widget;
    if (widget != null) addActor(widget);
}

gdx::Actor& FlickScrollPane::getWidget () {
    return widget;
}

bool FlickScrollPane::isPanning () {
    return gestureDetector.isPanning();
}

float FlickScrollPane::getVelocityX () {
    if (flingTimer <= 0) return 0;
    float alpha = flingTimer / flingTime;
    alpha = alpha * alpha * alpha;
    return velocityX * alpha * alpha * alpha;
}

float FlickScrollPane::getVelocityY () {
    return velocityY;
}

float FlickScrollPane::getPrefWidth () {
    return 150;
}

float FlickScrollPane::getPrefHeight () {
    return 150;
}

float FlickScrollPane::getMinWidth () {
    return 0;
}

float FlickScrollPane::getMinHeight () {
    return 0;
}

float FlickScrollPane::getMaxWidth () {
    return 0;
}

float FlickScrollPane::getMaxHeight () {
    return 0;
}

FlickScrollPane::FlickScrollPane (const gdx::Actor& widget,const gdx::Stage& stage) {
    this(widget, stage, null);
}

FlickScrollPane::FlickScrollPane (const gdx::Actor& widget,const gdx::Stage& stage,const std::string& name) {
    super(name);

    this.stage = stage;
    this.widget = widget;
    if (widget != null) this.addActor(widget);

    gestureDetector = new GestureDetector(new GestureListener() {
        public boolean pan (int x, int y, int deltaX, int deltaY) {
            amountX -= deltaX;
            amountY += deltaY;
            clamp();
            return false;
        }

        public boolean fling (float x, float y) {
            if (Math.abs(x) > 150) {
                flingTimer = flingTime;
                velocityX = x;
            }
            if (Math.abs(y) > 150) {
                flingTimer = flingTime;
                velocityY = -y;
            }
            return flingTimer > 0;
        }

        public boolean touchDown (int x, int y, int pointer) {
            flingTimer = 0;
            return true;
        }

        public boolean zoom (float originalDistance, float currentDistance) {
            return false;
        }

        public boolean tap (int x, int y, int count) {
            return FlickScrollPane.this.tap(x, y);
        }

        public boolean longPress (int x, int y) {
            return false;
        }
    });
}

