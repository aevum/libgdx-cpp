
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

namespace gdx_cpp {
namespace graphics {

class GL11 {
public:
    virtual void glClipPlanef (int plane,int offset) const = 0;
    virtual void glClipPlanef (int plane,const float*& equation) const = 0;
    virtual void glGetClipPlanef (int pname,int offset) const = 0;
    virtual void glGetClipPlanef (int pname,const float*& eqn) const = 0;
    virtual void glGetFloatv (int pname,int offset) const = 0;
    virtual void glGetFloatv (int pname,const float*& params) const = 0;
    virtual void glGetLightfv (int light,int pname,int offset) const = 0;
    virtual void glGetLightfv (int light,int pname,const float*& params) const = 0;
    virtual void glGetMaterialfv (int face,int pname,int offset) const = 0;
    virtual void glGetMaterialfv (int face,int pname,const float*& params) const = 0;
    virtual void glGetTexParameterfv (int target,int pname,int offset) const = 0;
    virtual void glGetTexParameterfv (int target,int pname,const float*& params) const = 0;
    virtual void glPointParameterf (int pname,float param) const = 0;
    virtual void glPointParameterfv (int pname,int offset) const = 0;
    virtual void glPointParameterfv (int pname,const float*& params) const = 0;
    virtual void glTexParameterfv (int target,int pname,int offset) const = 0;
    virtual void glTexParameterfv (int target,int pname,const float*& params) const = 0;
    virtual void glBindBuffer (int target,int buffer) const = 0;
    virtual void glBufferData (int target,int size,const char* data,int usage) const = 0;
    virtual void glBufferSubData (int target,int offset,int size,const char* data) const = 0;
    virtual void glColor4ub (char red,char green,char blue,char alpha) const = 0;
    virtual void glDeleteBuffers (int n,int offset) const = 0;
    virtual void glDeleteBuffers (int n,const int*& buffers) const = 0;
    virtual void glGetBooleanv (int pname,int offset) const = 0;
    virtual void glGetBooleanv (int pname,const int*& params) const = 0;
    virtual void glGetBufferParameteriv (int target,int pname,int offset) const = 0;
    virtual void glGetBufferParameteriv (int target,int pname,const int*& params) const = 0;
    virtual void glGenBuffers (int n,int offset) const = 0;
    virtual void glGenBuffers (int n,const int*& buffers) const = 0;
    virtual void glGetPointerv (int pname) const = 0;
    virtual void glGetTexEnviv (int env,int pname,int offset) const = 0;
    virtual void glGetTexEnviv (int env,int pname,const int*& params) const = 0;
    virtual void glGetTexParameteriv (int target,int pname,int offset) const = 0;
    virtual void glGetTexParameteriv (int target,int pname,const int*& params) const = 0;
    virtual   bool glIsBuffer (int buffer) const = 0;
    virtual   bool glIsEnabled (int cap) const = 0;
    virtual   bool glIsTexture (int texture) const = 0;
    virtual void glTexEnvi (int target,int pname,int param) const = 0;
    virtual void glTexEnviv (int target,int pname,int offset) const = 0;
    virtual void glTexEnviv (int target,int pname,const int*& params) const = 0;
    virtual void glTexParameteri (int target,int pname,int param) const = 0;
    virtual void glTexParameteriv (int target,int pname,int offset) const = 0;
    virtual void glTexParameteriv (int target,int pname,const int*& params) const = 0;
    virtual void glPointSizePointerOES (int type,int stride,const char* pointer) const = 0;
    virtual void glVertexPointer (int size,int type,int stride,int pointer) const = 0;
    virtual void glColorPointer (int size,int type,int stride,int pointer) const = 0;
    virtual void glNormalPointer (int type,int stride,int pointer) const = 0;
    virtual void glTexCoordPointer (int size,int type,int stride,int pointer) const = 0;
    virtual void glDrawElements (int mode,int count,int type,int indices) const = 0;

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_GL11_HPP_
