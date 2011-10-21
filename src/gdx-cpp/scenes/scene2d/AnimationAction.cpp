
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

#include "AnimationAction.hpp"

using namespace gdx_cpp::scenes::scene2d;

bool AnimationAction::isDone () {
    return done;
}

void AnimationAction::finish () {
    Action::finish();
    if (interpolator != NULL) {
        interpolator->finished();
    }
}

AnimationAction& AnimationAction::setInterpolator (const Interpolator* interpolator) {
    this->interpolator = interpolator;
    return this;
}

float AnimationAction::createInterpolatedAlpha (float delta) {
    taken += delta;
    if (taken >= duration) {
        taken = duration;
        done = true;
        return taken;
    } else if (interpolator == NULL) {
        return taken * invDuration;
    } else {
        float interpolatedTime = interpolator->getInterpolation(taken / duration) * duration;
        return interpolatedTime * invDuration;
    }
}

gdx_cpp::scenes::scene2d::Actor* AnimationAction::getTarget () {
    return target;
}

void AnimationAction::reset () {
    Action::reset();
    interpolator = NULL;
}

AnimationAction::AnimationAction()
 : target(0)
{

}
