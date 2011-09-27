/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License") = 0;
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

#ifndef GDX_CPP_GRAPHICS_G2D_SVG_SVGPIXMAPINTERFACE_H
#define GDX_CPP_GRAPHICS_G2D_SVG_SVGPIXMAPINTERFACE_H

#include "gdx-cpp/graphics/Color.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"

namespace gdx_cpp {

namespace graphics {

namespace g2d {

namespace svg {

/** Interface to an svg backend. Will provide the draw operations required to render svgs.
 */
class SvgPixmapInterface : public Pixmap
{
public:
    enum LineCap {
        ButtLineCap,
        SquareLineCap,
        RoundLineCap
    };

    enum LineJoin {
        MiterJoin    = 0,
        MiterJoinRevert  = 1,
        RoundJoin        = 2,
        BevelJoin        = 3,
        MiterJoinRound   = 4
    };

    virtual void setImageDimension(int width, int height) = 0;
    virtual void beginPath() = 0;
    virtual void begin() = 0;
    virtual void endPath() = 0;
    virtual void end() = 0;
    virtual void fillNone() = 0;
    virtual void fill(gdx_cpp::graphics::Color color) = 0;
    virtual void fillOpacity(float opactiy) = 0;
    virtual void strokeNone() = 0;
    virtual void stroke(gdx_cpp::graphics::Color color) = 0;
    virtual void setStrokeWidth(float width) = 0;
    virtual void setTranslation(float x, float y) = 0;
    virtual void setSkew(float skewX, float skewY) = 0;
    virtual void setRotationTranslation(float rotation, float x, float y) = 0;
    virtual void setStrokeOpacity(float opacit) = 0;
    virtual void setLineJoin(LineJoin join) = 0;
    virtual void setLineCap(LineCap cap) = 0;
    virtual void setMiterLimit(float limit) = 0;
    virtual void transAffine(const std::vector<float>& affine) = 0;
    virtual void setRotation(float radians) = 0;
    virtual void setScaling(float scaleX, float scaleY) = 0;
    virtual void moveTo(float x, float y, bool relative = false) = 0;
    virtual void lineTo(float x, float y, bool relative = false) = 0;
    virtual void curve3(float x, float y, bool relative = false) = 0;
    virtual void curve3(float x, float y, float x1, float y1, bool relative = false) = 0;
    
    virtual void closeSubPath() = 0;
    virtual void verticalLineTo(float y, bool relative = false) = 0;
    virtual void horizontalLineTo(float x, bool relative = false) = 0;
    virtual void curve4(float x1, float y1, float x2, float y2, float x, float y, bool relative = false) = 0;
    virtual void curve4(float x2, float y2, float x, float y, bool relative = false) = 0;
    

};

}

}

}

}

#endif // GDX_CPP_GRAPHICS_G2D_SVG_SVGPIXMAPINTERFACE_H
