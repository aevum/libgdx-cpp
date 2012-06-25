
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_VERTEXBUFFEROBJECTSUBDATA_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_VERTEXBUFFEROBJECTSUBDATA_HPP_

#include "VertexData.hpp"

class tm;
namespace gdx {
class ShaderProgram;


class VertexBufferObjectSubData : public VertexData {
public:

    VertexBufferObjectSubData (bool isStatic, int numVertices, const std::vector<VertexAttribute>& attributes) ;
        
    VertexAttributes& getAttributes ();
    int getNumVertices ();
    int getNumMaxVertices ();
    void setVertices(const float* vertices, int offset,int count);

    float_buffer& getBuffer();
    void bind ();
    void bind (ShaderProgram& shader);
    void unbind ();
    void unbind (ShaderProgram& shader);
    void invalidate ();
    void dispose ();
    int getBufferHandle ();

protected:
    VertexAttributes attributes;
    float_buffer buffer;
    byte_buffer byteBuffer;
    
    int bufferHandle;
    bool isDirect;
    bool isStatic;
    int usage;
    bool isDirty;
    bool isBound;
    int tmpHandle;
private:
    int createBufferObject ();
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GLUTILS_VERTEXBUFFEROBJECTSUBDATA_HPP_
