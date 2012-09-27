
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
#include "gdx-cpp/internal/memory"

namespace gdx {

class SpriteBatch;

class Sprite : public TextureRegion {
public:
    typedef std::array<float, 20> vertex_array_t;
    typedef ref_ptr_maker<Sprite>::shared_ptr_t ptr;

    Sprite();
    Sprite ( const gdx::Sprite::ptr& sprite );
    Sprite ( const gdx::Texture::ptr& texture ) ;
    Sprite ( const gdx::Texture::ptr& texture, int srcWidth, int srcHeight ) ;
    Sprite ( const gdx::Texture::ptr& texture, int srcX, int srcY, int srcWidth, int srcHeight ) ;
    Sprite ( const TextureRegion& region ) ;
    Sprite ( const TextureRegion& region, int srcX, int srcY, int srcWidth, int srcHeight ) ;

    virtual void set ( const gdx::Sprite::ptr& sprite );
    virtual void setBounds ( float x,float y,float width,float height );
    virtual void setSize ( float width,float height );
    virtual void setPosition ( float x,float y );
    virtual void translate ( float xAmount,float yAmount );
    virtual void setColor ( const Color& tint );
    virtual void setColor ( float r,float g,float b,float a );
    virtual void setOrigin ( float originX,float originY );
    virtual void setRotation ( float degrees );
    virtual void rotate ( float degrees );
    virtual void rotate90 ( bool clockwise );
    virtual void setScale ( float scaleXY );
    virtual void setScale ( float scaleX,float scaleY );
    virtual void scale ( float amount );
    const vertex_array_t& getVertices();
    const Rectangle& getBoundingRectangle ();
    virtual void draw ( SpriteBatch& spriteBatch );
    virtual void draw ( SpriteBatch& spriteBatch, float alphaModulation );
    virtual float getX ();
    virtual float getY ();
    virtual float getWidth ();
    virtual float getHeight ();
    virtual float getOriginX ();
    virtual float getOriginY ();
    virtual float getRotation ();
    virtual float getScaleX ();
    virtual float getScaleY ();
    virtual const Color& getColor ();
    virtual void setRegion ( float u,float v,float u2,float v2 );
    virtual void setRegion ( const TextureRegion& other );
    virtual void setU ( float u );
    virtual void setV ( float v );
    virtual void setU2 ( float u2 );
    virtual void setV2 ( float v2 );
    virtual void flip ( bool x,bool y );
    virtual void scroll ( float xAmount,float yAmount );

    enum {
        X1 = 0,
        Y1 = 1,
        C1 = 2,
        U1 = 3,
        V1 = 4,
        X2 = 5,
        Y2 = 6,
        C2 = 7,
        U2 = 8,
        V2 = 9,
        X3 = 10,
        Y3 = 11,
        C3 = 12,
        U3 = 13,
        V3 = 14,
        X4 = 15,
        Y4 = 16,
        C4 = 17,
        U4 = 18,
        V4 = 19
    };

    static const int VERTEX_SIZE = 2 + 1 + 2;
    static const int SPRITE_SIZE = 4 * VERTEX_SIZE;


    virtual ~Sprite();

protected:
    vertex_array_t vertices;

private:
    Color color;
    float x, y;
    float width, height;
    float originX, originY;
    float rotation;
    float scaleX, scaleY;
    bool dirty;
    Rectangle bounds;
    void initialize ( const gdx::Texture::ptr& texture, int srcX, int srcY, int srcWidth, int srcHeight );
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_SPRITE_HPP_
