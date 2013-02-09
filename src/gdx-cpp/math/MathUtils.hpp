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

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "gdx-cpp/utils/NumberUtils.hpp"

namespace gdx {

struct detail {
    static const float PI;
    static const int SIN_BITS;
    static const int SIN_MASK;
    static const int SIN_COUNT;
    
    static const float radFull;
    static const float degFull;
    static const float radToIndex;
    static const float degToIndex;
    
    static const float radiansToDegrees;
    static const float degreesToRadians;
    
    static const int ATAN2_BITS;
    static const int ATAN2_BITS2;
    static const int ATAN2_MASK;
    static const int ATAN2_COUNT;
    static const float INV_ATAN2_DIM_MINUS_1;
    
    static float _sin[];
    static float _cos[];
    static const int BIG_ENOUGH_INT;
    static const float BIG_ENOUGH_FLOOR;
    static const float CEIL;
    static const float BIG_ENOUGH_CEIL;
    static const float BIG_ENOUGH_ROUND;

    static const int ATAN2_DIM;
    static float _atan2[];

    detail () ;
};

inline float toDegrees(float radians) {
    return radians * (180.0f / detail::PI);
}

inline float toRadians(float degrees) {
    return degrees * (detail::PI / 180.0f);
}

inline float signum(float value) {
    return value < 0.0f ? -1.0f : (value == 0.0f ? 0.0f : 1.0f);
}

inline float sin (float rad) {
    return detail::_sin[(int)(rad * detail::radToIndex) & detail::SIN_MASK];
}

inline float cos (float rad) {
    return detail::_cos[(int)(rad * detail::radToIndex) & detail::SIN_MASK];
}

inline float sinDeg (float deg) {
    return detail::_sin[(int)(deg * detail::degToIndex) & detail::SIN_MASK];
}

inline float cosDeg (float deg) {
    return detail::_cos[(int)(deg * detail::degToIndex) & detail::SIN_MASK];
}

inline float atan2 (float y, float x) {
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
    float invDiv = 1 / ((x < y ? y : x) * detail::INV_ATAN2_DIM_MINUS_1);
    int xi = (int)(x * invDiv);
    int yi = (int)(y * invDiv);
    return (detail::_atan2[yi * detail::ATAN2_DIM + xi] + add) * mul;
}

/** Returns a random number between 0 (inclusive) and the specified value (inclusive). */
inline int random (int range) {
    return std::rand() % (range + 1);
}

inline int random (int start, int end) {
    return start + random(end - start);
}

inline bool randomBoolean () {
    return std::rand() % 2;
}

inline float random () {
    return ( std::rand() / (static_cast<float>(RAND_MAX) + 1.0f));
}

inline float random (float range) {
    return random() * range;
}

inline float random(float low, float high)
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
    temp = random() * (high - low) + low;
    return temp;
}

inline int nextPowerOfTwo (int value) {
    if (value == 0) return 1;
    value--;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    return value + 1;
}

inline bool isPowerOfTwo (int value) {
    return value != 0 && (value & (value - 1)) == 0;
}

inline int floor (float x) {
    return (int)(x + detail::BIG_ENOUGH_FLOOR) - detail::BIG_ENOUGH_INT;
}

inline int floorPositive (float x) {
    return (int)x;
}

inline int ceil (float x) {
    return (int)(x + detail::BIG_ENOUGH_CEIL) - detail::BIG_ENOUGH_INT;
}

inline int ceilPositive (float x) {
    return (int)(x + detail::CEIL);
}

inline int round (float x) {
    return (int)(x + detail::BIG_ENOUGH_ROUND) - detail::BIG_ENOUGH_INT;
}

inline int roundPositive (float x) {
    return (int)(x + 0.5f);
}

}
#endif // GDX_CPP_MATH_MATHUTILS_H

