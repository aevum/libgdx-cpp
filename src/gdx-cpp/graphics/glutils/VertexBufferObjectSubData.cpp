
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

#include "VertexBufferObjectSubData.hpp"

#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/graphics/GL11.hpp"
#include "gdx-cpp/graphics/GL20.hpp"
#include "gdx-cpp/graphics/glutils/ShaderProgram.hpp"
#include "gdx-cpp/gl.hpp"

using namespace gdx;

int VertexBufferObjectSubData::createBufferObject () {
    if (gl20 != NULL) {
        gl20->glGenBuffers(1, &tmpHandle);
        gl20->glBindBuffer(GL_ARRAY_BUFFER, tmpHandle);
        gl20->glBufferData(GL_ARRAY_BUFFER, byteBuffer.capacity(), NULL, usage);
        gl20->glBindBuffer(GL_ARRAY_BUFFER, 0);
    } else {
        gl11->glGenBuffers(1, &tmpHandle);
        gl11->glBindBuffer(GL_ARRAY_BUFFER, tmpHandle);
        gl11->glBufferData(GL_ARRAY_BUFFER, byteBuffer.capacity(), NULL, usage);
        gl11->glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    return tmpHandle;
}

VertexAttributes& VertexBufferObjectSubData::getAttributes () {
    return attributes;
}

int VertexBufferObjectSubData::getNumVertices () {
    return buffer.limit() * 4 / attributes.vertexSize;
}

int VertexBufferObjectSubData::getNumMaxVertices () {
    return byteBuffer.capacity() / attributes.vertexSize;
}

float_buffer& VertexBufferObjectSubData::getBuffer () {
    isDirty = true;
    return buffer;
}

void VertexBufferObjectSubData::setVertices (const float* vertices, int offset, int count) {
    isDirty = true;
    if (isDirect) {
        byteBuffer.copy(vertices , count , offset);
        buffer.position(0);
        buffer.limit(count);
    } else {
        buffer.clear();
        buffer.put(vertices, count, offset, count);
        buffer.flip();
        byteBuffer.position(0);
        byteBuffer.limit(buffer.limit() << 2);
    }

    if (isBound) {
        if (gl20 != NULL) {
            GL20& gl = *gl20;
            gl.glBufferSubData(GL_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);
        } else {
            GL11& gl = *gl11;
            gl.glBufferSubData(GL_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);
        }
        isDirty = false;
    }
}

void VertexBufferObjectSubData::bind () {
    GL11& gl = *gl11;

    gl.glBindBuffer(GL_ARRAY_BUFFER, bufferHandle);
    if (isDirty) {
        byteBuffer.limit(buffer.limit() * 4);
        gl.glBufferSubData(GL_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);
// gl.glBufferData(GL_ARRAY_BUFFER, byteBuffer.limit(),
// byteBuffer, usage);
        isDirty = false;
    }

    int textureUnit = 0;
    int numAttributes = attributes.size();

    for (int i = 0; i < numAttributes; i++) {
        VertexAttribute attribute = attributes.get(i);

        switch (attribute.usage) {
        case VertexAttributes::Usage::Position:
            gl.glEnableClientState(GL_VERTEX_ARRAY);
            gl.glVertexPointer(attribute.numComponents, GL_FLOAT, attributes.vertexSize, &attribute.offset);
            break;

        case VertexAttributes::Usage::Color:
        case VertexAttributes::Usage::ColorPacked:
        {
            int colorType = GL_FLOAT;
            if (attribute.usage == VertexAttributes::Usage::ColorPacked) colorType = GL_UNSIGNED_BYTE;

            gl.glEnableClientState(GL_COLOR_ARRAY);
            gl.glColorPointer(attribute.numComponents, colorType, attributes.vertexSize, &attribute.offset);
            break;
        }
        case VertexAttributes::Usage::Normal:
            gl.glEnableClientState(GL_NORMAL_ARRAY);
            gl.glNormalPointer(GL_FLOAT, attributes.vertexSize, &attribute.offset);
            break;

        case VertexAttributes::Usage::TextureCoordinates:
            gl.glClientActiveTexture(GL_TEXTURE0 + textureUnit);
            gl.glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            gl.glTexCoordPointer(attribute.numComponents, GL_FLOAT, attributes.vertexSize, &attribute.offset);
            textureUnit++;
            break;

        default:{
            std::stringstream ss;
            ss << "unkown vertex attribute type: " << attribute.usage;
            throw std::runtime_error(ss.str());
        }
        }
    }

    isBound = true;
}

void VertexBufferObjectSubData::bind (ShaderProgram& shader) {
    GL20& gl = *gl20;

    gl.glBindBuffer(GL_ARRAY_BUFFER, bufferHandle);
    if (isDirty) {
        byteBuffer.limit(buffer.limit() * 4);
        gl.glBufferSubData(GL_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);
// gl.glBufferData(GL_ARRAY_BUFFER, byteBuffer.limit(),
// byteBuffer, usage);
        isDirty = false;
    }

    int numAttributes = attributes.size();
    for (int i = 0; i < numAttributes; i++) {
        VertexAttribute& attribute = attributes.get(i);
        shader.enableVertexAttribute(attribute.alias);
        int colorType = GL_FLOAT;
        bool normalize = false;
        if (attribute.usage == VertexAttributes::Usage::ColorPacked) {
            colorType = GL_UNSIGNED_BYTE;
            normalize = true;
        }
        shader.setVertexAttribute(attribute.alias, attribute.numComponents, colorType, normalize, attributes.vertexSize,
                                  attribute.offset);
    }
    isBound = true;
}

void VertexBufferObjectSubData::unbind () {
    GL11& gl = *gl11;
    int textureUnit = 0;
    int numAttributes = attributes.size();

    for (int i = 0; i < numAttributes; i++) {

        VertexAttribute& attribute = attributes.get(i);
        switch (attribute.usage) {
        case VertexAttributes::Usage::Position:
            break; // no-op, we also need a position bound in gles
        case VertexAttributes::Usage::Color:
        case VertexAttributes::Usage::ColorPacked:
            gl.glDisableClientState(GL_COLOR_ARRAY);
            break;
        case VertexAttributes::Usage::Normal:
            gl.glDisableClientState(GL_NORMAL_ARRAY);
            break;
        case VertexAttributes::Usage::TextureCoordinates:
            gl.glClientActiveTexture(GL_TEXTURE0 + textureUnit);
            gl.glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            textureUnit++;
            break;
        default:
        {
            std::stringstream ss;
            ss << "unkown vertex attribute type: " << attribute.usage;
            throw std::runtime_error(ss.str());
        }
        }
    }

    gl.glBindBuffer(GL_ARRAY_BUFFER, 0);
    isBound = false;
}

void VertexBufferObjectSubData::unbind (ShaderProgram& shader) {
    GL20& gl = *gl20;
    int numAttributes = attributes.size();
    for (int i = 0; i < numAttributes; i++) {
        VertexAttribute attribute = attributes.get(i);
        shader.disableVertexAttribute(attribute.alias);
    }
    gl.glBindBuffer(GL_ARRAY_BUFFER, 0);
    isBound = false;
}

void VertexBufferObjectSubData::invalidate () {
    bufferHandle = createBufferObject();
    isDirty = true;
}

void VertexBufferObjectSubData::dispose () {
    if (gl20 != NULL) {
        tmpHandle = bufferHandle;
        
        GL20& gl = *gl20;
        gl.glBindBuffer(GL_ARRAY_BUFFER, 0);
        gl.glDeleteBuffers(1, &tmpHandle);

        bufferHandle = 0;
    } else {
        tmpHandle = bufferHandle;
        
        GL11& gl = *gl11;
        gl.glBindBuffer(GL_ARRAY_BUFFER, 0);
        gl.glDeleteBuffers(1, &tmpHandle);
        bufferHandle = 0;
    }
}

int VertexBufferObjectSubData::getBufferHandle () {
    return bufferHandle;
}

VertexBufferObjectSubData::VertexBufferObjectSubData(bool isStatic, int numVertices, const std::vector< VertexAttribute >& attributes)
        :
        bufferHandle(0)
        , tmpHandle(0)
        , isDirect(true)
        , usage(isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW)
        , isDirty(false)
        , isBound(false)
        , attributes(attributes)
        , isStatic(isStatic)
        , byteBuffer(this->attributes.vertexSize * numVertices)
        , buffer(byteBuffer.convert<float>())
{
    bufferHandle = createBufferObject();
    buffer.flip();
    byteBuffer.flip();
}


