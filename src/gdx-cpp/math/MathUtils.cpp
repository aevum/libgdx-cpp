#include <cmath>

#include "MathUtils.hpp"
#include "gdx-cpp/utils/NumberUtils.hpp"

using namespace gdx;


detail::detail() {
    for (int i = 0; i < ATAN2_DIM; i++) {
        for (int j = 0; j < ATAN2_DIM; j++) {
            double x0 = (double)i / detail::ATAN2_DIM;
            double y0 = (double)j / detail::ATAN2_DIM;
            detail::_atan2[j * detail::ATAN2_DIM + i] = (float)std::atan2(y0, x0);
        }
    }

    for (int i = 0; i < SIN_COUNT; ++i) {
        double a = (i + 0.5f) / SIN_COUNT * radFull;
        _sin[i] = (float) std::sin(a);
        _cos[i] = (float) std::cos(a);
    }
    
    for (int i = 0; i < 360; i += 90) {
        _sin[(int)(i * degToIndex) & SIN_MASK] = (float) std::sin((double)(i * degreesToRadians));
        _cos[(int)(i * degToIndex) & SIN_MASK] = (float) std::cos((double)(i * degreesToRadians));
    }
}

detail __detail;

const float detail::PI = 3.14159265f;
const int detail::SIN_BITS = 13;
const int detail::SIN_MASK = ~(-1 << SIN_BITS);
const int detail::SIN_COUNT = (SIN_MASK + 1);

const float detail::radFull = (detail::PI * 2.0f);
const float detail::degFull = 360.0f;
const float detail::radToIndex = (detail::SIN_COUNT / detail::radFull);
const float detail::degToIndex = (detail::SIN_COUNT / detail::degFull);

const float detail::radiansToDegrees = (180.0f / 3.1415927f);
const float detail::degreesToRadians = (detail::PI / 180.f);

const int detail::ATAN2_BITS = 7;
const int detail::ATAN2_BITS2 = 14;
const int detail::ATAN2_MASK  = 16383;
const int detail::ATAN2_COUNT = 16384;
const float detail::INV_ATAN2_DIM_MINUS_1 = (1.0f / (detail::ATAN2_DIM - 1));

float detail::_sin[SIN_COUNT];
float detail::_cos[SIN_COUNT];
const int detail::BIG_ENOUGH_INT = 16 * 1024;
const float detail::BIG_ENOUGH_FLOOR = detail::BIG_ENOUGH_INT;
const float detail::CEIL = 0.9999999;
const float detail::BIG_ENOUGH_CEIL = NumberUtils::longBitsToDouble(NumberUtils::doubleToLongBits(detail::BIG_ENOUGH_INT + 1) - 1);
const float detail::BIG_ENOUGH_ROUND = detail::BIG_ENOUGH_INT + 0.5f;
const int detail::ATAN2_DIM = 128;
float detail::_atan2[ATAN2_COUNT];
