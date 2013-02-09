
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

#ifndef GDX_CPP_UTILS_BASE64CODER_HPP_
#define GDX_CPP_UTILS_BASE64CODER_HPP_

#include <string>
#include <vector>

#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/implementation/System.hpp"

namespace gdx {

class Base64Coder {
public:
    static std::string encodeString (const std::string& s);
    static std::string encodeLines (char* bytes, int iLen, int iOff = 0, int lineLen = 76, char lineSeparator = gdx::system->getSeparator());
    static std::vector< char > encode (const char *in, int length, int iOff = 0);

    static std::string decodeString (const std::string& s);
    static std::vector< char > decodeLines (const std::string& s);
    static std::vector< char > decode (const std::string& s);
    static std::vector< char > decode (const char* bytes, int iLen, int iOff = 0);

private:
    struct static_impl;

    static static_impl* staticImpl;
    
    static char map1[64];
    static char map2[128];
};

} // namespace gdx

#endif // GDX_CPP_UTILS_BASE64CODER_HPP_
