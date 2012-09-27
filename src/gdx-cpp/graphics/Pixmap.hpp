
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
#include "gdx-cpp/internal/memory"
#include <string>

#include "gdx-cpp/files/FileHandle.hpp"

namespace gdx {

class Color;

class Pixmap: public Disposable {
public:
    typedef ref_ptr_maker<Pixmap>::shared_ptr_t ptr;

    enum Blending {
        None, SourceOver
    };

    enum Filter {
        NearestNeighbour, BiLinear
    };

    enum PixmapType {
        Gdx2d,
        Svg
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
        static const gdx::Pixmap::Format& fromGdx2DPixmapFormat (int format);

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
        Format(const std::string& p_name) : name(p_name) {
        }
    };

//     Pixmap (int width, int height, const Format& format) ;
//     Pixmap (unsigned char* encodedData, int offset, int len) ;
//     Pixmap (FileHandle& file) ;
//     Pixmap (gdx::Gdx2DPixmap* pixmap) ;

    static Pixmap::ptr newFromRect(int width, int height, const Format& format, PixmapType pixType);
    static Pixmap::ptr newFromPixmap(const Pixmap& pixmap);
    static Pixmap::ptr newFromFile(const gdx::FileHandle::ptr file);
      

    virtual PixmapType getType() const = 0;
    virtual void setColor (float r,float g,float b,float a) = 0;
    virtual void setColor (const Color& color) = 0;
    virtual void fill () = 0;
    virtual void setStrokeWidth (int width) = 0;
    virtual void drawLine (int x,int y,int x2,int y2) = 0;
    virtual void drawRectangle (int x,int y,int width,int height) = 0;
    virtual void drawPixmap (const Pixmap& pixmap,int x,int y,int srcx,int srcy,int srcWidth,int srcHeight) = 0;
    virtual void drawPixmap (const Pixmap& pixmap,int srcx,int srcy,int srcWidth,int srcHeight,int dstx,int dsty,int dstWidth,int dstHeight) = 0;
    virtual void fillRectangle (int x,int y,int width,int height) = 0;
    virtual void drawCircle (int x,int y,int radius) = 0;
    virtual void fillCircle (int x,int y,int radius) = 0;
    virtual int getPixel (int x,int y) const = 0;
    virtual int getWidth () const = 0;
    virtual int getHeight () const = 0;
    virtual void dispose () = 0;
    virtual void drawPixel (int x,int y) = 0;
    virtual int getGLFormat () const = 0;
    virtual int getGLInternalFormat () const = 0;
    virtual int getGLType () const = 0;
    virtual const unsigned char* getPixels () = 0;
    virtual const Format& getFormat () = 0;
    virtual void setScale(float scaleX, float scaleY) = 0;


    virtual ~Pixmap() { }
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_PIXMAP_HPP_
