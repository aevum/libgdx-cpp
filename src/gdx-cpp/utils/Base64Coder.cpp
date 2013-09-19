
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

#include <algorithm>
#include <ostream>
#include <stdexcept>

#include "Base64Coder.hpp"

using namespace gdx;

struct Base64Coder::static_impl {
    static_impl() {
        int i = 0;
        for (char c = 'A'; c <= 'Z'; c++)
            map1[i++] = c;
        for (char c = 'a'; c <= 'z'; c++)
            map1[i++] = c;
        for (char c = '0'; c <= '9'; c++)
            map1[i++] = c;

        map1[i++] = '+';
        map1[i++] = '/';

        for (auto & elem : map2)
            elem = -1;
        
        for (int i = 0; i < 64; i++)
            map2[(int) map1[i]] = (char)i;
    }
};

Base64Coder::static_impl* Base64Coder::staticImpl = new Base64Coder::static_impl;

char Base64Coder::map1[64];
char Base64Coder::map2[128];

std::string Base64Coder::encodeString (const std::string& s) {
    return std::string(&encode(s.c_str(), s.length())[0]);
}

std::string Base64Coder::encodeLines (char* bytes, int iLen, int iOff, int lineLen, char lineSeparator) {
    int blockLen = (lineLen * 3) / 4;

    if (blockLen <= 0) {
        throw new std::runtime_error("Block len is negative");
    }

    std::stringstream buf;
    
    int ip = 0;
    while (ip < iLen) {
        int l = std::min(iLen - ip, blockLen);
        buf << &encode(bytes, iOff + ip, l)[0];
        buf << lineSeparator;
        ip += l;
    }

    return buf.str();
}


std::vector<char> Base64Coder::encode (const char* in, int length, int iOff) {
    int oDataLen = (length * 4 + 2) / 3; // output length without padding
    int oLen = ((length + 2) / 3) * 4; // output length including padding
    std::vector<char> out;

    out.resize(oLen + 1);
    out[oLen] = 0;
    
    int ip = iOff;
    int iEnd = iOff + length;
    int op = 0;
    while (ip < iEnd) {
        int i0 = in[ip++] & 0xff;
        int i1 = ip < iEnd ? in[ip++] & 0xff : 0;
        int i2 = ip < iEnd ? in[ip++] & 0xff : 0;
        int o0 = i0 >> 2;
        int o1 = ((i0 & 3) << 4) | (i1 >> 4);
        int o2 = ((i1 & 0xf) << 2) | (i2 >> 6);
        int o3 = i2 & 0x3F;
        out[op++] = map1[o0];
        out[op++] = map1[o1];
        out[op] = op < oDataLen ? map1[o2] : '=';
        op++;
        out[op] = op < oDataLen ? map1[o3] : '=';
        op++;
    }
    return out;
}

std::string Base64Coder::decodeString (const std::string& s) {
    std::vector<char> decoded = decode(s);
    return std::string(&decoded[0], decoded.size());
}

std::vector<char> Base64Coder::decodeLines (const std::string& s) {
    std::vector<char> buf;
    buf.resize(s.length());

    int p = 0;
    for (auto & elem : s) {
        char c = elem;
        if (c != ' ' && c != '\r' && c != '\n' && c != '\t') buf[p++] = c;
    }
    
    return decode(&buf[0], buf.size(), p);
}

std::vector<char> Base64Coder::decode (const std::string& s) {
    return decode(s.c_str(), s.length());
}

std::vector< char > Base64Coder::decode (const char* in, int iLen, int iOff) {
    if (iLen % 4 != 0) throw new std::runtime_error("Length of Base64 encoded input string is not a multiple of 4.");

    while (iLen > 0 && in[iOff + iLen - 1] == '=')
        iLen--;

    int oLen = (iLen * 3) / 4;

    std::vector< char > out;
    out.resize(oLen);

    int ip = iOff;
    int iEnd = iOff + iLen;
    int op = 0;
    while (ip < iEnd) {
        int i0 = in[ip++];
        int i1 = in[ip++];
        int i2 = ip < iEnd ? in[ip++] : 'A';
        int i3 = ip < iEnd ? in[ip++] : 'A';
        if (i0 > 127 || i1 > 127 || i2 > 127 || i3 > 127)
            throw new std::runtime_error("Illegal character in Base64 encoded data.");
        int b0 = map2[i0];
        int b1 = map2[i1];
        int b2 = map2[i2];
        int b3 = map2[i3];
        if (b0 < 0 || b1 < 0 || b2 < 0 || b3 < 0)
            throw new std::runtime_error("Illegal character in Base64 encoded data.");
        int o0 = (b0 << 2) | (b1 >> 4);
        int o1 = ((b1 & 0xf) << 4) | (b2 >> 2);
        int o2 = ((b2 & 3) << 6) | b3;
        out[op++] = (char)o0;
        if (op < oLen) out[op++] = (char)o1;
        if (op < oLen) out[op++] = (char)o2;
    }
    return out;
}

