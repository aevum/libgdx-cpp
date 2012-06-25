#ifndef GDX_GL_H
#define GDX_GL_H

/* #undef GDX_BACKEND_IOS */
#define GDX_BACKEND_LINUX
/* #undef GDX_BACKEND_ANDROID */
/* #undef GDX_BACKEND_WIN32 */

#ifdef GDX_BACKEND_LINUX
#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>

#elif defined GDX_BACKEND_ANDROID

#include <GLES/gl.h>

#elif defined GDX_BACKEND_IOS

#include <OpenGLES/ES1/gl.h>

#else 

#endif

#endif //GDX_GL_H
