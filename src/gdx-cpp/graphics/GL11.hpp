
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

#ifndef GDX_CPP_GRAPHICS_GL11_HPP_
#define GDX_CPP_GRAPHICS_GL11_HPP_

#include "GL10.hpp"

namespace gdx_cpp {
namespace graphics {

class GL11 : public GL10 {
public:
    static const int GL_OES_VERSION_1_0 = 1;
    static const int GL_MAX_ELEMENTS_VERTICES = 0x80E8;
    static const int GL_MAX_ELEMENTS_INDICES = 0x80E9;
    static const int GL_POLYGON_SMOOTH_HINT = 0x0C53;
    static const int GL_VERSION_ES_CM_1_0 = 1;
    static const int GL_VERSION_ES_CL_1_0 = 1;
    static const int GL_VERSION_ES_CM_1_1 = 1;
    static const int GL_VERSION_ES_CL_1_1 = 1;
    static const int GL_CLIP_PLANE0 = 0x3000;
    static const int GL_CLIP_PLANE1 = 0x3001;
    static const int GL_CLIP_PLANE2 = 0x3002;
    static const int GL_CLIP_PLANE3 = 0x3003;
    static const int GL_CLIP_PLANE4 = 0x3004;
    static const int GL_CLIP_PLANE5 = 0x3005;
    static const int GL_CURRENT_COLOR = 0x0B00;
    static const int GL_CURRENT_NORMAL = 0x0B02;
    static const int GL_CURRENT_TEXTURE_COORDS = 0x0B03;
    static const int GL_POINT_SIZE = 0x0B11;
    static const int GL_POINT_SIZE_MIN = 0x8126;
    static const int GL_POINT_SIZE_MAX = 0x8127;
    static const int GL_POINT_FADE_THRESHOLD_SIZE = 0x8128;
    static const int GL_POINT_DISTANCE_ATTENUATION = 0x8129;
    static const int GL_LINE_WIDTH = 0x0B21;
    static const int GL_CULL_FACE_MODE = 0x0B45;
    static const int GL_FRONT_FACE = 0x0B46;
    static const int GL_SHADE_MODEL = 0x0B54;
    static const int GL_DEPTH_RANGE = 0x0B70;
    static const int GL_DEPTH_WRITEMASK = 0x0B72;
    static const int GL_DEPTH_CLEAR_VALUE = 0x0B73;
    static const int GL_DEPTH_FUNC = 0x0B74;
    static const int GL_STENCIL_CLEAR_VALUE = 0x0B91;
    static const int GL_STENCIL_FUNC = 0x0B92;
    static const int GL_STENCIL_VALUE_MASK = 0x0B93;
    static const int GL_STENCIL_FAIL = 0x0B94;
    static const int GL_STENCIL_PASS_DEPTH_FAIL = 0x0B95;
    static const int GL_STENCIL_PASS_DEPTH_PASS = 0x0B96;
    static const int GL_STENCIL_REF = 0x0B97;
    static const int GL_STENCIL_WRITEMASK = 0x0B98;
    static const int GL_MATRIX_MODE = 0x0BA0;
    static const int GL_VIEWPORT = 0x0BA2;
    static const int GL_MODELVIEW_STACK_DEPTH = 0x0BA3;
    static const int GL_PROJECTION_STACK_DEPTH = 0x0BA4;
    static const int GL_TEXTURE_STACK_DEPTH = 0x0BA5;
    static const int GL_MODELVIEW_MATRIX = 0x0BA6;
    static const int GL_PROJECTION_MATRIX = 0x0BA7;
    static const int GL_TEXTURE_MATRIX = 0x0BA8;
    static const int GL_ALPHA_TEST_FUNC = 0x0BC1;
    static const int GL_ALPHA_TEST_REF = 0x0BC2;
    static const int GL_BLEND_DST = 0x0BE0;
    static const int GL_BLEND_SRC = 0x0BE1;
    static const int GL_LOGIC_OP_MODE = 0x0BF0;
    static const int GL_SCISSOR_BOX = 0x0C10;
    static const int GL_COLOR_CLEAR_VALUE = 0x0C22;
    static const int GL_COLOR_WRITEMASK = 0x0C23;
    static const int GL_MAX_CLIP_PLANES = 0x0D32;
    static const int GL_POLYGON_OFFSET_UNITS = 0x2A00;
    static const int GL_POLYGON_OFFSET_FACTOR = 0x8038;
    static const int GL_TEXTURE_BINDING_2D = 0x8069;
    static const int GL_VERTEX_ARRAY_SIZE = 0x807A;
    static const int GL_VERTEX_ARRAY_TYPE = 0x807B;
    static const int GL_VERTEX_ARRAY_STRIDE = 0x807C;
    static const int GL_NORMAL_ARRAY_TYPE = 0x807E;
    static const int GL_NORMAL_ARRAY_STRIDE = 0x807F;
    static const int GL_COLOR_ARRAY_SIZE = 0x8081;
    static const int GL_COLOR_ARRAY_TYPE = 0x8082;
    static const int GL_COLOR_ARRAY_STRIDE = 0x8083;
    static const int GL_TEXTURE_COORD_ARRAY_SIZE = 0x8088;
    static const int GL_TEXTURE_COORD_ARRAY_TYPE = 0x8089;
    static const int GL_TEXTURE_COORD_ARRAY_STRIDE = 0x808A;
    static const int GL_VERTEX_ARRAY_POINTER = 0x808E;
    static const int GL_NORMAL_ARRAY_POINTER = 0x808F;
    static const int GL_COLOR_ARRAY_POINTER = 0x8090;
    static const int GL_TEXTURE_COORD_ARRAY_POINTER = 0x8092;
    static const int GL_SAMPLE_BUFFERS = 0x80A8;
    static const int GL_SAMPLES = 0x80A9;
    static const int GL_SAMPLE_COVERAGE_VALUE = 0x80AA;
    static const int GL_SAMPLE_COVERAGE_INVERT = 0x80AB;
    static const int GL_GENERATE_MIPMAP_HINT = 0x8192;
    static const int GL_GENERATE_MIPMAP = 0x8191;
    static const int GL_ACTIVE_TEXTURE = 0x84E0;
    static const int GL_CLIENT_ACTIVE_TEXTURE = 0x84E1;
    static const int GL_ARRAY_BUFFER = 0x8892;
    static const int GL_ELEMENT_ARRAY_BUFFER = 0x8893;
    static const int GL_ARRAY_BUFFER_BINDING = 0x8894;
    static const int GL_ELEMENT_ARRAY_BUFFER_BINDING = 0x8895;
    static const int GL_VERTEX_ARRAY_BUFFER_BINDING = 0x8896;
    static const int GL_NORMAL_ARRAY_BUFFER_BINDING = 0x8897;
    static const int GL_COLOR_ARRAY_BUFFER_BINDING = 0x8898;
    static const int GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING = 0x889A;
    static const int GL_STATIC_DRAW = 0x88E4;
    static const int GL_DYNAMIC_DRAW = 0x88E8;
    static const int GL_BUFFER_SIZE = 0x8764;
    static const int GL_BUFFER_USAGE = 0x8765;
    static const int GL_SUBTRACT = 0x84E7;
    static const int GL_COMBINE = 0x8570;
    static const int GL_COMBINE_RGB = 0x8571;
    static const int GL_COMBINE_ALPHA = 0x8572;
    static const int GL_RGB_SCALE = 0x8573;
    static const int GL_ADD_SIGNED = 0x8574;
    static const int GL_INTERPOLATE = 0x8575;
    static const int GL_CONSTANT = 0x8576;
    static const int GL_PRIMARY_COLOR = 0x8577;
    static const int GL_PREVIOUS = 0x8578;
    static const int GL_OPERAND0_RGB = 0x8590;
    static const int GL_OPERAND1_RGB = 0x8591;
    static const int GL_OPERAND2_RGB = 0x8592;
    static const int GL_OPERAND0_ALPHA = 0x8598;
    static const int GL_OPERAND1_ALPHA = 0x8599;
    static const int GL_OPERAND2_ALPHA = 0x859A;
    static const int GL_ALPHA_SCALE = 0x0D1C;
    static const int GL_SRC0_RGB = 0x8580;
    static const int GL_SRC1_RGB = 0x8581;
    static const int GL_SRC2_RGB = 0x8582;
    static const int GL_SRC0_ALPHA = 0x8588;
    static const int GL_SRC1_ALPHA = 0x8589;
    static const int GL_SRC2_ALPHA = 0x858A;
    static const int GL_DOT3_RGB = 0x86AE;
    static const int GL_DOT3_RGBA = 0x86AF;
    static const int GL_POINT_SIZE_ARRAY_OES = 0x8B9C;
    static const int GL_POINT_SIZE_ARRAY_TYPE_OES = 0x898A;
    static const int GL_POINT_SIZE_ARRAY_STRIDE_OES = 0x898B;
    static const int GL_POINT_SIZE_ARRAY_POINTER_OES = 0x898C;
    static const int GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES = 0x8B9F;
    static const int GL_POINT_SPRITE_OES = 0x8861;
    static const int GL_COORD_REPLACE_OES = 0x8862;
    static const int GL_OES_point_size_array = 1;
    static const int GL_OES_point_sprite = 1;
    
    virtual void glClipPlanef (int plane,int offset) const = 0;
    virtual void glClipPlanef (int plane,const float* equation) const = 0;
    virtual void glGetClipPlanef (int pname,int offset) const = 0;
    virtual void glGetClipPlanef (int pname,const float* eqn) const = 0;
    virtual void glGetFloatv (int pname,int offset) const = 0;
    virtual void glGetFloatv (int pname,const float* params) const = 0;
    virtual void glGetLightfv (int light,int pname,int offset) const = 0;
    virtual void glGetLightfv (int light,int pname,const float* params) const = 0;
    virtual void glGetMaterialfv (int face,int pname,int offset) const = 0;
    virtual void glGetMaterialfv (int face,int pname,const float* params) const = 0;
    virtual void glGetTexParameterfv (int target,int pname,int offset) const = 0;
    virtual void glGetTexParameterfv (int target,int pname,const float* params) const = 0;
    virtual void glPointParameterf (int pname,float param) const = 0;
    virtual void glPointParameterfv (int pname,int offset) const = 0;
    virtual void glPointParameterfv (int pname,const float* params) const = 0;
    virtual void glTexParameterfv (int target,int pname,int offset) const = 0;
    virtual void glTexParameterfv (int target,int pname,const float* params) const = 0;
    virtual void glBindBuffer (int target,int buffer) const = 0;
    virtual void glBufferData (int target,int size,const char* data,int usage) const = 0;
    virtual void glBufferSubData (int target,int offset,int size,const char* data) const = 0;
    virtual void glColor4ub (char red,char green,char blue,char alpha) const = 0;
    virtual void glDeleteBuffers (int n,int offset) const = 0;
    virtual void glDeleteBuffers (int n,const int* buffers) const = 0;
    virtual void glGetBooleanv (int pname,int offset) const = 0;
    virtual void glGetBooleanv (int pname,const int* params) const = 0;
    virtual void glGetBufferParameteriv (int target,int pname,int offset) const = 0;
    virtual void glGetBufferParameteriv (int target,int pname,const int* params) const = 0;
    virtual void glGenBuffers (int n,int offset) const = 0;
    virtual void glGenBuffers (int n,const int* buffers) const = 0;
    virtual void glGetPointerv (int pname) const = 0;
    virtual void glGetTexEnviv (int env,int pname,int offset) const = 0;
    virtual void glGetTexEnviv (int env,int pname,const int* params) const = 0;
    virtual void glGetTexParameteriv (int target,int pname,int offset) const = 0;
    virtual void glGetTexParameteriv (int target,int pname,const int* params) const = 0;
    virtual bool glIsBuffer (int buffer) const = 0;
    virtual bool glIsEnabled (int cap) const = 0;
    virtual bool glIsTexture (int texture) const = 0;
    virtual void glTexEnvi (int target,int pname,int param) const = 0;
    virtual void glTexEnviv (int target,int pname,int offset) const = 0;
    virtual void glTexEnviv (int target,int pname,const int* params) const = 0;
    virtual void glTexParameteri (int target,int pname,int param) const = 0;
    virtual void glTexParameteriv (int target,int pname,int offset) const = 0;
    virtual void glTexParameteriv (int target,int pname,const int* params) const = 0;
    virtual void glPointSizePointerOES (int type,int stride,const char* pointer) const = 0;
    virtual void glVertexPointer (int size,int type,int stride,int pointer) const = 0;
    virtual void glColorPointer (int size,int type,int stride,int pointer) const = 0;
    virtual void glNormalPointer (int type,int stride,int pointer) const = 0;
    virtual void glTexCoordPointer (int size,int type,int stride,int pointer) const = 0;
    virtual void glDrawElements (int mode,int count,int type,int indices) const = 0;

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_GL11_HPP_
