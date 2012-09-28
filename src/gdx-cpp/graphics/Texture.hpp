
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

#include <list>
#include "gdx-cpp/assets/Asset.hpp"
#include "gdx-cpp/internal/unordered_map"

#undef GL_NEAREST
#undef GL_LINEAR

namespace gdx {

class FileHandle;
class Texture
    : public Disposable,
    public Asset , public std::enable_shared_from_this<Texture> {
public:
    typedef ref_ptr_maker<Texture>::shared_ptr_t ptr;
    typedef ref_ptr_maker<Texture>::weak_ptr_t weak_ptr;

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

        bool isMipMap () ;

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

    Texture (const gdx::TextureData::ptr& data) ;
    Texture (int width, int height, const Pixmap::Format& format, Pixmap::PixmapType pixType) ;
    Texture (const gdx::Pixmap::ptr& pixmap, bool useMipMaps) ;
    Texture (const Pixmap::ptr pixmap, const Pixmap::Format& format, bool useMipMaps) ;
    Texture (const TextureData& data) ;

    const AssetType& getAssetType();
    void load (const TextureData::ptr& data);
    void bind ();
    void bind (int unit);
    void draw (Pixmap& pixmap, int x, int y);
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
    void setFilter (const Texture::TextureFilter& minFilter, const Texture::TextureFilter& magFilter);

    void setEnforcePotImages (bool enforcePotImages);
    static void clearAllTextures (Application* app);
    static void invalidateAllTextures (Application* app);
    static void setAssetManager (AssetManager* manager);
    std::string getManagedStatus ();
    static int createGLHandle ();

    static ptr newFromFile(const FileHandle::ptr& file,
                           const Pixmap::Format* format = NULL,
                           bool useMipMaps = false);

    virtual ~Texture();

protected:
    void dispose ();
    void initialize(const gdx::FileHandle::ptr& file, const gdx::Pixmap::Format* format, bool useMipMaps);
    Texture ();

private:
    void create (const gdx::TextureData::ptr& data);
    void uploadImageData (const Pixmap::ptr& pixmap);
    void reload ();
    static void addManagedTexture (gdx::Application* app, const gdx::Texture::ptr& texture);
    static AssetManager* assetManager;

    typedef std::list< Texture::weak_ptr > textureList;
    typedef gdx_unordered_map< Application* , textureList > managedTextureMap;

    static managedTextureMap managedTextures;

    static unsigned int buffer;

    TextureFilter minFilter;
    TextureFilter magFilter;
    TextureWrap uWrap;
    TextureWrap vWrap;

    TextureData::ptr data;

    unsigned int glHandle;

    bool enforcePotImages;
    bool useHWMipMap;
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_TEXTURE_HPP_

