
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_FILETEXTUREDATA_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_FILETEXTUREDATA_HPP_

#include "gdx-cpp/files/FileHandle.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"
#include "gdx-cpp/graphics/TextureData.hpp"

namespace gdx {

class FileTextureData: public gdx::TextureData {
public:
    FileTextureData (FileHandle::ptr file, gdx::Pixmap::ptr preloadedPixmap, const gdx::Pixmap::Format* format, bool useMipMaps) ;
    
    gdx::Pixmap::ptr getPixmap () override;
    bool disposePixmap () override;
    int getWidth () override;
    int getHeight () override;
    const gdx::Pixmap::Format* getFormat () override;
    bool useMipMaps () override;
    bool isManaged () override;
    FileHandle::ptr getFileHandle ();
    const gdx::TextureData::TextureDataType& getType () override;
    void uploadCompressedData () override;

private:
    FileHandle::ptr file;
    int width;
    int height;
    const Pixmap::Format* format;
    Pixmap::ptr pixmap;
    bool _useMipMaps;
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GLUTILS_FILETEXTUREDATA_HPP_
