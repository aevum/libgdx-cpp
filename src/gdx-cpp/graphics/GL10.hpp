
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

#ifndef GDX_CPP_GRAPHICS_GL10_HPP_
#define GDX_CPP_GRAPHICS_GL10_HPP_

#include "GLCommon.hpp"

#undef GL_OES_VERSION_1_0
#undef GL_OES_read_format
#undef GL_OES_compressed_paletted_texture
#undef GL_DEPTH_BUFFER_BIT
#undef GL_STENCIL_BUFFER_BIT
#undef GL_COLOR_BUFFER_BIT
#undef GL_FALSE
#undef GL_TRUE
#undef GL_POINTS
#undef GL_LINES
#undef GL_LINE_LOOP
#undef GL_LINE_STRIP
#undef GL_TRIANGLES
#undef GL_TRIANGLE_STRIP
#undef GL_TRIANGLE_FAN
#undef GL_NEVER
#undef GL_LESS
#undef GL_EQUAL
#undef GL_LEQUAL
#undef GL_GREATER
#undef GL_NOTEQUAL
#undef GL_GEQUAL
#undef GL_ALWAYS
#undef GL_ZERO
#undef GL_ONE
#undef GL_SRC_COLOR
#undef GL_ONE_MINUS_SRC_COLOR
#undef GL_SRC_ALPHA
#undef GL_ONE_MINUS_SRC_ALPHA
#undef GL_DST_ALPHA
#undef GL_ONE_MINUS_DST_ALPHA
#undef GL_DST_COLOR
#undef GL_ONE_MINUS_DST_COLOR
#undef GL_SRC_ALPHA_SATURATE
#undef GL_FRONT
#undef GL_BACK
#undef GL_FRONT_AND_BACK
#undef GL_FOG
#undef GL_LIGHTING
#undef GL_TEXTURE_2D
#undef GL_CULL_FACE
#undef GL_ALPHA_TEST
#undef GL_BLEND
#undef GL_COLOR_LOGIC_OP
#undef GL_DITHER
#undef GL_STENCIL_TEST
#undef GL_DEPTH_TEST
#undef GL_POINT_SMOOTH
#undef GL_LINE_SMOOTH
#undef GL_SCISSOR_TEST
#undef GL_COLOR_MATERIAL
#undef GL_NORMALIZE
#undef GL_RESCALE_NORMAL
#undef GL_POLYGON_OFFSET_FILL
#undef GL_VERTEX_ARRAY
#undef GL_NORMAL_ARRAY
#undef GL_COLOR_ARRAY
#undef GL_TEXTURE_COORD_ARRAY
#undef GL_MULTISAMPLE
#undef GL_SAMPLE_ALPHA_TO_COVERAGE
#undef GL_SAMPLE_ALPHA_TO_ONE
#undef GL_SAMPLE_COVERAGE
#undef GL_NO_ERROR
#undef GL_INVALID_ENUM
#undef GL_INVALID_VALUE
#undef GL_INVALID_OPERATION
#undef GL_STACK_OVERFLOW
#undef GL_STACK_UNDERFLOW
#undef GL_OUT_OF_MEMORY
#undef GL_EXP
#undef GL_EXP2
#undef GL_FOG_DENSITY
#undef GL_FOG_START
#undef GL_FOG_END
#undef GL_FOG_MODE
#undef GL_FOG_COLOR
#undef GL_CW
#undef GL_CCW
#undef GL_SMOOTH_POINT_SIZE_RANGE
#undef GL_SMOOTH_LINE_WIDTH_RANGE
#undef GL_ALIASED_POINT_SIZE_RANGE
#undef GL_ALIASED_LINE_WIDTH_RANGE
#undef GL_IMPLEMENTATION_COLOR_READ_TYPE_OES
#undef GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES
#undef GL_MAX_LIGHTS
#undef GL_MAX_TEXTURE_SIZE
#undef GL_MAX_MODELVIEW_STACK_DEPTH
#undef GL_MAX_PROJECTION_STACK_DEPTH
#undef GL_MAX_TEXTURE_STACK_DEPTH
#undef GL_MAX_VIEWPORT_DIMS
#undef GL_MAX_ELEMENTS_VERTICES
#undef GL_MAX_ELEMENTS_INDICES
#undef GL_MAX_TEXTURE_UNITS
#undef GL_NUM_COMPRESSED_TEXTURE_FORMATS
#undef GL_COMPRESSED_TEXTURE_FORMATS
#undef GL_SUBPIXEL_BITS
#undef GL_RED_BITS
#undef GL_GREEN_BITS
#undef GL_BLUE_BITS
#undef GL_ALPHA_BITS
#undef GL_DEPTH_BITS
#undef GL_STENCIL_BITS
#undef GL_DONT_CARE
#undef GL_FASTEST
#undef GL_NICEST
#undef GL_PERSPECTIVE_CORRECTION_HINT
#undef GL_POINT_SMOOTH_HINT
#undef GL_LINE_SMOOTH_HINT
#undef GL_POLYGON_SMOOTH_HINT
#undef GL_FOG_HINT
#undef GL_LIGHT_MODEL_AMBIENT
#undef GL_LIGHT_MODEL_TWO_SIDE
#undef GL_AMBIENT
#undef GL_DIFFUSE
#undef GL_SPECULAR
#undef GL_POSITION
#undef GL_SPOT_DIRECTION
#undef GL_SPOT_EXPONENT
#undef GL_SPOT_CUTOFF
#undef GL_CONSTANT_ATTENUATION
#undef GL_LINEAR_ATTENUATION
#undef GL_QUADRATIC_ATTENUATION
#undef GL_BYTE
#undef GL_UNSIGNED_BYTE
#undef GL_SHORT
#undef GL_UNSIGNED_SHORT
#undef GL_FLOAT
#undef GL_CLEAR
#undef GL_AND
#undef GL_AND_REVERSE
#undef GL_COPY
#undef GL_AND_INVERTED
#undef GL_NOOP
#undef GL_XOR
#undef GL_OR
#undef GL_NOR
#undef GL_EQUIV
#undef GL_INVERT
#undef GL_OR_REVERSE
#undef GL_COPY_INVERTED
#undef GL_OR_INVERTED
#undef GL_NAND
#undef GL_SET
#undef GL_EMISSION
#undef GL_SHININESS
#undef GL_AMBIENT_AND_DIFFUSE
#undef GL_MODELVIEW
#undef GL_PROJECTION
#undef GL_TEXTURE
#undef GL_ALPHA
#undef GL_RGB
#undef GL_RGBA
#undef GL_LUMINANCE
#undef GL_LUMINANCE_ALPHA
#undef GL_UNPACK_ALIGNMENT
#undef GL_PACK_ALIGNMENT
#undef GL_UNSIGNED_SHORT_4_4_4_4
#undef GL_UNSIGNED_SHORT_5_5_5_1
#undef GL_UNSIGNED_SHORT_5_6_5
#undef GL_FLAT
#undef GL_SMOOTH
#undef GL_KEEP
#undef GL_REPLACE
#undef GL_INCR
#undef GL_DECR
#undef GL_VENDOR
#undef GL_RENDERER
#undef GL_VERSION
#undef GL_EXTENSIONS
#undef GL_MODULATE
#undef GL_DECAL
#undef GL_ADD
#undef GL_TEXTURE_ENV_MODE
#undef GL_TEXTURE_ENV_COLOR
#undef GL_TEXTURE_ENV
#undef GL_NEAREST
#undef GL_LINEAR
#undef GL_NEAREST_MIPMAP_NEAREST
#undef GL_LINEAR_MIPMAP_NEAREST
#undef GL_NEAREST_MIPMAP_LINEAR
#undef GL_LINEAR_MIPMAP_LINEAR
#undef GL_TEXTURE_MAG_FILTER
#undef GL_TEXTURE_MIN_FILTER
#undef GL_TEXTURE_WRAP_S
#undef GL_TEXTURE_WRAP_T
#undef GL_TEXTURE0
#undef GL_TEXTURE1
#undef GL_TEXTURE2
#undef GL_TEXTURE3
#undef GL_TEXTURE4
#undef GL_TEXTURE5
#undef GL_TEXTURE6
#undef GL_TEXTURE7
#undef GL_TEXTURE8
#undef GL_TEXTURE9
#undef GL_TEXTURE10
#undef GL_TEXTURE11
#undef GL_TEXTURE12
#undef GL_TEXTURE13
#undef GL_TEXTURE14
#undef GL_TEXTURE15
#undef GL_TEXTURE16
#undef GL_TEXTURE17
#undef GL_TEXTURE18
#undef GL_TEXTURE19
#undef GL_TEXTURE20
#undef GL_TEXTURE21
#undef GL_TEXTURE22
#undef GL_TEXTURE23
#undef GL_TEXTURE24
#undef GL_TEXTURE25
#undef GL_TEXTURE26
#undef GL_TEXTURE27
#undef GL_TEXTURE28
#undef GL_TEXTURE29
#undef GL_TEXTURE30
#undef GL_TEXTURE31
#undef GL_REPEAT
#undef GL_CLAMP_TO_EDGE
#undef GL_PALETTE4_RGB8_OES
#undef GL_PALETTE4_RGBA8_OES
#undef GL_PALETTE4_R5_G6_B5_OES
#undef GL_PALETTE4_RGBA4_OES
#undef GL_PALETTE4_RGB5_A1_OES
#undef GL_PALETTE8_RGB8_OES
#undef GL_PALETTE8_RGBA8_OES
#undef GL_PALETTE8_R5_G6_B5_OES
#undef GL_PALETTE8_RGBA4_OES
#undef GL_PALETTE8_RGB5_A1_OES
#undef GL_LIGHT0
#undef GL_LIGHT1
#undef GL_LIGHT2
#undef GL_LIGHT3
#undef GL_LIGHT4
#undef GL_LIGHT5
#undef GL_LIGHT6
#undef GL_LIGHT7

#undef GL_POINT
#undef GL_LINE
#undef GL_FILL

namespace gdx_cpp {
namespace graphics {

class GL10 : virtual public GLCommon {
public:

    static const int GL_OES_VERSION_1_0;
    static const int GL_OES_read_format;
    static const int GL_OES_compressed_paletted_texture;
    static const int GL_DEPTH_BUFFER_BIT;
    static const int GL_STENCIL_BUFFER_BIT;
    static const int GL_COLOR_BUFFER_BIT;
    static const int GL_FALSE;
    static const int GL_TRUE;
    static const int GL_POINTS;
    static const int GL_LINES;
    static const int GL_LINE_LOOP;
    static const int GL_LINE_STRIP;
    static const int GL_TRIANGLES;
    static const int GL_TRIANGLE_STRIP;
    static const int GL_TRIANGLE_FAN;
    static const int GL_NEVER;
    static const int GL_LESS;
    static const int GL_EQUAL;
    static const int GL_LEQUAL;
    static const int GL_GREATER;
    static const int GL_NOTEQUAL;
    static const int GL_GEQUAL;
    static const int GL_ALWAYS;
    static const int GL_ZERO;
    static const int GL_ONE;
    static const int GL_SRC_COLOR;
    static const int GL_ONE_MINUS_SRC_COLOR;
    static const int GL_SRC_ALPHA;
    static const int GL_ONE_MINUS_SRC_ALPHA;
    static const int GL_DST_ALPHA;
    static const int GL_ONE_MINUS_DST_ALPHA;
    static const int GL_DST_COLOR;
    static const int GL_ONE_MINUS_DST_COLOR;
    static const int GL_SRC_ALPHA_SATURATE;
    static const int GL_FRONT;
    static const int GL_BACK;
    static const int GL_FRONT_AND_BACK;
    static const int GL_FOG;
    static const int GL_LIGHTING;
    static const int GL_TEXTURE_2D;
    static const int GL_CULL_FACE;
    static const int GL_ALPHA_TEST;
    static const int GL_BLEND;
    static const int GL_COLOR_LOGIC_OP;
    static const int GL_DITHER;
    static const int GL_STENCIL_TEST;
    static const int GL_DEPTH_TEST;
    static const int GL_POINT_SMOOTH;
    static const int GL_LINE_SMOOTH;
    static const int GL_SCISSOR_TEST;
    static const int GL_COLOR_MATERIAL;
    static const int GL_NORMALIZE;
    static const int GL_RESCALE_NORMAL;
    static const int GL_POLYGON_OFFSET_FILL;
    static const int GL_VERTEX_ARRAY;
    static const int GL_NORMAL_ARRAY;
    static const int GL_COLOR_ARRAY;
    static const int GL_TEXTURE_COORD_ARRAY;
    static const int GL_MULTISAMPLE;
    static const int GL_SAMPLE_ALPHA_TO_COVERAGE;
    static const int GL_SAMPLE_ALPHA_TO_ONE;
    static const int GL_SAMPLE_COVERAGE;
    static const int GL_NO_ERROR;
    static const int GL_INVALID_ENUM;
    static const int GL_INVALID_VALUE;
    static const int GL_INVALID_OPERATION;
    static const int GL_STACK_OVERFLOW;
    static const int GL_STACK_UNDERFLOW;
    static const int GL_OUT_OF_MEMORY;
    static const int GL_EXP;
    static const int GL_EXP2;
    static const int GL_FOG_DENSITY;
    static const int GL_FOG_START;
    static const int GL_FOG_END;
    static const int GL_FOG_MODE;
    static const int GL_FOG_COLOR;
    static const int GL_CW;
    static const int GL_CCW;
    static const int GL_SMOOTH_POINT_SIZE_RANGE;
    static const int GL_SMOOTH_LINE_WIDTH_RANGE;
    static const int GL_ALIASED_POINT_SIZE_RANGE;
    static const int GL_ALIASED_LINE_WIDTH_RANGE;
    static const int GL_IMPLEMENTATION_COLOR_READ_TYPE_OES;
    static const int GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES;
    static const int GL_MAX_LIGHTS;
    static const int GL_MAX_TEXTURE_SIZE;
    static const int GL_MAX_MODELVIEW_STACK_DEPTH;
    static const int GL_MAX_PROJECTION_STACK_DEPTH;
    static const int GL_MAX_TEXTURE_STACK_DEPTH;
    static const int GL_MAX_VIEWPORT_DIMS;
    static const int GL_MAX_ELEMENTS_VERTICES;
    static const int GL_MAX_ELEMENTS_INDICES;
    static const int GL_MAX_TEXTURE_UNITS;
    static const int GL_NUM_COMPRESSED_TEXTURE_FORMATS;
    static const int GL_COMPRESSED_TEXTURE_FORMATS;
    static const int GL_SUBPIXEL_BITS;
    static const int GL_RED_BITS;
    static const int GL_GREEN_BITS;
    static const int GL_BLUE_BITS;
    static const int GL_ALPHA_BITS;
    static const int GL_DEPTH_BITS;
    static const int GL_STENCIL_BITS;
    static const int GL_DONT_CARE;
    static const int GL_FASTEST;
    static const int GL_NICEST;
    static const int GL_PERSPECTIVE_CORRECTION_HINT;
    static const int GL_POINT_SMOOTH_HINT;
    static const int GL_LINE_SMOOTH_HINT;
    static const int GL_POLYGON_SMOOTH_HINT;
    static const int GL_FOG_HINT;
    static const int GL_LIGHT_MODEL_AMBIENT;
    static const int GL_LIGHT_MODEL_TWO_SIDE;
    static const int GL_AMBIENT;
    static const int GL_DIFFUSE;
    static const int GL_SPECULAR;
    static const int GL_POSITION;
    static const int GL_SPOT_DIRECTION;
    static const int GL_SPOT_EXPONENT;
    static const int GL_SPOT_CUTOFF;
    static const int GL_CONSTANT_ATTENUATION;
    static const int GL_LINEAR_ATTENUATION;
    static const int GL_QUADRATIC_ATTENUATION;
    static const int GL_BYTE;
    static const int GL_UNSIGNED_BYTE;
    static const int GL_SHORT;
    static const int GL_UNSIGNED_SHORT;
    static const int GL_FLOAT;
    static const int GL_CLEAR;
    static const int GL_AND;
    static const int GL_AND_REVERSE;
    static const int GL_COPY;
    static const int GL_AND_INVERTED;
    static const int GL_NOOP;
    static const int GL_XOR;
    static const int GL_OR;
    static const int GL_NOR;
    static const int GL_EQUIV;
    static const int GL_INVERT;
    static const int GL_OR_REVERSE;
    static const int GL_COPY_INVERTED;
    static const int GL_OR_INVERTED;
    static const int GL_NAND;
    static const int GL_SET;
    static const int GL_EMISSION;
    static const int GL_SHININESS;
    static const int GL_AMBIENT_AND_DIFFUSE;
    static const int GL_MODELVIEW;
    static const int GL_PROJECTION;
    static const int GL_TEXTURE;
    static const int GL_ALPHA;
    static const int GL_RGB;
    static const int GL_RGBA;
    static const int GL_LUMINANCE;
    static const int GL_LUMINANCE_ALPHA;
    static const int GL_UNPACK_ALIGNMENT;
    static const int GL_PACK_ALIGNMENT;
    static const int GL_UNSIGNED_SHORT_4_4_4_4;
    static const int GL_UNSIGNED_SHORT_5_5_5_1;
    static const int GL_UNSIGNED_SHORT_5_6_5;
    static const int GL_FLAT;
    static const int GL_SMOOTH;
    static const int GL_KEEP;
    static const int GL_REPLACE;
    static const int GL_INCR;
    static const int GL_DECR;
    static const int GL_VENDOR;
    static const int GL_RENDERER;
    static const int GL_VERSION;
    static const int GL_EXTENSIONS;
    static const int GL_MODULATE;
    static const int GL_DECAL;
    static const int GL_ADD;
    static const int GL_TEXTURE_ENV_MODE;
    static const int GL_TEXTURE_ENV_COLOR;
    static const int GL_TEXTURE_ENV;
    static const int GL_NEAREST;
    static const int GL_LINEAR;
    static const int GL_NEAREST_MIPMAP_NEAREST;
    static const int GL_LINEAR_MIPMAP_NEAREST;
    static const int GL_NEAREST_MIPMAP_LINEAR;
    static const int GL_LINEAR_MIPMAP_LINEAR;
    static const int GL_TEXTURE_MAG_FILTER;
    static const int GL_TEXTURE_MIN_FILTER;
    static const int GL_TEXTURE_WRAP_S;
    static const int GL_TEXTURE_WRAP_T;
    static const int GL_TEXTURE0;
    static const int GL_TEXTURE1;
    static const int GL_TEXTURE2;
    static const int GL_TEXTURE3;
    static const int GL_TEXTURE4;
    static const int GL_TEXTURE5;
    static const int GL_TEXTURE6;
    static const int GL_TEXTURE7;
    static const int GL_TEXTURE8;
    static const int GL_TEXTURE9;
    static const int GL_TEXTURE10;
    static const int GL_TEXTURE11;
    static const int GL_TEXTURE12;
    static const int GL_TEXTURE13;
    static const int GL_TEXTURE14;
    static const int GL_TEXTURE15;
    static const int GL_TEXTURE16;
    static const int GL_TEXTURE17;
    static const int GL_TEXTURE18;
    static const int GL_TEXTURE19;
    static const int GL_TEXTURE20;
    static const int GL_TEXTURE21;
    static const int GL_TEXTURE22;
    static const int GL_TEXTURE23;
    static const int GL_TEXTURE24;
    static const int GL_TEXTURE25;
    static const int GL_TEXTURE26;
    static const int GL_TEXTURE27;
    static const int GL_TEXTURE28;
    static const int GL_TEXTURE29;
    static const int GL_TEXTURE30;
    static const int GL_TEXTURE31;
    static const int GL_REPEAT;
    static const int GL_CLAMP_TO_EDGE;
    static const int GL_PALETTE4_RGB8_OES;
    static const int GL_PALETTE4_RGBA8_OES;
    static const int GL_PALETTE4_R5_G6_B5_OES;
    static const int GL_PALETTE4_RGBA4_OES;
    static const int GL_PALETTE4_RGB5_A1_OES;
    static const int GL_PALETTE8_RGB8_OES;
    static const int GL_PALETTE8_RGBA8_OES;
    static const int GL_PALETTE8_R5_G6_B5_OES;
    static const int GL_PALETTE8_RGBA4_OES;
    static const int GL_PALETTE8_RGB5_A1_OES;
    static const int GL_LIGHT0;
    static const int GL_LIGHT1;
    static const int GL_LIGHT2;
    static const int GL_LIGHT3;
    static const int GL_LIGHT4;
    static const int GL_LIGHT5;
    static const int GL_LIGHT6;
    static const int GL_LIGHT7;

    static const int GL_POINT;
    static const int GL_LINE;
    static const int GL_FILL;
    
    virtual void glAlphaFunc (int func,float ref) const = 0;
    virtual void glClientActiveTexture (int texture) const = 0;
    virtual void glColor4f (float red,float green,float blue,float alpha) const = 0;
    virtual void glColorPointer (int size,int type,int stride,const void* pointer) const = 0;
    virtual void glDisableClientState (int array) const = 0;
    virtual void glEnableClientState (int array) const = 0;
    virtual void glFogf (int pname,float param) const = 0;
    virtual void glFogfv (int pname,const float* params) const = 0;
    virtual void glFrustumf (float left,float right,float bottom,float top,float zNear,float zFar) const = 0;
    virtual void glLightModelf (int pname,float param) const = 0;
    virtual void glLightModelfv (int pname,const float* params) const = 0;
    virtual void glLightf (int light,int pname,float param) const = 0;
    virtual void glLightfv (int light,int pname,const float* params) const = 0;
    virtual void glLoadIdentity () const = 0;
    virtual void glLoadMatrixf (const float* m) const = 0;
    virtual void glLogicOp (int opcode) const = 0;
    virtual void glMaterialf (int face,int pname,float param) const = 0;
    virtual void glMaterialfv (int face,int pname,const float* params) const = 0;
    virtual void glMatrixMode (int mode) const = 0;
    virtual void glMultMatrixf (const float* m) const = 0;
    virtual void glMultiTexCoord4f (int target,float s,float t,float r,float q) const = 0;
    virtual void glNormal3f (float nx,float ny,float nz) const = 0;
    virtual void glNormalPointer (int type,int stride,const void* pointer) const = 0;
    virtual void glOrthof (float left,float right,float bottom,float top,float zNear,float zFar) const = 0;
    virtual void glPointSize (float size) const = 0;
    virtual void glPopMatrix () const = 0;
    virtual void glPushMatrix () const = 0;
    virtual void glRotatef (float angle,float x,float y,float z) const = 0;
    virtual void glSampleCoverage (float value,bool invert) const = 0;
    virtual void glScalef (float x,float y,float z) const = 0;
    virtual void glShadeModel (int mode) const = 0;
    virtual void glTexCoordPointer (int size,int type,int stride,const void * pointer) const = 0;
    virtual void glTexEnvf (int target,int pname,float param) const = 0;
    virtual void glTexEnvfv (int target,int pname,const float* params) const = 0;
    virtual void glTranslatef (float x,float y,float z) const = 0;
    virtual void glVertexPointer (int size,int type,int stride,const void* pointer) const = 0;
    virtual void glPolygonMode (int face,int mode) const = 0;
};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_GL10_HPP_
