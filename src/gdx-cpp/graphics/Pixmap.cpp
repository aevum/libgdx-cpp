
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

#include "Pixmap.hpp"

#include "gdx-cpp/graphics/g2d/Gdx2DPixmap.hpp"
#include "Color.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/files/FileHandle.hpp"

#include <cassert>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <iostream>

using namespace gdx_cpp::graphics;

Pixmap::Blending Pixmap::blending = SourceOver;

const Pixmap::Format Pixmap::Format::Alpha = Pixmap::Format("Alpha");
const Pixmap::Format Pixmap::Format::LuminanceAlpha = Pixmap::Format("LuminanceAlpha");
const Pixmap::Format Pixmap::Format::RGB565 = Pixmap::Format("RGB565");
const Pixmap::Format Pixmap::Format::RGBA4444 = Pixmap::Format("RGBA4444");
const Pixmap::Format Pixmap::Format::RGB888 = Pixmap::Format("RGB888");
const Pixmap::Format Pixmap::Format::RGBA8888 = Pixmap::Format("RGBA888");

void Pixmap::setBlending (const Blending& blending) {
    Pixmap::blending = blending;
    g2d::Gdx2DPixmap::setBlend(blending == Pixmap::None ? 0 : 1);
}

void Pixmap::setFilter (const Filter& filter) {
    g2d::Gdx2DPixmap::setScale(filter == NearestNeighbour ? GDX2D_SCALE_NEAREST : g2d::Gdx2DPixmap::GDX2D_SCALE_LINEAR);
}

void Pixmap::setColor (float r,float g,float b,float a) {
    color = Color::rgba8888(r, g, b, a);
}

void Pixmap::setColor (const Color& color) {
    this->color = Color::rgba8888(color.r, color.g, color.b, color.a);
}

void Pixmap::fill () {
    pixmap->clear(color);
}

void Pixmap::drawLine (int x,int y,int x2,int y2) {
    pixmap->drawLine(x, y, x2, y2, color);
}

void Pixmap::drawRectangle (int x,int y,int width,int height) {
    pixmap->drawRect(x, y, width, height, color);
}

void Pixmap::drawPixmap (const Pixmap& pixmap,int x,int y,int srcx,int srcy,int srcWidth,int srcHeight) {
    this->pixmap->drawPixmap(*pixmap.pixmap, srcx, srcy, x, y, srcWidth, srcHeight);
}

void Pixmap::drawPixmap (const Pixmap& pixmap,int srcx,int srcy,int srcWidth,int srcHeight,int dstx,int dsty,int dstWidth,int dstHeight) {
    this->pixmap->drawPixmap(*pixmap.pixmap, srcx, srcy, srcWidth, srcHeight, dstx, dsty, dstWidth, dstHeight);
}

void Pixmap::fillRectangle (int x,int y,int width,int height) {
    pixmap->fillRect(x, y, width, height, color);
}

void Pixmap::drawCircle (int x,int y,int radius) {
    pixmap->drawCircle(x, y, radius, color);
}

void Pixmap::fillCircle (int x,int y,int radius) {
    pixmap->fillCircle(x, y, radius, color);
}

int Pixmap::getPixel (int x, int y) const {
    return pixmap->getPixel(x, y);
}

int Pixmap::getWidth () const {
    return pixmap->getWidth();
}

int Pixmap::getHeight () const {
    return pixmap->getHeight();
}

void Pixmap::dispose () {
    std::cout << "called dispose" << std::endl;
    pixmap->dispose();
}

void Pixmap::drawPixel (int x,int y) {
    pixmap->setPixel(x, y, color);
}

int Pixmap::getGLFormat () const {
    return pixmap->getGLFormat();
}

int Pixmap::getGLInternalFormat () const {
    return pixmap->getGLInternalFormat();
}

int Pixmap::getGLType () const {
    return pixmap->getGLType();
}

const unsigned char* Pixmap::getPixels () const {
    return pixmap->getPixels();
}

const gdx_cpp::graphics::Pixmap::Format& Pixmap::getFormat () {
    return Format::fromGdx2DPixmapFormat(pixmap->getFormat());
}

Pixmap::Blending Pixmap::getBlending () {
    return blending;
}

int Pixmap::Format::toGdx2DPixmapFormat(const gdx_cpp::graphics::Pixmap::Format& format) {
    if (format == Pixmap::Format::Alpha) return GDX2D_FORMAT_ALPHA;
    if (format == Pixmap::Format::LuminanceAlpha) return GDX2D_FORMAT_LUMINANCE_ALPHA;
    if (format == Pixmap::Format::RGB565) return GDX2D_FORMAT_RGB565;
    if (format == Pixmap::Format::RGBA4444) return GDX2D_FORMAT_RGBA4444;
    if (format == Pixmap::Format::RGB888) return GDX2D_FORMAT_RGB888;
    if (format == Pixmap::Format::RGBA8888) return GDX2D_FORMAT_RGBA8888;

    std::stringstream ss;
    ss << "Unknown Format: " << format.toString();
    throw std::runtime_error(ss.str());
}

const Pixmap::Format& Pixmap::Format::fromGdx2DPixmapFormat(int format) {
    if (format == GDX2D_FORMAT_ALPHA) return Pixmap::Format::Alpha;
    if (format == GDX2D_FORMAT_LUMINANCE_ALPHA) return Pixmap::Format::LuminanceAlpha;
    if (format == GDX2D_FORMAT_RGB565) return Pixmap::Format::RGB565;
    if (format == GDX2D_FORMAT_RGBA4444) return Pixmap::Format::RGBA4444;
    if (format == GDX2D_FORMAT_RGB888) return Pixmap::Format::RGB888;
    if (format == GDX2D_FORMAT_RGBA8888) return Pixmap::Format::RGBA8888;

    std::stringstream ss;
    ss << "Unknown Gdx2DPixmap Format: " << format;
    throw std::runtime_error(ss.str());
}

Pixmap::Pixmap(int width, int height, const gdx_cpp::graphics::Pixmap::Format& format)
        : color(0)
{
    pixmap = g2d::Gdx2DPixmap::newPixmap(width, height, Format::toGdx2DPixmapFormat(format));
    assert(pixmap);
    setColor(0, 0, 0, 0);
    fill();
}

Pixmap::Pixmap(unsigned char* encodedData, int offset, int len) {
    pixmap = new g2d::Gdx2DPixmap(encodedData, offset, len, 0);
}

Pixmap::Pixmap(gdx_cpp::files::FileHandle& file) {

    std::cout << "CRIANDO PIXMAP" << std::endl;
    gdx_cpp::files::FileHandle::char_ptr bytes;
    int size = file.readBytes(bytes);
    std::cout << "TERMINOU DE LER OS BYTES FORAM LIDOS" << size << std::endl;
    pixmap = new g2d::Gdx2DPixmap((unsigned char*) bytes.get(), 0, size, 0);
    std::cout << "TERMINOU DE CRIAR O Gdx2DPixmap" << std::endl;
    assert(pixmap);
}

Pixmap::Pixmap(g2d::Gdx2DPixmap* pixmap)
 : color(0)
 {
    this->pixmap = pixmap;
}

void gdx_cpp::graphics::Pixmap::setStrokeWidth(int width)
{
}

gdx_cpp::graphics::Pixmap::~Pixmap()
{
    delete this->pixmap;
}


