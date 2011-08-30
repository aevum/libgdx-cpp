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

void LinuxGL10::glActiveTexture(int texture) const {
    ::glActiveTexture ( texture);
}
void LinuxGL10::glBindTexture(int target, int texture) const {
    ::glBindTexture ( target, texture);
}
void LinuxGL10::glBlendFunc(int sfactor, int dfactor) const {
    ::glBlendFunc ( sfactor, dfactor);
}
void LinuxGL10::glClear(int mask) const {
    ::glClear ( mask);
}
void LinuxGL10::glClearColor(float red, float green, float blue, float alpha) const {
    ::glClearColor ( red, green, blue, alpha);
}
void LinuxGL10::glClearDepthf(float depth) const {
    ::glClearDepthf ( depth);
}
void LinuxGL10::glClearStencil(int s) const {
    ::glClearStencil ( s);
}
void LinuxGL10::glColorMask(bool red, bool green, bool blue, bool alpha) const {
    ::glColorMask ( red, green, blue, alpha);
}
void LinuxGL10::glCompressedTexImage2D(int target, int level, int internalformat, int width, int height, int border, int imageSize, const unsigned char* data) const {
    ::glCompressedTexImage2D ( target, level, internalformat, width, height, border, imageSize, data);
}
void LinuxGL10::glCompressedTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int imageSize, const unsigned char* data) const {
    ::glCompressedTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, imageSize, data);
}
void LinuxGL10::glCopyTexImage2D(int target, int level, int internalformat, int x, int y, int width, int height, int border) const {
    ::glCopyTexImage2D ( target, level, internalformat, x, y, width, height, border);
}
void LinuxGL10::glCopyTexSubImage2D(int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) const {
    ::glCopyTexSubImage2D ( target, level, xoffset, yoffset, x, y, width, height);
}
void LinuxGL10::glCullFace(int mode) const {
    ::glCullFace ( mode);
}
void LinuxGL10::glDeleteTextures(int n, const int* textures) const {
    ::glDeleteTextures ( n, (GLuint*) textures);
}
void LinuxGL10::glDepthFunc(int func) const {
    ::glDepthFunc ( func);
}
void LinuxGL10::glDepthMask(bool flag) const {
    ::glDepthMask ( flag);
}
void LinuxGL10::glDepthRangef(float zNear, float zFar) const {
    ::glDepthRangef ( zNear, zFar);
}
void LinuxGL10::glDisable(int cap) const {
    ::glDisable ( cap);
}
void LinuxGL10::glDrawArrays(int mode, int first, int count) const {
    ::glDrawArrays ( mode, first, count);
}
void LinuxGL10::glDrawElements(int mode, int count, int type, const void* indices) const {
    ::glDrawElements ( mode, count, type, indices);
}
void LinuxGL10::glEnable(int cap) const {
    ::glEnable ( cap);
}
void LinuxGL10::glFinish() const {
    ::glFinish();
}
void LinuxGL10::glFlush() const {
    ::glFlush();
}
void LinuxGL10::glFrontFace(int mode) const {
    ::glFrontFace ( mode);
}
void LinuxGL10::glGenTextures(int n, int* textures) const {
    ::glGenTextures ( n, (GLuint*) textures);
}
int LinuxGL10::glGetError() const {
    return ::glGetError();
}
void LinuxGL10::glGetIntegerv(int pname, const int* params) const {
    ::glGetIntegerv ( pname, (GLint*) params);
}
std::string& LinuxGL10::glGetString(int name) const {
    ::glGetString(name);
}
void LinuxGL10::glHint(int target, int mode) const {
    ::glHint ( target, mode);
}
void LinuxGL10::glLineWidth(float width) const {
    ::glLineWidth ( width);
}
void LinuxGL10::glPixelStorei(int pname, int param) const {
    ::glPixelStorei ( pname, param);
}
void LinuxGL10::glPolygonOffset(float factor, float units) const {
    ::glPolygonOffset ( factor, units);
}
void LinuxGL10::glReadPixels(int x, int y, int width, int height, int format, int type, const void* pixels) const {
    ::glReadPixels ( x, y, width, height, format, type, (GLvoid*) pixels);
}
void LinuxGL10::glScissor(int x, int y, int width, int height) const {
    ::glScissor ( x, y, width, height);
}
void LinuxGL10::glStencilFunc(int func, int ref, int mask) const {
    ::glStencilFunc ( func, ref, mask);
}
void LinuxGL10::glStencilMask(int mask) const {
    ::glStencilMask ( mask);
}
void LinuxGL10::glStencilOp(int fail, int zfail, int zpass) const {
    ::glStencilOp ( fail, zfail, zpass);
}
void LinuxGL10::glTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type, const unsigned char* pixels) const {
    ::glTexImage2D ( target, level, internalformat, width, height, border, format, type, pixels);
}
void LinuxGL10::glTexParameterf(int target, int pname, float param) const {
    ::glTexParameterf ( target, pname, param);
}
void LinuxGL10::glTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, const unsigned char* pixels) const {
    ::glTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, type, pixels);
}
void LinuxGL10::glViewport(int x, int y, int width, int height) const {
    ::glViewport ( x, y, width, height);
}

void LinuxGL10::glAlphaFunc(int func, float ref) const {
    ::glAlphaFunc(func, ref);
}

void LinuxGL10::glFogfv(int pname, const float* params) const
{
    ::glFogfv(pname, params);
}
void LinuxGL10::glClientActiveTexture(int texture) const {
    ::glClientActiveTexture(texture);
}
void LinuxGL10::glColor4f(float red, float green, float blue, float alpha) const {
    ::glColor4f(red, green, blue, alpha);
}
void LinuxGL10::glColorPointer(int size, int type, int stride, const char* pointer) const {
    ::glColorPointer(size, type, stride, pointer);
}
void LinuxGL10::glDeleteTextures(int n, unsigned int* textures) const {
    ::glDeleteTextures(n, textures);
}
void LinuxGL10::glDisableClientState(int array) const {
    ::glDisableClientState(array);
}
void LinuxGL10::glEnableClientState(int array) const {
    ::glEnableClientState(array);
}
void LinuxGL10::glFogf(int pname, float param) const {
    ::glFogf(pname, param);
}

void LinuxGL10::glFrustumf(float left, float right, float bottom, float top, float zNear, float zFar) const {
    ::glFrustumf(left, right,bottom,top, zNear, zFar);
}

void LinuxGL10::glGenTextures(int n, unsigned int* textures) const {
    ::glGenTextures(n, textures);
}

void LinuxGL10::glLightf(int light, int pname, float param) const {
    ::glLightf(light, pname, param);
}

void LinuxGL10::glLightfv(int light, int pname, const float* params) const {
    ::glLightfv(light,pname,params);
}

void LinuxGL10::glLightModelf(int pname, float param) const {
    :: glLightModelf(pname, param);
}

void LinuxGL10::glLightModelfv(int pname, const float* params) const {
    ::glLightModelfv(pname, params);
}

void LinuxGL10::glLoadIdentity() const {
    ::glLoadIdentity();
}

void LinuxGL10::glLoadMatrixf(const float* m) const {
    ::glLoadMatrixf(m);
}

void LinuxGL10::glLogicOp(int opcode) const {
    ::glLogicOp(opcode);
}

void LinuxGL10::glMaterialf(int face, int pname, float param) const {
    ::glMaterialf(face,pname, param);
}

void LinuxGL10::glMaterialfv(int face, int pname, const float* params) const {
    ::glMaterialfv(face,pname, params);
}
void LinuxGL10::glMatrixMode(int mode) const {
    ::glMatrixMode(mode);
}
void LinuxGL10::glMultiTexCoord4f(int target, float s, float t, float r, float q) const {
    ::glMultiTexCoord4f(target, s, t, r, q);
}
void LinuxGL10::glMultMatrixf(const float* m) const {
    ::glMultMatrixf(m);
}
void LinuxGL10::glNormal3f(float nx, float ny, float nz) const {
    ::glNormal3f(nx,ny,nz);
}
void LinuxGL10::glNormalPointer(int type, int stride, const char* pointer) const {
    ::glNormalPointer(type, stride, pointer);
}
void LinuxGL10::glOrthof(float left, float right, float bottom, float top, float zNear, float zFar) const {
    ::glOrthof(left,right,bottom,top,zNear,zFar);
}

void LinuxGL10::glPointSize(float size) const {
    ::glPointSize(size);
}

void LinuxGL10::glPolygonMode(int face, int mode) const {
//     ::glPolygonMode(face, mode);
}

void LinuxGL10::glPopMatrix() const {
    ::glPopMatrix();
}
void LinuxGL10::glPushMatrix() const {
    ::glPushMatrix();
}

void LinuxGL10::glRotatef(float angle, float x, float y, float z) const {
    ::glRotatef(angle, x, y, z);
}
void LinuxGL10::glSampleCoverage(float value, bool invert) const {
    ::glSampleCoverage(value, invert);
}
void LinuxGL10::glScalef(float x, float y, float z) const {
    ::glScalef(x,y,z);
}
void LinuxGL10::glShadeModel(int mode) const {
    ::glShadeModel(mode);
}
void LinuxGL10::glTexCoordPointer(int size, int type, int stride, const char* pointer) const {
    ::glTexCoordPointer(size, type, stride, pointer);
}
void LinuxGL10::glTexEnvf(int target, int pname, float param) const {
    ::glTexEnvf(target,pname,param);
}
void LinuxGL10::glTexEnvfv(int target, int pname, const float* params) const {
    ::glTexEnvfv(target, pname, params);
}
void LinuxGL10::glTranslatef(float x, float y, float z) const {
    ::glTranslatef(x,y , z);
}
void LinuxGL10::glVertexPointer(int size, int type, int stride, const char* pointer) const {
    ::glVertexPointer(size, type, stride,  pointer);
}
