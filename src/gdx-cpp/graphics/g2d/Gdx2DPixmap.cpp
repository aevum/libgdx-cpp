
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

using namespace gdx_cpp::graphics::g2d;

void Gdx2DPixmap::dispose () {
    free(basePtr);
}

void Gdx2DPixmap::clear (int color) {
    clear(basePtr, color);
}

void Gdx2DPixmap::setPixel (int x,int y,int color) {
    setPixel(basePtr, x, y, color);
}

int Gdx2DPixmap::getPixel (int x,int y) {
    return getPixel(basePtr, x, y);
}

void Gdx2DPixmap::drawLine (int x,int y,int x2,int y2,int color) {
    drawLine(basePtr, x, y, x2, y2, color);
}

void Gdx2DPixmap::drawRect (int x,int y,int width,int height,int color) {
    drawRect(basePtr, x, y, width, height, color);
}

void Gdx2DPixmap::drawCircle (int x,int y,int radius,int color) {
    drawCircle(basePtr, x, y, radius, color);
}

void Gdx2DPixmap::fillRect (int x,int y,int width,int height,int color) {
    fillRect(basePtr, x, y, width, height, color);
}

void Gdx2DPixmap::fillCircle (int x,int y,int radius,int color) {
    fillCircle(basePtr, x, y, radius, color);
}

void Gdx2DPixmap::drawPixmap (const Gdx2DPixmap& src,int srcX,int srcY,int dstX,int dstY,int width,int height) {
    drawPixmap(src.basePtr, basePtr, srcX, srcY, width, height, dstX, dstY, width, height);
}

void Gdx2DPixmap::drawPixmap (const Gdx2DPixmap& src,int srcX,int srcY,int srcWidth,int srcHeight,int dstX,int dstY,int dstWidth,int dstHeight) {
    drawPixmap(src.basePtr, basePtr, srcX, srcY, srcWidth, srcHeight, dstX, dstY, dstWidth, dstHeight);
}

Gdx2DPixmap& Gdx2DPixmap::newPixmap (const InputStream& in,int requestedFormat) {
    try {
        return new Gdx2DPixmap(in, requestedFormat);
    } catch (IOException e) {
        return null;
    }
}

Gdx2DPixmap& Gdx2DPixmap::newPixmap (int width,int height,int format) {
    try {
        return new Gdx2DPixmap(width, height, format);
    } catch (IllegalArgumentException e) {
        return null;
    }
}

ByteBuffer& Gdx2DPixmap::getPixels () {
    return pixelPtr;
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
    switch (format) {
    case GDX2D_FORMAT_ALPHA:
        return GL10.GL_ALPHA;
    case GDX2D_FORMAT_LUMINANCE_ALPHA:
        return GL10.GL_LUMINANCE_ALPHA;
    case GDX2D_FORMAT_RGB888:
    case GDX2D_FORMAT_RGB565:
        return GL10.GL_RGB;
    case GDX2D_FORMAT_RGBA8888:
    case GDX2D_FORMAT_RGBA4444:
        return GL10.GL_RGBA;
    default:
        throw new GdxRuntimeException("unknown format: " + format);
    }
}

int Gdx2DPixmap::getGLFormat () {
    return getGLInternalFormat();
}

int Gdx2DPixmap::getGLType () {
    switch (format) {
    case GDX2D_FORMAT_ALPHA:
    case GDX2D_FORMAT_LUMINANCE_ALPHA:
    case GDX2D_FORMAT_RGB888:
    case GDX2D_FORMAT_RGBA8888:
        return GL10.GL_UNSIGNED_BYTE;
    case GDX2D_FORMAT_RGB565:
        return GL10.GL_UNSIGNED_SHORT_5_6_5;
    case GDX2D_FORMAT_RGBA4444:
        return GL10.GL_UNSIGNED_SHORT_4_4_4_4;
    default:
        throw new GdxRuntimeException("unknown format: " + format);
    }
}

std::string& Gdx2DPixmap::getFormatString () {
    switch (format) {
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

