
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

using namespace gdx_cpp::scenes::scene2d;

void Group::updateTransform () {
    if (originX != 0 || originY != 0)
        transform.setToTranslation(originX, originY);
    else
        transform.idt();
    if (rotation != 0) transform.mul(scenetransform.setToRotation(rotation));
    if (scaleX != 1 || scaleY != 1) transform.mul(scenetransform.setToScaling(scaleX, scaleY));
    if (originX != 0 || originY != 0) transform.mul(scenetransform.setToTranslation(-originX, -originY));
    transform.trn(x, y);

    if (parent != null) {
        scenetransform.set(parent.scenetransform);
        scenetransform.mul(transform);
    } else {
        scenetransform.set(transform);
    }
}

void Group::act (float delta) {
    super.act(delta);

    for (int i = 0; i < children.size(); i++) {
        Actor child = children.get(i);
        child.act(delta);
        if (child.isMarkedToRemove()) {
            child.markToRemove(false);
            removeActor(child);
            i--;
        }
    }

}

void Group::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    if (!visible) return;
    setupTransform(batch);
    drawChildren(batch, parentAlpha);
    resetTransform(batch);
}

void Group::setupTransform (const gdx_cpp::graphics::g2d::SpriteBatch& batch) {
    updateTransform();
    tmp4.set(scenetransform);

    if (debug && debugTexture != null && parent != null)
        batch.draw(debugTexture, x, y, originX, originY, width == 0 ? 200 : width, height == 0 ? 200 : height, scaleX, scaleY,
                   rotation, 0, 0, debugTexture.getWidth(), debugTexture.getHeight(), false, false);

    batch.end();
    oldBatchTransform.set(batch.getTransformMatrix());
    batch.setTransformMatrix(tmp4);
    batch.begin();
}

void Group::drawChildren (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    int len = children.size();
    for (int i = 0; i < len; i++) {
        Actor child = children.get(i);
        if (child.visible) {
            child.draw(batch, parentAlpha * color.a);
        }
    }
    batch.flush();
}

void Group::drawChild (const Actor& child,const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    if (child.visible) {
        child.draw(batch, parentAlpha * color.a);
    }
    batch.flush();
}

void Group::resetTransform (const gdx_cpp::graphics::g2d::SpriteBatch& batch) {
    batch.end();
    batch.setTransformMatrix(oldBatchTransform);
    batch.begin();
}

void Group::toChildCoordinates (const Actor& child,float x,float y,const gdx_cpp::math::Vector2& out) {
    if (child.rotation == 0) {
        if (child.scaleX == 1 && child.scaleY == 1) {
            out.x = x - child.x;
            out.y = y - child.y;
        } else {
            if (child.originX == 0 && child.originY == 0) {
                out.x = (x - child.x) / child.scaleX;
                out.y = (y - child.y) / child.scaleY;
            } else {
                out.x = (x - child.x - child.originX) / child.scaleX + child.originX;
                out.y = (y - child.y - child.originY) / child.scaleY + child.originY;
            }
        }
    } else {
        final float cos = (float)Math.cos((float)Math.toRadians(child.rotation));
        final float sin = (float)Math.sin((float)Math.toRadians(child.rotation));

        if (child.scaleX == 1 && child.scaleY == 1) {
            if (child.originX == 0 && child.originY == 0) {
                float tox = x - child.x;
                float toy = y - child.y;

                out.x = tox * cos + toy * sin;
                out.y = tox * -sin + toy * cos;
            } else {
                final float worldOriginX = child.x + child.originX;
                final float worldOriginY = child.y + child.originY;
                float fx = -child.originX;
                float fy = -child.originY;

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
            if (child.originX == 0 && child.originY == 0) {
                float tox = x - child.x;
                float toy = y - child.y;

                out.x = tox * cos + toy * sin;
                out.y = tox * -sin + toy * cos;

                out.x /= child.scaleX;
                out.y /= child.scaleY;
            } else {
                float srefX = child.originX * child.scaleX;
                float srefY = child.originY * child.scaleY;

                final float worldOriginX = child.x + child.originX;
                final float worldOriginY = child.y + child.originY;
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

                out.x /= child.scaleX;
                out.y /= child.scaleY;
            }
        }
    }
}

bool Group::touchDown (float x,float y,int pointer) {
    if (!touchable) return false;

    if (debug) Gdx.app.log("Group", name + ": " + x + ", " + y);

    if (focusedActor[pointer] != null) {
        point.x = x;
        point.y = y;
        focusedActor[pointer].toLocalCoordinates(point);
        focusedActor[pointer].touchDown(point.x, point.y, pointer);
        return true;
    }

    int len = children.size() - 1;
    for (int i = len; i >= 0; i--) {
        Actor child = children.get(i);
        if (!child.touchable) continue;

        toChildCoordinates(child, x, y, point);

        if (child.touchDown(point.x, point.y, pointer)) {
            if (child instanceof Group)
                lastTouchedChild = ((Group)child).lastTouchedChild;
            else
                lastTouchedChild = child;
            return true;
        }
    }

    return false;
}

bool Group::touchUp (float x,float y,int pointer) {
    if (!touchable) return false;

    if (focusedActor[pointer] != null) {
        point.x = x;
        point.y = y;
        focusedActor[pointer].toLocalCoordinates(point);
        focusedActor[pointer].touchUp(point.x, point.y, pointer);
        return true;
    }

    int len = children.size() - 1;
    for (int i = len; i >= 0; i--) {
        Actor child = children.get(i);
        if (!child.touchable) continue;

        toChildCoordinates(child, x, y, point);

        if (child.touchUp(point.x, point.y, pointer)) return true;
    }
    return false;
}

bool Group::touchMoved (float x,float y) {
    if (!touchable) return false;

    int len = children.size() - 1;
    for (int i = len; i >= 0; i--) {
        Actor child = children.get(i);
        if (!child.touchable) continue;

        toChildCoordinates(child, x, y, point);

        if (child.touchMoved(point.x, point.y)) return true;
    }
    return false;
}

bool Group::touchDragged (float x,float y,int pointer) {
    if (!touchable) return false;

    if (focusedActor[pointer] != null) {
        point.x = x;
        point.y = y;
        focusedActor[pointer].toLocalCoordinates(point);
        focusedActor[pointer].touchDragged(point.x, point.y, pointer);
        return true;
    }

    int len = children.size() - 1;
    for (int i = len; i >= 0; i--) {
        Actor child = children.get(i);
        if (!child.touchable) continue;

        toChildCoordinates(child, x, y, point);

        if (child.touchDragged(point.x, point.y, pointer)) return true;
    }
    return false;
}

bool Group::scrolled (int amount) {
    if (scrollFocusedActor != null) scrollFocusedActor.scrolled(amount);
    return false;
}

bool Group::keyDown (int keycode) {
    if (keyboardFocusedActor != null)
        return keyboardFocusedActor.keyDown(keycode);
    else
        return false;
}

bool Group::keyUp (int keycode) {
    if (keyboardFocusedActor != null)
        return keyboardFocusedActor.keyUp(keycode);
    else
        return false;
}

bool Group::keyTyped (char character) {
    if (keyboardFocusedActor != null)
        return keyboardFocusedActor.keyTyped(character);
    else
        return false;
}

Actor& Group::hit (float x,float y) {
    int len = children.size() - 1;
    for (int i = len; i >= 0; i--) {
        Actor child = children.get(i);

        toChildCoordinates(child, x, y, point);

        Actor hit = child.hit(point.x, point.y);
        if (hit != null) {
            return hit;
        }
    }
    return null;
}

void Group::addActor (const Actor& actor) {
    children.add(actor);
    if (actor instanceof Group) groups.add((Group)actor);
    if (actor.name != null) namesToActors.put(actor.name, actor);
    actor.parent = this;
}

void Group::addActorAt (int index,const Actor& actor) {
    children.add(index, actor);
    if (actor instanceof Group) groups.add((Group)actor);
    if (actor.name != null) namesToActors.put(actor.name, actor);
    actor.parent = this;
}

void Group::addActorBefore (const Actor& actorBefore,const Actor& actor) {
    int index = children.indexOf(actorBefore);
    children.add(index, actor);
    if (actor instanceof Group) groups.add((Group)actor);
    if (actor.name != null) namesToActors.put(actor.name, actor);
    actor.parent = this;
}

void Group::addActorAfter (const Actor& actorAfter,const Actor& actor) {
    int index = children.indexOf(actorAfter);
    if (index == children.size())
        children.add(actor);
    else
        children.add(index + 1, actor);
    if (actor instanceof Group) groups.add((Group)actor);
    if (actor.name != null) namesToActors.put(actor.name, actor);
    actor.parent = this;
}

void Group::removeActor (const Actor& actor) {
    children.remove(actor);
    if (actor instanceof Group) groups.remove((Group)actor);
    if (actor.name != null) namesToActors.remove(actor.name);
    unfocusAll(actor);
}

void Group::removeActorRecursive (const Actor& actor) {
    if (children.remove(actor)) {
        if (actor instanceof Group) groups.remove((Group)actor);
        if (actor.name != null) namesToActors.remove(actor.name);
        unfocusAll(actor);
        return;
    }

    for (int i = 0; i < groups.size(); i++) {
        groups.get(i).removeActorRecursive(actor);
    }
}

Actor& Group::findActor (const std::string& name) {
    Actor actor = namesToActors.get(name);
    if (actor == null) {
        int len = groups.size();
        for (int i = 0; i < len; i++) {
            actor = groups.get(i).findActor(name);
            if (actor != null) return actor;
        }
    }

    return actor;
}

bool Group::swapActor (int first,int second) {
    int maxIndex = children.size();
    if (first < 0 || first >= maxIndex) return false;
    if (second < 0 || second >= maxIndex) return false;
    Collections.swap(children, first, second);
    return true;
}

bool Group::swapActor (const Actor& first,const Actor& second) {
    int firstIndex = children.indexOf(first);
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

void Group::focus (const Actor& actor,int pointer) {
    focusedActor[pointer] = actor;
    if (parent != null) parent.focus(actor, pointer);
}

void Group::keyboardFocus (const Actor& actor) {
    keyboardFocusedActor = actor;
    if (parent != null) parent.keyboardFocus(actor);
}

void Group::scrollFocus (const Actor& actor) {
    scrollFocusedActor = actor;
    if (parent != null) parent.scrollFocus(actor);
}

void Group::enableDebugging (const std::string& debugTextureFile) {
    debugTexture = new Texture(Gdx.files.internal(debugTextureFile), false);
    debug = true;
}

void Group::disableDebugging () {
    if (debugTexture != null) debugTexture.dispose();
    debug = false;
}

void Group::clear () {
    this.children.clear();
    this.groups.clear();
    this.namesToActors.clear();
}

void Group::sortChildren (const Comparator<Actor>& comparator) {
    Collections.sort(this.children, comparator);
}

void Group::unfocusAll () {
    for (int i = 0; i < focusedActor.length; i++) {
        focusedActor[i] = null;
    }

    for (int i = 0; i < groups.size(); i++) {
        groups.get(i).unfocusAll();
    }

    keyboardFocusedActor = null;
    scrollFocusedActor = null;
}

void Group::unfocusAll (const Actor& actor) {
    for (int i = 0; i < focusedActor.length; i++) {
        if (focusedActor[i] == actor) {
            focus(null, i);
        }
    }

    if (keyboardFocusedActor == actor) keyboardFocus(null);
    if (scrollFocusedActor == actor) scrollFocus(null);
}

