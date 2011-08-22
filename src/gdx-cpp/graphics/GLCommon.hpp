
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

namespace gdx_cpp {
namespace graphics {

class GLCommon {
public:
    virtual   void glActiveTexture (int texture) = 0;
    virtual   void glBindTexture (int target,int texture) = 0;
    virtual   void glBlendFunc (int sfactor,int dfactor) = 0;
    virtual   void glClear (int mask) = 0;
    virtual   void glClearColor (float red,float green,float blue,float alpha) = 0;
    virtual   void glClearDepthf (float depth) = 0;
    virtual   void glClearStencil (int s) = 0;
    virtual   void glColorMask (bool red,bool green,bool blue,bool alpha) = 0;
    virtual   void glCompressedTexImage2D (int target,int level,int internalformat,int width,int height,int border,int imageSize,const Buffer& data) = 0;
    virtual   void glCompressedTexSubImage2D (int target,int level,int xoffset,int yoffset,int width,int height,int format,int imageSize,const Buffer& data) = 0;
    virtual   void glCopyTexImage2D (int target,int level,int internalformat,int x,int y,int width,int height,int border) = 0;
    virtual   void glCopyTexSubImage2D (int target,int level,int xoffset,int yoffset,int x,int y,int width,int height) = 0;
    virtual   void glCullFace (int mode) = 0;
    virtual   void glDeleteTextures (int n,const IntBuffer& textures) = 0;
    virtual   void glDepthFunc (int func) = 0;
    virtual   void glDepthMask (bool flag) = 0;
    virtual   void glDepthRangef (float zNear,float zFar) = 0;
    virtual   void glDisable (int cap) = 0;
    virtual   void glDrawArrays (int mode,int first,int count) = 0;
    virtual   void glDrawElements (int mode,int count,int type,const Buffer& indices) = 0;
    virtual   void glEnable (int cap) = 0;
    virtual   void glFinish () = 0;
    virtual   void glFlush () = 0;
    virtual   void glFrontFace (int mode) = 0;
    virtual   void glGenTextures (int n,const IntBuffer& textures) = 0;
    virtual   int glGetError () = 0;
    virtual   void glGetIntegerv (int pname,const IntBuffer& params) = 0;
    virtual   std::string& glGetString (int name) = 0;
    virtual   void glHint (int target,int mode) = 0;
    virtual   void glLineWidth (float width) = 0;
    virtual   void glPixelStorei (int pname,int param) = 0;
    virtual   void glPolygonOffset (float factor,float units) = 0;
    virtual   void glReadPixels (int x,int y,int width,int height,int format,int type,const Buffer& pixels) = 0;
    virtual   void glScissor (int x,int y,int width,int height) = 0;
    virtual   void glStencilFunc (int func,int ref,int mask) = 0;
    virtual   void glStencilMask (int mask) = 0;
    virtual   void glStencilOp (int fail,int zfail,int zpass) = 0;
    virtual   void glTexImage2D (int target,int level,int internalformat,int width,int height,int border,int format,int type,const Buffer& pixels) = 0;
    virtual   void glTexParameterf (int target,int pname,float param) = 0;
    virtual   void glTexSubImage2D (int target,int level,int xoffset,int yoffset,int width,int height,int format,int type,const Buffer& pixels) = 0;
    virtual   void glViewport (int x,int y,int width,int height) = 0;

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_GLCOMMON_HPP_
