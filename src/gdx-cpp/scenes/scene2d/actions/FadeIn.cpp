
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

#include "FadeIn.hpp"

using namespace gdx_cpp::scenes::scene2d::actions;

ActionResetingPool<FadeIn*> FadeIn::pool = ActionResetingPool<FadeIn*>(4, 100);

FadeIn* FadeIn::operator()(float duration)
{
    FadeIn* action = pool.obtain();
    action->duration = duration;
    action->invDuration = 1 / duration;
    return action;
}

void FadeIn::setTarget (const gdx_cpp::scenes::scene2d::Actor* actor) {
    this->target = actor;
    this->startAlpha = this->target.color.a;
    this->deltaAlpha = 1 - this->target.color.a;
    this->taken = 0;
    this->done = false;
}

void FadeIn::act (float delta) {
    float alpha = createInterpolatedAlpha(delta);
    if (done) {
        target->color.a = 1.0f;
    } else {
        target->color.a = startAlpha + deltaAlpha * alpha;
    }
}

void FadeIn::finish () {
    pool.free(this);
    if (listener != NULL) {
        listener->completed(this);
    }
}

gdx_cpp::scenes::scene2d::Action& FadeIn::copy () {
    FadeIn* fadeIn = FadeIn(duration);
    if (interpolator != NULL) fadeIn->setInterpolator(interpolator.copy());
    return fadeIn;
}

FadeIn::FadeIn()
: startAlpha(0)
, deltaAlpha(0)
, target(0)
{
}