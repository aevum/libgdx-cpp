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

using namespace gdx;

template <typename T>
struct json_deleter {
    void operator()(void* item) {
        delete static_cast<T*>(item);
    }
};

JsonValue::JsonValue(int val) : item_type(json_int) {
    item_val = gdx_shared_ptr<void>( new int(val), json_deleter<int>() );
}

JsonValue::JsonValue(int* val) : item_val(gdx_shared_ptr<void>(val, json_deleter<int>())),
item_type(json_int) {

}

JsonValue::JsonValue(float val) : item_val(gdx_shared_ptr<void>( new float(val), json_deleter<float>() ) ),
item_type(json_float) {

}

JsonValue::JsonValue(float* val) : item_val(gdx_shared_ptr<void>(val, json_deleter<float>())),
item_type(json_float)
{
}

JsonValue::JsonValue(bool* val) : item_val(gdx_shared_ptr<void>( val, json_deleter<bool>() )),
item_type(json_bool) {
}

JsonValue::JsonValue(const std::string& val)
    : item_val(gdx_shared_ptr<void>( new std::string(val), json_deleter<std::string>())),
item_type(json_string)
{
}

JsonValue::JsonValue(std::string* val)
    : item_val(gdx_shared_ptr<void>( val , json_deleter<std::string>())),
item_type(json_string)
{
}

JsonValue::JsonValue(const item_map& val) : item_type(json_json) {
    item_val = gdx_shared_ptr<void>( new item_map(val), json_deleter<item_map>() );
}

JsonValue::JsonValue(const array& val) : item_type(json_list) {
    item_val = gdx_shared_ptr<void>( new array(val), json_deleter<item_map>() );
}

JsonValue::JsonValue(bool val) : item_val(gdx_shared_ptr<void>(new bool(val), json_deleter<bool>())),
item_type(json_bool) {
}

JsonValue& JsonValue::at(unsigned int idx)
{
    if (this->item_type == json_null) {
        array* new_array = new array;
        this->item_val = gdx_shared_ptr<void>(new_array, json_deleter<array>());
        this->item_type = json_list;
    }

    assert(item_type == json_list);
    array& thisAsArray = this->as_array();

    if (idx >= thisAsArray.size()) {
        thisAsArray.resize(idx + 1);
    }

    if (!thisAsArray[idx]) {
        thisAsArray[idx] = ptr(new JsonValue);
    }

#ifdef GDX_DEBUGGING
    array& asArray = *this;
    assert( asArray.size() > idx );
    return *(asArray[idx]);
#else
    return *this->as_array()[idx];
#endif
}

const JsonValue& JsonValue::at(unsigned int index) const
{
    assert(item_type == json_list);
    const array& thisAsArray = this->as_array();
    assert(thisAsArray.size() > index);

    return *thisAsArray[index];
}

const JsonValue& JsonValue::operator[](const std::string& name) const
{
    return operator[](name.c_str());
}

JsonValue& JsonValue::operator[](const std::string& name)
{
    return operator[](name.c_str());
}

const JsonValue& JsonValue::operator[](const char* name) const
{
    assert(item_type == json_json);
    
    item_map::const_iterator found = this->as_item_map().find(name);
    
    if (found == this->as_item_map().end()) {
        throw std::runtime_error("Missing field named [" + std::string(name) + "]");
    }
    
    return *found->second;
}

JsonValue& JsonValue::operator[](const char* name)
{
    if (this->item_type == json_null) {
        this->item_val = gdx_shared_ptr<void>(new item_map, json_deleter<item_map>());
        this->item_type = json_json;
    }
    
    assert(item_type == json_json);
    
    item_map& thisAsMap = this->as_item_map();
    
    if (thisAsMap.count(name) == 0) {
        thisAsMap[name] = ptr(new JsonValue);
    }
    
    return *thisAsMap[name];
}

size_t JsonValue::count() const
{
    if (item_type == json_json) {
        return this->as_item_map().size();
    } else if (item_type == json_list) {
        return this->as_array().size();
    } else if (item_type == json_null) {
        return 0;
    }

    return 1;
}

bool JsonValue::contains(const std::string& name) const
{
    if (item_type == json_null) {
        return false;
    }
    assert(item_type == json_json);
    return this->as_item_map().count(name) > 0;
}

JsonValue::~JsonValue() {
}

JsonValue::item_map::const_iterator JsonValue::begin() const {
    assert(item_type == json_json);
    return this->as_item_map().begin();
}

JsonValue::item_map::const_iterator JsonValue::end() const {
    assert(item_type == json_json);
    return this->as_item_map().end();
}

JsonValue::JsonValue() : item_type(json_null)
{
}

void JsonValue::toString(std::ostream& out, bool prettyPrint, int ident) const
{
    std::string identLevel(ident, '\t');

    switch (item_type) {
    case json_bool:
        out << (this->as_bool() ? "true" : "false");
        break;
    case json_float:
        out << this->as_float();
        break;
    case json_int:
        out << this->as_int();
        break;
    case json_list: {
        JsonValue::array::const_iterator iit = this->as_array().begin();
        JsonValue::array::const_iterator eend = this->as_array().end();

        out << "[";
        if (prettyPrint) out << std::endl;

        for (; iit != eend;) {
            out << identLevel;

            (*iit)->toString(out, prettyPrint, ident + 1);

            if (++iit == eend)
                break;

            out << ",";
            if (prettyPrint) out << std::endl;
        }

        out << "]";
    }
    break;
    case json_json: {

        JsonValue::item_map::const_iterator it =  this->as_item_map().begin();
        JsonValue::item_map::const_iterator end = this->as_item_map().end();

        out << "{";
        if (prettyPrint) out << std::endl;

        for (; it != end;) {
            out << identLevel;

            out << '"' << it->first << "\" : ";
            it->second->toString(out, prettyPrint, ident + 1);

            if (++it == end) {
                if (prettyPrint) out << std::endl;
                break;
            }

            out << ",";
            if (prettyPrint) out << std::endl;
        }
        if (prettyPrint) out << identLevel.substr(0, identLevel.length() - 1);
        out << " }";
    }
    break;
    case json_null:
        out << "null";
        break;
    case json_string:
        out << "\"" << this->as_string() << "\"";
        break;
    };
}


void JsonValue::toString(std::ostream& out, bool prettyPrint) const
{
    toString(out, prettyPrint, 1);
}

//sob... c++ sucks A LOT sometimes...
namespace gdx {
namespace utils {

std::ostream& operator<< (std::ostream& out, const JsonValue& item) {
    item.toString(out);
    return out;
}

}
}

JsonValue& JsonValue::operator+=(const JsonValue& other) {
    assert(item_type == json_json && other.item_type == json_json);

    item_map& thisAsMap = this->as_item_map();
    const item_map& otherAsMap = other.as_item_map();

    item_map::const_iterator it = otherAsMap.begin();
    item_map::const_iterator end = otherAsMap.end();

    for (; it != end; ++it) {
        ptr newValue = ptr(new JsonValue);
        *newValue = *it->second;
        thisAsMap[it->first] = newValue;
    }

    return *this;
}
JsonValue::JsonValue(JsonValue::item_map* val) : item_val(gdx_shared_ptr<void>( val , json_deleter<item_map>() )),
item_type(json_json) {
    
}

JsonValue::JsonValue(JsonValue::array* val) : item_val(gdx_shared_ptr<void>( val, json_deleter<array>() )),
item_type(json_list) {    
}

JsonValue& JsonValue::operator=(const std::string& other) {
    if (item_type == json_null) {
        this->item_val = gdx_shared_ptr<void>(new std::string(other), json_deleter<std::string>());
        this->item_type = json_string;
    } else {
        this->as_string() = other;
    }
    return *this;
}

JsonValue& JsonValue::operator=(const char* other) {
    if (item_type == json_null) {
        this->item_val = gdx_shared_ptr<void>(new std::string(other), json_deleter<std::string>());
        this->item_type = json_string;
    } else {
        this->as_string() = other;
    }
    return *this;
}

JsonValue& JsonValue::operator=(int other) {
    if (item_type == json_null) {
        this->item_val = gdx_shared_ptr<void>(new int(other), json_deleter<int>());
        this->item_type = json_int;
    } else {
        this->as_int() = other;
    }
    return *this;
}

JsonValue& JsonValue::operator=(bool other) {
    if (item_type == json_null) {
        this->item_val = gdx_shared_ptr<void>(new bool(other), json_deleter<bool>());
        this->item_type = json_bool;
    } else {
        this->as_bool() = other;
    }
    return *this;
}

JsonValue& JsonValue::operator=(float other) {
    if (item_type == json_null) {
        this->item_val = gdx_shared_ptr<void>(new float(other), json_deleter<float>());
        this->item_type = json_float;
    } else {
        this->as_float() = other;
    }
    return *this;
}

JsonValue& JsonValue::operator=(const JsonValue::array& other) {
    if (item_type == json_null) {
        this->item_val = gdx_shared_ptr<void>(new array(other), json_deleter<array>());
        this->item_type = json_list;
    } else {
        this->as_array() = other;
    }
    return *this;
}

JsonValue& JsonValue::operator=(const JsonValue& other) {
    this->item_type = other.item_type;
    this->item_val = other.item_val;

    return *this;
}
JsonValue& JsonValue::operator=(const JsonValue::ptr& other) {
    this->item_type = other->item_type;
    this->item_val = other->item_val;

    return *this;
}

JsonValue& JsonValue::operator+(const JsonValue& other) {
    return *this += other;
}

int& JsonValue::as_int() {
    build_from_null<int>();
    assert(item_type == json_int);
    return *(int*)item_val.get();
}

const int& JsonValue::as_int() const {
    assert(item_type == json_int);
    return *(int*)item_val.get();
}

bool& JsonValue::as_bool() {
    build_from_null<bool>();
    assert(item_type == json_bool);
    return *(bool*)item_val.get();
}

const bool& JsonValue::as_bool() const {
    assert(item_type == json_bool);
    return *(bool*)item_val.get();
}

float& JsonValue::as_float() {
    build_from_null<float>();
    assert(item_type == json_float);
    return *(float*)item_val.get();
}

const float& JsonValue::as_float() const {
    assert(item_type == json_float);
    return *(float*)item_val.get();
}

std::string& JsonValue::as_string() {
    build_from_null<std::string>();
    assert(item_type == json_string);
    return *(std::string*)item_val.get();
}

const std::string& JsonValue::as_string() const {
    assert(item_type == json_string);
    return *(std::string*)item_val.get();
}

JsonValue::array& JsonValue::as_array() {
    build_from_null<array>();
    assert(item_type == json_list);
    return *(array*)item_val.get();
}

const JsonValue::array& JsonValue::as_array() const {
    assert(item_type == json_list);
    return *(array*)item_val.get();
}

JsonValue::item_map& JsonValue::as_item_map() {
    build_from_null<item_map>();
    assert(item_type == json_json);
    return *(item_map*)item_val.get();
}

const JsonValue::item_map& JsonValue::as_item_map() const {
    assert(item_type == json_json);
    return *(item_map*)item_val.get();
}

void JsonValue::removeChild ( const std::string& childName ) {
    assert(item_type == json_json);
    this->as_item_map().erase(childName);
}
