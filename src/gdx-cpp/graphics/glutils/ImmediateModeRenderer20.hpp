
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

namespace gdx_cpp {
namespace graphics {
namespace glutils {

class ImmediateModeRenderer20 {
public:
    std::string& createVertexShader (bool hasNormals,bool hasColors,int numTexCoords);
    void begin (const gdx_cpp::math::Matrix4& projModelView,int primitiveType);
    void begin (const ShaderProgram& shader,int primitiveType);
    void color (float r,float g,float b,float a);
    void texCoord (float u,float v);
    void normal (float x,float y,float z);
    void vertex (float x,float y,float z);
    void end ();
    int getNumVertices ();

protected:


private:
    gdx_cpp::graphics::VertexAttribute* buildVertexAttributes (bool hasNormals,bool hasColor,int numTexCoords);
    std::string& createFragmentShader (bool hasNormals,bool hasColors,int numTexCoords);
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace glutils

#endif // GDX_CPP_GRAPHICS_GLUTILS_IMMEDIATEMODERENDERER20_HPP_

