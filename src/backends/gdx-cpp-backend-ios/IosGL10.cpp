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


#include "IosGL10.hpp"

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

using namespace gdx::ios;

void IosGL10::glActiveTexture(int texture) const {
    ::glActiveTexture ( texture);
}
void IosGL10::glBindTexture(int target, int texture) const {
    ::glBindTexture ( target, texture);
}
void IosGL10::glBlendFunc(int sfactor, int dfactor) const {
    ::glBlendFunc ( sfactor, dfactor);
}
void IosGL10::glClear(int mask) const {
    ::glClear ( mask);
}
void IosGL10::glClearColor(float red, float green, float blue, float alpha) const {
    ::glClearColor ( red, green, blue, alpha);
}
void IosGL10::glClearDepthf(float depth) const {

#ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES
    ::glClearDepth ( depth);
#else
    ::glClearDepthf ( depth);
#endif
}
void IosGL10::glClearStencil(int s) const {
    ::glClearStencil ( s);
}
void IosGL10::glColorMask(bool red, bool green, bool blue, bool alpha) const {
    ::glColorMask ( red, green, blue, alpha);
}
void IosGL10::glCompressedTexImage2D(int target, int level, int internalformat, int width, int height, int border, int imageSize, const unsigned char* data) const {
    ::glCompressedTexImage2D ( target, level, internalformat, width, height, border, imageSize, data);
}
void IosGL10::glCompressedTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int imageSize, const unsigned char* data) const {
    ::glCompressedTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, imageSize, data);
}
void IosGL10::glCopyTexImage2D(int target, int level, int internalformat, int x, int y, int width, int height, int border) const {
    ::glCopyTexImage2D ( target, level, internalformat, x, y, width, height, border);
}
void IosGL10::glCopyTexSubImage2D(int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) const {
    ::glCopyTexSubImage2D ( target, level, xoffset, yoffset, x, y, width, height);
}
void IosGL10::glCullFace(int mode) const {
    ::glCullFace ( mode);
}
void IosGL10::glDeleteTextures(int n, const int* textures) const {
    ::glDeleteTextures ( n, (GLuint*) textures);
}
void IosGL10::glDepthFunc(int func) const {
    ::glDepthFunc ( func);
}
void IosGL10::glDepthMask(bool flag) const {
    ::glDepthMask ( flag);
}
void IosGL10::glDepthRangef(float zNear, float zFar) const {
#ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES
    ::glDepthRange ( zNear, zFar);
#else
    ::glDepthRangef ( zNear, zFar);
#endif

}
void IosGL10::glDisable(int cap) const {
    ::glDisable ( cap);
}
void IosGL10::glDrawArrays(int mode, int first, int count) const {
    ::glDrawArrays ( mode, first, count);
}
void IosGL10::glDrawElements(int mode, int count, int type, const void* indices) const {
    ::glDrawElements ( mode, count, type, indices);
}
void IosGL10::glEnable(int cap) const {
    ::glEnable ( cap);
}
void IosGL10::glFinish() const {
    ::glFinish();
}
void IosGL10::glFlush() const {
    ::glFlush();
}
void IosGL10::glFrontFace(int mode) const {
    ::glFrontFace ( mode);
}
void IosGL10::glGenTextures(int n, int* textures) const {
    ::glGenTextures ( n, (GLuint*) textures);
}
int IosGL10::glGetError() const {
    return ::glGetError();
}
void IosGL10::glGetIntegerv(int pname, const int* params) const {
    ::glGetIntegerv ( pname, (GLint*) params);
}
std::string IosGL10::glGetString(int name) const {
    const GLubyte* str = ::glGetString(name);
    if (str)
        return std::string((char*) str);
    return "";
}
void IosGL10::glHint(int target, int mode) const {
    ::glHint ( target, mode);
}
void IosGL10::glLineWidth(float width) const {
    ::glLineWidth ( width);
}
void IosGL10::glPixelStorei(int pname, int param) const {
    ::glPixelStorei ( pname, param);
}
void IosGL10::glPolygonOffset(float factor, float units) const {
    ::glPolygonOffset ( factor, units);
}
void IosGL10::glReadPixels(int x, int y, int width, int height, int format, int type, const void* pixels) const {
    ::glReadPixels ( x, y, width, height, format, type, (GLvoid*) pixels);
}
void IosGL10::glScissor(int x, int y, int width, int height) const {
    ::glScissor ( x, y, width, height);
}
void IosGL10::glStencilFunc(int func, int ref, int mask) const {
    ::glStencilFunc ( func, ref, mask);
}
void IosGL10::glStencilMask(int mask) const {
    ::glStencilMask ( mask);
}
void IosGL10::glStencilOp(int fail, int zfail, int zpass) const {
    ::glStencilOp ( fail, zfail, zpass);
}
void IosGL10::glTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type, const unsigned char* pixels) const {
    ::glTexImage2D ( target, level, internalformat, width, height, border, format, type, pixels);
}
void IosGL10::glTexParameterf(int target, int pname, float param) const {
    ::glTexParameterf ( target, pname, param);
}
void IosGL10::glTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, const unsigned char* pixels) const {
    ::glTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, type, pixels);
}
void IosGL10::glViewport(int x, int y, int width, int height) const {
    ::glViewport ( x, y, width, height);
}

void IosGL10::glAlphaFunc(int func, float ref) const {
    ::glAlphaFunc(func, ref);
}

void IosGL10::glFogfv(int pname, const float* params) const
{
    ::glFogfv(pname, params);
}
void IosGL10::glClientActiveTexture(int texture) const {
    ::glClientActiveTexture(texture);
}
void IosGL10::glColor4f(float red, float green, float blue, float alpha) const {
    ::glColor4f(red, green, blue, alpha);
}
void IosGL10::glColorPointer(int size, int type, int stride, const void* pointer) const {
    ::glColorPointer(size, type, stride, pointer);
}
void IosGL10::glDeleteTextures(int n, unsigned int* textures) const {
    ::glDeleteTextures(n, textures);
}
void IosGL10::glDisableClientState(int array) const {
    ::glDisableClientState(array);
}
void IosGL10::glEnableClientState(int array) const {
    ::glEnableClientState(array);
}
void IosGL10::glFogf(int pname, float param) const {
    ::glFogf(pname, param);
}

void IosGL10::glFrustumf(float left, float right, float bottom, float top, float zNear, float zFar) const {
#ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES
    ::glFrustum(left, right,bottom,top, zNear, zFar);
#else
    ::glFrustumf(left, right,bottom,top, zNear, zFar);
#endif
}

void IosGL10::glGenTextures(int n, unsigned int* textures) const {
    ::glGenTextures(n, textures);
}

void IosGL10::glLightf(int light, int pname, float param) const {
    ::glLightf(light, pname, param);
}

void IosGL10::glLightfv(int light, int pname, const float* params) const {
    ::glLightfv(light,pname,params);
}

void IosGL10::glLightModelf(int pname, float param) const {
    :: glLightModelf(pname, param);
}

void IosGL10::glLightModelfv(int pname, const float* params) const {
    ::glLightModelfv(pname, params);
}

void IosGL10::glLoadIdentity() const {
    ::glLoadIdentity();
}

void IosGL10::glLoadMatrixf(const float* m) const {
    ::glLoadMatrixf(m);
}

void IosGL10::glLogicOp(int opcode) const {
    ::glLogicOp(opcode);
}

void IosGL10::glMaterialf(int face, int pname, float param) const {
    ::glMaterialf(face,pname, param);
}

void IosGL10::glMaterialfv(int face, int pname, const float* params) const {
    ::glMaterialfv(face,pname, params);
}
void IosGL10::glMatrixMode(int mode) const {
    ::glMatrixMode(mode);
}
void IosGL10::glMultiTexCoord4f(int target, float s, float t, float r, float q) const {
    ::glMultiTexCoord4f(target, s, t, r, q);
}
void IosGL10::glMultMatrixf(const float* m) const {
    ::glMultMatrixf(m);
}
void IosGL10::glNormal3f(float nx, float ny, float nz) const {
    ::glNormal3f(nx,ny,nz);
}
void IosGL10::glNormalPointer(int type, int stride, const void* pointer) const {
    ::glNormalPointer(type, stride, pointer);
}
void IosGL10::glOrthof(float left, float right, float bottom, float top, float zNear, float zFar) const {
#ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES
    ::glOrtho(left,right,bottom,top,zNear,zFar);
#else
    ::glOrthof(left,right,bottom,top,zNear,zFar);
#endif
}

void IosGL10::glPointSize(float size) const {
    ::glPointSize(size);
}

void IosGL10::glPolygonMode(int face, int mode) const {
//     ::glPolygonMode(face, mode);
}

void IosGL10::glPopMatrix() const {
    ::glPopMatrix();
}
void IosGL10::glPushMatrix() const {
    ::glPushMatrix();
}

void IosGL10::glRotatef(float angle, float x, float y, float z) const {
    ::glRotatef(angle, x, y, z);
}
void IosGL10::glSampleCoverage(float value, bool invert) const {
    ::glSampleCoverage(value, invert);
}
void IosGL10::glScalef(float x, float y, float z) const {
    ::glScalef(x,y,z);
}
void IosGL10::glShadeModel(int mode) const {
    ::glShadeModel(mode);
}
void IosGL10::glTexCoordPointer(int size, int type, int stride, const void* pointer) const {
    ::glTexCoordPointer(size, type, stride, pointer);
}
void IosGL10::glTexEnvf(int target, int pname, float param) const {
    ::glTexEnvf(target,pname,param);
}
void IosGL10::glTexEnvfv(int target, int pname, const float* params) const {
    ::glTexEnvfv(target, pname, params);
}
void IosGL10::glTranslatef(float x, float y, float z) const {
    ::glTranslatef(x,y , z);
}
void IosGL10::glVertexPointer(int size, int type, int stride, const void* pointer) const {
    ::glVertexPointer(size, type, stride,  pointer);
}
