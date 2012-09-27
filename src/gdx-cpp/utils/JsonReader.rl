
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

#include "JsonReader.hpp"
#include <stdexcept>
#include <list>
#include "StringConvertion.hpp"
#include <string.h>
#include "ArrayUtils.hpp"

#include "gdx-cpp/Gdx.hpp"

using namespace gdx::utils;
using namespace gdx;


JsonValue* JsonReader::root = 0;
JsonValue* JsonReader::current = 0;
std::list< JsonValue* > JsonReader::elements;

%%{
 machine json;
 write data;
}%%

JsonReader::JsonReader()
{
}

JsonValue::ptr JsonReader::parse (const std::string& json) {
    return parse(json.c_str(), 0, json.length());
}

JsonValue::ptr JsonReader::parse (const gdx::FileHandle& file) {
    try {
        gdx::FileHandle::buffer_ptr buffer;
        int size = file.readBytes(buffer);

        return parse(buffer.get(), 0, size);
    } catch (...) {
        gdx_log_error("gdx","Error parsing file: " + file.name());
    }
}

JsonValue::ptr JsonReader::parse (const char* data, int offset, int length) {
    elements.clear();

    unsigned int cs, top = 0;

    std::vector<int> stack;
    char* s = NULL, *p = (char*)data + offset,* pe = (char*)data + length,* eof = pe;

    std::list<std::string> names;

    bool needsUnescape = false;

    bool debug = false;

    if (debug) {
       gdx_log_debug("JsonReader","\n");
    }

    try {
        %%{
                machine json;


				prepush {
					stack.resize(top + 1);
				}
                action buffer {
                        s = p;
                        needsUnescape = false;
                }
                action needsUnescape {
                        needsUnescape = true;
                }
                action name {
                        std::string name(s, p-s);
                        s = p;
                        if (needsUnescape) name = unescape(name);
                        if (debug)gdx_log_debug("JsonReader","name: %s", name.c_str());
                        names.push_back(name);
                }
                action string {
                        std::string value(s, p-s);
                        s = p;
                        if (needsUnescape) value = unescape(value);
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug)gdx_log_debug("JsonReader","string: %s = %s", name.c_str(), value.c_str());;
                        string(name, value);
                }
                action number {
                        std::string value(s, p-s);
                        s = p;
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }
                        if (debug)gdx_log_debug("JsonReader","number: %s = %s", name.c_str(), value.c_str());

                        if (value.find(".") != std::string::npos) {
                            number(name, from_string<float>(value));
                        } else {
                            number(name, from_string<int>(value));
                        }
                }
                action trueValue {
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = true", name.c_str());
                        }
                        boolean(name, true);
                }
                action falseValue {
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = false", name.c_str());
                        }
                        boolean(name, false);
                }
                action null {
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","nulll: %s", name.c_str());
                        }
                        string(name, "");
                }
                action startObject {
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","startObject: %s", name.c_str());
                        }
                        startObject(name);
                        fcall object;
                }
                action endObject {
                        if (debug) {
                           gdx_log_debug("JsonReader","endObject");
                        }
                        pop();
                        fret;
                }
                action startArray {
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","startArray: %s", name.c_str());
                        }
                        startArray(name);
                        fcall array;
                }
                action endArray {
                        if (debug) {
                           gdx_log_debug("JsonReader","endArray");
                        }
                        pop();
                        fret;
                }

                # parse single quote
                quotedChars = (^["\\] | ('\\' ["\\/bfnrtu] >needsUnescape))*;
                unquotedChars = [a-zA-Z_$] ^([:}\],] | space)*;
                name = ('"' quotedChars >buffer %name '"') | unquotedChars >buffer %name;

                startObject = '{' @startObject;
                startArray = '[' @startArray;
                string = '"' quotedChars >buffer %string '"';
                unquotedString = unquotedChars >buffer %string;
                number = ('-'? ('0' | ([1-9][0-9]*)) ('.' [0-9]+)? ([eE] [+\-]? [0-9]+)?) >buffer %number;
                nullValue = 'null' %null;
                booleanValue = 'true' %trueValue | 'false' %falseValue;
                value = startObject | startArray | number | string @2 | nullValue @2 | booleanValue @2 | unquotedString @-1;

                nameValue = name space* ':' space* value;

                object := space* (nameValue space*)? (',' space* nameValue space*)** ','? space* '}' @endObject;

                array := space* (value space*)? (',' space* value space*)** ','? space* ']' @endArray;

                main := space* value space*;

                write init;
                write exec;
        }%%

    } catch (std::runtime_error& ex) {

    }

    if (p < pe) {
        
        int lineNumber = 1;
        for (char* aux = p; aux < pe; aux++)
            if (*aux == '\n') lineNumber++;
        gdx_log_error("gdx","Error parsing JSON on line " + to_string(lineNumber) + " near: " + std::string(p, pe - p));
    } else if (elements.size() != 0) {
        int element_type = elements.front()->item_type;

        std::list< JsonValue* >::iterator it = elements.begin();
        std::list< JsonValue* >::iterator end = elements.end();

        for (; it != end; ++it) {
            delete *it;
        }

        elements.clear();

        if (element_type == json_json)
            gdx_log_error("gdx","Error parsing JSON, unmatched brace.");
        else
            gdx_log_error("gdx","Error parsing JSON, unmatched bracket.");
    }

    JsonValue* _root = root;
    root = NULL;

    return gdx_shared_ptr< JsonValue >(_root);
}


void JsonReader::set (const std::string& name, gdx::JsonValue* value) {
    switch (current->item_type) {
        case json_json:
            ((JsonValue::item_map&)(*current))[name] = value;
            break;
        case json_list:
            ((JsonValue::array&)*current).push_back(value);
            break;
        default:
            current = value;
            break;
    }
}

void JsonReader::startObject (const std::string& name) {
    JsonValue* value = JsonValue::newNodeAsJson();

    if (current != NULL) {
        set(name, value);
    }

    elements.push_back(value);
    current = value;
}

void JsonReader::startArray (const std::string& name) {
    JsonValue* array_item = JsonValue::newNodeAsArray();

    if (current != NULL) {
        set(name, array_item);
    }

    elements.push_back(array_item);
    current = array_item;
}

void JsonReader::pop () {
    root = elements.back();
    elements.pop_back();
    current = elements.size() > 0 ? elements.back() : NULL;
}

void JsonReader::string (const std::string& name,const std::string& value) {
    set(name, JsonValue::newNodeAsString(new std::string(value)));
}

void JsonReader::number (const std::string& name, float value) {
    set(name, JsonValue::newNodeAsFloat(new float(value)));
}

void JsonReader::boolean (const std::string& name, bool value) {
    set(name, JsonValue::newNodeAsBool(new bool(value)));
}

std::string JsonReader::unescape (const std::string& value) {
    int length = value.length();
    std::stringstream buffer;
    for (int i = 0; i < length;) {
        char c = value[i++];
        if (c != '\\') {
            buffer << c;
            continue;
        }
        if (i == length) break;
        c = value[i++];
        if (c == 'u') {
            buffer << from_string< int >(value.substr(i, i + 4));
            i += 4;
            continue;
        }
        switch (c) {
        case '"':
        case '\\':
        case '/':
            break;
        case 'b':
            c = '\b';
            break;
        case 'f':
            c = '\f';
            break;
        case 'n':
            c = '\n';
            break;
        case 'r':
            c = '\r';
            break;
        case 't':
            c = '\t';
            break;
        default:
            gdx_log_error("gdx","Illegal escaped character: \\" + c);
        }

        buffer << c;
    }
    return buffer.str();
}

void JsonReader::number(const std::string& name, int value)
{
    set(name, JsonValue::newNodeAsInt(new int(value)));
}

