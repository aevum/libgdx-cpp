
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

#include "FileTextureData.hpp"

#include "gdx-cpp/graphics/Pixmap.hpp"
#include "gdx-cpp/files/FileHandle.hpp"

#include <stdexcept>

using namespace gdx_cpp;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp::graphics::glutils;

gdx_cpp::graphics::Pixmap::ptr FileTextureData::getPixmap () {
    if (pixmap != NULL) {
        Pixmap::ptr tmp = pixmap;
        this->pixmap.reset();
        return tmp;
    } else {
        Pixmap::ptr pixmap = Pixmap::ptr(new Pixmap(*file));
        width = pixmap->getWidth();
        height = pixmap->getHeight();
        if (format == NULL) format = &pixmap->getFormat();
        return pixmap;
    }
}

bool FileTextureData::disposePixmap () {
    return true;
}

int FileTextureData::getWidth () {
    return width;
}

int FileTextureData::getHeight () {
    return height;
}

const gdx_cpp::graphics::Pixmap::Format* FileTextureData::getFormat () {
    return format;
}

bool FileTextureData::useMipMaps () {
    return _useMipMaps;
}

bool FileTextureData::isManaged () {
    return true;
}

gdx_cpp::files::FileHandle::ptr FileTextureData::getFileHandle () {
    return file;
}

const TextureData::TextureDataType& FileTextureData::getType () {
    return TextureData::TextureDataType::Pixmap;
}

void FileTextureData::uploadCompressedData () {
    throw std::runtime_error("This TextureData implementation does not upload data itself");
}

FileTextureData::FileTextureData(Files::fhandle_ptr file, gdx_cpp::graphics::Pixmap::ptr preloadedPixmap,
                                 const Pixmap::Format* format, bool useMipMaps)
:
file(file)
, _useMipMaps(useMipMaps)
, format(format)
, pixmap(preloadedPixmap)
{
    if (pixmap != NULL) {
        width = pixmap->getWidth();
        height = pixmap->getHeight();
        if (format == NULL)
            this->format = &pixmap->getFormat();
    }
}


