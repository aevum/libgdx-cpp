
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

#include "AccelerateInterpolator.hpp"

using namespace gdx_cpp::scenes::scene2d::interpolators;

AccelerateInterpolator& AccelerateInterpolator::newObject () {
    return new AccelerateInterpolator();
}

AccelerateInterpolator& AccelerateInterpolator::$ (float factor) {
    AccelerateInterpolator inter = pool.obtain();
    inter.factor = factor;
    inter.doubledFactor = factor * 2;
    return inter;
}

AccelerateInterpolator& AccelerateInterpolator::$ () {
    return $(DEFAULT_FACTOR);
}

void AccelerateInterpolator::finished () {
    pool.free(this);
}

float AccelerateInterpolator::getInterpolation (float input) {
    if (factor == 1.0f) {
        return input * input;
    } else {
        return (float)Math.pow(input, doubledFactor);
    }
}

gdx_cpp::scenes::scene2d::Interpolator& AccelerateInterpolator::copy () {
    return $(factor);
}

