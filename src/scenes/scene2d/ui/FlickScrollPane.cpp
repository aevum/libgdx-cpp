
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

using namespace gdx_cpp::scenes::scene2d::ui;

void FlickScrollPane::calculateBoundsAndPositions (const gdx_cpp::math::Matrix4& batchTransform) {
    // get available space size by subtracting background's
    // padded area
    hasHScroll = false;
    hasVScroll = false;

    // Figure out if we need horizontal/vertical scrollbars,
    if (widget.width > width) hasHScroll = true;
    if (widget.height > height) hasVScroll = true;

    // Set the widget area bounds
    widgetAreaBounds.set(0, 0, width, height);

    // Calculate the widgets offset depending on the scroll state and
    // available widget area.
    widget.y = -(!hasVScroll ? (int)(widget.height - height) : 0)
               - (hasVScroll ? (int)((widget.height - height) * (1 - vScrollAmount)) : 0);
    widget.x = -(hasHScroll ? (int)((widget.width - width) * hScrollAmount) : 0);

    // Caculate the scissor bounds based on the batch transform,
    // the available widget area and the camera transform. We
    // need to project those to screen coordinates for OpenGL ES
    // to consume. This is pretty freaking nasty...
    ScissorStack.calculateScissors(stage.getCamera(), batchTransform, widgetAreaBounds, scissorBounds);
}

void FlickScrollPane::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    // setup transform for this group
    setupTransform(batch);

    // if invalidated layout!
    if (invalidated) layout();

    // calculate the bounds for the scrollbars, the widget
    // area and the scissor area. Nasty...
    calculateBoundsAndPositions(batch.getTransformMatrix());

    // enable scissors for widget area and draw that damn
    // widget. Nasty #2
    ScissorStack.pushScissors(scissorBounds);
    drawChildren(batch, parentAlpha);
    ScissorStack.popScissors();

    resetTransform(batch);
}

void FlickScrollPane::layout () {
    if (widget instanceof Layout) {
        Layout layout = (Layout)widget;
        widget.width = Math.max(width, layout.getPrefWidth());
        widget.height = Math.max(height, layout.getPrefHeight());
        layout.invalidate();
        layout.layout();
    }
    invalidated = false;
}

void FlickScrollPane::invalidate () {
    if (widget instanceof Layout) ((Layout)widget).invalidate();
    invalidated = true;
}

float FlickScrollPane::getPrefWidth () {
    return prefWidth;
}

float FlickScrollPane::getPrefHeight () {
    return prefHeight;
}

bool FlickScrollPane::touchDown (float x,float y,int pointer) {
    if (pointer != 0 || !touchable | hit(x, y) == null) {
        Gdx.app.log("", "HERE d");
        return false;
    }
    lastPoint.set(x, y);
    scrolling = true;
    scrollingStarted = System.currentTimeMillis();
    scrollStartPoint.x = x;
    scrollStartPoint.y = y;
    focus(this, 0);
    return true;
}

bool FlickScrollPane::touchUp (float x,float y,int pointer) {

    focus(null, 0);

    if (pointer != 0) {
        return false;
    }

    if (scrolling) {
        scrolling = false;
        long timetaken = System.currentTimeMillis() - scrollingStarted;
        float diffx = Math.max(scrollStartPoint.x, x) - Math.min(scrollStartPoint.x, x);
        float diffy = Math.max(scrollStartPoint.y, y) - Math.min(scrollStartPoint.y, y);

        System.out.println(String.format("Scrolled for %dms, %f on x, %f on y ", timetaken, diffx, diffy));

        if (vScrollAmount > 1f) {
            smoothScrollTo(0, 1f);
            return true;
        }

        else if (vScrollAmount < 0f) {
            smoothScrollTo(0f, 0f);
            return true;
        }

        if (diffx < 10 && diffy < 10) {
            if (timetaken < 190) {
                System.out.println("User has clicked");
                Actor hitchild;
for (Actor child : children) {

                    Vector2 point = new Vector2();
                    toChildCoordinates(child, x, y, point);

                    if ((hitchild = child.hit(point.x, point.y)) != null) {
                        hitchild.touchDown(point.x, point.y, pointer);
                        hitchild.touchUp(point.x, point.y, pointer);

                        Gdx.app.log("flick", hitchild.toString());

                        return true;
                    }
                }
            }
        }

        // fling

        else {
            float yaccel = diffy / timetaken;
            float xaccel = diffx / timetaken;
            System.out.println(String.format("y accel %f x accel %f", yaccel, xaccel));

            if (yaccel > 1 || xaccel > 1) {
                System.out.println("fling");

                if (scrollStartPoint.y > y) {
                    smoothScrollTo(hScrollAmount, (Math.max(vScrollAmount + (1 / widget.height) * -(diffy * 4), 0f)),
                                   (int)(timetaken * 1.5));
                } else {
                    smoothScrollTo(hScrollAmount, Math.min(vScrollAmount + (1 / widget.height) * (diffy * 4), 1f),
                                   (int)(timetaken * 1.5));
                }

                if (listener != null) {
                    listener.onFlinged();
                }
            }
        }

        //

        // if (scrolling) {
        // focus(null, 0);
        // scrolling = false;
        // return true;
        // } else

    }

    return super.touchUp(x, y, pointer);

}

bool FlickScrollPane::touchDragged (float x,float y,int pointer) {
    if (pointer != 0 || !touchable) return false;
    if (scrolling) {
        if (hasHScroll) {
            hScrollAmount -= (x - lastPoint.x) / (widget.width - width);
            if (overscrolls) {
                hScrollAmount = Math.max(0, hScrollAmount);
                hScrollAmount = Math.min(1, hScrollAmount);
            }
        }

        if (hasVScroll) {
            vScrollAmount += (y - lastPoint.y) / (widget.height - height);
            if (overscrolls) {
                vScrollAmount = Math.max(0, vScrollAmount);
                vScrollAmount = Math.min(1, vScrollAmount);
            }
        }
        lastPoint.set(x, y);
        return true;
    }

    Gdx.app.log("", "HERE dr!");

    return false;
}

gdx_cpp::scenes::scene2d::Actor& FlickScrollPane::hit (float x,float y) {
    return x > 0 && x < width && y > 0 && y < height ? this : null;
}

void FlickScrollPane::setWidget (const gdx_cpp::scenes::scene2d::Actor& widget) {
    if (widget == null) throw new IllegalArgumentException("widget must not be null");
    this.removeActor(this.widget);
    this.widget = widget;
    this.addActor(widget);
    invalidate();
}

void FlickScrollPane::scrollHorizontalTo (float scroll) {
    Gdx.app.log("", "scrollHorizontalTo");
    hScrollAmount = scroll;
}

float FlickScrollPane::getHorizontalScrollAmount () {
    return hScrollAmount;
}

void FlickScrollPane::scrollVerticalTo (float scroll) {
    vScrollAmount = scroll;
}

float FlickScrollPane::getVerticalScrollAmount () {
    return vScrollAmount;
}

void FlickScrollPane::smoothScrollTo (float horizontal,float vertical) {
    smoothScrollTo(horizontal, vertical, SCROLLTIMEDEFAULT);
}

void FlickScrollPane::smoothScrollTo (float horizontal,float vertical,int duration) {

    // Gdx.app.log("", String.format("hScrollAmount %f", hScrollAmount));
    // Gdx.app.log("", String.format("hScrollAmount %f", horizontal));

    smoothscrolldestx = horizontal;
    smoothscrolldesty = vertical;
    scrollstarth = hScrollAmount;
    scrollstartv = vScrollAmount;
    scrolledtime = 0;
    scrolltime = duration;

}

void FlickScrollPane::cancelAnimation () {
    smoothscrolldestx = -1;
    smoothscrolldesty = -1;
}

void FlickScrollPane::act (float delta) {
    super.act(delta);

    if (smoothscrolldestx != -1 && smoothscrolldesty != -1) {

        touchable = false;

        scrolledtime += (delta * 1000);

        float relscrolltime = ((float)1f / scrolltime) * scrolledtime;

        if (smoothscrolldestx > scrollstarth) {
            // hScrollAmount += (((smoothscrolldestx - scrollstarth)) / scrolltime) * (delta * 1000);

            hScrollAmount = scrollstarth + (smoothscrolldestx - scrollstarth) * interpolator.getInterpolation(relscrolltime);
        } else {
            // hScrollAmount -= (((scrollstarth - smoothscrolldestx)) / scrolltime) * (delta * 1000);

            hScrollAmount = scrollstarth - (scrollstarth - smoothscrolldestx) * interpolator.getInterpolation(relscrolltime);

        }

        if (smoothscrolldesty > scrollstartv) {
            // vScrollAmount += (((smoothscrolldesty - scrollstartv)) / scrolltime) * (delta * 1000);
            vScrollAmount = scrollstartv + (smoothscrolldesty - scrollstartv) * interpolator.getInterpolation(relscrolltime);
        } else {
            // vScrollAmount -= (((scrollstartv - smoothscrolldesty)) / scrolltime) * (delta * 1000);
            vScrollAmount = scrollstartv - (scrollstartv - smoothscrolldesty) * interpolator.getInterpolation(relscrolltime);
        }

        // Gdx.app.log("", String.format("t %f h %f v %f", relscrolltime, hScrollAmount, vScrollAmount));

        if (scrolledtime >= scrolltime) {
            hScrollAmount = smoothscrolldestx;
            vScrollAmount = smoothscrolldesty;
            smoothscrolldestx = -1;
            smoothscrolldesty = -1;
            touchable = true;
            scrolledtime = 0;
            Gdx.app.log("", "SCROLL OVER");
            if (listener != null) {
                listener.onSmoothScrollComplete();
            }
        }

    }

}

void FlickScrollPane::setListener (const Listener& listener) {
    this.listener = listener;
}

