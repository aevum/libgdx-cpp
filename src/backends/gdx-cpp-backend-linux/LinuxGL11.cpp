
#include "LinuxGL11.hpp"

#include <stdexcept>

#ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>

#else

#include <GLES/gl.h>

#endif

using namespace gdx_cpp::backends::nix;

void LinuxGL11::glClipPlanef(int plane, const float* equation) const {
#ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES
    ::glClipPlane (plane, (GLdouble*) equation);
#else
    ::glClipPlanef (plane, (GLfloat*) equation);
#endif
}
void LinuxGL11::glGetClipPlanef(int pname, const float* eqn) const {
#ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES
    ::glGetClipPlane (pname, (GLdouble*) eqn);
#else
    ::glGetClipPlanef (pname, (GLfloat*) eqn);
#endif
}
void LinuxGL11::glGetFloatv(int pname, const float* params) const {
    ::glGetFloatv (pname, (GLfloat*) params);
}
void LinuxGL11::glGetLightfv(int light, int pname, const float* params) const {
    ::glGetLightfv (light, pname,(GLfloat*) params);
}
void LinuxGL11::glGetMaterialfv(int face, int pname, const float* params) const {
    ::glGetMaterialfv (face, pname, (GLfloat*) params);
}
void LinuxGL11::glGetTexParameterfv(int target, int pname, const float* params) const {
    ::glGetTexParameterfv (target, pname, (GLfloat*) params);
}
void LinuxGL11::glPointParameterf(int pname, float param) const {

#ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES
::glPointParameterfARB (pname, param);
#else
    ::glPointParameterf (pname, param);
#endif
}

void LinuxGL11::glPointParameterfv (int pname,const float* params) const {
#ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES
::glPointParameterfvARB ( pname, params);
#else
    ::glPointParameterfv ( pname, params);
#endif
}

void LinuxGL11::glTexParameterfv (int target,int pname,const float* params) const {
    ::glTexParameterfv (target, pname, params);
}

void LinuxGL11::glBindBuffer (int target,int buffer) const {
    ::glBindBuffer (target, buffer);
}

void LinuxGL11::glBufferData (int target,int size,const char* data,int usage) const {
    ::glBufferData (target, size, data, usage);
}

void LinuxGL11::glBufferSubData (int target,int offset,int size,const void* data) const {
    ::glBufferSubData (target, offset, size, data);
}
void LinuxGL11::glColor4ub (char red,char green,char blue,char alpha) const {
    ::glColor4ub (red, green, blue, alpha);
}
void LinuxGL11::glDeleteBuffers (int n,const int* buffers) const {
    ::glDeleteBuffers (n, (GLuint*)buffers);
}
void LinuxGL11::glGetBooleanv (int pname,const int* params) const {
    ::glGetBooleanv (pname, (GLboolean*) params);
}
void LinuxGL11::glGetBufferParameteriv (int target,int pname,const int* params) const {
    ::glGetBufferParameteriv (target, pname, (GLint*)params);
}
void LinuxGL11::glGenBuffers (int n, const int* buffers) const {
    ::glGenBuffers (n, (GLuint*) buffers);
}
void LinuxGL11::glGetPointerv (int pname) const {
//     ::glGetPointerv (pname);
}
void LinuxGL11::glGetTexEnviv (int env,int pname,const int* params) const {
    ::glGetTexEnviv (env, pname, (GLint*) params);
}
void LinuxGL11::glGetTexParameteriv (int target,int pname,const int* params) const {
    ::glGetTexParameteriv (target, pname, (GLint*) params);
}
bool LinuxGL11::glIsBuffer (int buffer) const {
    ::glIsBuffer ( buffer );
}
bool LinuxGL11::glIsEnabled (int cap) const {
    ::glIsEnabled (cap);
}
bool LinuxGL11::glIsTexture (int texture) const {
    ::glIsTexture (texture);
}
void LinuxGL11::glTexEnvi (int target,int pname,int param) const {
    ::glTexEnvi (target, pname, param);
}
void LinuxGL11::glTexEnviv (int target,int pname,const int* params) const {
    ::glTexEnviv (target, pname, params);
}
void LinuxGL11::glTexParameteri (int target,int pname,int param) const {
    ::glTexParameteri (target, pname, param);
}
void LinuxGL11::glTexParameteriv (int target,int pname,const int* params) const {
    ::glTexParameteriv (target, pname, params);
}
void LinuxGL11::glPointSizePointerOES (int type,int stride,const char* pointer) const {
//     ::glPointSize (type, stride, pointer);
}
void LinuxGL11::glVertexPointer (int size,int type,int stride,void* pointer) const {
    ::glVertexPointer (size, type, stride, (GLvoid*) pointer);
}
void LinuxGL11::glColorPointer (int size,int type,int stride, void* pointer) const {
    ::glColorPointer (size, type, stride, pointer);
}
void LinuxGL11::glNormalPointer (int type,int stride,void* pointer) const {
    ::glNormalPointer (type, stride, pointer);
}
void LinuxGL11::glTexCoordPointer (int size,int type,int stride,void* pointer) const {
    ::glTexCoordPointer (size, type, stride, pointer);
}
void LinuxGL11::glDrawElements (int mode,int count,int type,void* indices) const {
    ::glDrawElements (mode, count, type, indices);
}



