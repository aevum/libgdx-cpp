
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

namespace gdx_cpp {
namespace graphics {

class Texture: public gdx_cpp::utils::Disposable {
public:
    bool isMipMap ();
    int getGLEnum ();
    int getGLEnum ();
    static int createGLHandle ();
    void load (const TextureData& data);
    void bind ();
    void bind (int unit);
    void draw (const Pixmap& pixmap,int x,int y);
    int getWidth ();
    int getHeight ();
    TextureFilter& getMinFilter ();
    TextureFilter& getMagFilter ();
    TextureWrap& getUWrap ();
    TextureWrap& getVWrap ();
    TextureData& getTextureData ();
    bool isManaged ();
    int getTextureObjectHandle ();
    void setWrap (const TextureWrap& u,const TextureWrap& v);
    void setFilter (const TextureFilter& minFilter,const TextureFilter& magFilter);
    void dispose ();
    void setEnforcePotImages (bool enforcePotImages);
    static void clearAllTextures (const gdx_cpp::Application& app);
    static void invalidateAllTextures (const gdx_cpp::Application& app);
    static void setAssetManager (const gdx_cpp::assets::AssetManager& manager);
    static std::string& getManagedStatus ();

protected:


private:
    void create (const TextureData& data);
    void uploadImageData (const Pixmap& pixmap);
    void reload ();
    static void addManagedTexture (const gdx_cpp::Application& app,const Texture& texture);
    static AssetManager assetManager;
};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_TEXTURE_HPP_
