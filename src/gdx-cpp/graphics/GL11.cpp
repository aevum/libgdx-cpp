/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 */

#include "GL11.hpp"

#include <gdx-cpp/gl.hpp>
#include <gdx-cpp/internal/gl>

using namespace gdx;

void GL11::glClipPlanef(int plane, const float* equation) const {
    ::glClipPlanef (plane, (GLfloat*) equation);
}
void GL11::glGetClipPlanef(int pname, const float* eqn) const {
    ::glGetClipPlanef (pname, (GLfloat*) eqn);
}
void GL11::glGetFloatv(int pname, const float* params) const {
    ::glGetFloatv (pname, (GLfloat*) params);
}
void GL11::glGetLightfv(int light, int pname, const float* params) const {
    ::glGetLightfv (light, pname,(GLfloat*) params);
}
void GL11::glGetMaterialfv(int face, int pname, const float* params) const {
    ::glGetMaterialfv (face, pname, (GLfloat*) params);
}
void GL11::glGetTexParameterfv(int target, int pname, const float* params) const {
    ::glGetTexParameterfv (target, pname, (GLfloat*) params);
}
void GL11::glPointParameterf(int pname, float param) const {
    ::glPointParameterf (pname, param);
}

void GL11::glPointParameterfv (int pname,const float* params) const {
    ::glPointParameterfv ( pname, params);
}

void GL11::glTexParameterfv (int target,int pname,const float* params) const {
    ::glTexParameterfv (target, pname, params);
}

void GL11::glBindBuffer (int target,int buffer) const {
    ::glBindBuffer (target, buffer);
}

void GL11::glBufferData (int target,int size,const char* data,int usage) const {
    ::glBufferData (target, size, data, usage);
}

void GL11::glBufferSubData (int target,int offset,int size,const void* data) const {
    ::glBufferSubData (target, offset, size, data);
}
void GL11::glColor4ub (char red,char green,char blue,char alpha) const {
    ::glColor4ub (red, green, blue, alpha);
}
void GL11::glDeleteBuffers (int n,const int* buffers) const {
    ::glDeleteBuffers (n, (GLuint*)buffers);
}
void GL11::glGetBooleanv (int pname,const int* params) const {
    ::glGetBooleanv (pname, (GLboolean*) params);
}
void GL11::glGetBufferParameteriv (int target,int pname,const int* params) const {
    ::glGetBufferParameteriv (target, pname, (GLint*)params);
}
void GL11::glGenBuffers (int n, const int* buffers) const {
    ::glGenBuffers (n, (GLuint*) buffers);
}
void GL11::glGetPointerv (int pname) const {
    //     ::glGetPointerv (pname);
}
void GL11::glGetTexEnviv (int env,int pname,const int* params) const {
    ::glGetTexEnviv (env, pname, (GLint*) params);
}
void GL11::glGetTexParameteriv (int target,int pname,const int* params) const {
    ::glGetTexParameteriv (target, pname, (GLint*) params);
}
bool GL11::glIsBuffer (int buffer) const {
    return ::glIsBuffer ( buffer );
}
bool GL11::glIsEnabled (int cap) const {
    return ::glIsEnabled (cap);
}
bool GL11::glIsTexture (int texture) const {
    return ::glIsTexture (texture);
}
void GL11::glTexEnvi (int target,int pname,int param) const {
    ::glTexEnvi (target, pname, param);
}
void GL11::glTexEnviv (int target,int pname,const int* params) const {
    ::glTexEnviv (target, pname, params);
}
void GL11::glTexParameteri (int target,int pname,int param) const {
    ::glTexParameteri (target, pname, param);
}
void GL11::glTexParameteriv (int target,int pname,const int* params) const {
    ::glTexParameteriv (target, pname, params);
}
void GL11::glPointSizePointerOES (int type,int stride,const char* pointer) const {
    //     ::glPointSize (type, stride, pointer);
}

void GL11::glDrawElements ( int mode, int count, unsigned int type, void* indices ) const {
    ::glDrawElements (mode, count, type, indices);
}



