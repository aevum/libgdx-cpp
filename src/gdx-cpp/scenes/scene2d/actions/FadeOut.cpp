
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

#include "FadeOut.hpp"

using namespace gdx_cpp::scenes::scene2d::actions;

ActionResetingPool<FadeOut*> FadeOut::pool = ActionResetingPool<FadeOut*>(4, 100);

FadeOut* FadeOut::operator()(float duration)
{
    FadeOut* action = pool.obtain();
    action->duration = duration;
    action->invDuration = 1 / duration;
    return action;
}

void FadeOut::setTarget (const gdx_cpp::scenes::scene2d::Actor& actor) {
    this->target = actor;
    this->startAlpha = target->color.a;
    this->deltaAlpha = -target->color.a;
    this->taken = 0;
    this->done = false;
}

void FadeOut::act (float delta) {
    float alpha = createInterpolatedAlpha(delta);
    if (done) {
        target->color.a = 0.0f;
    } else {
        target->color.a = startAlpha + deltaAlpha * alpha;
    }
}

void FadeOut::finish () {
    AnimationAction::finish();
    pool.free(this);
}

gdx_cpp::scenes::scene2d::Action& FadeOut::copy () {
    FadeOut* fadeOut = FadeOut(duration);
    if (interpolator != NULL) fadeOut->setInterpolator(interpolator->copy());
    return fadeOut;
}

gdx_cpp::scenes::scene2d::actions::FadeOut::FadeOut()
: startAlpha(0)
, deltaAlpha(0)
{
}


