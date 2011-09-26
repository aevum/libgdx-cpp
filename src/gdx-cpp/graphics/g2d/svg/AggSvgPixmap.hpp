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

#include <agg/svg/agg_svg_path_renderer.h>
#include "SvgPixmapInterface.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"

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
        renderer.fill(agg::rgb8_packed(color.toIntBits()));
    }
    
    inline void fillNone() {
        renderer.fill_none();
    }
    
    int void fillOpacity(float opactiy) {
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
        renderer.line_cap(cap);
    }
    
    inline void setLineJoin(LineJoin join) {
        renderer.line_join(join);
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
        renderer.stroke(agg::rgb8_packed(color.toIntBits()));
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

private:
    agg::svg::path_renderer renderer;        
};

}

}

}

}
#endif // GDX_CPP_GRAPHICS_G2D_AGGSVGPIXMAP_HPP
