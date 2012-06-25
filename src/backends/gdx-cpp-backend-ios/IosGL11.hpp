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


#ifndef GDX_CPP_BACKENDS_IOS_IOSGL11_HPP
#define GDX_CPP_BACKENDS_IOS_IOSGL11_HPP

#include <gdx-cpp/graphics/GL11.hpp>
#include "IosGL10.hpp"

namespace gdx {

namespace backends {

namespace ios {

class IosGL11 : public IosGL10, virtual public GL11
{
public:
     void glClipPlanef (int plane,const float* equation) const ;
     void glGetClipPlanef (int pname,const float* eqn) const ;
     void glGetFloatv (int pname,const float* params) const ;
     void glGetLightfv (int light,int pname,const float* params) const ;
     void glGetMaterialfv (int face,int pname,const float* params) const ;
     void glGetTexParameterfv (int target,int pname,const float* params) const ;
     void glPointParameterf (int pname,float param) const ;
     void glPointParameterfv (int pname,const float* params) const;
     void glTexParameterfv (int target,int pname,const float* params) const;
     void glBindBuffer (int target,int buffer) const;
     void glBufferData (int target,int size,const char* data,int usage) const;
     void glBufferSubData (int target,int offset,int size,const void* data) const;
     void glColor4ub (char red,char green,char blue,char alpha) const;
     void glDeleteBuffers (int n,const int* buffers) const;
     void glGetBooleanv (int pname,const int* params) const;
     void glGetBufferParameteriv (int target,int pname,const int* params) const;
     void glGenBuffers (int n,const int* buffers) const;
     void glGetPointerv (int pname) const;
     void glGetTexEnviv (int env,int pname,const int* params) const;
     void glGetTexParameteriv (int target,int pname,const int* params) const;
     bool glIsBuffer (int buffer) const;
     bool glIsEnabled (int cap) const;
     bool glIsTexture (int texture) const;
     void glTexEnvi (int target,int pname,int param) const;
     void glTexEnviv (int target,int pname,const int* params) const;
     void glTexParameteri (int target,int pname,int param) const;
     void glTexParameteriv (int target,int pname,const int* params) const;
     void glPointSizePointerOES (int type,int stride,const char* pointer) const;
     void glVertexPointer (int size, int type, int stride, void* pointer) const;
     void glColorPointer (int size, int type, int stride, void* pointer) const;
     void glNormalPointer (int type, int stride, void* pointer) const;
     void glTexCoordPointer (int size, int type, int stride, void* pointer) const;
     void glDrawElements (int mode, int count, int type, void* indices) const;
};

}

}

}

#endif // GDX_CPP_BACKENDS_IOS_IOSGL11_HPP
