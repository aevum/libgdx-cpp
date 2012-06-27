
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

#include "LittleEndianInputStream.hpp"

using namespace gdx::utils;

void LittleEndianInputStream::readFully () throws IOException {
    din.readFully(b);
}

void LittleEndianInputStream::readFully (int off,int len) throws IOException {
    din.readFully(b, off, len);
}

int LittleEndianInputStream::skipBytes (int n) throws IOException {
    return din.skipBytes(n);
}

bool LittleEndianInputStream::readBoolean () throws IOException {
    return din.readBoolean();
}

char LittleEndianInputStream::readByte () throws IOException {
    return din.readByte();
}

int LittleEndianInputStream::readUnsignedByte () throws IOException {
    return din.readUnsignedByte();
}

short& LittleEndianInputStream::readShort () throws IOException {
    int low = din.read();
    int high = din.read();
    return (short)((high << 8) | (low & 0xff));
}

int LittleEndianInputStream::readUnsignedShort () throws IOException {
    int low = din.read();
    int high = din.read();
    return ((high & 0xff) << 8) | (low & 0xff);
}

char LittleEndianInputStream::readChar () throws IOException {
    return din.readChar();
}

int LittleEndianInputStream::readInt () throws IOException {
    int[] res = new int[4];
    for (int i = 3; i >= 0; i--)
        res[i] = din.read();

    return ((res[0] & 0xff) << 24) | ((res[1] & 0xff) << 16) | ((res[2] & 0xff) << 8) | (res[3] & 0xff);
}

long LittleEndianInputStream::readLong () throws IOException {
    int[] res = new int[8];
    for (int i = 7; i >= 0; i--)
        res[i] = din.read();

    return (((long)(res[0] & 0xff) << 56) | ((long)(res[1] & 0xff) << 48) | ((long)(res[2] & 0xff) << 40)
    | ((long)(res[3] & 0xff) << 32) | ((long)(res[4] & 0xff) << 24) | ((long)(res[5] & 0xff) << 16)
    | ((long)(res[6] & 0xff) << 8) | ((long)(res[7] & 0xff)));
}

float LittleEndianInputStream::readFloat () throws IOException {
    return Float.intBitsToFloat(readInt());
}

double LittleEndianInputStream::readDouble () throws IOException {
    return Double.longBitsToDouble(readLong());
}

std::string& LittleEndianInputStream::readLine () throws IOException {
    return din.readLine();
}

std::string& LittleEndianInputStream::readUTF () throws IOException {
    return din.readUTF();
}

