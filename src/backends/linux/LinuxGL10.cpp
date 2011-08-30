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


#include "LinuxGL10.hpp"

#include <GLES/gl.h>
#include <GLES/glext.h>

using namespace gdx_cpp::backends::nix;

void gdx_cpp::backends::nix::LinuxGL10::glAlphaFunc(int func, float ref) const
{
    glAlphaFunc(func, ref);
}

void gdx_cpp::backends::nix::LinuxGL10::glClientActiveTexture(int texture) const
{
    glClientActiveTexture(texture);
}

void gdx_cpp::backends::nix::LinuxGL10::glColor4f(float red, float green, float blue, float alpha) const
{
    glColor4f(red, green, blue, alpha);
}

void gdx_cpp::backends::nix::LinuxGL10::glColorPointer(int size, int type, int stride, const char* pointer) const
{
    glColorPointer(size, type, stride, pointer);
}

void gdx_cpp::backends::nix::LinuxGL10::glDeleteTextures(int n, int offset) const
{
    glDeleteTextures(n, offset);
}

void gdx_cpp::backends::nix::LinuxGL10::glDisableClientState(int array) const
{
    glDisableClientState(array);
}

void gdx_cpp::backends::nix::LinuxGL10::glEnableClientState(int array) const
{
    glEnableClientState(array);
}
void gdx_cpp::backends::nix::LinuxGL10::glFogf(int pname, float param) const
{
    glFogf(pname, param);
}
void gdx_cpp::backends::nix::LinuxGL10::glFogfv(int pname, int offset) const
{
    glFogfv(pname,offset);
}
void gdx_cpp::backends::nix::LinuxGL10::glFogfv(int pname, const float*& params) const
{
    glFogfv(pname, params);
}
void gdx_cpp::backends::nix::LinuxGL10::glFrustumf(float left, float right, float bottom, float top, float zNear, float zFar) const
{
    glFrustumf(left, right,bottom,top, zNear, zFar);
}
void gdx_cpp::backends::nix::LinuxGL10::glGenTextures(int n, int offset) const
{
    glGenTextures(n, offset);
}

void gdx_cpp::backends::nix::LinuxGL10::glGetIntegerv(int pname, int offset) const
{
    glGetIntegerv(pname, offset);
}

void gdx_cpp::backends::nix::LinuxGL10::glLightf(int light, int pname, float param) const
{
    glLightf(light, pname, param);
}

void gdx_cpp::backends::nix::LinuxGL10::glLightfv(int light, int pname, int offset) const
{
    glLightfv(light, pname, offset);
}

void gdx_cpp::backends::nix::LinuxGL10::glLightfv(int light, int pname, const float*& params) const
{
    glLightfv(light,pname,params);
}
void gdx_cpp::backends::nix::LinuxGL10::glLightModelf(int pname, float param) const
{
    glLightModelf(pname, param);
}
void gdx_cpp::backends::nix::LinuxGL10::glLightModelfv(int pname, int offset) const
{
    glLightModelfv(pname, offset);
}
void gdx_cpp::backends::nix::LinuxGL10::glLightModelfv(int pname, const float*& params) const
{
    glLightModelfv(pname, params);
}
void gdx_cpp::backends::nix::LinuxGL10::glLoadIdentity() const
{
    glLoadIdentity();
}
void gdx_cpp::backends::nix::LinuxGL10::glLoadMatrixf(float* m, int offset) const
{
    glLoadMatrixf(m);
}
void gdx_cpp::backends::nix::LinuxGL10::glLoadMatrixf(const float* m) const
{
    glLoadMatrixf(m);
}

void gdx_cpp::backends::nix::LinuxGL10::glLogicOp(int opcode) const
{
    glLogicOp(opcode);
}

void gdx_cpp::backends::nix::LinuxGL10::glMaterialf(int face, int pname, float param) const
{
    glMaterialf(face,pname, param);
}
void gdx_cpp::backends::nix::LinuxGL10::glMaterialfv(int face, int pname, int offset) const
{
    glMaterialfv(face,pname, offset);
}
void gdx_cpp::backends::nix::LinuxGL10::glMaterialfv(int face, int pname, const float*& params) const
{
    glMaterialfv(face,pname, params);
}
void gdx_cpp::backends::nix::LinuxGL10::glMatrixMode(int mode) const
{
    glMatrixMode(mode);
}
void gdx_cpp::backends::nix::LinuxGL10::glMultiTexCoord4f(int target, float s, float t, float r, float q) const
{
    glMultiTexCoord4f(target, s, t, r, q);
}
void gdx_cpp::backends::nix::LinuxGL10::glMultMatrixf(int offset) const
{
    glMultMatrixf(offset);
}
void gdx_cpp::backends::nix::LinuxGL10::glMultMatrixf(const float*& m) const
{
    glMultMatrixf(m);
}
void gdx_cpp::backends::nix::LinuxGL10::glNormal3f(float nx, float ny, float nz) const
{
    glNormal3f(nx,ny,nz);
}
void gdx_cpp::backends::nix::LinuxGL10::glNormalPointer(int type, int stride, const char* pointer) const
{
    glNormalPointer(type, stride, pointer);
}
void gdx_cpp::backends::nix::LinuxGL10::glOrthof(float left, float right, float bottom, float top, float zNear, float zFar) const
{
    glOrthof(left,right,bottom,top,zNear,zFar);
}
void gdx_cpp::backends::nix::LinuxGL10::glPointSize(float size) const
{
    glPointSize(size);
}
void gdx_cpp::backends::nix::LinuxGL10::glPolygonMode(int face, int mode) const
{
    glPolygonMode(face, mode);
}
void gdx_cpp::backends::nix::LinuxGL10::glPopMatrix() const
{
    glPopMatrix();
}
void gdx_cpp::backends::nix::LinuxGL10::glPushMatrix() const
{
    glPushMatrix();
}

void gdx_cpp::backends::nix::LinuxGL10::glRotatef(float angle, float x, float y, float z) const
{
    glRotatef(angle, x, y, z);
}
void gdx_cpp::backends::nix::LinuxGL10::glSampleCoverage(float value, bool invert) const
{
    glSampleCoverage(value, invert);
}
void gdx_cpp::backends::nix::LinuxGL10::glScalef(float x, float y, float z) const
{
    glScalef(x,y,z);
}
void gdx_cpp::backends::nix::LinuxGL10::glShadeModel(int mode) const
{
    glShadeModel(mode);
}
void gdx_cpp::backends::nix::LinuxGL10::glTexCoordPointer(int size, int type, int stride, const char* pointer) const
{
    glTexCoordPointer(size, type, stride, pointer);
}
void gdx_cpp::backends::nix::LinuxGL10::glTexEnvf(int target, int pname, float param) const
{
    glTexEnvf(target,pname,param);
}
void gdx_cpp::backends::nix::LinuxGL10::glTexEnvfv(int target, int pname, int offset) const
{
    glTexEnvfv(target, pname, offset);
}
void gdx_cpp::backends::nix::LinuxGL10::glTexEnvfv(int target, int pname, const float*& params) const
{
    glTexEnvfv(target, pname, params);
}
void gdx_cpp::backends::nix::LinuxGL10::glTranslatef(float x, float y, float z) const
{
    glTranslatef(x,y , z);
}
void gdx_cpp::backends::nix::LinuxGL10::glVertexPointer(int size, int type, int stride, const char* pointer) const
{
    glVertexPointer(size, type, stride,  pointer);
}



