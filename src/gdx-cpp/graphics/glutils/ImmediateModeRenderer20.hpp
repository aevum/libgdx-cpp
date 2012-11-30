
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_IMMEDIATEMODERENDERER20_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_IMMEDIATEMODERENDERER20_HPP_

#include "ImmediateModeRenderer.hpp"
#include "ShaderProgram.hpp"
#include "gdx-cpp/graphics/Mesh.hpp"

#include <string>
#include <vector>

namespace gdx {
class ImmediateModeRenderer20 : public ImmediateModeRenderer {
public:
    RendererType getRendererType() { return RendererType::IMMEDIATE_GLES20; }
    
    std::string createVertexShader (bool hasNormals, bool hasColors, int numTexCoords);
    void begin (Matrix4& projModelView,int primitiveType);
    void begin (ShaderProgram* shader, int primitiveType);
    void color (float r,float g,float b,float a);
    void texCoord (float u,float v);
    void normal (float x,float y,float z);
    void vertex (float x,float y,float z);
    void end ();
    int getNumVertices ();
    int getMaxVertices ();
    void dispose ();
    
    ImmediateModeRenderer20 (bool hasNormals,bool hasColors,int numTexCoords, int maxVertices = 5000);

protected:
    int primitiveType;
    int vertexIdx;
    int numSetTexCoords;
    int maxVertices;
    int numVertices;
    Mesh mesh;
    int numTexCoords;
    int vertexSize;
    int normalOffset;
    int colorOffset;
    int texCoordOffset ;
    Matrix4 projModelView;
    float* vertices;
    ShaderProgram* customShader ;
    ShaderProgram* defaultShader ;
    std::vector<VertexAttribute> attribs;
    std::string vertexShader;
    std::string fragmentShader;

private:
    std::vector<VertexAttribute> buildVertexAttributes (bool hasNormals,bool hasColor,int numTexCoords);
    std::string createFragmentShader (bool hasNormals, bool hasColors, int numTexCoords);
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GLUTILS_IMMEDIATEMODERENDERER20_HPP_
