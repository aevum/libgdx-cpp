#include <GL/gl.h>
#include <GL/glu.h>

#include "EmscriptenGLU.hpp"

namespace gdx {
class GL10;
}  // namespace gdx

using namespace gdx::scripten;

void EmscriptenGLU::gluLookAt (const GL10& gl,float eyeX,float eyeY,float eyeZ,float centerX,float centerY,float centerZ,float upX,float upY,float upZ) const {
    ::gluLookAt ( eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

void EmscriptenGLU::gluOrtho2D(const gdx::GL10& gl, float left, float right, float bottom, float top) const {
    ::gluOrtho2D (left, right, bottom, top);
}

bool EmscriptenGLU::gluUnProject(float winX, float winY, float winZ, float* model, float* proj, int* view, float* objX, float* objY, float* objZ) const {
    return ::gluUnProject ((GLdouble) winX, (GLdouble) winY, (GLdouble) winZ,
                    (GLdouble*) model,(GLdouble*) proj,(GLint*) view, (GLdouble*)objX, (GLdouble*)objY, (GLdouble*)objZ);
}
bool EmscriptenGLU::gluProject(float objX, float objY, float objZ, float* model, float* projection, int* view, float* winX, float* winY, float* winZ) const {
    return ::gluProject ((GLdouble) objX, (GLdouble) objY, (GLdouble) objZ,(GLdouble*) model,
                  (GLdouble*) projection,(GLint*) view,(GLdouble*) winX,(GLdouble*) winY,(GLdouble*) winZ);
}
void EmscriptenGLU::gluPerspective(const gdx::GL10& gl, float fovy, float aspect, float zNear, float zFar) const {
    ::gluPerspective ( fovy, aspect, zNear, zFar);
}

