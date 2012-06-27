
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

#include "OvershootInterpolator.hpp"

using namespace gdx::interpolators;

OvershootInterpolator& OvershootInterpolator::newObject () {
    return new OvershootInterpolator();
}

OvershootInterpolator& OvershootInterpolator::$ (float factor) {
    OvershootInterpolator inter = pool.obtain();
    inter.factor = factor;
    inter.doubledFactor = factor * 2;
    return inter;
}

OvershootInterpolator& OvershootInterpolator::$ () {
    return $(DEFAULT_FACTOR);
}

void OvershootInterpolator::finished () {
    pool.free(this);
}

float OvershootInterpolator::getInterpolation (float t) {
    t -= 1.0f;
    return t * t * ((factor + 1) * t + factor) + 1.0f;
}

gdx::Interpolator& OvershootInterpolator::copy () {
    return $(factor);
}

