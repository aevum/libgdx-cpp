
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

#include "gdx-cpp/utils/Disposable.hpp"
#include "gdx-cpp/utils/Aliases.hpp"
#include "gdx-cpp/graphics/g2d/detail/gdx2d.h"

#include <string>
#include <vector>
#include <istream>
#include "gdx-cpp/graphics/Pixmap.hpp"
#include "gdx-cpp/graphics/Color.hpp"

namespace gdx_cpp {
namespace graphics {
namespace g2d {

class Gdx2DPixmap: public graphics::Pixmap {
public:
    typedef ref_ptr_maker<Gdx2DPixmap>::type ptr;

    static const int GDX2D_SCALE_LINEAR = 1;

    static void setBlending (const Blending& blending);
    static void setFilter (const Filter& filter);
    static Blending getBlending ();
    
    Gdx2DPixmap (std::istream& in, int requestedFormat);
    Gdx2DPixmap (int width, int height, int format);
    Gdx2DPixmap (const Gdx2DPixmap& other);
    Gdx2DPixmap (unsigned char* encodedData, int offset, int len, int requestedFormat);

    static Gdx2DPixmap* newPixmap (int width,int height,int format);
    static Gdx2DPixmap* newPixmap (std::istream& in, int requestedFormat);

    void setColor(float r, float g, float b, float a);
    void setColor(const gdx_cpp::graphics::Color& color);
    
    void dispose ();
    void fill ();
    void drawPixel (int x,int y);
    int getPixel (int x,int y) const;
    void drawLine (int x, int y, int x2, int y2);
    void drawRectangle (int x, int y, int width, int height);
    void drawCircle (int x, int y, int radius);
    void fillRectangle (int x, int y, int width, int height);
    void fillCircle (int x, int y, int radius);
    void drawPixmap (const gdx_cpp::graphics::Pixmap& src, int srcX, int srcY, int dstX, int dstY, int width);
    void drawPixmap (const graphics::Pixmap& src,int srcX,int srcY,int srcWidth,int srcHeight,int dstX,int dstY,int dstWidth,int dstHeight);    
    void drawPixmap(const gdx_cpp::graphics::Pixmap& pixmap, int x, int y, int srcx, int srcy, int srcWidth, int srcHeight);
    void setStrokeWidth(int width);
    
    PixmapType getType() const { return Pixmap::Gdx2d; }
    
    const unsigned char* getPixels ();
    int getHeight () const;
    int getWidth () const;
    const Pixmap::Format& getFormat ();
    
    int getGLInternalFormat () const;
    int getGLFormat () const;
    int getGLType () const;
    void setScale(float scaleX, float scaleY);
    
    const std::string getFormatString ();
    
    static void setBlend (int blend);
    static void setScale (int scale);
    
    static struct init {
      init()
      {
        Gdx2DPixmap::setBlend(GDX2D_BLEND_SRC_OVER);
        Gdx2DPixmap::setScale(GDX2D_SCALE_LINEAR);
      }
      
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

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_GDX2DPIXMAP_HPP_
