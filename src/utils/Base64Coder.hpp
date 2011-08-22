
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

namespace gdx_cpp {
namespace utils {

class Base64Coder {
public:
    static std::string& encodeString (const std::string& s);
    static std::string& encodeLines ();
    static std::string& encodeLines (int iOff,int iLen,int lineLen,const std::string& lineSeparator);
    static char* encode ();
    static char* encode (int iLen);
    static char* encode (int iOff,int iLen);
    static std::string& decodeString (const std::string& s);
    static char* decodeLines (const std::string& s);
    static char* decode (const std::string& s);
    static char* decode ();
    static char* decode (int iOff,int iLen);

protected:


private:

};

} // namespace gdx_cpp
} // namespace utils

#endif // GDX_CPP_UTILS_BASE64CODER_HPP_
