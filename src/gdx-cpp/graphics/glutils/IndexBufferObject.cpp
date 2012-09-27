
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

#include "IndexBufferObject.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/graphics/GL20.hpp"
#include "gdx-cpp/graphics/GL11.hpp"
#include "gdx-cpp/gl.hpp"

using namespace gdx;


int IndexBufferObject::createBufferObject () {
    if (gl20 != NULL) {
        gl20->glGenBuffers(1, &tmpHandle);
        return tmpHandle;
    } else if (gl11 != NULL) {
        gl11->glGenBuffers(1, &tmpHandle);
        return tmpHandle;
    }

    return 0;
}

int IndexBufferObject::getNumIndices () {
    return buffer.limit();
}

int IndexBufferObject::getNumMaxIndices () {
    return buffer.capacity();
}

void IndexBufferObject::setIndices (const std::vector< short int >& indices, int offset, int count) {
    isDirty = true;
    buffer.clear();
    buffer.put(indices, offset, count);
    buffer.flip();
    byteBuffer.position(0);
    byteBuffer.limit(count << 1);

    if (isBound) {
        if (gl11 != NULL) {
            GL11& gl = *gl11;
            gl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteBuffer.limit(), byteBuffer, usage);
        } else if (gl11 != NULL) {
            GL20& gl = *gl20;
            gl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteBuffer.limit(), byteBuffer, usage);
        }
        isDirty = false;
    }
}

short_buffer& IndexBufferObject::getBuffer () {
    isDirty = true;
    return buffer;
}

void IndexBufferObject::bind () {
    if (bufferHandle == 0)
        gdx_log_error("gdx",__FILE__ ": Buffer handler is not initialized?");

    if (gl11 != NULL) {
        GL11& gl = *gl11;
        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferHandle);
        if (isDirty) {
            byteBuffer.limit(buffer.limit() * 2);
            gl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteBuffer.limit(), byteBuffer, usage);
            isDirty = false;
        }
    } else {
        GL20& gl = *gl20;
        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferHandle);
        if (isDirty) {
            byteBuffer.limit(buffer.limit() * 2);
            gl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteBuffer.limit(), byteBuffer, usage);
            isDirty = false;
        }
    }
    isBound = true;
}

void IndexBufferObject::unbind () {
    if (gl11 != NULL) {
        gl11->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    } else if (gl20 != NULL) {
        gl20->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    isBound = false;
}

void IndexBufferObject::invalidate () {
    bufferHandle = createBufferObject();
    isDirty = true;
}

void IndexBufferObject::dispose () {
    if (gl20 != NULL) {
        tmpHandle = bufferHandle;
        GL20& gl = *gl20;
        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        gl.glDeleteBuffers(1, &tmpHandle);
        bufferHandle = 0;
    } else if (gl11 != NULL) {
        tmpHandle = bufferHandle;
        GL11& gl = *gl11;
        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        gl.glDeleteBuffers(1, &tmpHandle);
        bufferHandle = 0;
    }
}

IndexBufferObject::IndexBufferObject(bool isStatic, int maxIndices)
    : byteBuffer(maxIndices * 2),
bufferHandle(0),
isDirect(true),
isDirty(true),
isBound(false),
usage(0),
tmpHandle(0)
{
    isDirect = true;

    buffer = byteBuffer.convert<short>();
    buffer.flip();
    byteBuffer.flip();
    bufferHandle = createBufferObject();
    usage = isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
}

IndexBufferObject::IndexBufferObject(int maxIndices)
: byteBuffer(maxIndices * 2),
bufferHandle(0),
isDirect(true),
isDirty(true),
isBound(false),
usage(0),
tmpHandle(0)
{
    buffer = byteBuffer.convert<short>();
    buffer.flip();
    byteBuffer.flip();
    bufferHandle = createBufferObject();
    usage = GL_STATIC_DRAW;
}


