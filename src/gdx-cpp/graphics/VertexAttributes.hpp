
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

#ifndef GDX_CPP_GRAPHICS_VERTEXATTRIBUTES_HPP_
#define GDX_CPP_GRAPHICS_VERTEXATTRIBUTES_HPP_

#include <string>
#include <vector>
#include "VertexAttribute.hpp"

namespace gdx_cpp {
namespace graphics {

class VertexAttributes {
public:
    class Usage {
    public:
        const static int Position = 0;
        const static int Color = 1;
        const static int ColorPacked = 5;
        const static int Normal = 2;
        const static int TextureCoordinates = 3;
        const static int Generic = 4;
    };

    VertexAttributes (const std::vector<VertexAttribute>& attributes);
    
    int size ();
    VertexAttribute& get (int index);
    std::string toString ();
    int vertexSize;

private:
    int calculateOffsets ();
    void checkValidity ();
    std::vector<VertexAttribute> attributes;
};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_VERTEXATTRIBUTES_HPP_
