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


#include "IosGL20.hpp"

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

using namespace gdx_cpp::backends::ios;

void IosGL20::glAttachShader (int program,int shader) const {
    ::glAttachShader (program,shader);
}
void IosGL20::glBindAttribLocation (int program,int index,const std::string& name) const {
    ::glBindAttribLocation (program, index, name.c_str());
}
void IosGL20::glBindBuffer (int target,int buffer) const {
    ::glBindBuffer (target,buffer);
}
void IosGL20::glBindFramebuffer (int target,int framebuffer) const {
    ::glBindFramebuffer (target,framebuffer);
}
void IosGL20::glBindRenderbuffer (int target,int renderbuffer) const {
    ::glBindRenderbuffer (target,renderbuffer);
}
void IosGL20::glBlendColor (float red,float green,float blue,float alpha) const {
    ::glBlendColor (red,green,blue,alpha);
}
void IosGL20::glBlendEquation (int mode) const {
    ::glBlendEquation (mode);
}
void IosGL20::glBlendEquationSeparate (int modeRGB,int modeAlpha) const {
    ::glBlendEquationSeparate (modeRGB,modeAlpha);
}
void IosGL20::glBlendFuncSeparate (int srcRGB,int dstRGB,int srcAlpha,int dstAlpha) const {
    ::glBlendFuncSeparate (srcRGB,dstRGB,srcAlpha,dstAlpha);
}
void IosGL20::glBufferData (int target,int size,const char* data,int usage) const {
    ::glBufferData (target, size,data,usage);
}
void IosGL20::glBufferSubData (int target,int offset,int size,const char* data) const {
    ::glBufferSubData (target, offset, size,data);
}
int IosGL20::glCheckFramebufferStatus (int target) const {
    return ::glCheckFramebufferStatus (target);
}
void IosGL20::glCompileShader (int shader) const {
    ::glCompileShader (shader);
}

int IosGL20::glCreateProgram () const {
    return ::glCreateProgram();
}

int IosGL20::glCreateShader (int type) const {
    return ::glCreateShader (type);
}
void IosGL20::glDeleteBuffers (int n,const int* buffers) const {
    ::glDeleteBuffers (n, (const GLuint*) buffers);
}
void IosGL20::glDeleteFramebuffers (int n,const int* framebuffers) const {
    ::glDeleteFramebuffers (n, (const GLuint*) framebuffers);
}
void IosGL20::glDeleteProgram (int program) const {
    ::glDeleteProgram (program);
}
void IosGL20::glDeleteRenderbuffers (int n,const int* renderbuffers) const {
    ::glDeleteRenderbuffers (n, (const GLuint*)renderbuffers);
}
void IosGL20::glDeleteShader (int shader) const {
    ::glDeleteShader (shader);
}
void IosGL20::glDetachShader (int program,int shader) const {
    ::glDetachShader (program,shader);
}
void IosGL20::glDisableVertexAttribArray (int index) const {
    ::glDisableVertexAttribArray (index);
}
void IosGL20::glDrawElements (int mode,int count,int type,int indices) const {
    ::glDrawElements (mode,count,type,&indices);
}
void IosGL20::glEnableVertexAttribArray (int index) const {
    ::glEnableVertexAttribArray (index);
}
void IosGL20::glFramebufferRenderbuffer (int target,int attachment,int renderbuffertarget,int renderbuffer) const {
    ::glFramebufferRenderbuffer (target,attachment,renderbuffertarget,renderbuffer);
}
void IosGL20::glFramebufferTexture2D (int target,int attachment,int textarget,int texture,int level) const {
    ::glFramebufferTexture2D (target,attachment,textarget,texture,level);
}
void IosGL20::glGenBuffers (int n,const int* buffers) const {
    ::glGenBuffers (n, (GLuint*) buffers);
}
void IosGL20::glGenerateMipmap (int target) const {
    ::glGenerateMipmap (target);
}
void IosGL20::glGenFramebuffers (int n,const int* framebuffers) const {
    ::glGenFramebuffers (n, (GLuint *) framebuffers);
}
void IosGL20::glGenRenderbuffers (int n,const int* renderbuffers) const {
    ::glGenRenderbuffers (n, (GLuint *) renderbuffers);
}
std::string IosGL20::glGetActiveAttrib (int program,int index,const int* size,const char* type) const {
    GLsizei length = 0;
    GLchar buffer[2048];
    
    ::glGetActiveAttrib (program, index, 2048, &length, (GLint*) size, (GLenum*) type, buffer);

    return buffer;
}
std::string IosGL20::glGetActiveUniform (int program,int index,const int* size,const char* type) const {
    GLsizei length = 0;
    GLchar buffer[2048];
    
    ::glGetActiveUniform (program, index, 2048, &length, (GLint*) size,(GLenum*) type, buffer);

    return buffer;
}
void IosGL20::glGetAttachedShaders (int program,int maxcount,const char* count,const int* shaders) const {
    ::glGetAttachedShaders (program,maxcount,(GLsizei*) count,(GLuint*) shaders);
}
int IosGL20::glGetAttribLocation (int program,const std::string& name) const {
    return ::glGetAttribLocation (program, name.c_str());
}
void IosGL20::glGetBooleanv (int pname,const char* params) const {
    ::glGetBooleanv (pname, (GLboolean*) params);
}
void IosGL20::glGetBufferParameteriv (int target,int pname,const int* params) const {
    ::glGetBufferParameteriv (target,pname, (GLint*) params);
}
void IosGL20::glGetFloatv (int pname,const float* params) const {
    ::glGetFloatv (pname, (GLfloat*) params);
}
void IosGL20::glGetFramebufferAttachmentParameteriv (int target,int attachment,int pname,const int* params) const {
    ::glGetFramebufferAttachmentParameteriv (target,attachment,pname, (GLint*) params);
}
void IosGL20::glGetProgramiv (int program,int pname,const int* params) const {
    ::glGetProgramiv (program,pname, (GLint*) params);
}
std::string IosGL20::glGetProgramInfoLog (int program) const {
    GLchar buffer[2048];
    GLsizei length = 0;
    
    ::glGetProgramInfoLog (program, 2048,  &length, buffer);

    return buffer;
}
void IosGL20::glGetRenderbufferParameteriv (int target,int pname,const int* params) const {
    ::glGetRenderbufferParameteriv (target, pname, (GLint*)params);
}
void IosGL20::glGetShaderiv (int shader,int pname,const int* params) const {
    ::glGetShaderiv (shader,pname, (GLint*)params);
}
std::string IosGL20::glGetShaderInfoLog (int shader) const {
    GLchar buffer[2048];
    GLsizei size;
    ::glGetShaderInfoLog (shader, 2048, &size, buffer);

    return buffer;
}
void IosGL20::glGetShaderPrecisionFormat (int shadertype,int precisiontype,const int* range,const int* precision) const {
    ::glGetShaderPrecisionFormat (shadertype,precisiontype, (GLint*)range, (GLint*)precision);
}
void IosGL20::glGetShaderSource (int shader,int bufsize,const char* length,const std::string& source) const {
    //this is bogus. Fix if you need it someday on the future :)
    ::glGetShaderSource (shader,bufsize,(GLsizei*)length, (GLchar*) source.c_str());
}
void IosGL20::glGetTexParameterfv (int target,int pname,const float* params) const {
    ::glGetTexParameterfv (target,pname, (GLfloat*) params);
}
void IosGL20::glGetTexParameteriv (int target,int pname,const int* params) const {
    ::glGetTexParameteriv (target,pname, (GLint*)params);
}
void IosGL20::glGetUniformfv (int program,int location,const float* params) const {
    ::glGetUniformfv (program,location, (GLfloat*)params);
}
void IosGL20::glGetUniformiv (int program,int location,const int* params) const {
    ::glGetUniformiv (program,location, (GLint*)params);
}
int IosGL20::glGetUniformLocation (int program,const std::string& name) const {
    return ::glGetUniformLocation (program,name.c_str());
}
void IosGL20::glGetVertexAttribfv (int index,int pname,const float* params) const {
    ::glGetVertexAttribfv (index,pname, (GLfloat*)params);
}
void IosGL20::glGetVertexAttribiv (int index,int pname,const int* params) const {
    ::glGetVertexAttribiv (index,pname,(GLint*)params);
}
void IosGL20::glGetVertexAttribPointerv (int index,int pname,const char* pointer) const {
    ::glGetVertexAttribPointerv (index,pname,(GLvoid**) &pointer);
}
bool IosGL20::glIsBuffer (int buffer) const {
    return ::glIsBuffer (buffer);
}
bool IosGL20::glIsEnabled (int cap) const {
    return ::glIsEnabled (cap);
}
bool IosGL20::glIsFramebuffer (int framebuffer) const {
    return ::glIsFramebuffer (framebuffer);
}
bool IosGL20::glIsProgram (int program) const {
    return ::glIsProgram (program);
}
bool IosGL20::glIsRenderbuffer (int renderbuffer) const {
    return ::glIsRenderbuffer (renderbuffer);
}
bool IosGL20::glIsShader (int shader) const {
    return ::glIsShader (shader);
}
bool IosGL20::glIsTexture (int texture) const {
    return ::glIsTexture (texture);
}
void IosGL20::glLinkProgram (int program) const {
    ::glLinkProgram (program);
}
void IosGL20::glReleaseShaderCompiler () const {
    ::glReleaseShaderCompiler();
}

void IosGL20::glRenderbufferStorage (int target,int internalformat,int width,int height) const {
    ::glRenderbufferStorage (target,internalformat,width,height);
}
void IosGL20::glSampleCoverage (float value,bool invert) const {
    ::glSampleCoverage (value,invert);
}
void IosGL20::glShaderBinary (int n,const int* shaders,int binaryformat,const char* binary,int length) const {
    ::glShaderBinary (n, (const GLuint*)shaders,binaryformat, binary,length);
}
void IosGL20::glShaderSource (int shader,const std::string& string) const {
    GLint length = string.size();
    const GLchar* sources[1] = { (GLchar*) string.c_str() };
    
    ::glShaderSource (shader, 1, (const GLchar**) &sources, &length);
}
void IosGL20::glStencilFuncSeparate (int face,int func,int ref,int mask) const {
    ::glStencilFuncSeparate (face, func, ref,mask);
}
void IosGL20::glStencilMaskSeparate (int face,int mask) const {
    ::glStencilMaskSeparate (face,mask);
}
void IosGL20::glStencilOpSeparate (int face,int fail,int zfail,int zpass) const {
    ::glStencilOpSeparate ( face, fail, zfail, zpass);
}
void IosGL20::glTexParameterfv (int target,int pname,const float* params) const {
    ::glTexParameterfv ( target, pname, params);
}
void IosGL20::glTexParameteri (int target,int pname,int param) const {
    ::glTexParameteri (target, pname, param);
}
void IosGL20::glTexParameteriv (int target,int pname,const int* params) const {
    ::glTexParameteriv (target,pname,params);
}
void IosGL20::glUniform1f (int location,float x) const {
    ::glUniform1f (location,x);
}
void IosGL20::glUniform1fv (int location,int count,const float* v) const {
    ::glUniform1fv (location,count,v);
}
void IosGL20::glUniform1i (int location,int x) const {
    ::glUniform1i (location, x);
}
void IosGL20::glUniform1iv (int location,int count,const int* v) const {
    ::glUniform1iv (location, count, v);
}
void IosGL20::glUniform2f (int location,float x,float y) const {
    ::glUniform2f ( location, x,y);
}
void IosGL20::glUniform2fv (int location,int count,const float* v) const {
    ::glUniform2fv (location,count, v);
}
void IosGL20::glUniform2i (int location,int x,int y) const {
    ::glUniform2i (location,x,y);
}
void IosGL20::glUniform2iv (int location,int count,const int* v) const {
    ::glUniform2iv (location,count, v);
}
void IosGL20::glUniform3f (int location,float x,float y,float z) const {
    ::glUniform3f ( location,x,y, z);
}
void IosGL20::glUniform3fv (int location,int count,const float* v) const {
    ::glUniform3fv (location, count, v);
}
void IosGL20::glUniform3i (int location,int x,int y,int z) const {
    ::glUniform3i (location,x,y,z);
}
void IosGL20::glUniform3iv (int location,int count,const int* v) const {
    ::glUniform3iv (location, count, v);
}
void IosGL20::glUniform4f (int location,float x,float y,float z,float w) const {
    ::glUniform4f ( location, x, y, z, w);
}
void IosGL20::glUniform4fv (int location,int count,const float* v) const {
    ::glUniform4fv ( location, count, v);
}
void IosGL20::glUniform4i (int location,int x,int y,int z,int w) const {
    ::glUniform4i (location,x, y, z, w);
}
void IosGL20::glUniform4iv (int location,int count,const int* v) const {
    ::glUniform4iv ( location, count, v);
}
void IosGL20::glUniformMatrix2fv (int location,int count,bool transpose,const float* value) const {
    ::glUniformMatrix2fv ( location, count, transpose,value);
}
void IosGL20::glUniformMatrix3fv (int location,int count,bool transpose,const float* value) const {
    ::glUniformMatrix3fv (location, count, transpose, value);
}
void IosGL20::glUniformMatrix4fv (int location,int count,bool transpose,const float* value) const {
    ::glUniformMatrix4fv ( location, count, transpose, value);
}
void IosGL20::glUseProgram (int program) const {
    ::glUseProgram ( program);
}
void IosGL20::glValidateProgram (int program) const {
    ::glValidateProgram ( program);
}
void IosGL20::glVertexAttrib1f (int indx,float x) const {
    ::glVertexAttrib1f ( indx, x);
}
void IosGL20::glVertexAttrib1fv (int indx,const float* values) const {
    ::glVertexAttrib1fv (indx, values);
}
void IosGL20::glVertexAttrib2f (int indx,float x,float y) const {
    ::glVertexAttrib2f (indx,x,y);
}
void IosGL20::glVertexAttrib2fv (int indx,const float* values) const {
    ::glVertexAttrib2fv (indx,values);
}
void IosGL20::glVertexAttrib3f (int indx,float x,float y,float z) const {
    ::glVertexAttrib3f (indx,x,y,z);
}
void IosGL20::glVertexAttrib3fv (int indx,const float* values) const {
    ::glVertexAttrib3fv (indx, values);
}
void IosGL20::glVertexAttrib4f (int indx,float x,float y,float z,float w) const {
    ::glVertexAttrib4f (indx,x, y, z, w);
}
void IosGL20::glVertexAttrib4fv (int indx,const float* values) const {
    ::glVertexAttrib4fv (indx, values);
}
void IosGL20::glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,const void* ptr) const {
    ::glVertexAttribPointer (indx,size,type,normalized,stride, ptr);
}
void IosGL20::glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,int ptr) const {
    ::glVertexAttribPointer (indx,size,type,normalized,stride, (GLvoid*) ptr);
}

void IosGL20::glActiveTexture (int texture) const {
    ::glActiveTexture ( texture);
}
void IosGL20::glBindTexture (int target,int texture) const {
    ::glBindTexture ( target, texture);
}
void IosGL20::glBlendFunc (int sfactor,int dfactor) const {
    ::glBlendFunc ( sfactor, dfactor);
}
void IosGL20::glClear (int mask) const {
    ::glClear ( mask);
}
void IosGL20::glClearColor (float red,float green,float blue,float alpha) const {
    ::glClearColor ( red, green, blue, alpha);
}
void IosGL20::glClearDepthf (float depth) const {
    ::glClearDepthf ( depth);
}
void IosGL20::glClearStencil (int s) const {
    ::glClearStencil ( s);
}
void IosGL20::glColorMask (bool red,bool green,bool blue,bool alpha) const {
    ::glColorMask ( red, green, blue, alpha);
}
void IosGL20::glCompressedTexImage2D (int target,int level,int internalformat,int width,int height,int border,int imageSize,const unsigned char* data) const {
    ::glCompressedTexImage2D ( target, level, internalformat, width, height, border, imageSize, data);
}
void IosGL20::glCompressedTexSubImage2D (int target,int level,int xoffset,int yoffset,int width,int height,int format,int imageSize,const unsigned char* data) const {
    ::glCompressedTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, imageSize, data);
}
void IosGL20::glCopyTexImage2D (int target,int level,int internalformat,int x,int y,int width,int height,int border) const {
    ::glCopyTexImage2D ( target, level, internalformat, x, y, width, height, border);
}
void IosGL20::glCopyTexSubImage2D (int target,int level,int xoffset,int yoffset,int x,int y,int width,int height) const {
    ::glCopyTexSubImage2D ( target, level, xoffset, yoffset, x, y, width, height);
}
void IosGL20::glCullFace (int mode) const {
    ::glCullFace ( mode);
}
void IosGL20::glDeleteTextures (int n, const int* textures) const {
    ::glDeleteTextures ( n, (GLuint*) textures);
}
void IosGL20::glDepthFunc (int func) const {
    ::glDepthFunc ( func);
}
void IosGL20::glDepthMask (bool flag) const {
    ::glDepthMask ( flag);
}
void IosGL20::glDepthRangef (float zNear,float zFar) const {
    ::glDepthRangef ( zNear, zFar);
}
void IosGL20::glDisable (int cap) const {
    ::glDisable ( cap);
}
void IosGL20::glDrawArrays (int mode,int first,int count) const {
    ::glDrawArrays ( mode, first, count);
}
void IosGL20::glDrawElements (int mode,int count,int type, const void* indices) const {
    ::glDrawElements ( mode, count, type, indices);
}
void IosGL20::glEnable (int cap) const {
    ::glEnable ( cap);
}
void IosGL20::glFinish () const {
    ::glFinish();
}
void IosGL20::glFlush () const {
    ::glFlush();
}

void IosGL20::glFrontFace (int mode) const {
    ::glFrontFace ( mode);
}
void IosGL20::glGenTextures (int n,int* textures) const {
    ::glGenTextures ( n, (GLuint*) textures);
}
int IosGL20::glGetError () const {
    return ::glGetError();
}
void IosGL20::glGetIntegerv (int pname,const int* params) const {
    ::glGetIntegerv ( pname, (GLint*) params);
}
std::string IosGL20::glGetString (int name) const {
    const GLubyte* str = ::glGetString(name);
    return std::string((char*)str);
}
void IosGL20::glHint (int target,int mode) const {
    ::glHint ( target, mode);
}
void IosGL20::glLineWidth (float width) const {
    ::glLineWidth ( width);
}
void IosGL20::glPixelStorei (int pname,int param) const {
    ::glPixelStorei ( pname, param);
}
void IosGL20::glPolygonOffset (float factor,float units) const {
    ::glPolygonOffset ( factor, units);
}
void IosGL20::glReadPixels (int x,int y,int width,int height,int format,int type,const void* pixels) const {
    ::glReadPixels ( x, y, width, height, format, type, (GLvoid*) pixels);
}
void IosGL20::glScissor (int x,int y,int width,int height) const {
    ::glScissor ( x, y, width, height);
}
void IosGL20::glStencilFunc (int func,int ref,int mask) const {
    ::glStencilFunc ( func, ref, mask);
}
void IosGL20::glStencilMask (int mask) const {
    ::glStencilMask ( mask);
}
void IosGL20::glStencilOp (int fail,int zfail,int zpass) const {
    ::glStencilOp ( fail, zfail, zpass);
}
void IosGL20::glTexImage2D (int target,int level,int internalformat,int width,int height,int border,int format,int type,const unsigned char* pixels) const {
    ::glTexImage2D ( target, level, internalformat, width, height, border, format, type, pixels);
}
void IosGL20::glTexParameterf (int target,int pname,float param) const {
    ::glTexParameterf ( target, pname, param);
}
void IosGL20::glTexSubImage2D (int target,int level,int xoffset,int yoffset,int width,int height,int format,int type,const unsigned char* pixels) const {
    ::glTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, type, pixels);
}
void IosGL20::glViewport (int x,int y,int width,int height) const {
    ::glViewport ( x, y, width, height);
}
