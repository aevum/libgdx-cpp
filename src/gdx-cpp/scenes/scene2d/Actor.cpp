
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
#include "gdx-cpp/Gdx.hpp"
#include "Group.hpp"
#include "Action.hpp"

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

void Actor::toLocalCoordinates (gdx_cpp::math::Vector2& point) {
    if (parent == NULL) {
        return;
    }

    parent->toLocalCoordinates(point);
    Group::toChildCoordinates(this, point.x, point.y, point);
}

void Actor::remove () {
    parent->removeActor(this);
}

void Actor::act (float delta) {
    actions.iter();

    Action* action = 0;
    while ((action = actions.next()) != NULL) {
        action->act(delta);
        if (action->isDone()) {
            action->finish();
            actions.remove();
        }
    }
}

void Actor::action (Action* const action) {
    action->setTarget(this);
    actions.add(action);
}

void Actor::clearActions () {
    actions.clear();
}

std::string Actor::toString () const {
    char buffer[1024];
    sprintf(buffer, "%s: [x= %f, y= %f, refX= %f, refY= %f, width= %f, height=%f]", name.c_str(), x, y, originX, originY, width, height);
            
    return std::string(buffer);
}

void Actor::markToRemove (bool remove) {
    toRemove = remove;
}

bool Actor::isMarkedToRemove () {
    return toRemove;
}

Actor::Actor ()
 : toRemove(false)
 , color(1,1,1,1)
 , touchable(true)
 , visible(true)
 , parent(NULL)
 , actions(10)
 , scaleX(1)
 ,scaleY(1)
{    
}

Actor::Actor (const std::string& name)
: toRemove(false)
, color(1,1,1,1)
, touchable(true)
, visible(true)
, parent(NULL)
, actions(10)
, scaleX(1)
, scaleY(1)
{
    this->name = name;
}

