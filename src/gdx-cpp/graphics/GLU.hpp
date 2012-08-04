
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#ifndef GDX_CPP_GRAPHICS_GLU_HPP_
#define GDX_CPP_GRAPHICS_GLU_HPP_

namespace gdx {

class GLU {
public:
    virtual void gluLookAt (const GL10& gl,float eyeX,float eyeY,float eyeZ,float centerX,float centerY,float centerZ,float upX,float upY,float upZ) const = 0;
    virtual void gluOrtho2D (const GL10& gl,float left,float right,float bottom,float top) const = 0;
    virtual void gluPerspective (const GL10& gl,float fovy,float aspect,float zNear,float zFar) const = 0;
    virtual bool gluProject (float objX,float objY,float objZ, float* model, float* projection, int* view, float* winX, float* winY, float* winZ) const = 0;
    virtual bool gluUnProject (float winX,float winY,float winZ,float* model,float* proj, int* view,float* objX,float* objY,float* objZ) const = 0;

    virtual ~GLU() { }
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GLU_HPP_
