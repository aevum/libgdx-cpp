
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

#include "MathUtils.hpp"

using namespace gdx_cpp::math;

float MathUtils::sin (float rad) {
    return sin[(int)(rad * radToIndex) & SIN_MASK];
}

float MathUtils::cos (float rad) {
    return cos[(int)(rad * radToIndex) & SIN_MASK];
}

float MathUtils::sinDeg (float deg) {
    return sin[(int)(deg * degToIndex) & SIN_MASK];
}

float MathUtils::cosDeg (float deg) {
    return cos[(int)(deg * degToIndex) & SIN_MASK];
}

float MathUtils::atan2 (float y,float x) {
    float add, mul;
    if (x < 0) {
        if (y < 0) {
            y = -y;
            mul = 1;
        } else
            mul = -1;
        x = -x;
        add = -3.141592653f;
    } else {
        if (y < 0) {
            y = -y;
            mul = -1;
        } else
            mul = 1;
        add = 0;
    }
    float invDiv = 1 / ((x < y ? y : x) * INV_ATAN2_DIM_MINUS_1);
    int xi = (int)(x * invDiv);
    int yi = (int)(y * invDiv);
    return (atan2[yi * ATAN2_DIM + xi] + add) * mul;
}

int MathUtils::random (int range) {
    return random.nextInt(range + 1);
}

int MathUtils::random (int start,int end) {
    return start + random.nextInt(end - start + 1);
}

bool MathUtils::randomBoolean () {
    return random.nextBoolean();
}

float MathUtils::random () {
    return random.nextFloat();
}

float MathUtils::random (float range) {
    return random.nextFloat() * range;
}

float MathUtils::random (float start,float end) {
    return start + random.nextFloat() * (end - start);
}

int MathUtils::nextPowerOfTwo (int value) {
    if (value == 0) return 1;
    value--;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    return value + 1;
}

bool MathUtils::isPowerOfTwo (int value) {
    return value != 0 && (value & value - 1) == 0;
}

int MathUtils::floor (float x) {
    return (int)(x + BIG_ENOUGH_FLOOR) - BIG_ENOUGH_INT;
}

int MathUtils::floorPositive (float x) {
    return (int)x;
}

int MathUtils::ceil (float x) {
    return (int)(x + BIG_ENOUGH_CEIL) - BIG_ENOUGH_INT;
}

int MathUtils::ceilPositive (float x) {
    return (int)(x + CEIL);
}

int MathUtils::round (float x) {
    return (int)(x + BIG_ENOUGH_ROUND) - BIG_ENOUGH_INT;
}

int MathUtils::roundPositive (float x) {
    return (int)(x + 0.5f);
}

