
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
#include "gdx-cpp/utils/MatrixBase.hpp"

namespace gdx {

class TextureRegion {
public:
    static TextureRegion newFromTexture ( Texture::ptr texture );
    static TextureRegion newFromRegion ( TextureRegion& region );

    TextureRegion ();
    TextureRegion ( Texture::ptr _texture );
    TextureRegion ( Texture::ptr _texture, int x, int y, int width, int height );
    TextureRegion ( Texture::ptr _texture, float u, float v, float u2, float v2 );
    TextureRegion ( const TextureRegion& region );
    TextureRegion ( TextureRegion& region, int x, int y, int width, int height );
    virtual void setRegion ( const Texture::ptr& texture );
    virtual void setRegion ( int x,int y,int width,int height );
    virtual void setRegion ( float u,float v,float u2,float v2 );
    virtual void setRegion ( const TextureRegion& region );
    virtual void setRegion ( const TextureRegion& region, int x, int y, int width, int height );
    const Texture::ptr& getTexture () const;
    void setTexture ( const Texture::ptr& texture );
    
    bool isValid() const { return this->texture != nullptr; }
    
    float getU () const;
    void setU ( float u );
    float getV () const;
    void setV ( float v );
    float getU2 () const;
    void setU2 ( float u2 );
    float getV2 () const;
    void setV2 ( float v2 );
    int getRegionX () const;
    void setRegionX ( int x );
    int getRegionY () const;
    void setRegionY ( int y );
    int getRegionWidth () const;
    void setRegionWidth ( int width );
    int getRegionHeight () const;
    void setRegionHeight ( int height );
    void flip ( bool x,bool y );
    void scroll ( float xAmount,float yAmount );

    template < std::size_t tileWidth, std::size_t tileHeight >
    MatrixBase< TextureRegion, tileWidth, tileHeight > split () {
        int x = getRegionX();
        int y = getRegionY();
        int width = getRegionWidth();
        int height = getRegionHeight();

        if ( width < 0 ) {
            x = x - width;
            width = -width;
        }

        if ( height < 0 ) {
            y = y - height;
            height = -height;
        }

        const int rows = height / tileHeight;
        const int cols = width / tileWidth;

        MatrixBase< TextureRegion, tileHeight, tileWidth > matrix ( rows, cols );

        for ( int row = 0, startX = x; row < rows; row++, y += tileHeight ) {
            x = startX;
            for ( int col = 0; col < cols; col++, x += tileWidth ) {
                matrix[row][col] = TextureRegion(texture, x, y, tileWidth, tileHeight);
            }
        }

        return matrix;
    }

    template <std::size_t tileWidth, std::size_t tileHeight >
    MatrixBase< TextureRegion, tileWidth, tileHeight > split ( const Texture::ptr& texture ) {
        TextureRegion region ( texture );
        return region.split < tileWidth, tileHeight > ();
    }

    float u, v;
    float u2, v2;

    virtual ~TextureRegion();

protected:
    Texture::ptr texture;

private:

};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_TEXTUREREGION_HPP_
