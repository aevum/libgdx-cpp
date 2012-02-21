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
 *  @author aevum team
 */


#include <gdx-cpp/graphics/g2d/svg/AggSvgPixmap.hpp>

#include <gdx-cpp/graphics/GL10.hpp>

#include <agg_svg_path_renderer.h>
#include <agg_rendering_buffer.h>
#include <agg_pixfmt_rgb.h>
#include <agg_scanline_p.h>

#undef GL_RGBA
#undef GL_UNSIGNED_BYTE

using namespace gdx_cpp::graphics::g2d::svg;
using namespace gdx_cpp::utils;
using namespace gdx_cpp::graphics;

namespace gdx_cpp {
namespace graphics {
namespace g2d {
namespace svg {

class AggTransform : public gdx_cpp::utils::SvgRendererHandler::transform {
public:  
    friend class AggSvgPixmap;
    
    AggTransform()
            : transform(new agg::trans_affine),
            should_del(true)
    {
    }

    AggTransform(agg::trans_affine& _transform)
            : transform(&_transform),
            should_del(false)
    {
    }

    virtual void affine(const std::vector< float >& matrix) {
        transform->premultiply(agg::trans_affine(matrix[0], matrix[1], matrix[2], matrix[3], matrix[4], matrix[5]));
    }

    virtual void rotate(float radians) {
        transform->rotate(radians);
    }

    virtual void rotate_trasnlate(float radians, float x, float y) {
        agg::trans_affine t = agg::trans_affine_translation(-x, -y);
        t *= agg::trans_affine_rotation(radians);
        t *= agg::trans_affine_translation(x, y);
        transform->premultiply(t);
    }

    virtual void scale(float scale_x, float scale_y) {
        transform->premultiply(agg::trans_affine_scaling(scale_x, scale_y));
    }

    virtual void skew(float x, float y) {
        transform->premultiply(agg::trans_affine_skewing(agg::deg2rad(x), agg::deg2rad(y)));
    }

    virtual void skew_x(float skew) {
        transform->premultiply(agg::trans_affine_skewing(agg::deg2rad(skew), 0));
    }

    virtual void skew_y(float skew) {
        transform->premultiply(agg::trans_affine_skewing(0, agg::deg2rad(skew)));
    }

    virtual void translate(float x, float y) {
        transform->premultiply(agg::trans_affine_translation(x, y));
    }

    ~AggTransform() {
        if (should_del) {
            delete transform;
        }
    }

private:
    agg::trans_affine* transform;
    ///ps: this is lame...
    bool should_del;
};

}
}
}
}

struct AggSvgPixmap::impl {
    agg::svg::path_renderer renderer;
    agg::rgba8 color;

    svg::AggTransform transform;
};


AggSvgPixmap::AggSvgPixmap(int width, int height)
        : pimpl(new  AggSvgPixmap::impl),
        width(width), height(height) , data(0)  , scaleX(1), scaleY(1)
{
}

void AggSvgPixmap::curve3(float x, float y, bool relative) {
    pimpl->renderer.curve3(x, y, relative);
}

void AggSvgPixmap::closeSubPath() {
    pimpl->renderer.close_subpath();
}

void AggSvgPixmap::beginPath() {
    pimpl->renderer.begin_path();
}

void AggSvgPixmap::begin() {
    pimpl->renderer.push_attr();
}

void AggSvgPixmap::setImageDimension(int width, int height) {
    this->width = width;
    this->height = height;
}

AggSvgPixmap::AggSvgPixmap() : pimpl(new AggSvgPixmap::impl), width(0), height(0) , data(0) , scaleX(1), scaleY(1)
{
}

void AggSvgPixmap::curve3(float x, float y, float x1, float y1, bool relative) {
    pimpl->renderer.curve3(x, y, x1, y1 , relative);
}

void AggSvgPixmap::curve4(float x2, float y2, float x, float y, bool relative) {
    pimpl->renderer.curve4(x2, y2, x, y, relative);
}

void AggSvgPixmap::curve4(float x1, float y1, float x2, float y2, float x, float y, bool relative) {
    pimpl->renderer.curve4(x1, y1, x2, y2, x, y, relative);
}

void AggSvgPixmap::end() {
    pimpl->renderer.pop_attr();
}

void AggSvgPixmap::endPath() {
    pimpl->renderer.end_path();
}

void AggSvgPixmap::fill(Color color) {
    pimpl->renderer.fill(agg::rgba_pre(color.r, color.g, color.b));
}

void AggSvgPixmap::fillNone() {
    pimpl->renderer.fill_none();
}

void AggSvgPixmap::fillOpacity(float opactiy) {
    pimpl->renderer.fill_opacity(opactiy);
}

void AggSvgPixmap::horizontalLineTo(float x, bool relative) {
    pimpl->renderer.hline_to(x, relative);
}

void AggSvgPixmap::lineTo(float x, float y, bool relative) {
    pimpl->renderer.line_to(x, y, relative);
}

void AggSvgPixmap::moveTo(float x, float y, bool relative) {
    pimpl->renderer.move_to(x, y, relative);
}

void AggSvgPixmap::setLineCap(utils::SvgRendererHandler::LineCap cap) {
    pimpl->renderer.line_cap((agg::line_cap_e) cap);
}

void AggSvgPixmap::setLineJoin(utils::SvgRendererHandler::LineJoin join) {
    pimpl->renderer.line_join((agg::line_join_e) join);
}

void AggSvgPixmap::setMiterLimit(float limit) {
    pimpl->renderer.miter_limit(limit);
}

void AggSvgPixmap::setSkew(float skewX, float skewY) {
    pimpl->renderer.transform().premultiply(agg::trans_affine_skewing(agg::deg2rad(skewX), agg::deg2rad(skewY)));
}

void AggSvgPixmap::setStrokeOpacity(float opacit) {
    pimpl->renderer.stroke_opacity(opacit);
}

void AggSvgPixmap::setStrokeWidth(float width) {
    pimpl->renderer.stroke_width(width);
}

void AggSvgPixmap::stroke(Color color) {
    pimpl->renderer.stroke(agg::rgba_pre(color.r, color.g, color.b, color.a));
}

void AggSvgPixmap::strokeNone() {
    pimpl->renderer.stroke_none();
}

void AggSvgPixmap::verticalLineTo(float y, bool relative) {
    pimpl->renderer.vline_to(y, relative);
}

void AggSvgPixmap::setScale(float scaleX, float scaleY) {
    this->scaleX = scaleX;
    this->scaleY = scaleY;
}

void AggSvgPixmap::dispose() {
    delete [] data;
    data = NULL;
}

void AggSvgPixmap::drawCircle(int x, int y, int radius) {

}

void AggSvgPixmap::drawLine(int x, int y, int x2, int y2) {
    pimpl->renderer.begin_path();
    pimpl->renderer.move_to(x, y);
    pimpl->renderer.line_to(x, y);
    pimpl->renderer.end_path();
}

void AggSvgPixmap::drawPixel(int x, int y) {
    pimpl->renderer.begin_path();
    pimpl->renderer.move_to(x, y);
    pimpl->renderer.line_to(x + 1, y + 1);
    pimpl->renderer.end_path();
}

void AggSvgPixmap::drawPixmap(const gdx_cpp::graphics::Pixmap& pixmap, int x, int y, int srcx, int srcy, int srcWidth, int srcHeight) {
}

void AggSvgPixmap::drawPixmap(const gdx_cpp::graphics::Pixmap& pixmap, int srcx, int srcy, int srcWidth, int srcHeight, int dstx, int dsty, int dstWidth, int dstHeight) {
}

void AggSvgPixmap::drawRectangle(int x, int y, int width, int height) {
    pimpl->renderer.begin_path();
    pimpl->renderer.move_to(x, y);
    pimpl->renderer.line_to(x + width, y);
    pimpl->renderer.line_to(x, y + height);
    pimpl->renderer.move_to(x + width, y + height);
    pimpl->renderer.line_to(x + width, y);
    pimpl->renderer.line_to(x, y + height);
    pimpl->renderer.end_path();
}

void AggSvgPixmap::fillCircle(int x, int y, int radius) {
}

void AggSvgPixmap::fillRectangle(int x, int y, int width, int height) {
}

const gdx_cpp::graphics::Pixmap::Format& AggSvgPixmap::getFormat() {
    return Pixmap::Format::RGBA8888;
}
int AggSvgPixmap::getGLFormat() const {
    return GL10::GL_RGBA;
}
int AggSvgPixmap::getGLInternalFormat() const {
    return GL10::GL_RGBA;
}
int AggSvgPixmap::getGLType() const {
    return GL10::GL_UNSIGNED_BYTE;
}
int AggSvgPixmap::getHeight() const {
    return height * scaleX;
}
int AggSvgPixmap::getPixel(int x, int y) const {
    return 0;
}
const unsigned char* AggSvgPixmap::getPixels() {
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
    }

    agg::rendering_buffer rbuf(data,
                               scaledWidth,
                               scaledHeight,
                               scaledWidth * 4);

    pixfmt pixf(rbuf);
    renderer_base rb(pixf);
    renderer_solid ren(rb);

    rb.clear(agg::rgba8(0,0,0,0));

    agg::rasterizer_scanline_aa<> ras;
    agg::scanline_p8 sl;
    agg::trans_affine mtx;

    mtx *= agg::trans_affine_scaling(scaleX, scaleY);
    
    pimpl->renderer.expand(0.01);
    pimpl->renderer.render(ras, sl, ren, mtx, rb, rb.clip_box(), 1.0);

    return rbuf.buf();
}


void AggSvgPixmap::setColor(float r, float g, float b, float a) {
    pimpl->color = agg::rgba8(r,g,b,a);
}

void AggSvgPixmap::fill() {
    pimpl->renderer.fill(pimpl->color);
}

void AggSvgPixmap::fillRadialGradient(const gdx_cpp::utils::SvgRendererHandler::RadialGradient& gradient) {
    agg::svg::radial_gradient ra_gradient;

    ra_gradient.cx = gradient.cx;
    ra_gradient.cy = gradient.cy;
    ra_gradient.fx = gradient.fx;
    ra_gradient.fy = gradient.fy;
    ra_gradient.r = gradient.r;

    if (gradient.gradient_transform) {
        ra_gradient.transform = *static_cast<AggTransform*>(gradient.gradient_transform)->transform;
    }

    for (int i = 0; i < gradient.stops.size(); ++i) {
        agg::svg::svg_gradient::stop stop;
        const SvgRendererHandler::GradientStopData& data = gradient.stops[i];

        stop.color = agg::rgba(data.color.r, data.color.g, data.color.b, data.color.a);
        stop.opacity = data.opacity;
        stop.offset = data.offset;

        ra_gradient.stops.push_back(stop);
    }

    pimpl->renderer.fill_gradient(ra_gradient);
}
void AggSvgPixmap::fillLinearGradient(const gdx_cpp::utils::SvgRendererHandler::LinearGradient& gradient) {
    agg::svg::linear_gradient li_gradient;

    li_gradient.x1 = gradient.x1;
    li_gradient.y1 = gradient.y1;
    li_gradient.x2 = gradient.x2;
    li_gradient.y2 = gradient.y2;

    if (gradient.gradient_transform) {
        li_gradient.transform = *static_cast<AggTransform*>(gradient.gradient_transform)->transform;
    }

    for (int i = 0; i < gradient.stops.size(); ++i) {
        agg::svg::svg_gradient::stop stop;
        const SvgRendererHandler::GradientStopData& data = gradient.stops[i];

        stop.color = agg::rgba(data.color.r, data.color.g, data.color.b, data.color.a);
        stop.opacity = data.opacity;
        stop.offset = data.offset;

        li_gradient.stops.push_back(stop);
    }

    pimpl->renderer.fill_gradient(li_gradient);
}

void AggSvgPixmap::setColor(const gdx_cpp::graphics::Color& color) {
    pimpl->color = agg::rgba8(color.r, color.g, color.b, color.a);
}

Pixmap::PixmapType AggSvgPixmap::getType() const {
    return Pixmap::Svg;
}

int AggSvgPixmap::getWidth() const {
    return width * scaleY;
}

void AggSvgPixmap::setStrokeWidth(int width) {
    this->setStrokeWidth((float)width);
}

AggSvgPixmap::~AggSvgPixmap() {
    delete [] data;
    delete pimpl;
}

SvgPixmapInterface::transform* AggSvgPixmap::createTransform() {
    return new AggTransform();
}

SvgPixmapInterface::transform* const AggSvgPixmap::currentTransform() {
    return new AggTransform(pimpl->renderer.transform());
}


