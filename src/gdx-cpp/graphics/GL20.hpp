
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

namespace gdx_cpp {
namespace graphics {

class GL20 {
public:
    virtual   void glAttachShader (int program,int shader) = 0;
    virtual   void glBindAttribLocation (int program,int index,const std::string& name) = 0;
    virtual   void glBindBuffer (int target,int buffer) = 0;
    virtual   void glBindFramebuffer (int target,int framebuffer) = 0;
    virtual   void glBindRenderbuffer (int target,int renderbuffer) = 0;
    virtual   void glBlendColor (float red,float green,float blue,float alpha) = 0;
    virtual   void glBlendEquation (int mode) = 0;
    virtual   void glBlendEquationSeparate (int modeRGB,int modeAlpha) = 0;
    virtual   void glBlendFuncSeparate (int srcRGB,int dstRGB,int srcAlpha,int dstAlpha) = 0;
    virtual   void glBufferData (int target,int size,const Buffer& data,int usage) = 0;
    virtual   void glBufferSubData (int target,int offset,int size,const Buffer& data) = 0;
    virtual   int glCheckFramebufferStatus (int target) = 0;
    virtual   void glCompileShader (int shader) = 0;
    virtual   int glCreateProgram () = 0;
    virtual   int glCreateShader (int type) = 0;
    virtual   void glDeleteBuffers (int n,const IntBuffer& buffers) = 0;
    virtual   void glDeleteFramebuffers (int n,const IntBuffer& framebuffers) = 0;
    virtual   void glDeleteProgram (int program) = 0;
    virtual   void glDeleteRenderbuffers (int n,const IntBuffer& renderbuffers) = 0;
    virtual   void glDeleteShader (int shader) = 0;
    virtual   void glDetachShader (int program,int shader) = 0;
    virtual   void glDisableVertexAttribArray (int index) = 0;
    virtual   void glDrawElements (int mode,int count,int type,int indices) = 0;
    virtual   void glEnableVertexAttribArray (int index) = 0;
    virtual   void glFramebufferRenderbuffer (int target,int attachment,int renderbuffertarget,int renderbuffer) = 0;
    virtual   void glFramebufferTexture2D (int target,int attachment,int textarget,int texture,int level) = 0;
    virtual   void glGenBuffers (int n,const IntBuffer& buffers) = 0;
    virtual   void glGenerateMipmap (int target) = 0;
    virtual   void glGenFramebuffers (int n,const IntBuffer& framebuffers) = 0;
    virtual   void glGenRenderbuffers (int n,const IntBuffer& renderbuffers) = 0;
    virtual   std::string& glGetActiveAttrib (int program,int index,const IntBuffer& size,const Buffer& type) = 0;
    virtual   std::string& glGetActiveUniform (int program,int index,const IntBuffer& size,const Buffer& type) = 0;
    virtual   void glGetAttachedShaders (int program,int maxcount,const Buffer& count,const IntBuffer& shaders) = 0;
    virtual   int glGetAttribLocation (int program,const std::string& name) = 0;
    virtual   void glGetBooleanv (int pname,const Buffer& params) = 0;
    virtual   void glGetBufferParameteriv (int target,int pname,const IntBuffer& params) = 0;
    virtual   void glGetFloatv (int pname,const FloatBuffer& params) = 0;
    virtual   void glGetFramebufferAttachmentParameteriv (int target,int attachment,int pname,const IntBuffer& params) = 0;
    virtual   void glGetProgramiv (int program,int pname,const IntBuffer& params) = 0;
    virtual   std::string& glGetProgramInfoLog (int program) = 0;
    virtual   void glGetRenderbufferParameteriv (int target,int pname,const IntBuffer& params) = 0;
    virtual   void glGetShaderiv (int shader,int pname,const IntBuffer& params) = 0;
    virtual   std::string& glGetShaderInfoLog (int shader) = 0;
    virtual   void glGetShaderPrecisionFormat (int shadertype,int precisiontype,const IntBuffer& range,const IntBuffer& precision) = 0;
    virtual   void glGetShaderSource (int shader,int bufsize,const Buffer& length,const std::string& source) = 0;
    virtual   void glGetTexParameterfv (int target,int pname,const FloatBuffer& params) = 0;
    virtual   void glGetTexParameteriv (int target,int pname,const IntBuffer& params) = 0;
    virtual   void glGetUniformfv (int program,int location,const FloatBuffer& params) = 0;
    virtual   void glGetUniformiv (int program,int location,const IntBuffer& params) = 0;
    virtual   int glGetUniformLocation (int program,const std::string& name) = 0;
    virtual   void glGetVertexAttribfv (int index,int pname,const FloatBuffer& params) = 0;
    virtual   void glGetVertexAttribiv (int index,int pname,const IntBuffer& params) = 0;
    virtual   void glGetVertexAttribPointerv (int index,int pname,const Buffer& pointer) = 0;
    virtual   bool glIsBuffer (int buffer) = 0;
    virtual   bool glIsEnabled (int cap) = 0;
    virtual   bool glIsFramebuffer (int framebuffer) = 0;
    virtual   bool glIsProgram (int program) = 0;
    virtual   bool glIsRenderbuffer (int renderbuffer) = 0;
    virtual   bool glIsShader (int shader) = 0;
    virtual   bool glIsTexture (int texture) = 0;
    virtual   void glLinkProgram (int program) = 0;
    virtual   void glReleaseShaderCompiler () = 0;
    virtual   void glRenderbufferStorage (int target,int internalformat,int width,int height) = 0;
    virtual   void glSampleCoverage (float value,bool invert) = 0;
    virtual   void glShaderBinary (int n,const IntBuffer& shaders,int binaryformat,const Buffer& binary,int length) = 0;
    virtual   void glShaderSource (int shader,const std::string& string) = 0;
    virtual   void glStencilFuncSeparate (int face,int func,int ref,int mask) = 0;
    virtual   void glStencilMaskSeparate (int face,int mask) = 0;
    virtual   void glStencilOpSeparate (int face,int fail,int zfail,int zpass) = 0;
    virtual   void glTexParameterfv (int target,int pname,const FloatBuffer& params) = 0;
    virtual   void glTexParameteri (int target,int pname,int param) = 0;
    virtual   void glTexParameteriv (int target,int pname,const IntBuffer& params) = 0;
    virtual   void glUniform1f (int location,float x) = 0;
    virtual   void glUniform1fv (int location,int count,const FloatBuffer& v) = 0;
    virtual   void glUniform1i (int location,int x) = 0;
    virtual   void glUniform1iv (int location,int count,const IntBuffer& v) = 0;
    virtual   void glUniform2f (int location,float x,float y) = 0;
    virtual   void glUniform2fv (int location,int count,const FloatBuffer& v) = 0;
    virtual   void glUniform2i (int location,int x,int y) = 0;
    virtual   void glUniform2iv (int location,int count,const IntBuffer& v) = 0;
    virtual   void glUniform3f (int location,float x,float y,float z) = 0;
    virtual   void glUniform3fv (int location,int count,const FloatBuffer& v) = 0;
    virtual   void glUniform3i (int location,int x,int y,int z) = 0;
    virtual   void glUniform3iv (int location,int count,const IntBuffer& v) = 0;
    virtual   void glUniform4f (int location,float x,float y,float z,float w) = 0;
    virtual   void glUniform4fv (int location,int count,const FloatBuffer& v) = 0;
    virtual   void glUniform4i (int location,int x,int y,int z,int w) = 0;
    virtual   void glUniform4iv (int location,int count,const IntBuffer& v) = 0;
    virtual   void glUniformMatrix2fv (int location,int count,bool transpose,const FloatBuffer& value) = 0;
    virtual   void glUniformMatrix3fv (int location,int count,bool transpose,const FloatBuffer& value) = 0;
    virtual   void glUniformMatrix4fv (int location,int count,bool transpose,const FloatBuffer& value) = 0;
    virtual   void glUseProgram (int program) = 0;
    virtual   void glValidateProgram (int program) = 0;
    virtual   void glVertexAttrib1f (int indx,float x) = 0;
    virtual   void glVertexAttrib1fv (int indx,const FloatBuffer& values) = 0;
    virtual   void glVertexAttrib2f (int indx,float x,float y) = 0;
    virtual   void glVertexAttrib2fv (int indx,const FloatBuffer& values) = 0;
    virtual   void glVertexAttrib3f (int indx,float x,float y,float z) = 0;
    virtual   void glVertexAttrib3fv (int indx,const FloatBuffer& values) = 0;
    virtual   void glVertexAttrib4f (int indx,float x,float y,float z,float w) = 0;
    virtual   void glVertexAttrib4fv (int indx,const FloatBuffer& values) = 0;
    virtual   void glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,const Buffer& ptr) = 0;
    virtual   void glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,int ptr) = 0;

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_GL20_HPP_
