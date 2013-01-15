
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

#ifndef GDX_CPP_GRAPHICS_GL20_HPP_
#define GDX_CPP_GRAPHICS_GL20_HPP_

#include "GLCommon.hpp"


// Extensions
#undef GL_COVERAGE_BUFFER_BIT_NV

namespace gdx {

class GL20 : virtual public GLCommon {
public:

  static const int GL_ES_VERSION_2_0;
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
  static const int GL_FUNC_ADD;
  static const int GL_BLEND_EQUATION;
  static const int GL_BLEND_EQUATION_RGB;
  static const int GL_BLEND_EQUATION_ALPHA;
  static const int GL_FUNC_SUBTRACT;
  static const int GL_FUNC_REVERSE_SUBTRACT;
  static const int GL_BLEND_DST_RGB;
  static const int GL_BLEND_SRC_RGB;
  static const int GL_BLEND_DST_ALPHA;
  static const int GL_BLEND_SRC_ALPHA;
  static const int GL_CONSTANT_COLOR;
  static const int GL_ONE_MINUS_CONSTANT_COLOR;
  static const int GL_CONSTANT_ALPHA;
  static const int GL_ONE_MINUS_CONSTANT_ALPHA;
  static const int GL_BLEND_COLOR;
  static const int GL_ARRAY_BUFFER;
  static const int GL_ELEMENT_ARRAY_BUFFER;
  static const int GL_ARRAY_BUFFER_BINDING;
  static const int GL_ELEMENT_ARRAY_BUFFER_BINDING;
  static const int GL_STREAM_DRAW;
  static const int GL_STATIC_DRAW;
  static const int GL_DYNAMIC_DRAW;
  static const int GL_BUFFER_SIZE;
  static const int GL_BUFFER_USAGE;
  static const int GL_CURRENT_VERTEX_ATTRIB;
  static const int GL_FRONT;
  static const int GL_BACK;
  static const int GL_FRONT_AND_BACK;
  static const int GL_TEXTURE_2D;
  static const int GL_CULL_FACE;
  static const int GL_BLEND;
  static const int GL_DITHER;
  static const int GL_STENCIL_TEST;
  static const int GL_DEPTH_TEST;
  static const int GL_SCISSOR_TEST;
  static const int GL_POLYGON_OFFSET_FILL;
  static const int GL_SAMPLE_ALPHA_TO_COVERAGE;
  static const int GL_SAMPLE_COVERAGE;
  static const int GL_NO_ERROR;
  static const int GL_INVALID_ENUM;
  static const int GL_INVALID_VALUE;
  static const int GL_INVALID_OPERATION;
  static const int GL_OUT_OF_MEMORY;
  static const int GL_CW;
  static const int GL_CCW;
  static const int GL_LINE_WIDTH;
  static const int GL_ALIASED_POINT_SIZE_RANGE;
  static const int GL_ALIASED_LINE_WIDTH_RANGE;
  static const int GL_CULL_FACE_MODE;
  static const int GL_FRONT_FACE;
  static const int GL_DEPTH_RANGE;
  static const int GL_DEPTH_WRITEMASK;
  static const int GL_DEPTH_CLEAR_VALUE;
  static const int GL_DEPTH_FUNC;
  static const int GL_STENCIL_CLEAR_VALUE;
  static const int GL_STENCIL_FUNC;
  static const int GL_STENCIL_FAIL;
  static const int GL_STENCIL_PASS_DEPTH_FAIL;
  static const int GL_STENCIL_PASS_DEPTH_PASS;
  static const int GL_STENCIL_REF;
  static const int GL_STENCIL_VALUE_MASK;
  static const int GL_STENCIL_WRITEMASK;
  static const int GL_STENCIL_BACK_FUNC;
  static const int GL_STENCIL_BACK_FAIL;
  static const int GL_STENCIL_BACK_PASS_DEPTH_FAIL;
  static const int GL_STENCIL_BACK_PASS_DEPTH_PASS;
  static const int GL_STENCIL_BACK_REF;
  static const int GL_STENCIL_BACK_VALUE_MASK;
  static const int GL_STENCIL_BACK_WRITEMASK;
  static const int GL_VIEWPORT;
  static const int GL_SCISSOR_BOX;
  static const int GL_COLOR_CLEAR_VALUE;
  static const int GL_COLOR_WRITEMASK;
  static const int GL_UNPACK_ALIGNMENT;
  static const int GL_PACK_ALIGNMENT;
  static const int GL_MAX_TEXTURE_SIZE;
  static const int GL_MAX_VIEWPORT_DIMS;
  static const int GL_SUBPIXEL_BITS;
  static const int GL_RED_BITS;
  static const int GL_GREEN_BITS;
  static const int GL_BLUE_BITS;
  static const int GL_ALPHA_BITS;
  static const int GL_DEPTH_BITS;
  static const int GL_STENCIL_BITS;
  static const int GL_POLYGON_OFFSET_UNITS;
  static const int GL_POLYGON_OFFSET_FACTOR;
  static const int GL_TEXTURE_BINDING_2D;
  static const int GL_SAMPLE_BUFFERS;
  static const int GL_SAMPLES;
  static const int GL_SAMPLE_COVERAGE_VALUE;
  static const int GL_SAMPLE_COVERAGE_INVERT;
  static const int GL_NUM_COMPRESSED_TEXTURE_FORMATS;
  static const int GL_COMPRESSED_TEXTURE_FORMATS;
  static const int GL_DONT_CARE;
  static const int GL_FASTEST;
  static const int GL_NICEST;
  static const int GL_GENERATE_MIPMAP_HINT;
  static const int GL_BYTE;
  static const int GL_UNSIGNED_BYTE;
  static const int GL_SHORT;
  static const int GL_UNSIGNED_SHORT;
  static const int GL_INT;
  static const int GL_UNSIGNED_INT;
  static const int GL_FLOAT;
  static const int GL_FIXED;
  static const int GL_DEPTH_COMPONENT;
  static const int GL_ALPHA;
  static const int GL_RGB;
  static const int GL_RGBA;
  static const int GL_LUMINANCE;
  static const int GL_LUMINANCE_ALPHA;
  static const int GL_UNSIGNED_SHORT_4_4_4_4;
  static const int GL_UNSIGNED_SHORT_5_5_5_1;
  static const int GL_UNSIGNED_SHORT_5_6_5;
  static const int GL_FRAGMENT_SHADER;
  static const int GL_VERTEX_SHADER;
  static const int GL_MAX_VERTEX_ATTRIBS;
  static const int GL_MAX_VERTEX_UNIFORM_VECTORS;
  static const int GL_MAX_VARYING_VECTORS;
  static const int GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
  static const int GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS;
  static const int GL_MAX_TEXTURE_IMAGE_UNITS;
  static const int GL_MAX_FRAGMENT_UNIFORM_VECTORS;
  static const int GL_SHADER_TYPE;
  static const int GL_DELETE_STATUS;
  static const int GL_LINK_STATUS;
  static const int GL_VALIDATE_STATUS;
  static const int GL_ATTACHED_SHADERS;
  static const int GL_ACTIVE_UNIFORMS;
  static const int GL_ACTIVE_UNIFORM_MAX_LENGTH;
  static const int GL_ACTIVE_ATTRIBUTES;
  static const int GL_ACTIVE_ATTRIBUTE_MAX_LENGTH;
  static const int GL_SHADING_LANGUAGE_VERSION;
  static const int GL_CURRENT_PROGRAM;
  static const int GL_NEVER;
  static const int GL_LESS;
  static const int GL_EQUAL;
  static const int GL_LEQUAL;
  static const int GL_GREATER;
  static const int GL_NOTEQUAL;
  static const int GL_GEQUAL;
  static const int GL_ALWAYS;
  static const int GL_KEEP;
  static const int GL_REPLACE;
  static const int GL_INCR;
  static const int GL_DECR;
  static const int GL_INVERT;
  static const int GL_INCR_WRAP;
  static const int GL_DECR_WRAP;
  static const int GL_VENDOR;
  static const int GL_RENDERER;
  static const int GL_VERSION;
  static const int GL_EXTENSIONS;
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
  static const int GL_TEXTURE;
  static const int GL_TEXTURE_CUBE_MAP;
  static const int GL_TEXTURE_BINDING_CUBE_MAP;
  static const int GL_TEXTURE_CUBE_MAP_POSITIVE_X;
  static const int GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
  static const int GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
  static const int GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
  static const int GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
  static const int GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
  static const int GL_MAX_CUBE_MAP_TEXTURE_SIZE;
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
  static const int GL_ACTIVE_TEXTURE;
  static const int GL_REPEAT;
  static const int GL_CLAMP_TO_EDGE;
  static const int GL_MIRRORED_REPEAT;
  static const int GL_FLOAT_VEC2;
  static const int GL_FLOAT_VEC3;
  static const int GL_FLOAT_VEC4;
  static const int GL_INT_VEC2;
  static const int GL_INT_VEC3;
  static const int GL_INT_VEC4;
  static const int GL_BOOL;
  static const int GL_BOOL_VEC2;
  static const int GL_BOOL_VEC3;
  static const int GL_BOOL_VEC4;
  static const int GL_FLOAT_MAT2;
  static const int GL_FLOAT_MAT3;
  static const int GL_FLOAT_MAT4;
  static const int GL_SAMPLER_2D;
  static const int GL_SAMPLER_CUBE;
  static const int GL_VERTEX_ATTRIB_ARRAY_ENABLED;
  static const int GL_VERTEX_ATTRIB_ARRAY_SIZE;
  static const int GL_VERTEX_ATTRIB_ARRAY_STRIDE;
  static const int GL_VERTEX_ATTRIB_ARRAY_TYPE;
  static const int GL_VERTEX_ATTRIB_ARRAY_NORMALIZED;
  static const int GL_VERTEX_ATTRIB_ARRAY_POINTER;
  static const int GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING;
  static const int GL_IMPLEMENTATION_COLOR_READ_TYPE;
  static const int GL_IMPLEMENTATION_COLOR_READ_FORMAT;
  static const int GL_COMPILE_STATUS;
  static const int GL_INFO_LOG_LENGTH;
  static const int GL_SHADER_SOURCE_LENGTH;
  static const int GL_SHADER_COMPILER;
  static const int GL_SHADER_BINARY_FORMATS;
  static const int GL_NUM_SHADER_BINARY_FORMATS;
  static const int GL_LOW_FLOAT;
  static const int GL_MEDIUM_FLOAT;
  static const int GL_HIGH_FLOAT;
  static const int GL_LOW_INT;
  static const int GL_MEDIUM_INT;
  static const int GL_HIGH_INT;
  static const int GL_FRAMEBUFFER;
  static const int GL_RENDERBUFFER;
  static const int GL_RGBA4;
  static const int GL_RGB5_A1;
  static const int GL_RGB565;
  static const int GL_DEPTH_COMPONENT16;
  static const int GL_STENCIL_INDEX;
  static const int GL_STENCIL_INDEX8;
  static const int GL_RENDERBUFFER_WIDTH;
  static const int GL_RENDERBUFFER_HEIGHT;
  static const int GL_RENDERBUFFER_INTERNAL_FORMAT;
  static const int GL_RENDERBUFFER_RED_SIZE;
  static const int GL_RENDERBUFFER_GREEN_SIZE;
  static const int GL_RENDERBUFFER_BLUE_SIZE;
  static const int GL_RENDERBUFFER_ALPHA_SIZE;
  static const int GL_RENDERBUFFER_DEPTH_SIZE;
  static const int GL_RENDERBUFFER_STENCIL_SIZE;
  static const int GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE;
  static const int GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME;
  static const int GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL;
  static const int GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE;
  static const int GL_COLOR_ATTACHMENT0;
  static const int GL_DEPTH_ATTACHMENT;
  static const int GL_STENCIL_ATTACHMENT;
  static const int GL_NONE;
  static const int GL_FRAMEBUFFER_COMPLETE;
  static const int GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT;
  static const int GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT;
  static const int GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS;
  static const int GL_FRAMEBUFFER_UNSUPPORTED;
  static const int GL_FRAMEBUFFER_BINDING;
  static const int GL_RENDERBUFFER_BINDING;
  static const int GL_MAX_RENDERBUFFER_SIZE;
  static const int GL_INVALID_FRAMEBUFFER_OPERATION;
  static const int GL_VERTEX_PROGRAM_POINT_SIZE;

  // Extensions
  static const int GL_COVERAGE_BUFFER_BIT_NV;
  
    virtual void glAttachShader (int program,int shader) const;
    virtual void glBindAttribLocation (int program,int index,const std::string& name) const;
    virtual void glBindBuffer (int target,int buffer) const;
    virtual void glBindFramebuffer (int target,int framebuffer) const;
    virtual void glBindRenderbuffer (int target,int renderbuffer) const;
    virtual void glBlendColor (float red,float green,float blue,float alpha) const;
    virtual void glBlendEquation (int mode) const;
    virtual void glBlendEquationSeparate (int modeRGB,int modeAlpha) const;
    virtual void glBlendFuncSeparate (int srcRGB,int dstRGB,int srcAlpha,int dstAlpha) const;
    virtual void glBufferData (int target,int size,const unsigned char* data,int usage) const;
    virtual void glBufferSubData (int target,int offset,int size,const char* data) const;
    virtual int glCheckFramebufferStatus (int target) const;
    virtual void glCompileShader (int shader) const;
    virtual int glCreateProgram () const;
    virtual int glCreateShader (int type) const;
    virtual void glDeleteBuffers (int n, unsigned int* buffers) const;
    virtual void glDeleteFramebuffers (int n,const unsigned int* framebuffers) const;
    virtual void glDeleteProgram (int program) const;
    virtual void glDeleteRenderbuffers (int n,const unsigned int* renderbuffers) const;
    virtual void glDeleteShader (int shader) const;
    virtual void glDetachShader (int program,int shader) const;
    virtual void glDisableVertexAttribArray (int index) const;
    virtual void glDrawElements (int mode,int count,int type, const void* indices) const;
    virtual void glEnableVertexAttribArray (int index) const;
    virtual void glFramebufferRenderbuffer (int target,int attachment,int renderbuffertarget,int renderbuffer) const;
    virtual void glFramebufferTexture2D (int target,int attachment,int textarget,int texture,int level) const;
    virtual void glGenBuffers (int n, unsigned int* buffers) const;
    virtual void glGenerateMipmap (int target) const;
    virtual void glGenFramebuffers (int n, unsigned int* framebuffers) const;
    virtual void glGenRenderbuffers (int n, unsigned int* renderbuffers) const;
    virtual   std::string glGetActiveAttrib (int program,int index,const int* size,const char* type) const;
    virtual   std::string glGetActiveUniform (int program,int index,const int* size,const char* type) const;
    virtual void glGetAttachedShaders (int program,int maxcount, int* count, unsigned int* shaders) const;
    virtual   int glGetAttribLocation (int program,const char* name) const;
    virtual void glGetBooleanv (unsigned int pname, unsigned char* params) const;
    virtual void glGetBufferParameteriv (unsigned int target, unsigned int pname, int* params) const;
    virtual void glGetFloatv (int pname, float* params) const;
    virtual void glGetFramebufferAttachmentParameteriv (int target,int attachment,int pname, int* params) const;
    virtual void glGetProgramiv (int program,int pname, int* params) const;
    virtual   std::string glGetProgramInfoLog (int program) const;
    virtual void glGetRenderbufferParameteriv (int target,int pname, int* params) const;
    virtual void glGetShaderiv (int shader,int pname, int* params) const;
    virtual   std::string glGetShaderInfoLog (int shader) const;
    virtual void glGetShaderPrecisionFormat (int shadertype,int precisiontype, int* range, int* precision) const;
    virtual void glGetShaderSource (unsigned int shader,int bufsize, int* length, char* source) const;
    virtual void glGetTexParameterfv (int target,int pname, float* params) const;
    virtual void glGetTexParameteriv (int target,int pname, int* params) const;
    virtual void glGetUniformfv (int program,int location, float* params) const;
    virtual void glGetUniformiv (int program,int location, int* params) const;
    virtual   int glGetUniformLocation (int program, const std::string& name) const;
    virtual void glGetVertexAttribfv (int index,int pname, float* params) const;
    virtual void glGetVertexAttribiv (int index,int pname, int* params) const;
    virtual void glGetVertexAttribPointerv (int index,int pname, void* pointer) const;
    virtual   bool glIsBuffer (int buffer) const;
    virtual   bool glIsEnabled (int cap) const;
    virtual   bool glIsFramebuffer (int framebuffer) const;
    virtual   bool glIsProgram (int program) const;
    virtual   bool glIsRenderbuffer (int renderbuffer) const;
    virtual   bool glIsShader (int shader) const;
    virtual   bool glIsTexture (int texture) const;
    virtual void glLinkProgram (int program) const;
    virtual void glReleaseShaderCompiler () const;
    virtual void glRenderbufferStorage (int target,int internalformat,int width,int height) const;
    virtual void glSampleCoverage (float value,bool invert) const;
    virtual void glShaderBinary (int n,const unsigned int* shaders,int binaryformat,const void* binary,int length) const;
    virtual void glShaderSource (int shader, const std::string& string) const;
    virtual void glStencilFuncSeparate (int face,int func,int ref,int mask) const;
    virtual void glStencilMaskSeparate (int face,int mask) const;
    virtual void glStencilOpSeparate (int face,int fail,int zfail,int zpass) const;
    virtual void glTexParameterfv (int target,int pname,const float* params) const;
    virtual void glTexParameteri (int target,int pname,int param) const;
    virtual void glTexParameteriv (int target,int pname,const int* params) const;
    virtual void glUniform1f (int location,float x) const;
    virtual void glUniform1fv (int location,int count,const float* v) const;
    virtual void glUniform1i (int location,int x) const;
    virtual void glUniform1iv (int location,int count,const int* v) const;
    virtual void glUniform2f (int location,float x,float y) const;
    virtual void glUniform2fv (int location,int count,const float* v) const;
    virtual void glUniform2i (int location,int x,int y) const;
    virtual void glUniform2iv (int location,int count,const int* v) const;
    virtual void glUniform3f (int location,float x,float y,float z) const;
    virtual void glUniform3fv (int location,int count,const float* v) const;
    virtual void glUniform3i (int location,int x,int y,int z) const;
    virtual void glUniform3iv (int location,int count,const int* v) const;
    virtual void glUniform4f (int location,float x,float y,float z,float w) const;
    virtual void glUniform4fv (int location,int count,const float* v) const;
    virtual void glUniform4i (int location,int x,int y,int z,int w) const;
    virtual void glUniform4iv (int location,int count,const int* v) const;
    virtual void glUniformMatrix2fv (int location,int count,bool transpose,const float* value) const;
    virtual void glUniformMatrix3fv (int location,int count,bool transpose,const float* value) const;
    virtual void glUniformMatrix4fv (int location,int count,bool transpose,const float* value) const;
    virtual void glUseProgram (int program) const;
    virtual void glValidateProgram (int program) const;
    virtual void glVertexAttrib1f (int indx,float x) const;
    virtual void glVertexAttrib1fv (int indx,const float* values) const;
    virtual void glVertexAttrib2f (int indx,float x,float y) const;
    virtual void glVertexAttrib2fv (int indx,const float* values) const;
    virtual void glVertexAttrib3f (int indx,float x,float y,float z) const;
    virtual void glVertexAttrib3fv (int indx,const float* values) const;
    virtual void glVertexAttrib4f (int indx,float x,float y,float z,float w) const;
    virtual void glVertexAttrib4fv (int indx,const float* values) const;
    virtual void glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,const void* ptr) const;
    virtual void glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,int ptr) const;

protected:


private:

};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GL20_HPP_
