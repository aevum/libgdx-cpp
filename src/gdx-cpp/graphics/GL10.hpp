
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

#include <set>

#include "GLCommon.hpp"

//#undef GL_SRC_ALPHA
//#undef GL_ONE_MINUS_DST_COLOR
//#undef GL_ONE_MINUS_SRC_ALPHA
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
namespace gdx {

class GL10 : virtual public GLCommon {
public:
	const static int GL_OES_VERSION_1_0 = 1;
	const static int GL_OES_read_format = 1;
	const static int GL_OES_compressed_paletted_texture = 1;
	const static int GL_DEPTH_BUFFER_BIT = 0x00000100;
	const static int GL_STENCIL_BUFFER_BIT = 0x00000400;
	const static int GL_COLOR_BUFFER_BIT = 0x00004000;
	const static int GL_FALSE = 0;
	const static int GL_TRUE = 1;
	const static int GL_POINTS = 0x0000;
	const static int GL_LINES = 0x0001;
	const static int GL_LINE_LOOP = 0x0002;
	const static int GL_LINE_STRIP = 0x0003;
	const static int GL_TRIANGLES = 0x0004;
	const static int GL_TRIANGLE_STRIP = 0x0005;
	const static int GL_TRIANGLE_FAN = 0x0006;
	const static int GL_NEVER = 0x0200;
	const static int GL_LESS = 0x0201;
	const static int GL_EQUAL = 0x0202;
	const static int GL_LEQUAL = 0x0203;
	const static int GL_GREATER = 0x0204;
	const static int GL_NOTEQUAL = 0x0205;
	const static int GL_GEQUAL = 0x0206;
	const static int GL_ALWAYS = 0x0207;
	const static int GL_ZERO = 0;
	const static int GL_ONE = 1;
	const static int GL_SRC_COLOR = 0x0300;
	const static int GL_ONE_MINUS_SRC_COLOR = 0x0301;
	const static int GL_SRC_ALPHA = 0x0302;
	const static int GL_ONE_MINUS_SRC_ALPHA = 0x0303;
	const static int GL_DST_ALPHA = 0x0304;
	const static int GL_ONE_MINUS_DST_ALPHA = 0x0305;
	const static int GL_DST_COLOR = 0x0306;
	const static int GL_ONE_MINUS_DST_COLOR = 0x0307;
	const static int GL_SRC_ALPHA_SATURATE = 0x0308;
	const static int GL_FRONT = 0x0404;
	const static int GL_BACK = 0x0405;
	const static int GL_FRONT_AND_BACK = 0x0408;
	const static int GL_FOG = 0x0B60;
	const static int GL_LIGHTING = 0x0B50;
	const static int GL_TEXTURE_2D = 0x0DE1;
	const static int GL_CULL_FACE = 0x0B44;
	const static int GL_ALPHA_TEST = 0x0BC0;
	const static int GL_BLEND = 0x0BE2;
	const static int GL_COLOR_LOGIC_OP = 0x0BF2;
	const static int GL_DITHER = 0x0BD0;
	const static int GL_STENCIL_TEST = 0x0B90;
	const static int GL_DEPTH_TEST = 0x0B71;
	const static int GL_POINT_SMOOTH = 0x0B10;
	const static int GL_LINE_SMOOTH = 0x0B20;
	const static int GL_SCISSOR_TEST = 0x0C11;
	const static int GL_COLOR_MATERIAL = 0x0B57;
	const static int GL_NORMALIZE = 0x0BA1;
	const static int GL_RESCALE_NORMAL = 0x803A;
	const static int GL_POLYGON_OFFSET_FILL = 0x8037;
	const static int GL_VERTEX_ARRAY = 0x8074;
	const static int GL_NORMAL_ARRAY = 0x8075;
	const static int GL_COLOR_ARRAY = 0x8076;
	const static int GL_TEXTURE_COORD_ARRAY = 0x8078;
	const static int GL_MULTISAMPLE = 0x809D;
	const static int GL_SAMPLE_ALPHA_TO_COVERAGE = 0x809E;
	const static int GL_SAMPLE_ALPHA_TO_ONE = 0x809F;
	const static int GL_SAMPLE_COVERAGE = 0x80A0;
	const static int GL_NO_ERROR = 0;
	const static int GL_INVALID_ENUM = 0x0500;
	const static int GL_INVALID_VALUE = 0x0501;
	const static int GL_INVALID_OPERATION = 0x0502;
	const static int GL_STACK_OVERFLOW = 0x0503;
	const static int GL_STACK_UNDERFLOW = 0x0504;
	const static int GL_OUT_OF_MEMORY = 0x0505;
	const static int GL_EXP = 0x0800;
	const static int GL_EXP2 = 0x0801;
	const static int GL_FOG_DENSITY = 0x0B62;
	const static int GL_FOG_START = 0x0B63;
	const static int GL_FOG_END = 0x0B64;
	const static int GL_FOG_MODE = 0x0B65;
	const static int GL_FOG_COLOR = 0x0B66;
	const static int GL_CW = 0x0900;
	const static int GL_CCW = 0x0901;
	const static int GL_SMOOTH_POINT_SIZE_RANGE = 0x0B12;
	const static int GL_SMOOTH_LINE_WIDTH_RANGE = 0x0B22;
	const static int GL_ALIASED_POINT_SIZE_RANGE = 0x846D;
	const static int GL_ALIASED_LINE_WIDTH_RANGE = 0x846E;
	const static int GL_IMPLEMENTATION_COLOR_READ_TYPE_OES = 0x8B9A;
	const static int GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES = 0x8B9B;
	const static int GL_MAX_LIGHTS = 0x0D31;
	const static int GL_MAX_TEXTURE_SIZE = 0x0D33;
	const static int GL_MAX_MODELVIEW_STACK_DEPTH = 0x0D36;
	const static int GL_MAX_PROJECTION_STACK_DEPTH = 0x0D38;
	const static int GL_MAX_TEXTURE_STACK_DEPTH = 0x0D39;
	const static int GL_MAX_VIEWPORT_DIMS = 0x0D3A;
	const static int GL_MAX_ELEMENTS_VERTICES = 0x80E8;
	const static int GL_MAX_ELEMENTS_INDICES = 0x80E9;
	const static int GL_MAX_TEXTURE_UNITS = 0x84E2;
	const static int GL_NUM_COMPRESSED_TEXTURE_FORMATS = 0x86A2;
	const static int GL_COMPRESSED_TEXTURE_FORMATS = 0x86A3;
	const static int GL_SUBPIXEL_BITS = 0x0D50;
	const static int GL_RED_BITS = 0x0D52;
	const static int GL_GREEN_BITS = 0x0D53;
	const static int GL_BLUE_BITS = 0x0D54;
	const static int GL_ALPHA_BITS = 0x0D55;
	const static int GL_DEPTH_BITS = 0x0D56;
	const static int GL_STENCIL_BITS = 0x0D57;
	const static int GL_DONT_CARE = 0x1100;
	const static int GL_FASTEST = 0x1101;
	const static int GL_NICEST = 0x1102;
	const static int GL_PERSPECTIVE_CORRECTION_HINT = 0x0C50;
	const static int GL_POINT_SMOOTH_HINT = 0x0C51;
	const static int GL_LINE_SMOOTH_HINT = 0x0C52;
	const static int GL_POLYGON_SMOOTH_HINT = 0x0C53;
	const static int GL_FOG_HINT = 0x0C54;
	const static int GL_LIGHT_MODEL_AMBIENT = 0x0B53;
	const static int GL_LIGHT_MODEL_TWO_SIDE = 0x0B52;
	const static int GL_AMBIENT = 0x1200;
	const static int GL_DIFFUSE = 0x1201;
	const static int GL_SPECULAR = 0x1202;
	const static int GL_POSITION = 0x1203;
	const static int GL_SPOT_DIRECTION = 0x1204;
	const static int GL_SPOT_EXPONENT = 0x1205;
	const static int GL_SPOT_CUTOFF = 0x1206;
	const static int GL_CONSTANT_ATTENUATION = 0x1207;
	const static int GL_LINEAR_ATTENUATION = 0x1208;
	const static int GL_QUADRATIC_ATTENUATION = 0x1209;
	const static int GL_BYTE = 0x1400;
	const static int GL_UNSIGNED_BYTE = 0x1401;
	const static int GL_SHORT = 0x1402;
	const static int GL_UNSIGNED_SHORT = 0x1403;
	const static int GL_FLOAT = 0x1406;
	const static int GL_CLEAR = 0x1500;
	const static int GL_AND = 0x1501;
	const static int GL_AND_REVERSE = 0x1502;
	const static int GL_COPY = 0x1503;
	const static int GL_AND_INVERTED = 0x1504;
	const static int GL_NOOP = 0x1505;
	const static int GL_XOR = 0x1506;
	const static int GL_OR = 0x1507;
	const static int GL_NOR = 0x1508;
	const static int GL_EQUIV = 0x1509;
	const static int GL_INVERT = 0x150A;
	const static int GL_OR_REVERSE = 0x150B;
	const static int GL_COPY_INVERTED = 0x150C;
	const static int GL_OR_INVERTED = 0x150D;
	const static int GL_NAND = 0x150E;
	const static int GL_SET = 0x150F;
	const static int GL_EMISSION = 0x1600;
	const static int GL_SHININESS = 0x1601;
	const static int GL_AMBIENT_AND_DIFFUSE = 0x1602;
	const static int GL_MODELVIEW = 0x1700;
	const static int GL_PROJECTION = 0x1701;
	const static int GL_TEXTURE = 0x1702;
	const static int GL_ALPHA = 0x1906;
	const static int GL_RGB = 0x1907;
	const static int GL_RGBA = 0x1908;
	const static int GL_LUMINANCE = 0x1909;
	const static int GL_LUMINANCE_ALPHA = 0x190A;
	const static int GL_UNPACK_ALIGNMENT = 0x0CF5;
	const static int GL_PACK_ALIGNMENT = 0x0D05;
	const static int GL_UNSIGNED_SHORT_4_4_4_4 = 0x8033;
	const static int GL_UNSIGNED_SHORT_5_5_5_1 = 0x8034;
	const static int GL_UNSIGNED_SHORT_5_6_5 = 0x8363;
	const static int GL_FLAT = 0x1D00;
	const static int GL_SMOOTH = 0x1D01;
	const static int GL_KEEP = 0x1E00;
	const static int GL_REPLACE = 0x1E01;
	const static int GL_INCR = 0x1E02;
	const static int GL_DECR = 0x1E03;
	const static int GL_VENDOR = 0x1F00;
	const static int GL_RENDERER = 0x1F01;
	const static int GL_VERSION = 0x1F02;
	const static int GL_EXTENSIONS = 0x1F03;
	const static int GL_MODULATE = 0x2100;
	const static int GL_DECAL = 0x2101;
	const static int GL_ADD = 0x0104;
	const static int GL_TEXTURE_ENV_MODE = 0x2200;
	const static int GL_TEXTURE_ENV_COLOR = 0x2201;
	const static int GL_TEXTURE_ENV = 0x2300;
	const static int GL_NEAREST = 0x2600;
	const static int GL_LINEAR = 0x2601;
	const static int GL_NEAREST_MIPMAP_NEAREST = 0x2700;
	const static int GL_LINEAR_MIPMAP_NEAREST = 0x2701;
	const static int GL_NEAREST_MIPMAP_LINEAR = 0x2702;
	const static int GL_LINEAR_MIPMAP_LINEAR = 0x2703;
	const static int GL_TEXTURE_MAG_FILTER = 0x2800;
	const static int GL_TEXTURE_MIN_FILTER = 0x2801;
	const static int GL_TEXTURE_WRAP_S = 0x2802;
	const static int GL_TEXTURE_WRAP_T = 0x2803;
	const static int GL_TEXTURE0 = 0x84C0;
	const static int GL_TEXTURE1 = 0x84C1;
	const static int GL_TEXTURE2 = 0x84C2;
	const static int GL_TEXTURE3 = 0x84C3;
	const static int GL_TEXTURE4 = 0x84C4;
	const static int GL_TEXTURE5 = 0x84C5;
	const static int GL_TEXTURE6 = 0x84C6;
	const static int GL_TEXTURE7 = 0x84C7;
	const static int GL_TEXTURE8 = 0x84C8;
	const static int GL_TEXTURE9 = 0x84C9;
	const static int GL_TEXTURE10 = 0x84CA;
	const static int GL_TEXTURE11 = 0x84CB;
	const static int GL_TEXTURE12 = 0x84CC;
	const static int GL_TEXTURE13 = 0x84CD;
	const static int GL_TEXTURE14 = 0x84CE;
	const static int GL_TEXTURE15 = 0x84CF;
	const static int GL_TEXTURE16 = 0x84D0;
	const static int GL_TEXTURE17 = 0x84D1;
	const static int GL_TEXTURE18 = 0x84D2;
	const static int GL_TEXTURE19 = 0x84D3;
	const static int GL_TEXTURE20 = 0x84D4;
	const static int GL_TEXTURE21 = 0x84D5;
	const static int GL_TEXTURE22 = 0x84D6;
	const static int GL_TEXTURE23 = 0x84D7;
	const static int GL_TEXTURE24 = 0x84D8;
	const static int GL_TEXTURE25 = 0x84D9;
	const static int GL_TEXTURE26 = 0x84DA;
	const static int GL_TEXTURE27 = 0x84DB;
	const static int GL_TEXTURE28 = 0x84DC;
	const static int GL_TEXTURE29 = 0x84DD;
	const static int GL_TEXTURE30 = 0x84DE;
	const static int GL_TEXTURE31 = 0x84DF;
	const static int GL_REPEAT = 0x2901;
	const static int GL_CLAMP_TO_EDGE = 0x812F;
	const static int GL_PALETTE4_RGB8_OES = 0x8B90;
	const static int GL_PALETTE4_RGBA8_OES = 0x8B91;
	const static int GL_PALETTE4_R5_G6_B5_OES = 0x8B92;
	const static int GL_PALETTE4_RGBA4_OES = 0x8B93;
	const static int GL_PALETTE4_RGB5_A1_OES = 0x8B94;
	const static int GL_PALETTE8_RGB8_OES = 0x8B95;
	const static int GL_PALETTE8_RGBA8_OES = 0x8B96;
	const static int GL_PALETTE8_R5_G6_B5_OES = 0x8B97;
	const static int GL_PALETTE8_RGBA4_OES = 0x8B98;
	const static int GL_PALETTE8_RGB5_A1_OES = 0x8B99;
	const static int GL_LIGHT0 = 0x4000;
	const static int GL_LIGHT1 = 0x4001;
	const static int GL_LIGHT2 = 0x4002;
	const static int GL_LIGHT3 = 0x4003;
	const static int GL_LIGHT4 = 0x4004;
	const static int GL_LIGHT5 = 0x4005;
	const static int GL_LIGHT6 = 0x4006;
	const static int GL_LIGHT7 = 0x4007;
	const static int GL_POINT = 0x1B00;
	const static int GL_LINE = 0x1B01;
	const static int GL_FILL = 0x1B02;

    enum VertexStates {
        VERTEX_STATE_GL_COLOR_ARRAY = 1 << 0,
        VERTEX_STATE_GL_EDGE_FLAG_ARRAY = 1 << 1,
        VERTEX_STATE_GL_FOG_COORD_ARRAY = 1 << 2,
        VERTEX_STATE_GL_INDEX_ARRAY = 1 << 3,
        VERTEX_STATE_GL_NORMAL_ARRAY = 1 << 4,
        VERTEX_STATE_GL_SECONDARY_COLOR_ARRAY = 1 << 5,
        VERTEX_STATE_GL_TEXTURE_COORD_ARRAY = 1 << 6,
        VERTEX_STATE_GL_VERTEX_ARRAY = 1 << 7
    };
    
    virtual void glAlphaFunc (int func,float ref) const ;
    virtual void glClientActiveTexture (int texture) const ;
    virtual void glColor4f (float red,float green,float blue,float alpha) const ;
    virtual void glColorPointer (int size,int type,int stride,const void* pointer) ;
    virtual void glDisableClientState (int array) ;
    virtual void glEnableClientState (int array) ;
    virtual void glFogf (int pname,float param) const ;
    virtual void glFogfv (int pname,const float* params) const ;
    virtual void glFrustumf (float left,float right,float bottom,float top,float zNear,float zFar) const ;
    virtual void glLightModelf (int pname,float param) const ;
    virtual void glLightModelfv (int pname,const float* params) const ;
    virtual void glLightf (int light,int pname,float param) const ;
    virtual void glLightfv (int light,int pname,const float* params) const ;
    virtual void glLoadIdentity () const ;
    virtual void glLoadMatrixf (const float* m) const ;
    virtual void glLogicOp (int opcode) const ;
    virtual void glMaterialf (int face,int pname,float param) const ;
    virtual void glMaterialfv (int face,int pname,const float* params) const ;
    virtual void glMatrixMode (int mode) const ;
    virtual void glMultMatrixf (const float* m) const ;
    virtual void glMultiTexCoord4f (int target,float s,float t,float r,float q) const ;
    virtual void glNormal3f (float nx,float ny,float nz) const ;
    virtual void glNormalPointer (int type,int stride,const void* pointer) const ;
    virtual void glOrthof (float left,float right,float bottom,float top,float zNear,float zFar) const ;
    virtual void glPointSize (float size) const ;
    virtual void glPopMatrix () const ;
    virtual void glPushMatrix () const ;
    virtual void glRotatef (float angle,float x,float y,float z) const ;
    virtual void glSampleCoverage (float value,bool invert) const ;
    virtual void glScalef (float x,float y,float z) const ;
    virtual void glShadeModel (int mode) const ;
    virtual void glTexCoordPointer (int size,int type,int stride,const void * pointer) ;
    virtual void glTexEnvf (int target,int pname,float param) const ;
    virtual void glTexEnvfv (int target,int pname,const float* params) const ;
    virtual void glTranslatef (float x,float y,float z) const ;
    virtual void glVertexPointer (int size, unsigned int type,int stride,const void* pointer) ;
    virtual void glPolygonMode (int face,int mode) const ;
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GL10_HPP_
