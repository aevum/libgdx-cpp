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


#include "AndroidGL20.hpp"

#include <GLES2/gl2.h>

using namespace gdx_cpp::backends::nix;

void AndroidGL20::glAttachShader (int program,int shader) const {
    glAttachShader (program,shader);
}
void AndroidGL20::glBindAttribLocation (int program,int index,const std::string& name) const {
    glBindAttribLocation (program, index, name.c_str());
}
void AndroidGL20::glBindBuffer (int target,int buffer) const {
    glBindBuffer (target,buffer);
}
void AndroidGL20::glBindFramebuffer (int target,int framebuffer) const {
    glBindFramebuffer (target,framebuffer);
}
void AndroidGL20::glBindRenderbuffer (int target,int renderbuffer) const {
    glBindRenderbuffer (target,renderbuffer);
}
void AndroidGL20::glBlendColor (float red,float green,float blue,float alpha) const {
    glBlendColor (red,green,blue,alpha);
}
void AndroidGL20::glBlendEquation (int mode) const {
    glBlendEquation (mode);
}
void AndroidGL20::glBlendEquationSeparate (int modeRGB,int modeAlpha) const {
    glBlendEquationSeparate (modeRGB,modeAlpha);
}
void AndroidGL20::glBlendFuncSeparate (int srcRGB,int dstRGB,int srcAlpha,int dstAlpha) const {
    glBlendFuncSeparate (srcRGB,dstRGB,srcAlpha,dstAlpha);
}
void AndroidGL20::glBufferData (int target,int size,const char* data,int usage) const {
    glBufferData (target, size,data,usage);
}
void AndroidGL20::glBufferSubData (int target,int offset,int size,const char* data) const {
    glBufferSubData (target, offset, size,data);
}
int AndroidGL20::glCheckFramebufferStatus (int target) const {
    return glCheckFramebufferStatus (target);
}
void AndroidGL20::glCompileShader (int shader) const {
    glCompileShader (shader);
}

int AndroidGL20::glCreateProgram () const {
    return glCreateProgram();
}

int AndroidGL20::glCreateShader (int type) const {
    return glCreateShader (type);
}
void AndroidGL20::glDeleteBuffers (int n,const int* buffers) const {
    glDeleteBuffers (n, buffers);
}
void AndroidGL20::glDeleteFramebuffers (int n,const int* framebuffers) const {
    glDeleteFramebuffers (n, framebuffers);
}
void AndroidGL20::glDeleteProgram (int program) const {
    glDeleteProgram (program);
}
void AndroidGL20::glDeleteRenderbuffers (int n,const int* renderbuffers) const {
    glDeleteRenderbuffers (n,renderbuffers);
}
void AndroidGL20::glDeleteShader (int shader) const {
    glDeleteShader (shader);
}
void AndroidGL20::glDetachShader (int program,int shader) const {
    glDetachShader (program,shader);
}
void AndroidGL20::glDisableVertexAttribArray (int index) const {
    glDisableVertexAttribArray (index);
}
void AndroidGL20::glDrawElements (int mode,int count,int type,int indices) const {
    glDrawElements (mode,count,type,indices);
}
void AndroidGL20::glEnableVertexAttribArray (int index) const {
    glEnableVertexAttribArray (index);
}
void AndroidGL20::glFramebufferRenderbuffer (int target,int attachment,int renderbuffertarget,int renderbuffer) const {
    glFramebufferRenderbuffer (target,attachment,renderbuffertarget,renderbuffer);
}
void AndroidGL20::glFramebufferTexture2D (int target,int attachment,int textarget,int texture,int level) const {
    glFramebufferTexture2D (target,attachment,textarget,texture,level);
}
void AndroidGL20::glGenBuffers (int n,const int* buffers) const {
    glGenBuffers (n, buffers);
}
void AndroidGL20::glGenerateMipmap (int target) const {
    glGenerateMipmap (target);
}
void AndroidGL20::glGenFramebuffers (int n,const int* framebuffers) const {
    glGenFramebuffers (n,framebuffers);
}
void AndroidGL20::glGenRenderbuffers (int n,const int* renderbuffers) const {
    glGenRenderbuffers (n, renderbuffers);
}
std::string AndroidGL20::glGetActiveAttrib (int program,int index,const int* size,const char* type) const {
    glGetActiveAttrib (program, index, size, type);
}
std::string AndroidGL20::glGetActiveUniform (int program,int index,const int* size,const char* type) const {
    glGetActiveUniform (program, index, size,type);
}
void AndroidGL20::glGetAttachedShaders (int program,int maxcount,const char* count,const int* shaders) const {
    glGetAttachedShaders (program,maxcount,count, shaders);
}
int AndroidGL20::glGetAttribLocation (int program,const std::string& name) const {
    glGetAttribLocation (program, name);
}
void AndroidGL20::glGetBooleanv (int pname,const char* params) const {
    glGetBooleanv (pname, params);
}
void AndroidGL20::glGetBufferParameteriv (int target,int pname,const int* params) const {
    glGetBufferParameteriv (target,pname,params);
}
void AndroidGL20::glGetFloatv (int pname,const float* params) const {
    glGetFloatv (pname,params);
}
void AndroidGL20::glGetFramebufferAttachmentParameteriv (int target,int attachment,int pname,const int* params) const {
    glGetFramebufferAttachmentParameteriv (target,attachment,pname,params);
}
void AndroidGL20::glGetProgramiv (int program,int pname,const int* params) const {
    glGetProgramiv (program,pname,params);
}
std::string& AndroidGL20::glGetProgramInfoLog (int program) const {
    glGetProgramInfoLog (program);
}
void AndroidGL20::glGetRenderbufferParameteriv (int target,int pname,const int* params) const {
    glGetRenderbufferParameteriv (target,pname,params);
}
void AndroidGL20::glGetShaderiv (int shader,int pname,const int* params) const {
    glGetShaderiv (shader,pname, params);
}
std::string& AndroidGL20::glGetShaderInfoLog (int shader) const {
    glGetShaderInfoLog (shader);
}
void AndroidGL20::glGetShaderPrecisionFormat (int shadertype,int precisiontype,const int* range,const int* precision) const {
    glGetShaderPrecisionFormat (shadertype,precisiontype, range, precision);
}
void AndroidGL20::glGetShaderSource (int shader,int bufsize,const char* length,const std::string& source) const {
    glGetShaderSource (shader,bufsize,length, source);
}
void AndroidGL20::glGetTexParameterfv (int target,int pname,const float* params) const {
    glGetTexParameterfv (target,pname, params);
}
void AndroidGL20::glGetTexParameteriv (int target,int pname,const int* params) const {
    glGetTexParameteriv (target,pname, params);
}
void AndroidGL20::glGetUniformfv (int program,int location,const float* params) const {
    glGetUniformfv (program,location, params);
}
void AndroidGL20::glGetUniformiv (int program,int location,const int* params) const {
    glGetUniformiv (program,location, params);
}
int AndroidGL20::glGetUniformLocation (int program,const std::string& name) const {
    glGetUniformLocation (program,name);
}
void AndroidGL20::glGetVertexAttribfv (int index,int pname,const float* params) const {
    glGetVertexAttribfv (index,pname,params);
}
void AndroidGL20::glGetVertexAttribiv (int index,int pname,const int* params) const {
    glGetVertexAttribiv (index,pname,params);
}
void AndroidGL20::glGetVertexAttribPointerv (int index,int pname,const char* pointer) const {
    glGetVertexAttribPointerv (index,pname,pointer);
}
bool AndroidGL20::glIsBuffer (int buffer) const {
    glIsBuffer (buffer);
}
bool AndroidGL20::glIsEnabled (int cap) const {
    glIsEnabled (cap);
}
bool AndroidGL20::glIsFramebuffer (int framebuffer) const {
    glIsFramebuffer (framebuffer);
}
bool AndroidGL20::glIsProgram (int program) const {
    glIsProgram (program);
}
bool AndroidGL20::glIsRenderbuffer (int renderbuffer) const {
    glIsRenderbuffer (renderbuffer);
}
bool AndroidGL20::glIsShader (int shader) const {
    glIsShader (shader);
}
bool AndroidGL20::glIsTexture (int texture) const {
    glIsTexture (texture);
}
void AndroidGL20::glLinkProgram (int program) const {
    glLinkProgram (program);
}
void AndroidGL20::glReleaseShaderCompiler () const {
    glReleaseShaderCompiler();
}

void AndroidGL20::glRenderbufferStorage (int target,int internalformat,int width,int height) const {
    glRenderbufferStorage (target,internalformat,width,height);
}
void AndroidGL20::glSampleCoverage (float value,bool invert) const {
    glSampleCoverage (value,invert);
}
void AndroidGL20::glShaderBinary (int n,const int* shaders,int binaryformat,const char* binary,int length) const {
    glShaderBinary (n, shaders,binaryformat, binary,length);
}
void AndroidGL20::glShaderSource (int shader,const std::string& string) const {
    glShaderSource (shader,string);
}
void AndroidGL20::glStencilFuncSeparate (int face,int func,int ref,int mask) const {
    glStencilFuncSeparate (face, func, ref,mask);
}
void AndroidGL20::glStencilMaskSeparate (int face,int mask) const {
    glStencilMaskSeparate (face,mask);
}
void AndroidGL20::glStencilOpSeparate (int face,int fail,int zfail,int zpass) const {
    glStencilOpSeparate ( face, fail, zfail, zpass);
}
void AndroidGL20::glTexParameterfv (int target,int pname,const float* params) const {
    glTexParameterfv ( target, pname, params);
}
void AndroidGL20::glTexParameteri (int target,int pname,int param) const {
    glTexParameteri (target, pname, param);
}
void AndroidGL20::glTexParameteriv (int target,int pname,const int* params) const {
    glTexParameteriv (target,pname,params);
}
void AndroidGL20::glUniform1f (int location,float x) const {
    glUniform1f (location,x);
}
void AndroidGL20::glUniform1fv (int location,int count,const float* v) const {
    glUniform1fv (location,count,v);
}
void AndroidGL20::glUniform1i (int location,int x) const {
    glUniform1i (location, x);
}
void AndroidGL20::glUniform1iv (int location,int count,const int* v) const {
    glUniform1iv (location, count, v);
}
void AndroidGL20::glUniform2f (int location,float x,float y) const {
    glUniform2f ( location, x,y);
}
void AndroidGL20::glUniform2fv (int location,int count,const float* v) const {
    glUniform2fv (location,count, v);
}
void AndroidGL20::glUniform2i (int location,int x,int y) const {
    glUniform2i (location,x,y);
}
void AndroidGL20::glUniform2iv (int location,int count,const int* v) const {
    glUniform2iv (location,count, v);
}
void AndroidGL20::glUniform3f (int location,float x,float y,float z) const {
    glUniform3f ( location,x,y, z);
}
void AndroidGL20::glUniform3fv (int location,int count,const float* v) const {
    glUniform3fv (location, count, v);
}
void AndroidGL20::glUniform3i (int location,int x,int y,int z) const {
    glUniform3i (location,x,y,z);
}
void AndroidGL20::glUniform3iv (int location,int count,const int* v) const {
    glUniform3iv (location, count, v);
}
void AndroidGL20::glUniform4f (int location,float x,float y,float z,float w) const {
    glUniform4f ( location, x, y, z, w);
}
void AndroidGL20::glUniform4fv (int location,int count,const float* v) const {
    glUniform4fv ( location, count, v);
}
void AndroidGL20::glUniform4i (int location,int x,int y,int z,int w) const {
    glUniform4i (location,x, y, z, w);
}
void AndroidGL20::glUniform4iv (int location,int count,const int* v) const {
    glUniform4iv ( location, count, v);
}
void AndroidGL20::glUniformMatrix2fv (int location,int count,bool transpose,const float* value) const {
    glUniformMatrix2fv ( location, count, transpose,value);
}
void AndroidGL20::glUniformMatrix3fv (int location,int count,bool transpose,const float* value) const {
    glUniformMatrix3fv (location, count, transpose, value);
}
void AndroidGL20::glUniformMatrix4fv (int location,int count,bool transpose,const float* value) const {
    glUniformMatrix4fv ( location, count, transpose, value);
}
void AndroidGL20::glUseProgram (int program) const {
    glUseProgram ( program);
}
void AndroidGL20::glValidateProgram (int program) const {
    glValidateProgram ( program);
}
void AndroidGL20::glVertexAttrib1f (int indx,float x) const {
    glVertexAttrib1f ( indx, x);
}
void AndroidGL20::glVertexAttrib1fv (int indx,const float* values) const {
    glVertexAttrib1fv (indx, values);
}
void AndroidGL20::glVertexAttrib2f (int indx,float x,float y) const {
    glVertexAttrib2f (indx,x,y);
}
void AndroidGL20::glVertexAttrib2fv (int indx,const float* values) const {
    glVertexAttrib2fv (indx,values);
}
void AndroidGL20::glVertexAttrib3f (int indx,float x,float y,float z) const {
    glVertexAttrib3f (indx,x,y,z);
}
void AndroidGL20::glVertexAttrib3fv (int indx,const float* values) const {
    glVertexAttrib3fv (indx, values);
}
void AndroidGL20::glVertexAttrib4f (int indx,float x,float y,float z,float w) const {
    glVertexAttrib4f (indx,x, y, z, w);
}
void AndroidGL20::glVertexAttrib4fv (int indx,const float* values) const {
    glVertexAttrib4fv (indx, values);
}
void AndroidGL20::glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,const void* ptr) const {
    glVertexAttribPointer (indx,size,type,normalized,stride, ptr);
}
void AndroidGL20::glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,int ptr) const {
    glVertexAttribPointer (indx,size,type,normalized,stride,ptr);
}

