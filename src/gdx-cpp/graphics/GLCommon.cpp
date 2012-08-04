
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

#include "gdx-cpp/graphics/GLCommon.hpp"
#include "gdx-cpp/gl.hpp"

using namespace gdx;

void GLCommon::glActiveTexture(int texture) const
{
    ::glActiveTexture ( texture);
}

void GLCommon::glBindTexture(int target, int texture) const {
    static unsigned int lastTarget = -1, lastTexture = -1;
    
    if (target != lastTarget && texture != lastTexture) {
        ::glBindTexture ( target, texture);
//         lastTarget = target;
//         lastTexture = texture;
    }
}

void GLCommon::glBlendFunc(int sfactor, int dfactor) const {
    static int lastSfactor = -1, lastDfactor = -1;
    
    if (lastSfactor != sfactor && lastDfactor != dfactor) {
        ::glBlendFunc ( sfactor, dfactor);
        lastDfactor = dfactor;
        lastSfactor = sfactor;
    }
}

void GLCommon::glClear(int mask) const {
    ::glClear ( mask);
}

void GLCommon::glClearColor(float red, float green, float blue, float alpha) const {
    ::glClearColor ( red, green, blue, alpha);
}

void GLCommon::glClearDepthf(float depth) const {
    
    #ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES
    ::glClearDepth ( depth);
    #else
    ::glClearDepthf ( depth);
    #endif
}

void GLCommon::glClearStencil(int s) const {
    ::glClearStencil ( s);
}

void GLCommon::glColorMask(bool red, bool green, bool blue, bool alpha) const {
    ::glColorMask ( red, green, blue, alpha);
}

void GLCommon::glCompressedTexImage2D(int target, int level, int internalformat, int width, int height, int border, int imageSize, const unsigned char* data) const {
    ::glCompressedTexImage2D ( target, level, internalformat, width, height, border, imageSize, data);
}

void GLCommon::glCompressedTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int imageSize, const unsigned char* data) const {
    ::glCompressedTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void GLCommon::glCopyTexImage2D(int target, int level, int internalformat, int x, int y, int width, int height, int border) const {
    ::glCopyTexImage2D ( target, level, internalformat, x, y, width, height, border);
}

void GLCommon::glCopyTexSubImage2D(int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) const {
    ::glCopyTexSubImage2D ( target, level, xoffset, yoffset, x, y, width, height);
}

void GLCommon::glCullFace(int mode) const {
    ::glCullFace ( mode);
}

void GLCommon::glDeleteTextures(int n, const unsigned int* textures) const {
    ::glDeleteTextures ( n, textures);
}

void GLCommon::glDepthFunc(int func) const {
    ::glDepthFunc ( func);
}

void GLCommon::glGenTextures(int n, unsigned int* textures) const {
    ::glGenTextures(n, textures);
}

void GLCommon::glDepthMask(bool flag) const {
    ::glDepthMask ( flag);
}

void GLCommon::glDepthRangef(float zNear, float zFar) const {
    #ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES
    ::glDepthRange ( zNear, zFar);
    #else
    ::glDepthRangef ( zNear, zFar);
    #endif

    
}
void GLCommon::glDisable(int cap) {
    if (enabled_states.count(cap)) {
        enabled_states.erase(cap);
        ::glDisable (cap);
    }
}

void GLCommon::glDrawArrays(int mode, int first, int count) const {
    ::glDrawArrays ( mode, first, count);
}
void GLCommon::glDrawElements(int mode, int count, int type, const void* indices) const {
    ::glDrawElements ( mode, count, type, indices);
}
void GLCommon::glEnable(int cap) {
    if (enabled_states.count(cap) == 0) {
        enabled_states.insert(cap);
        ::glEnable ( cap);
    }
}
void GLCommon::glFinish() const {
    ::glFinish();
}
void GLCommon::glFlush() const {
    ::glFlush();
}
void GLCommon::glFrontFace(int mode) const {
    ::glFrontFace ( mode);
}

int GLCommon::glGetError() const {
    return ::glGetError();
}
void GLCommon::glGetIntegerv(int pname, const int* params) const {
    ::glGetIntegerv ( pname, (GLint*) params);
}
std::string GLCommon::glGetString(int name) const {
    const GLubyte* str = ::glGetString(name);
    if (str)
        return std::string((char*) str);
    return "";
}
void GLCommon::glHint(int target, int mode) const {
    ::glHint ( target, mode);
}
void GLCommon::glLineWidth(float width) const {
    ::glLineWidth ( width);
}
void GLCommon::glPixelStorei(int pname, int param) const {
    ::glPixelStorei ( pname, param);
}
void GLCommon::glPolygonOffset(float factor, float units) const {
    ::glPolygonOffset ( factor, units);
}
void GLCommon::glReadPixels(int x, int y, int width, int height, int format, int type, const void* pixels) const {
    ::glReadPixels ( x, y, width, height, format, type, (GLvoid*) pixels);
}
void GLCommon::glScissor(int x, int y, int width, int height) const {
    ::glScissor ( x, y, width, height);
}
void GLCommon::glStencilFunc(int func, int ref, int mask) const {
    ::glStencilFunc ( func, ref, mask);
}
void GLCommon::glStencilMask(int mask) const {
    ::glStencilMask ( mask);
}
void GLCommon::glStencilOp(int fail, int zfail, int zpass) const {
    ::glStencilOp ( fail, zfail, zpass);
}
void GLCommon::glTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type, const unsigned char* pixels) const {
    ::glTexImage2D ( target, level, internalformat, width, height, border, format, type, pixels);
}
void GLCommon::glTexParameterf(int target, int pname, float param) const {
    ::glTexParameterf ( target, pname, param);
}
void GLCommon::glTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, const unsigned char* pixels) const {
    ::glTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, type, pixels);
}
void GLCommon::glViewport(int x, int y, int width, int height) const {
    ::glViewport ( x, y, width, height);
}

GLCommon::GLCommon() : vertex_states(0) , last_vertex_pointer((void*) -1), last_tex_coord_pointer((void*) -1), last_color_pointer((void*) -1)
{
}

GLCommon::~GLCommon() {
}
