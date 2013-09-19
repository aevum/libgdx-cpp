
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

#include <string>

#include "GLCommon.hpp"

namespace gdx {

class GL20 : virtual public GLCommon {
public:
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
    virtual void glDrawElements (int mode,int count,unsigned int type, const void* indices) const override;
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
