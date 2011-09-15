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


#ifndef GDX_CPP_BACKENDS_NIX_LINUXGL10_HPP
#define GDX_CPP_BACKENDS_NIX_LINUXGL10_HPP

#include <gdx-cpp/graphics/GL10.hpp>

namespace gdx_cpp {

namespace backends {

namespace android {

class AndroidGL10 : virtual public graphics::GL10
{
public:
    virtual void glActiveTexture (int texture) const ;
    void glBindTexture (int target,int texture) const ;
    void glBlendFunc (int sfactor,int dfactor) const ;
    void glClear (int mask) const ;
    void glClearColor (float red,float green,float blue,float alpha) const ;
    void glClearDepthf (float depth) const ;
    void glClearStencil (int s) const ;
    void glColorMask (bool red,bool green,bool blue,bool alpha) const ;
    void glCompressedTexImage2D (int target,int level,int internalformat,int width,int height,int border,int imageSize,const unsigned char* data) const ;
    void glCompressedTexSubImage2D (int target,int level,int xoffset,int yoffset,int width,int height,int format,int imageSize,const unsigned char* data) const ;
    void glCopyTexImage2D (int target,int level,int internalformat,int x,int y,int width,int height,int border) const ;
    void glCopyTexSubImage2D (int target,int level,int xoffset,int yoffset,int x,int y,int width,int height) const ;
    void glCullFace (int mode) const ;
    void glDeleteTextures (int n, const int* textures) const ;
    void glDepthFunc (int func) const ;
    void glDepthMask (bool flag) const ;
    void glDepthRangef (float zNear,float zFar) const ;
    void glDisable (int cap) const ;
    void glDrawArrays (int mode,int first,int count) const ;
    void glDrawElements (int mode,int count,int type, const void* indices) const ;
    void glEnable (int cap) const ;
    void glFinish () const ;
    void glFlush () const ;

    void glFrontFace (int mode) const ;
    void glGenTextures (int n,int* textures) const ;
    int glGetError () const ;
    void glGetIntegerv (int pname,const int* params) const ;
    std::string glGetString (int name) const ;
    void glHint (int target,int mode) const ;
    void glLineWidth (float width) const ;
    void glPixelStorei (int pname,int param) const ;
    void glPolygonOffset (float factor,float units) const ;
    void glReadPixels (int x,int y,int width,int height,int format,int type,const void* pixels) const ;
    void glScissor (int x,int y,int width,int height) const ;
    void glStencilFunc (int func,int ref,int mask) const ;
    void glStencilMask (int mask) const ;
    void glStencilOp (int fail,int zfail,int zpass) const ;
    void glTexImage2D (int target,int level,int internalformat,int width,int height,int border,int format,int type,const unsigned char* pixels) const ;
    void glTexParameterf (int target,int pname,float param) const ;
    void glTexSubImage2D (int target,int level,int xoffset,int yoffset,int width,int height,int format,int type,const unsigned char* pixels) const ;
    void glViewport (int x,int y,int width,int height) const ;
    void glAlphaFunc(int func, float ref) const;
    void glClientActiveTexture(int texture) const;
    void glColor4f(float red, float green, float blue, float alpha) const;
    void glColorPointer(int size, int type, int stride, const void* pointer) const;
    void glDeleteTextures(int n, unsigned int* textures) const;
    void glDisableClientState(int array) const;
    void glEnableClientState(int array) const;
    void glFogf(int pname, float param) const;
    void glFogfv(int pname, const float* params) const;
    void glFrustumf(float left, float right, float bottom, float top, float zNear, float zFar) const;
    void glGenTextures(int n, unsigned int* textures) const;
    void glLightf(int light, int pname, float param) const;
    void glLightfv(int light, int pname, const float* params) const;
    void glLightModelf(int pname, float param) const;
    void glLightModelfv(int pname, const float* params) const;
    void glLoadIdentity() const;
    void glLoadMatrixf(const float* m) const;

    void glLogicOp(int opcode) const;

    void glMaterialf(int face, int pname, float param) const;

    void glMaterialfv(int face, int pname, const float* params) const;
    void glMatrixMode(int mode) const;
    void glMultiTexCoord4f(int target, float s, float t, float r, float q) const;
    void glMultMatrixf(const float* m) const;
    void glNormal3f(float nx, float ny, float nz) const;
    void glNormalPointer(int type, int stride, const void* pointer) const;
    void glOrthof(float left, float right, float bottom, float top, float zNear, float zFar) const;

    void glPointSize(float size) const;

    void glPolygonMode(int face, int mode) const;

    void glPopMatrix() const;
    void glPushMatrix() const;

    void glRotatef(float angle, float x, float y, float z) const;
    void glSampleCoverage(float value, bool invert) const;
    void glScalef(float x, float y, float z) const;
    void glShadeModel(int mode) const;
    void glTexCoordPointer(int size, int type, int stride, const void* pointer) const;
    void glTexEnvf(int target, int pname, float param) const;
    void glTexEnvfv(int target, int pname, const float* params) const;
    void glTranslatef(float x, float y, float z) const;
    void glVertexPointer(int size, int type, int stride, const void* pointer) const;
};

}

}

}

#endif // GDX_CPP_BACKENDS_NIX_LINUXGL10_HPP
