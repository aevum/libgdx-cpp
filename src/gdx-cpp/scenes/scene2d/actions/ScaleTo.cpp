
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

#include "ScaleTo.hpp"

using namespace gdx::actions;

ActionResetingPool<ScaleTo> ScaleTo::pool = ActionResetingPool<ScaleTo>(4, 100);

ScaleTo* ScaleTo::build (float scaleX,float scaleY,float duration) {
    ScaleTo* action = pool.obtain();
    action->scaleX = scaleX;
    action->scaleY = scaleY;
    action->duration = duration;
    action->invDuration = 1 / duration;
    return action;
}

void ScaleTo::setTarget (gdx::Actor* actor) {
    this->target = actor;
    this->startScaleX = target->scaleX;
    this->deltaScaleX = scaleX - target->scaleX;
    this->startScaleY = target->scaleY;
    this->deltaScaleY = scaleY - target->scaleY;
    this->taken = 0;
    this->done = false;
}

void ScaleTo::act (float delta) {
    float alpha = createInterpolatedAlpha(delta);
    if (done) {
        target->scaleX = scaleX;
        target->scaleY = scaleY;
    } else {
        target->scaleX = startScaleX + deltaScaleX * alpha;
        target->scaleY = startScaleY + deltaScaleY * alpha;
    }
}

void ScaleTo::finish () {
    AnimationAction::finish();
    pool.free(this);
}

gdx::Action* ScaleTo::copy () {
    ScaleTo* scaleTo = ScaleTo::build(scaleX, scaleY, duration);
    if (interpolator != NULL) scaleTo->setInterpolator(interpolator->copy());
    return scaleTo;
}

