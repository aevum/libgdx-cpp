
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_VERTEXARRAY_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_VERTEXARRAY_HPP_

#include "VertexData.hpp"

namespace gdx_cpp {
namespace graphics {
namespace glutils {

class VertexArray : public VertexData {
public:

    VertexArray (int numVertices, const gdx_cpp::graphics::VertexAttributes& attributes) ;
    
    void dispose ();
    utils::float_buffer& getBuffer ();
    int getNumVertices ();
    int getNumMaxVertices ();
    void setVertices (const float* vertices, int offset, int count);
    void bind ();
    void unbind ();
    gdx_cpp::graphics::VertexAttributes& getAttributes ();

protected:

    VertexAttributes attributes;
    utils::float_buffer buffer;
    utils::byte_buffer byteBuffer;
    bool isBound;
private:

};

} // namespace gdx_cpp
} // namespace graphics
} // namespace glutils

#endif // GDX_CPP_GRAPHICS_GLUTILS_VERTEXARRAY_HPP_
