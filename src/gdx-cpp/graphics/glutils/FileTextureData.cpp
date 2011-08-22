
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

using namespace gdx_cpp::graphics::glutils;

gdx_cpp::graphics::Pixmap& FileTextureData::getPixmap () {
    if (pixmap != null) {
        Pixmap tmp = pixmap;
        this.pixmap = null;
        return tmp;
    } else {
        Pixmap pixmap = new Pixmap(file);
        width = pixmap.getWidth();
        height = pixmap.getHeight();
        if (format == null) format = pixmap.getFormat();
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

gdx_cpp::graphics::Pixmap::Format& FileTextureData::getFormat () {
    return format;
}

bool FileTextureData::useMipMaps () {
    return useMipMaps;
}

bool FileTextureData::isManaged () {
    return true;
}

gdx_cpp::files::FileHandle& FileTextureData::getFileHandle () {
    return file;
}

TextureDataType& FileTextureData::getType () {
    return TextureDataType.Pixmap;
}

void FileTextureData::uploadCompressedData () {
    throw new GdxRuntimeException("This TextureData implementation does not upload data itself");
}

