
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

void Stage::setViewport (float width,float height,bool stretch) {
    if (!stretch) {
        if (width > height && width / (float)Gdx.graphics.getWidth() <= height / (float)Gdx.graphics.getHeight()) {
            float toDeviceSpace = Gdx.graphics.getHeight() / height;
            float toViewportSpace = height / Gdx.graphics.getHeight();

            float deviceWidth = width * toDeviceSpace;
            this.width = width + (Gdx.graphics.getWidth() - deviceWidth) * toViewportSpace;
            this.height = height;
        } else {
            float toDeviceSpace = Gdx.graphics.getWidth() / width;
            float toViewportSpace = width / Gdx.graphics.getWidth();

            float deviceHeight = height * toDeviceSpace;
            this.height = height + (Gdx.graphics.getHeight() - deviceHeight) * toViewportSpace;
            this.width = width;
        }
    } else {
        this.width = width;
        this.height = height;
    }

    this.stretch = stretch;
    centerX = width / 2;
    centerY = height / 2;

    camera.position.set(centerX, centerY, 0);
    camera.viewportWidth = this.width;
    camera.viewportHeight = this.height;
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
    toStageCoordinates(x, y, coords);
    Group.toChildCoordinates(root, coords.x, coords.y, point);
    return root.touchUp(point.x, point.y, pointer);
}

bool Stage::touchDragged (int x,int y,int pointer) {
    toStageCoordinates(x, y, coords);
    Group.toChildCoordinates(root, coords.x, coords.y, point);
    return root.touchDragged(point.x, point.y, pointer);
}

bool Stage::touchMoved (int x,int y) {
    toStageCoordinates(x, y, coords);
    Group.toChildCoordinates(root, coords.x, coords.y, point);
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
    batch.setProjectionMatrix(camera.combined);
    batch.begin();
    root.draw(batch, 1);
    batch.end();
}

void Stage::dispose () {
    batch.dispose();
}

void Stage::addActor (const Actor& actor) {
    root.addActor(actor);
}

std::string& Stage::graphToString () {
    StringBuilder buffer = new StringBuilder();
    graphToString(buffer, root, 0);
    return buffer.toString();
}

void Stage::graphToString (const StringBuilder& buffer,const Actor& actor,int level) {
    for (int i = 0; i < level; i++)
        buffer.append(' ');

    buffer.append(actor);
    buffer.append("\n");

    if (actor instanceof Group) {
        Group group = (Group)actor;
        for (int i = 0; i < group.getActors().size(); i++)
            graphToString(buffer, group.getActors().get(i), level + 1);
    }
}

Group& Stage::getRoot () {
    return root;
}

gdx_cpp::graphics::g2d::SpriteBatch& Stage::getSpriteBatch () {
    return batch;
}

gdx_cpp::graphics::Camera& Stage::getCamera () {
    return camera;
}

void Stage::setCamera (const gdx_cpp::graphics::Camera& camera) {
    this.camera = camera;
}

Actor& Stage::getLastTouchedChild () {
    return root.lastTouchedChild;
}

Actor& Stage::hit (float x,float y) {
    Group.toChildCoordinates(root, x, y, point);
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

