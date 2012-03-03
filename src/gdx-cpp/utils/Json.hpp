
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

#ifndef GDX_CPP_UTILS_JSON_HPP_
#define GDX_CPP_UTILS_JSON_HPP_

#include "gdx-cpp/files/FileHandle.hpp"
#include <string.h>
#include <list>
#include <stdexcept>

#include "JsonItem.hpp"

namespace gdx_cpp {
namespace utils {

class Json {
public:

    
    void setIgnoreUnknownFields (bool ignoreUnknownFields);
    void setOutputType (const gdx_cpp::utils::JsonWriter::OutputType& outputType);
    void addClassTag (const std::string& tag,const Class& type);
    void setTypeName (const std::string& typeName);
    void setUsePrototypes (bool usePrototypes);
    void setElementType (const Class& type,const std::string& fieldName,const Class& elementType);
    std::string& toJson (const JsonValue& object);
    void toJson (const JsonValue& object,const gdx_cpp::files::FileHandle& file);
    void toJson (const JsonValue& object,const Class& knownType,const gdx_cpp::files::FileHandle& file);
    void toJson (const JsonValue& object,const Class& knownType,const Class& elementType,const gdx_cpp::files::FileHandle& file);
    void toJson (const JsonValue& object,const Writer& writer);
    void toJson (const JsonValue& object,const Class& knownType,const Writer& writer);
    void toJson (const JsonValue& object,const Class& knownType,const Class& elementType,const Writer& writer);
    void writeFields (const JsonValue& object);
    void writeField (const JsonValue& object,const std::string& name);
    void writeField (const JsonValue& object,const std::string& name,const Class& elementType);
    void writeField (const JsonValue& object,const std::string& fieldName,const std::string& jsonName);
    void writeField (const JsonValue& object,const std::string& fieldName,const std::string& jsonName,const Class& elementType);
    void writeValue (const std::string& name,const JsonValue& value);
    void writeValue (const std::string& name,const JsonValue& value,const Class& knownType);
    void writeValue (const std::string& name,const JsonValue& value,const Class& knownType,const Class& elementType);
    void writeValue (const JsonValue& value);
    void writeValue (const JsonValue& value,const Class& knownType);
    void writeValue (const JsonValue& value,const Class& knownType,const Class& elementType);
    void writeObjectStart (const std::string& name);
    void writeObjectStart (const std::string& name,const Class& actualType,const Class& knownType);
    void writeObjectStart ();
    void writeObjectStart (const Class& actualType,const Class& knownType);
    void writeObjectEnd ();
    void writeArrayStart (const std::string& name);
    void writeArrayStart ();
    void writeArrayEnd ();
    void writeType (const Class& type);
    void readField (const JsonValue& object,const std::string& name,const JsonValue& jsonData);
    void readField (const JsonValue& object,const std::string& name, const Class& elementType,const JsonValue& jsonData);
    void readField (const JsonValue& object,const std::string& fieldName,const std::string& jsonName,const JsonValue& jsonData);
    void readField (const gdx_cpp::utils::Json::json_item& object, const std::string& fieldName, const std::string& jsonName, const gdx_cpp::utils::Json::json_item& jsonData);
    void readFields (const JsonValue& object,const JsonValue& jsonData);
    std::string& prettyPrint (const JsonValue& object);
    std::string& prettyPrint (const std::string& json);
    std::string& prettyPrint (const JsonValue& object,bool fieldsOnSameLine);
    std::string& prettyPrint (const std::string& json,bool fieldsOnSameLine);
    void write (const Json& json,const T& object,const Class& knownType);
    T& read (const Json& json,const JsonValue& jsonData, const Class& type);
    void write (const Json& json);
    void read (const Json& json,const ObjectMap<String, Object>& jsonData);

    Json ();
    Json (const gdx_cpp::utils::JsonWriter::OutputType& outputType);

protected:
    bool debug = false;

private:
    std::vector< JsonValue > getDefaultValues (const JsonValue& type);
    std::string& convertToString (const JsonValue& object);

    void prettyPrint (const JsonValue& object,const StringBuilder& buffer,int indent,bool fieldsOnSameLine);
    bool isFlat (const ObjectMap<?, ?>& map);
    bool isFlat (const Array& array);
    void indent (int count,const StringBuilder& buffer);
    JsonWriter writer ;
    std::string typeName = "class";
    bool usePrototypes = true;
    OutputType outputType ;
    std::tr1::unordered_map < int , std::tr1::unordered_map< std::string, FieldMetadata> > typeToFields;
    ObjectMap<String, Class> tagToClass = new ObjectMap();
    ObjectMap<Class, String> classToTag = new ObjectMap();
    ObjectMap<Class, Serializer> classToSerializer = new ObjectMap();
    ObjectMap<Class, Object[]> classToDefaultValues = new ObjectMap();
    boolean ignoreUnknownFields ;
};

} // namespace gdx_cpp
} // namespace utils

#endif // GDX_CPP_UTILS_JSON_HPP_
