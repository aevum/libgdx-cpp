
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_PIXMAPTEXTUREDATA_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_PIXMAPTEXTUREDATA_HPP_

#include "gdx-cpp/graphics/TextureData.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"
#include "gdx-cpp/utils/Aliases.hpp"

namespace gdx_cpp {
namespace graphics {
namespace glutils {

class PixmapTextureData: public gdx_cpp::graphics::TextureData {
public:
    typedef ref_ptr_maker<PixmapTextureData>::type ptr;

    PixmapTextureData (gdx_cpp::graphics::Pixmap::ptr pixmap,
                       gdx_cpp::graphics::Pixmap::Format* format,
                       bool useMipMaps, bool disposePixmap) ;
    
    bool disposePixmap ();
    gdx_cpp::graphics::Pixmap::ptr getPixmap ();
    int getWidth ();
    int getHeight ();
    const gdx_cpp::graphics::Pixmap::Format* getFormat ();
    bool useMipMaps ();
    bool isManaged ();
    const TextureData::TextureDataType& getType ();
    void uploadCompressedData ();

protected:
    graphics::Pixmap::ptr pixmap;
    const graphics::Pixmap::Format& format;
    
    bool _useMipMaps;
    bool _disposePixmap;
private:

};

} // namespace gdx_cpp
} // namespace graphics
} // namespace glutils

#endif // GDX_CPP_GRAPHICS_GLUTILS_PIXMAPTEXTUREDATA_HPP_
