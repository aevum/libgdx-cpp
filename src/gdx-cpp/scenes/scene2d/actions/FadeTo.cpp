
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

#include "FadeTo.hpp"

using namespace gdx_cpp::scenes::scene2d::actions;

ActionResetingPool<FadeTo*> FadeTo::pool = ActionResetingPool<FadeTo*>(4, 100);

FadeTo* FadeTo::operator () (float alpha,float duration) {
    FadeTo* action = pool.obtain();
    action->toAlpha = std::min(std::max(alpha, 0.0f), 1.0f);
    action->duration = duration;
    action->invDuration = 1 / duration;
    return action;
}

void FadeTo::setTarget (const gdx_cpp::scenes::scene2d::Actor& actor) {
    this->target = actor;
    this->startAlpha = this->target->color.a;
    this->deltaAlpha = toAlpha - this->target->color.a;
    this->taken = 0;
    this->done = false;
}

void FadeTo::act (float delta) {
    float alpha = createInterpolatedAlpha(delta);
    if (done) {
        target->color.a = toAlpha;
    } else {
        float val = startAlpha + deltaAlpha * alpha;
        target->color.a = std::min(std::max(val, 0.0f), 1.0f);
    }
}

void FadeTo::finish () {
    AnimationAction::finish();
    pool.free(this);
}

gdx_cpp::scenes::scene2d::Action& FadeTo::copy () {
    FadeTo* fadeTo = FadeTo(toAlpha, duration);
    if (interpolator != NULL) fadeTo->setInterpolator(interpolator->copy());
    return fadeTo;
}

