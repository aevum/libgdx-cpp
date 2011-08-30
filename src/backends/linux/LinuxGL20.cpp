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


#include "LinuxGL20.hpp"

#include <GLES2/gl2.h>

using namespace gdx_cpp::backends::nix;

void LinuxGL20::glAttachShader (int program,int shader) {
    glAttachShader (program,shader);
}
void LinuxGL20::glBindAttribLocation (int program,int index,const std::string& name) {
    glBindAttribLocation (program, index, name.c_str());
}
void LinuxGL20::glBindBuffer (int target,int buffer) {
    glBindBuffer (target,buffer);
}
void LinuxGL20::glBindFramebuffer (int target,int framebuffer) {
    glBindFramebuffer (target,framebuffer);
}
void LinuxGL20::glBindRenderbuffer (int target,int renderbuffer) {
    glBindRenderbuffer (target,renderbuffer);
}
void LinuxGL20::glBlendColor (float red,float green,float blue,float alpha) {
    glBlendColor (red,green,blue,alpha);
}
void LinuxGL20::glBlendEquation (int mode) {
    glBlendEquation (mode);
}
void LinuxGL20::glBlendEquationSeparate (int modeRGB,int modeAlpha) {
    glBlendEquationSeparate (modeRGB,modeAlpha);
}
void LinuxGL20::glBlendFuncSeparate (int srcRGB,int dstRGB,int srcAlpha,int dstAlpha) {
    glBlendFuncSeparate (srcRGB,dstRGB,srcAlpha,dstAlpha);
}
void LinuxGL20::glBufferData (int target,int size,const char* data,int usage) {
    glBufferData (target, size,data,usage);
}
void LinuxGL20::glBufferSubData (int target,int offset,int size,const char* data) {
    glBufferSubData (target, offset, size,data);
}
int LinuxGL20::glCheckFramebufferStatus (int target) {
    return glCheckFramebufferStatus (target);
}
void LinuxGL20::glCompileShader (int shader) {
    glCompileShader (shader);
}

int LinuxGL20::glCreateProgram () {
    return glCreateProgram();
}

int LinuxGL20::glCreateShader (int type) {
    return glCreateShader (type);
}
void LinuxGL20::glDeleteBuffers (int n,const int* buffers) {
    glDeleteBuffers (n, buffers);
}
void LinuxGL20::glDeleteFramebuffers (int n,const int* framebuffers) {
    glDeleteFramebuffers (n, framebuffers);
}
void LinuxGL20::glDeleteProgram (int program) {
    glDeleteProgram (program);
}
void LinuxGL20::glDeleteRenderbuffers (int n,const int* renderbuffers) {
    glDeleteRenderbuffers (n,renderbuffers);
}
void LinuxGL20::glDeleteShader (int shader) {
    glDeleteShader (shader);
}
void LinuxGL20::glDetachShader (int program,int shader) {
    glDetachShader (program,shader);
}
void LinuxGL20::glDisableVertexAttribArray (int index) {
    glDisableVertexAttribArray (index);
}
void LinuxGL20::glDrawElements (int mode,int count,int type,int indices) {
    glDrawElements (mode,count,type,indices);
}
void LinuxGL20::glEnableVertexAttribArray (int index) {
    glEnableVertexAttribArray (index);
}
void LinuxGL20::glFramebufferRenderbuffer (int target,int attachment,int renderbuffertarget,int renderbuffer) {
    glFramebufferRenderbuffer (target,attachment,renderbuffertarget,renderbuffer);
}
void LinuxGL20::glFramebufferTexture2D (int target,int attachment,int textarget,int texture,int level) {
    glFramebufferTexture2D (target,attachment,textarget,texture,level);
}
void LinuxGL20::glGenBuffers (int n,const int* buffers) {
    glGenBuffers (n, buffers);
}
void LinuxGL20::glGenerateMipmap (int target) {
    glGenerateMipmap (target);
}
void LinuxGL20::glGenFramebuffers (int n,const int* framebuffers) {
    glGenFramebuffers (n,framebuffers);
}
void LinuxGL20::glGenRenderbuffers (int n,const int* renderbuffers) {
    glGenRenderbuffers (n, renderbuffers);
}
std::string LinuxGL20::glGetActiveAttrib (int program,int index,const int* size,const char* type) {
    glGetActiveAttrib (program, index, size, type);
}
std::string LinuxGL20::glGetActiveUniform (int program,int index,const int* size,const char* type) {
    glGetActiveUniform (program, index, size,type);
}
void LinuxGL20::glGetAttachedShaders (int program,int maxcount,const char* count,const int* shaders) {
    glGetAttachedShaders (program,maxcount,count, shaders);
}
int LinuxGL20::glGetAttribLocation (int program,const std::string& name) {
    glGetAttribLocation (program, name);
}
void LinuxGL20::glGetBooleanv (int pname,const char* params) {
    glGetBooleanv (pname, params);
}
void LinuxGL20::glGetBufferParameteriv (int target,int pname,const int* params) {
    glGetBufferParameteriv (target,pname,params);
}
void LinuxGL20::glGetFloatv (int pname,const float* params) {
    glGetFloatv (pname,params);
}
void LinuxGL20::glGetFramebufferAttachmentParameteriv (int target,int attachment,int pname,const int* params) {
    glGetFramebufferAttachmentParameteriv (target,attachment,pname,params);
}
void LinuxGL20::glGetProgramiv (int program,int pname,const int* params) {
    glGetProgramiv (program,pname,params);
}
std::string& LinuxGL20::glGetProgramInfoLog (int program) {
    glGetProgramInfoLog (program);
}
void LinuxGL20::glGetRenderbufferParameteriv (int target,int pname,const int* params) {
    glGetRenderbufferParameteriv (target,pname,params);
}
void LinuxGL20::glGetShaderiv (int shader,int pname,const int* params) {
    glGetShaderiv (shader,pname, params);
}
std::string& LinuxGL20::glGetShaderInfoLog (int shader) {
    glGetShaderInfoLog (shader);
}
void LinuxGL20::glGetShaderPrecisionFormat (int shadertype,int precisiontype,const int* range,const int* precision) {
    glGetShaderPrecisionFormat (shadertype,precisiontype, range, precision);
}
void LinuxGL20::glGetShaderSource (int shader,int bufsize,const char* length,const std::string& source) {
    glGetShaderSource (shader,bufsize,length, source);
}
void LinuxGL20::glGetTexParameterfv (int target,int pname,const float* params) {
    glGetTexParameterfv (target,pname, params);
}
void LinuxGL20::glGetTexParameteriv (int target,int pname,const int* params) {
    glGetTexParameteriv (target,pname, params);
}
void LinuxGL20::glGetUniformfv (int program,int location,const float* params) {
    glGetUniformfv (program,location, params);
}
void LinuxGL20::glGetUniformiv (int program,int location,const int* params) {
    glGetUniformiv (program,location, params);
}
int LinuxGL20::glGetUniformLocation (int program,const std::string& name) {
    glGetUniformLocation (program,name);
}
void LinuxGL20::glGetVertexAttribfv (int index,int pname,const float* params) {
    glGetVertexAttribfv (index,pname,params);
}
void LinuxGL20::glGetVertexAttribiv (int index,int pname,const int* params) {
    glGetVertexAttribiv (index,pname,params);
}
void LinuxGL20::glGetVertexAttribPointerv (int index,int pname,const char* pointer) {
    glGetVertexAttribPointerv (index,pname,pointer);
}
bool LinuxGL20::glIsBuffer (int buffer) {
    glIsBuffer (buffer);
}
bool LinuxGL20::glIsEnabled (int cap) {
    glIsEnabled (cap);
}
bool LinuxGL20::glIsFramebuffer (int framebuffer) {
    glIsFramebuffer (framebuffer);
}
bool LinuxGL20::glIsProgram (int program) {
    glIsProgram (program);
}
bool LinuxGL20::glIsRenderbuffer (int renderbuffer) {
    glIsRenderbuffer (renderbuffer);
}
bool LinuxGL20::glIsShader (int shader) {
    glIsShader (shader);
}
bool LinuxGL20::glIsTexture (int texture) {
    glIsTexture (texture);
}
void LinuxGL20::glLinkProgram (int program) {
    glLinkProgram (program);
}
void LinuxGL20::glReleaseShaderCompiler () {
    glReleaseShaderCompiler();
}

void LinuxGL20::glRenderbufferStorage (int target,int internalformat,int width,int height) {
    glRenderbufferStorage (target,internalformat,width,height);
}
void LinuxGL20::glSampleCoverage (float value,bool invert) {
    glSampleCoverage (value,invert);
}
void LinuxGL20::glShaderBinary (int n,const int* shaders,int binaryformat,const char* binary,int length) {
    glShaderBinary (n, shaders,binaryformat, binary,length);
}
void LinuxGL20::glShaderSource (int shader,const std::string& string) {
    glShaderSource (shader,string);
}
void LinuxGL20::glStencilFuncSeparate (int face,int func,int ref,int mask) {
    glStencilFuncSeparate (face, func, ref,mask);
}
void LinuxGL20::glStencilMaskSeparate (int face,int mask) {
    glStencilMaskSeparate (face,mask);
}
void LinuxGL20::glStencilOpSeparate (int face,int fail,int zfail,int zpass) {
    glStencilOpSeparate ( face, fail, zfail, zpass);
}
void LinuxGL20::glTexParameterfv (int target,int pname,const float* params) {
    glTexParameterfv ( target, pname, params);
}
void LinuxGL20::glTexParameteri (int target,int pname,int param) {
    glTexParameteri (target, pname, param);
}
void LinuxGL20::glTexParameteriv (int target,int pname,const int* params) {
    glTexParameteriv (target,pname,params);
}
void LinuxGL20::glUniform1f (int location,float x) {
    glUniform1f (location,x);
}
void LinuxGL20::glUniform1fv (int location,int count,const float* v) {
    glUniform1fv (location,count,v);
}
void LinuxGL20::glUniform1i (int location,int x) {
    glUniform1i (location, x);
}
void LinuxGL20::glUniform1iv (int location,int count,const int* v) {
    glUniform1iv (location, count, v);
}
void LinuxGL20::glUniform2f (int location,float x,float y) {
    glUniform2f ( location, x,y);
}
void LinuxGL20::glUniform2fv (int location,int count,const float* v) {
    glUniform2fv (location,count, v);
}
void LinuxGL20::glUniform2i (int location,int x,int y) {
    glUniform2i (location,x,y);
}
void LinuxGL20::glUniform2iv (int location,int count,const int* v) {
    glUniform2iv (location,count, v);
}
void LinuxGL20::glUniform3f (int location,float x,float y,float z) {
    glUniform3f ( location,x,y, z);
}
void LinuxGL20::glUniform3fv (int location,int count,const float* v) {
    glUniform3fv (location, count, v);
}
void LinuxGL20::glUniform3i (int location,int x,int y,int z) {
    glUniform3i (location,x,y,z);
}
void LinuxGL20::glUniform3iv (int location,int count,const int* v) {
    glUniform3iv (location, count, v);
}
void LinuxGL20::glUniform4f (int location,float x,float y,float z,float w) {
    glUniform4f ( location, x, y, z, w);
}
void LinuxGL20::glUniform4fv (int location,int count,const float* v) {
    glUniform4fv ( location, count, v);
}
void LinuxGL20::glUniform4i (int location,int x,int y,int z,int w) {
    glUniform4i (location,x, y, z, w);
}
void LinuxGL20::glUniform4iv (int location,int count,const int* v) {
    glUniform4iv ( location, count, v);
}
void LinuxGL20::glUniformMatrix2fv (int location,int count,bool transpose,const float* value) {
    glUniformMatrix2fv ( location, count, transpose,value);
}
void LinuxGL20::glUniformMatrix3fv (int location,int count,bool transpose,const float* value) {
    glUniformMatrix3fv (location, count, transpose, value);
}
void LinuxGL20::glUniformMatrix4fv (int location,int count,bool transpose,const float* value) {
    glUniformMatrix4fv ( location, count, transpose, value);
}
void LinuxGL20::glUseProgram (int program) {
    glUseProgram ( program);
}
void LinuxGL20::glValidateProgram (int program) {
    glValidateProgram ( program);
}
void LinuxGL20::glVertexAttrib1f (int indx,float x) {
    glVertexAttrib1f ( indx, x);
}
void LinuxGL20::glVertexAttrib1fv (int indx,const float* values) {
    glVertexAttrib1fv (indx, values);
}
void LinuxGL20::glVertexAttrib2f (int indx,float x,float y) {
    glVertexAttrib2f (indx,x,y);
}
void LinuxGL20::glVertexAttrib2fv (int indx,const float* values) {
    glVertexAttrib2fv (indx,values);
}
void LinuxGL20::glVertexAttrib3f (int indx,float x,float y,float z) {
    glVertexAttrib3f (indx,x,y,z);
}
void LinuxGL20::glVertexAttrib3fv (int indx,const float* values) {
    glVertexAttrib3fv (indx, values);
}
void LinuxGL20::glVertexAttrib4f (int indx,float x,float y,float z,float w) {
    glVertexAttrib4f (indx,x, y, z, w);
}
void LinuxGL20::glVertexAttrib4fv (int indx,const float* values) {
    glVertexAttrib4fv (indx, values);
}
void LinuxGL20::glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,const void* ptr) {
    glVertexAttribPointer (indx,size,type,normalized,stride, ptr);
}
void LinuxGL20::glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,int ptr) {
    glVertexAttribPointer (indx,size,type,normalized,stride,ptr);
}

