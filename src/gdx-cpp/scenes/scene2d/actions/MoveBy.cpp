
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

#include "MoveBy.hpp"

using namespace gdx_cpp::scenes::scene2d::actions;

MoveBy& MoveBy::newObject () {
    return new MoveBy();
}

MoveBy& MoveBy::$ (float x,float y,float duration) {
    MoveBy action = pool.obtain();
    action.x = action.initialX = x;
    action.y = action.initialY = y;
    action.duration = duration;
    action.invDuration = 1 / duration;
    return action;
}

void MoveBy::setTarget (const gdx_cpp::scenes::scene2d::Actor& actor) {
    this.target = actor;
    this.startX = target.x;
    this.startY = target.y;
    this.deltaX = x;
    this.deltaY = y;
    this.x = target.x + x;
    this.y = target.y + y;
    this.taken = 0;
    this.done = false;
}

void MoveBy::act (float delta) {
    float alpha = createInterpolatedAlpha(delta);
    if (done) {
        target.x = x;
        target.y = y;
    } else {
        target.x = startX + deltaX * alpha;
        target.y = startY + deltaY * alpha;
    }
}

void MoveBy::finish () {
    super.finish();
    pool.free(this);
}

gdx_cpp::scenes::scene2d::Action& MoveBy::copy () {
    MoveBy moveBy = $(initialX, initialY, duration);
    if (interpolator != null) moveBy.setInterpolator(interpolator.copy());
    return moveBy;
}

