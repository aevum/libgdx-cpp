
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

#include "Color.hpp"
#include "gdx-cpp/utils/NumberUtils.hpp"

using namespace gdx_cpp::graphics;

const Color Color::WHITE = Color(1, 1, 1, 1);
const Color Color::BLACK = Color(0, 0, 0, 1);
const Color Color::RED = Color(1, 0, 0, 1);
const Color Color::GREEN = Color(0, 1, 0, 1);
const Color Color::BLUE = Color(0, 0, 1, 1);

Color& Color::set (const Color& color) {
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
    this->a = color.a;
    clamp();
    return *this;
}

Color& Color::mul (const Color& color) {
    this->r *= color.r;
    this->g *= color.g;
    this->b *= color.b;
    this->a *= color.a;
    clamp();
    return *this;
}

Color& Color::mul (float value) {
    this->r *= value;
    this->g *= value;
    this->b *= value;
    this->a *= value;
    clamp();
    return *this;
}

Color& Color::add (const Color& color) {
    this->r += color.r;
    this->g += color.g;
    this->b += color.b;
    this->a += color.a;
    clamp();
    return *this;
}

Color& Color::sub (const Color& color) {
    this->r -= color.r;
    this->g -= color.g;
    this->b -= color.b;
    this->a -= color.a;
    clamp();
    return *this;
}

void Color::clamp () {
    if (r < 0)
        r = 0;
    else if (r > 1) r = 1;

    if (g < 0)
        g = 0;
    else if (g > 1) g = 1;

    if (b < 0)
        b = 0;
    else if (b > 1) b = 1;

    if (a < 0)
        a = 0;
    else if (a > 1) a = 1;
}

void Color::set (float r,float g,float b,float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

bool Color::equals (const Color& o) {
    if (this == &o) return true;

    return o.a == a &&
           o.b == b &&
           o.g == g &&
           o.r == r;
}

int Color::hashCode () {
    int result = (r != +0.0f ? gdx_cpp::utils::NumberUtils::floatToIntBits(r) : 0);
    result = 31 * result + (g != + 0.0f ? gdx_cpp::utils::NumberUtils::floatToIntBits(g) : 0);
    result = 31 * result + (b != + 0.0f ? gdx_cpp::utils::NumberUtils::floatToIntBits(b) : 0);
    result = 31 * result + (a != + 0.0f ? gdx_cpp::utils::NumberUtils::floatToIntBits(a) : 0);
    return result;
}

const std::string Color::toString () {
       //TODO: fix it
    return "FIXME";//;Integer.toHexString(toIntBits());
}

gdx_cpp::graphics::Color gdx_cpp::graphics::Color::fromRgb(unsigned int val)
{
    return Color(((val >> 16) & 0xFF) / 255.f, ((val >> 8) & 0xFF) / 255.f, (val & 0xFF) / 255.f, 1);
}

float Color::toFloatBits (int r,int g,int b,int a) {
    int color = (a << 24) | (b << 16) | (g << 8) | r;
    float floatColor = gdx_cpp::utils::NumberUtils::intBitsToFloat(color & 0xfeffffff);
    return floatColor;
}

int Color::toIntBits (int r,int g,int b,int a) {
    return (a << 24) | (b << 16) | (g << 8) | r;
}

float Color::toFloatBits () const {
    int color = ((int)(255 * a) << 24) | ((int)(255 * b) << 16) | ((int)(255 * g) << 8) | ((int)(255 * r));
    return gdx_cpp::utils::NumberUtils::intBitsToFloat(color & 0xfeffffff);
}

int Color::toIntBits () const {
    int color = ((int)(255 * a) << 24) | ((int)(255 * b) << 16) | ((int)(255 * g) << 8) | ((int)(255 * r));
    return color;
}

float Color::toFloatBits (float r,float g,float b,float a) {
    int color = ((int)(255 * a) << 24) | ((int)(255 * b) << 16) | ((int)(255 * g) << 8) | ((int)(255 * r));
    return gdx_cpp::utils::NumberUtils::intBitsToFloat(color & 0xfeffffff);
}

int Color::alpha (float alpha) {
    return (int)(alpha * 255.0f);
}

int Color::luminanceAlpha (float luminance,float alpha) {
    return ((int)(luminance * 255.0f) << 8) | (int)(alpha * 255);
}

int Color::rgb565 (float r,float g,float b) {
    return ((int)(r * 31) << 11) | ((int)(g * 63) << 5) | (int)(b * 31);
}

int Color::rgba4444 (float r,float g,float b,float a) {
    return ((int)(r * 15) << 12) | ((int)(g * 15) << 8) | ((int)(b * 15) << 4) | (int)(a * 15);
}

int Color::rgb888 (float r,float g,float b) {
    return ((int)(r * 255) << 16) | ((int)(g * 255) << 8) | (int)(b * 255);
}

int Color::rgba8888 (float r,float g,float b,float a) {
    return ((int)(r * 255) << 24) | ((int)(g * 255) << 16) | ((int)(b * 255) << 8) | (int)(a * 255);
}

Color::Color(float r, float g, float b, float a)
  : r(r)
  , g(g)
  , b(b)
  , a(a)
{
    clamp();
}

Color::Color(const Color& color) {
    set(color);
}


