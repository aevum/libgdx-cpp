
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

#include "RotateTo.hpp"

using namespace gdx_cpp::scenes::scene2d::actions;

RotateTo& RotateTo::newObject () {
    return new RotateTo();
}

RotateTo& RotateTo::$ (float rotation,float duration) {
    RotateTo action = pool.obtain();
    action.rotation = rotation;
    action.duration = duration;
    action.invDuration = 1 / duration;
    return action;
}

void RotateTo::setTarget (const gdx_cpp::scenes::scene2d::Actor& actor) {
    this.target = actor;
    this.startRotation = target.rotation;
    this.deltaRotation = rotation - target.rotation;
    this.taken = 0;
    this.done = false;
}

void RotateTo::act (float delta) {
    float alpha = createInterpolatedAlpha(delta);
    if (done) {
        target.rotation = rotation;
    } else {
        target.rotation = startRotation + deltaRotation * alpha;
    }
}

void RotateTo::finish () {
    super.finish();
    pool.free(this);
}

gdx_cpp::scenes::scene2d::Action& RotateTo::copy () {
    RotateTo rotateTo = $(rotation, duration);
    if (interpolator != null) rotateTo.setInterpolator(interpolator.copy());
    return rotateTo;
}

