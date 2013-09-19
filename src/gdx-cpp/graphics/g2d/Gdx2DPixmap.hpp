
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

#ifndef GDX_CPP_GRAPHICS_G2D_GDX2DPIXMAP_HPP_
#define GDX_CPP_GRAPHICS_G2D_GDX2DPIXMAP_HPP_

#include <istream>
#include <string>
#include <vector>

#include "gdx-cpp/files/FileHandle.hpp"
#include "gdx-cpp/graphics/Color.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"
#include "gdx-cpp/internal/memory"
#include "gdx-cpp/utils/Disposable.hpp"

extern "C" struct gdx2d_pixmap;

namespace gdx {

class Gdx2DPixmap: public Pixmap {
public:
    typedef ref_ptr_maker<Gdx2DPixmap>::shared_ptr_t ptr;

    static const int GDX2D_SCALE_LINEAR = 1;

    static void setBlending ( const Blending& blending );
    static void setFilter ( const Filter& filter );
    static Blending getBlending ();

    Gdx2DPixmap ( FileHandle::ptr fhandle, int requestedFormat );
    Gdx2DPixmap ( int width, int height, int format );
    Gdx2DPixmap ( const Gdx2DPixmap& other );
    Gdx2DPixmap ( unsigned char* encodedData, int offset, int len, int requestedFormat );

    static Gdx2DPixmap* pixmapFromByteArray ( unsigned char* buffer, unsigned int size, int requestedFormat );
    static Gdx2DPixmap* newPixmap ( int width,int height,int format );
    static Gdx2DPixmap* newPixmapFromFile ( FileHandle::ptr fhandle, int requestedFormat );
    static Gdx2DPixmap* newPixmapFromBuffer ( unsigned char* data, int len, int requestedFormat );

    void setColor ( float r, float g, float b, float a ) override;
    void setColor ( const gdx::Color& color ) override;

    void dispose () override;
    void fill () override;
    void drawPixel ( int x,int y ) override;
    int getPixel ( int x,int y ) const override;
    void drawLine ( int x, int y, int x2, int y2 ) override;
    void drawRectangle ( int x, int y, int width, int height ) override;
    void drawCircle ( int x, int y, int radius ) override;
    void fillRectangle ( int x, int y, int width, int height ) override;
    void fillCircle ( int x, int y, int radius ) override;
    void drawPixmap ( const gdx::Pixmap& src, int srcX, int srcY, int dstX, int dstY, int width );
    void drawPixmap ( const Pixmap& src,int srcX,int srcY,int srcWidth,int srcHeight,int dstX,int dstY,int dstWidth,int dstHeight ) override;
    void drawPixmap ( const gdx::Pixmap& pixmap, int x, int y, int srcx, int srcy, int srcWidth, int srcHeight ) override;
    void setStrokeWidth ( int width ) override;

    PixmapType getType() const override {
        return Pixmap::PixmapType::PixmapType_Gdx2d;
    }

    const unsigned char* getPixels () override;
    int getHeight () const override;
    int getWidth () const override;
    const Pixmap::Format& getFormat () override;

    int getGLInternalFormat () const override;
    int getGLFormat () const override;
    int getGLType () const override;
    void setScale ( float scaleX, float scaleY ) override;

    const std::string getFormatString ();

    static void setBlend ( int blend );
    static void setScale ( int scale );

    static struct init {
        init() ;
    } init;

    virtual ~Gdx2DPixmap();

protected:
    int width;
    int height;
    int format;
    int color;
    
    gdx2d_pixmap* pixData;
private:
    static Blending blending;
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_GDX2DPIXMAP_HPP_
