
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

namespace gdx_cpp {
namespace graphics {
namespace g2d {

class TextureRegion {
public:
    void setRegion (const gdx_cpp::graphics::Texture& texture);
    void setRegion (int x,int y,int width,int height);
    void setRegion (float u,float v,float u2,float v2);
    void setRegion (const TextureRegion& region);
    void setRegion (const TextureRegion& region,int x,int y,int width,int height);
    gdx_cpp::graphics::Texture& getTexture ();
    void setTexture (const gdx_cpp::graphics::Texture& texture);
    float getU ();
    void setU (float u);
    float getV ();
    void setV (float v);
    float getU2 ();
    void setU2 (float u2);
    float getV2 ();
    void setV2 (float v2);
    int getRegionX ();
    void setRegionX (int x);
    int getRegionY ();
    void setRegionY (int y);
    int getRegionWidth ();
    void setRegionWidth (int width);
    int getRegionHeight ();
    void setRegionHeight (int height);
    void flip (bool x,bool y);
    void scroll (float xAmount,float yAmount);
    TextureRegion* split (int tileWidth,int tileHeight);
    static TextureRegion* split (const gdx_cpp::graphics::Texture& texture,int tileWidth,int tileHeight);

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_TEXTUREREGION_HPP_
