
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

#include "gdx-cpp/graphics/TextureData.hpp"

namespace gdx_cpp {

class FileHandle;

namespace graphics {
namespace glutils {

class FileTextureData: public gdx_cpp::graphics::TextureData {
public:
    FileTextureData (gdx_cpp::FileHandle* file, gdx_cpp::graphics::Pixmap::ptr preloadedPixmap, gdx_cpp::graphics::Pixmap::Format* format, bool useMipMaps) ;
    
    gdx_cpp::graphics::Pixmap::ptr getPixmap ();
    bool disposePixmap ();
    int getWidth ();
    int getHeight ();
    Pixmap::Format* getFormat ();
    bool useMipMaps ();
    bool isManaged ();
    files::FileHandle* getFileHandle ();
    TextureDataType& getType ();
    void uploadCompressedData ();

private:
    FileHandle* file;
    int width;
    int height;
    Pixmap::Format* format;
    Pixmap::ptr pixmap;
    bool _useMipMaps;
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace glutils

#endif // GDX_CPP_GRAPHICS_GLUTILS_FILETEXTUREDATA_HPP_
