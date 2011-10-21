
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

#include "Stage.hpp"

using namespace gdx_cpp::scenes::scene2d;
using namespace gdx_cpp;

void Stage::setViewport (float width, float height, bool stretch) {
    if (!stretch) {
        if (width > height && width / (float)Gdx::graphics->getWidth() <= height / (float)Gdx::graphics->getHeight()) {
            float toDeviceSpace = Gdx::graphics->getHeight() / height;
            float toViewportSpace = height / Gdx::graphics->getHeight();

            float deviceWidth = width * toDeviceSpace;
            this->width = width + (Gdx::graphics->getWidth() - deviceWidth) * toViewportSpace;
            this->height = height;
        } else {
            float toDeviceSpace = Gdx::graphics->getWidth() / width;
            float toViewportSpace = width / Gdx::graphics->getWidth();

            float deviceHeight = height * toDeviceSpace;
            this->height = height + (Gdx::graphics->getHeight() - deviceHeight) * toViewportSpace;
            this->width = width;
        }
    } else {
        this->width = width;
        this->height = height;
    }

    this->stretch = stretch;
    centerX = this->width / 2;
    centerY = this->height / 2;

    camera.position.set(centerX, centerY, 0);
    camera.viewportWidth = this->width;
    camera.viewportHeight = this->height;
}

float Stage::width () {
    return width;
}

float Stage::height () {
    return height;
}

int Stage::left () {
    return 0;
}

float Stage::right () {
    return width - 1;
}

float Stage::top () {
    return height - 1;
}

float Stage::bottom () {
    return 0;
}

float Stage::centerX () {
    return centerX;
}

float Stage::centerY () {
    return centerY;
}

bool Stage::isStretched () {
    return stretch;
}

Actor& Stage::findActor (const std::string& name) {
    return root.findActor(name);
}

std::list<Actor>& Stage::getActors () {
    return root.getActors();
}

std::list<Group>& Stage::getGroups () {
    return root.getGroups();
}

bool Stage::touchDown (int x,int y,int pointer,int button) {
    toStageCoordinates(x, y, coords);
    Group.toChildCoordinates(root, coords.x, coords.y, point);
    return root.touchDown(point.x, point.y, pointer);
}

bool Stage::touchUp (int x,int y,int pointer,int button) {
    Actor actor = root.focusedActor[pointer];
    if (actor == NULL) return false;
    toStageCoordinates(x, y, coords);
    Group::toChildCoordinates(root, coords.x, coords.y, point);
    root.touchUp(point.x, point.y, pointer);
    return true;
}

bool Stage::touchDragged (int x,int y,int pointer) {
    boolean foundFocusedActor = false;
    for (int i = 0, n = 20; i < n; i++) {
        if (root.focusedActor[i] != NULL) {
            foundFocusedActor = true;
            break;
        }
    }
    if (!foundFocusedActor) return false;
    toStageCoordinates(x, y, coords);
    Group::toChildCoordinates(root, coords.x, coords.y, point);
    root.touchDragged(point.x, point.y, pointer);
    return true;
}

bool Stage::touchMoved (int x,int y) {
    toStageCoordinates(x, y, coords);
    Group::toChildCoordinates(root, coords.x, coords.y, point);
    return root.touchMoved(point.x, point.y);
}

bool Stage::scrolled (int amount) {
    return root.scrolled(amount);
}

bool Stage::keyDown (int keycode) {
    return root.keyDown(keycode);
}

bool Stage::keyUp (int keycode) {
    return root.keyUp(keycode);
}

bool Stage::keyTyped (char character) {
    return root.keyTyped(character);
}

void Stage::act (float delta) {
    root.act(delta);
}

void Stage::draw () {
    camera.update();
    batch->setProjectionMatrix(camera.combined);
    batch->begin();
    root.draw(batch, 1);
    batch->end();
}

void Stage::dispose () {
    batch->dispose();
}

void Stage::addActor (const Actor& actor) {
    root.addActor(actor);
}

std::string Stage::graphToString () {
    std::stringstream buffer;
    graphToString(buffer, &root, 0);
    return buffer.str();
}

void Stage::graphToString (std::stringstream& buffer, const Actor* actor,int level) {
    for (int i = 0; i < level; i++)
        buffer << ' ';

    buffer << actor.toString() << std::endl;
    
    if (actor.getType() == Actor::Actor_Group) {
        Group& group = (Group&)actor;

        std::list< Actor* >::iterator it = group.getActors().begin();
        std::list< Actor* >::iterator end = group.getActors().end();
        
        for (;it != end;++it)
            graphToString(buffer, *it, level + 1);
    }
}

scenes::scene2d::Group& Stage::getRoot () {
    return root;
}

gdx_cpp::graphics::g2d::SpriteBatch* Stage::getSpriteBatch () {
    return batch;
}

gdx_cpp::graphics::Camera& Stage::getCamera () {
    return camera;
}

void Stage::setCamera (const gdx_cpp::graphics::Camera& camera) {
    this->camera = camera;
}

Actor* Stage::getLastTouchedChild () {
    return root.lastTouchedChild;
}

Actor* Stage::hit (float x,float y) {
    Group::toChildCoordinates(root, x, y, point);
    return root.hit(point.x, point.y);
}

void Stage::toStageCoordinates (int x,int y,const gdx_cpp::math::Vector2& out) {
    camera.unproject(tmp.set(x, y, 0));
    out.x = tmp.x;
    out.y = tmp.y;
}

void Stage::clear () {
    root.clear();
}

void Stage::removeActor (const Actor& actor) {
    root.removeActorRecursive(actor);
}

void Stage::unfocusAll () {
    root.unfocusAll();
}

Stage::Stage (float width,float height,bool stretch)
: width(width)
 ,height(height)
 ,stretch(stretch)
 ,root("root")
 ,batch(new graphics::g2d::SpriteBatch)
{
    setViewport(width, height, stretch);
}

scenes::scene2d::Stage::~Stage()
{
    batch->dispose();
    delete batch;
}


