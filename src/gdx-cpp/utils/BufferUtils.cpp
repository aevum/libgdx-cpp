
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

#include "BufferUtils.hpp"

using namespace gdx;

void BufferUtils::copy (const Buffer& dst,int numFloats,int offset) {
    copyJni(src, dst, numFloats, offset);
    dst.position(0);

    if (dst instanceof ByteBuffer)
        dst.limit(numFloats << 2);
    else if (dst instanceof FloatBuffer) dst.limit(numFloats);
}

void BufferUtils::copy (int srcOffset,const Buffer& dst,int numElements) {
    copyJni(src, srcOffset, dst, positionInBytes(dst), numElements);
    dst.limit(dst.position() + bytesToElements(dst, numElements));
}

void BufferUtils::copy (int srcOffset,const Buffer& dst,int numElements) {
    copyJni(src, srcOffset << 1, dst, positionInBytes(dst), numElements << 1);
    dst.limit(dst.position() + bytesToElements(dst, numElements << 1));
}

void BufferUtils::copy (int srcOffset,const Buffer& dst,int numElements) {
    copyJni(src, srcOffset << 1, dst, positionInBytes(dst), numElements << 1);
    dst.limit(dst.position() + bytesToElements(dst, numElements << 1));
}

void BufferUtils::copy (int srcOffset,const Buffer& dst,int numElements) {
    copyJni(src, srcOffset << 2, dst, positionInBytes(dst), numElements << 2);
    dst.limit(dst.position() + bytesToElements(dst, numElements << 2));
}

void BufferUtils::copy (int srcOffset,const Buffer& dst,int numElements) {
    copyJni(src, srcOffset << 3, dst, positionInBytes(dst), numElements << 3);
    dst.limit(dst.position() + bytesToElements(dst, numElements << 3));
}

void BufferUtils::copy (int srcOffset,const Buffer& dst,int numElements) {
    copyJni(src, srcOffset << 2, dst, positionInBytes(dst), numElements << 2);
    dst.limit(dst.position() + bytesToElements(dst, numElements << 2));
}

void BufferUtils::copy (int srcOffset,const Buffer& dst,int numElements) {
    copyJni(src, srcOffset << 3, dst, positionInBytes(dst), numElements << 3);
    dst.limit(dst.position() + bytesToElements(dst, numElements << 3));
}

void BufferUtils::copy (const Buffer& src,const Buffer& dst,int numElements) {
    int numBytes = elementsToBytes(src, numElements);
    copyJni(src, positionInBytes(src), dst, positionInBytes(dst), numBytes);
    dst.limit(dst.position() + bytesToElements(dst, numBytes));
}

int BufferUtils::positionInBytes (const Buffer& dst) {
    if (dst instanceof ByteBuffer)
        return dst.position();
    else if (dst instanceof ShortBuffer)
        return dst.position() << 1;
    else if (dst instanceof CharBuffer)
        return dst.position() << 1;
    else if (dst instanceof IntBuffer)
        return dst.position() << 2;
    else if (dst instanceof LongBuffer)
        return dst.position() << 3;
    else if (dst instanceof FloatBuffer)
        return dst.position() << 2;
    else if (dst instanceof DoubleBuffer)
        return dst.position() << 3;
    else
        throw new GdxRuntimeException("Can't copy to a " + dst.getClass().getName() + " instance");
}

int BufferUtils::bytesToElements (const Buffer& dst,int bytes) {
    if (dst instanceof ByteBuffer)
        return bytes;
    else if (dst instanceof ShortBuffer)
        return bytes >>> 1;
    else if (dst instanceof CharBuffer)
        return bytes >>> 1;
    else if (dst instanceof IntBuffer)
        return bytes >>> 2;
    else if (dst instanceof LongBuffer)
        return bytes >>> 3;
    else if (dst instanceof FloatBuffer)
        return bytes >>> 2;
    else if (dst instanceof DoubleBuffer)
        return bytes >>> 3;
    else
        throw new GdxRuntimeException("Can't copy to a " + dst.getClass().getName() + " instance");
}

int BufferUtils::elementsToBytes (const Buffer& dst,int elements) {
    if (dst instanceof ByteBuffer)
        return elements;
    else if (dst instanceof ShortBuffer)
        return elements << 1;
    else if (dst instanceof CharBuffer)
        return elements << 1;
    else if (dst instanceof IntBuffer)
        return elements << 2;
    else if (dst instanceof LongBuffer)
        return elements << 3;
    else if (dst instanceof FloatBuffer)
        return elements << 2;
    else if (dst instanceof DoubleBuffer)
        return elements << 3;
    else
        throw new GdxRuntimeException("Can't copy to a " + dst.getClass().getName() + " instance");
}

FloatBuffer& BufferUtils::newFloatBuffer (int numFloats) {
    ByteBuffer buffer = ByteBuffer.allocateDirect(numFloats * 4);
    buffer.order(ByteOrder.nativeOrder());
    return buffer.asFloatBuffer();
}

DoubleBuffer& BufferUtils::newDoubleBuffer (int numDoubles) {
    ByteBuffer buffer = ByteBuffer.allocateDirect(numDoubles * 8);
    buffer.order(ByteOrder.nativeOrder());
    return buffer.asDoubleBuffer();
}

ByteBuffer& BufferUtils::newByteBuffer (int numBytes) {
    ByteBuffer buffer = ByteBuffer.allocateDirect(numBytes);
    buffer.order(ByteOrder.nativeOrder());
    return buffer;
}

ShortBuffer& BufferUtils::newShortBuffer (int numShorts) {
    ByteBuffer buffer = ByteBuffer.allocateDirect(numShorts * 2);
    buffer.order(ByteOrder.nativeOrder());
    return buffer.asShortBuffer();
}

CharBuffer& BufferUtils::newCharBuffer (int numChars) {
    ByteBuffer buffer = ByteBuffer.allocateDirect(numChars * 2);
    buffer.order(ByteOrder.nativeOrder());
    return buffer.asCharBuffer();
}

IntBuffer& BufferUtils::newIntBuffer (int numInts) {
    ByteBuffer buffer = ByteBuffer.allocateDirect(numInts * 4);
    buffer.order(ByteOrder.nativeOrder());
    return buffer.asIntBuffer();
}

LongBuffer& BufferUtils::newLongBuffer (int numLongs) {
    ByteBuffer buffer = ByteBuffer.allocateDirect(numLongs * 8);
    buffer.order(ByteOrder.nativeOrder());
    return buffer.asLongBuffer();
}

