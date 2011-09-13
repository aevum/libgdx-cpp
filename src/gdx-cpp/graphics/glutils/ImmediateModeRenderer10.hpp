
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_IMMEDIATEMODERENDERER10_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_IMMEDIATEMODERENDERER10_HPP_

#include "gdx-cpp/utils/Buffer.hpp"

namespace gdx_cpp {
namespace math {
class Matrix4;
class Vector3;
}
namespace graphics {
namespace glutils {

class ImmediateModeRenderer10 {
public:
    ImmediateModeRenderer10(int maxVertices = 2000);
    ~ImmediateModeRenderer10();
    void begin (gdx_cpp::math::Matrix4& projModelView, int primitiveType);
    void begin (int primitiveType);
    void color (float r,float g,float b,float a);
    void normal (float x,float y,float z);
    void texCoord (float u,float v);
    void vertex (float x,float y,float z);
    int getNumVertices ();
    void end ();
    void vertex (const gdx_cpp::math::Vector3& point);

protected:


private:
    utils::float_buffer allocateBuffer (int numFloats);

    float* positions;
    gdx_cpp::utils::float_buffer  positionsBuffer;
    float* colors;
    gdx_cpp::utils::float_buffer  colorsBuffer;
    float* normals;
    gdx_cpp::utils::float_buffer  normalsBuffer;
    float* texCoords;
    gdx_cpp::utils::float_buffer  texCoordsBuffer;


    int primitiveType;
    int idxPos;
    int idxCols;
    int idxNors;
    int idxTexCoords;

    bool hasCols;
    bool hasNors;
    bool hasTexCoords;
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace glutils

#endif // GDX_CPP_GRAPHICS_GLUTILS_IMMEDIATEMODERENDERER10_HPP_
