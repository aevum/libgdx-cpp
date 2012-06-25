
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

#include "SplitPane.hpp"

using namespace gdx::ui;

void SplitPane::setStyle (const SplitPaneStyle& style) {
    this.style = style;
}

void SplitPane::layout () {
    if (!invalidated) return;
    invalidated = false;

    if (firstWidget instanceof Layout) {
        Layout layout = (Layout)firstWidget;
        layout.layout();
        firstWidget.width = layout.getPrefWidth();
        firstWidget.height = layout.getPrefHeight();
    }
    if (secondWidget instanceof Layout) {
        Layout layout = (Layout)secondWidget;
        layout.layout();
        secondWidget.width = layout.getPrefWidth();
        secondWidget.height = layout.getPrefHeight();
    }
}

void SplitPane::invalidate () {
    if (firstWidget instanceof Layout) ((Layout)firstWidget).invalidate();
    if (secondWidget instanceof Layout) ((Layout)secondWidget).invalidate();
    invalidated = true;
}

float SplitPane::getPrefWidth () {
    return 150;
}

float SplitPane::getPrefHeight () {
    return 150;
}

float SplitPane::getMinWidth () {
    return 0;
}

float SplitPane::getMinHeight () {
    return 0;
}

float SplitPane::getMaxWidth () {
    return 0;
}

float SplitPane::getMaxHeight () {
    return 0;
}

void SplitPane::calculateBoundsAndPositions (const gdx::Matrix4& transform) {
    if (oldSplitAmount != splitAmount) {
        oldSplitAmount = splitAmount;
        invalidate();
    }

    if (!vertical)
        calculateHorizBoundsAndPositions();
    else
        calculateVertBoundsAndPositions();

    boolean layoutFirst = false;
    boolean layoutSecond = false;
    if (firstWidget.width != firstWidgetBounds.width || firstWidget.height != firstWidgetBounds.height) {
        layoutFirst = true;
    }
    if (secondWidget.width != secondWidgetBounds.width || secondWidget.height != secondWidgetBounds.height) {
        layoutSecond = true;
    }

    firstWidget.x = firstWidgetBounds.x;
    firstWidget.y = firstWidgetBounds.y;
    firstWidget.width = firstWidgetBounds.width;
    firstWidget.height = firstWidgetBounds.height;

    secondWidget.x = secondWidgetBounds.x;
    secondWidget.y = secondWidgetBounds.y;
    secondWidget.width = secondWidgetBounds.width;
    secondWidget.height = secondWidgetBounds.height;

    if (layoutFirst && firstWidget instanceof Layout) {
        ((Layout)firstWidget).invalidate();
    }

    if (layoutSecond && secondWidget instanceof Layout) {
        ((Layout)secondWidget).invalidate();
    }
    ScissorStack.calculateScissors(stage.getCamera(), transform, firstWidgetBounds, scissors[0]);
    ScissorStack.calculateScissors(stage.getCamera(), transform, secondWidgetBounds, scissors[1]);
}

void SplitPane::calculateHorizBoundsAndPositions () {
    NinePatch handle = style.handle;

    float availWidth = width - handle.getTotalWidth();
    float leftAreaWidth = (int)(availWidth * splitAmount);
    float rightAreaWidth = (availWidth - leftAreaWidth);
    float handleWidth = (handle.getTotalWidth());

    firstWidgetBounds.set(0, 0, leftAreaWidth, height);
    secondWidgetBounds.set(leftAreaWidth + handleWidth, 0, rightAreaWidth, height);
    handleBounds.set(leftAreaWidth, 0, handleWidth, height);
}

void SplitPane::calculateVertBoundsAndPositions () {
    NinePatch handle = style.handle;

    float availHeight = height - handle.getTotalHeight();
    float topAreaHeight = (int)(availHeight * splitAmount);
    float bottomAreaHeight = (availHeight - topAreaHeight);
    float handleHeight = handle.getTotalHeight();

    firstWidgetBounds.set(0, height - topAreaHeight, width, topAreaHeight);
    secondWidgetBounds.set(0, 0, width, bottomAreaHeight);
    handleBounds.set(0, bottomAreaHeight, width, handleHeight);
}

void SplitPane::draw (const gdx::SpriteBatch& batch,float parentAlpha) {
    NinePatch handle = style.handle;

    applyTransform(batch);
    calculateBoundsAndPositions(batch.getTransformMatrix());
    for (int i = 0; i < children.size(); i++) {
        ScissorStack.pushScissors(scissors[i]);
        drawChild(children.get(i), batch, parentAlpha);
        ScissorStack.popScissors();
    }
    batch.setColor(color.r, color.g, color.b, color.a);
    handle.draw(batch, handleBounds.x, handleBounds.y, handleBounds.width, handleBounds.height);
    if (invalidated) layout();
    resetTransform(batch);
}

bool SplitPane::touchDown (float x,float y,int pointer) {
    if (pointer != 0) return false;
    if (handleBounds.contains(x, y)) {
        touchDrag = true;
        lastPoint.set(x, y);
        handlePos.set(handleBounds.x, handleBounds.y);
        return true;
    }
    return super.touchDown(x, y, pointer);
}

void SplitPane::touchUp (float x,float y,int pointer) {
    if (touchDrag) {
        touchDrag = false;
        return;
    }
    super.touchUp(x, y, pointer);
}

void SplitPane::touchDragged (float x,float y,int pointer) {
    NinePatch handle = style.handle;

    if (touchDrag) {
        if (!vertical) {
            float delta = x - lastPoint.x;
            float availWidth = width - handle.getTotalWidth();
            float dragX = handlePos.x + delta;
            handlePos.x = dragX;
            dragX = Math.max(0, dragX);
            dragX = Math.min(availWidth, dragX);
            splitAmount = dragX / availWidth;
            if (splitAmount < minAmount) splitAmount = minAmount;
            if (splitAmount > maxAmount) splitAmount = maxAmount;
            invalidate();
            lastPoint.set(x, y);
        } else {
            float delta = y - lastPoint.y;
            float availHeight = height - handle.getTotalHeight();
            float dragY = handlePos.y + delta;
            handlePos.y = dragY;
            dragY = Math.max(0, dragY);
            dragY = Math.min(availHeight, dragY);
            splitAmount = 1 - (dragY / availHeight);
            if (splitAmount < minAmount) splitAmount = minAmount;
            if (splitAmount > maxAmount) splitAmount = maxAmount;
            invalidate();
            lastPoint.set(x, y);
        }
    } else
        super.touchDragged(x, y, pointer);
}

gdx::Actor& SplitPane::hit (float x,float y) {
    return x > 0 && x < width && y > 0 && y < height ? this : null;
}

void SplitPane::setSplitAmount (float split) {
    this.splitAmount = Math.max(Math.min(maxAmount, split), minAmount);
    invalidate();
}

float SplitPane::getSplit () {
    return splitAmount;
}

void SplitPane::setMinSplitAmount (float minAmount) {
    if (minAmount < 0) throw new GdxRuntimeException("minAmount has to be >= 0");
    if (minAmount >= maxAmount) throw new GdxRuntimeException("minAmount has to be < maxAmount");
    this.minAmount = minAmount;
}

void SplitPane::setMaxSplitAmount (float maxAmount) {
    if (maxAmount > 1) throw new GdxRuntimeException("maxAmount has to be >= 0");
    if (maxAmount <= minAmount) throw new GdxRuntimeException("maxAmount has to be > minAmount");
    this.maxAmount = maxAmount;
}

void SplitPane::setWidgets (const gdx::Actor& firstWidget,const gdx::Actor& secondWidget) {
    if (firstWidget == null) throw new IllegalArgumentException("firstWidget must not be null");
    if (secondWidget == null) throw new IllegalArgumentException("secondWidget must not be null");
    this.removeActor(this.firstWidget);
    this.removeActor(this.secondWidget);
    this.firstWidget = firstWidget;
    this.secondWidget = secondWidget;
    this.addActor(firstWidget);
    this.addActor(secondWidget);
    invalidate();
}

SplitPane::SplitPane (const gdx::Actor& firstWidget,const gdx::Actor& secondWidget,bool vertical,const gdx::Stage& stage,const Skin& skin) {
    this(firstWidget, secondWidget, vertical, stage, skin.getStyle(SplitPaneStyle.class), null);
}

SplitPane::SplitPane (const gdx::Actor& firstWidget,const gdx::Actor& secondWidget,bool vertical,const gdx::Stage& stage,const SplitPaneStyle& style) {
    this(firstWidget, secondWidget, vertical, stage, style, null);
}

SplitPane::SplitPane (const gdx::Actor& firstWidget,const gdx::Actor& secondWidget,bool vertical,const gdx::Stage& stage,const SplitPaneStyle& style,const std::string& name) {
    super(name);
    this.stage = stage;
    setStyle(style);
    this.firstWidget = firstWidget;
    this.secondWidget = secondWidget;
    this.vertical = vertical;

    this.addActor(firstWidget);
    this.addActor(secondWidget);
}

