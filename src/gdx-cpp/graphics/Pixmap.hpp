
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

#ifndef GDX_CPP_GRAPHICS_PIXMAP_HPP_
#define GDX_CPP_GRAPHICS_PIXMAP_HPP_

#include "gdx-cpp/utils/Disposable.hpp"
#include "gdx-cpp/utils/Aliases.hpp"
#include "g2d/Gdx2DPixmap.hpp"

namespace gdx_cpp {
    
namespace files {
    class FileHandle;
}

    
namespace graphics {

class Color;

class Pixmap: public utils::Disposable {
public:
    typedef ref_ptr_maker<Pixmap>::type ptr;
    
    enum Blending {
        None, SourceOver
    };

    enum Filter {
        NearestNeighbour, BiLinear
    };

    class Format {
    public:
        const static Format Alpha;
        const static Format LuminanceAlpha;
        const static Format RGB565;
        const static Format RGBA4444;
        const static Format RGB888;
        const static Format RGBA8888;
        
        static int toGdx2DPixmapFormat (const Format& format);
        static const gdx_cpp::graphics::Pixmap::Format& fromGdx2DPixmapFormat (int format);

        inline bool operator == (const Format& other) const {
            return this == &other;
        }

        inline bool operator !=(const Format& other) const {
            return !(*this == other);
        }

        const std::string& toString() const {
            return name;
        }
    private:
        std::string name;
        Format(const std::string& name) : name(name) {
        }
    };

    Pixmap (int width, int height, const Format& format) ;
    Pixmap (unsigned char* encodedData, int offset, int len) ;
    Pixmap (files::FileHandle& file) ;
    Pixmap (gdx_cpp::graphics::g2d::Gdx2DPixmap::ptr pixmap) ;
    
    static void setBlending (const Blending& blending);
    static void setFilter (const Filter& filter);
    static Blending getBlending ();
    
    void setColor (float r,float g,float b,float a);
    void setColor (const Color& color);
    void fill ();
    void setStrokeWidth (int width);
    void drawLine (int x,int y,int x2,int y2);
    void drawRectangle (int x,int y,int width,int height);
    void drawPixmap (const Pixmap& pixmap,int x,int y,int srcx,int srcy,int srcWidth,int srcHeight);
    void drawPixmap (const Pixmap& pixmap,int srcx,int srcy,int srcWidth,int srcHeight,int dstx,int dsty,int dstWidth,int dstHeight);
    void fillRectangle (int x,int y,int width,int height);
    void drawCircle (int x,int y,int radius);
    void fillCircle (int x,int y,int radius);
    int getPixel (int x,int y) const;
    int getWidth () const;
    int getHeight () const;
    void dispose ();
    void drawPixel (int x,int y);
    int getGLFormat () const;
    int getGLInternalFormat () const;
    int getGLType () const;
    const unsigned char* getPixels () const;
    const Format& getFormat ();
protected:
    g2d::Gdx2DPixmap::ptr pixmap;
    int color;

private:
    static Blending blending;
};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_PIXMAP_HPP_
