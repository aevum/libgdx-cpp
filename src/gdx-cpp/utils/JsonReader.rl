
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

using namespace gdx;

%%{
 machine json;
 write data;
}%%

JsonReader::JsonReader()
{
}

JsonValue JsonReader::parse (const std::string& json) {
    return parse(json.c_str(), 0, json.length());
}

JsonValue JsonReader::parse (const gdx::FileHandle& file) {
    try {
        gdx::FileHandle::buffer_ptr buffer;
        int size = file.readBytes(buffer);

        return parse(buffer.get(), 0, size);
    } catch (...) {
        gdx_log_error("gdx","Error parsing file: %s", file.name().c_str());
    }
}

JsonValue JsonReader::parse(const char* data, int offset, int length)
{
    JsonReader reader;
    return reader.doParse(data,offset, length);
}

JsonValue JsonReader::doParse (const char* data, int offset, int length) {
    root = JsonValue();
    current = nullptr;
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
                        
                        null(name);
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
        gdx_log_error("gdx","Error parsing JSON on line %d near: %s", lineNumber, std::string(p, pe - p).c_str());
    } else if (elements.size() != 0) {
        int element_type = elements.front()->getType();

        elements.clear();

        if (element_type == JsonValue::json_json)
            gdx_log_error("gdx","Error parsing JSON, unmatched brace.");
        else
            gdx_log_error("gdx","Error parsing JSON, unmatched bracket.");
    }

    return root;
}
void JsonReader::startObject (const std::string& name) {
    if (current) {
        elements.push_back(set(name, JsonValue::item_map()));        
    } else {
        root = JsonValue::item_map();
        elements.push_back(&root);
    }

    current = elements.back();
}

void JsonReader::startArray (const std::string& name) {
    if (current) {        
        elements.push_back(set(name, JsonValue::array()));
    } else {
        root = JsonValue::array();
        elements.push_back(&root);
    }
    
    current = elements.back();
}

void JsonReader::pop () {
    elements.pop_back();
    current = elements.size() > 0 ? elements.back() : &root;
}

void JsonReader::string (const std::string& name,const std::string& value) {
    set(name, value);
}

void JsonReader::number (const std::string& name, float value) {
    set(name, value);
}

void JsonReader::boolean (const std::string& name, bool value) {
    set(name, value);
}

void JsonReader::number(const std::string& name, int value)
{
    set(name, value);
}

void JsonReader::null(const std::string& name)
{
    set(name, JsonValue());
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
            char result[5] = { 0, 0, 0, 0 ,0 };
            
            int codepoint = strtol(value.substr(i, 4).c_str(), NULL, 16);            
            
            if (codepoint <= 0x7f) {
                result[0] = static_cast<char>(codepoint);
            } else if (codepoint <= 0x7FF) {
                result[1] = static_cast<char>(0x80 | (0x3f & codepoint));
                result[0] = static_cast<char>(0xC0 | (codepoint >> 6));
            } else if (codepoint <= 0xFFFF) {
                result[2] = static_cast<char>(0x80 | (0x3f & codepoint));
                result[1] = (0x80 | static_cast<char>((0x3f & (codepoint >> 6))));
                result[0] = (0xE0 | static_cast<char>(codepoint >> 12));
            } else if (codepoint <= 0x10FFFF) {
                result[3] = static_cast<char>(0x80 | (0x3f & codepoint));
                result[2] = static_cast<char>(0x80 | (0x3f & (codepoint >> 6)));
                result[1] = static_cast<char>(0x80 | (0x3f & (codepoint >> 12)));
                result[0] = static_cast<char>(0xF0 | (codepoint >> 18));
            }
                                    
            buffer << result;
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

JsonValue* JsonReader::set(const std::string& name, const JsonValue& value)
{
    if (current->getType() == gdx::JsonValue::json_list) {
        (*current).as_array().push_back(value);
        return &(*current).as_array().back();
    } else if (current->getType() == gdx::JsonValue::json_json) {
        (*current)[name] = value;
        return &(*current)[name];
    } else {
        (*current) = value;
        return current;
    }
}