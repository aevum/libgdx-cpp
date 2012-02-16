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

#include <tr1/memory>
#include <tr1/unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <stdexcept>
#include "gdx-cpp/utils/Aliases.hpp"

namespace gdx_cpp {

namespace utils {

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
    typedef ref_ptr_maker< JsonValue >::type ptr;
    typedef std::tr1::unordered_map< std::string, ptr > item_map;
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
    JsonValue(item_map* val) : item_val(std::tr1::shared_ptr<void>( val )),item_type(json_json) {}
    JsonValue(const array& val) ;
    JsonValue(array* val) : item_val(std::tr1::shared_ptr<void>( val )), item_type(json_list) {}
    JsonValue(const JsonValue& other) : item_val(other.item_val), item_type(other.item_type)
    {
    }
   
    JsonValue& operator = (const std::string& other) {
        if (item_type == json_null) {
            this->item_val = std::tr1::shared_ptr<void>(new std::string(other));
            this->item_type = json_string;
        } else {
            this->as_string() = other;
        }
        return *this;
    }

    JsonValue& operator = (const char* other) {
        if (item_type == json_null) {
            this->item_val = std::tr1::shared_ptr<void>(new std::string(other));
            this->item_type = json_string;
        } else {
            this->as_string() = other;
        }
        return *this;
    }
    
    JsonValue& operator = (int other) {
        if (item_type == json_null) {
            this->item_val = std::tr1::shared_ptr<void>(new int(other));
            this->item_type = json_int;
        } else {
            this->as_int() = other;
        }
        return *this;
    }

    JsonValue& operator = (bool other) {
        if (item_type == json_null) {
            this->item_val = std::tr1::shared_ptr<void>(new bool(other));
            this->item_type = json_bool;
        } else {
            this->as_bool() = other;
        }
        return *this;
    }

    JsonValue& operator = (float other) {
        if (item_type == json_null) {
            this->item_val = std::tr1::shared_ptr<void>(new float(other));
            this->item_type = json_float;
        } else {
            this->as_float() = other;
        }
        return *this;
    }

    JsonValue& operator = (const array& other) {
        if (item_type == json_null) {
            this->item_val = std::tr1::shared_ptr<void>(new array(other));
            this->item_type = json_list;
        } else {
            this->as_array() = other;
        }
        return *this;
    }

    JsonValue& operator = (const JsonValue& other) {
        this->item_type = other.item_type;
        this->item_val = other.item_val;

        return *this;
    }

    JsonValue& operator = (const ptr& other) {
        this->item_type = other->item_type;
        this->item_val = other->item_val;
        
        return *this;
    }

    JsonValue& operator + (const JsonValue& other) {
        return *this += other;
    }

    JsonValue& operator += (const JsonValue& other) ;
   
    int& as_int()       { build_from_null<int>(); assert(item_type == json_int); return *(int*)item_val.get(); }
    const int& as_int() const { assert(item_type == json_int); return *(int*)item_val.get(); }

    bool& as_bool()       { build_from_null<bool>(); assert(item_type == json_bool); return *(bool*)item_val.get(); }
    const bool& as_bool() const { assert(item_type == json_bool); return *(bool*)item_val.get(); }

    float& as_float()       { build_from_null<float>(); assert(item_type == json_float); return *(float*)item_val.get(); }
    const float& as_float() const { assert(item_type == json_float); return *(float*)item_val.get(); }

    std::string& as_string()       { build_from_null<std::string>(); assert(item_type == json_string); return *(std::string*)item_val.get(); }
    const std::string& as_string() const { assert(item_type == json_string); return *(std::string*)item_val.get(); }

    array& as_array()       { build_from_null<array>(); assert(item_type == json_list); return *(array*)item_val.get(); }
    const array& as_array() const { assert(item_type == json_list); return *(array*)item_val.get(); }
    
    item_map& as_item_map()       { build_from_null<item_map>(); assert(item_type == json_json); return *(item_map*)item_val.get(); }
    const item_map& as_item_map() const { assert(item_type == json_json); return *(item_map*)item_val.get(); }
    
    const JsonValue& operator[](const std::string& name) const;
    JsonValue& operator[](const std::string& name);

    const JsonValue& operator[](const char* name) const;
    JsonValue& operator[](const char* name);
    
    JsonValue& at(unsigned int idx);
    const JsonValue& at(unsigned int index) const;
    
    JsonValue() ;

    void toString(std::ostream& out, bool prettyPrint = false) const;

    item_map::const_iterator begin() ;
    item_map::const_iterator end() ;

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
    std::tr1::shared_ptr<void> item_val;
    json_item_type item_type;
    
    operator array& ();
    operator item_map& ();
    operator int&();
    operator bool&();
    operator float&();
    operator std::string&();
};

}

}

#endif // GDX_CPP_UTILS_JSONITEM_HPP
