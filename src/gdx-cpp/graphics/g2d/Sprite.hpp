
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

#ifndef GDX_CPP_GRAPHICS_G2D_SPRITE_HPP_
#define GDX_CPP_GRAPHICS_G2D_SPRITE_HPP_

#include "gdx-cpp/graphics/Color.hpp"
#include "gdx-cpp/graphics/Texture.hpp"
#include "gdx-cpp/math/Rectangle.hpp"
#include "gdx-cpp/graphics/g2d/TextureRegion.hpp"

namespace gdx_cpp {
namespace graphics {
namespace g2d {

class Sprite : public TextureRegion {
public:
    Sprite();
    Sprite (graphics::Texture::ptr texture) ;
    Sprite (Texture texture, int srcWidth, int srcHeight) ;
    Sprite (Texture::ptr texture, int srcX, int srcY, int srcWidth, int srcHeight) ;
    Sprite (TextureRegion region) ;
    Sprite (TextureRegion region, int srcX, int srcY, int srcWidth, int srcHeight) ;
    
    void set (const Sprite& sprite);
    void setBounds (float x,float y,float width,float height);
    void setSize (float width,float height);
    void setPosition (float x,float y);
    void translate (float xAmount,float yAmount);
    void setColor (const gdx_cpp::graphics::Color& tint);
    void setColor (float r,float g,float b,float a);
    void setOrigin (float originX,float originY);
    void setRotation (float degrees);
    void rotate (float degrees);
    void rotate90 (bool clockwise);
    void setScale (float scaleXY);
    void setScale (float scaleX,float scaleY);
    void scale (float amount);
    float* const getVertices ();
    const gdx_cpp::math::Rectangle& getBoundingRectangle ();
    void draw (const SpriteBatch& spriteBatch);
    void draw (const SpriteBatch& spriteBatch,float alphaModulation);
    float getX ();
    float getY ();
    float getWidth ();
    float getHeight ();
    float getOriginX ();
    float getOriginY ();
    float getRotation ();
    float getScaleX ();
    float getScaleY ();
    gdx_cpp::graphics::Color& getColor ();
    void setRegion (float u,float v,float u2,float v2);
    void setU (float u);
    void setV (float v);
    void setU2 (float u2);
    void setV2 (float v2);
    void flip (bool x,bool y);
    void scroll (float xAmount,float yAmount);

    static const int X1 = 0;
    static const int Y1 = 1;
    static const int C1 = 2;
    static const int U1 = 3;
    static const int V1 = 4;
    static const int X2 = 5;
    static const int Y2 = 6;
    static const int C2 = 7;
    static const int U2 = 8;
    static const int V2 = 9;
    static const int X3 = 10;
    static const int Y3 = 11;
    static const int C3 = 12;
    static const int U3 = 13;
    static const int V3 = 14;
    static const int X4 = 15;
    static const int Y4 = 16;
    static const int C4 = 17;
    static const int U4 = 18;
    static const int V4 = 19;
protected:
    static const int VERTEX_SIZE = 2 + 1 + 2;
    static const int SPRITE_SIZE = 4 * VERTEX_SIZE;
    float vertices[20];
    
private:   
    graphics::Color color = new Color(1, 1, 1, 1);
    float x, y;
    float width, height;
    float originX, originY;
    float rotation;
    float scaleX = 1, scaleY = 1;
    bool dirty = true;
    void initialize(Texture arg1,  arg2, int arg3, int arg4, int arg5);
    math::Rectangle bounds;   
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_SPRITE_HPP_
