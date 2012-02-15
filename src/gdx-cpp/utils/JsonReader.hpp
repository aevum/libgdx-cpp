
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

#ifndef GDX_CPP_UTILS_JSONREADER_HPP_
#define GDX_CPP_UTILS_JSONREADER_HPP_

#include "JsonValue.hpp"

#include <string>
#include <list>
#include "gdx-cpp/files/FileHandle.hpp"

namespace gdx_cpp {
namespace utils {

class JsonReader {
public:
    JsonReader();
    
    static JsonValue::ptr parse (const std::string& json);
    static JsonValue::ptr parse (const gdx_cpp::files::FileHandle& file);
    static JsonValue::ptr parse (const char* data, int offset, int length);

protected:
    static void startObject (const std::string& name);
    static void startArray (const std::string& name);

    static void pop ();

    static void string (const std::string& name,  const std::string& value);
    static void number (const std::string& name,  float value);
    static void number (const std::string& name,  int value);
    static void boolean (const std::string& name, bool value);

private:    
    static void set (const std::string& name, gdx_cpp::utils::JsonValue::ptr value);
    
    static std::string unescape (const std::string& value);

    static JsonValue::ptr root;
    static JsonValue::ptr current;

    static std::list< JsonValue::ptr > elements;
};

} // namespace gdx_cpp
} // namespace utils

#endif // GDX_CPP_UTILS_JSONREADER_HPP_
