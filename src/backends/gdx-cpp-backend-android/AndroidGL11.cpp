
#include "AndroidGL11.hpp"
#include <GLES/gl.h>

using namespace gdx_cpp::backends::android;

void AndroidGL11::glClipPlanef(int plane, const float* equation) const {
    ::glClipPlanef (plane, equation);
}
void AndroidGL11::glGetClipPlanef(int pname, const float* eqn) const {
    ::glGetClipPlanef (pname, (GLfloat*) eqn);
}
void AndroidGL11::glGetFloatv(int pname, const float* params) const {
    ::glGetFloatv (pname, (GLfloat*) params);
}
void AndroidGL11::glGetLightfv(int light, int pname, const float* params) const {
    ::glGetLightfv (light, pname,(GLfloat*) params);
}
void AndroidGL11::glGetMaterialfv(int face, int pname, const float* params) const {
    ::glGetMaterialfv (face, pname, (GLfloat*) params);
}
void AndroidGL11::glGetTexParameterfv(int target, int pname, const float* params) const {
    ::glGetTexParameterfv (target, pname, (GLfloat*) params);
}
void AndroidGL11::glPointParameterf(int pname, float param) const {
    ::glPointParameterf (pname, param);
}

void AndroidGL11::glPointParameterfv (int pname,const float* params) const {
    ::glPointParameterfv ( pname, params);
}
void AndroidGL11::glTexParameterfv (int target,int pname,const float* params) const {
    ::glTexParameterfv (target, pname, params);
}
void AndroidGL11::glBindBuffer (int target,int buffer) const {
    ::glBindBuffer (target, buffer);
}
void AndroidGL11::glBufferData (int target,int size,const char* data,int usage) const {
    ::glBufferData (target, size, data, usage);
}
void AndroidGL11::glBufferSubData (int target,int offset,int size,const void* data) const {
    ::glBufferSubData (target, offset, size, data);
}
void AndroidGL11::glColor4ub (char red,char green,char blue,char alpha) const {
    ::glColor4ub (red, green, blue, alpha);
}
void AndroidGL11::glDeleteBuffers (int n,const int* buffers) const {
    ::glDeleteBuffers (n, (GLuint*)buffers);
}
void AndroidGL11::glGetBooleanv (int pname,const int* params) const {
    ::glGetBooleanv (pname, (GLboolean*) params);
}
void AndroidGL11::glGetBufferParameteriv (int target,int pname,const int* params) const {
    ::glGetBufferParameteriv (target, pname, (GLint*)params);
}
void AndroidGL11::glGenBuffers (int n,const int* buffers) const {
    ::glGenBuffers (n,(GLuint*) buffers);
}
void AndroidGL11::glGetPointerv (int pname) const {
//     ::glGetPointerv (pname);
}
void AndroidGL11::glGetTexEnviv (int env,int pname,const int* params) const {
    ::glGetTexEnviv (env, pname, (GLint*) params);
}
void AndroidGL11::glGetTexParameteriv (int target,int pname,const int* params) const {
    ::glGetTexParameteriv (target, pname, (GLint*) params);
}
bool AndroidGL11::glIsBuffer (int buffer) const {
    ::glIsBuffer (buffer);
}
bool AndroidGL11::glIsEnabled (int cap) const {
    ::glIsEnabled (cap);
}
bool AndroidGL11::glIsTexture (int texture) const {
    ::glIsTexture (texture);
}
void AndroidGL11::glTexEnvi (int target,int pname,int param) const {
    ::glTexEnvi (target, pname, param);
}
void AndroidGL11::glTexEnviv (int target,int pname,const int* params) const {
    ::glTexEnviv (target, pname, params);
}
void AndroidGL11::glTexParameteri (int target,int pname,int param) const {
    ::glTexParameteri (target, pname, param);
}
void AndroidGL11::glTexParameteriv (int target,int pname,const int* params) const {
    ::glTexParameteriv (target, pname, params);
}
void AndroidGL11::glPointSizePointerOES (int type,int stride,const char* pointer) const {
    ::glPointSizePointerOES (type, stride, pointer);
}
void AndroidGL11::glVertexPointer (int size,int type,int stride,void* pointer) const {
    ::glVertexPointer (size, type, stride, (GLvoid*) pointer);
}
void AndroidGL11::glColorPointer (int size,int type,int stride, void* pointer) const {
    ::glColorPointer (size, type, stride, pointer);
}
void AndroidGL11::glNormalPointer (int type,int stride,void* pointer) const {
    ::glNormalPointer (type, stride, pointer);
}
void AndroidGL11::glTexCoordPointer (int size,int type,int stride,void* pointer) const {
    ::glTexCoordPointer (size, type, stride, pointer);
}
void AndroidGL11::glDrawElements (int mode,int count,int type,void* indices) const {
    ::glDrawElements (mode, count, type, indices);
}


