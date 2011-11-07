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
#include <list>
#include <string>

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

struct json_item {
    typedef ref_ptr_maker< json_item >::type ptr;
    typedef std::tr1::unordered_map< std::string, json_item* > item_map;
    typedef std::list< json_item* > array;

    
    json_item(int val) ;
    json_item(int* val) ;
    json_item(float val) ;
    json_item(float* val) ;
    json_item(bool val) ;
    json_item(bool* val) ;
    json_item(const std::string& val) ;
    json_item(std::string* val) ;
    json_item(const item_map& val) ;
    json_item(item_map* val) : item_type(json_json), item_val(std::tr1::shared_ptr<void>( val )) {}
    json_item(const array& val) ;
    json_item(array* val) : item_type(json_list) , item_val(std::tr1::shared_ptr<void>( val )) {}
    json_item(const json_item& other) : item_val(other.item_val), item_type(other.item_type)
    {
    }

    operator int();
    operator std::string&() ;
    operator array& () ;
    operator json_item&() ;
    operator bool () ;
    operator std::tr1::unordered_map< std::string, json_item* >& () ;
    operator float();
    
    json_item& operator [](const std::string& name) ;

    json_item() : item_type(json_null)
    {
    }

    item_map::const_iterator begin() {
        return ((item_map&)*this).begin();
    }

    item_map::const_iterator end() {
        return ((item_map&)*this).end();
    }
    
    static json_item* newNodeAsJson(json_item::item_map* preset = NULL) {
        return new json_item(preset == NULL ? new json_item::item_map : preset);
    }
    
    static json_item* newNodeAsInt(int* val = NULL) {
        return new json_item(val == NULL ? new int(0) : val);
    }
    
    static json_item* newNodeAsArray(json_item::array* preset = NULL) {
        return new json_item(preset == NULL ? new json_item::array : preset);
    }
    
    static json_item* newNodeAsString(std::string* preset = NULL) {
        return new json_item(preset == NULL ? new std::string : preset);
    }
    
    static json_item* newNodeAsBool(bool* preset = NULL) {
        return new json_item(preset == NULL ? new bool : preset);
    }

    static json_item* newNodeAsFloat(float* preset = NULL) {
        return new json_item(preset == NULL ? new float : preset);
    }

    json_item_type getType() {
        return (json_item_type) item_type;
    }
    
private:
    friend class JsonReader;
    std::tr1::shared_ptr<void> item_val;
    char item_type;
};

}

}

#endif // GDX_CPP_UTILS_JSONITEM_HPP
