
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

#ifndef GDX_CPP_GRAPHICS_G2D_TEXTUREATLAS_HPP_
#define GDX_CPP_GRAPHICS_G2D_TEXTUREATLAS_HPP_

#include <gdx-cpp/utils/Disposable.hpp>
#include <gdx-cpp/files/FileHandle.hpp>
#include <gdx-cpp/graphics/Texture.hpp>
#include <gdx-cpp/graphics/g2d/TextureRegion.hpp>
#include <gdx-cpp/graphics/g2d/Sprite.hpp>

#include <gdx-cpp/internal/memory>

#include <cmath>
#include <string>
#include <vector>
#include <set>

namespace gdx {

class TextureAtlas: public gdx::Disposable {
public:   
    class AtlasRegion : public gdx::TextureRegion, public ref_ptr_maker<AtlasRegion> {
    public:
        int index;
        std::string name;
        float offsetX;
        float offsetY;
        int packedWidth;
        int packedHeight;
        int originalWidth;
        int originalHeight;
        bool rotate;

        AtlasRegion (const gdx::Texture::ptr& texture, int x, int y, int width, int height);
        AtlasRegion (const AtlasRegion& region);

        void flip (bool x, bool y);
    };    
    
    struct TextureAtlasData {
      friend class TextureAtlas;
      
      struct Page : public ref_ptr_maker<Page> {
            gdx::FileHandle::ptr textureFile;
            gdx::Texture::ptr texture;
            bool useMipMaps;
            gdx::Pixmap::Format format;
            gdx::Texture::TextureFilter minFilter;
            gdx::Texture::TextureFilter magFilter;
            gdx::Texture::TextureWrap uWrap;
            gdx::Texture::TextureWrap vWrap;

            Page (const FileHandle::ptr& _handle, bool _useMipMaps, gdx::Pixmap::Format _format, 
                  gdx::Texture::TextureFilter _minFilter, gdx::Texture::TextureFilter _magFilter,
                  gdx::Texture::TextureWrap _uWrap, gdx::Texture::TextureWrap _vWrap) ;          
      };
      
      struct Region : public ref_ptr_maker<Region> {
          Page::shared_ptr_t page;
          int index;
          std::string name;
          float offsetX;
          float offsetY;
          int originalWidth;
          int originalHeight;
          bool rotate;
          int left;
          int top;
          int width;
          int height;
          bool flip;
      };
            
      virtual void read(const gdx::FileHandle::ptr& packFile, const gdx::FileHandle::ptr& imagesDir, bool flip);
      
        std::vector< TextureAtlas::TextureAtlasData::Page::shared_ptr_t >& getPages();
        std::vector< TextureAtlas::TextureAtlasData::Region::shared_ptr_t >& getRegions();
      
    private:
      std::vector< TextureAtlasData::Page::shared_ptr_t > pages;
      std::vector< TextureAtlasData::Region::shared_ptr_t > regions;
    };
    
    class AtlasSprite: public gdx::Sprite {
    public:
        AtlasRegion region;
        float originalOffsetX, originalOffsetY;

        AtlasSprite (AtlasRegion _region) ;

        virtual void setPosition (float x, float y);
        virtual void setBounds (float x, float y, float width, float height);
        virtual void setSize (float width, float height);
        virtual void setOrigin (float originX, float originY);
        virtual void flip (bool x, bool y);
        virtual float getX();
        virtual float getY();
        virtual float getOriginX();
        virtual float getOriginY();
        virtual float getWidth();
        virtual float getHeight();
        
        AtlasRegion getAtlasRegion();
    };    
    
    ref_ptr_maker< AtlasRegion >::shared_ptr_t addRegion (const std::string& name, const gdx::Texture::ptr& texture, int x, int y, int width, int height);
    ref_ptr_maker< AtlasRegion >::shared_ptr_t addRegion (const std::string& name, gdx::TextureRegion textureRegion);
    std::vector<AtlasRegion> getRegions();
    ref_ptr_maker< AtlasRegion >::shared_ptr_t findRegion (const std::string& name);
    AtlasRegion::shared_ptr_t findRegion (const std::string& name,int index);
    std::vector< AtlasRegion::shared_ptr_t > findRegions (const std::string& name);
    std::vector< Sprite::ptr > createSprites ();
    Sprite::ptr createSprite (const std::string& name);
    Sprite::ptr createSprite (const std::string& name,int index);
    std::vector< Sprite::ptr > createSprites (const std::string& name);
    void dispose ();
    
    static int compare(const TextureAtlasData::Region& a, const TextureAtlasData::Region& b);
    
    static std::unique_ptr<TextureAtlas> newAtlasFrom() {
    }
    
private:
    std::string tuple[2];
    std::set<Texture::ptr> textures;
    std::vector<AtlasRegion::shared_ptr_t> regions;
    
    void load (const TextureAtlasData& data);
    Sprite::ptr newSprite (const gdx::TextureAtlas::AtlasRegion& region);
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_TEXTUREATLAS_HPP_
