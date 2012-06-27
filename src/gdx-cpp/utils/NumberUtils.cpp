
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

#include "NumberUtils.hpp"

#include <string.h>

using namespace gdx;

uint32_t NumberUtils::floatToIntBits (float value) {
    uint32_t y;
    memcpy(&y, &value, sizeof(uint32_t));
    return y;
}

int NumberUtils::floatToRawIntBits (float value) {
    union {
        int i;
        float f;
    } u;
    u.f = (float)value;
    return u.i;
}

float NumberUtils::intBitsToFloat (int value) {
    union {
        float f;  // assuming 32-bit IEEE 754 single-precision
        int i;    // assuming 32-bit 2's complement int
    } u;

    u.i = value;
    return u.f;
}

long NumberUtils::doubleToLongBits (double value) {
  union { double f; uint64_t i; } u;
  u.f = value;
  return u.i;
}

double NumberUtils::longBitsToDouble (long value) {
  union { double f; uint64_t i; } u;
  u.i = value;
  return u.i;
}

