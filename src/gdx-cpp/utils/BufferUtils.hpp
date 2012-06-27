
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

#ifndef GDX_CPP_UTILS_BUFFERUTILS_HPP_
#define GDX_CPP_UTILS_BUFFERUTILS_HPP_

#include "Buffer.hpp"

namespace gdx {
class BufferUtils {
public:
    static void copy (float * value, const gdx::buffer<float>& dst, int numFloats,int offset);

//     static void copy (const Buffer& dst,int numFloats,int offset);
//     static void copy (int srcOffset,const Buffer& dst,int numElements);
//     static void copy (int srcOffset,const Buffer& dst,int numElements);
//     static void copy (int srcOffset,const Buffer& dst,int numElements);
//     static void copy (int srcOffset,const Buffer& dst,int numElements);
//     static void copy (int srcOffset,const Buffer& dst,int numElements);
//     static void copy (int srcOffset,const Buffer& dst,int numElements);
//     static void copy (int srcOffset,const Buffer& dst,int numElements);
//     static void copy (const Buffer& src,const Buffer& dst,int numElements);
//     static FloatBuffer& newFloatBuffer (int numFloats);
//     static DoubleBuffer& newDoubleBuffer (int numDoubles);
//     static ByteBuffer& newByteBuffer (int numBytes);
//     static ShortBuffer& newShortBuffer (int numShorts);
//     static CharBuffer& newCharBuffer (int numChars);
//     static IntBuffer& newIntBuffer (int numInts);
//     static LongBuffer& newLongBuffer (int numLongs);

protected:


private:
//     static int positionInBytes (const Buffer& dst);
//     static int bytesToElements (const Buffer& dst,int bytes);
//     static int elementsToBytes (const Buffer& dst,int elements);
};

} // namespace gdx

#endif // GDX_CPP_UTILS_BUFFERUTILS_HPP_
