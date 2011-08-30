
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

#include "VertexArray.hpp"

#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/graphics/GL10.hpp"
#include "gdx-cpp/graphics/GL11.hpp"

using namespace gdx_cpp::graphics::glutils;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

void VertexArray::dispose () {
}

utils::float_buffer& VertexArray::getBuffer () {
    return buffer;
}

int VertexArray::getNumVertices () {
    return buffer.limit() * 4 / attributes.vertexSize;
}

int VertexArray::getNumMaxVertices () {
    return byteBuffer.capacity() / attributes.vertexSize;
}

void VertexArray::setVertices (const std::vector< float >& vertices, int offset, int count) {
    byteBuffer.copy(vertices, count, offset);
    buffer.position(0);
    buffer.limit(count);
}

void VertexArray::bind () {
    GL10& gl = *Gdx::gl10;
    int textureUnit = 0;
    int numAttributes = attributes.size();

    byteBuffer.limit(buffer.limit() * 4);

    for (int i = 0; i < numAttributes; i++) {
        VertexAttribute& attribute = attributes.get(i);

        switch (attribute.usage) {
        case VertexAttributes::Usage::Position:
            byteBuffer.position(attribute.offset);
            gl.glEnableClientState(GL11::GL_VERTEX_ARRAY);
            gl.glVertexPointer(attribute.numComponents, GL10::GL_FLOAT, attributes.vertexSize, byteBuffer);
            break;

        case VertexAttributes::Usage::Color:
        case VertexAttributes::Usage::ColorPacked:
        {
            int colorType = GL10::GL_FLOAT;
            if (attribute.usage == VertexAttributes::Usage::ColorPacked) colorType = GL11::GL_UNSIGNED_BYTE;
            byteBuffer.position(attribute.offset);
            gl.glEnableClientState(GL10::GL_COLOR_ARRAY);
            gl.glColorPointer(attribute.numComponents, colorType, attributes.vertexSize, byteBuffer);
            break;
        }
        case VertexAttributes::Usage::Normal:
            byteBuffer.position(attribute.offset);
            gl.glEnableClientState(GL10::GL_NORMAL_ARRAY);
            gl.glNormalPointer(GL10::GL_FLOAT, attributes.vertexSize, byteBuffer);
            break;

        case VertexAttributes::Usage::TextureCoordinates:
            gl.glClientActiveTexture(GL10::GL_TEXTURE0 + textureUnit);
            gl.glEnableClientState(GL10::GL_TEXTURE_COORD_ARRAY);
            byteBuffer.position(attribute.offset);
            gl.glTexCoordPointer(attribute.numComponents, GL10::GL_FLOAT, attributes.vertexSize, byteBuffer);
            textureUnit++;
            break;

        default:
            break;
            // throw new GdxRuntimeException("unkown vertex attribute type: " + attribute.usage);
        }
    }

    isBound = true;
}

void VertexArray::unbind () {
    GL10& gl = *Gdx::gl10;
    int textureUnit = 0;
    int numAttributes = attributes.size();

    for (int i = 0; i < numAttributes; i++) {

        VertexAttribute& attribute = attributes.get(i);
        switch (attribute.usage) {
        case VertexAttributes::Usage::Position:
            break; // no-op, we also need a position bound in gles
        case VertexAttributes::Usage::Color:
        case VertexAttributes::Usage::ColorPacked:
            gl.glDisableClientState(GL11::GL_COLOR_ARRAY);
            break;
        case VertexAttributes::Usage::Normal:
            gl.glDisableClientState(GL11::GL_NORMAL_ARRAY);
            break;
        case VertexAttributes::Usage::TextureCoordinates:
            gl.glClientActiveTexture(GL11::GL_TEXTURE0 + textureUnit);
            gl.glDisableClientState(GL11::GL_TEXTURE_COORD_ARRAY);
            textureUnit++;
            break;
        default:
            break;
            // throw new GdxRuntimeException("unkown vertex attribute type: " + attribute.usage);
        }
    }
    byteBuffer.position(0);
    isBound = false;
}

gdx_cpp::graphics::VertexAttributes& VertexArray::getAttributes () {
    return attributes;
}

VertexArray::VertexArray(int numVertices, const gdx_cpp::graphics::VertexAttributes& attributes)
:
isBound(false)
, attributes(attributes)
, byteBuffer(this->attributes.vertexSize * numVertices)
, buffer(byteBuffer.convert<float>())
{
    buffer.flip();
    byteBuffer.flip();
}
