
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
#include "gdx-cpp/Gdx.hpp"

#include <stdexcept>

using namespace gdx;

gdx::Pixmap::ptr FileTextureData::getPixmap () {
    if (pixmap) {
        Pixmap::ptr tmp = pixmap;
        this->pixmap.reset();
        return tmp;
    } else {
        Pixmap::ptr pixmap = Pixmap::newFromFile(file);
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

const gdx::Pixmap::Format* FileTextureData::getFormat () {
    return format;
}

bool FileTextureData::useMipMaps () {
    return _useMipMaps;
}

bool FileTextureData::isManaged () {
    return true;
}

gdx::FileHandle::ptr FileTextureData::getFileHandle () {
    return file;
}

const TextureData::TextureDataType& FileTextureData::getType () {
    return TextureData::TextureDataType::Pixmap;
}

void FileTextureData::uploadCompressedData () {
    throw std::runtime_error("This TextureData implementation does not upload data itself");
}

FileTextureData::FileTextureData(FileHandle::ptr file, gdx::Pixmap::ptr preloadedPixmap,
                                 const Pixmap::Format* format, bool useMipMaps)
:
file(file),
format(format),
pixmap(preloadedPixmap),
_useMipMaps(useMipMaps)
{
    if (pixmap) {
        width = pixmap->getWidth();
        height = pixmap->getHeight();
        if (format == NULL)
            this->format = &pixmap->getFormat();
    }
}


