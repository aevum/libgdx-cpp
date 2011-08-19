
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

#ifndef GDX_CPP_GRAPHICS_GL10_HPP_
#define GDX_CPP_GRAPHICS_GL10_HPP_

namespace gdx_cpp {
namespace graphics {

class GL10 {
public:
    virtual   void glAlphaFunc (int func,float ref) = 0;
    virtual   void glClientActiveTexture (int texture) = 0;
    virtual   void glColor4f (float red,float green,float blue,float alpha) = 0;
    virtual   void glColorPointer (int size,int type,int stride,const Buffer& pointer) = 0;
    virtual   void glDeleteTextures (int n,int offset) = 0;
    virtual   void glDisableClientState (int array) = 0;
    virtual   void glEnableClientState (int array) = 0;
    virtual   void glFogf (int pname,float param) = 0;
    virtual   void glFogfv (int pname,int offset) = 0;
    virtual   void glFogfv (int pname,const FloatBuffer& params) = 0;
    virtual   void glFrustumf (float left,float right,float bottom,float top,float zNear,float zFar) = 0;
    virtual   void glGenTextures (int n,int offset) = 0;
    virtual   void glGetIntegerv (int pname,int offset) = 0;
    virtual   void glLightModelf (int pname,float param) = 0;
    virtual   void glLightModelfv (int pname,int offset) = 0;
    virtual   void glLightModelfv (int pname,const FloatBuffer& params) = 0;
    virtual   void glLightf (int light,int pname,float param) = 0;
    virtual   void glLightfv (int light,int pname,int offset) = 0;
    virtual   void glLightfv (int light,int pname,const FloatBuffer& params) = 0;
    virtual   void glLoadIdentity () = 0;
    virtual   void glLoadMatrixf (int offset) = 0;
    virtual   void glLoadMatrixf (const FloatBuffer& m) = 0;
    virtual   void glLogicOp (int opcode) = 0;
    virtual   void glMaterialf (int face,int pname,float param) = 0;
    virtual   void glMaterialfv (int face,int pname,int offset) = 0;
    virtual   void glMaterialfv (int face,int pname,const FloatBuffer& params) = 0;
    virtual   void glMatrixMode (int mode) = 0;
    virtual   void glMultMatrixf (int offset) = 0;
    virtual   void glMultMatrixf (const FloatBuffer& m) = 0;
    virtual   void glMultiTexCoord4f (int target,float s,float t,float r,float q) = 0;
    virtual   void glNormal3f (float nx,float ny,float nz) = 0;
    virtual   void glNormalPointer (int type,int stride,const Buffer& pointer) = 0;
    virtual   void glOrthof (float left,float right,float bottom,float top,float zNear,float zFar) = 0;
    virtual   void glPointSize (float size) = 0;
    virtual   void glPopMatrix () = 0;
    virtual   void glPushMatrix () = 0;
    virtual   void glRotatef (float angle,float x,float y,float z) = 0;
    virtual   void glSampleCoverage (float value,bool invert) = 0;
    virtual   void glScalef (float x,float y,float z) = 0;
    virtual   void glShadeModel (int mode) = 0;
    virtual   void glTexCoordPointer (int size,int type,int stride,const Buffer& pointer) = 0;
    virtual   void glTexEnvf (int target,int pname,float param) = 0;
    virtual   void glTexEnvfv (int target,int pname,int offset) = 0;
    virtual   void glTexEnvfv (int target,int pname,const FloatBuffer& params) = 0;
    virtual   void glTranslatef (float x,float y,float z) = 0;
    virtual   void glVertexPointer (int size,int type,int stride,const Buffer& pointer) = 0;
    virtual   void glPolygonMode (int face,int mode) = 0;

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_GL10_HPP_
