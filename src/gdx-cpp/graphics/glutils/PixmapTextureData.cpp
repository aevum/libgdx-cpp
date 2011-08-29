
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

#include "PixmapTextureData.hpp"
#include "gdx-cpp/Gdx.hpp"

using namespace gdx_cpp::graphics::glutils;

bool PixmapTextureData::disposePixmap () {
    return _disposePixmap;
}

gdx_cpp::graphics::Pixmap::ptr PixmapTextureData::getPixmap () {
    return pixmap;
}

int PixmapTextureData::getWidth () {
    return pixmap->getWidth();
}

int PixmapTextureData::getHeight () {
    return pixmap->getHeight();
}

const gdx_cpp::graphics::Pixmap::Format* PixmapTextureData::getFormat () {
    return &format;
}

bool PixmapTextureData::useMipMaps () {
    return _useMipMaps;
}

bool PixmapTextureData::isManaged () {
    return false;
}

const gdx_cpp::graphics::TextureData::TextureDataType& PixmapTextureData::getType () {
    return TextureDataType::Pixmap;
}

void PixmapTextureData::uploadCompressedData () {
    gdx_cpp::Gdx::app->error(__FILE__) << "This TextureData implementation does not upload data itself";
}

PixmapTextureData::PixmapTextureData(gdx_cpp::graphics::Pixmap::ptr pixmap,
                                     gdx_cpp::graphics::Pixmap::Format* format,
                                     bool useMipMaps, bool disposePixmap)
: _useMipMaps(useMipMaps)
, _disposePixmap(disposePixmap)
, pixmap(pixmap)
, format(format == NULL ? pixmap->getFormat() : *format)
{
}


