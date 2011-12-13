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

#include "JsonValue.hpp"

#include <cassert>
#include <algorithm>

using namespace gdx_cpp::utils;

JsonValue::JsonValue(int val) : item_type(json_int) {
    item_val = std::tr1::shared_ptr<void>( new int(val) );
}

JsonValue::JsonValue(int* val) : item_val(std::tr1::shared_ptr<void>(val)), item_type(json_int) {

}

JsonValue::JsonValue(float val) : item_type(json_float) {
    item_val = std::tr1::shared_ptr<void>( new int(val) );
}

JsonValue::JsonValue(float* val) : item_val(std::tr1::shared_ptr<void>(val)), item_type(json_float)
{
}

JsonValue::JsonValue(bool* val) : item_type(json_bool) , item_val(std::tr1::shared_ptr<void>( val )) {
}

JsonValue::JsonValue(const std::string& val)
        : item_type(json_string)
{
    item_val = std::tr1::shared_ptr<void>( new std::string(val) );
}

JsonValue::JsonValue(std::string* val)
        : item_type(json_string), item_val(std::tr1::shared_ptr<void>( val ))
{
}

JsonValue::JsonValue(const item_map& val) : item_type(json_json) {
    item_val = std::tr1::shared_ptr<void>( new item_map(val) );
}

JsonValue::JsonValue(const array& val) : item_type(json_list) {
    item_val = std::tr1::shared_ptr<void>( new array(val) );
}

JsonValue::JsonValue(bool val) : item_type(json_bool) , item_val(std::tr1::shared_ptr<void>(new bool(val))) {
}

gdx_cpp::utils::JsonValue& gdx_cpp::utils::JsonValue::at(int idx)
{
    assert(item_type == json_list);
#ifdef GDX_DEBUGGING
    array& asArray = *this;
    assert( asArray.size() > idx );
    return *(asArray[idx]);
#else
    return *((array&)*this)[idx];
#endif
}

JsonValue& JsonValue::operator[](const std::string& name)
{
    assert(item_type == json_json);
#ifdef GDX_DEBUGGING
    item_map& map = *this;
    assert(map.count(name));
    return *(map[name]);
#else
    return *((item_map&)*this)[name];
#endif
}

size_t JsonValue::count()
{
   if (item_type == json_json) {
       return ((item_map&)*this).size();
   } else if (item_type == json_list) {
       return ((array&)*this).size();
   }
   return 1;
}

bool JsonValue::contains(const std::string& name) const
{
    assert(item_type == json_json);    
    return ((item_map&) *this).count(name) > 0;
}

JsonValue::~JsonValue() {
    if (item_type == json_list) {
        array& lst = *this;

        array::iterator it = lst.begin();
        array::iterator end = lst.end();

        for (; it != end; ++it) {
            delete *it;
        }
    } else if (item_type == json_json) {
        item_map& map = *this;

        item_map::iterator it = map.begin();
        item_map::iterator end = map.end();

        for (; it != end; ++it) {
            delete it->second;
        }
    }
}

JsonValue::item_map::const_iterator JsonValue::begin() {
    assert(item_type == json_json);
    return ((item_map&)*this).begin();
}

JsonValue::item_map::const_iterator JsonValue::end() {
    assert(item_type == json_json);
    return ((item_map&)*this).end();
}

JsonValue::JsonValue() : item_type(json_null)
{
}

//sob... c++ sucks A LOT sometimes...
namespace gdx_cpp {
namespace utils {

std::ostream& operator<< (std::ostream& out, gdx_cpp::utils::JsonValue& item) {
    switch (item.getType()) {
    case json_bool:
        out << ((bool)item ? "true" : "false");
        break;
    case json_float:
        out << (float) item;
        break;
    case json_int:
        out << (int) item;
        break;
    case json_list: {
        JsonValue::array::iterator iit = ((JsonValue::array&)item).begin();
        JsonValue::array::iterator eend = ((JsonValue::array&)item).end();

        out << "[ ";

        for (; iit != eend;) {
            out << **iit;
            if (++iit == eend)
                break;
            out << " , ";
        }

        out << " ]";
    }
    break;
    case json_json: {

        JsonValue::item_map::const_iterator it = item.begin();
        JsonValue::item_map::const_iterator end = item.end();

        out << "{ ";
        
        for (; it != end;) {        
            out << it->first << " : " << *it->second;
            if (++it == end)
                break;            
            out << " , ";
        }
        out << " }";
    }
    break;
    case json_null:
        out << "null";
        break;
    case json_string:
        out << "\"" << (std::string&) item << "\"";
        break;
    };

    return out;
}
}
}

