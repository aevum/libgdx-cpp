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

#ifndef GDX_CPP_UTILS_JSONITEM_HPP
#define GDX_CPP_UTILS_JSONITEM_HPP

#include "gdx-cpp/internal/memory"
#include "gdx-cpp/internal/unordered_map"
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <stdexcept>
#include "gdx-cpp/internal/memory"

namespace gdx {

enum json_item_type {
    json_string,
    json_int,
    json_bool,
    json_list,
    json_json,
    json_float,
    json_null
};

class JsonValue {
public:
    typedef ref_ptr_maker< JsonValue >::shared_ptr_def ptr;
    typedef gdx_unordered_map< std::string, ptr > item_map;
    typedef std::vector< ptr > array;

    JsonValue(int val) ;
    JsonValue(int* val) ;
    JsonValue(float val) ;
    JsonValue(float* val) ;
    JsonValue(bool val) ;
    JsonValue(bool* val) ;
    JsonValue(const std::string& val) ;
    JsonValue(std::string* val) ;
    JsonValue(const item_map& val) ;
    JsonValue(item_map* val) ;
    JsonValue(const array& val) ;
    JsonValue(array* val) ;
    JsonValue(const JsonValue& other) : item_val(other.item_val), item_type(other.item_type)
    {
    }
   
    JsonValue& operator = (const std::string& other) ;

    JsonValue& operator = (const char* other) ;
    
    JsonValue& operator = (int other) ;

    JsonValue& operator = (bool other) ;

    JsonValue& operator = (float other) ;

    JsonValue& operator = (const array& other) ;

    JsonValue& operator = (const JsonValue& other) ;

    JsonValue& operator = (const ptr& other) ;

    JsonValue& operator + (const JsonValue& other) ;

    JsonValue& operator += (const JsonValue& other) ;
   
    int& as_int();
    const int& as_int() const;

    bool& as_bool();
    const bool& as_bool() const;

    float& as_float();
    const float& as_float() const;

    std::string& as_string();
    const std::string& as_string() const;

    array& as_array();
    const array& as_array() const ;
    
    item_map& as_item_map();
    const item_map& as_item_map() const ;
    
    const JsonValue& operator[](const std::string& name) const;
    JsonValue& operator[](const std::string& name);

    const JsonValue& operator[](const char* name) const;
    JsonValue& operator[](const char* name);
    
    JsonValue& at(unsigned int idx);
    const JsonValue& at(unsigned int index) const;

    void removeChild(const std::string& childName);
    JsonValue() ;

    void toString(std::ostream& out, bool prettyPrint = false) const;

    item_map::const_iterator begin() const;
    item_map::const_iterator end() const;

    size_t count() const;

    bool contains(const std::string& name) const;

    static JsonValue::ptr newNodeAsJson(JsonValue::item_map* preset = NULL) {
        return ptr(new JsonValue(preset == NULL ? new JsonValue::item_map : preset));
    }

    static JsonValue::ptr newNodeAsInt(int* val = NULL) {
        return ptr(new JsonValue(val == NULL ? new int(0) : val));
    }

    static JsonValue::ptr newNodeAsArray(JsonValue::array* preset = NULL) {
        return ptr(new JsonValue(preset == NULL ? new JsonValue::array : preset));
    }

    static JsonValue::ptr newNodeAsString(std::string* preset = NULL) {
        return ptr(new JsonValue(preset == NULL ? new std::string : preset));
    }

    static JsonValue::ptr newNodeAsBool(bool* preset = NULL) {
        return ptr(new JsonValue(preset == NULL ? new bool : preset));
    }

    static JsonValue::ptr newNodeAsFloat(float* preset = NULL) {
        return ptr(new JsonValue(preset == NULL ? new float : preset));
    }

    json_item_type getType() const {
        return (json_item_type) item_type;
    }

    ~JsonValue() ;

    friend std::ostream& operator<< (std::ostream &out, const JsonValue& item);

private:
    template <typename T>
    void build_from_null() {
        if ( item_type == json_null) {
            *this = T();
        }
    }

    void toString(std::ostream& out, bool prettyPrint, int ident) const;
    
    friend class JsonReader;
    gdx_shared_ptr<void> item_val;
    json_item_type item_type;
    
    operator array& ();
    operator item_map& ();
    operator int&();
    operator bool&();
    operator float&();
    operator std::string&();
};

}

#endif // GDX_CPP_UTILS_JSONITEM_HPP
