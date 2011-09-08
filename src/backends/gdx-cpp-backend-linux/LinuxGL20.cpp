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

#ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

#else
#include <GLES2/gl2.h>
#endif

using namespace gdx_cpp::backends::nix;

void LinuxGL20::glAttachShader (int program,int shader) const {
    glAttachShader (program,shader);
}
void LinuxGL20::glBindAttribLocation (int program,int index,const std::string& name) const {
    glBindAttribLocation (program, index, name.c_str());
}
void LinuxGL20::glBindBuffer (int target,int buffer) const {
    glBindBuffer (target,buffer);
}
void LinuxGL20::glBindFramebuffer (int target,int framebuffer) const {
    glBindFramebuffer (target,framebuffer);
}
void LinuxGL20::glBindRenderbuffer (int target,int renderbuffer) const {
    glBindRenderbuffer (target,renderbuffer);
}
void LinuxGL20::glBlendColor (float red,float green,float blue,float alpha) const {
    glBlendColor (red,green,blue,alpha);
}
void LinuxGL20::glBlendEquation (int mode) const {
    glBlendEquation (mode);
}
void LinuxGL20::glBlendEquationSeparate (int modeRGB,int modeAlpha) const {
    glBlendEquationSeparate (modeRGB,modeAlpha);
}
void LinuxGL20::glBlendFuncSeparate (int srcRGB,int dstRGB,int srcAlpha,int dstAlpha) const {
    glBlendFuncSeparate (srcRGB,dstRGB,srcAlpha,dstAlpha);
}
void LinuxGL20::glBufferData (int target,int size,const char* data,int usage) const {
    glBufferData (target, size,data,usage);
}
void LinuxGL20::glBufferSubData (int target,int offset,int size,const char* data) const {
    glBufferSubData (target, offset, size,data);
}
int LinuxGL20::glCheckFramebufferStatus (int target) const {
    return glCheckFramebufferStatus (target);
}
void LinuxGL20::glCompileShader (int shader) const {
    glCompileShader (shader);
}

int LinuxGL20::glCreateProgram () const {
    return glCreateProgram();
}

int LinuxGL20::glCreateShader (int type) const {
    return glCreateShader (type);
}
void LinuxGL20::glDeleteBuffers (int n,const int* buffers) const {
    glDeleteBuffers (n, buffers);
}
void LinuxGL20::glDeleteFramebuffers (int n,const int* framebuffers) const {
    glDeleteFramebuffers (n, framebuffers);
}
void LinuxGL20::glDeleteProgram (int program) const {
    glDeleteProgram (program);
}
void LinuxGL20::glDeleteRenderbuffers (int n,const int* renderbuffers) const {
    glDeleteRenderbuffers (n,renderbuffers);
}
void LinuxGL20::glDeleteShader (int shader) const {
    glDeleteShader (shader);
}
void LinuxGL20::glDetachShader (int program,int shader) const {
    glDetachShader (program,shader);
}
void LinuxGL20::glDisableVertexAttribArray (int index) const {
    glDisableVertexAttribArray (index);
}
void LinuxGL20::glDrawElements (int mode,int count,int type,int indices) const {
    glDrawElements (mode,count,type,indices);
}
void LinuxGL20::glEnableVertexAttribArray (int index) const {
    glEnableVertexAttribArray (index);
}
void LinuxGL20::glFramebufferRenderbuffer (int target,int attachment,int renderbuffertarget,int renderbuffer) const {
    glFramebufferRenderbuffer (target,attachment,renderbuffertarget,renderbuffer);
}
void LinuxGL20::glFramebufferTexture2D (int target,int attachment,int textarget,int texture,int level) const {
    glFramebufferTexture2D (target,attachment,textarget,texture,level);
}
void LinuxGL20::glGenBuffers (int n,const int* buffers) const {
    glGenBuffers (n, buffers);
}
void LinuxGL20::glGenerateMipmap (int target) const {
    glGenerateMipmap (target);
}
void LinuxGL20::glGenFramebuffers (int n,const int* framebuffers) const {
    glGenFramebuffers (n,framebuffers);
}
void LinuxGL20::glGenRenderbuffers (int n,const int* renderbuffers) const {
    glGenRenderbuffers (n, renderbuffers);
}
std::string LinuxGL20::glGetActiveAttrib (int program,int index,const int* size,const char* type) const {
    glGetActiveAttrib (program, index, size, type);
}
std::string LinuxGL20::glGetActiveUniform (int program,int index,const int* size,const char* type) const {
    glGetActiveUniform (program, index, size,type);
}
void LinuxGL20::glGetAttachedShaders (int program,int maxcount,const char* count,const int* shaders) const {
    glGetAttachedShaders (program,maxcount,count, shaders);
}
int LinuxGL20::glGetAttribLocation (int program,const std::string& name) const {
    glGetAttribLocation (program, name);
}
void LinuxGL20::glGetBooleanv (int pname,const char* params) const {
    glGetBooleanv (pname, params);
}
void LinuxGL20::glGetBufferParameteriv (int target,int pname,const int* params) const {
    glGetBufferParameteriv (target,pname,params);
}
void LinuxGL20::glGetFloatv (int pname,const float* params) const {
    glGetFloatv (pname,params);
}
void LinuxGL20::glGetFramebufferAttachmentParameteriv (int target,int attachment,int pname,const int* params) const {
    glGetFramebufferAttachmentParameteriv (target,attachment,pname,params);
}
void LinuxGL20::glGetProgramiv (int program,int pname,const int* params) const {
    glGetProgramiv (program,pname,params);
}
std::string& LinuxGL20::glGetProgramInfoLog (int program) const {
    glGetProgramInfoLog (program);
}
void LinuxGL20::glGetRenderbufferParameteriv (int target,int pname,const int* params) const {
    glGetRenderbufferParameteriv (target,pname,params);
}
void LinuxGL20::glGetShaderiv (int shader,int pname,const int* params) const {
    glGetShaderiv (shader,pname, params);
}
std::string& LinuxGL20::glGetShaderInfoLog (int shader) const {
    glGetShaderInfoLog (shader);
}
void LinuxGL20::glGetShaderPrecisionFormat (int shadertype,int precisiontype,const int* range,const int* precision) const {
    glGetShaderPrecisionFormat (shadertype,precisiontype, range, precision);
}
void LinuxGL20::glGetShaderSource (int shader,int bufsize,const char* length,const std::string& source) const {
    glGetShaderSource (shader,bufsize,length, source);
}
void LinuxGL20::glGetTexParameterfv (int target,int pname,const float* params) const {
    glGetTexParameterfv (target,pname, params);
}
void LinuxGL20::glGetTexParameteriv (int target,int pname,const int* params) const {
    glGetTexParameteriv (target,pname, params);
}
void LinuxGL20::glGetUniformfv (int program,int location,const float* params) const {
    glGetUniformfv (program,location, params);
}
void LinuxGL20::glGetUniformiv (int program,int location,const int* params) const {
    glGetUniformiv (program,location, params);
}
int LinuxGL20::glGetUniformLocation (int program,const std::string& name) const {
    glGetUniformLocation (program,name);
}
void LinuxGL20::glGetVertexAttribfv (int index,int pname,const float* params) const {
    glGetVertexAttribfv (index,pname,params);
}
void LinuxGL20::glGetVertexAttribiv (int index,int pname,const int* params) const {
    glGetVertexAttribiv (index,pname,params);
}
void LinuxGL20::glGetVertexAttribPointerv (int index,int pname,const char* pointer) const {
    glGetVertexAttribPointerv (index,pname,pointer);
}
bool LinuxGL20::glIsBuffer (int buffer) const {
    glIsBuffer (buffer);
}
bool LinuxGL20::glIsEnabled (int cap) const {
    glIsEnabled (cap);
}
bool LinuxGL20::glIsFramebuffer (int framebuffer) const {
    glIsFramebuffer (framebuffer);
}
bool LinuxGL20::glIsProgram (int program) const {
    glIsProgram (program);
}
bool LinuxGL20::glIsRenderbuffer (int renderbuffer) const {
    glIsRenderbuffer (renderbuffer);
}
bool LinuxGL20::glIsShader (int shader) const {
    glIsShader (shader);
}
bool LinuxGL20::glIsTexture (int texture) const {
    glIsTexture (texture);
}
void LinuxGL20::glLinkProgram (int program) const {
    glLinkProgram (program);
}
void LinuxGL20::glReleaseShaderCompiler () const {
    glReleaseShaderCompiler();
}

void LinuxGL20::glRenderbufferStorage (int target,int internalformat,int width,int height) const {
    glRenderbufferStorage (target,internalformat,width,height);
}
void LinuxGL20::glSampleCoverage (float value,bool invert) const {
    glSampleCoverage (value,invert);
}
void LinuxGL20::glShaderBinary (int n,const int* shaders,int binaryformat,const char* binary,int length) const {
    glShaderBinary (n, shaders,binaryformat, binary,length);
}
void LinuxGL20::glShaderSource (int shader,const std::string& string) const {
    glShaderSource (shader,string);
}
void LinuxGL20::glStencilFuncSeparate (int face,int func,int ref,int mask) const {
    glStencilFuncSeparate (face, func, ref,mask);
}
void LinuxGL20::glStencilMaskSeparate (int face,int mask) const {
    glStencilMaskSeparate (face,mask);
}
void LinuxGL20::glStencilOpSeparate (int face,int fail,int zfail,int zpass) const {
    glStencilOpSeparate ( face, fail, zfail, zpass);
}
void LinuxGL20::glTexParameterfv (int target,int pname,const float* params) const {
    glTexParameterfv ( target, pname, params);
}
void LinuxGL20::glTexParameteri (int target,int pname,int param) const {
    glTexParameteri (target, pname, param);
}
void LinuxGL20::glTexParameteriv (int target,int pname,const int* params) const {
    glTexParameteriv (target,pname,params);
}
void LinuxGL20::glUniform1f (int location,float x) const {
    glUniform1f (location,x);
}
void LinuxGL20::glUniform1fv (int location,int count,const float* v) const {
    glUniform1fv (location,count,v);
}
void LinuxGL20::glUniform1i (int location,int x) const {
    glUniform1i (location, x);
}
void LinuxGL20::glUniform1iv (int location,int count,const int* v) const {
    glUniform1iv (location, count, v);
}
void LinuxGL20::glUniform2f (int location,float x,float y) const {
    glUniform2f ( location, x,y);
}
void LinuxGL20::glUniform2fv (int location,int count,const float* v) const {
    glUniform2fv (location,count, v);
}
void LinuxGL20::glUniform2i (int location,int x,int y) const {
    glUniform2i (location,x,y);
}
void LinuxGL20::glUniform2iv (int location,int count,const int* v) const {
    glUniform2iv (location,count, v);
}
void LinuxGL20::glUniform3f (int location,float x,float y,float z) const {
    glUniform3f ( location,x,y, z);
}
void LinuxGL20::glUniform3fv (int location,int count,const float* v) const {
    glUniform3fv (location, count, v);
}
void LinuxGL20::glUniform3i (int location,int x,int y,int z) const {
    glUniform3i (location,x,y,z);
}
void LinuxGL20::glUniform3iv (int location,int count,const int* v) const {
    glUniform3iv (location, count, v);
}
void LinuxGL20::glUniform4f (int location,float x,float y,float z,float w) const {
    glUniform4f ( location, x, y, z, w);
}
void LinuxGL20::glUniform4fv (int location,int count,const float* v) const {
    glUniform4fv ( location, count, v);
}
void LinuxGL20::glUniform4i (int location,int x,int y,int z,int w) const {
    glUniform4i (location,x, y, z, w);
}
void LinuxGL20::glUniform4iv (int location,int count,const int* v) const {
    glUniform4iv ( location, count, v);
}
void LinuxGL20::glUniformMatrix2fv (int location,int count,bool transpose,const float* value) const {
    glUniformMatrix2fv ( location, count, transpose,value);
}
void LinuxGL20::glUniformMatrix3fv (int location,int count,bool transpose,const float* value) const {
    glUniformMatrix3fv (location, count, transpose, value);
}
void LinuxGL20::glUniformMatrix4fv (int location,int count,bool transpose,const float* value) const {
    glUniformMatrix4fv ( location, count, transpose, value);
}
void LinuxGL20::glUseProgram (int program) const {
    glUseProgram ( program);
}
void LinuxGL20::glValidateProgram (int program) const {
    glValidateProgram ( program);
}
void LinuxGL20::glVertexAttrib1f (int indx,float x) const {
    glVertexAttrib1f ( indx, x);
}
void LinuxGL20::glVertexAttrib1fv (int indx,const float* values) const {
    glVertexAttrib1fv (indx, values);
}
void LinuxGL20::glVertexAttrib2f (int indx,float x,float y) const {
    glVertexAttrib2f (indx,x,y);
}
void LinuxGL20::glVertexAttrib2fv (int indx,const float* values) const {
    glVertexAttrib2fv (indx,values);
}
void LinuxGL20::glVertexAttrib3f (int indx,float x,float y,float z) const {
    glVertexAttrib3f (indx,x,y,z);
}
void LinuxGL20::glVertexAttrib3fv (int indx,const float* values) const {
    glVertexAttrib3fv (indx, values);
}
void LinuxGL20::glVertexAttrib4f (int indx,float x,float y,float z,float w) const {
    glVertexAttrib4f (indx,x, y, z, w);
}
void LinuxGL20::glVertexAttrib4fv (int indx,const float* values) const {
    glVertexAttrib4fv (indx, values);
}
void LinuxGL20::glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,const void* ptr) const {
    glVertexAttribPointer (indx,size,type,normalized,stride, ptr);
}
void LinuxGL20::glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,int ptr) const {
    glVertexAttribPointer (indx,size,type,normalized,stride,ptr);
}

void LinuxGL20::glActiveTexture (int texture) const {
    ::glActiveTexture ( texture);
}
void LinuxGL20::glBindTexture (int target,int texture) const {
    ::glBindTexture ( target, texture);
}
void LinuxGL20::glBlendFunc (int sfactor,int dfactor) const {
    ::glBlendFunc ( sfactor, dfactor);
}
void LinuxGL20::glClear (int mask) const {
    ::glClear ( mask);
}
void LinuxGL20::glClearColor (float red,float green,float blue,float alpha) const {
    ::glClearColor ( red, green, blue, alpha);
}
void LinuxGL20::glClearDepthf (float depth) const {
    ::glClearDepthf ( depth);
}
void LinuxGL20::glClearStencil (int s) const {
    ::glClearStencil ( s);
}
void LinuxGL20::glColorMask (bool red,bool green,bool blue,bool alpha) const {
    ::glColorMask ( red, green, blue, alpha);
}
void LinuxGL20::glCompressedTexImage2D (int target,int level,int internalformat,int width,int height,int border,int imageSize,const unsigned char* data) const {
    ::glCompressedTexImage2D ( target, level, internalformat, width, height, border, imageSize, data);
}
void LinuxGL20::glCompressedTexSubImage2D (int target,int level,int xoffset,int yoffset,int width,int height,int format,int imageSize,const unsigned char* data) const {
    ::glCompressedTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, imageSize, data);
}
void LinuxGL20::glCopyTexImage2D (int target,int level,int internalformat,int x,int y,int width,int height,int border) const {
    ::glCopyTexImage2D ( target, level, internalformat, x, y, width, height, border);
}
void LinuxGL20::glCopyTexSubImage2D (int target,int level,int xoffset,int yoffset,int x,int y,int width,int height) const {
    ::glCopyTexSubImage2D ( target, level, xoffset, yoffset, x, y, width, height);
}
void LinuxGL20::glCullFace (int mode) const {
    ::glCullFace ( mode);
}
void LinuxGL20::glDeleteTextures (int n, const int* textures) const {
    ::glDeleteTextures ( n, (GLuint*) textures);
}
void LinuxGL20::glDepthFunc (int func) const {
    ::glDepthFunc ( func);
}
void LinuxGL20::glDepthMask (bool flag) const {
    ::glDepthMask ( flag);
}
void LinuxGL20::glDepthRangef (float zNear,float zFar) const {
    ::glDepthRangef ( zNear, zFar);
}
void LinuxGL20::glDisable (int cap) const {
    ::glDisable ( cap);
}
void LinuxGL20::glDrawArrays (int mode,int first,int count) const {
    ::glDrawArrays ( mode, first, count);
}
void LinuxGL20::glDrawElements (int mode,int count,int type, const void* indices) const {
    ::glDrawElements ( mode, count, type, indices);
}
void LinuxGL20::glEnable (int cap) const {
    ::glEnable ( cap);
}
void LinuxGL20::glFinish () const {
    ::glFinish();
}
void LinuxGL20::glFlush () const {
    ::glFlush();
}

void LinuxGL20::glFrontFace (int mode) const {
    ::glFrontFace ( mode);
}
void LinuxGL20::glGenTextures (int n,int* textures) const {
    ::glGenTextures ( n, (GLuint*) textures);
}
int LinuxGL20::glGetError () const {
    return ::glGetError();
}
void LinuxGL20::glGetIntegerv (int pname,const int* params) const {
    ::glGetIntegerv ( pname, (GLint*) params);
}
std::string LinuxGL20::glGetString (int name) const {
    const GLubyte* str = ::glGetString(name);
    return std::string((char*)str);
}
void LinuxGL20::glHint (int target,int mode) const {
    ::glHint ( target, mode);
}
void LinuxGL20::glLineWidth (float width) const {
    ::glLineWidth ( width);
}
void LinuxGL20::glPixelStorei (int pname,int param) const {
    ::glPixelStorei ( pname, param);
}
void LinuxGL20::glPolygonOffset (float factor,float units) const {
    ::glPolygonOffset ( factor, units);
}
void LinuxGL20::glReadPixels (int x,int y,int width,int height,int format,int type,const void* pixels) const {
    ::glReadPixels ( x, y, width, height, format, type, (GLvoid*) pixels);
}
void LinuxGL20::glScissor (int x,int y,int width,int height) const {
    ::glScissor ( x, y, width, height);
}
void LinuxGL20::glStencilFunc (int func,int ref,int mask) const {
    ::glStencilFunc ( func, ref, mask);
}
void LinuxGL20::glStencilMask (int mask) const {
    ::glStencilMask ( mask);
}
void LinuxGL20::glStencilOp (int fail,int zfail,int zpass) const {
    ::glStencilOp ( fail, zfail, zpass);
}
void LinuxGL20::glTexImage2D (int target,int level,int internalformat,int width,int height,int border,int format,int type,const unsigned char* pixels) const {
    ::glTexImage2D ( target, level, internalformat, width, height, border, format, type, pixels);
}
void LinuxGL20::glTexParameterf (int target,int pname,float param) const {
    ::glTexParameterf ( target, pname, param);
}
void LinuxGL20::glTexSubImage2D (int target,int level,int xoffset,int yoffset,int width,int height,int format,int type,const unsigned char* pixels) const {
    ::glTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, type, pixels);
}
void LinuxGL20::glViewport (int x,int y,int width,int height) const {
    ::glViewport ( x, y, width, height);
}
