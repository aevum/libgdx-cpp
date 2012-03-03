
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

#ifndef GDX_CPP_UTILS_JSONWRITER_HPP_
#define GDX_CPP_UTILS_JSONWRITER_HPP_

namespace gdx_cpp {
namespace utils {

class JsonWriter {
public:
    void setOutputType (const OutputType& outputType);
    JsonWriter& name (const std::string& name);
    JsonWriter& object ();
    JsonWriter& array ();
    JsonWriter& value (const Object& value);
    JsonWriter& object (const std::string& name);
    JsonWriter& array (const std::string& name);
    JsonWriter& set (const std::string& name,const Object& value);
    JsonWriter& pop ();
    void write (int off,int len);
    void flush ();
    void close ();
    std::string& quoteValue (const std::string& value);
    std::string& quoteName (const std::string& value);
    JsonWriter (const Writer& writer);

protected:
    Writer writer ;

private:
    Array<JsonObject> stack = new Array();
    JsonObject current ;
    boolean named ;
    OutputType outputType = OutputType.json;
};

} // namespace gdx_cpp
} // namespace utils

#endif // GDX_CPP_UTILS_JSONWRITER_HPP_
