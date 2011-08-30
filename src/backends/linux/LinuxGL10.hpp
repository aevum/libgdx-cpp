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

namespace nix {

class LinuxGL10 : public graphics::GL10
{
public:
     void glAlphaFunc (int func,float ref) const ;
     void glClientActiveTexture (int texture) const ;
     void glColor4f (float red,float green,float blue,float alpha) const ;
     void glColorPointer (int size,int type,int stride,const char* pointer) const ;
     void glDeleteTextures (int n,int offset) const ;
     void glDisableClientState (int array) const ;
     void glEnableClientState (int array) const ;
     void glFogf (int pname,float param) const ;
     void glFogfv (int pname,int offset) const ;
     void glFogfv (int pname,const float*& params) const ;
     void glFrustumf (float left,float right,float bottom,float top,float zNear,float zFar) const ;
     void glGenTextures (int n,int offset) const ;
     void glGetIntegerv (int pname,int offset) const ;
     void glLightModelf (int pname,float param) const ;
     void glLightModelfv (int pname,int offset) const ;
     void glLightModelfv (int pname,const float*& params) const ;
     void glLightf (int light,int pname,float param) const ;
     void glLightfv (int light,int pname,int offset) const ;
     void glLightfv (int light,int pname,const float*& params) const ;
     void glLoadIdentity () const ;
     void glLoadMatrixf (float* m, int offset) const ;
     void glLoadMatrixf (const float* m) const ;
     void glLogicOp (int opcode) const ;
     void glMaterialf (int face,int pname,float param) const ;
     void glMaterialfv (int face,int pname,int offset) const ;
     void glMaterialfv (int face,int pname,const float*& params) const ;
     void glMatrixMode (int mode) const ;
     void glMultMatrixf (int offset) const ;
     void glMultMatrixf (const float*& m) const ;
     void glMultiTexCoord4f (int target,float s,float t,float r,float q) const ;
     void glNormal3f (float nx,float ny,float nz) const ;
     void glNormalPointer (int type,int stride,const char* pointer) const ;
     void glOrthof (float left,float right,float bottom,float top,float zNear,float zFar) const ;
     void glPointSize (float size) const ;
     void glPopMatrix () const ;
     void glPushMatrix () const ;
     void glRotatef (float angle,float x,float y,float z) const ;
     void glSampleCoverage (float value,bool invert) const ;
     void glScalef (float x,float y,float z) const ;
     void glShadeModel (int mode) const ;
     void glTexCoordPointer (int size,int type,int stride,const char* pointer) const ;
     void glTexEnvf (int target,int pname,float param) const ;
     void glTexEnvfv (int target,int pname,int offset) const ;
     void glTexEnvfv (int target,int pname,const float*& params) const ;
     void glTranslatef (float x,float y,float z) const ;
     void glVertexPointer (int size,int type,int stride,const char* pointer) const ;
     void glPolygonMode (int face,int mode) const ;
   
};

}

}

}

#endif // GDX_CPP_BACKENDS_NIX_LINUXGL10_HPP
