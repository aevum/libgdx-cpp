
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
#include <set>

#undef GL_GENERATE_MIPMAP

namespace gdx {

class GLCommon {
public:
    static const int GL_GENERATE_MIPMAP;
  
    virtual void glActiveTexture (int texture) const;
    virtual void glBindTexture (int target,int texture) const;
    virtual void glBlendFunc (int sfactor,int dfactor) const;
    virtual void glClear (int mask) const;
    virtual void glClearColor (float red,float green,float blue,float alpha) const;
    virtual void glClearDepthf (float depth) const;
    virtual void glClearStencil (int s) const;
    virtual void glColorMask (bool red,bool green,bool blue,bool alpha) const;
    virtual void glCompressedTexImage2D (int target,int level,int internalformat,int width,int height,int border,int imageSize,const unsigned char* data) const;
    virtual void glCompressedTexSubImage2D (int target,int level,int xoffset,int yoffset,int width,int height,int format,int imageSize,const unsigned char* data) const;
    virtual void glCopyTexImage2D (int target,int level,int internalformat,int x,int y,int width,int height,int border) const;
    virtual void glCopyTexSubImage2D (int target,int level,int xoffset,int yoffset,int x,int y,int width,int height) const;
    virtual void glCullFace (int mode) const;
    virtual void glDeleteTextures (int n,const unsigned int* textures) const;
    virtual void glDepthFunc (int func) const;
    virtual void glDepthMask (bool flag) const;
    virtual void glDepthRangef (float zNear,float zFar) const;
    virtual void glDisable (int cap);
    virtual void glDrawArrays (int mode,int first,int count) const;
    virtual void glDrawElements (int mode,int count,int type, const void* indices) const;
    virtual void glEnable (int cap);
    virtual void glFinish () const;
    virtual void glFlush () const;
    virtual void glFrontFace (int mode) const;
    virtual void glGenTextures (int n, unsigned int* textures) const;
    virtual int glGetError () const;
    virtual void glGetIntegerv (int pname,const int* params) const;
    virtual std::string glGetString (int name) const;
    virtual void glHint (int target,int mode) const;
    virtual void glLineWidth (float width) const;
    virtual void glPixelStorei (int pname,int param) const;
    virtual void glPolygonOffset (float factor,float units) const;
    virtual void glReadPixels (int x,int y,int width,int height,int format,int type,const void* pixels) const;
    virtual void glScissor (int x,int y,int width,int height) const;
    virtual void glStencilFunc (int func,int ref,int mask) const;
    virtual void glStencilMask (int mask) const;
    virtual void glStencilOp (int fail,int zfail,int zpass) const;
    virtual void glTexImage2D (int target,int level,int internalformat,int width,int height,int border,int format,int type,const unsigned char* pixels) const;
    virtual void glTexParameterf (int target,int pname,float param) const;
    virtual void glTexSubImage2D (int target,int level,int xoffset,int yoffset,int width,int height,int format,int type,const unsigned char* pixels) const;
    virtual void glViewport (int x,int y,int width,int height) const;


    GLCommon();
    
    virtual ~GLCommon();
    
protected:
    unsigned char vertex_states;
    const void* last_vertex_pointer;
    const void* last_tex_coord_pointer;
    const void* last_color_pointer;
    std::set<int> enabled_states;
    
private:
    GLCommon(const GLCommon&) = delete;
    GLCommon& operator=(const GLCommon& other) = delete;
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GLCOMMON_HPP_
