
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

#include "Actor.hpp"

using namespace gdx_cpp::scenes::scene2d;

bool Actor::touchMoved (float x,float y) {
    return false;
}

bool Actor::scrolled (int amount) {
    return false;
}

bool Actor::keyDown (int keycode) {
    return false;
}

bool Actor::keyUp (int keycode) {
    return false;
}

bool Actor::keyTyped (char character) {
    return false;
}

void Actor::toLocalCoordinates (const gdx_cpp::math::Vector2& point) {
    if (parent == null) {
        return;
    }

    parent.toLocalCoordinates(point);
    Group.toChildCoordinates(this, point.x, point.y, point);
}

void Actor::remove () {
    parent.removeActor(this);
}

void Actor::act (float delta) {
    actions.iter();
    Action action;

    while ((action = actions.next()) != null) {
        action.act(delta);
        if (action.isDone()) {
            action.finish();
            actions.remove();
        }
    }
}

void Actor::action (const Action& action) {
    action.setTarget(this);
    actions.add(action);
}

void Actor::clearActions () {
    actions.clear();
}

std::string& Actor::toString () {
    return name + ": [x=" + x + ", y=" + y + ", refX=" + originX + ", refY=" + originY + ", width=" + width + ", height="
           + height + "]";
}

void Actor::markToRemove (const final& boolean) {
    toRemove = remove;
}

bool Actor::isMarkedToRemove () {
    return toRemove;
}

