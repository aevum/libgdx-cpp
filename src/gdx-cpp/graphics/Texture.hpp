
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

#ifndef GDX_CPP_GRAPHICS_TEXTURE_HPP_
#define GDX_CPP_GRAPHICS_TEXTURE_HPP_

#include "gdx-cpp/utils/Disposable.hpp"
#include "gdx-cpp/graphics/GL10.hpp"
#include "gdx-cpp/assets/AssetManager.hpp"
#include "gdx-cpp/Application.hpp"
#include "TextureData.hpp"

#include <tr1/unordered_map>
#include <tr1/shared_ptr.h>
#include <list>
#include "gdx-cpp/assets/Asset.hpp"

#undef GL_NEAREST
#undef GL_LINEAR

namespace gdx_cpp {

namespace files {
    class FileHandle;
}
    
namespace graphics {

class Texture
    : public gdx_cpp::utils::Disposable,
      public gdx_cpp::assets::Asset,
      public std::tr1::enable_shared_from_this<Texture> {
public:
    typedef ref_ptr_maker<Texture>::type ptr;
    typedef ref_ptr_maker<Texture>::weak_type weak_ptr;
    
    class TextureFilter {
    public:
        const static TextureFilter Nearest;
        const static TextureFilter Linear;
        const static TextureFilter MipMap;
        const static TextureFilter MipMapNearestNearest;
        const static TextureFilter MipMapLinearNearest;
        const static TextureFilter MipMapNearestLinear;
        const static TextureFilter MipMapLinearLinear;
        
        int glEnum;

        bool isMipMap () {
            return glEnum != gdx_cpp::graphics::GL10::GL_NEAREST && glEnum != GL10::GL_LINEAR;
        }

        int getGLEnum () const {
            return glEnum;
        }

    private:
        TextureFilter (int glEnum) {
            this->glEnum = glEnum;
        }
    };

    class TextureWrap {
    public:
        static const TextureWrap ClampToEdge;
        static const TextureWrap Repeat;
       
        int getGLEnum () const {
            return glEnum;
        }

        int glEnum;

      private:
        TextureWrap (int glEnum) {
            this->glEnum = glEnum;
        }
    };

    Texture (const gdx_cpp::graphics::TextureData::ptr data) ;
    Texture (int width, int height, const gdx_cpp::graphics::Pixmap::Format& format, gdx_cpp::graphics::Pixmap::PixmapType pixType) ;
    Texture (const gdx_cpp::graphics::Pixmap::ptr pixmap, bool useMipMaps) ;
    Texture (const gdx_cpp::graphics::Pixmap::ptr pixmap, const Pixmap::Format& format, bool useMipMaps) ;
    Texture (const TextureData& data) ;

    const gdx_cpp::assets::AssetType& getAssetType();
    void load (const gdx_cpp::graphics::TextureData::ptr& data);
    void bind ();
    void bind (int unit);
    void draw (gdx_cpp::graphics::Pixmap& pixmap, int x, int y);
    int getWidth () const;
    int getHeight () const;
    const TextureFilter& getMinFilter () const;
    const TextureFilter& getMagFilter () const;
    const TextureWrap& getUWrap () const;
    const TextureWrap& getVWrap () const;
    TextureData::ptr getTextureData ();
    bool isManaged ();
    int getTextureObjectHandle ();
    void setWrap (const TextureWrap& u, const TextureWrap& v);
    void setFilter (const gdx_cpp::graphics::Texture::TextureFilter& minFilter, const gdx_cpp::graphics::Texture::TextureFilter& magFilter);
    
    void setEnforcePotImages (bool enforcePotImages);
    static void clearAllTextures (gdx_cpp::Application* app);
    static void invalidateAllTextures (gdx_cpp::Application* app);
    static void setAssetManager (gdx_cpp::assets::AssetManager* manager);
    std::string getManagedStatus ();
    static int createGLHandle ();

    static ptr fromFile(const gdx_cpp::files::FileHandle::ptr file,
                        const gdx_cpp::graphics::Pixmap::Format* format = NULL,
                        bool useMipMaps = false);

    ~Texture();
    void dispose ();
    
protected:
    void initialize(const gdx_cpp::files::FileHandle::ptr file, const gdx_cpp::graphics::Pixmap::Format* format, bool useMipMaps);
    Texture ();
    
    
private:
    void create (gdx_cpp::graphics::TextureData::ptr data);
    void uploadImageData (const gdx_cpp::graphics::Pixmap::ptr& pixmap);
    void reload ();
    static void addManagedTexture (gdx_cpp::Application* app, const gdx_cpp::graphics::Texture::ptr texture);
    static assets::AssetManager* assetManager;

    typedef std::list< Texture::ptr > textureList;
    typedef std::tr1::unordered_map< Application* , textureList > managedTextureMap;
    
    static managedTextureMap managedTextures;

    static int buffer;

    TextureFilter minFilter;
    TextureFilter magFilter;
    TextureWrap uWrap;
    TextureWrap vWrap;
    
    TextureData::ptr data;

    int glHandle;
    
    bool enforcePotImages;
    bool useHWMipMap;
};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_TEXTURE_HPP_

