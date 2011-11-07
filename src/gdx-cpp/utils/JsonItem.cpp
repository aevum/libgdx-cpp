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

#include "JsonItem.hpp"

#include <cassert>

using namespace gdx_cpp::utils;

json_item::json_item(int val) : item_type(json_int) {
    item_val = std::tr1::shared_ptr<void>( new int(val) );
}

json_item::json_item(int* val) : item_val(std::tr1::shared_ptr<void>(val)), item_type(json_int) {
    
}

json_item::json_item(float val) : item_type(json_float) {
    item_val = std::tr1::shared_ptr<void>( new int(val) );
}

json_item::json_item(float* val) : item_val(std::tr1::shared_ptr<void>(val)), item_type(json_float)
{    
}

json_item::json_item(bool* val) : item_type(json_bool) , item_val(std::tr1::shared_ptr<void>( val )) {
}

json_item::json_item(const std::string& val)
    : item_type(json_string)
{
    item_val = std::tr1::shared_ptr<void>( new std::string(val) );
}

json_item::json_item(std::string* val)
    : item_type(json_string), item_val(std::tr1::shared_ptr<void>( val ))
{
}

json_item::json_item(const item_map& val) : item_type(json_json) {
    item_val = std::tr1::shared_ptr<void>( new item_map(val) );
}

json_item::json_item(const array& val) : item_type(json_list) {
    item_val = std::tr1::shared_ptr<void>( new array(val) );
}

gdx_cpp::utils::json_item& json_item::operator[](const std::string& name) {
    assert(item_type == json_json);

    item_map map = *this;
    return *map[name];
}

json_item::operator int() {
    assert(item_type == json_int);
    return *(int*)item_val.get();
}

json_item::operator std::string& () {
    assert(item_type == json_string);
    return *(std::string*) item_val.get();
}

json_item::operator json_item::array& () {
    assert(item_type == json_list);
    return *(json_item::array *) item_val.get();
}

json_item::operator json_item& () {
    assert(item_type == json_json);
    return *(json_item*) item_val.get();
}

json_item::operator bool() {
    assert(item_type == json_bool);
    return *(bool*) item_val.get();
}

json_item::operator std::tr1::unordered_map< std::string, json_item* >&() {
    assert(item_type == json_json);
    return *(item_map*) item_val.get();
}

json_item::json_item(bool val) : item_type(json_bool) , item_val(std::tr1::shared_ptr<void>(new bool(val))) {
}

gdx_cpp::utils::json_item::operator float()
{
    assert(item_type == json_float);
    return *(float*) item_val.get();
}
