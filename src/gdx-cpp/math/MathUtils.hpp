/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 */


#ifndef GDX_CPP_MATH_MATHUTILS_H
#define GDX_CPP_MATH_MATHUTILS_H

#include <cstdlib>
#include <cmath>

#define SIN_BITS 13
#define SIN_MASK ~(-1 << SIN_BITS)
#define SIN_COUNT SIN_MASK + 1

#define radFull (PI * 2)
#define degFull 360
#define radToIndex SIN_COUNT / radFull
#define degToIndex SIN_COUNT / degFull

#define radiansToDegrees 180.0 / 3.1415927
#define degreesToRadians  math::utils::PI / 180

#include "gdx-cpp/utils/NumberUtils.hpp"

namespace gdx_cpp {

namespace math {

namespace utils {

const double PI = 4.0 * std::atan(1);
static float _sin[SIN_COUNT];
static float _cos[SIN_COUNT];
static int BIG_ENOUGH_INT = 16 * 1024;
static double BIG_ENOUGH_FLOOR = BIG_ENOUGH_INT;
static double CEIL = 0.9999999;
static double BIG_ENOUGH_CEIL = gdx_cpp::utils::NumberUtils::longBitsToDouble(gdx_cpp::utils::NumberUtils::doubleToLongBits(BIG_ENOUGH_INT + 1) - 1);
static double BIG_ENOUGH_ROUND = BIG_ENOUGH_INT + 0.5f;

float toDegrees(float radians) {
    return radians * (180.0 / PI);
}

float toRadians(float degrees) {
    return degrees * (PI / 180.0);
}


float signum(float value) {
    return value < 0 ? -1 : (value == 0 ? 0 : 1);
}

float sin (float rad) {
    return utils::_sin[(int)(rad * radToIndex) & SIN_MASK];
}

float cos (float rad) {
    return utils::_cos[(int)(rad * radToIndex) & SIN_MASK];
}

float sinDeg (float deg) {
    return utils::_sin[(int)(deg * degToIndex) & SIN_MASK];
}

float cosDeg (float deg) {
    return utils::_cos[(int)(deg * degToIndex) & SIN_MASK];
}

namespace detail {

// Adjust for accuracy.
#define ATAN2_BITS 7
#define ATAN2_BITS2 ATAN2_BITS << 1
#define ATAN2_MASK (~(-1 << ATAN2_BITS2))
#define ATAN2_COUNT ATAN2_MASK + 1
#define INV_ATAN2_DIM_MINUS_1 1.0 / (detail::ATAN2_DIM - 1)

static const int ATAN2_DIM ((int) std::sqrt((float)ATAN2_COUNT));
static float _atan2[ATAN2_COUNT];

struct calc_atan {
    calc_atan() {
        for (int i = 0; i < ATAN2_DIM; i++) {
            for (int j = 0; j < ATAN2_DIM; j++) {
                float x0 = (float)i / detail::ATAN2_DIM;
                float y0 = (float)j / detail::ATAN2_DIM;
                detail::_atan2[j * detail::ATAN2_DIM + i] = (float)std::atan2(y0, x0);
            }
        }
    }
} atan;

struct calc_sin {
    calc_sin() {
        for (int i = 0; i < SIN_COUNT; ++i) {
            float a = (i + 0.5f) / SIN_COUNT * radFull;
            utils::_sin[i] = (float) std::sin(a);
            utils::_cos[i] = (float) std::cos(a);
        }
        for (int i = 0; i < 360; i += 90) {
            utils::_sin[(int)(i * degToIndex) & SIN_MASK] = (float) std::sin(i * degreesToRadians);
            utils::_cos[(int)(i * degToIndex) & SIN_MASK] = (float) std::cos(i * degreesToRadians);
        }

    }
} calc;

}

float atan2 (float y, float x) {
    float add = 0, mul = 0;
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
    return (detail::_atan2[yi * detail::ATAN2_DIM + xi] + add) * mul;
}

/** Returns a random number between 0 (inclusive) and the specified value (inclusive). */
int random (int range) {
    return std::rand() % range + 1;
}

int random (int start, int end) {
    return start + random(end - start + 1);
}

bool randomBoolean () {
    return std::rand() % 2;
}

float random () {
    return ( std::rand() / (static_cast<float>(RAND_MAX) + 1.0));
}

float random (float range) {
    return utils::random() * range;
}

float random(float low, float high)
{
    double temp;

    /* swap low & high around if the user makes no sense */
    if (low > high)
    {
        temp = low;
        low = high;
        high = temp;
    }

    /* calculate the random number & return it */
    temp = utils::random() * (high - low) + low;
    return temp;
}

int nextPowerOfTwo (int value) {
    if (value == 0) return 1;
    value--;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    return value + 1;
}

bool isPowerOfTwo (int value) {
    return value != 0 && (value & value - 1) == 0;
}

int floor (float x) {
    return (int)(x + BIG_ENOUGH_FLOOR) - BIG_ENOUGH_INT;
}

int floorPositive (float x) {
    return (int)x;
}

int ceil (float x) {
    return (int)(x + BIG_ENOUGH_CEIL) - BIG_ENOUGH_INT;
}

int ceilPositive (float x) {
    return (int)(x + CEIL);
}

int round (float x) {
    return (int)(x + BIG_ENOUGH_ROUND) - BIG_ENOUGH_INT;
}

int roundPositive (float x) {
    return (int)(x + 0.5f);
}

}
}
}
#endif // GDX_CPP_MATH_MATHUTILS_H

