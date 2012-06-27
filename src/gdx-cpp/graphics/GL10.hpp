
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

#include "GLCommon.hpp"
#include <set>

namespace gdx {

class GL10 : virtual public GLCommon {
public:
    enum VertexStates {
        VERTEX_STATE_GL_COLOR_ARRAY = 1 << 0,
        VERTEX_STATE_GL_EDGE_FLAG_ARRAY = 1 << 1,
        VERTEX_STATE_GL_FOG_COORD_ARRAY = 1 << 2,
        VERTEX_STATE_GL_INDEX_ARRAY = 1 << 3,
        VERTEX_STATE_GL_NORMAL_ARRAY = 1 << 4,
        VERTEX_STATE_GL_SECONDARY_COLOR_ARRAY = 1 << 5,
        VERTEX_STATE_GL_TEXTURE_COORD_ARRAY = 1 << 6,
        VERTEX_STATE_GL_VERTEX_ARRAY = 1 << 7
    };
    
    virtual void glAlphaFunc (int func,float ref) const ;
    virtual void glClientActiveTexture (int texture) const ;
    virtual void glColor4f (float red,float green,float blue,float alpha) const ;
    virtual void glColorPointer (int size,int type,int stride,const void* pointer) ;
    virtual void glDisableClientState (int array) ;
    virtual void glEnableClientState (int array) ;
    virtual void glFogf (int pname,float param) const ;
    virtual void glFogfv (int pname,const float* params) const ;
    virtual void glFrustumf (float left,float right,float bottom,float top,float zNear,float zFar) const ;
    virtual void glLightModelf (int pname,float param) const ;
    virtual void glLightModelfv (int pname,const float* params) const ;
    virtual void glLightf (int light,int pname,float param) const ;
    virtual void glLightfv (int light,int pname,const float* params) const ;
    virtual void glLoadIdentity () const ;
    virtual void glLoadMatrixf (const float* m) const ;
    virtual void glLogicOp (int opcode) const ;
    virtual void glMaterialf (int face,int pname,float param) const ;
    virtual void glMaterialfv (int face,int pname,const float* params) const ;
    virtual void glMatrixMode (int mode) const ;
    virtual void glMultMatrixf (const float* m) const ;
    virtual void glMultiTexCoord4f (int target,float s,float t,float r,float q) const ;
    virtual void glNormal3f (float nx,float ny,float nz) const ;
    virtual void glNormalPointer (int type,int stride,const void* pointer) const ;
    virtual void glOrthof (float left,float right,float bottom,float top,float zNear,float zFar) const ;
    virtual void glPointSize (float size) const ;
    virtual void glPopMatrix () const ;
    virtual void glPushMatrix () const ;
    virtual void glRotatef (float angle,float x,float y,float z) const ;
    virtual void glSampleCoverage (float value,bool invert) const ;
    virtual void glScalef (float x,float y,float z) const ;
    virtual void glShadeModel (int mode) const ;
    virtual void glTexCoordPointer (int size,int type,int stride,const void * pointer) ;
    virtual void glTexEnvf (int target,int pname,float param) const ;
    virtual void glTexEnvfv (int target,int pname,const float* params) const ;
    virtual void glTranslatef (float x,float y,float z) const ;
    virtual void glVertexPointer (int size,int type,int stride,const void* pointer) ;
    virtual void glPolygonMode (int face,int mode) const ;
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GL10_HPP_
