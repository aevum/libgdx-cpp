
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

#include "RotateBy.hpp"

using namespace gdx::actions;

ActionResetingPool<RotateBy> RotateBy::pool = ActionResetingPool<RotateBy>(4, 100);

RotateBy* RotateBy::build (float rotation,float duration) {
    RotateBy* action = pool.obtain();
    action->rotation = rotation;
    action->duration = duration;
    action->invDuration = 1 / duration;
    return action;
}

void RotateBy::setTarget (gdx::Actor* actor) {
    this->target = actor;
    this->startRotation = target->rotation;
    this->deltaRotation = rotation;
    this->taken = 0;
    this->done = false;
}

void RotateBy::act (float delta) {
    float alpha = createInterpolatedAlpha(delta);
    if (done) {
        target->rotation = startRotation + rotation;
    } else {
        target->rotation = startRotation + deltaRotation * alpha;
    }
}

void RotateBy::finish () {
    AnimationAction::finish();
    pool.free(this);
}

gdx::Action* RotateBy::copy () {
    RotateBy* rotateBy = RotateBy::build(rotation, duration);
    if (interpolator != NULL) rotateBy->setInterpolator(interpolator->copy());
    return rotateBy;
}

