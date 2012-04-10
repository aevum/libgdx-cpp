#ifndef GDX_GL_H
#define GDX_GL_H

#ifdef LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>

#else

#include <GLES/gl.h>

#endif

#endif //GDX_GL_H