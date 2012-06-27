
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_VERTEXDATA_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_VERTEXDATA_HPP_

#include <vector>

#include "gdx-cpp/utils/Disposable.hpp"
#include "gdx-cpp/utils/Buffer.hpp"
#include "gdx-cpp/graphics/VertexAttributes.hpp"

namespace gdx {

class VertexData: public Disposable {
public:
    struct Kind {
        static const int VertexBufferObject = 0;
        static const int Other = 1;
    };

    virtual int getKind() {
        return Kind::Other;
    }
    
    virtual int getNumVertices () = 0;
    virtual int getNumMaxVertices () = 0;
    virtual VertexAttributes& getAttributes () = 0;
    virtual void setVertices (const float* vertices, int offset,int count) = 0;
    virtual float_buffer& getBuffer () = 0;
    virtual void bind () = 0;
    virtual void unbind () = 0;
    virtual void dispose () = 0;

};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GLUTILS_VERTEXDATA_HPP_
