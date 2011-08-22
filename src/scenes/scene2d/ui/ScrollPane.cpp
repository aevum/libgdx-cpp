
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

#include "ScrollPane.hpp"

using namespace gdx_cpp::scenes::scene2d::ui;

void ScrollPane::calculateBoundsAndPositions (const gdx_cpp::math::Matrix4& batchTransform) {
    final NinePatch background = style.background;
    final NinePatch hScrollKnob = style.hScrollKnob;
    final NinePatch vScrollKnob = style.vScrollKnob;

    // get available space size by subtracting background's
    // padded area
    float areaWidth = width - background.getLeftWidth() - background.getRightWidth();
    float areaHeight = height - background.getTopHeight() - background.getBottomHeight();
    hasHScroll = false;
    hasVScroll = false;

    // Figure out if we need horizontal/vertical scrollbars,
    if (widget.width > areaWidth) hasHScroll = true;
    if (widget.height > areaHeight) hasVScroll = true;

    // check again, now taking into account the area
    // that's taken up by any enabled scrollbars
    if (hasVScroll && (widget.width > areaWidth - vScrollKnob.getTotalWidth())) {
        hasHScroll = true;
        areaWidth -= vScrollKnob.getTotalWidth();
    }
    if (hasHScroll && (widget.height > areaHeight - hScrollKnob.getTotalHeight())) {
        hasVScroll = true;
        areaHeight -= hScrollKnob.getTotalHeight();
    }

    // now we know what scrollbars we need, set the bounds and
    // scroll knob sizes accordingly
    if (hasHScroll) {
        hScrollBounds.set(background.getLeftWidth(), background.getBottomHeight(), areaWidth, hScrollKnob.getTotalHeight());
        hScrollKnobBounds.width = Math.max(hScrollKnob.getTotalWidth(), (int)(hScrollBounds.width * areaWidth / widget.width));
        hScrollKnobBounds.height = hScrollKnob.getTotalHeight();

        hScrollKnobBounds.x = hScrollBounds.x + (int)((hScrollBounds.width - hScrollKnobBounds.width) * hScrollAmount);
        hScrollKnobBounds.y = hScrollBounds.y;
    }

    if (hasVScroll) {
        vScrollBounds.set(width - background.getRightWidth() - vScrollKnob.getTotalWidth(), height - background.getTopHeight()
                          - areaHeight, vScrollKnob.getTotalWidth(), areaHeight);
        vScrollKnobBounds.width = vScrollKnob.getTotalWidth();
        vScrollKnobBounds.height = Math.max(vScrollKnob.getTotalHeight(),
                                            (int)(vScrollBounds.height * areaHeight / widget.height));
        vScrollKnobBounds.x = vScrollBounds.x;
        vScrollKnobBounds.y = vScrollBounds.y + (int)((vScrollBounds.height - vScrollKnobBounds.height) * (1 - vScrollAmount));
    }

    // Set the widget area bounds
    widgetAreaBounds.set(background.getLeftWidth(), background.getBottomHeight()
                         + (hasHScroll ? hScrollKnob.getTotalHeight() : 0), areaWidth, areaHeight);

    // Calculate the widgets offset depending on the scroll state and
    // available widget area.
    widget.y = widgetAreaBounds.y - (!hasVScroll ? (int)(widget.height - areaHeight) : 0)
               - (hasVScroll ? (int)((widget.height - areaHeight) * (1 - vScrollAmount)) : 0);
    widget.x = widgetAreaBounds.x - (hasHScroll ? (int)((widget.width - areaWidth) * hScrollAmount) : 0);

    // Caculate the scissor bounds based on the batch transform,
    // the available widget area and the camera transform. We
    // need to project those to screen coordinates for OpenGL ES
    // to consume. This is pretty freaking nasty...
    ScissorStack.calculateScissors(stage.getCamera(), batchTransform, widgetAreaBounds, scissorBounds);
}

void ScrollPane::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    final NinePatch background = style.background;
    final NinePatch hScrollKnob = style.hScrollKnob;
    final NinePatch hScroll = style.hScroll;
    final NinePatch vScrollKnob = style.vScrollKnob;
    final NinePatch vScroll = style.vScroll;

    // setup transform for this group
    setupTransform(batch);

    // if invalidated layout!
    if (invalidated) layout();

    // calculate the bounds for the scrollbars, the widget
    // area and the scissor area. Nasty...
    calculateBoundsAndPositions(batch.getTransformMatrix());

    // first draw the background ninepatch
    batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);
    background.draw(batch, 0, 0, width, height);

    // enable scissors for widget area and draw that damn
    // widget. Nasty #2
    ScissorStack.pushScissors(scissorBounds);
    drawChildren(batch, parentAlpha);
    ScissorStack.popScissors();

    // render scrollbars and knobs on top.
    batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);
    if (hasHScroll) {
        hScroll.draw(batch, hScrollBounds.x, hScrollBounds.y, hScrollBounds.width, hScrollBounds.height);
        hScrollKnob.draw(batch, hScrollKnobBounds.x, hScrollKnobBounds.y, hScrollKnobBounds.width, hScrollKnobBounds.height);
    }
    if (hasVScroll) {
        vScroll.draw(batch, vScrollBounds.x, vScrollBounds.y, vScrollBounds.width, vScrollBounds.height);
        vScrollKnob.draw(batch, vScrollKnobBounds.x, vScrollKnobBounds.y, vScrollKnobBounds.width, vScrollKnobBounds.height);
    }

    resetTransform(batch);
}

void ScrollPane::layout () {
    if (widget instanceof Layout) {
        Layout layout = (Layout)widget;
        widget.width = Math.max(width, layout.getPrefWidth());
        widget.height = Math.max(height, layout.getPrefHeight());
        layout.invalidate();
        layout.layout();
    }
    invalidated = false;
}

void ScrollPane::invalidate () {
    if (widget instanceof Layout) ((Layout)widget).invalidate();
    invalidated = true;
}

float ScrollPane::getPrefWidth () {
    return prefWidth;
}

float ScrollPane::getPrefHeight () {
    return prefHeight;
}

bool ScrollPane::touchDown (float x,float y,int pointer) {
    if (pointer != 0) return false;

    if (hasHScroll && hScrollBounds.contains(x, y)) {
        if (hScrollKnobBounds.contains(x, y)) {
            lastPoint.set(x, y);
            handlePos = hScrollKnobBounds.x;
            touchScrollH = true;
            focus(this, 0);
        } else {
            if (x < hScrollKnobBounds.x) {
                hScrollAmount = Math.max(0, hScrollAmount - 0.1f);
            } else {
                hScrollAmount = Math.min(1, hScrollAmount + 0.1f);
            }
        }
        return true;
    } else if (hasVScroll && vScrollBounds.contains(x, y)) {
        if (vScrollKnobBounds.contains(x, y)) {
            lastPoint.set(x, y);
            handlePos = vScrollKnobBounds.y;
            touchScrollV = true;
            focus(this, 0);
        } else {
            if (y < vScrollKnobBounds.y) {
                vScrollAmount = Math.min(1, vScrollAmount + 0.1f);
            } else {
                vScrollAmount = Math.max(0, vScrollAmount - 0.1f);
            }
        }
        return true;
    } else if (widgetAreaBounds.contains(x, y)) {
        return super.touchDown(x, y, pointer);
    } else
        return false;
}

bool ScrollPane::touchUp (float x,float y,int pointer) {
    if (pointer != 0) return false;
    if (touchScrollH || touchScrollV) {
        focus(null, 0);
        touchScrollH = false;
        touchScrollV = false;
        return true;
    } else
        return super.touchUp(x, y, pointer);
}

bool ScrollPane::touchDragged (float x,float y,int pointer) {
    if (pointer != 0) return false;
    if (touchScrollH) {
        float delta = x - lastPoint.x;
        float scrollH = handlePos + delta;
        handlePos = scrollH;
        scrollH = Math.max(hScrollBounds.x, scrollH);
        scrollH = Math.min(hScrollBounds.x + hScrollBounds.width - hScrollKnobBounds.width, scrollH);
        hScrollAmount = (scrollH - hScrollBounds.x) / (hScrollBounds.width - hScrollKnobBounds.width);
        lastPoint.set(x, y);
        return true;
    } else if (touchScrollV) {
        float delta = y - lastPoint.y;
        float scrollV = handlePos + delta;
        handlePos = scrollV;
        scrollV = Math.max(vScrollBounds.y, scrollV);
        scrollV = Math.min(vScrollBounds.y + vScrollBounds.height - vScrollKnobBounds.height, scrollV);
        vScrollAmount = 1 - ((scrollV - vScrollBounds.y) / (vScrollBounds.height - vScrollKnobBounds.height));
        lastPoint.set(x, y);
        return true;
    } else
        return super.touchDragged(x, y, pointer);
}

gdx_cpp::scenes::scene2d::Actor& ScrollPane::hit (float x,float y) {
    return x > 0 && x < width && y > 0 && y < height ? this : null;
}

void ScrollPane::setWidget (const gdx_cpp::scenes::scene2d::Actor& widget) {
    if (widget == null) throw new IllegalArgumentException("widget must not be null");
    this.removeActor(this.widget);
    this.widget = widget;
    this.addActor(widget);
    invalidate();
}

