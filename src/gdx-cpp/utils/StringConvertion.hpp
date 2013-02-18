/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 *  @author aevum team
 */

#ifndef GDX_CPP_UTILS_STRINGCONVERTION_HPP
#define GDX_CPP_UTILS_STRINGCONVERTION_HPP

#include <cassert>
#include <string>
#include <sstream>
#include <cstdio>
#include <stdexcept>
#include <cstdlib>

namespace gdx {

template <typename returnType>
returnType from_string(const std::string& str) {
    std::stringstream ss;
    ss << str;
    returnType retval;
    ss >> retval;

    return retval;
}

template <>
inline std::string from_string<std::string>(const std::string& str) {
    return str;
}

template <>
inline float from_string<float>(const std::string& str) {
    return atof(str.c_str());
}

template <>
inline bool from_string<bool>(const std::string& str) {
    assert(str == "1" || str == "true" || str == "false" || str == "0");
    return str == "1" || str == "true";
}

template <typename returnType>
returnType from_hex_string(const std::string& str) {
    static std::stringstream ss;
    ss.clear();
    ss << std::hex << str;
    returnType retval;
    ss >> retval;
    
    return retval;
}

template <typename T>
std::string to_string(const T& item) {
    static std::stringstream ss;
    ss.str("");

    ss << item;

    return ss.str();
}

}

#endif // GDX_CPP_UTILS_STRINGCONVERTION_HPP
