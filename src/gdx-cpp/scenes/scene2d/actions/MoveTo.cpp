
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

#include "MoveTo.hpp"

using namespace gdx::actions;

ActionResetingPool<MoveTo> MoveTo::pool = ActionResetingPool<MoveTo>(4, 100);

MoveTo* MoveTo::build (float x,float y,float duration) {
    MoveTo* action = pool.obtain();
    action->x = x;
    action->y = y;
    action->duration = duration;
    action->invDuration = 1 / duration;
    return action;
}

void MoveTo::setTarget (gdx::Actor* actor) {
    this->target = actor;
    this->startX = target->x;
    this->startY = target->y;
    this->deltaX = x - target->x;
    this->deltaY = y - target->y;
    this->taken = 0;
    this->done = false;
}

void MoveTo::act (float delta) {
    float alpha = createInterpolatedAlpha(delta);
    if (done) {
        target->x = x;
        target->y = y;
    } else {
        target->x = startX + deltaX * alpha;
        target->y = startY + deltaY * alpha;
    }
}

void MoveTo::finish () {
    AnimationAction::finish();
    pool.free(this);
}

gdx::Action* MoveTo::copy () {
    MoveTo* moveTo = MoveTo::build(x, y, duration);
    if (interpolator != NULL) moveTo->setInterpolator(interpolator->copy());
    return moveTo;
}

