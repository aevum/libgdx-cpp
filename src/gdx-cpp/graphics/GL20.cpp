
/*
 *    Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *
 *    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *    @author Ozires Bortolon de Faria ozires@aevumlab.com
 */

#include "GL20.hpp"

using namespace gdx;
using namespace std;

#include<gdx-cpp/internal/gl>

#include <stddef.h>

void GL20::glAttachShader ( int program, int shader ) const
{
    ::glAttachShader ( program, shader );
}

void GL20::glBindAttribLocation ( int program, int index, const string& name ) const
{
    ::glBindAttribLocation ( program, index, name.c_str() );
}

void GL20::glBindBuffer ( int target,int buffer ) const
{
    ::glBindBuffer ( target, buffer );
}

void GL20::glBindFramebuffer ( int target,int framebuffer ) const
{
    ::glBindFramebuffer ( target, framebuffer );
}

void GL20::glBindRenderbuffer ( int target,int renderbuffer ) const
{
    ::glBindRenderbuffer ( target, renderbuffer );
}
void GL20::glBlendColor ( float red,float green,float blue,float alpha ) const
{
    ::glBlendColor ( red, green, blue, alpha );
}
void GL20::glBlendEquation ( int mode ) const
{
    ::glBlendEquation ( mode );
}
void GL20::glBlendEquationSeparate ( int modeRGB,int modeAlpha ) const
{
    ::glBlendEquationSeparate ( modeRGB, modeAlpha );
}
void GL20::glBlendFuncSeparate ( int srcRGB,int dstRGB,int srcAlpha,int dstAlpha ) const
{
    ::glBlendFuncSeparate ( srcRGB, dstRGB, srcAlpha, dstAlpha );
}
void GL20::glBufferData ( int target,int size,const unsigned char* data,int usage ) const
{
    ::glBufferData ( target, size, data, usage );
}
void GL20::glBufferSubData ( int target,int offset,int size,const char* data ) const
{
    ::glBufferSubData ( target, offset, size, data );
}
int GL20::glCheckFramebufferStatus ( int target ) const
{
    return ::glCheckFramebufferStatus ( target );
}
void GL20::glCompileShader ( int shader ) const
{
    ::glCompileShader ( shader );
}
int GL20::glCreateProgram () const
{
    return ::glCreateProgram();
}
int GL20::glCreateShader ( int type ) const
{
    return ::glCreateShader ( type );
}
void GL20::glDeleteBuffers ( int n, unsigned int* buffers ) const
{
    ::glDeleteBuffers ( n, buffers );
}
void GL20::glDeleteFramebuffers ( int n,const unsigned int* framebuffers ) const
{
    ::glDeleteFramebuffers ( n, framebuffers );
}
void GL20::glDeleteProgram ( int program ) const
{
    ::glDeleteProgram ( program );
}
void GL20::glDeleteRenderbuffers ( int n,const unsigned int* renderbuffers ) const
{
    ::glDeleteRenderbuffers ( n, renderbuffers );
}
void GL20::glDeleteShader ( int shader ) const
{
    ::glDeleteShader ( shader );
}
void GL20::glDetachShader ( int program,int shader ) const
{
    ::glDetachShader ( program, shader );
}
void GL20::glDisableVertexAttribArray ( int index ) const
{
    ::glDisableVertexAttribArray ( index );
}
void GL20::glDrawElements ( int mode,int count,int type, const void* indices ) const
{
    ::glDrawElements ( mode, count, type, indices );
}
void GL20::glEnableVertexAttribArray ( int index ) const
{
    ::glEnableVertexAttribArray ( index );
}
void GL20::glFramebufferRenderbuffer ( int target,int attachment,int renderbuffertarget,int renderbuffer ) const
{
    ::glFramebufferRenderbuffer ( target, attachment, renderbuffertarget, renderbuffer );
}
void GL20::glFramebufferTexture2D ( int target,int attachment,int textarget,int texture,int level ) const
{
    ::glFramebufferTexture2D ( target, attachment, textarget, texture, level );
}
void GL20::glGenBuffers ( int n, unsigned int* buffers ) const
{

    ::glGenBuffers ( n, buffers );
}
void GL20::glGenerateMipmap ( int target ) const
{
    ::glGenerateMipmap ( target );
}
void GL20::glGenFramebuffers ( int n, unsigned int* framebuffers ) const
{
    ::glGenFramebuffers ( n, framebuffers );
}
void GL20::glGenRenderbuffers ( int n, unsigned int* renderbuffers ) const
{
    ::glGenRenderbuffers ( n, renderbuffers );
}

std::string GL20::glGetActiveAttrib ( int program,int index, const int* size, const char* type ) const
{
    GLint max_length;
    glGetProgramiv ( program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max_length );
    char* buf = new char[max_length + 1];
    ::glGetActiveAttrib ( program, index, max_length + 1, NULL, ( int * ) size, ( unsigned int* ) type, buf );
    return buf;
}

std::string GL20::glGetActiveUniform ( int program,int index,const int* size,const char* type ) const
{
    GLint max_length;
    glGetProgramiv ( program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length );
    char* buf = new char[max_length + 1];
    ::glGetActiveUniform ( program, index, max_length + 1, NULL, ( int* ) size, ( unsigned int* ) type, buf );
    return buf;
}

void GL20::glGetAttachedShaders ( int program,int maxcount, int* count, unsigned int* shaders ) const
{
    ::glGetAttachedShaders ( program, maxcount, count, shaders );
}
int GL20::glGetAttribLocation ( int program, const char* name ) const
{
    return ::glGetAttribLocation ( program, name );
}
void GL20::glGetBooleanv ( unsigned int pname, unsigned char* params ) const
{
    ::glGetBooleanv ( pname, params );
}
void GL20::glGetBufferParameteriv ( unsigned int target, unsigned int pname, int* params ) const
{
    ::glGetBufferParameteriv ( target, pname, params );
}
void GL20::glGetFloatv ( int pname, float* params ) const
{
    ::glGetFloatv ( pname, params );
}
void GL20::glGetFramebufferAttachmentParameteriv ( int target,int attachment,int pname, int* params ) const
{
    ::glGetFramebufferAttachmentParameteriv ( target, attachment, pname, params );
}
void GL20::glGetProgramiv ( int program, int pname, int* params ) const
{
    ::glGetProgramiv ( program, pname, params );
}
std::string GL20::glGetProgramInfoLog ( int program ) const
{
    char buf[512];
    int length = 0;
    ::glGetProgramInfoLog ( program, 512, &length, buf );
    return string ( buf );
}

void GL20::glGetRenderbufferParameteriv ( int target,int pname, int* params ) const
{
    ::glGetRenderbufferParameteriv ( target, pname, params );
}
void GL20::glGetShaderiv ( int shader,int pname, int* params ) const
{
    ::glGetShaderiv ( shader, pname, params );
}

std::string GL20::glGetShaderInfoLog ( int shader ) const
{
    int length = 0;
    glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &length );
    char buf[length];
    ::glGetShaderInfoLog ( shader, length, NULL, buf );
    return buf;
}
void GL20::glGetShaderPrecisionFormat ( int shadertype,int precisiontype, int* range, int* precision ) const
{
    ::glGetShaderPrecisionFormat ( shadertype, precisiontype, range, precision );
}
void GL20::glGetShaderSource ( unsigned int shader,int bufsize, int* length, char* source ) const
{
    ::glGetShaderSource ( shader, bufsize, length, source );
}
void GL20::glGetTexParameterfv ( int target,int pname, float* params ) const
{
    ::glGetTexParameterfv ( target, pname, params );
}
void GL20::glGetTexParameteriv ( int target,int pname, int* params ) const
{
    ::glGetTexParameteriv ( target, pname, params );
}
void GL20::glGetUniformfv ( int program,int location, float* params ) const
{
    ::glGetUniformfv ( program, location, params );
}
void GL20::glGetUniformiv ( int program,int location, int* params ) const
{
    ::glGetUniformiv ( program, location, params );
}
int GL20::glGetUniformLocation ( int program,const std::string& name ) const
{
    return ::glGetUniformLocation ( program, name.c_str() );
}
void GL20::glGetVertexAttribfv ( int index,int pname, float* params ) const
{
    ::glGetVertexAttribfv ( index, pname, params );
}
void GL20::glGetVertexAttribiv ( int index,int pname, int* params ) const
{
    ::glGetVertexAttribiv ( index, pname, params );
}
void GL20::glGetVertexAttribPointerv ( int index,int pname, void* pointer ) const
{
    ::glGetVertexAttribPointerv ( index, pname, &pointer );
}
bool GL20::glIsBuffer ( int buffer ) const
{
    return ::glIsBuffer ( buffer );
}
bool GL20::glIsEnabled ( int cap ) const
{
    return ::glIsEnabled ( cap );
}
bool GL20::glIsFramebuffer ( int framebuffer ) const
{
    return ::glIsFramebuffer ( framebuffer );
}
bool GL20::glIsProgram ( int program ) const
{
    return ::glIsProgram ( program );
}
bool GL20::glIsRenderbuffer ( int renderbuffer ) const
{
    return ::glIsRenderbuffer ( renderbuffer );
}
bool GL20::glIsShader ( int shader ) const
{
    return ::glIsShader ( shader );
}
bool GL20::glIsTexture ( int texture ) const
{
    return ::glIsTexture ( texture );
}
void GL20::glLinkProgram ( int program ) const
{
    ::glLinkProgram ( program );
}
void GL20::glReleaseShaderCompiler () const
{
    ::glReleaseShaderCompiler();
}
void GL20::glRenderbufferStorage ( int target,int internalformat,int width,int height ) const
{
    ::glRenderbufferStorage ( target, internalformat, width, height );
}
void GL20::glSampleCoverage ( float value,bool invert ) const
{
    ::glSampleCoverage ( value, invert );
}
void GL20::glShaderBinary ( int n,const unsigned int* shaders, int binaryformat,const void* binary,int length ) const
{
    ::glShaderBinary ( n, shaders, binaryformat, binary, length );
}

void GL20::glShaderSource ( int shader, const std::string& shaderString ) const
{
    int length = shaderString.size();
    const char* buf = shaderString.c_str();
    ::glShaderSource ( shader, 1, &buf, &length );
}
void GL20::glStencilFuncSeparate ( int face,int func,int ref,int mask ) const
{
    ::glStencilFuncSeparate ( face, func, ref, mask );
}
void GL20::glStencilMaskSeparate ( int face,int mask ) const
{
    ::glStencilMaskSeparate ( face, mask );
}
void GL20::glStencilOpSeparate ( int face,int fail,int zfail,int zpass ) const
{
    ::glStencilOpSeparate ( face, fail, zfail, zpass );
}
void GL20::glTexParameterfv ( int target,int pname,const float* params ) const
{
    ::glTexParameterfv ( target, pname, params );
}
void GL20::glTexParameteri ( int target,int pname,int param ) const
{
    ::glTexParameteri ( target, pname, param );
}
void GL20::glTexParameteriv ( int target,int pname,const int* params ) const
{
    ::glTexParameteriv ( target, pname, params );
}
void GL20::glUniform1f ( int location,float x ) const
{
    ::glUniform1f ( location, x );
}
void GL20::glUniform1fv ( int location,int count,const float* v ) const
{
    ::glUniform1fv ( location, count, v );
}
void GL20::glUniform1i ( int location,int x ) const
{
    ::glUniform1i ( location, x );
}
void GL20::glUniform1iv ( int location,int count,const int* v ) const
{
    ::glUniform1iv ( location, count, v );
}
void GL20::glUniform2f ( int location,float x,float y ) const
{
    ::glUniform2f ( location, x, y );
}
void GL20::glUniform2fv ( int location,int count,const float* v ) const
{
    ::glUniform2fv ( location, count, v );
}
void GL20::glUniform2i ( int location,int x,int y ) const
{
    ::glUniform2i ( location, x, y );
}
void GL20::glUniform2iv ( int location,int count,const int* v ) const
{
    ::glUniform2iv ( location, count, v );
}
void GL20::glUniform3f ( int location,float x,float y,float z ) const
{
    ::glUniform3f ( location, x, y, z );
}
void GL20::glUniform3fv ( int location,int count,const float* v ) const
{
    ::glUniform3fv ( location, count, v );
}
void GL20::glUniform3i ( int location,int x,int y,int z ) const
{
    ::glUniform3i ( location, x, y, z );
}
void GL20::glUniform3iv ( int location,int count,const int* v ) const
{
    ::glUniform3iv ( location, count, v );
}
void GL20::glUniform4f ( int location,float x,float y,float z,float w ) const
{
    ::glUniform4f ( location, x, y, z, w );
}
void GL20::glUniform4fv ( int location,int count,const float* v ) const
{
    ::glUniform4fv ( location, count, v );
}
void GL20::glUniform4i ( int location,int x,int y,int z,int w ) const
{
    ::glUniform4i ( location, x, y, z, w );
}
void GL20::glUniform4iv ( int location,int count,const int* v ) const
{
    ::glUniform4iv ( location, count, v );
}
void GL20::glUniformMatrix2fv ( int location,int count,bool transpose,const float* value ) const
{
    ::glUniformMatrix2fv ( location, count, transpose, value );
}
void GL20::glUniformMatrix3fv ( int location,int count,bool transpose,const float* value ) const
{
    ::glUniformMatrix3fv ( location, count, transpose, value );
}
void GL20::glUniformMatrix4fv ( int location,int count,bool transpose,const float* value ) const
{
    ::glUniformMatrix4fv ( location, count, transpose, value );
}
void GL20::glUseProgram ( int program ) const
{
    ::glUseProgram ( program );
}
void GL20::glValidateProgram ( int program ) const
{
    ::glValidateProgram ( program );
}
void GL20::glVertexAttrib1f ( int indx,float x ) const
{
    ::glVertexAttrib1f ( indx, x );
}
void GL20::glVertexAttrib1fv ( int indx,const float* values ) const
{
    ::glVertexAttrib1fv ( indx, values );
}
void GL20::glVertexAttrib2f ( int indx,float x,float y ) const
{
    ::glVertexAttrib2f ( indx, x, y );
}
void GL20::glVertexAttrib2fv ( int indx,const float* values ) const
{
    ::glVertexAttrib2fv ( indx, values );
}
void GL20::glVertexAttrib3f ( int indx,float x,float y,float z ) const
{
    ::glVertexAttrib3f ( indx, x, y, z );
}
void GL20::glVertexAttrib3fv ( int indx,const float* values ) const
{
    ::glVertexAttrib3fv ( indx, values );
}
void GL20::glVertexAttrib4f ( int indx,float x,float y,float z,float w ) const
{
    ::glVertexAttrib4f ( indx, x, y, z, w );
}
void GL20::glVertexAttrib4fv ( int indx,const float* values ) const
{
    ::glVertexAttrib4fv ( indx, values );
}
void GL20::glVertexAttribPointer ( int indx,int size,int type,bool normalized,int stride,const void* ptr ) const
{
    ::glVertexAttribPointer ( indx, size, type, normalized, stride, ptr );
}
void GL20::glVertexAttribPointer ( int indx,int size,int type,bool normalized,int stride,int ptr ) const
{
    ::glVertexAttribPointer ( indx, size, type, normalized, stride, ( void* ) (intptr_t) ptr );
}
