
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

class GL11 : virtual public GL10 {
public:
    static const int GL_OES_VERSION_1_0;
    static const int GL_MAX_ELEMENTS_VERTICES;
    static const int GL_MAX_ELEMENTS_INDICES;
    static const int GL_POLYGON_SMOOTH_HINT;
    static const int GL_VERSION_ES_CM_1_0;
    static const int GL_VERSION_ES_CL_1_0;
    static const int GL_VERSION_ES_CM_1_1;
    static const int GL_VERSION_ES_CL_1_1;
    static const int GL_CLIP_PLANE0;
    static const int GL_CLIP_PLANE1;
    static const int GL_CLIP_PLANE2;
    static const int GL_CLIP_PLANE3;
    static const int GL_CLIP_PLANE4;
    static const int GL_CLIP_PLANE5;
    static const int GL_CURRENT_COLOR;
    static const int GL_CURRENT_NORMAL;
    static const int GL_CURRENT_TEXTURE_COORDS;
    static const int GL_POINT_SIZE;
    static const int GL_POINT_SIZE_MIN;
    static const int GL_POINT_SIZE_MAX;
    static const int GL_POINT_FADE_THRESHOLD_SIZE;
    static const int GL_POINT_DISTANCE_ATTENUATION;
    static const int GL_LINE_WIDTH;
    static const int GL_CULL_FACE_MODE;
    static const int GL_FRONT_FACE;
    static const int GL_SHADE_MODEL;
    static const int GL_DEPTH_RANGE;
    static const int GL_DEPTH_WRITEMASK;
    static const int GL_DEPTH_CLEAR_VALUE;
    static const int GL_DEPTH_FUNC;
    static const int GL_STENCIL_CLEAR_VALUE;
    static const int GL_STENCIL_FUNC;
    static const int GL_STENCIL_VALUE_MASK;
    static const int GL_STENCIL_FAIL;
    static const int GL_STENCIL_PASS_DEPTH_FAIL;
    static const int GL_STENCIL_PASS_DEPTH_PASS;
    static const int GL_STENCIL_REF;
    static const int GL_STENCIL_WRITEMASK;
    static const int GL_MATRIX_MODE;
    static const int GL_VIEWPORT;
    static const int GL_MODELVIEW_STACK_DEPTH;
    static const int GL_PROJECTION_STACK_DEPTH;
    static const int GL_TEXTURE_STACK_DEPTH;
    static const int GL_MODELVIEW_MATRIX;
    static const int GL_PROJECTION_MATRIX;
    static const int GL_TEXTURE_MATRIX;
    static const int GL_ALPHA_TEST_FUNC;
    static const int GL_ALPHA_TEST_REF;
    static const int GL_BLEND_DST;
    static const int GL_BLEND_SRC;
    static const int GL_LOGIC_OP_MODE;
    static const int GL_SCISSOR_BOX;
    static const int GL_COLOR_CLEAR_VALUE;
    static const int GL_COLOR_WRITEMASK;
    static const int GL_MAX_CLIP_PLANES;
    static const int GL_POLYGON_OFFSET_UNITS;
    static const int GL_POLYGON_OFFSET_FACTOR;
    static const int GL_TEXTURE_BINDING_2D;
    static const int GL_VERTEX_ARRAY_SIZE;
    static const int GL_VERTEX_ARRAY_TYPE;
    static const int GL_VERTEX_ARRAY_STRIDE;
    static const int GL_NORMAL_ARRAY_TYPE;
    static const int GL_NORMAL_ARRAY_STRIDE;
    static const int GL_COLOR_ARRAY_SIZE;
    static const int GL_COLOR_ARRAY_TYPE;
    static const int GL_COLOR_ARRAY_STRIDE;
    static const int GL_TEXTURE_COORD_ARRAY_SIZE;
    static const int GL_TEXTURE_COORD_ARRAY_TYPE;
    static const int GL_TEXTURE_COORD_ARRAY_STRIDE;
    static const int GL_VERTEX_ARRAY_POINTER;
    static const int GL_NORMAL_ARRAY_POINTER;
    static const int GL_COLOR_ARRAY_POINTER;
    static const int GL_TEXTURE_COORD_ARRAY_POINTER;
    static const int GL_SAMPLE_BUFFERS;
    static const int GL_SAMPLES;
    static const int GL_SAMPLE_COVERAGE_VALUE;
    static const int GL_SAMPLE_COVERAGE_INVERT;
    static const int GL_GENERATE_MIPMAP_HINT;
    static const int GL_GENERATE_MIPMAP;
    static const int GL_ACTIVE_TEXTURE;
    static const int GL_CLIENT_ACTIVE_TEXTURE;
    static const int GL_ARRAY_BUFFER;
    static const int GL_ELEMENT_ARRAY_BUFFER;
    static const int GL_ARRAY_BUFFER_BINDING;
    static const int GL_ELEMENT_ARRAY_BUFFER_BINDING;
    static const int GL_VERTEX_ARRAY_BUFFER_BINDING;
    static const int GL_NORMAL_ARRAY_BUFFER_BINDING;
    static const int GL_COLOR_ARRAY_BUFFER_BINDING;
    static const int GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING;
    static const int GL_STATIC_DRAW;
    static const int GL_DYNAMIC_DRAW;
    static const int GL_BUFFER_SIZE;
    static const int GL_BUFFER_USAGE;
    static const int GL_SUBTRACT;
    static const int GL_COMBINE;
    static const int GL_COMBINE_RGB;
    static const int GL_COMBINE_ALPHA;
    static const int GL_RGB_SCALE;
    static const int GL_ADD_SIGNED;
    static const int GL_INTERPOLATE;
    static const int GL_CONSTANT;
    static const int GL_PRIMARY_COLOR;
    static const int GL_PREVIOUS;
    static const int GL_OPERAND0_RGB;
    static const int GL_OPERAND1_RGB;
    static const int GL_OPERAND2_RGB;
    static const int GL_OPERAND0_ALPHA;
    static const int GL_OPERAND1_ALPHA;
    static const int GL_OPERAND2_ALPHA;
    static const int GL_ALPHA_SCALE;
    static const int GL_SRC0_RGB;
    static const int GL_SRC1_RGB;
    static const int GL_SRC2_RGB;
    static const int GL_SRC0_ALPHA;
    static const int GL_SRC1_ALPHA;
    static const int GL_SRC2_ALPHA;
    static const int GL_DOT3_RGB;
    static const int GL_DOT3_RGBA;
    static const int GL_POINT_SIZE_ARRAY_OES;
    static const int GL_POINT_SIZE_ARRAY_TYPE_OES;
    static const int GL_POINT_SIZE_ARRAY_STRIDE_OES;
    static const int GL_POINT_SIZE_ARRAY_POINTER_OES;
    static const int GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES;
    static const int GL_POINT_SPRITE_OES;
    static const int GL_COORD_REPLACE_OES;
    static const int GL_OES_point_size_array;
    static const int GL_OES_point_sprite;
    
    virtual void glClipPlanef (int plane,const float* equation) const = 0;
    virtual void glGetClipPlanef (int pname,const float* eqn) const = 0;
    virtual void glGetFloatv (int pname,const float* params) const = 0;
    virtual void glGetLightfv (int light,int pname,const float* params) const = 0;
    virtual void glGetMaterialfv (int face,int pname,const float* params) const = 0;
    virtual void glGetTexParameterfv (int target,int pname,const float* params) const = 0;
    virtual void glPointParameterf (int pname,float param) const = 0;
    virtual void glPointParameterfv (int pname,const float* params) const = 0;
    virtual void glTexParameterfv (int target,int pname,const float* params) const = 0;
    virtual void glBindBuffer (int target,int buffer) const = 0;
    virtual void glBufferData (int target,int size,const char* data,int usage) const = 0;
    virtual void glBufferSubData (int target,int offset,int size,const void* data) const = 0;
    virtual void glColor4ub (char red,char green,char blue,char alpha) const = 0;
    virtual void glDeleteBuffers (int n,const int* buffers) const = 0;
    virtual void glGetBooleanv (int pname,const int* params) const = 0;
    virtual void glGetBufferParameteriv (int target,int pname,const int* params) const = 0;
    virtual void glGenBuffers (int n,const int* buffers) const = 0;
    virtual void glGetPointerv (int pname) const = 0;
    virtual void glGetTexEnviv (int env,int pname,const int* params) const = 0;
    virtual void glGetTexParameteriv (int target,int pname,const int* params) const = 0;
    virtual bool glIsBuffer (int buffer) const = 0;
    virtual bool glIsEnabled (int cap) const = 0;
    virtual bool glIsTexture (int texture) const = 0;
    virtual void glTexEnvi (int target,int pname,int param) const = 0;
    virtual void glTexEnviv (int target,int pname,const int* params) const = 0;
    virtual void glTexParameteri (int target,int pname,int param) const = 0;
    virtual void glTexParameteriv (int target,int pname,const int* params) const = 0;
    virtual void glPointSizePointerOES (int type,int stride,const char* pointer) const = 0;
    virtual void glVertexPointer (int size,int type,int stride, void* pointer) const = 0;
    virtual void glColorPointer (int size,int type,int stride,void* pointer) const = 0;
    virtual void glNormalPointer (int type,int stride,void* pointer) const = 0;
    virtual void glTexCoordPointer (int size,int type,int stride,void* pointer) const = 0;
    virtual void glDrawElements (int mode,int count,int type,void* indices) const = 0;

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_GL11_HPP_
