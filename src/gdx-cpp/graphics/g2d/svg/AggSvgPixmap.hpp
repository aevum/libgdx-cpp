/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 *  @author aevum team
 */

#ifndef GDX_CPP_GRAPHICS_G2D_AGGSVGPIXMAP_HPP
#define GDX_CPP_GRAPHICS_G2D_AGGSVGPIXMAP_HPP

#include <stdexcept>

#include "SvgPixmapInterface.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"
#include "gdx-cpp/Files.hpp"
#include "gdx-cpp/utils/XmlReader.hpp"
#include "SvgParser.hpp"

#include <agg_svg_path_renderer.h>
#include <agg_rendering_buffer.h>
#include <agg_pixfmt_rgba.h>
#include <agg_scanline_p.h>

#include <gdx-cpp/graphics/GL10.hpp>

#undef GL_RGBA
#undef GL_UNSIGNED_BYTE

namespace gdx_cpp {

namespace graphics {

namespace g2d {

namespace svg {

/** Implements the SvgPixmapInterface using the AntiGrains Svg backend
 *
 */
class AggSvgPixmap : public SvgPixmapInterface
{
public:

    static AggSvgPixmap* newFromFile(const Files::fhandle_ptr& file) {
        static utils::XmlReader reader;

        AggSvgPixmap* pix = new AggSvgPixmap;        
        SvgParser parser(*pix);
        
        parser.render(reader.parse(*file).get());
        
        return pix;
    }
    
    AggSvgPixmap()
        : width(0), height(0) , data(0) , scaleX(1), scaleY(1)
    {
    }

    AggSvgPixmap(int width, int height)
    : width(width), height(height) , data(0)  , scaleX(1), scaleY(1)
    {
    }

    inline void setImageDimension(int width, int height) {
        this->width = width;
        this->height = height;
    }
    
    inline void begin() {
        renderer.push_attr();
    }
    
    inline void beginPath() {
        renderer.begin_path();
    }
    
    inline void closeSubPath() {
        renderer.close_subpath();
    }
    
    inline void curve3(float x, float y, bool relative = false) {
      renderer.curve3(x, y, relative);
    }
    
    inline void curve3(float x, float y, float x1, float y1, bool relative = false) {
        renderer.curve3(x, y, x1, y1 , relative);
    }
    
    inline void curve4(float x2, float y2, float x, float y, bool relative = false) {
        renderer.curve4(x2, y2, x, y, relative);
    }
    
    inline void curve4(float x1, float y1, float x2, float y2, float x, float y, bool relative = false) {
        renderer.curve4(x1, y1, x2, y2, x, y, relative);
    }

    inline void end() {
        renderer.pop_attr();
    }
    
    inline void endPath() {
        renderer.end_path();
    }
    
    inline void fill(Color color) {
        renderer.fill(agg::rgba_pre(color.r, color.g, color.b));
    }
    
    inline void fillNone() {
        renderer.fill_none();
    }
    
    inline void fillOpacity(float opactiy) {
        renderer.fill_opacity(opactiy);
    }
    
    inline void horizontalLineTo(float x, bool relative = false) {
        renderer.hline_to(x, relative);
    }
    
    inline void lineTo(float x, float y, bool relative = false) {
        renderer.line_to(x, y, relative);
    }
    
    inline void moveTo(float x, float y, bool relative = false) {
        renderer.move_to(x, y, relative);
    }
    
    inline void setLineCap(LineCap cap) {
        renderer.line_cap((agg::line_cap_e) cap);
    }
    
    inline void setLineJoin(LineJoin join) {
        renderer.line_join((agg::line_join_e) join);
    }
    
    inline void setMiterLimit(float limit) {
        renderer.miter_limit(limit);
    }
    
    inline void setRotation(float radians) {
        renderer.transform().premultiply(agg::trans_affine_rotation(radians));
    }
    
    inline void setRotationTranslation(float rotation, float x, float y) {
        agg::trans_affine t = agg::trans_affine_translation(-x, -y);
        t *= agg::trans_affine_rotation(rotation);
        t *= agg::trans_affine_translation(x, y);
        renderer.transform().premultiply(t);
    }
    
    inline void setScaling(float scaleX, float scaleY) {
        renderer.transform().premultiply(agg::trans_affine_scaling(scaleX, scaleY));
    }
    
    inline void setSkew(float skewX, float skewY) {
        renderer.transform().premultiply(agg::trans_affine_skewing(agg::deg2rad(skewX), agg::deg2rad(skewY)));
    }
    
    inline void setStrokeOpacity(float opacit) {
        renderer.stroke_opacity(opacit);
    }
    
    inline void setStrokeWidth(float width) {
        renderer.stroke_width(width);
    }
    
    inline void setTranslation(float x, float y) {
        renderer.transform().premultiply(agg::trans_affine_translation(x, y));
    }
    
    inline void stroke(Color color) {
        renderer.stroke(agg::rgba_pre(color.r, color.g, color.b, color.a));
    }
    
    inline void strokeNone() {
        renderer.stroke_none();
    }
    
    inline void transAffine(const std::vector< float >& affine) {
        renderer.transform().premultiply(agg::trans_affine(affine[0], affine[1], affine[2], affine[3], affine[4], affine[5]));
    }
    
    inline void verticalLineTo(float y, bool relative = false) {
        renderer.vline_to(y, relative);
    }

    inline void setScale(float scaleX, float scaleY) {
        this->scaleX = scaleX;
        this->scaleY = scaleY;
    }

    void dispose() {
        delete [] data;
        data = NULL;
    }

    void drawCircle(int x, int y, int radius) {
        
    }

    void drawLine(int x, int y, int x2, int y2) {
        renderer.begin_path();
        renderer.move_to(x, y);
        renderer.line_to(x, y);
        renderer.end_path();
    }

    void drawPixel(int x, int y) {
        renderer.begin_path();
        renderer.move_to(x, y);
        renderer.line_to(x + 1, y + 1);
        renderer.end_path();
    }

    void drawPixmap(const gdx_cpp::graphics::Pixmap& pixmap, int x, int y, int srcx, int srcy, int srcWidth, int srcHeight) {
    }

    void drawPixmap(const gdx_cpp::graphics::Pixmap& pixmap, int srcx, int srcy, int srcWidth, int srcHeight, int dstx, int dsty, int dstWidth, int dstHeight) {
    }

    void drawRectangle(int x, int y, int width, int height) {
        renderer.begin_path();
        renderer.move_to(x, y);
        renderer.line_to(x + width, y);        
        renderer.line_to(x, y + height);
        renderer.move_to(x + width, y + height);
        renderer.line_to(x + width, y);
        renderer.line_to(x, y + height);
        renderer.end_path();
    }

    void fill() {
        renderer.fill(agg::rgba8_pre(color.r, color.b, color.g, color.a));
    }

    void fillCircle(int x, int y, int radius) {

    }

    void fillRectangle(int x, int y, int width, int height) {

    }

    const gdx_cpp::graphics::Pixmap::Format& getFormat() {
        return Pixmap::Format::RGBA8888;
    }

    int getGLFormat() const {
        return GL10::GL_RGBA;
    }

    int getGLInternalFormat() const {
        return GL10::GL_RGBA;
    }
    
    int getGLType() const {
        return GL10::GL_UNSIGNED_BYTE;
    }

    int getHeight() const {
        return height * scaleX;
    }

    int getPixel(int x, int y) const {
        return 0;
    }

    const unsigned char* getPixels() {
        typedef agg::pixfmt_rgba32 pixfmt;
        typedef agg::renderer_base<pixfmt> renderer_base;
        typedef agg::renderer_scanline_aa_solid<renderer_base> renderer_solid;
        
        if (width <= 0 || height <= 0) {
            throw std::runtime_error("Missing width or height values to render svg");
        }

        int scaledWidth = width * scaleX;
        int scaledHeight = height * scaleY;
        
        if (!data || (strlen((char*) data) !=  scaledWidth * scaledHeight * 4)) {
            delete [] data;
            data = new unsigned char[scaledWidth * scaledHeight * 4];
            buffer.attach(data, scaledWidth, scaledHeight, scaledWidth * 4);
        }

        pixfmt pixf(buffer);
        renderer_base rb(pixf);
        renderer_solid ren(rb);

        rb.clear(agg::rgba(1,1,1,0));

        agg::rasterizer_scanline_aa<> ras;
        agg::scanline_p8 sl;
        agg::trans_affine mtx;

        mtx *= agg::trans_affine_scaling(scaleX, scaleY);

        renderer.render(ras, sl, ren, mtx, rb.clip_box(), 1.0);

        return buffer.buf();
    }

    void setColor(float r, float g, float b, float a) {
        color = agg::rgba8(r,g,b,a);
    }

    void setColor(const gdx_cpp::graphics::Color& color) {
        this->color = agg::rgba8(color.r, color.g, color.b, color.a);
    }

    PixmapType getType() const {
        return Pixmap::Svg;
    }

    int getWidth() const {
        return width * scaleY;
    }

    void setStrokeWidth(int width) {
        this->setStrokeWidth((float)width);
    }

    ~AggSvgPixmap() {
        delete [] data;
    }

    agg::rendering_buffer buffer;
private:
    agg::svg::path_renderer renderer;
    agg::rgba8 color;

    float scaleX,scaleY;
    int width;
    int height;
    unsigned char* data;
};

}

}

}

}
#endif // GDX_CPP_GRAPHICS_G2D_AGGSVGPIXMAP_HPP
