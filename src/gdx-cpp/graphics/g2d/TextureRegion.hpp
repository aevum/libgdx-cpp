
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

#ifndef GDX_CPP_GRAPHICS_G2D_TEXTUREREGION_HPP_
#define GDX_CPP_GRAPHICS_G2D_TEXTUREREGION_HPP_

#include "gdx-cpp/graphics/Texture.hpp"
#include <gdx-cpp/utils/MatrixBase.hpp>//TODO check

namespace gdx_cpp {
namespace graphics {
namespace g2d {

class TextureRegion {
public:
    typedef ref_ptr_maker<TextureRegion>::type ptr;
    typedef ref_ptr_maker<gdx_cpp::graphics::Texture >::type ptrTexture;

    TextureRegion ();
    TextureRegion (TextureRegion::ptrTexture _texture);
    TextureRegion (TextureRegion::ptrTexture _texture, int x, int y, int width, int height);
    TextureRegion (TextureRegion::ptrTexture _texture, float u, float v, float u2, float v2);
    TextureRegion (gdx_cpp::graphics::g2d::TextureRegion& region);
    TextureRegion (gdx_cpp::graphics::g2d::TextureRegion& region, int x, int y, int width, int height);
    void setRegion (gdx_cpp::graphics::g2d::TextureRegion::ptrTexture texture);
    void setRegion (int x,int y,int width,int height);
    void setRegion (float u,float v,float u2,float v2);
    void setRegion (const TextureRegion& region);
    void setRegion (const gdx_cpp::graphics::g2d::TextureRegion& region, int x, int y, int width, int height);
    ptrTexture getTexture ();
    void setTexture (gdx_cpp::graphics::g2d::TextureRegion::ptrTexture texture);
    float getU () const;
    void setU (float u);
    float getV () const;
    void setV (float v);
    float getU2 () const;
    void setU2 (float u2);
    float getV2 () const;
    void setV2 (float v2);
    int getRegionX () const;
    void setRegionX (int x);
    int getRegionY () const;
    void setRegionY (int y);
    int getRegionWidth () const;
    void setRegionWidth (int width);
    int getRegionHeight () const;
    void setRegionHeight (int height);
    void flip (bool x,bool y);
    void scroll (float xAmount,float yAmount);
    utils::MatrixBase< gdx_cpp::graphics::g2d::TextureRegion::ptr > split (int tileWidth, int tileHeight);
    utils::MatrixBase< gdx_cpp::graphics::g2d::TextureRegion::ptr > split (gdx_cpp::graphics::Texture::ptr texture, int tileWidth, int tileHeight);

    float u, v;
    float u2, v2;
protected:
    TextureRegion::ptrTexture texture;

private:

};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_TEXTUREREGION_HPP_
