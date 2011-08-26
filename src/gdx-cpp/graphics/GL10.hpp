
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

namespace gdx_cpp {
namespace graphics {

class GL10 : public GLCommon {
public:

    static const int GL_OES_VERSION_1_0 = 1;
    static const int GL_OES_read_format = 1;
    static const int GL_OES_compressed_paletted_texture = 1;
    static const int GL_DEPTH_BUFFER_BIT = 0x00000100;
    static const int GL_STENCIL_BUFFER_BIT = 0x00000400;
    static const int GL_COLOR_BUFFER_BIT = 0x00004000;
    static const int GL_FALSE = 0;
    static const int GL_TRUE = 1;
    static const int GL_POINTS = 0x0000;
    static const int GL_LINES = 0x0001;
    static const int GL_LINE_LOOP = 0x0002;
    static const int GL_LINE_STRIP = 0x0003;
    static const int GL_TRIANGLES = 0x0004;
    static const int GL_TRIANGLE_STRIP = 0x0005;
    static const int GL_TRIANGLE_FAN = 0x0006;
    static const int GL_NEVER = 0x0200;
    static const int GL_LESS = 0x0201;
    static const int GL_EQUAL = 0x0202;
    static const int GL_LEQUAL = 0x0203;
    static const int GL_GREATER = 0x0204;
    static const int GL_NOTEQUAL = 0x0205;
    static const int GL_GEQUAL = 0x0206;
    static const int GL_ALWAYS = 0x0207;
    static const int GL_ZERO = 0;
    static const int GL_ONE = 1;
    static const int GL_SRC_COLOR = 0x0300;
    static const int GL_ONE_MINUS_SRC_COLOR = 0x0301;
    static const int GL_SRC_ALPHA = 0x0302;
    static const int GL_ONE_MINUS_SRC_ALPHA = 0x0303;
    static const int GL_DST_ALPHA = 0x0304;
    static const int GL_ONE_MINUS_DST_ALPHA = 0x0305;
    static const int GL_DST_COLOR = 0x0306;
    static const int GL_ONE_MINUS_DST_COLOR = 0x0307;
    static const int GL_SRC_ALPHA_SATURATE = 0x0308;
    static const int GL_FRONT = 0x0404;
    static const int GL_BACK = 0x0405;
    static const int GL_FRONT_AND_BACK = 0x0408;
    static const int GL_FOG = 0x0B60;
    static const int GL_LIGHTING = 0x0B50;
    static const int GL_TEXTURE_2D = 0x0DE1;
    static const int GL_CULL_FACE = 0x0B44;
    static const int GL_ALPHA_TEST = 0x0BC0;
    static const int GL_BLEND = 0x0BE2;
    static const int GL_COLOR_LOGIC_OP = 0x0BF2;
    static const int GL_DITHER = 0x0BD0;
    static const int GL_STENCIL_TEST = 0x0B90;
    static const int GL_DEPTH_TEST = 0x0B71;
    static const int GL_POINT_SMOOTH = 0x0B10;
    static const int GL_LINE_SMOOTH = 0x0B20;
    static const int GL_SCISSOR_TEST = 0x0C11;
    static const int GL_COLOR_MATERIAL = 0x0B57;
    static const int GL_NORMALIZE = 0x0BA1;
    static const int GL_RESCALE_NORMAL = 0x803A;
    static const int GL_POLYGON_OFFSET_FILL = 0x8037;
    static const int GL_VERTEX_ARRAY = 0x8074;
    static const int GL_NORMAL_ARRAY = 0x8075;
    static const int GL_COLOR_ARRAY = 0x8076;
    static const int GL_TEXTURE_COORD_ARRAY = 0x8078;
    static const int GL_MULTISAMPLE = 0x809D;
    static const int GL_SAMPLE_ALPHA_TO_COVERAGE = 0x809E;
    static const int GL_SAMPLE_ALPHA_TO_ONE = 0x809F;
    static const int GL_SAMPLE_COVERAGE = 0x80A0;
    static const int GL_NO_ERROR = 0;
    static const int GL_INVALID_ENUM = 0x0500;
    static const int GL_INVALID_VALUE = 0x0501;
    static const int GL_INVALID_OPERATION = 0x0502;
    static const int GL_STACK_OVERFLOW = 0x0503;
    static const int GL_STACK_UNDERFLOW = 0x0504;
    static const int GL_OUT_OF_MEMORY = 0x0505;
    static const int GL_EXP = 0x0800;
    static const int GL_EXP2 = 0x0801;
    static const int GL_FOG_DENSITY = 0x0B62;
    static const int GL_FOG_START = 0x0B63;
    static const int GL_FOG_END = 0x0B64;
    static const int GL_FOG_MODE = 0x0B65;
    static const int GL_FOG_COLOR = 0x0B66;
    static const int GL_CW = 0x0900;
    static const int GL_CCW = 0x0901;
    static const int GL_SMOOTH_POINT_SIZE_RANGE = 0x0B12;
    static const int GL_SMOOTH_LINE_WIDTH_RANGE = 0x0B22;
    static const int GL_ALIASED_POINT_SIZE_RANGE = 0x846D;
    static const int GL_ALIASED_LINE_WIDTH_RANGE = 0x846E;
    static const int GL_IMPLEMENTATION_COLOR_READ_TYPE_OES = 0x8B9A;
    static const int GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES = 0x8B9B;
    static const int GL_MAX_LIGHTS = 0x0D31;
    static const int GL_MAX_TEXTURE_SIZE = 0x0D33;
    static const int GL_MAX_MODELVIEW_STACK_DEPTH = 0x0D36;
    static const int GL_MAX_PROJECTION_STACK_DEPTH = 0x0D38;
    static const int GL_MAX_TEXTURE_STACK_DEPTH = 0x0D39;
    static const int GL_MAX_VIEWPORT_DIMS = 0x0D3A;
    static const int GL_MAX_ELEMENTS_VERTICES = 0x80E8;
    static const int GL_MAX_ELEMENTS_INDICES = 0x80E9;
    static const int GL_MAX_TEXTURE_UNITS = 0x84E2;
    static const int GL_NUM_COMPRESSED_TEXTURE_FORMATS = 0x86A2;
    static const int GL_COMPRESSED_TEXTURE_FORMATS = 0x86A3;
    static const int GL_SUBPIXEL_BITS = 0x0D50;
    static const int GL_RED_BITS = 0x0D52;
    static const int GL_GREEN_BITS = 0x0D53;
    static const int GL_BLUE_BITS = 0x0D54;
    static const int GL_ALPHA_BITS = 0x0D55;
    static const int GL_DEPTH_BITS = 0x0D56;
    static const int GL_STENCIL_BITS = 0x0D57;
    static const int GL_DONT_CARE = 0x1100;
    static const int GL_FASTEST = 0x1101;
    static const int GL_NICEST = 0x1102;
    static const int GL_PERSPECTIVE_CORRECTION_HINT = 0x0C50;
    static const int GL_POINT_SMOOTH_HINT = 0x0C51;
    static const int GL_LINE_SMOOTH_HINT = 0x0C52;
    static const int GL_POLYGON_SMOOTH_HINT = 0x0C53;
    static const int GL_FOG_HINT = 0x0C54;
    static const int GL_LIGHT_MODEL_AMBIENT = 0x0B53;
    static const int GL_LIGHT_MODEL_TWO_SIDE = 0x0B52;
    static const int GL_AMBIENT = 0x1200;
    static const int GL_DIFFUSE = 0x1201;
    static const int GL_SPECULAR = 0x1202;
    static const int GL_POSITION = 0x1203;
    static const int GL_SPOT_DIRECTION = 0x1204;
    static const int GL_SPOT_EXPONENT = 0x1205;
    static const int GL_SPOT_CUTOFF = 0x1206;
    static const int GL_CONSTANT_ATTENUATION = 0x1207;
    static const int GL_LINEAR_ATTENUATION = 0x1208;
    static const int GL_QUADRATIC_ATTENUATION = 0x1209;
    static const int GL_BYTE = 0x1400;
    static const int GL_UNSIGNED_BYTE = 0x1401;
    static const int GL_SHORT = 0x1402;
    static const int GL_UNSIGNED_SHORT = 0x1403;
    static const int GL_FLOAT = 0x1406;
    static const int GL_CLEAR = 0x1500;
    static const int GL_AND = 0x1501;
    static const int GL_AND_REVERSE = 0x1502;
    static const int GL_COPY = 0x1503;
    static const int GL_AND_INVERTED = 0x1504;
    static const int GL_NOOP = 0x1505;
    static const int GL_XOR = 0x1506;
    static const int GL_OR = 0x1507;
    static const int GL_NOR = 0x1508;
    static const int GL_EQUIV = 0x1509;
    static const int GL_INVERT = 0x150A;
    static const int GL_OR_REVERSE = 0x150B;
    static const int GL_COPY_INVERTED = 0x150C;
    static const int GL_OR_INVERTED = 0x150D;
    static const int GL_NAND = 0x150E;
    static const int GL_SET = 0x150F;
    static const int GL_EMISSION = 0x1600;
    static const int GL_SHININESS = 0x1601;
    static const int GL_AMBIENT_AND_DIFFUSE = 0x1602;
    static const int GL_MODELVIEW = 0x1700;
    static const int GL_PROJECTION = 0x1701;
    static const int GL_TEXTURE = 0x1702;
    static const int GL_ALPHA = 0x1906;
    static const int GL_RGB = 0x1907;
    static const int GL_RGBA = 0x1908;
    static const int GL_LUMINANCE = 0x1909;
    static const int GL_LUMINANCE_ALPHA = 0x190A;
    static const int GL_UNPACK_ALIGNMENT = 0x0CF5;
    static const int GL_PACK_ALIGNMENT = 0x0D05;
    static const int GL_UNSIGNED_SHORT_4_4_4_4 = 0x8033;
    static const int GL_UNSIGNED_SHORT_5_5_5_1 = 0x8034;
    static const int GL_UNSIGNED_SHORT_5_6_5 = 0x8363;
    static const int GL_FLAT = 0x1D00;
    static const int GL_SMOOTH = 0x1D01;
    static const int GL_KEEP = 0x1E00;
    static const int GL_REPLACE = 0x1E01;
    static const int GL_INCR = 0x1E02;
    static const int GL_DECR = 0x1E03;
    static const int GL_VENDOR = 0x1F00;
    static const int GL_RENDERER = 0x1F01;
    static const int GL_VERSION = 0x1F02;
    static const int GL_EXTENSIONS = 0x1F03;
    static const int GL_MODULATE = 0x2100;
    static const int GL_DECAL = 0x2101;
    static const int GL_ADD = 0x0104;
    static const int GL_TEXTURE_ENV_MODE = 0x2200;
    static const int GL_TEXTURE_ENV_COLOR = 0x2201;
    static const int GL_TEXTURE_ENV = 0x2300;
    static const int GL_NEAREST = 0x2600;
    static const int GL_LINEAR = 0x2601;
    static const int GL_NEAREST_MIPMAP_NEAREST = 0x2700;
    static const int GL_LINEAR_MIPMAP_NEAREST = 0x2701;
    static const int GL_NEAREST_MIPMAP_LINEAR = 0x2702;
    static const int GL_LINEAR_MIPMAP_LINEAR = 0x2703;
    static const int GL_TEXTURE_MAG_FILTER = 0x2800;
    static const int GL_TEXTURE_MIN_FILTER = 0x2801;
    static const int GL_TEXTURE_WRAP_S = 0x2802;
    static const int GL_TEXTURE_WRAP_T = 0x2803;
    static const int GL_TEXTURE0 = 0x84C0;
    static const int GL_TEXTURE1 = 0x84C1;
    static const int GL_TEXTURE2 = 0x84C2;
    static const int GL_TEXTURE3 = 0x84C3;
    static const int GL_TEXTURE4 = 0x84C4;
    static const int GL_TEXTURE5 = 0x84C5;
    static const int GL_TEXTURE6 = 0x84C6;
    static const int GL_TEXTURE7 = 0x84C7;
    static const int GL_TEXTURE8 = 0x84C8;
    static const int GL_TEXTURE9 = 0x84C9;
    static const int GL_TEXTURE10 = 0x84CA;
    static const int GL_TEXTURE11 = 0x84CB;
    static const int GL_TEXTURE12 = 0x84CC;
    static const int GL_TEXTURE13 = 0x84CD;
    static const int GL_TEXTURE14 = 0x84CE;
    static const int GL_TEXTURE15 = 0x84CF;
    static const int GL_TEXTURE16 = 0x84D0;
    static const int GL_TEXTURE17 = 0x84D1;
    static const int GL_TEXTURE18 = 0x84D2;
    static const int GL_TEXTURE19 = 0x84D3;
    static const int GL_TEXTURE20 = 0x84D4;
    static const int GL_TEXTURE21 = 0x84D5;
    static const int GL_TEXTURE22 = 0x84D6;
    static const int GL_TEXTURE23 = 0x84D7;
    static const int GL_TEXTURE24 = 0x84D8;
    static const int GL_TEXTURE25 = 0x84D9;
    static const int GL_TEXTURE26 = 0x84DA;
    static const int GL_TEXTURE27 = 0x84DB;
    static const int GL_TEXTURE28 = 0x84DC;
    static const int GL_TEXTURE29 = 0x84DD;
    static const int GL_TEXTURE30 = 0x84DE;
    static const int GL_TEXTURE31 = 0x84DF;
    static const int GL_REPEAT = 0x2901;
    static const int GL_CLAMP_TO_EDGE = 0x812F;
    static const int GL_PALETTE4_RGB8_OES = 0x8B90;
    static const int GL_PALETTE4_RGBA8_OES = 0x8B91;
    static const int GL_PALETTE4_R5_G6_B5_OES = 0x8B92;
    static const int GL_PALETTE4_RGBA4_OES = 0x8B93;
    static const int GL_PALETTE4_RGB5_A1_OES = 0x8B94;
    static const int GL_PALETTE8_RGB8_OES = 0x8B95;
    static const int GL_PALETTE8_RGBA8_OES = 0x8B96;
    static const int GL_PALETTE8_R5_G6_B5_OES = 0x8B97;
    static const int GL_PALETTE8_RGBA4_OES = 0x8B98;
    static const int GL_PALETTE8_RGB5_A1_OES = 0x8B99;
    static const int GL_LIGHT0 = 0x4000;
    static const int GL_LIGHT1 = 0x4001;
    static const int GL_LIGHT2 = 0x4002;
    static const int GL_LIGHT3 = 0x4003;
    static const int GL_LIGHT4 = 0x4004;
    static const int GL_LIGHT5 = 0x4005;
    static const int GL_LIGHT6 = 0x4006;
    static const int GL_LIGHT7 = 0x4007;

    static const int GL_POINT = 0x1B00;
    static const int GL_LINE = 0x1B01;
    static const int GL_FILL = 0x1B02;
    
    virtual void glAlphaFunc (int func,float ref) const = 0;
    virtual void glClientActiveTexture (int texture) const = 0;
    virtual void glColor4f (float red,float green,float blue,float alpha) const = 0;
    virtual void glColorPointer (int size,int type,int stride,const char*& pointer) const = 0;
    virtual void glDeleteTextures (int n,int offset) const = 0;
    virtual void glDisableClientState (int array) const = 0;
    virtual void glEnableClientState (int array) const = 0;
    virtual void glFogf (int pname,float param) const = 0;
    virtual void glFogfv (int pname,int offset) const = 0;
    virtual void glFogfv (int pname,const float*& params) const = 0;
    virtual void glFrustumf (float left,float right,float bottom,float top,float zNear,float zFar) const = 0;
    virtual void glGenTextures (int n,int offset) const = 0;
    virtual void glGetIntegerv (int pname,int offset) const = 0;
    virtual void glLightModelf (int pname,float param) const = 0;
    virtual void glLightModelfv (int pname,int offset) const = 0;
    virtual void glLightModelfv (int pname,const float*& params) const = 0;
    virtual void glLightf (int light,int pname,float param) const = 0;
    virtual void glLightfv (int light,int pname,int offset) const = 0;
    virtual void glLightfv (int light,int pname,const float*& params) const = 0;
    virtual void glLoadIdentity () const = 0;
    virtual void glLoadMatrixf (float* m, int offset) const = 0;
    virtual void glLoadMatrixf (const float* m) const = 0;
    virtual void glLogicOp (int opcode) const = 0;
    virtual void glMaterialf (int face,int pname,float param) const = 0;
    virtual void glMaterialfv (int face,int pname,int offset) const = 0;
    virtual void glMaterialfv (int face,int pname,const float*& params) const = 0;
    virtual void glMatrixMode (int mode) const = 0;
    virtual void glMultMatrixf (int offset) const = 0;
    virtual void glMultMatrixf (const float*& m) const = 0;
    virtual void glMultiTexCoord4f (int target,float s,float t,float r,float q) const = 0;
    virtual void glNormal3f (float nx,float ny,float nz) const = 0;
    virtual void glNormalPointer (int type,int stride,const char*& pointer) const = 0;
    virtual void glOrthof (float left,float right,float bottom,float top,float zNear,float zFar) const = 0;
    virtual void glPointSize (float size) const = 0;
    virtual void glPopMatrix () const = 0;
    virtual void glPushMatrix () const = 0;
    virtual void glRotatef (float angle,float x,float y,float z) const = 0;
    virtual void glSampleCoverage (float value,bool invert) const = 0;
    virtual void glScalef (float x,float y,float z) const = 0;
    virtual void glShadeModel (int mode) const = 0;
    virtual void glTexCoordPointer (int size,int type,int stride,const char*& pointer) const = 0;
    virtual void glTexEnvf (int target,int pname,float param) const = 0;
    virtual void glTexEnvfv (int target,int pname,int offset) const = 0;
    virtual void glTexEnvfv (int target,int pname,const float*& params) const = 0;
    virtual void glTranslatef (float x,float y,float z) const = 0;
    virtual void glVertexPointer (int size,int type,int stride,const char*& pointer) const = 0;
    virtual void glPolygonMode (int face,int mode) const = 0;
};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_GL10_HPP_
