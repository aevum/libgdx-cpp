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

#ifndef GDX_CPP_UTILS_SVGRENDERERHANDLER_HPP
#define GDX_CPP_UTILS_SVGRENDERERHANDLER_HPP

#include "gdx-cpp/graphics/Color.hpp"
#include <vector>
#include <list>

namespace gdx {

/** Base handler for svg images. This interface is used to interpret Svg Specification data
 *
 */
class SvgRendererHandler
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

    class transform {
    public:
        virtual void skew_x(float skew) = 0;
        virtual void skew_y(float skew) = 0;
        virtual void affine(const std::vector<float>& matrix) = 0;
        virtual void translate(float x, float y) = 0;
        virtual void rotate(float radians) = 0;
        virtual void rotate_trasnlate(float radians, float x, float y) = 0;
        virtual void scale(float scale_x, float scale_y) = 0;
        virtual void skew(float x, float y) = 0;

        virtual ~transform() { }
    };
    
    struct GradientStopData {
        gdx::Color color;
        float opacity;
        float offset;
        GradientStopData() : color(0, 0, 0,1), opacity(1), offset(0) {
        }

        virtual ~GradientStopData() { }
    };

    struct LinearGradient {
        float x1,x2,y1,y2;
        transform* gradient_transform;
        std::vector< GradientStopData > stops;

        LinearGradient() : x1(0), x2(0), y1(0), y2(0), gradient_transform(nullptr) { }
        virtual ~LinearGradient() { delete gradient_transform; }
    };

    struct RadialGradient {
        float cx, cy, fx, fy, r;
        transform* gradient_transform;
        std::vector< GradientStopData > stops;
        
        RadialGradient() : cx(0), cy(0), fx(0), fy(0), r(0), gradient_transform(nullptr) { }
        virtual ~RadialGradient() { delete gradient_transform; }
    };
    
    virtual void setImageDimension(int width, int height) = 0;
    virtual void beginPath() = 0;
    virtual void begin() = 0;
    virtual void endPath() = 0;
    virtual void end() = 0;
    virtual void fillNone() = 0;
    virtual void fill(const gdx::Color& color) = 0;
    virtual void fillOpacity(float opactiy) = 0;
    virtual void strokeNone() = 0;
    virtual void stroke(gdx::Color color) = 0;
    virtual void setStrokeWidth(float width) = 0;
    virtual void setStrokeOpacity(float opacit) = 0;
    virtual void setLineJoin(LineJoin join) = 0;
    virtual void setLineCap(LineCap cap) = 0;
    virtual void setMiterLimit(float limit) = 0;
    virtual void moveTo(float x, float y, bool relative = false) = 0;
    virtual void lineTo(float x, float y, bool relative = false) = 0;
    virtual void curve3(float x, float y, bool relative = false) = 0;
    virtual void curve3(float x, float y, float x1, float y1, bool relative = false) = 0;

    virtual void boundingRect(float& x1, float& y1, float& x2, float& y2) = 0;
    virtual void fillLinearGradient(const LinearGradient&) = 0;
    virtual void fillRadialGradient(const RadialGradient&) = 0;
    
    virtual transform* createTransform() = 0;
    virtual transform& currentTransform() = 0;
    
    virtual void closeSubPath() = 0;
    virtual void verticalLineTo(float y, bool relative = false) = 0;
    virtual void horizontalLineTo(float x, bool relative = false) = 0;
    virtual void curve4(float x1, float y1, float x2, float y2, float x, float y, bool relative = false) = 0;
    virtual void curve4(float x2, float y2, float x, float y, bool relative = false) = 0;
};

}

#endif // GDX_CPP_UTILS_SVGRENDERERHANDLER_HPP
