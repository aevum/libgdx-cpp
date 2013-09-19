
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

#ifndef GDX_CPP_GRAPHICS_GL11_HPP_
#define GDX_CPP_GRAPHICS_GL11_HPP_

#include "GL10.hpp"

namespace gdx {

class GL11 : virtual public GL10 {
public:
    virtual void glClipPlanef (int plane,const float* equation) const;
    virtual void glGetClipPlanef (int pname,const float* eqn) const;
    virtual void glGetFloatv (int pname,const float* params) const;
    virtual void glGetLightfv (int light,int pname,const float* params) const;
    virtual void glGetMaterialfv (int face,int pname,const float* params) const;
    virtual void glGetTexParameterfv (int target,int pname,const float* params) const;
    virtual void glPointParameterf (int pname,float param) const;
    virtual void glPointParameterfv (int pname,const float* params) const;
    virtual void glTexParameterfv (int target,int pname,const float* params) const;
    virtual void glBindBuffer (int target,int buffer) const;
    virtual void glBufferData (int target,int size,const char* data,int usage) const;
    virtual void glBufferSubData (int target,int offset,int size,const void* data) const;
    virtual void glColor4ub (char red,char green,char blue,char alpha) const;
    virtual void glDeleteBuffers (int n,const int* buffers) const;
    virtual void glGetBooleanv (int pname,const int* params) const;
    virtual void glGetBufferParameteriv (int target,int pname,const int* params) const;
    virtual void glGenBuffers (int n,const int* buffers) const;
    virtual void glGetPointerv (int pname) const;
    virtual void glGetTexEnviv (int env,int pname,const int* params) const;
    virtual void glGetTexParameteriv (int target,int pname,const int* params) const;
    virtual bool glIsBuffer (int buffer) const;
    virtual bool glIsEnabled (int cap) const;
    virtual bool glIsTexture (int texture) const;
    virtual void glTexEnvi (int target,int pname,int param) const;
    virtual void glTexEnviv (int target,int pname,const int* params) const;
    virtual void glTexParameteri (int target,int pname,int param) const;
    virtual void glTexParameteriv (int target,int pname,const int* params) const;
    virtual void glPointSizePointerOES (int type,int stride,const char* pointer) const;
    virtual void glDrawElements (int mode,int count, unsigned int type, const void* indices) const override;
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GL11_HPP_
