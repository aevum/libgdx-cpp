
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

#ifndef GDX_CPP_GRAPHICS_TEXTUREDICT_HPP_
#define GDX_CPP_GRAPHICS_TEXTUREDICT_HPP_

namespace gdx_cpp {
namespace graphics {

class TextureDict {
public:
    static TextureRef& loadTexture (const std::string& path);
    static TextureRef& loadTexture (const std::string& path,const gdx_cpp::graphics::Texture::TextureFilter& minFilter,const gdx_cpp::graphics::Texture::TextureFilter& magFilter,const gdx_cpp::graphics::Texture::TextureWrap& uwrap,const gdx_cpp::graphics::Texture::TextureWrap& vwrap);
    static void removeTexture (const std::string& path);
    static void unloadAll ();

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_TEXTUREDICT_HPP_
