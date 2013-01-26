
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

#include <gdx-cpp/files/FileHandle.hpp>
#include <gdx-cpp/graphics/Texture.hpp>
#include <gdx-cpp/graphics/g2d/Sprite.hpp>
#include <gdx-cpp/graphics/g2d/TextureRegion.hpp>
#include <gdx-cpp/utils/Disposable.hpp>
#include <cmath>
#include <gdx-cpp/internal/memory>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "gdx-cpp/internal/memory"

namespace gdx {

class TextureAtlas: public gdx::Disposable {
public:
    class AtlasRegion : public gdx::TextureRegion {
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

        AtlasRegion();
        AtlasRegion (const gdx::Texture::ptr& texture, int x, int y, int width, int height);
        AtlasRegion (const AtlasRegion& region);

        void flip (bool x, bool y);
    };

    class TextureAtlasDataProvider {
    public:
        virtual std::vector< AtlasRegion > loadAtlasRegions() = 0;
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

    AtlasRegion addRegion (const std::string& name, const gdx::Texture::ptr& texture, int x, int y, int width, int height);
    AtlasRegion addRegion (const std::string& name, gdx::TextureRegion textureRegion);
    bool findRegion (const std::string& name, AtlasRegion& placement);
    bool findRegion (const std::string& name, int index, AtlasRegion& placement);
    std::vector< AtlasRegion > findRegions (const std::string& name);
    std::vector< Sprite::ptr > createSprites ();
    Sprite::ptr createSprite (const std::string& name);
    Sprite::ptr createSprite (const std::string& name,int index);
    std::vector< Sprite::ptr > createSprites (const std::string& name);
    void dispose ();

    static std::unique_ptr<TextureAtlas> newAtlasFromProvider(TextureAtlasDataProvider& provider) ;

private:
    std::set<Texture::ptr> textures;
    std::vector< AtlasRegion > regions;

    Sprite::ptr newSprite (const gdx::TextureAtlas::AtlasRegion& region);
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_TEXTUREATLAS_HPP_
