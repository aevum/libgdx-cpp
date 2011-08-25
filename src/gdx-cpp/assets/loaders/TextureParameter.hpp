
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

#ifndef GDX_CPP_ASSETS_LOADERS_TEXTUREPARAMETER_HPP_
#define GDX_CPP_ASSETS_LOADERS_TEXTUREPARAMETER_HPP_

#include "gdx-cpp/graphics/Texture.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"
#include "gdx-cpp/utils/Aliases.hpp"
#include "Parameter.hpp"

namespace gdx_cpp {
namespace assets {
namespace loaders {

struct TextureParameter : public Parameter {
    typedef ref_ptr_maker<TextureParameter>::type ptr;
    
    /** the format of the final Texture. Uses the source images format if null **/
    gdx_cpp::graphics::Pixmap::Format format;
    /** whether to generate mipmaps **/
    bool genMipMaps;
    /** The texture to put the {@link TextureData} in **/
    graphics::Texture::ptr texture;

    TextureParameter() : genMipMaps(true) {
    }
};

} // namespace gdx_cpp
} // namespace assets
} // namespace loaders

#endif // GDX_CPP_ASSETS_LOADERS_TEXTUREPARAMETER_HPP_
