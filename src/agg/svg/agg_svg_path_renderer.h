//----------------------------------------------------------------------------
// Anti-Grain Geometry - Version 2.3
// Copyright (C) 2002-2005 Maxim Shemanarev (http://www.antigrain.com)
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//----------------------------------------------------------------------------
// Contact: mcseem@antigrain.com
//          mcseemagg@yahoo.com
//          http://www.antigrain.com
//----------------------------------------------------------------------------
//
// SVG path renderer.
//
//----------------------------------------------------------------------------
#ifndef AGG_SVG_PATH_RENDERER_INCLUDED
#define AGG_SVG_PATH_RENDERER_INCLUDED

#include <agg_path_storage.h>
#include "agg_conv_transform.h"
#include "agg_conv_stroke.h"
#include "agg_conv_contour.h"
#include "agg_conv_curve.h"
#include "agg_color_rgba.h"
#include "agg_renderer_scanline.h"
#include "agg_bounding_rect.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_span_interpolator_linear.h"
#include "agg_span_allocator.h"
#include "agg_span_gradient.h"
#include "agg_pixfmt_rgba.h"


#include <iostream>
#include <agg_ellipse.h>

namespace agg
{
namespace svg
{
template<class VertexSource> class conv_count
{
public:
    conv_count(VertexSource& vs) : m_source(&vs), m_count(0) {}

    void count(unsigned n) {
        m_count = n;
    }
    unsigned count() const {
        return m_count;
    }

    void rewind(unsigned path_id) {
        m_source->rewind(path_id);
    }
    unsigned vertex(double* x, double* y)
    {
        ++m_count;
        return m_source->vertex(x, y);
    }

private:
    VertexSource* m_source;
    unsigned m_count;
};

//============================================================================
//defines a gradient data for a path
class svg_gradient {
public:
    enum enum_gradient_type {
        e_linear,
        e_radial
    };

    struct stop {
        rgba8 color;
        float opacity;
        float offset;

        stop() : opacity(1), offset(0) { }
    };

    pod_bvector < stop > stops;
    const enum_gradient_type gradient_type;
    trans_affine transform;

    virtual svg_gradient* clone() = 0;

    svg_gradient(enum_gradient_type grad_type)
            : gradient_type(grad_type)
    {
    }
    svg_gradient(const svg_gradient& other) :
            stops(other.stops),
            gradient_type(other.gradient_type),
            transform(other.transform)
    {
    }

    virtual ~svg_gradient() { }
};

struct linear_gradient : public svg_gradient {
public:
    double x1,y1,x2,y2;

    linear_gradient() : svg_gradient(e_linear), x1(0),y1(0),x2(0),y2(0) { }

    linear_gradient(const linear_gradient& other)
            : svg_gradient(other)
            ,x1(other.x1)
            ,y1(other.y1)
            ,x2(other.x2)
            ,y2(other.y2)
    {
    }

    virtual linear_gradient* clone() {
        return new linear_gradient(*this);
    }

    template <typename color_array_type,
                typename scanline,
                typename renderer_base_type,
                typename rasterizer>
    void  render_gradient(trans_affine& _transform,
                          color_array_type& color_array,
                          rasterizer& ras,
                          scanline& sl,
                          renderer_base_type& renderer_base)
    {
        //------------------------- gradient transformation
        
        this->transform *= _transform;

        double dx = x2 - x1;
        double dy = y2 - y1;
        
        double distance = sqrt(dx * dx + dy * dy);
        double angle = atan2(dy, dx);
        
        this->transform.invert();
        
        this->transform *= agg::trans_affine_translation(-x1, -y1);
        this->transform *= agg::trans_affine_rotation(-angle);

        //-------------------------
        
        typedef agg::span_interpolator_linear<> interpolator_type;
        typedef agg::span_allocator<agg::rgba8> span_allocator_type;
        typedef gradient_x gradient_func_type;
        
        span_allocator_type span_allocator;                  // Span Allocator
        interpolator_type span_interpolator(this->transform);
        
        typedef agg::span_gradient<agg::rgba8,
        interpolator_type,
        gradient_func_type,
        color_array_type > span_gradient_type;

        gradient_func_type grad_func;

        typedef agg::renderer_scanline_aa<renderer_base_type, span_allocator_type,
        span_gradient_type> renderer_gradient_type;

        span_gradient_type span_gradient(span_interpolator, grad_func, color_array, 0, distance);
        renderer_gradient_type ren_gradient(renderer_base, span_allocator, span_gradient);

        agg::render_scanlines(ras, sl, ren_gradient);
    }
};


class radial_gradient : public svg_gradient {
public:
    double cx, cy, r, fx, fy;

    virtual radial_gradient* clone() {
        return new radial_gradient(*this);
    }

    radial_gradient() : svg_gradient(e_radial) , cx(0), cy(0), r(0), fx(0) , fy(0)  { }
    radial_gradient(const radial_gradient& other)
            : svg_gradient(other), cx(other.cx), cy(other.cy), r(other.r), fx(other.fx) , fy(other.fy)  {

    }

    template <typename color_array_type,
                typename scanline,
                typename renderer_base_type,
                typename rasterizer>
    void  render_gradient(trans_affine& _transform,
                          color_array_type& color_array,
                          rasterizer& ras,
                          scanline& sl,
                          renderer_base_type& renderer_base)
    {
        //------------------------- gradient transformation
        
        this->transform *= _transform;
        
        this->transform.invert();        
        this->transform *= agg::trans_affine_translation(-cx, -cy);
        
        //-------------------------
        
        typedef agg::span_interpolator_linear<> interpolator_type;
        typedef agg::span_allocator<agg::rgba8> span_allocator_type;
        typedef gradient_radial_focus gradient_func_type;
        
        span_allocator_type span_allocator;                  // Span Allocator
        interpolator_type span_interpolator(this->transform);
        
        typedef agg::span_gradient<agg::rgba8,
                    interpolator_type,
                    gradient_func_type,
                    color_array_type > span_gradient_type;
        
        gradient_func_type grad_func(r, fx - cx , fy - cy);
        
        typedef agg::renderer_scanline_aa<renderer_base_type, span_allocator_type,
        span_gradient_type> renderer_gradient_type;
        
        span_gradient_type span_gradient(span_interpolator, grad_func, color_array, 0, r);
        
        renderer_gradient_type ren_gradient(renderer_base, span_allocator, span_gradient);
        
        agg::render_scanlines(ras, sl, ren_gradient);

        ras.reset();
    }
};


//============================================================================
// Basic path attributes
struct path_attributes
{
    unsigned     index;
    rgba8        fill_color;
    rgba8        stroke_color;
    bool         fill_flag;
    bool         stroke_flag;
    bool         even_odd_flag;
    line_join_e  line_join;
    line_cap_e   line_cap;
    double       miter_limit;
    double       stroke_width;
    trans_affine transform;

    svg_gradient* gradient;

    // Empty constructor
    path_attributes() :
            index(0),
            fill_color(rgba(0,0,0)),
            stroke_color(rgba(0,0,0)),
            fill_flag(true),
            stroke_flag(false),
            even_odd_flag(false),
            line_join(miter_join),
            line_cap(butt_cap),
            miter_limit(4.0),
            stroke_width(1.0),
            transform(),
            gradient(0)
    {
    }

    path_attributes& operator=(const path_attributes& other) {
        this->index = other.index;
        this->fill_color = other.fill_color;
        this->stroke_color = other.stroke_color;
        this->fill_flag = other.fill_flag;
        this->stroke_flag = other.stroke_flag;
        this->even_odd_flag = other.even_odd_flag;
        this->line_join = other.line_join;
        this->line_cap = other.line_cap;
        this->miter_limit = other.miter_limit;
        this->stroke_width = other.stroke_width;
        this->transform = other.transform;

        if (this->gradient) {
            delete this->gradient;
        }

        this->gradient = other.gradient ? other.gradient->clone() : NULL;

        return *this;
    }

    // Copy constructor
    path_attributes(const path_attributes& attr) :
            index(attr.index),
            fill_color(attr.fill_color),
            stroke_color(attr.stroke_color),
            fill_flag(attr.fill_flag),
            stroke_flag(attr.stroke_flag),
            even_odd_flag(attr.even_odd_flag),
            line_join(attr.line_join),
            line_cap(attr.line_cap),
            miter_limit(attr.miter_limit),
            stroke_width(attr.stroke_width),
            transform(attr.transform),
            gradient(attr.gradient ? attr.gradient->clone() : NULL)
    {
    }

    // Copy constructor with new index value
    path_attributes(const path_attributes& attr, unsigned idx) :
            index(idx),
            fill_color(attr.fill_color),
            stroke_color(attr.stroke_color),
            fill_flag(attr.fill_flag),
            stroke_flag(attr.stroke_flag),
            even_odd_flag(attr.even_odd_flag),
            line_join(attr.line_join),
            line_cap(attr.line_cap),
            miter_limit(attr.miter_limit),
            stroke_width(attr.stroke_width),
            transform(attr.transform),
            gradient(attr.gradient ? attr.gradient->clone() : NULL)
    {
    }

    ~path_attributes() {
        delete gradient;
        gradient = NULL;
    }
};


//============================================================================
// Path container and renderer.
struct path_renderer
{
    typedef pod_bvector<path_attributes>   attr_storage;

    typedef conv_curve<path_storage>       curved;
    typedef conv_count<curved>             curved_count;

    typedef conv_stroke<curved_count>      curved_stroked;
    typedef conv_transform<curved_stroked> curved_stroked_trans;

    typedef conv_transform<curved_count>   curved_trans;
    typedef conv_contour<curved_trans>     curved_trans_contour;

    path_renderer();

    void remove_all();

    // Use these functions as follows:
    // begin_path() when the XML tag <path> comes ("start_element" handler)
    // parse_path() on "d=" tag attribute
    // end_path() when parsing of the entire tag is done.
    void begin_path();    
    void end_path();

    // The following functions are essentially a "reflection" of
    // the respective SVG path commands.
    void move_to(double x, double y, bool rel=false);   // M, m
    void line_to(double x,  double y, bool rel=false);  // L, l
    void hline_to(double x, bool rel=false);            // H, h
    void vline_to(double y, bool rel=false);            // V, v
    void curve3(double x1, double y1,                   // Q, q
                double x,  double y, bool rel=false);
    void curve3(double x, double y, bool rel=false);    // T, t
    void curve4(double x1, double y1,                   // C, c
                double x2, double y2,
                double x,  double y, bool rel=false);
    void curve4(double x2, double y2,                   // S, s
                double x,  double y, bool rel=false);
    void close_subpath();                               // Z, z

//        template<class VertexSource>
//        void add_path(VertexSource& vs,
//                      unsigned path_id = 0,
//                      bool solid_path = true)
//        {
//            m_storage.add_path(vs, path_id, solid_path);
//        }


    unsigned vertex_count() const {
        return m_curved_count.count();
    }


    // Call these functions on <g> tag (start_element, end_element respectively)
    void push_attr();
    void pop_attr();

    // Attribute setting functions.
    void fill(const rgba8& f);
    void stroke(const rgba8& s);
    void even_odd(bool flag);
    void stroke_width(double w);
    void fill_none();
    void stroke_none();
    void fill_opacity(double op);
    void stroke_opacity(double op);
    void line_join(line_join_e join);
    void line_cap(line_cap_e cap);
    void miter_limit(double ml);
    trans_affine& transform();

    void fill_gradient(svg_gradient& gradient);

    // Make all polygons CCW-oriented
    void arrange_orientations()
    {
        m_storage.arrange_orientations_all_paths(path_flags_ccw);
    }

    // Expand all polygons
    void expand(double value)
    {
        m_curved_trans_contour.width(value);
    }

    unsigned operator [](unsigned idx)
    {
        m_transform = m_attr_storage[idx].transform;
        return m_attr_storage[idx].index;
    }

    void bounding_rect(double* x1, double* y1, double* x2, double* y2)
    {
        agg::conv_transform<agg::path_storage> trans(m_storage, m_transform);
        agg::bounding_rect(trans, *this, 0, m_attr_storage.size(), x1, y1, x2, y2);
    }

    // Rendering. One can specify two additional parameters:
    // trans_affine and opacity. They can be used to transform the whole
    // image and/or to make it translucent.
    template<class Rasterizer, class Scanline, class Renderer, class RendererBase>
    void render(Rasterizer& ras,
                Scanline& sl,
                Renderer& ren,
                const trans_affine& mtx,
                RendererBase& renderer_base,
                const rect_i& cb,
                double opacity=1.0)
    {
        unsigned i;

        ras.clip_box(cb.x1, cb.y1, cb.x2, cb.y2);
        m_curved_count.count(0);

        for (i = 0; i < m_attr_storage.size(); i++)
        {
            const path_attributes& attr = m_attr_storage[i];
            m_transform = attr.transform;
            m_transform *= mtx;
            double scl = m_transform.scale();
            //m_curved.approximation_method(curve_inc);
            m_curved.approximation_scale(scl);
            m_curved.angle_tolerance(0.0);

            rgba8 color;

            if (attr.fill_flag)
            {
                ras.reset();
                ras.filling_rule(attr.even_odd_flag ? fill_even_odd : fill_non_zero);
                if (fabs(m_curved_trans_contour.width()) < 0.0001)
                {
                    ras.add_path(m_curved_trans, attr.index);
                }
                else
                {
                    m_curved_trans_contour.miter_limit(attr.miter_limit);
                    ras.add_path(m_curved_trans_contour, attr.index);
                }

                if (attr.gradient) {
                    fill_color_array(gradient_color_array, attr.gradient->stops);

                    if (attr.gradient->gradient_type == svg_gradient::e_linear) {
                        static_cast<linear_gradient*>(attr.gradient)->render_gradient(m_transform, gradient_color_array, ras, sl, renderer_base);
                    } else if (attr.gradient->gradient_type == svg_gradient::e_radial) {
                        static_cast<radial_gradient*>(attr.gradient)->render_gradient(m_transform, gradient_color_array, ras, sl, renderer_base);
                    }
                } else {
                    color = attr.fill_color;
                    color.opacity(color.opacity() * opacity);
                    ren.color(color);
                    agg::render_scanlines(ras, sl, ren);
                }
            }

            if (attr.stroke_flag)
            {
                m_curved_stroked.width(attr.stroke_width);
                //m_curved_stroked.line_join((attr.line_join == miter_join) ? miter_join_round : attr.line_join);
                m_curved_stroked.line_join(attr.line_join);
                m_curved_stroked.line_cap(attr.line_cap);
                m_curved_stroked.miter_limit(attr.miter_limit);
                m_curved_stroked.inner_join(inner_round);
                m_curved_stroked.approximation_scale(scl);

                // If the *visual* line width is considerable we
                // turn on processing of curve cusps.
                //---------------------
                if (attr.stroke_width * scl > 1.0)
                {
                    m_curved.angle_tolerance(0.2);
                }
                ras.reset();
                ras.filling_rule(fill_non_zero);
                ras.add_path(m_curved_stroked_trans, attr.index);
                color = attr.stroke_color;
                color.opacity(color.opacity() * opacity);
                ren.color(color);
                agg::render_scanlines(ras, sl, ren);
            }


        }
    }

private:

    template <typename ColorArray>
    void fill_color_array(ColorArray& array, pod_bvector< svg_gradient::stop >& stops) {
        unsigned i = 0;

        unsigned int stop = 0;

        while (stop < stops.size()) {
            const unsigned int nextStopPos = array.size() * stops[stop + 1].offset;
            const unsigned int sliceSize = nextStopPos - i;
            const float opactiy_interval = (stops[stop + 1].opacity - stops[stop].opacity) / (float) sliceSize;

            for (int j = 0; i < nextStopPos; ++i, j++) {
                array[i] = stops[stop].color.gradient(stops[stop + 1].color, j / (float) sliceSize);
                array[i].opacity(stops[stop].opacity + (j *  opactiy_interval));
            }

            stop++;
        }
    }

    typedef agg::pod_auto_array<agg::rgba8, 1024> color_array_type;
    color_array_type gradient_color_array;

    path_attributes& cur_attr();

    path_storage   m_storage;
    attr_storage   m_attr_storage;
    attr_storage   m_attr_stack;
    trans_affine   m_transform;

    curved                       m_curved;
    curved_count                 m_curved_count;

    curved_stroked               m_curved_stroked;
    curved_stroked_trans         m_curved_stroked_trans;

    curved_trans                 m_curved_trans;
    curved_trans_contour         m_curved_trans_contour;
};

}
}

#endif
