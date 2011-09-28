
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
#include <iostream>
#include <cstdio>

using namespace gdx_cpp::graphics::g2d;
using namespace gdx_cpp;

Gdx2DPixmap::Blending Gdx2DPixmap::blending = SourceOver;

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

graphics::Pixmap::Blending graphics::g2d::Gdx2DPixmap::getBlending()
{
    return blending;
}

void graphics::g2d::Gdx2DPixmap::drawPixmap(const gdx_cpp::graphics::Pixmap& pixmap, int x, int y, int srcx, int srcy, int srcWidth, int srcHeight)
{
    graphics::Pixmap::Blending last = blending;
    setBlend(graphics::Pixmap::None);    
    drawPixmap(pixmap, srcx, srcy, x, y, srcWidth, srcHeight );
    setBlend(last);
}

void graphics::g2d::Gdx2DPixmap::setBlending(const gdx_cpp::graphics::Pixmap::Blending& _blending)
{
    blending = _blending;
}

void graphics::g2d::Gdx2DPixmap::setFilter(const gdx_cpp::graphics::Pixmap::Filter& filter)
{
    setScale(filter == NearestNeighbour ? GDX2D_SCALE_NEAREST : GDX2D_SCALE_LINEAR);
}

void graphics::g2d::Gdx2DPixmap::setStrokeWidth(int width)
{

}

Gdx2DPixmap::Gdx2DPixmap (std::istream& in, int requestedFormat)
        :
        pixData(0)
        ,width(0)
        ,height(0)
        ,format(0)
{

    in.seekg(0, std::ios::end);
    std::ifstream::pos_type filesize = in.tellg();
    in.seekg(0, std::ios::beg);
    
    std::vector<char> bytes(filesize);
    
    in.read(&bytes[0], filesize);
    
    pixData = load((unsigned char*)&bytes[0], 0, filesize, requestedFormat);

    width = pixData->width;
    height = pixData->height;
    format = pixData->format;

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

void Gdx2DPixmap::fill () {
    assert(pixData != NULL);
    if (pixData != NULL) {
        gdx2d_clear(pixData, color);
    }
}

void Gdx2DPixmap::drawPixel (int x,int y) {
    assert(pixData != NULL);
    gdx2d_set_pixel(pixData, x, y, color);
}

int Gdx2DPixmap::getPixel (int x,int y) const {
    assert(pixData != NULL);
    return gdx2d_get_pixel(pixData, x, y);
}

void Gdx2DPixmap::drawLine (int x,int y,int x2,int y2) {
    assert(pixData != NULL);
    gdx2d_draw_line(pixData, x, y, x2, y2, color);
}

void Gdx2DPixmap::drawRectangle (int x,int y,int width,int height) {
    assert(pixData != NULL);
    gdx2d_draw_rect((gdx2d_pixmap*)pixData, x, y, width, height, color);
}

void Gdx2DPixmap::drawCircle (int x,int y,int radius) {
    assert(pixData != NULL);
    gdx2d_draw_circle((gdx2d_pixmap*)pixData, x, y, radius, color);
}

void Gdx2DPixmap::fillRectangle (int x,int y,int width,int height) {
    assert(pixData != NULL);
    gdx2d_fill_rect((gdx2d_pixmap*)pixData, x, y, width, height, color);
}

void Gdx2DPixmap::fillCircle (int x,int y,int radius) {
    assert(pixData != NULL);
    gdx2d_fill_circle((gdx2d_pixmap*)pixData, x, y, radius, color);
}

void Gdx2DPixmap::drawPixmap (const gdx_cpp::graphics::Pixmap& src, int srcX, int srcY, int dstX, int dstY, int width) {
    drawPixmap(src, srcX, srcY, width, height, dstX, dstY, width, height);
}

void Gdx2DPixmap::drawPixmap (const gdx_cpp::graphics::Pixmap& src, int srcX, int srcY, int srcWidth, int srcHeight, int dstX, int dstY, int dstWidth, int dstHeight) {
    assert(pixData != NULL);

    if (src.getType() == graphics::Pixmap::Gdx2d) {    
        gdx2d_draw_pixmap((gdx2d_pixmap*)((Gdx2DPixmap&) src).pixData, (gdx2d_pixmap*)pixData, srcX, srcY, srcWidth, srcHeight, dstX, dstY, dstWidth, dstHeight);
    } else {
        throw std::runtime_error("Unsupported conversion: expected a Gdx2DPixmap");
    }
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

int Gdx2DPixmap::getHeight () const {
    return height;
}

int Gdx2DPixmap::getWidth () const {
    return width;
}

const graphics::Pixmap::Format& Gdx2DPixmap::getFormat () {
    return Pixmap::Format::fromGdx2DPixmapFormat(format);
}

int Gdx2DPixmap::getGLInternalFormat () const {
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
//         ss << "unknown format: " << pixData->format;
        throw std::runtime_error(ss.str());
    }
    }
}

int Gdx2DPixmap::getGLFormat () const {
    return getGLInternalFormat();
}

int Gdx2DPixmap::getGLType () const {
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

void graphics::g2d::Gdx2DPixmap::setColor(float r, float g, float b, float a)
{
    this->color = graphics::Color::rgba8888(r, g, b, a);
}

void graphics::g2d::Gdx2DPixmap::setColor(const gdx_cpp::graphics::Color& color)
{
    this->color = graphics::Color::rgba8888(color.r, color.g, color.b, color.a);
}

void graphics::g2d::Gdx2DPixmap::setScale(float scaleX, float scaleY)
{
    throw std::runtime_error("Unsupported operation");
}

