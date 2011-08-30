/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#ifndef GDX_CPP_BACKENDS_NIX_LINUXGL20_HPP
#define GDX_CPP_BACKENDS_NIX_LINUXGL20_HPP

#include <gdx-cpp/graphics/GL20.hpp>

namespace gdx_cpp {

namespace backends {

namespace nix {

class LinuxGL20 : public graphics::GL20
{
public:
     void glAttachShader (int program,int shader);
     void glBindAttribLocation (int program,int index,const std::string& name);
     void glBindBuffer (int target,int buffer);
     void glBindFramebuffer (int target,int framebuffer);
     void glBindRenderbuffer (int target,int renderbuffer);
     void glBlendColor (float red,float green,float blue,float alpha);
     void glBlendEquation (int mode);
     void glBlendEquationSeparate (int modeRGB,int modeAlpha);
     void glBlendFuncSeparate (int srcRGB,int dstRGB,int srcAlpha,int dstAlpha);
     void glBufferData (int target,int size,const char* data,int usage);
     void glBufferSubData (int target,int offset,int size,const char* data);
     int glCheckFramebufferStatus (int target);
     void glCompileShader (int shader);
     int glCreateProgram ();
     int glCreateShader (int type);
     void glDeleteBuffers (int n,const int* buffers);
     void glDeleteFramebuffers (int n,const int* framebuffers);
     void glDeleteProgram (int program);
     void glDeleteRenderbuffers (int n,const int* renderbuffers);
     void glDeleteShader (int shader);
     void glDetachShader (int program,int shader);
     void glDisableVertexAttribArray (int index);
     void glDrawElements (int mode,int count,int type,int indices);
     void glEnableVertexAttribArray (int index);
     void glFramebufferRenderbuffer (int target,int attachment,int renderbuffertarget,int renderbuffer);
     void glFramebufferTexture2D (int target,int attachment,int textarget,int texture,int level);
     void glGenBuffers (int n,const int* buffers);
     void glGenerateMipmap (int target);
     void glGenFramebuffers (int n,const int* framebuffers);
     void glGenRenderbuffers (int n,const int* renderbuffers);
       std::string glGetActiveAttrib (int program,int index,const int* size,const char* type);
       std::string glGetActiveUniform (int program,int index,const int* size,const char* type);
     void glGetAttachedShaders (int program,int maxcount,const char* count,const int* shaders);
       int glGetAttribLocation (int program,const std::string& name);
     void glGetBooleanv (int pname,const char* params);
     void glGetBufferParameteriv (int target,int pname,const int* params);
     void glGetFloatv (int pname,const float* params);
     void glGetFramebufferAttachmentParameteriv (int target,int attachment,int pname,const int* params);
     void glGetProgramiv (int program,int pname,const int* params);
       std::string& glGetProgramInfoLog (int program);
     void glGetRenderbufferParameteriv (int target,int pname,const int* params);
     void glGetShaderiv (int shader,int pname,const int* params);
       std::string& glGetShaderInfoLog (int shader);
     void glGetShaderPrecisionFormat (int shadertype,int precisiontype,const int* range,const int* precision);
     void glGetShaderSource (int shader,int bufsize,const char* length,const std::string& source);
     void glGetTexParameterfv (int target,int pname,const float* params);
     void glGetTexParameteriv (int target,int pname,const int* params);
     void glGetUniformfv (int program,int location,const float* params);
     void glGetUniformiv (int program,int location,const int* params);
       int glGetUniformLocation (int program,const std::string& name);
     void glGetVertexAttribfv (int index,int pname,const float* params);
     void glGetVertexAttribiv (int index,int pname,const int* params);
     void glGetVertexAttribPointerv (int index,int pname,const char* pointer);
       bool glIsBuffer (int buffer);
       bool glIsEnabled (int cap);
       bool glIsFramebuffer (int framebuffer);
       bool glIsProgram (int program);
       bool glIsRenderbuffer (int renderbuffer);
       bool glIsShader (int shader);
       bool glIsTexture (int texture);
     void glLinkProgram (int program);
     void glReleaseShaderCompiler ();
     void glRenderbufferStorage (int target,int internalformat,int width,int height);
     void glSampleCoverage (float value,bool invert);
     void glShaderBinary (int n,const int* shaders,int binaryformat,const char* binary,int length);
     void glShaderSource (int shader,const std::string& string);
     void glStencilFuncSeparate (int face,int func,int ref,int mask);
     void glStencilMaskSeparate (int face,int mask);
     void glStencilOpSeparate (int face,int fail,int zfail,int zpass);
     void glTexParameterfv (int target,int pname,const float* params);
     void glTexParameteri (int target,int pname,int param);
     void glTexParameteriv (int target,int pname,const int* params);
     void glUniform1f (int location,float x);
     void glUniform1fv (int location,int count,const float* v);
     void glUniform1i (int location,int x);
     void glUniform1iv (int location,int count,const int* v);
     void glUniform2f (int location,float x,float y);
     void glUniform2fv (int location,int count,const float* v);
     void glUniform2i (int location,int x,int y);
     void glUniform2iv (int location,int count,const int* v);
     void glUniform3f (int location,float x,float y,float z);
     void glUniform3fv (int location,int count,const float* v);
     void glUniform3i (int location,int x,int y,int z);
     void glUniform3iv (int location,int count,const int* v);
     void glUniform4f (int location,float x,float y,float z,float w);
     void glUniform4fv (int location,int count,const float* v);
     void glUniform4i (int location,int x,int y,int z,int w);
     void glUniform4iv (int location,int count,const int* v);
     void glUniformMatrix2fv (int location,int count,bool transpose,const float* value);
     void glUniformMatrix3fv (int location,int count,bool transpose,const float* value);
     void glUniformMatrix4fv (int location,int count,bool transpose,const float* value);
     void glUseProgram (int program);
     void glValidateProgram (int program);
     void glVertexAttrib1f (int indx,float x);
     void glVertexAttrib1fv (int indx,const float* values);
     void glVertexAttrib2f (int indx,float x,float y);
     void glVertexAttrib2fv (int indx,const float* values);
     void glVertexAttrib3f (int indx,float x,float y,float z);
     void glVertexAttrib3fv (int indx,const float* values);
     void glVertexAttrib4f (int indx,float x,float y,float z,float w);
     void glVertexAttrib4fv (int indx,const float* values);
     void glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,const void* ptr);
     void glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,int ptr);
};

}

}

}

#endif // GDX_CPP_BACKENDS_NIX_LINUXGL20_HPP
