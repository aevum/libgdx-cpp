
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

using namespace gdx_cpp::graphics::glutils;

void VertexArray::dispose () {

}

FloatBuffer& VertexArray::getBuffer () {
    return buffer;
}

int VertexArray::getNumVertices () {
    return buffer.limit() * 4 / attributes.vertexSize;
}

int VertexArray::getNumMaxVertices () {
    return byteBuffer.capacity() / attributes.vertexSize;
}

void VertexArray::setVertices (int offset,int count) {
    BufferUtils.copy(vertices, byteBuffer, count, offset);
    buffer.position(0);
    buffer.limit(count);
}

void VertexArray::bind () {
    GL10 gl = Gdx.gl10;
    int textureUnit = 0;
    int numAttributes = attributes.size();

    byteBuffer.limit(buffer.limit() * 4);

    for (int i = 0; i < numAttributes; i++) {
        VertexAttribute attribute = attributes.get(i);

        switch (attribute.usage) {
        case Usage.Position:
            byteBuffer.position(attribute.offset);
            gl.glEnableClientState(GL11.GL_VERTEX_ARRAY);
            gl.glVertexPointer(attribute.numComponents, GL10.GL_FLOAT, attributes.vertexSize, byteBuffer);
            break;

        case Usage.Color:
        case Usage.ColorPacked:
            int colorType = GL10.GL_FLOAT;
            if (attribute.usage == Usage.ColorPacked) colorType = GL11.GL_UNSIGNED_BYTE;
            byteBuffer.position(attribute.offset);
            gl.glEnableClientState(GL10.GL_COLOR_ARRAY);
            gl.glColorPointer(attribute.numComponents, colorType, attributes.vertexSize, byteBuffer);
            break;

        case Usage.Normal:
            byteBuffer.position(attribute.offset);
            gl.glEnableClientState(GL10.GL_NORMAL_ARRAY);
            gl.glNormalPointer(GL10.GL_FLOAT, attributes.vertexSize, byteBuffer);
            break;

        case Usage.TextureCoordinates:
            gl.glClientActiveTexture(GL10.GL_TEXTURE0 + textureUnit);
            gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY);
            byteBuffer.position(attribute.offset);
            gl.glTexCoordPointer(attribute.numComponents, GL10.GL_FLOAT, attributes.vertexSize, byteBuffer);
            textureUnit++;
            break;

        default:
            // throw new GdxRuntimeException("unkown vertex attribute type: " + attribute.usage);
        }
    }

    isBound = true;
}

void VertexArray::unbind () {
    GL10 gl = Gdx.gl10;
    int textureUnit = 0;
    int numAttributes = attributes.size();

    for (int i = 0; i < numAttributes; i++) {

        VertexAttribute attribute = attributes.get(i);
        switch (attribute.usage) {
        case Usage.Position:
            break; // no-op, we also need a position bound in gles
        case Usage.Color:
        case Usage.ColorPacked:
            gl.glDisableClientState(GL11.GL_COLOR_ARRAY);
            break;
        case Usage.Normal:
            gl.glDisableClientState(GL11.GL_NORMAL_ARRAY);
            break;
        case Usage.TextureCoordinates:
            gl.glClientActiveTexture(GL11.GL_TEXTURE0 + textureUnit);
            gl.glDisableClientState(GL11.GL_TEXTURE_COORD_ARRAY);
            textureUnit++;
            break;
        default:
            // throw new GdxRuntimeException("unkown vertex attribute type: " + attribute.usage);
        }
    }
    byteBuffer.position(0);
    isBound = false;
}

gdx_cpp::graphics::VertexAttributes& VertexArray::getAttributes () {
    return attributes;
}

