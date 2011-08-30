
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

#ifndef GDX_CPP_GRAPHICS_GLCOMMON_HPP_
#define GDX_CPP_GRAPHICS_GLCOMMON_HPP_

#include <string>

namespace gdx_cpp {
namespace graphics {

class GLCommon {
public:
    static const int GL_GENERATE_MIPMAP = 0x8191;
  
    virtual void glActiveTexture (int texture) const = 0;
    virtual void glBindTexture (int target,int texture) const = 0;
    virtual void glBlendFunc (int sfactor,int dfactor) const = 0;
    virtual void glClear (int mask) const = 0;
    virtual void glClearColor (float red,float green,float blue,float alpha) const = 0;
    virtual void glClearDepthf (float depth) const = 0;
    virtual void glClearStencil (int s) const = 0;
    virtual void glColorMask (bool red,bool green,bool blue,bool alpha) const = 0;
    virtual void glCompressedTexImage2D (int target,int level,int internalformat,int width,int height,int border,int imageSize,const unsigned char* data) const = 0;
    virtual void glCompressedTexSubImage2D (int target,int level,int xoffset,int yoffset,int width,int height,int format,int imageSize,const unsigned char* data) const = 0;
    virtual void glCopyTexImage2D (int target,int level,int internalformat,int x,int y,int width,int height,int border) const = 0;
    virtual void glCopyTexSubImage2D (int target,int level,int xoffset,int yoffset,int x,int y,int width,int height) const = 0;
    virtual void glCullFace (int mode) const = 0;
    virtual void glDeleteTextures (int n,const int* textures) const = 0;
    virtual void glDepthFunc (int func) const = 0;
    virtual void glDepthMask (bool flag) const = 0;
    virtual void glDepthRangef (float zNear,float zFar) const = 0;
    virtual void glDisable (int cap) const = 0;
    virtual void glDrawArrays (int mode,int first,int count) const = 0;
    virtual void glDrawElements (int mode,int count,int type, const void* indices) const = 0;
    virtual void glEnable (int cap) const = 0;
    virtual void glFinish () const = 0;
    virtual void glFlush () const = 0;
    virtual void glFrontFace (int mode) const = 0;
    virtual void glGenTextures (int n,int* textures) const = 0;
    virtual   int glGetError () const = 0;
    virtual void glGetIntegerv (int pname,const int* params) const = 0;
    virtual   std::string& glGetString (int name) const = 0;
    virtual void glHint (int target,int mode) const = 0;
    virtual void glLineWidth (float width) const = 0;
    virtual void glPixelStorei (int pname,int param) const = 0;
    virtual void glPolygonOffset (float factor,float units) const = 0;
    virtual void glReadPixels (int x,int y,int width,int height,int format,int type,const unsigned char* pixels) const = 0;
    virtual void glScissor (int x,int y,int width,int height) const = 0;
    virtual void glStencilFunc (int func,int ref,int mask) const = 0;
    virtual void glStencilMask (int mask) const = 0;
    virtual void glStencilOp (int fail,int zfail,int zpass) const = 0;
    virtual void glTexImage2D (int target,int level,int internalformat,int width,int height,int border,int format,int type,const unsigned char* pixels) const = 0;
    virtual void glTexParameterf (int target,int pname,float param) const = 0;
    virtual void glTexSubImage2D (int target,int level,int xoffset,int yoffset,int width,int height,int format,int type,const unsigned char* pixels) const = 0;
    virtual void glViewport (int x,int y,int width,int height) const = 0;

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_GLCOMMON_HPP_
