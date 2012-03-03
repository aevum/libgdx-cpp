
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

const Pixmap::Format Pixmap::Format::Alpha = Pixmap::Format("Alpha");
const Pixmap::Format Pixmap::Format::LuminanceAlpha = Pixmap::Format("LuminanceAlpha");
const Pixmap::Format Pixmap::Format::RGB565 = Pixmap::Format("RGB565");
const Pixmap::Format Pixmap::Format::RGBA4444 = Pixmap::Format("RGBA4444");
const Pixmap::Format Pixmap::Format::RGB888 = Pixmap::Format("RGB888");
const Pixmap::Format Pixmap::Format::RGBA8888 = Pixmap::Format("RGBA888");

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

// Pixmap::Pixmap(int width, int height, const gdx_cpp::graphics::Pixmap::Format& format)
//         : color(0)
// {
//     pixmap = g2d::Gdx2DPixmap::newPixmap(width, height, Format::toGdx2DPixmapFormat(format));
//     assert(pixmap);
//     setColor(0, 0, 0, 0);
//     fill();
// }
// 
// Pixmap::Pixmap(unsigned char* encodedData, int offset, int len) {
//     pixmap = new g2d::Gdx2DPixmap(encodedData, offset, len, 0);
// }
// 
// Pixmap::Pixmap(gdx_cpp::files::FileHandle& file) {
// 
//     gdx_cpp::files::FileHandle::char_ptr bytes;
//     int size = file.readBytes(bytes);
//     pixmap = new g2d::Gdx2DPixmap((unsigned char*) bytes.get(), 0, size, 0);
//     assert(pixmap);
// }
// 
// Pixmap::Pixmap(g2d::Gdx2DPixmap* pixmap)
//  : color(0)
//  {
//     this->pixmap = pixmap;
// }

Pixmap::ptr Pixmap::newFromFile(const gdx_cpp::files::FileHandle::ptr file)
{
    return Pixmap::ptr(gdx_cpp::Gdx::graphics->resolvePixmap(file));
}

Pixmap::ptr Pixmap::newFromPixmap(const gdx_cpp::graphics::Pixmap& pixmap)
{
    return Pixmap::ptr(gdx_cpp::Gdx::graphics->resolvePixmap(pixmap));
}

Pixmap::ptr Pixmap::newFromRect(int width, int height,
                                const gdx_cpp::graphics::Pixmap::Format& format,
                                gdx_cpp::graphics::Pixmap::PixmapType pixType)
{
    return Pixmap::ptr(gdx_cpp::Gdx::graphics->resolvePixmap(width, height, format, pixType));
}





