
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

namespace gdx_cpp {
namespace graphics {
namespace g2d {

class Gdx2DPixmap: public utils::Disposable {
public:
    typedef ref_ptr_maker<Gdx2DPixmap>::type ptr;

    static const int GDX2D_SCALE_LINEAR = 1;

    Gdx2DPixmap (std::istream& in, int requestedFormat);
    Gdx2DPixmap (int width, int height, int format);
    Gdx2DPixmap (const Gdx2DPixmap& other);
    Gdx2DPixmap (unsigned char* encodedData, int offset, int len, int requestedFormat);

    static Gdx2DPixmap::ptr newPixmap (int width,int height,int format);
    static Gdx2DPixmap::ptr newPixmap (std::istream& in, int requestedFormat);
    
    void dispose ();
    void clear (int color);
    void setPixel (int x,int y,int color);
    int getPixel (int x,int y);
    void drawLine (int x,int y,int x2,int y2,int color);
    void drawRect (int x,int y,int width,int height,int color);
    void drawCircle (int x,int y,int radius,int color);
    void fillRect (int x,int y,int width,int height,int color);
    void fillCircle (int x,int y,int radius,int color);
    void drawPixmap (const Gdx2DPixmap& src,int srcX,int srcY,int dstX,int dstY,int width,int height);
    void drawPixmap (const Gdx2DPixmap& src,int srcX,int srcY,int srcWidth,int srcHeight,int dstX,int dstY,int dstWidth,int dstHeight);
    
    const unsigned char*const getPixels ();
    int getHeight ();
    int getWidth ();
    int getFormat ();
    int getGLInternalFormat ();
    int getGLFormat ();
    int getGLType ();
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
  gdx2d_pixmap* pixData;

private:

};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_GDX2DPIXMAP_HPP_
