
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

#include "Gdx2DPixmap.hpp"

#include "gdx-cpp/graphics/GL10.hpp"
#include "gdx-cpp/Gdx.hpp"
#include <cassert>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <stdexcept>
#include <sstream>

using namespace gdx_cpp::graphics::g2d;
using namespace gdx_cpp;


//these were the private native Jni-wrapped methods

gdx2d_pixmap* load (unsigned char* buffer, int offset, int len, int requestedFormat) {
    unsigned char* p_buffer = buffer + offset;
    gdx2d_pixmap* pixmap = gdx2d_load(p_buffer, len, requestedFormat);
    return pixmap;
}

gdx2d_pixmap* newPixmap (int width, int height, int format) {
    gdx2d_pixmap* pixmap = gdx2d_new(width, height, format);
    return pixmap;
}

Gdx2DPixmap::Gdx2DPixmap (std::istream& in, int requestedFormat)
        :
        pixData(0)
        ,width(0)
        ,height(0)
        ,format(0)
{

    char* nativeBuffer = (char*) malloc(1024);
    int bufSize = 1024;

    int readBytes = 0;

    while (!in.eof()) {
        in.read(nativeBuffer, 1024);
        readBytes += in.tellg();
        while (readBytes >= bufSize) {
            nativeBuffer = (char*) realloc(nativeBuffer, bufSize * 2);
            bufSize *= 2;
        }
    }

    pixData = load((unsigned char*)nativeBuffer, 0, readBytes, requestedFormat);

    width = pixData->width;
    height = pixData->height;
    format = pixData->format;

    free(nativeBuffer);

    if (pixData == NULL) {
        throw std::runtime_error("couldn't load pixmap");

    }
}

Gdx2DPixmap::Gdx2DPixmap (int width, int height, int format)
        : pixData(0)
        ,width(width)
        ,height(height)
        ,format(format)
{
    pixData = ::newPixmap(width, height, format);
    assert(pixData);
}

Gdx2DPixmap::Gdx2DPixmap (const Gdx2DPixmap& other)
        : pixData(0)
{
    this->pixData =  (gdx2d_pixmap*) malloc(sizeof(gdx2d_pixmap));
    memcpy(this->pixData, other.pixData, sizeof(gdx2d_pixmap));

    this->width = pixData->width;
    this->height = pixData->height;
    this->format = pixData->format;
}

Gdx2DPixmap::Gdx2DPixmap (unsigned char* encodedData, int offset, int len, int requestedFormat)
        : pixData(0)
{
    this->pixData = load(encodedData, offset, len, requestedFormat);
    this->width = pixData->width;
    this->height = pixData->height;
    this->format = pixData->format;

    if (!pixData) {
        throw std::runtime_error("Failed loading pixmap");
    }
}

graphics::g2d::Gdx2DPixmap::~Gdx2DPixmap()
{
    dispose();
}

void graphics::g2d::Gdx2DPixmap::setBlend(int blend)
{
    gdx2d_set_blend(blend);
}

void graphics::g2d::Gdx2DPixmap::setScale(int scale)
{
    gdx2d_set_scale(scale);
}


void Gdx2DPixmap::dispose () {
    if (pixData != NULL) {
        gdx2d_free(pixData);
        pixData = NULL;
    }
}

void Gdx2DPixmap::clear (int color) {
    assert(pixData != NULL);
    if (pixData != NULL) {
        gdx2d_clear(pixData, color);
    }
}

void Gdx2DPixmap::setPixel (int x,int y,int color) {
    assert(pixData != NULL);
    gdx2d_set_pixel(pixData, x, y, color);
}

int Gdx2DPixmap::getPixel (int x,int y) {
    assert(pixData != NULL);
    return gdx2d_get_pixel(pixData, x, y);
}

void Gdx2DPixmap::drawLine (int x,int y,int x2,int y2,int color) {
    assert(pixData != NULL);
    gdx2d_draw_line(pixData, x, y, x2, y2, color);
}

void Gdx2DPixmap::drawRect (int x,int y,int width,int height,int color) {
    assert(pixData != NULL);
    gdx2d_draw_rect((gdx2d_pixmap*)pixData, x, y, width, height, color);
}

void Gdx2DPixmap::drawCircle (int x,int y,int radius,int color) {
    assert(pixData != NULL);
    gdx2d_draw_circle((gdx2d_pixmap*)pixData, x, y, radius, color);
}

void Gdx2DPixmap::fillRect (int x,int y,int width,int height,int color) {
    assert(pixData != NULL);
    gdx2d_fill_rect((gdx2d_pixmap*)pixData, x, y, width, height, color);
}

void Gdx2DPixmap::fillCircle (int x,int y,int radius,int color) {
    assert(pixData != NULL);
    gdx2d_fill_circle((gdx2d_pixmap*)pixData, x, y, radius, color);
}

void Gdx2DPixmap::drawPixmap (const Gdx2DPixmap& src, int srcX, int srcY, int dstX, int dstY, int width, int height) {
    drawPixmap(src, srcX, srcY, width, height, dstX, dstY, width, height);
}

void Gdx2DPixmap::drawPixmap (const Gdx2DPixmap& src,int srcX,int srcY,int srcWidth,int srcHeight,int dstX,int dstY,int dstWidth,int dstHeight) {
    assert(pixData != NULL);
    gdx2d_draw_pixmap((gdx2d_pixmap*)src.pixData, (gdx2d_pixmap*)pixData, srcX, srcY, srcWidth, srcHeight, dstX, dstY, dstWidth, dstHeight);
}

graphics::g2d::Gdx2DPixmap* Gdx2DPixmap::newPixmap (std::istream& in, int requestedFormat) {
    return new Gdx2DPixmap(in, requestedFormat);
}

graphics::g2d::Gdx2DPixmap* Gdx2DPixmap::newPixmap (int width, int height, int format) {
    return new Gdx2DPixmap(width, height, format);
}

const unsigned char* Gdx2DPixmap::getPixels () {
    assert(pixData != NULL);
    return pixData->pixels;
}

int Gdx2DPixmap::getHeight () {
    return height;
}

int Gdx2DPixmap::getWidth () {
    return width;
}

int Gdx2DPixmap::getFormat () {
    return format;
}

int Gdx2DPixmap::getGLInternalFormat () {
    using namespace gdx_cpp::graphics;

    switch (pixData->format) {
    case GDX2D_FORMAT_ALPHA:
        return GL10::GL_ALPHA;
    case GDX2D_FORMAT_LUMINANCE_ALPHA:
        return GL10::GL_LUMINANCE_ALPHA;
    case GDX2D_FORMAT_RGB888:
    case GDX2D_FORMAT_RGB565:
        return GL10::GL_RGB;
    case GDX2D_FORMAT_RGBA8888:
    case GDX2D_FORMAT_RGBA4444:
        return GL10::GL_RGBA;
    default:
    {
        std::stringstream ss;
        ss << "unknown format: " << pixData->format;
        throw std::runtime_error(ss.str());
    }
    }
}

int Gdx2DPixmap::getGLFormat () {
    return getGLInternalFormat();
}

int Gdx2DPixmap::getGLType () {
    using namespace gdx_cpp::graphics;
    switch (pixData->format) {
    case GDX2D_FORMAT_ALPHA:
    case GDX2D_FORMAT_LUMINANCE_ALPHA:
    case GDX2D_FORMAT_RGB888:
    case GDX2D_FORMAT_RGBA8888:
        return GL10::GL_UNSIGNED_BYTE;
    case GDX2D_FORMAT_RGB565:
        return GL10::GL_UNSIGNED_SHORT_5_6_5;
    case GDX2D_FORMAT_RGBA4444:
        return GL10::GL_UNSIGNED_SHORT_4_4_4_4;
    default:
    {
        std::stringstream ss;
        ss << "unknown format: " << pixData->format;
        throw std::runtime_error(ss.str());
    }
    }
}

const std::string Gdx2DPixmap::getFormatString () {
    switch (pixData->format) {
    case GDX2D_FORMAT_ALPHA:
        return "alpha";
    case GDX2D_FORMAT_LUMINANCE_ALPHA:
        return "luminance alpha";
    case GDX2D_FORMAT_RGB888:
        return "rgb888";
    case GDX2D_FORMAT_RGBA8888:
        return "rgba8888";
    case GDX2D_FORMAT_RGB565:
        return "rgb565";
    case GDX2D_FORMAT_RGBA4444:
        return "rgba4444";
    default:
        return "unknown";
    }
}

