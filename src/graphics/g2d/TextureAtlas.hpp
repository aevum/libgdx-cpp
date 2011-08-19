
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

namespace gdx_cpp {
namespace graphics {
namespace g2d {

class TextureAtlas: public gdx_cpp::utils::Disposable {
public:
    gdx_cpp::utils::ArrayPage>& getPages ();
    gdx_cpp::utils::ArrayRegion>& getRegion ();
    AtlasRegion& addRegion (const std::string& name,const gdx_cpp::graphics::Texture& texture,int x,int y,int width,int height);
    AtlasRegion& addRegion (const std::string& name,const TextureRegion& textureRegion);
    std::list<AtlasRegion>& getRegions ();
    AtlasRegion& findRegion (const std::string& name);
    AtlasRegion& findRegion (const std::string& name,int index);
    std::list<AtlasRegion>& findRegions (const std::string& name);
    std::list<Sprite>& createSprites ();
    Sprite& createSprite (const std::string& name);
    Sprite& createSprite (const std::string& name,int index);
    std::list<Sprite>& createSprites (const std::string& name);
    void dispose ();
    int compare (const gdx_cpp::graphics::g2d::TextureAtlas::TextureAtlasData::Region& region1,const gdx_cpp::graphics::g2d::TextureAtlas::TextureAtlasData::Region& region2);
    void flip (bool x,bool y);
    void setPosition (float x,float y);
    void setBounds (float x,float y,float width,float height);
    void setOrigin (float originX,float originY);
    void flip (bool x,bool y);
    float getX ();
    float getY ();
    AtlasRegion& getAtlasRegion ();
    FileHandle textureFile;
    boolean useMipMaps;
    Format format;
    TextureFilter minFilter;
    TextureFilter magFilter;
    TextureWrap uWrap;
    TextureWrap vWrap;

protected:


private:
    void load (const TextureAtlasData& data);
    Sprite& newSprite (const AtlasRegion& region);
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_TEXTUREATLAS_HPP_
