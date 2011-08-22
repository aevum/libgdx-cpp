
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

using namespace gdx_cpp::graphics;

void Pixmap::setBlending (const Blending& blending) {
    Pixmap.blending = blending;
    Gdx2DPixmap.setBlend(blending == Blending.None ? 0 : 1);
}

void Pixmap::setFilter (const Filter& filter) {
    Gdx2DPixmap.setScale(filter == Filter.NearestNeighbour ? Gdx2DPixmap.GDX2D_SCALE_NEAREST : Gdx2DPixmap.GDX2D_SCALE_LINEAR);
}

void Pixmap::setColor (float r,float g,float b,float a) {
    color = Color.rgba8888(r, g, b, a);
}

void Pixmap::setColor (const Color& color) {
    this.color = Color.rgba8888(color.r, color.g, color.b, color.a);
}

void Pixmap::fill () {
    pixmap.clear(color);
}

void Pixmap::setStrokeWidth (int width);

/** Draws a line between the given coordinates using the currently set color.
 *
 * @param x The x-coodinate of the first point
 * @param y The y-coordinate of the first point
 * @param x2 The x-coordinate of the first point
 * @param y2 The y-coordinate of the first point */
public void drawLine (int x, int y, int x2, int y2) {
    pixmap.drawLine(x, y, x2, y2, color);
}

void Pixmap::drawLine (int x,int y,int x2,int y2) {
    pixmap.drawLine(x, y, x2, y2, color);
}

void Pixmap::drawRectangle (int x,int y,int width,int height) {
    pixmap.drawRect(x, y, width, height, color);
}

void Pixmap::drawPixmap (const Pixmap& pixmap,int x,int y,int srcx,int srcy,int srcWidth,int srcHeight) {
    this.pixmap.drawPixmap(pixmap.pixmap, srcx, srcy, x, y, srcWidth, srcHeight);
}

void Pixmap::drawPixmap (const Pixmap& pixmap,int srcx,int srcy,int srcWidth,int srcHeight,int dstx,int dsty,int dstWidth,int dstHeight) {
    this.pixmap.drawPixmap(pixmap.pixmap, srcx, srcy, srcWidth, srcHeight, dstx, dsty, dstWidth, dstHeight);
}

void Pixmap::fillRectangle (int x,int y,int width,int height) {
    pixmap.fillRect(x, y, width, height, color);
}

void Pixmap::drawCircle (int x,int y,int radius) {
    pixmap.drawCircle(x, y, radius, color);
}

void Pixmap::fillCircle (int x,int y,int radius) {
    pixmap.fillCircle(x, y, radius, color);
}

int Pixmap::getPixel (int x,int y) {
    return pixmap.getPixel(x, y);
}

int Pixmap::getWidth () {
    return pixmap.getWidth();
}

int Pixmap::getHeight () {
    return pixmap.getHeight();
}

void Pixmap::dispose () {
    pixmap.dispose();
}

void Pixmap::drawPixel (int x,int y) {
    pixmap.setPixel(x, y, color);
}

int Pixmap::getGLFormat () {
    return pixmap.getGLFormat();
}

int Pixmap::getGLInternalFormat () {
    return pixmap.getGLInternalFormat();
}

int Pixmap::getGLType () {
    return pixmap.getGLType();
}

ByteBuffer& Pixmap::getPixels () {
    return pixmap.getPixels();
}

Format& Pixmap::getFormat () {
    return Format.fromGdx2DPixmapFormat(pixmap.getFormat());
}

Blending& Pixmap::getBlending () {
    return blending;
}

