
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_VERTEXBUFFEROBJECT_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_VERTEXBUFFEROBJECT_HPP_

#include "VertexData.hpp"
#include "gdx-cpp/graphics/VertexAttributes.hpp"

namespace gdx_cpp {
namespace graphics {
namespace glutils {

class ShaderProgram;

class VertexBufferObject : public VertexData {
public:

    VertexBufferObject (bool isStatic, int numVertices, const gdx_cpp::graphics::VertexAttributes& attributes);
    VertexBufferObject (bool isStatic, int numVertices, const std::vector< gdx_cpp::graphics::VertexAttribute >& attributes);
    
    gdx_cpp::graphics::VertexAttributes& getAttributes ();
    int getNumVertices ();
    int getNumMaxVertices ();
    utils::float_buffer& getBuffer ();
    void setVertices (const float* vertices, int offset, int count);
    void bind ();
    void bind (gdx_cpp::graphics::glutils::ShaderProgram& shader);
    void unbind ();
    void unbind (gdx_cpp::graphics::glutils::ShaderProgram& shader);
    void invalidate ();
    void dispose ();

    int getKind();
    
protected:
    int bufferHandle;
    int tmpHandle;
    bool isDirect;
    int usage;
    bool isDirty;
    graphics::VertexAttributes attributes;
    bool isBound;
    bool isStatic;
    utils::byte_buffer byteBuffer;
    utils::float_buffer buffer;
    
private:
    int createBufferObject ();
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace glutils

#endif // GDX_CPP_GRAPHICS_GLUTILS_VERTEXBUFFEROBJECT_HPP_
