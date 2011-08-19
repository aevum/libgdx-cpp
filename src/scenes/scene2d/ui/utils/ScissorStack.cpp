
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

#include "ScissorStack.hpp"

using namespace gdx_cpp::scenes::scene2d::ui::utils;

void ScissorStack::pushScissors (const gdx_cpp::math::Rectangle& scissor) {
    fix(scissor);

    if (scissors.size == 0) {
        Gdx.gl.glEnable(GL10.GL_SCISSOR_TEST);
    } else {
        // merge scissors
        Rectangle parent = scissors.get(scissors.size - 1);
        float minX = Math.max(parent.x, scissor.x);
        float maxX = Math.min(parent.x + parent.width, scissor.x + scissor.width);
        scissor.x = minX;
        scissor.width = maxX - minX;

        float minY = Math.max(parent.y, scissor.y);
        float maxY = Math.min(parent.y + parent.height, scissor.y + scissor.height);
        scissor.y = minY;
        scissor.height = maxY - minY;
    }
    scissors.add(scissor);
    Gdx.gl.glScissor((int)scissor.x, (int)scissor.y, (int)scissor.width, (int)scissor.height);
}

void ScissorStack::popScissors () {
    scissors.pop();
    if (scissors.size == 0)
        Gdx.gl.glDisable(GL10.GL_SCISSOR_TEST);
    else {
        Rectangle scissor = scissors.peek();
        Gdx.gl.glScissor((int)scissor.x, (int)scissor.y, (int)scissor.width, (int)scissor.height);
    }
}

void ScissorStack::fix (const gdx_cpp::math::Rectangle& rect) {
    if (rect.width < 0) {
        rect.width = -rect.width;
        rect.x -= rect.width;
    }
    if (rect.height < 0) {
        rect.height = -rect.height;
        rect.y -= rect.height;
    }
}

void ScissorStack::calculateScissors (const gdx_cpp::graphics::Camera& camera,const gdx_cpp::math::Matrix4& batchTransform,const gdx_cpp::math::Rectangle& area,const gdx_cpp::math::Rectangle& scissor) {
    tmp.set(area.x, area.y, 0);
    tmp.mul(batchTransform);
    camera.project(tmp);
    scissor.x = tmp.x;
    scissor.y = tmp.y;

    tmp.set(area.x + area.width, area.y + area.height, 0);
    tmp.mul(batchTransform);
    camera.project(tmp);
    scissor.width = tmp.x - scissor.x;
    scissor.height = tmp.y - scissor.y;
}

gdx_cpp::math::Rectangle& ScissorStack::getViewport () {
    if (scissors.size == 0) {
        viewport.set(0, 0, Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
        return viewport;
    } else {
        Rectangle scissor = scissors.peek();
        viewport.set(scissor);
        return viewport;
    }
}

void ScissorStack::toWindowCoordinates (const gdx_cpp::graphics::Camera& camera,const gdx_cpp::math::Matrix4& transformMatrix,const gdx_cpp::math::Vector2& point) {
    tmp.set(point.x, point.y, 0);
    tmp.mul(transformMatrix);
    camera.project(tmp);
    tmp.y = Gdx.graphics.getHeight() - tmp.y;
    point.x = tmp.x;
    point.y = tmp.y;
}

