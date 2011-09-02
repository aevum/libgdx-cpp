/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License") const;
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

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>


namespace gdx_cpp {

namespace backends {

namespace nix {

class LinuxGL20 : public graphics::GL20
{
public:
    inline void glActiveTexture (int texture) const {
        ::glActiveTexture ( texture);
    }
    inline void glBindTexture (int target,int texture) const {
        ::glBindTexture ( target, texture);
    }
    inline void glBlendFunc (int sfactor,int dfactor) const {
        ::glBlendFunc ( sfactor, dfactor);
    }
    inline void glClear (int mask) const {
        ::glClear ( mask);
    }
    inline void glClearColor (float red,float green,float blue,float alpha) const {
        ::glClearColor ( red, green, blue, alpha);
    }
    inline void glClearDepthf (float depth) const {
        ::glClearDepthf ( depth);
    }
    inline void glClearStencil (int s) const {
        ::glClearStencil ( s);
    }
    inline void glColorMask (bool red,bool green,bool blue,bool alpha) const {
        ::glColorMask ( red, green, blue, alpha);
    }
    inline void glCompressedTexImage2D (int target,int level,int internalformat,int width,int height,int border,int imageSize,const unsigned char* data) const {
        ::glCompressedTexImage2D ( target, level, internalformat, width, height, border, imageSize, data);
    }
    inline void glCompressedTexSubImage2D (int target,int level,int xoffset,int yoffset,int width,int height,int format,int imageSize,const unsigned char* data) const {
        ::glCompressedTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, imageSize, data);
    }
    inline void glCopyTexImage2D (int target,int level,int internalformat,int x,int y,int width,int height,int border) const {
        ::glCopyTexImage2D ( target, level, internalformat, x, y, width, height, border);
    }
    inline void glCopyTexSubImage2D (int target,int level,int xoffset,int yoffset,int x,int y,int width,int height) const {
        ::glCopyTexSubImage2D ( target, level, xoffset, yoffset, x, y, width, height);
    }
    inline void glCullFace (int mode) const {
        ::glCullFace ( mode);
    }
    inline void glDeleteTextures (int n, const int* textures) const {
        ::glDeleteTextures ( n, (GLuint*) textures);
    }
    inline void glDepthFunc (int func) const {
        ::glDepthFunc ( func);
    }
    inline void glDepthMask (bool flag) const {
        ::glDepthMask ( flag);
    }
    inline void glDepthRangef (float zNear,float zFar) const {
        ::glDepthRangef ( zNear, zFar);
    }
    inline void glDisable (int cap) const {
        ::glDisable ( cap);
    }
    inline void glDrawArrays (int mode,int first,int count) const {
        ::glDrawArrays ( mode, first, count);
    }
    inline void glDrawElements (int mode,int count,int type, const void* indices) const {
        ::glDrawElements ( mode, count, type, indices);
    }
    inline void glEnable (int cap) const {
        ::glEnable ( cap);
    }
    inline void glFinish () const{
        ::glFinish();
    }
    inline void glFlush () const{
        ::glFlush();
    }
    
    inline void glFrontFace (int mode) const {
        ::glFrontFace ( mode);
    }
    inline void glGenTextures (int n,int* textures) const {
        ::glGenTextures ( n, (GLuint*) textures);
    }
    inline int glGetError () const {
        return ::glGetError();
    }
    inline void glGetIntegerv (int pname,const int* params) const {
        ::glGetIntegerv ( pname, (GLint*) params);
    }
    std::string& glGetString (int name) const {
        ::glGetString(name);
    }
    inline void glHint (int target,int mode) const {
        ::glHint ( target, mode);
    }
    inline void glLineWidth (float width) const {
        ::glLineWidth ( width);
    }
    inline void glPixelStorei (int pname,int param) const {
        ::glPixelStorei ( pname, param);
    }
    inline void glPolygonOffset (float factor,float units) const {
        ::glPolygonOffset ( factor, units);
    }
    inline void glReadPixels (int x,int y,int width,int height,int format,int type,const void* pixels) const {
        ::glReadPixels ( x, y, width, height, format, type, (GLvoid*) pixels);
    }
    inline void glScissor (int x,int y,int width,int height) const {
        ::glScissor ( x, y, width, height);
    }
    inline void glStencilFunc (int func,int ref,int mask) const {
        ::glStencilFunc ( func, ref, mask);
    }
    inline void glStencilMask (int mask) const {
        ::glStencilMask ( mask);
    }
    inline void glStencilOp (int fail,int zfail,int zpass) const {
        ::glStencilOp ( fail, zfail, zpass);
    }
    inline void glTexImage2D (int target,int level,int internalformat,int width,int height,int border,int format,int type,const unsigned char* pixels) const {
        ::glTexImage2D ( target, level, internalformat, width, height, border, format, type, pixels);
    }
    inline void glTexParameterf (int target,int pname,float param) const {
        ::glTexParameterf ( target, pname, param);
    }
    inline void glTexSubImage2D (int target,int level,int xoffset,int yoffset,int width,int height,int format,int type,const unsigned char* pixels) const {
        ::glTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, type, pixels);
    }
    inline void glViewport (int x,int y,int width,int height) const {
        ::glViewport ( x, y, width, height);
    }
    
    void glAttachShader (int program,int shader) const;
     void glBindAttribLocation (int program,int index,const std::string& name) const;
     void glBindBuffer (int target,int buffer) const;
     void glBindFramebuffer (int target,int framebuffer) const;
     void glBindRenderbuffer (int target,int renderbuffer) const;
     void glBlendColor (float red,float green,float blue,float alpha) const;
     void glBlendEquation (int mode) const;
     void glBlendEquationSeparate (int modeRGB,int modeAlpha) const;
     void glBlendFuncSeparate (int srcRGB,int dstRGB,int srcAlpha,int dstAlpha) const;
     void glBufferData (int target,int size,const char* data,int usage) const;
     void glBufferSubData (int target,int offset,int size,const char* data) const;
     int glCheckFramebufferStatus (int target) const;
     void glCompileShader (int shader) const;
     int glCreateProgram () const;
     int glCreateShader (int type) const;
     void glDeleteBuffers (int n,const int* buffers) const;
     void glDeleteFramebuffers (int n,const int* framebuffers) const;
     void glDeleteProgram (int program) const;
     void glDeleteRenderbuffers (int n,const int* renderbuffers) const;
     void glDeleteShader (int shader) const;
     void glDetachShader (int program,int shader) const;
     void glDisableVertexAttribArray (int index) const;
     void glDrawElements (int mode,int count,int type,int indices) const;
     void glEnableVertexAttribArray (int index) const;
     void glFramebufferRenderbuffer (int target,int attachment,int renderbuffertarget,int renderbuffer) const;
     void glFramebufferTexture2D (int target,int attachment,int textarget,int texture,int level) const;
     void glGenBuffers (int n,const int* buffers) const;
     void glGenerateMipmap (int target) const;
     void glGenFramebuffers (int n,const int* framebuffers) const;
     void glGenRenderbuffers (int n,const int* renderbuffers) const;
       std::string glGetActiveAttrib (int program,int index,const int* size,const char* type) const;
       std::string glGetActiveUniform (int program,int index,const int* size,const char* type) const;
     void glGetAttachedShaders (int program,int maxcount,const char* count,const int* shaders) const;
       int glGetAttribLocation (int program,const std::string& name) const;
     void glGetBooleanv (int pname,const char* params) const;
     void glGetBufferParameteriv (int target,int pname,const int* params) const;
     void glGetFloatv (int pname,const float* params) const;
     void glGetFramebufferAttachmentParameteriv (int target,int attachment,int pname,const int* params) const;
     void glGetProgramiv (int program,int pname,const int* params) const;
       std::string& glGetProgramInfoLog (int program) const;
     void glGetRenderbufferParameteriv (int target,int pname,const int* params) const;
     void glGetShaderiv (int shader,int pname,const int* params) const;
       std::string& glGetShaderInfoLog (int shader) const;
     void glGetShaderPrecisionFormat (int shadertype,int precisiontype,const int* range,const int* precision) const;
     void glGetShaderSource (int shader,int bufsize,const char* length,const std::string& source) const;
     void glGetTexParameterfv (int target,int pname,const float* params) const;
     void glGetTexParameteriv (int target,int pname,const int* params) const;
     void glGetUniformfv (int program,int location,const float* params) const;
     void glGetUniformiv (int program,int location,const int* params) const;
       int glGetUniformLocation (int program,const std::string& name) const;
     void glGetVertexAttribfv (int index,int pname,const float* params) const;
     void glGetVertexAttribiv (int index,int pname,const int* params) const;
     void glGetVertexAttribPointerv (int index,int pname,const char* pointer) const;
       bool glIsBuffer (int buffer) const;
       bool glIsEnabled (int cap) const;
       bool glIsFramebuffer (int framebuffer) const;
       bool glIsProgram (int program) const;
       bool glIsRenderbuffer (int renderbuffer) const;
       bool glIsShader (int shader) const;
       bool glIsTexture (int texture) const;
     void glLinkProgram (int program) const;
     void glReleaseShaderCompiler () const;
     void glRenderbufferStorage (int target,int internalformat,int width,int height) const;
     void glSampleCoverage (float value,bool invert) const;
     void glShaderBinary (int n,const int* shaders,int binaryformat,const char* binary,int length) const;
     void glShaderSource (int shader,const std::string& string) const;
     void glStencilFuncSeparate (int face,int func,int ref,int mask) const;
     void glStencilMaskSeparate (int face,int mask) const;
     void glStencilOpSeparate (int face,int fail,int zfail,int zpass) const;
     void glTexParameterfv (int target,int pname,const float* params) const;
     void glTexParameteri (int target,int pname,int param) const;
     void glTexParameteriv (int target,int pname,const int* params) const;
     void glUniform1f (int location,float x) const;
     void glUniform1fv (int location,int count,const float* v) const;
     void glUniform1i (int location,int x) const;
     void glUniform1iv (int location,int count,const int* v) const;
     void glUniform2f (int location,float x,float y) const;
     void glUniform2fv (int location,int count,const float* v) const;
     void glUniform2i (int location,int x,int y) const;
     void glUniform2iv (int location,int count,const int* v) const;
     void glUniform3f (int location,float x,float y,float z) const;
     void glUniform3fv (int location,int count,const float* v) const;
     void glUniform3i (int location,int x,int y,int z) const;
     void glUniform3iv (int location,int count,const int* v) const;
     void glUniform4f (int location,float x,float y,float z,float w) const;
     void glUniform4fv (int location,int count,const float* v) const;
     void glUniform4i (int location,int x,int y,int z,int w) const;
     void glUniform4iv (int location,int count,const int* v) const;
     void glUniformMatrix2fv (int location,int count,bool transpose,const float* value) const;
     void glUniformMatrix3fv (int location,int count,bool transpose,const float* value) const;
     void glUniformMatrix4fv (int location,int count,bool transpose,const float* value) const;
     void glUseProgram (int program) const;
     void glValidateProgram (int program) const;
     void glVertexAttrib1f (int indx,float x) const;
     void glVertexAttrib1fv (int indx,const float* values) const;
     void glVertexAttrib2f (int indx,float x,float y) const;
     void glVertexAttrib2fv (int indx,const float* values) const;
     void glVertexAttrib3f (int indx,float x,float y,float z) const;
     void glVertexAttrib3fv (int indx,const float* values) const;
     void glVertexAttrib4f (int indx,float x,float y,float z,float w) const;
     void glVertexAttrib4fv (int indx,const float* values) const;
     void glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,const void* ptr) const;
     void glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,int ptr) const;
};

}

}

}

#endif // GDX_CPP_BACKENDS_NIX_LINUXGL20_HPP
