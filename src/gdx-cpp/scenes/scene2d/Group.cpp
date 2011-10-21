
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

#include "Group.hpp"

#include "gdx-cpp/utils/StringConvertion.hpp"
#include <math/MathUtils.hpp>

using namespace gdx_cpp::scenes::scene2d;
using namespace gdx_cpp;

gdx_cpp::graphics::Texture::ptr Group::debugTexture;
bool Group::debug = false;

void Group::act (float delta) {
    Actor::act(delta);

    ActorList::iterator it = children.begin();
    ActorList::iterator end = children.end();
    
    for (; it != end; ++it) {
        it->act(delta);
        if (it->isMarkedToRemove()) {
            it->markToRemove(false);
            removeActor(*it);
            it--;
        }
    }
}

void Group::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    if (!visible) return;

    if (debug && debugTexture != NULL && parent != NULL)
        batch.draw(*debugTexture, x, y, originX, originY, width == 0 ? 200 : width, height == 0 ? 200 : height, scaleX, scaleY,
                   rotation, 0, 0, debugTexture->getWidth(), debugTexture->getHeight(), false, false);

    if (transform) applyTransform(batch);
    drawChildren(batch, parentAlpha);
    if (transform) resetTransform(batch);
}

void Group::drawChildren (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    parentAlpha *= color.a;
    
    ActorList::iterator it = children.begin();
    ActorList::iterator end = children.end();
    
    if (transform) {       
        for (; it != end; ++it) {
            if (!it->visible) continue;
            it->draw(batch, parentAlpha);
        }
    } else {
        
        for (; it != end; ++it) {
            if (!it->visible) continue;
            it->x += x;
            it->y += y;
            it->draw(batch, parentAlpha);
            it->x -= x;
            it->y -= y;
        }
    }
    if (transform) batch.flush();
}

void Group::drawChild (const Actor& child, const gdx_cpp::graphics::g2d::SpriteBatch& batch, float parentAlpha) {
    if (child.visible) child.draw(batch, parentAlpha * color.a);
    if (transform) batch.flush();
}

void Group::applyTransform (const gdx_cpp::graphics::g2d::SpriteBatch& batch) {
    gdx_cpp::math::Matrix4& newBatchTransform = updateTransform();

    batch.end();
    oldBatchTransform.set(batch.getTransformMatrix());
    batch.setTransformMatrix(newBatchTransform);
    batch.begin();
}

gdx_cpp::math::Matrix4& Group::updateTransform () {
    gdx_cpp::math::Matrix3& temp = worldTransform;
    
    if (originX != 0 || originY != 0)
        localTransform.setToTranslation(originX, originY);
    else
        localTransform.idt();
    if (rotation != 0) localTransform.mul(temp.setToRotation(rotation));
    if (scaleX != 1 || scaleY != 1) localTransform.mul(temp.setToScaling(scaleX, scaleY));
    if (originX != 0 || originY != 0) localTransform.mul(temp.setToTranslation(-originX, -originY));
    localTransform.trn(x, y);

    Group* parentGroup = *parent;
    while (parentGroup != NULL) {
        if (parentGroup->transform) break;
        parentGroup = parentGroup->parent;
    }

    if (parentGroup != NULL) {
        worldTransform.set(parentGroup->worldTransform);
        worldTransform.mul(localTransform);
    } else {
        worldTransform.set(localTransform);
    }

    batchTransform.set(worldTransform);
    return batchTransform;
}

void Group::resetTransform (const gdx_cpp::graphics::g2d::SpriteBatch& batch) {
    batch.end();
    batch.setTransformMatrix(oldBatchTransform);
    batch.begin();
}

bool Group::touchDown (float x,float y,int pointer) {
    if (!touchable) return false;

    if (debug) gdx_cpp::Gdx::app->log("Group", name + ": " + gdx_cpp::utils::to_string(x) + ", " + gdx_cpp::utils::to_string(y));

    if (focusedActor[pointer] != NULL) {
        point.x = x;
        point.y = y;
        focusedActor[pointer]->toLocalCoordinates(point);
        focusedActor[pointer]->touchDown(point.x, point.y, pointer);
        return true;
    }

    ActorList::reverse_iterator child = children.rbegin();
    ActorList::reverse_iterator end = children.rend();
    
    for (; child != end; ++child) {   
        if (!child->touchable) continue;

        toChildCoordinates(child, x, y, point);
        if (child->hit(point.x, point.y) == NULL) continue;
        if (child->touchDown(point.x, point.y, pointer)) {
            if (focusedActor[pointer] == NULL) {
                focus(child, pointer);
            }
            
            if (child->getType() == Actor::Actor_Group)
                lastTouchedChild = ((Group*)*child)->lastTouchedChild;
            else
                lastTouchedChild = child;

            return true;
        }
    }

    return false;
}

void Group::touchUp (float x,float y,int pointer) {
    if (!touchable) return;
    point.x = x;
    point.y = y;

    Actor* actor = focusedActor[pointer];
    if (actor != this) {
        actor->toLocalCoordinates(point);
        actor->touchUp(point.x, point.y, pointer);
    }
    // If the focused actor hasn't changed and hasn't already lost focus, remove its focus.
    if (focusedActor[pointer] == actor && actor != NULL) actor->parent->focus(NULL, pointer);
}

bool Group::touchMoved (float x,float y) {
    if (!touchable) return false;

    ActorList::reverse_iterator child = children.rbegin();
    ActorList::reverse_iterator end = children.rend();
    
    for (; child != end; ++child) {   
        if (!child->touchable) continue;

        toChildCoordinates(child, x, y, point);

        if (child->touchMoved(point.x, point.y)) return true;
    }
    return false;
}

void Group::touchDragged (float x,float y,int pointer) {
    if (focusedActor[pointer] != NULL) {
        if (!touchable) return;
        point.x = x;
        point.y = y;
        focusedActor[pointer]->toLocalCoordinates(point);
        focusedActor[pointer]->touchDragged(point.x, point.y, pointer);
    }
}

bool Group::scrolled (int amount) {
    if (scrollFocusedActor != NULL) scrollFocusedActor->scrolled(amount);
    return false;
}

bool Group::keyDown (int keycode) {
    if (keyboardFocusedActor != NULL)
        return keyboardFocusedActor->keyDown(keycode);
    else
        return false;
}

bool Group::keyUp (int keycode) {
    if (keyboardFocusedActor != NULL)
        return keyboardFocusedActor->keyUp(keycode);
    else
        return false;
}

bool Group::keyTyped (char character) {
    if (keyboardFocusedActor != NULL)
        return keyboardFocusedActor->keyTyped(character);
    else
        return false;
}

Actor* Group::hit (float x,float y) {
    ActorList::reverse_iterator child = children.rbegin();
    ActorList::reverse_iterator end = children.rend();
    
    for (; child != end; ++child) {   
        toChildCoordinates(*child, x, y, point);

        Actor* hit = child->hit(point.x, point.y);
        if (hit != NULL) {
            return hit;
        }
    }
    return NULL;
}

void Group::addActor (const Actor* actor) {
    children.push_back(actor);
    if (actor->getType() == Actor_Group) groups.push_back((Group*) actor);
    if (!actor->name.empty()) namesToActors[actor->name] = actor;
    actor->parent = this;
}

void Group::addActorAt (int index,const Actor* actor) {
    children.insert(children.begin() + index, actor);
    
    if (actor->getType() == Actor_Group) groups.push_back((Group*)actor);
    if (!actor->name.empty()) namesToActors[actor->name] = actor;

    actor->parent = this;
}

void Group::addActorBefore (const Actor* actorBefore, const Actor* actor) {
    ActorList::iterator item = std::find(children.begin(), children.end(), actorBefore);    
    children.push_back(item - 1, actor);
    
    if (actor->getType() == Actor::Actor_Group) groups.push_back((Group*)actor);
    if (!actor->name.empty()) namesToActors[actor->name] = actor;
    actor->parent = this;
}

void Group::addActorAfter (const Actor* actorAfter,const Actor* actor) {
    ActorList::iterator item = std::find(children.begin(), children.end(), actorAfter);

    children.push_back(item, actor);

    if (actor->getType() == Actor_Group) groups.push_back((Group*)actor);
    
    if (!actor->name.empty()) namesToActors[actor->name] = actor;
    actor->parent = this;
}

void Group::removeActor (const Actor* actor) {
    children.erase(std::find(children.begin(), children.end(), actor));
    
    if (actor->getType() == Actor_Group) groups.remove((Group*)actor);
    if (!actor->name.empty()) namesToActors.erase(actor->name);
    unfocusAll(actor);
}

void Group::removeActorRecursive (const Actor* actor) {
    if (children.remove(actor)) {
        if (actor->getType() == Actor_Group) groups.remove((Group*)actor);
        if (!actor->name.empty()) namesToActors.erase(actor->name);
        unfocusAll(actor);
        return;
    }

    std::list<Group>::iterator it = children.begin();
    std::list<Group>::iterator end = children.end();

    for (; it != end; ++it) {
        it->removeActorRecursive(actor);
    }
}

Actor& Group::findActor (const std::string& name) {       
    Actor* actor = NULL;
    
    if (namesToActors.count(name) == 0) {       
        std::list<Group>::iterator it = children.begin();
        std::list<Group>::iterator end = children.end();
        
        for (; it != end; ++it) {
            actor = it->findActor(name);
            if (actor != NULL) return actor;
        }
    }

    return actor;
}

bool Group::swapActor (int first,int second) {
    int maxIndex = children.size();
    
    if (first < 0 || first >= maxIndex) return false;
    if (second < 0 || second >= maxIndex) return false;

    Actor* a = children[first];
    Actor* b = children[second];

    children[first] = b;
    children[second] = a;

    return true;
}

bool Group::swapActor (const Actor* first,const Actor* second) {

    int firstIndex = children.find(first);
    int secondIndex = children.indexOf(second);

    if (firstIndex == -1 || secondIndex == -1) return false;

    Collections.swap(children, firstIndex, secondIndex);
    return true;
}

std::list<Actor>& Group::getActors () {
    return immutableChildren;
}

std::list<Group>& Group::getGroups () {
    return immutableGroups;
}

void Group::focus (const Actor* actor,int pointer) {
    Actor* existingActor = focusedActor[pointer];
    if (existingActor != NULL) {
        // An actor already has focus. Remove the focus if it is not a child of this group, because the focused actor could be
        // further down in the hiearchy.
        focusedActor[pointer] = NULL;
        if (existingActor->parent != this) existingActor->parent->focus(NULL, pointer);
    }
    if (debug) Gdx::app->log("Group", std::string("focus: ") + (actor == NULL ? "null" : actor->name));
    focusedActor[pointer] = actor;
    if (parent != NULL) parent->focus(actor, pointer);
}

void Group::keyboardFocus (const Actor* actor) {
    keyboardFocusedActor = actor;
    if (parent != NULL) parent->keyboardFocus(actor);
}

void Group::scrollFocus (const Actor* actor) {
    scrollFocusedActor = actor;
    if (parent != NULL) parent.scrollFocus(actor);
}

void Group::clear () {
    children.clear();
    groups.clear();
    namesToActors.clear();
}

void Group::sortChildren (const Comparator<Actor>& comparator) {
    Collections.sort(children, comparator);
}

void Group::unfocusAll () {
    for (int i = 0; i < 20; i++) {
        focusedActor[i] = NULL;
    }

    for (int i = 0; i < groups.size(); i++) {
        groups[i].unfocusAll();
    }

    keyboardFocusedActor = NULL;
    scrollFocusedActor = NULL;
}

void Group::unfocusAll (const Actor* actor) {
    for (int i = 0; i < 20; i++) {
        if (focusedActor[i] == actor) {
            focus(NULL, i);
        }
    }

    if (keyboardFocusedActor == actor) keyboardFocus(NULL);
    if (scrollFocusedActor == actor) scrollFocus(NULL);
}

void Group::toChildCoordinates (const Actor* child,float x,float y,const gdx_cpp::math::Vector2& out) {
    if (child->rotation == 0) {
        if (child->scaleX == 1 && child->scaleY == 1) {
            out.x = x - child->x;
            out.y = y - child->y;
        } else {
            if (child->originX == 0 && child->originY == 0) {
                out.x = (x - child->x) / child->scaleX;
                out.y = (y - child->y) / child->scaleY;
            } else {
                out.x = (x - child->x - child->originX) / child->scaleX + child->originX;
                out.y = (y - child->y - child->originY) / child->scaleY + child->originY;
            }
        }
    } else {
        float cos = (float)math::utils::cos(child.rotation * math::utils::degreesToRadians);
        float sin = (float)math::utils::sin(child.rotation * math::utils::degreesToRadians);

        if (child->scaleX == 1 && child->scaleY == 1) {
            if (child->originX == 0 && child->originY == 0) {
                float tox = x - child->x;
                float toy = y - child->y;

                out.x = tox * cos + toy * sin;
                out.y = tox * -sin + toy * cos;
            } else {
                float worldOriginX = child->x + child->originX;
                float worldOriginY = child->y + child->originY;
                float fx = -child->originX;
                float fy = -child->originY;

                float x1 = cos * fx - sin * fy;
                float y1 = sin * fx + cos * fy;
                x1 += worldOriginX;
                y1 += worldOriginY;

                float tox = x - x1;
                float toy = y - y1;

                out.x = tox * cos + toy * sin;
                out.y = tox * -sin + toy * cos;
            }
        } else {
            if (child->originX == 0 && child->originY == 0) {
                float tox = x - child->x;
                float toy = y - child->y;

                out.x = tox * cos + toy * sin;
                out.y = tox * -sin + toy * cos;

                out.x /= child->scaleX;
                out.y /= child->scaleY;
            } else {
                float srefX = child->originX * child->scaleX;
                float srefY = child->originY * child->scaleY;

                float worldOriginX = child->x + child->originX;
                float worldOriginY = child->y + child->originY;
                float fx = -srefX;
                float fy = -srefY;

                float x1 = cos * fx - sin * fy;
                float y1 = sin * fx + cos * fy;
                x1 += worldOriginX;
                y1 += worldOriginY;

                float tox = x - x1;
                float toy = y - y1;

                out.x = tox * cos + toy * sin;
                out.y = tox * -sin + toy * cos;

                out.x /= child->scaleX;
                out.y /= child->scaleY;
            }
        }
    }
}

void Group::enableDebugging (const std::string& debugTextureFile) {
    debugTexture = graphics::Texture::fromFile(Gdx::files->internal(debugTextureFile), 0, false);
    debug = true;
}

void Group::disableDebugging () {
    if (debugTexture != NULL) debugTexture->dispose();
    debug = false;
}

Group::Group ()
    : Actor("")
    , transform(true)
    , lastTouchedChild(NULL)
    , keyboardFocusedActor(NULL)
    , scrollFocusedActor(NULL)
{
}

Group::Group (const std::string& name)
    : Actor(name)
    , transform(true)
    , lastTouchedChild(NULL)
    , keyboardFocusedActor(NULL)
    , scrollFocusedActor(NULL)
{
}

