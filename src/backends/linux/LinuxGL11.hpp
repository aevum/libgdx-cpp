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


#ifndef GDX_CPP_BACKENDS_NIX_LINUXGL11_HPP
#define GDX_CPP_BACKENDS_NIX_LINUXGL11_HPP
#include <gdx-cpp/graphics/GL11.hpp>

namespace gdx_cpp {

namespace backends {

namespace nix {

class LinuxGL11 : public graphics::GL11
{
public:

    inline void glClipPlanef (int plane,int offset) {
        glClipPlanef (plane, offset);
    }
    inline void glClipPlanef (int plane,const float* equation) {
        glClipPlanef (plane, equation);
    }
    inline void glGetClipPlanef (int pname,int offset) {
        glGetClipPlanef (pname, offset);
    }
    inline void glGetClipPlanef (int pname,const float* eqn) {
        glGetClipPlanef (pname, eqn);
    }
    inline void glGetFloatv (int pname,int offset) {
        glGetFloatv (pname, offset);
    }
    inline void glGetFloatv (int pname,const float* params) {
        glGetFloatv (pname, params);
    }
    inline void glGetLightfv (int light,int pname,int offset) {
        glGetLightfv (light, pname, offset);
    }
    inline void glGetLightfv (int light,int pname,const float* params) {
        glGetLightfv (light, pname, params);
    }
    inline void glGetMaterialfv (int face,int pname,int offset) {
        glGetMaterialfv (face, pname, offset);
    }
    inline void glGetMaterialfv (int face,int pname,const float* params) {
        glGetMaterialfv (face, pname, params);
    }
    inline void glGetTexParameterfv (int target,int pname,int offset) {
        glGetTexParameterfv (target, pname, offset);
    }
    inline void glGetTexParameterfv (int target,int pname,const float* params) {
        glGetTexParameterfv (target, pname, params);
    }
    inline void glPointParameterf (int pname,float param) {
        glPointParameterf (pname, param);
    }
    inline void glPointParameterfv (int pname,int offset) {
        glPointParameterfv (pname, offset);
    }
    inline void glPointParameterfv (int pname,const float* params) {
        glPointParameterfv ( pname, params);
    }
    inline void glTexParameterfv (int target,int pname,int offset) {
        glTexParameterfv (target, pname, offset);
    }
    inline void glTexParameterfv (int target,int pname,const float* params) {
        glTexParameterfv (target, pname, params);
    }
    inline void glBindBuffer (int target,int buffer) {
        glBindBuffer (target, buffer);
    }
    inline void glBufferData (int target,int size,const char* data,int usage) {
        glBufferData (target, size, data, usage);
    }
    inline void glBufferSubData (int target,int offset,int size,const char* data) {
        glBufferSubData (target, offset, size, data);
    }
    inline void glColor4ub (char red,char green,char blue,char alpha) {
        glColor4ub (red, green, blue, alpha);
    }
    inline void glDeleteBuffers (int n,int offset) {
        glDeleteBuffers (n, offset);
    }
    inline void glDeleteBuffers (int n,const int* buffers) {
        glDeleteBuffers (n, buffers);
    }
    inline void glGetBooleanv (int pname,int offset) {
        glGetBooleanv (pname, offset);
    }
    inline void glGetBooleanv (int pname,const int* params) {
        glGetBooleanv (pname, params);
    }
    inline void glGetBufferParameteriv (int target,int pname,int offset) {
        glGetBufferParameteriv (target, pname, offset);
    }
    inline void glGetBufferParameteriv (int target,int pname,const int* params) {
        glGetBufferParameteriv (target, pname, params);
    }
    inline void glGenBuffers (int n,int offset) {
        glGenBuffers (n, offset);
    }
    inline void glGenBuffers (int n,const int* buffers) {
        glGenBuffers (n, buffers);
    }
    inline void glGetPointerv (int pname) {
        glGetPointerv (pname);
    }
    inline void glGetTexEnviv (int env,int pname,int offset) {
        glGetTexEnviv (env, pname, offset);
    }
    inline void glGetTexEnviv (int env,int pname,const int* params) {
        glGetTexEnviv (env, pname, params);
    }
    inline void glGetTexParameteriv (int target,int pname,int offset) {
        glGetTexParameteriv (target, pname, offset);
    }
    inline void glGetTexParameteriv (int target,int pname,const int* params) {
        glGetTexParameteriv (target, pname, params);
    }
    inline bool glIsBuffer (int buffer) {
        glIsBuffer (buffer);
    }
    inline bool glIsEnabled (int cap) {
        glIsEnabled (cap);
    }
    inline bool glIsTexture (int texture) {
        glIsTexture (texture);
    }
    inline void glTexEnvi (int target,int pname,int param) {
        glTexEnvi (target, pname, param);
    }
    inline void glTexEnviv (int target,int pname,int offset) {
        glTexEnviv (target, pname, offset);
    }
    inline void glTexEnviv (int target,int pname,const int* params) {
        glTexEnviv (target, pname, params);
    }
    inline void glTexParameteri (int target,int pname,int param) {
        glTexParameteri (target, pname, param);
    }
    inline void glTexParameteriv (int target,int pname,int offset) {
        glTexParameteriv (target, pname, offset);
    }
    inline void glTexParameteriv (int target,int pname,const int* params) {
        glTexParameteriv (target, pname, params);
    }
    inline void glPointSizePointerOES (int type,int stride,const char* pointer) {
        glPointSizePointerOES (type, stride, pointer);
    }
    inline void glVertexPointer (int size,int type,int stride,int pointer) {
        glVertexPointer (size, type, stride, pointer);
    }
    inline void glColorPointer (int size,int type,int stride,int pointer) {
        glColorPointer (size, type, stride, pointer);
    }
    inline void glNormalPointer (int type,int stride,int pointer) {
        glNormalPointer (type, stride, pointer);
    }
    inline void glTexCoordPointer (int size,int type,int stride,int pointer) {
        glTexCoordPointer (size, type, stride, pointer);
    }
    inline void glDrawElements (int mode,int count,int type,int indices) {
        glDrawElements (mode, count, type, indices);
    }


};

}

}

}

#endif // GDX_CPP_BACKENDS_NIX_LINUXGL11_HPP
