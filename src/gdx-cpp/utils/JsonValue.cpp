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

#include <gdx-cpp/Gdx.hpp>
#include <cassert>
#include <utility>
#include <sstream>

#include "JsonValue.hpp"

using namespace gdx;

template <typename T>
struct json_deleter {
    void operator()(void* item) {
        delete static_cast<T*>(item);
    }
};

JsonValue::JsonValue()
{
}

JsonValue& JsonValue::at(unsigned int idx)
{
    if (this->item_val.type == json_null) {
        this->item_val = array();
    }

    assert(item_val.type == json_list);
    array& thisAsArray = this->as_array();

    if (idx >= thisAsArray.size()) {
        thisAsArray.resize(idx + 1);
    }

    return this->as_array()[idx];
}

const JsonValue& JsonValue::at(unsigned int index) const
{
    assert(item_val.type == json_list);
    const array& thisAsArray = this->as_array();
    assert(thisAsArray.size() > index);

    return thisAsArray[index];
}

const JsonValue& JsonValue::operator[](const char* name) const
{
    assert(item_val.type == json_json);
    
    auto found = this->as_item_map().find(name);
    
    if (found == this->as_item_map().end()) {
        gdx_log_error("gdx","Missing field named [%s]", name);
    }
    
    return found->second;
}

JsonValue& JsonValue::operator[](const char* name)
{
    if (this->item_val.type == json_null) {
        this->item_val = item_map();
    }
    
    assert(item_val.type == json_json);
    
    return this->as_item_map()[name];
}


const JsonValue& JsonValue::operator[](const std::string& name) const
{
    return operator[](name.c_str());
}

JsonValue& JsonValue::operator[](const std::string& name)
{
    return operator[](name.c_str());
}

size_t JsonValue::count() const
{
    if (item_val.type == json_json) {
        return this->as_item_map().size();
    } else if (item_val.type == json_list) {
        return this->as_array().size();
    } else if (item_val.type == json_null) {
        return 0;
    }

    return 1;
}

bool JsonValue::contains(const std::string& name) const
{
    if (item_val.type == json_null) {
        return false;
    }
    assert(item_val.type == json_json);
    return this->as_item_map().count(name) > 0;
}

JsonValue::~JsonValue() {
}

JsonValue::item_map::const_iterator JsonValue::begin() const {
    assert(item_val.type == json_json);
    return this->as_item_map().begin();
}

JsonValue::item_map::const_iterator JsonValue::end() const {
    assert(item_val.type == json_json);
    return this->as_item_map().end();
}

void JsonValue::toString(std::ostream& out, bool prettyPrint, int ident) const
{
    std::string identLevel(ident, ' ');

    switch (item_val.type) {
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
        auto iit = this->as_array().begin();
        auto eend = this->as_array().end();

        out << "[";
        for (; iit != eend;) {
            (*iit).toString(out, prettyPrint, ident + 1);

            if (++iit == eend)
                break;

            out << ",";
            if (prettyPrint) out << std::endl << identLevel;
        }

        out << "]";
    }
    break;
    case json_json: {

        auto it =  this->as_item_map().begin();
        auto end = this->as_item_map().end();

        out << "{";
        if (prettyPrint) out << std::endl;

        for (; it != end;) {
            out << identLevel;

            out << '"' << it->first << "\" : ";
            it->second.toString(out, prettyPrint, ident + 1);

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
    item_map& thisAsMap = this->as_item_map();
    const item_map& otherAsMap = other.as_item_map();

    auto it = otherAsMap.begin();
    auto end = otherAsMap.end();

    for (; it != end; ++it) {
        thisAsMap[it->first] = it->second;
    }

    return *this;
}

JsonValue& JsonValue::operator=(const JsonValue& other) {
    this->item_val = other.item_val;

    return *this;
}

JsonValue& JsonValue::operator+(const JsonValue& other) {
    return *this += other;
}

int& JsonValue::as_int() {
    if (item_val.type == json_null) {
        item_val = 0;
    }
    assert(item_val.type == json_int);
    return item_val.value.int_val;
}

const int& JsonValue::as_int() const {
    assert(item_val.type == json_int);
    return item_val.value.int_val;
}

bool& JsonValue::as_bool() {
    if (item_val.type == json_null) {
        item_val = false;
    }

    if (item_val.type != json_bool) {
        gdx_log_debug("JsonValue", "deu pau %s", toString().c_str());
    }

    assert(item_val.type == json_bool);
    return item_val.value.bool_val;
}

const bool& JsonValue::as_bool() const {
    assert(item_val.type == json_bool);
    return item_val.value.bool_val;
}

float& JsonValue::as_float() {
    if (item_val.type == json_null) {
        item_val = 1.0f;
    }
    
    assert(item_val.type == json_float);
    return item_val.value.float_val;
}

const float& JsonValue::as_float() const {
    assert(item_val.type == json_float);
    return item_val.value.float_val;
}

std::string& JsonValue::as_string() {
    if (item_val.type == json_null) {
        item_val = std::string();
    }
    assert(item_val.type == json_string);
    return item_val.value.string_val;
}

const std::string& JsonValue::as_string() const {
    assert(item_val.type == json_string);
    return item_val.value.string_val;
}

JsonValue::array& JsonValue::as_array() {
    if (item_val.type == json_null) {
        item_val = array();
    }
    
    return item_val.value.array_val;
}

const JsonValue::array& JsonValue::as_array() const {
    assert(item_val.type == json_list);
    return item_val.value.array_val;
}

JsonValue::item_map& JsonValue::as_item_map() {
    if (item_val.type == json_null) {
        item_val = item_map();
    }
    
    return item_val.value.item_map_val;
}

const JsonValue::item_map& JsonValue::as_item_map() const {
    assert(item_val.type == json_json);
    return item_val.value.item_map_val;
}

void JsonValue::removeChild ( const std::string& childName ) {
    assert(item_val.type == json_json);
    this->as_item_map().erase(childName);
}

std::string JsonValue::toString() const
{
    std::stringstream ss;
    this->toString(ss, true);
    return ss.str();
}
