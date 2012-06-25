
#include "IosGL11.hpp"

#include <stdexcept>

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

using namespace gdx::ios;

void IosGL11::glClipPlanef(int plane, const float* equation) const {
    ::glClipPlanef (plane, (GLfloat*) equation);
}
void IosGL11::glGetClipPlanef(int pname, const float* eqn) const {
    ::glGetClipPlanef (pname, (GLfloat*) eqn);
}
void IosGL11::glGetFloatv(int pname, const float* params) const {
    ::glGetFloatv (pname, (GLfloat*) params);
}
void IosGL11::glGetLightfv(int light, int pname, const float* params) const {
    ::glGetLightfv (light, pname,(GLfloat*) params);
}
void IosGL11::glGetMaterialfv(int face, int pname, const float* params) const {
    ::glGetMaterialfv (face, pname, (GLfloat*) params);
}
void IosGL11::glGetTexParameterfv(int target, int pname, const float* params) const {
    ::glGetTexParameterfv (target, pname, (GLfloat*) params);
}
void IosGL11::glPointParameterf(int pname, float param) const {
    ::glPointParameterf (pname, param);
}

void IosGL11::glPointParameterfv (int pname,const float* params) const {
    ::glPointParameterfv ( pname, params);
}

void IosGL11::glTexParameterfv (int target,int pname,const float* params) const {
    ::glTexParameterfv (target, pname, params);
}

void IosGL11::glBindBuffer (int target,int buffer) const {
    ::glBindBuffer (target, buffer);
}

void IosGL11::glBufferData (int target,int size,const char* data,int usage) const {
    ::glBufferData (target, size, data, usage);
}

void IosGL11::glBufferSubData (int target,int offset,int size,const void* data) const {
    ::glBufferSubData (target, offset, size, data);
}
void IosGL11::glColor4ub (char red,char green,char blue,char alpha) const {
    ::glColor4ub (red, green, blue, alpha);
}
void IosGL11::glDeleteBuffers (int n,const int* buffers) const {
    ::glDeleteBuffers (n, (GLuint*)buffers);
}
void IosGL11::glGetBooleanv (int pname,const int* params) const {
    ::glGetBooleanv (pname, (GLboolean*) params);
}
void IosGL11::glGetBufferParameteriv (int target,int pname,const int* params) const {
    ::glGetBufferParameteriv (target, pname, (GLint*)params);
}
void IosGL11::glGenBuffers (int n, const int* buffers) const {
    ::glGenBuffers (n, (GLuint*) buffers);
}
void IosGL11::glGetPointerv (int pname) const {
//     ::glGetPointerv (pname);
}
void IosGL11::glGetTexEnviv (int env,int pname,const int* params) const {
    ::glGetTexEnviv (env, pname, (GLint*) params);
}
void IosGL11::glGetTexParameteriv (int target,int pname,const int* params) const {
    ::glGetTexParameteriv (target, pname, (GLint*) params);
}
bool IosGL11::glIsBuffer (int buffer) const {
    return ::glIsBuffer ( buffer );
}
bool IosGL11::glIsEnabled (int cap) const {
    return ::glIsEnabled (cap);
}
bool IosGL11::glIsTexture (int texture) const {
    return ::glIsTexture (texture);
}
void IosGL11::glTexEnvi (int target,int pname,int param) const {
    ::glTexEnvi (target, pname, param);
}
void IosGL11::glTexEnviv (int target,int pname,const int* params) const {
    ::glTexEnviv (target, pname, params);
}
void IosGL11::glTexParameteri (int target,int pname,int param) const {
    ::glTexParameteri (target, pname, param);
}
void IosGL11::glTexParameteriv (int target,int pname,const int* params) const {
    ::glTexParameteriv (target, pname, params);
}
void IosGL11::glPointSizePointerOES (int type,int stride,const char* pointer) const {
//     ::glPointSize (type, stride, pointer);
}
void IosGL11::glVertexPointer (int size,int type,int stride,void* pointer) const {
    ::glVertexPointer (size, type, stride, (GLvoid*) pointer);
}
void IosGL11::glColorPointer (int size,int type,int stride, void* pointer) const {
    ::glColorPointer (size, type, stride, pointer);
}
void IosGL11::glNormalPointer (int type,int stride,void* pointer) const {
    ::glNormalPointer (type, stride, pointer);
}
void IosGL11::glTexCoordPointer (int size,int type,int stride,void* pointer) const {
    ::glTexCoordPointer (size, type, stride, pointer);
}
void IosGL11::glDrawElements (int mode,int count,int type,void* indices) const {
    ::glDrawElements (mode, count, type, indices);
}



