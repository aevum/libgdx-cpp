
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

#include "IndexBufferObjectSubData.hpp"

#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/graphics/GL20.hpp"
#include "gdx-cpp/graphics/GL11.hpp"
#include "gdx-cpp/graphics/GL10.hpp"
#include "gdx-cpp/gl.hpp"

using namespace gdx;

int IndexBufferObjectSubData::createBufferObject () {
    if (gl20 != NULL) {
        gl20->glGenBuffers(1, &tmpHandle);
        gl20->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmpHandle);
        gl20->glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteBuffer.capacity(), NULL, usage);
        gl20->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        return tmpHandle;
    } else if (gl11 != NULL) {
        gl11->glGenBuffers(1, &tmpHandle);
        gl11->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmpHandle);
        gl11->glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteBuffer.capacity(), NULL, usage);
        gl11->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        return tmpHandle;
    }

    return 0;
}

int IndexBufferObjectSubData::getNumIndices () {
    return buffer.limit();
}

int IndexBufferObjectSubData::getNumMaxIndices () {
    return buffer.capacity();
}

void IndexBufferObjectSubData::setIndices (const std::vector<short>& indices, int offset,int count) {
    isDirty = true;
    buffer.clear();
    buffer.put(indices, offset, count);
    buffer.flip();
    byteBuffer.position(0);
    byteBuffer.limit(count << 1);

    if (isBound) {
        if (gl11 != NULL) {
            GL11& gl = *gl11;
// gl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteBuffer
// .limit(), byteBuffer, usage);
            gl.glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);
        } else if (gl11 != NULL) {
            GL20& gl = *gl20;
// gl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteBuffer
// .limit(), byteBuffer, usage);
            gl.glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);

        }
        isDirty = false;
    }
}

gdx::short_buffer& IndexBufferObjectSubData::getBuffer () {
    isDirty = true;
    return buffer;
}

void IndexBufferObjectSubData::bind () {
    if (bufferHandle == 0) throw std::runtime_error("buuh");

    if (gl11 != NULL) {
        GL11& gl = *gl11;
        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferHandle);
        if (isDirty) {
// gl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteBuffer
// .limit(), byteBuffer, usage);
            byteBuffer.limit(buffer.limit() * 2);
            gl.glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);
            isDirty = false;
        }
    } else {
        GL20& gl = *gl20;
        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferHandle);
        if (isDirty) {
// gl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteBuffer
// .limit(), byteBuffer, usage);
            byteBuffer.limit(buffer.limit() * 2);
            gl.glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, byteBuffer.limit(), byteBuffer);
            isDirty = false;
        }
    }
    isBound = true;
}

void IndexBufferObjectSubData::unbind () {
    if (gl11 != NULL) {
        gl11->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    } else if (gl20 != NULL) {
        gl20->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    isBound = false;
}

void IndexBufferObjectSubData::invalidate () {
    bufferHandle = createBufferObject();
    isDirty = true;
}

void IndexBufferObjectSubData::dispose () {
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

IndexBufferObjectSubData::IndexBufferObjectSubData(bool isStatic, int maxIndices)
:
tmpHandle(0)
, byteBuffer(maxIndices * 2)
, buffer(byteBuffer.convert<short>())
, bufferHandle(0)
, isDirect(true)
, isDirty(true)
, isBound(false)
, usage(isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW)
{
    // if (Gdx.app.getType() == ApplicationType.Android
    // && Gdx.app.getVersion() < 5) {
    // byteBuffer = ByteBuffer.allocate(maxIndices * 2);
    // byteBuffer.order(ByteOrder.nativeOrder());
    // isDirect = false;
    // } else {
//     byteBuffer.order(ByteOrder.nativeOrder());
    buffer.flip();
    byteBuffer.flip();
    bufferHandle = createBufferObject();
}

IndexBufferObjectSubData::IndexBufferObjectSubData(int maxIndices)
:
tmpHandle(0)
, byteBuffer(maxIndices * 2)
, buffer(byteBuffer.convert<short>())
, bufferHandle(0)
, isDirect(true)
, isDirty(true)
, isBound(false)
, usage(GL_STATIC_DRAW)
{
    buffer.flip();
    byteBuffer.flip();
    bufferHandle = createBufferObject();
}


