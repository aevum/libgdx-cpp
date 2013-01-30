#ifndef GDX_GL_H
#define GDX_GL_H

#include <gdx-cpp/config.hpp>

#ifdef GDX_BACKEND_LINUX

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>

#elif defined GDX_BACKEND_ANDROID

#include <GLES/gl.h>
#include <GLES2/gl2.h>

#elif defined GDX_BACKEND_IOS

#include <OpenGLES/ES1/gl.h>

#else 

#endif

#endif //GDX_GL_H
