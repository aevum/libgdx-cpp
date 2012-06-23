/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 * 
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 * 
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 */

#include "GL10.hpp"

#include <gdx-cpp/gl.hpp>

using namespace gdx_cpp::graphics;





void GL10::glAlphaFunc(int func, float ref) const {
    ::glAlphaFunc(func, ref);
}

void GL10::glFogfv(int pname, const float* params) const
{
    ::glFogfv(pname, params);
}
void GL10::glClientActiveTexture(int texture) const {
    static unsigned int lastTexture = -1;
    if (texture != lastTexture) {
        ::glClientActiveTexture(texture);
        lastTexture = texture;
    }
}
void GL10::glColor4f(float red, float green, float blue, float alpha) const {
    static float lastRed = -1, lastGreen = -1, lastBlue = -1, lastAlpha = -1;
    if (red != lastRed && green != lastGreen && blue != lastBlue && alpha != lastAlpha) {
        ::glColor4f(red, green, blue, alpha);
        lastRed = red;
        lastGreen = green;
        lastBlue = blue;
        lastAlpha = alpha;
    }
}
void GL10::glColorPointer(int size, int type, int stride, const void* pointer) {
    if (last_color_pointer != pointer) {
        last_color_pointer = pointer;
        ::glColorPointer(size, type, stride, pointer);
    }
}

void GL10::glDisableClientState(int array) {
    unsigned char state = 0;
    switch(array) {
        case GL_COLOR_ARRAY:
            state = VERTEX_STATE_GL_COLOR_ARRAY;
            break;

#ifdef GL_VERSION_1_3
        case GL_EDGE_FLAG_ARRAY:
            state = VERTEX_STATE_GL_EDGE_FLAG_ARRAY;
            break;
            
        case GL_FOG_COORD_ARRAY:
            state = VERTEX_STATE_GL_FOG_COORD_ARRAY;
            break;
            
        case GL_INDEX_ARRAY:
            state = VERTEX_STATE_GL_INDEX_ARRAY;
            break;            

        case GL_SECONDARY_COLOR_ARRAY:
            state = VERTEX_STATE_GL_SECONDARY_COLOR_ARRAY;
            break;
#endif
        case GL_NORMAL_ARRAY:
            state = VERTEX_STATE_GL_NORMAL_ARRAY;
            break;
            
        case GL_TEXTURE_COORD_ARRAY:
            state = VERTEX_STATE_GL_TEXTURE_COORD_ARRAY;
            break;
        case GL_VERTEX_ARRAY:
            state = VERTEX_STATE_GL_VERTEX_ARRAY;
            break;
    }
    
    if (array == GL_TEXTURE_COORD_ARRAY || (state & vertex_states)) {
        vertex_states &= ~state;
        ::glDisableClientState(array);
    }
}
void GL10::glEnableClientState(int array) {
    unsigned char state = 0;
    switch(array) {
        case GL_COLOR_ARRAY:
            state = VERTEX_STATE_GL_COLOR_ARRAY;
            break;
#ifdef GL_VERSION_1_3
        case GL_EDGE_FLAG_ARRAY:
            state = VERTEX_STATE_GL_EDGE_FLAG_ARRAY;
            break;
            
        case GL_FOG_COORD_ARRAY:
            state = VERTEX_STATE_GL_FOG_COORD_ARRAY;
            break;
            
        case GL_INDEX_ARRAY:
            state = VERTEX_STATE_GL_INDEX_ARRAY;
            break;
            
        case GL_SECONDARY_COLOR_ARRAY:
            state = VERTEX_STATE_GL_SECONDARY_COLOR_ARRAY;
            break;
#endif
        case GL_NORMAL_ARRAY:
            state = VERTEX_STATE_GL_NORMAL_ARRAY;
            break;
        case GL_TEXTURE_COORD_ARRAY:
            state = VERTEX_STATE_GL_TEXTURE_COORD_ARRAY;
            break;
        case GL_VERTEX_ARRAY:
            state = VERTEX_STATE_GL_VERTEX_ARRAY;
            break;
    }
    
    if (array == GL_TEXTURE_COORD_ARRAY || (vertex_states & state) == 0) {
        vertex_states |= state;
        ::glEnableClientState(array);
    }
}
void GL10::glFogf(int pname, float param) const {
    ::glFogf(pname, param);
}

void GL10::glFrustumf(float left, float right, float bottom, float top, float zNear, float zFar) const {
    #ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES
    ::glFrustum(left, right,bottom,top, zNear, zFar);
    #else
    ::glFrustumf(left, right,bottom,top, zNear, zFar);
    #endif
}



void GL10::glLightf(int light, int pname, float param) const {
    ::glLightf(light, pname, param);
}

void GL10::glLightfv(int light, int pname, const float* params) const {
    ::glLightfv(light,pname,params);
}

void GL10::glLightModelf(int pname, float param) const {
    :: glLightModelf(pname, param);
}

void GL10::glLightModelfv(int pname, const float* params) const {
    ::glLightModelfv(pname, params);
}

void GL10::glLoadIdentity() const {
    ::glLoadIdentity();
}

void GL10::glLoadMatrixf(const float* m) const {
    ::glLoadMatrixf(m);
}

void GL10::glLogicOp(int opcode) const {
    ::glLogicOp(opcode);
}

void GL10::glMaterialf(int face, int pname, float param) const {
    ::glMaterialf(face,pname, param);
}

void GL10::glMaterialfv(int face, int pname, const float* params) const {
    ::glMaterialfv(face,pname, params);
}
void GL10::glMatrixMode(int mode) const {
    ::glMatrixMode(mode);
}
void GL10::glMultiTexCoord4f(int target, float s, float t, float r, float q) const {
    ::glMultiTexCoord4f(target, s, t, r, q);
}
void GL10::glMultMatrixf(const float* m) const {
    ::glMultMatrixf(m);
}
void GL10::glNormal3f(float nx, float ny, float nz) const {
    ::glNormal3f(nx,ny,nz);
}
void GL10::glNormalPointer(int type, int stride, const void* pointer) const {
    ::glNormalPointer(type, stride, pointer);
}
void GL10::glOrthof(float left, float right, float bottom, float top, float zNear, float zFar) const {
    #ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES
    ::glOrtho(left,right,bottom,top,zNear,zFar);
    #else
    ::glOrthof(left,right,bottom,top,zNear,zFar);
    #endif
}

void GL10::glPointSize(float size) const {
    ::glPointSize(size);
}

void GL10::glPolygonMode(int face, int mode) const {
    //     ::glPolygonMode(face, mode);
}

void GL10::glPopMatrix() const {
    ::glPopMatrix();
}
void GL10::glPushMatrix() const {
    ::glPushMatrix();
}

void GL10::glRotatef(float angle, float x, float y, float z) const {
    ::glRotatef(angle, x, y, z);
}
void GL10::glSampleCoverage(float value, bool invert) const {
    ::glSampleCoverage(value, invert);
}
void GL10::glScalef(float x, float y, float z) const {
    ::glScalef(x,y,z);
}
void GL10::glShadeModel(int mode) const {
    ::glShadeModel(mode);
}
void GL10::glTexCoordPointer(int size, int type, int stride, const void* pointer) {
    if (last_tex_coord_pointer != pointer) {
        last_tex_coord_pointer = pointer;
        ::glTexCoordPointer(size, type, stride, pointer);
    }
}
void GL10::glTexEnvf(int target, int pname, float param) const {
    ::glTexEnvf(target,pname,param);
}
void GL10::glTexEnvfv(int target, int pname, const float* params) const {
    ::glTexEnvfv(target, pname, params);
}
void GL10::glTranslatef(float x, float y, float z) const {
    ::glTranslatef(x,y , z);
}
void GL10::glVertexPointer(int size, int type, int stride, const void* pointer) {
    if (pointer != last_vertex_pointer) {
        last_vertex_pointer = pointer;
        ::glVertexPointer(size, type, stride,  pointer);
    }
}
