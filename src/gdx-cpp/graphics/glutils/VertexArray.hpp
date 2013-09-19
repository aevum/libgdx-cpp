
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
#include "gdx-cpp/graphics/VertexAttributes.hpp"
#include "gdx-cpp/utils/Buffer.hpp"

namespace gdx {

class VertexArray : public VertexData {
public:

    VertexArray (int numVertices, VertexAttributes  attributes) ;
    
    void dispose () override;
    float_buffer& getBuffer () override;
    int getNumVertices () override;
    int getNumMaxVertices () override;
    void setVertices (const float* vertices, int offset, int count) override;
    void bind () override;
    void unbind () override;
    VertexAttributes& getAttributes () override;

protected:

    VertexAttributes attributes;
    float_buffer buffer;
    byte_buffer byteBuffer;
    bool isBound;
private:

};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GLUTILS_VERTEXARRAY_HPP_
