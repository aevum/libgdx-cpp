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


#include "AndroidGL10.hpp"

#include <GLES/gl.h>

using namespace gdx_cpp::backends::android;

void AndroidGL10::glActiveTexture(int texture) const {
    ::glActiveTexture ( texture);
}
void AndroidGL10::glBindTexture(int target, int texture) const {
    ::glBindTexture ( target, texture);
}
void AndroidGL10::glBlendFunc(int sfactor, int dfactor) const {
    ::glBlendFunc ( sfactor, dfactor);
}
void AndroidGL10::glClear(int mask) const {
    ::glClear ( mask);
}
void AndroidGL10::glClearColor(float red, float green, float blue, float alpha) const {
    ::glClearColor ( red, green, blue, alpha);
}
void AndroidGL10::glClearDepthf(float depth) const {
    ::glClearDepthf ( depth);
}
void AndroidGL10::glClearStencil(int s) const {
    ::glClearStencil ( s);
}
void AndroidGL10::glColorMask(bool red, bool green, bool blue, bool alpha) const {
    ::glColorMask ( red, green, blue, alpha);
}
void AndroidGL10::glCompressedTexImage2D(int target, int level, int internalformat, int width, int height, int border, int imageSize, const unsigned char* data) const {
    ::glCompressedTexImage2D ( target, level, internalformat, width, height, border, imageSize, data);
}
void AndroidGL10::glCompressedTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int imageSize, const unsigned char* data) const {
    ::glCompressedTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, imageSize, data);
}
void AndroidGL10::glCopyTexImage2D(int target, int level, int internalformat, int x, int y, int width, int height, int border) const {
    ::glCopyTexImage2D ( target, level, internalformat, x, y, width, height, border);
}
void AndroidGL10::glCopyTexSubImage2D(int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) const {
    ::glCopyTexSubImage2D ( target, level, xoffset, yoffset, x, y, width, height);
}
void AndroidGL10::glCullFace(int mode) const {
    ::glCullFace ( mode);
}
void AndroidGL10::glDeleteTextures(int n, const int* textures) const {
    ::glDeleteTextures ( n, (GLuint*) textures);
}
void AndroidGL10::glDepthFunc(int func) const {
    ::glDepthFunc ( func);
}
void AndroidGL10::glDepthMask(bool flag) const {
    ::glDepthMask ( flag);
}
void AndroidGL10::glDepthRangef(float zNear, float zFar) const {
    ::glDepthRangef ( zNear, zFar);
}
void AndroidGL10::glDisable(int cap) const {
    ::glDisable ( cap);
}
void AndroidGL10::glDrawArrays(int mode, int first, int count) const {
    ::glDrawArrays ( mode, first, count);
}
void AndroidGL10::glDrawElements(int mode, int count, int type, const void* indices) const {
    ::glDrawElements ( mode, count, type, indices);
}
void AndroidGL10::glEnable(int cap) const {
    ::glEnable ( cap);
}
void AndroidGL10::glFinish() const {
    ::glFinish();
}
void AndroidGL10::glFlush() const {
    ::glFlush();
}
void AndroidGL10::glFrontFace(int mode) const {
    ::glFrontFace ( mode);
}
void AndroidGL10::glGenTextures(int n, int* textures) const {
    ::glGenTextures ( n, (GLuint*) textures);
}
int AndroidGL10::glGetError() const {
    return ::glGetError();
}
void AndroidGL10::glGetIntegerv(int pname, const int* params) const {
    ::glGetIntegerv ( pname, (GLint*) params);
}
std::string AndroidGL10::glGetString(int name) const {
    const GLubyte* str = ::glGetString(name);
    return std::string((char*)str);
}
void AndroidGL10::glHint(int target, int mode) const {
    ::glHint ( target, mode);
}
void AndroidGL10::glLineWidth(float width) const {
    ::glLineWidth ( width);
}
void AndroidGL10::glPixelStorei(int pname, int param) const {
    ::glPixelStorei ( pname, param);
}
void AndroidGL10::glPolygonOffset(float factor, float units) const {
    ::glPolygonOffset ( factor, units);
}
void AndroidGL10::glReadPixels(int x, int y, int width, int height, int format, int type, const void* pixels) const {
    ::glReadPixels ( x, y, width, height, format, type, (GLvoid*) pixels);
}
void AndroidGL10::glScissor(int x, int y, int width, int height) const {
    ::glScissor ( x, y, width, height);
}
void AndroidGL10::glStencilFunc(int func, int ref, int mask) const {
    ::glStencilFunc ( func, ref, mask);
}
void AndroidGL10::glStencilMask(int mask) const {
    ::glStencilMask ( mask);
}
void AndroidGL10::glStencilOp(int fail, int zfail, int zpass) const {
    ::glStencilOp ( fail, zfail, zpass);
}
void AndroidGL10::glTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type, const unsigned char* pixels) const {
    ::glTexImage2D ( target, level, internalformat, width, height, border, format, type, pixels);
}
void AndroidGL10::glTexParameterf(int target, int pname, float param) const {
    ::glTexParameterf ( target, pname, param);
}
void AndroidGL10::glTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, const unsigned char* pixels) const {
    ::glTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, type, pixels);
}
void AndroidGL10::glViewport(int x, int y, int width, int height) const {
    ::glViewport ( x, y, width, height);
}

void AndroidGL10::glAlphaFunc(int func, float ref) const {
    ::glAlphaFunc(func, ref);
}

void AndroidGL10::glFogfv(int pname, const float* params) const
{
    ::glFogfv(pname, params);
}
void AndroidGL10::glClientActiveTexture(int texture) const {
    ::glClientActiveTexture(texture);
}
void AndroidGL10::glColor4f(float red, float green, float blue, float alpha) const {
    ::glColor4f(red, green, blue, alpha);
}
void AndroidGL10::glColorPointer(int size, int type, int stride, const void* pointer) const {
    ::glColorPointer(size, type, stride, pointer);
}
void AndroidGL10::glDeleteTextures(int n, unsigned int* textures) const {
    ::glDeleteTextures(n, textures);
}
void AndroidGL10::glDisableClientState(int array) const {
    ::glDisableClientState(array);
}
void AndroidGL10::glEnableClientState(int array) const {
    ::glEnableClientState(array);
}
void AndroidGL10::glFogf(int pname, float param) const {
    ::glFogf(pname, param);
}

void AndroidGL10::glFrustumf(float left, float right, float bottom, float top, float zNear, float zFar) const {
    ::glFrustumf(left, right,bottom,top, zNear, zFar);
}

void AndroidGL10::glGenTextures(int n, unsigned int* textures) const {
    ::glGenTextures(n, textures);
}

void AndroidGL10::glLightf(int light, int pname, float param) const {
    ::glLightf(light, pname, param);
}

void AndroidGL10::glLightfv(int light, int pname, const float* params) const {
    ::glLightfv(light,pname,params);
}

void AndroidGL10::glLightModelf(int pname, float param) const {
    :: glLightModelf(pname, param);
}

void AndroidGL10::glLightModelfv(int pname, const float* params) const {
    ::glLightModelfv(pname, params);
}

void AndroidGL10::glLoadIdentity() const {
    ::glLoadIdentity();
}

void AndroidGL10::glLoadMatrixf(const float* m) const {
    ::glLoadMatrixf(m);
}

void AndroidGL10::glLogicOp(int opcode) const {
    ::glLogicOp(opcode);
}

void AndroidGL10::glMaterialf(int face, int pname, float param) const {
    ::glMaterialf(face,pname, param);
}

void AndroidGL10::glMaterialfv(int face, int pname, const float* params) const {
    ::glMaterialfv(face,pname, params);
}
void AndroidGL10::glMatrixMode(int mode) const {
    ::glMatrixMode(mode);
}
void AndroidGL10::glMultiTexCoord4f(int target, float s, float t, float r, float q) const {
    ::glMultiTexCoord4f(target, s, t, r, q);
}
void AndroidGL10::glMultMatrixf(const float* m) const {
    ::glMultMatrixf(m);
}
void AndroidGL10::glNormal3f(float nx, float ny, float nz) const {
    ::glNormal3f(nx,ny,nz);
}
void AndroidGL10::glNormalPointer(int type, int stride, const void* pointer) const {
    ::glNormalPointer(type, stride, pointer);
}
void AndroidGL10::glOrthof(float left, float right, float bottom, float top, float zNear, float zFar) const {
    ::glOrthof(left,right,bottom,top,zNear,zFar);
}

void AndroidGL10::glPointSize(float size) const {
    ::glPointSize(size);
}

void AndroidGL10::glPolygonMode(int face, int mode) const {
//     ::glPolygonMode(face, mode);
}

void AndroidGL10::glPopMatrix() const {
    ::glPopMatrix();
}
void AndroidGL10::glPushMatrix() const {
    ::glPushMatrix();
}

void AndroidGL10::glRotatef(float angle, float x, float y, float z) const {
    ::glRotatef(angle, x, y, z);
}
void AndroidGL10::glSampleCoverage(float value, bool invert) const {
    ::glSampleCoverage(value, invert);
}
void AndroidGL10::glScalef(float x, float y, float z) const {
    ::glScalef(x,y,z);
}
void AndroidGL10::glShadeModel(int mode) const {
    ::glShadeModel(mode);
}
void AndroidGL10::glTexCoordPointer(int size, int type, int stride, const void* pointer) const {
    ::glTexCoordPointer(size, type, stride, pointer);
}
void AndroidGL10::glTexEnvf(int target, int pname, float param) const {
    ::glTexEnvf(target,pname,param);
}
void AndroidGL10::glTexEnvfv(int target, int pname, const float* params) const {
    ::glTexEnvfv(target, pname, params);
}
void AndroidGL10::glTranslatef(float x, float y, float z) const {
    ::glTranslatef(x,y , z);
}
void AndroidGL10::glVertexPointer(int size, int type, int stride, const void* pointer) const {
    ::glVertexPointer(size, type, stride,  pointer);
}
