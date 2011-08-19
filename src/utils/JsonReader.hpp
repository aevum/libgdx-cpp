
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

namespace gdx_cpp {
namespace utils {

class JsonReader {
public:
    Object& parse (const std::string& json);
    Object& parse (const Reader& reader);
    Object& parse (const InputStream& input);
    Object& parse (const gdx_cpp::files::FileHandle& file);
    Object& parse (int offset,int length);

protected:
    void startObject (const std::string& name);
    void startArray (const std::string& name);
    void pop ();
    void string (const std::string& name,const std::string& value);
    void number (const std::string& name,const std::string& value);

private:
    static char* init__json_actions_0 ();
    static short* init__json_key_offsets_0 ();
    static char* init__json_trans_keys_0 ();
    static char* init__json_single_lengths_0 ();
    static char* init__json_range_lengths_0 ();
    static short* init__json_index_offsets_0 ();
    static char* init__json_indicies_0 ();
    static char* init__json_trans_targs_0 ();
    static char* init__json_trans_actions_0 ();
    static char* init__json_eof_actions_0 ();
    void set (const std::string& name,const Object& value);
    std::string& unescape (const std::string& value);
};

} // namespace gdx_cpp
} // namespace utils

#endif // GDX_CPP_UTILS_JSONREADER_HPP_
