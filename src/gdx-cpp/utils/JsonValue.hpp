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

#include <stddef.h>
#include <cassert>
#include <fstream>
#include <initializer_list>
#include <map>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <vector>

#include "gdx-cpp/internal/memory"

namespace gdx {

/**
 * 
 * 
 */
class JsonValue {   
public:
    enum json_item_type {        
        json_null,
        json_string,
        json_int,
        json_bool,
        json_list,
        json_json,
        json_float
    };

    typedef ref_ptr_maker< JsonValue >::shared_ptr_t ptr;
    
    typedef std::map< std::string, JsonValue > item_map;
    typedef std::vector< JsonValue > array;

protected:
    union json_internal_type_u {
        explicit json_internal_type_u() { }
        ~json_internal_type_u() { }
        
        int int_val;
        float float_val;
        std::string string_val;
        item_map item_map_val;
        array array_val;
        bool bool_val;
    };
    
    struct json_value_t {
        json_item_type type;
        json_internal_type_u value;
                
        template <typename T>
        explicit json_value_t(const T& val) {
            *this = val;
        }        
        
        ~json_value_t() {
            switch(type) {
                case json_json:
                    value.item_map_val.~map();
                    break;
                case json_list:
                    value.array_val.~vector();
                    break;
                case json_string:
                    value.string_val.~basic_string();                    
                    break;
                default:
                    break;
            }
        }
        
        json_value_t() : type(json_null) {
        }
        
        json_value_t& operator=(std::nullptr_t val) {
            type = json_null;            
            return * this;
        }
        
        json_value_t& operator=(const char* val) {
            type = json_string;
            new (&value.string_val) std::string(val);
            return * this;
        }
        
        json_value_t& operator=(const std::string& val) {
            type = json_string;
            new (&value.string_val) std::string(val);
            return * this;
        }
                
        json_value_t& operator=(int val) {
            type = json_int;
            new (&value.int_val) int(val);
            return * this;
        }
        
        json_value_t& operator=(bool val) {
            type = json_bool;
            new (&value.bool_val) bool(val);
            return *this;
        }
        
        json_value_t& operator=(float val) {
            type = json_float;
            new (&value.float_val) float(val);
            return *this;
        }
        
        json_value_t& operator =(const item_map& val) {
            type = json_json;
            new (&value.item_map_val) item_map(val);
            return *this;
        }
        
        json_value_t& operator = (const array& val) {
            type = json_list;
            new (&value.array_val) array(val);
            return *this;
        }
                
        json_value_t& operator = (const json_value_t& other) {
             switch(other.type) {
                case json_bool:
                    new (&value.bool_val) bool(other.value.bool_val);
                    break;
                case json_float:
                    new (&value.float_val) float(other.value.float_val);
                    break;
                case json_int:
                    new (&value.int_val) int(other.value.int_val);
                    break;
                case json_json:
                    new (&value.item_map_val) item_map(other.value.item_map_val);
                    break;
                case json_list:
                    new (&value.array_val) array(other.value.array_val);
                    break;
                case json_string:
                    new (&value.string_val) std::string(other.value.string_val);
                    break;
                case json_null:
                    break;
            }
            
            this->type = other.type;            
            return *this;
        }
        
        json_value_t(const json_value_t& other) {
            *this = other;
        }
    };
    
public:
    static JsonValue make_array(std::initializer_list< JsonValue > items) {
        JsonValue val;
        for (const auto& item : items) {
            val.as_array().push_back(item);
        }
        return val;
    }
    
    JsonValue();  
    
    JsonValue(std::initializer_list<JsonValue> list) {
        assert(list.size() % 2 == 0 && "JsonValue initializer list must be in key, pair form");
        int i = 0;
        JsonValue key;
        for(auto item : list) {
            if (i++ % 2 == 0) {
                assert(item.getType() == json_string);
                key = item;
                
            } else {                
                this->as_item_map()[key.as_string()] = item;
            }
        }
    }
    
    
    
    //we don't want implicit conversions to any other types than the ones specified
    template <typename T>
    JsonValue(const T& value) = delete;
    
    JsonValue(std::nullptr_t null) : item_val(null) { }
    JsonValue(const char* char_data) : item_val(char_data) { }
    JsonValue(int value) : item_val(value) { }
    JsonValue(bool value) : item_val(value) { }
    JsonValue(float value) : item_val(value) { }    
    JsonValue(const array& value) : item_val(value) { }
    JsonValue(const item_map& value) : item_val(value) { }
    JsonValue(const std::string& value) : item_val(value) { }    
    JsonValue(const JsonValue::ptr& other) : item_val(other->item_val) { }    
    JsonValue(const JsonValue& other) : item_val(other.item_val) { }

    //we don't want implicit assignment's too
    template <typename T>
    JsonValue& operator = (const T& other) = delete;

    JsonValue& operator = (int value) { this->item_val = value; return *this; }
    JsonValue& operator = (bool value) { this->item_val = value; return *this;  }    
    JsonValue& operator = (float value) { this->item_val = value; return *this; }
    JsonValue& operator = (const array& value) { this->item_val = value; return *this; }
    JsonValue& operator = (const item_map& value) { this->item_val = value; return *this; }
    JsonValue& operator = (const std::string& value) { this->item_val = value; return *this; }
    JsonValue& operator = (std::nullptr_t value) { this->item_val = nullptr; return *this; }
    
    JsonValue& operator = (const JsonValue& other) ;

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

    void toString(std::ostream& out, bool prettyPrint = false) const;

    std::string toString() const;
    
    item_map::const_iterator begin() const;
    item_map::const_iterator end() const;

    size_t count() const;

    bool contains(const std::string& name) const;

    json_item_type getType() const {
        return item_val.type;
    }

    ~JsonValue() ;

    friend std::ostream& operator<< (std::ostream &out, const JsonValue& item);
    
private:
    void toString(std::ostream& out, bool prettyPrint, int ident) const;
    
    friend class JsonReader;
    
    operator array& () = delete;
    operator item_map& () = delete;
    operator int&() = delete;
    operator bool&() = delete;
    operator float&() = delete;
    operator std::string&() = delete;
    
    json_value_t item_val;
};

}

#endif // GDX_CPP_UTILS_JSONITEM_HPP
