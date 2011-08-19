
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

#include "Base64Coder.hpp"

using namespace gdx_cpp::utils;

std::string& Base64Coder::encodeString (const std::string& s) {
    return new String(encode(s.getBytes()));
}

std::string& Base64Coder::encodeLines () {
    return encodeLines(in, 0, in.length, 76, systemLineSeparator);
}

std::string& Base64Coder::encodeLines (int iOff,int iLen,int lineLen,const std::string& lineSeparator) {
    int blockLen = (lineLen * 3) / 4;
    if (blockLen <= 0) throw new IllegalArgumentException();
    int lines = (iLen + blockLen - 1) / blockLen;
    int bufLen = ((iLen + 2) / 3) * 4 + lines * lineSeparator.length();
    StringBuilder buf = new StringBuilder(bufLen);
    int ip = 0;
    while (ip < iLen) {
        int l = Math.min(iLen - ip, blockLen);
        buf.append(encode(in, iOff + ip, l));
        buf.append(lineSeparator);
        ip += l;
    }
    return buf.toString();
}

char* Base64Coder::encode () {
    return encode(in, 0, in.length);
}

char* Base64Coder::encode (int iLen) {
    return encode(in, 0, iLen);
}

char* Base64Coder::encode (int iOff,int iLen) {
    int oDataLen = (iLen * 4 + 2) / 3; // output length without padding
    int oLen = ((iLen + 2) / 3) * 4; // output length including padding
    char[] out = new char[oLen];
    int ip = iOff;
    int iEnd = iOff + iLen;
    int op = 0;
    while (ip < iEnd) {
        int i0 = in[ip++] & 0xff;
        int i1 = ip < iEnd ? in[ip++] & 0xff : 0;
        int i2 = ip < iEnd ? in[ip++] & 0xff : 0;
        int o0 = i0 >>> 2;
        int o1 = ((i0 & 3) << 4) | (i1 >>> 4);
        int o2 = ((i1 & 0xf) << 2) | (i2 >>> 6);
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

std::string& Base64Coder::decodeString (const std::string& s) {
    return new String(decode(s));
}

char* Base64Coder::decodeLines (const std::string& s) {
    char[] buf = new char[s.length()];
    int p = 0;
    for (int ip = 0; ip < s.length(); ip++) {
        char c = s.charAt(ip);
        if (c != ' ' && c != '\r' && c != '\n' && c != '\t') buf[p++] = c;
    }
    return decode(buf, 0, p);
}

char* Base64Coder::decode (const std::string& s) {
    return decode(s.toCharArray());
}

char* Base64Coder::decode () {
    return decode(in, 0, in.length);
}

char* Base64Coder::decode (int iOff,int iLen) {
    if (iLen % 4 != 0) throw new IllegalArgumentException("Length of Base64 encoded input string is not a multiple of 4.");
    while (iLen > 0 && in[iOff + iLen - 1] == '=')
        iLen--;
    int oLen = (iLen * 3) / 4;
    byte[] out = new byte[oLen];
    int ip = iOff;
    int iEnd = iOff + iLen;
    int op = 0;
    while (ip < iEnd) {
        int i0 = in[ip++];
        int i1 = in[ip++];
        int i2 = ip < iEnd ? in[ip++] : 'A';
        int i3 = ip < iEnd ? in[ip++] : 'A';
        if (i0 > 127 || i1 > 127 || i2 > 127 || i3 > 127)
            throw new IllegalArgumentException("Illegal character in Base64 encoded data.");
        int b0 = map2[i0];
        int b1 = map2[i1];
        int b2 = map2[i2];
        int b3 = map2[i3];
        if (b0 < 0 || b1 < 0 || b2 < 0 || b3 < 0)
            throw new IllegalArgumentException("Illegal character in Base64 encoded data.");
        int o0 = (b0 << 2) | (b1 >>> 4);
        int o1 = ((b1 & 0xf) << 4) | (b2 >>> 2);
        int o2 = ((b2 & 3) << 6) | b3;
        out[op++] = (byte)o0;
        if (op < oLen) out[op++] = (byte)o1;
        if (op < oLen) out[op++] = (byte)o2;
    }
    return out;
}

