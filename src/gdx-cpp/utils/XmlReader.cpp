
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

#include <algorithm>
#include <memory>
#include <unordered_map>
#include <utility>

#include "StringConvertion.hpp"
#include "XmlReader.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/files/FileHandle.hpp"

using namespace gdx;

const char XmlReader::_xml_actions[26] = { 0, 1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 2, 0, 6, 2, 1, 4, 2, 2, 4}; 
const char XmlReader::_xml_key_offsets[36] = {0, 0, 4, 9, 14, 20, 26, 30, 35, 36, 37, 42, 46, 50, 51, 52, 56, 57, 62, 67, 73, 79, 83, 88, 89, 90, 95,99, 103, 104, 108, 109, 110, 111, 112, 115};
const char XmlReader::_xml_trans_keys[116] = {32, 60, 9, 13, 32, 47, 62, 9, 13, 32, 47, 62, 9, 13, 32, 47, 61, 62, 9, 13, 32, 47, 61, 62, 9, 13, 32,61, 9, 13, 32, 34, 39, 9, 13, 34, 34, 32, 47, 62, 9, 13, 32, 62, 9, 13, 32, 62, 9, 13, 39, 39, 32, 60, 9, 13, 60, 32,47, 62, 9, 13, 32, 47, 62, 9, 13, 32, 47, 61, 62, 9, 13, 32, 47, 61, 62, 9, 13, 32, 61, 9, 13, 32, 34, 39, 9, 13, 34,34, 32, 47, 62, 9, 13, 32, 62, 9, 13, 32, 62, 9, 13, 60, 32, 47, 9, 13, 62, 62, 39, 39, 32, 9, 13, 0};
const char XmlReader::_xml_single_lengths[36] =  {0, 2, 3, 3, 4, 4, 2, 3, 1, 1, 3, 2, 2, 1, 1, 2, 1, 3, 3, 4, 4, 2, 3, 1, 1, 3, 2, 2, 1, 2, 1, 1, 1, 1, 1,0};
const char XmlReader::_xml_range_lengths[36] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1,0};
const short XmlReader::_xml_index_offsets[36] = {0, 0, 4, 9, 14, 20, 26, 30, 35, 37, 39, 44, 48, 52, 54, 56, 60, 62, 67, 72, 78, 84, 88, 93, 95, 97,102, 106, 110, 112, 116, 118, 120, 122, 124, 127};
const char XmlReader::_xml_indicies[129] = {0, 2, 0, 1, 2, 1, 1, 2, 3, 5, 6, 7, 5, 4, 9, 10, 1, 11, 9, 8, 13, 1, 14, 1, 13, 12, 15, 16, 15, 1, 16,17, 18, 16, 1, 20, 19, 22, 21, 9, 10, 11, 9, 1, 23, 24, 23, 1, 25, 11, 25, 1, 20, 26, 22, 27, 29, 30, 29, 28, 32, 31,30, 34, 1, 30, 33, 36, 37, 38, 36, 35, 40, 41, 1, 42, 40, 39, 44, 1, 45, 1, 44, 43, 46, 47, 46, 1, 47, 48, 49, 47, 1,51, 50, 53, 52, 40, 41, 42, 40, 1, 54, 55, 54, 1, 56, 42, 56, 1, 57, 1, 57, 34, 57, 1, 1, 58, 59, 58, 51, 60, 53, 61,62, 62, 1, 1, 0};
const char XmlReader::_xml_trans_targs[63] = {1, 0, 2, 3, 3, 4, 11, 34, 5, 4, 11, 34, 5, 6, 7, 6, 7, 8, 13, 9, 10, 9, 10, 12, 34, 12, 14, 14, 16, 15,17, 16, 17, 18, 30, 18, 19, 26, 28, 20, 19, 26, 28, 20, 21, 22, 21, 22, 23, 32, 24, 25, 24, 25, 27, 28, 27, 29, 31, 35,33, 33, 34};
const char XmlReader::_xml_trans_actions[63] = {0, 0, 0, 1, 0, 3, 3, 20, 1, 0, 0, 9, 0, 11, 11, 0, 0, 0, 0, 1, 17, 0, 13, 5, 23, 0, 1, 0, 1, 0, 0, 0,15, 1, 0, 0, 3, 3, 20, 1, 0, 0, 9, 0, 11, 11, 0, 0, 0, 0, 1, 17, 0, 13, 5, 23, 0, 0, 0, 7, 1, 0, 0};

const int XmlReader::xml_start = 1;
const int XmlReader::xml_first_final = 34;
const int XmlReader::xml_error = 0;
const int XmlReader::xml_en_elementBody = 15;
const int XmlReader::xml_en_main = 1;

XmlReader::XmlReader()
{
}

XmlReader::Element::ptr XmlReader::parse (const std::string& xml) {
    return parse(xml.c_str(), 0, xml.length());
}

XmlReader::Element::ptr XmlReader::parse (std::ifstream& reader) {
    reader.seekg (0, std::ios::end);
    int length = reader.tellg();
    reader.seekg (0, std::ios::beg);

    std::vector<char> buffer(length);
    reader.read(&buffer[0], length);

    return parse(&buffer[0], 0, length);
}

XmlReader::Element::ptr XmlReader::parse (FileHandle& file) {
    FileHandle::buffer_ptr buffer;
    int size = file.readBytes(buffer);
    return parse(buffer.get(), 0 , size);
}

XmlReader::Element::ptr XmlReader::parse (const char* data, int offset, int length) {
    int cs, p = offset, pe = length;

    int s = 0;
    std::string attributeName;
    bool hasBody = false;

    // line 3 "Xml.java"
    {
        cs = xml_start;
    }

    // line 7 "Xml.java"
    {
        int _klen = 0;
        int _trans = 0;
        int _acts = 0;
        int _nacts = 0;
        int _keys = 0;
        int _goto_targ = 0;

_goto:
        while (true) {
            switch (_goto_targ) {
            case 0:
                if (p == pe) {
                    _goto_targ = 4;
                    goto _goto;
                }
                if (cs == 0) {
                    _goto_targ = 5;
                    goto _goto;
                }
            case 1:
                do {
                    _keys = _xml_key_offsets[cs];
                    _trans = _xml_index_offsets[cs];
                    _klen = _xml_single_lengths[cs];
                    if (_klen > 0) {
                        int _lower = _keys;
                        int _mid;
                        int _upper = _keys + _klen - 1;
                        while (true) {
                            if (_upper < _lower) break;

                            _mid = _lower + ((_upper - _lower) >> 1);
                            if (data[p] < _xml_trans_keys[_mid])
                                _upper = _mid - 1;
                            else if (data[p] > _xml_trans_keys[_mid])
                                _lower = _mid + 1;
                            else {
                                _trans += (_mid - _keys);
                                goto _match;
                            }
                        }
                        _keys += _klen;
                        _trans += _klen;
                    }

                    _klen = _xml_range_lengths[cs];
                    if (_klen > 0) {
                        int _lower = _keys;
                        int _mid;
                        int _upper = _keys + (_klen << 1) - 2;
                        while (true) {
                            if (_upper < _lower) break;

                            _mid = _lower + (((_upper - _lower) >> 1) & ~1);
                            if (data[p] < _xml_trans_keys[_mid])
                                _upper = _mid - 2;
                            else if (data[p] > _xml_trans_keys[_mid + 1])
                                _lower = _mid + 2;
                            else {
                                _trans += ((_mid - _keys) >> 1);
                                goto _match;
                            }
                        }
                        _trans += _klen;
                    }
                } while (false);
_match:
                
                _trans = _xml_indicies[_trans];
                cs = _xml_trans_targs[_trans];

                if (_xml_trans_actions[_trans] != 0) {
                    _acts = _xml_trans_actions[_trans];
                    _nacts = (int)_xml_actions[_acts++];
                    while (_nacts-- > 0) {
                        switch (_xml_actions[_acts++]) {
                        case 0:
                            // line 80 "Xml.rl"
                        {
                            s = p;
                        }
                        break;
                        case 1:
                            // line 81 "Xml.rl"
                        {
                            char c = data[s];
                            if (c == '?' || c == '!') {
                                if (data[s + 1] == '[' && //
                                        data[s + 2] == 'C' && //
                                        data[s + 3] == 'D' && //
                                        data[s + 4] == 'A' && //
                                        data[s + 5] == 'T' && //
                                        data[s + 6] == 'A' && //
                                        data[s + 7] == '[') {
                                    s += 8;
                                    p = s + 2;
                                    while (data[p - 2] != ']' || data[p - 1] != ']' || data[p] != '>')
                                        p++;
                                    text(std::string(&data[s], p - s - 2));
                                } else
                                    while (data[p] != '>')
                                        p++;
                                {
                                    cs = 15;
                                    _goto_targ = 2;
                                    goto _goto;
                                }
                            }
                            hasBody = true;
                            open(std::string(&data[s], p - s));
                        }
                        break;
                        case 2:
                            // line 105 "Xml.rl"
                        {
                            hasBody = false;
                            close();
                            {
                                cs = 15;
                                _goto_targ = 2;
                                goto _goto;
                            }
                        }
                        break;
                        case 3:
                            // line 110 "Xml.rl"
                        {
                            close();
                            {
                                cs = 15;
                                _goto_targ = 2;
                                goto _goto;
                            }
                        }
                        break;
                        case 4:
                            // line 114 "Xml.rl"
                        {
                            if (hasBody) {
                                cs = 15;
                                _goto_targ = 2;
                                goto _goto;
                            }
                        }
                        break;
                        case 5:
                            // line 117 "Xml.rl"
                        {
                            attributeName.assign(&data[s], p - s);
                        }
                        break;
                        case 6:
                            // line 120 "Xml.rl"
                        {
                            attribute(attributeName, std::string(&data[s], p - s));
                        }
                        break;
                        case 7:
                            // line 123 "Xml.rl"
                        {
                            int end = p;
                            while (end != s) {
                                switch (data[end - 1]) {
                                case ' ':
                                case '\t':
                                case '\n':
                                case '\r':
                                    end--;
                                    continue;
                                }
                                break;
                            }
                            int current = s;
                            bool entityFound = false;
                            while (current != end) {
                                if (data[current++] != '&') continue;
                                int entityStart = current;
                                while (current != end) {
                                    if (data[current++] != ';') continue;
                                    textBuffer  << std::string(&data[s], entityStart - s - 1);
                                    std::string name(data, entityStart, current - entityStart - 1);
                                    std::string value = entity(name);
                                    textBuffer << (value.empty() ? value : name);
                                    s = current;
                                    entityFound = true;
                                    break;
                                }
                            }
                            if (entityFound) {
                                if (s < end)
                                    textBuffer << std::string(&data[s], end - s);
                                text(textBuffer.str());
                                textBuffer.clear();
                            } else
                                text(std::string(&data[s], end - s));
                        }
                        break;
                        // line 190 "Xml.java"
                        }
                    }
                }

            case 2:
                if (cs == 0) {
                    _goto_targ = 5;
                    goto _goto;
                }
                if (++p != pe) {
                    _goto_targ = 1;
                    goto _goto;
                }
            case 4:
            case 5:
                break;
            }
            break;
        }
    }

    // line 170 "Xml.rl"

    if (p < pe) {
        int lineNumber = 1;
        for (int i = 0; i < p; i++)
            if (data[i] == '\n') lineNumber++;
        gdx_log_error("gdx","Error parsing XML on line %d near: %s", lineNumber, std::string(&data[p], std::min(32, pe - p)).c_str());
    } else if (elements.size() != 0) {
        Element::ptr element = elements.back();
        elements.clear();
        gdx_log_error("gdx","Error parsing XML, unclosed element: %s", element->getName().c_str());
    }

    Element::ptr root = this->root;
    this->root.reset();
    
    return root;
}

void XmlReader::open (const std::string& name) {
    Element::ptr child = Element::ptr(new Element(name));

    if (current)
        current->addChild(child);
    
    elements.push_back(child);
    current = child;
}

void XmlReader::attribute (std::string name, std::string value) {
    current->setAttribute(name, value);
}

std::string XmlReader::entity (const std::string& name) {
    if (name == "lt") return "<";
    if (name == "gt") return ">";
    if (name == "amp") return "&";
    if (name == "apos") return "'";
    if (name == "quot") return "\"";

    return "";
}

void XmlReader::text (std::string text) {
    std::string existing = current->getText();
    current->setText(!existing.empty() ? existing + text : text);
}

void XmlReader::close () {
    root = elements.back();
    elements.pop_back();
    current = elements.size() > 0 ? elements.back() : nullptr;
}

XmlReader::Element::Element(const std::string& name) {
    this->name = name;
}
std::string XmlReader::Element::getName() {
    return name;
}
std::string XmlReader::Element::getAttribute(const std::string& name) {
    if (attributes.empty() || !attributes.count(name))
        gdx_log_error("gdx","Element %s doesn't have attribute: %s", this->name.c_str(), name.c_str());

    return attributes[name];
}

std::string XmlReader::Element::getAttribute(const std::string& name, const std::string& defaultValue) {
    if (attributes.empty())
        return defaultValue;

    if (attributes.count(name)) {
        return attributes[name];
    }

    return defaultValue;
}

void XmlReader::Element::setAttribute(const std::string& name, const std::string& value) {
    attributes[name] = value;
}

int XmlReader::Element::getChildCount() {
    return children.size();;
}

XmlReader::Element::ptr const XmlReader::Element::getChild(int i) {
    if (children.size() == 0) gdx_log_error("gdx","Element has no children: %s", name.c_str());
    return children[i];
}

void XmlReader::Element::addChild(const XmlReader::Element::ptr& element) {
    children.push_back(element);
}

const std::string& XmlReader::Element::getText() {
    return text;
}

void XmlReader::Element::setText(const std::string& text) {
    this->text = text;
}

std::string XmlReader::Element::toString() const {
    return toString("");
}
std::string XmlReader::Element::toString(const std::string& indent) const {
    std::stringstream buffer;

    buffer << indent << '<' << name ;

    if (attributes.size()) {
        auto it = attributes.begin();
        auto end = attributes.end();

        for (; it != end; ++it) {
            buffer << ' ' << it->first << "=\"" << it->second << '\"';
        }
    }

    if (children.empty() && (text.empty() || text.size() == 0))
        buffer << "/>";
    else {
        buffer << ">\n";
        std::string childIndent = indent + '\t';
        if (!text.empty() && text.length() > 0) {
            buffer << childIndent << text << '\n';
        }
        if (children.size()) {
            auto it = children.begin();
            auto end = children.end();

            for (; it != end; ++it) {
                buffer << (*it)->toString(childIndent) << '\n';
            }
        }

        buffer<< indent << "</" << name << '>';
    }
    return buffer.str();
}

XmlReader::Element::ptr const XmlReader::Element::getChildByName(const std::string& name) {
    if (children.empty())
        return nullptr;

    for (auto & elem : children) {
        Element::ptr& element = elem;
        if (element->name == name)
            return element;
    }
    
    return nullptr;
}

XmlReader::Element::ptr const XmlReader::Element::getChildByNameRecursive(const std::string& name) {
    if (children.empty())
        return nullptr;

    for (auto & elem : children) {
        const Element::ptr& element = elem;

        if (element->name == name)
            return element;

        const Element::ptr& found = element->getChildByNameRecursive(name);
        if (found) return found;
    }
    
    return nullptr;
}

std::vector< XmlReader::Element::ptr > XmlReader::Element::getChildrenByName(const std::string& name) {
    ElementVector chld;

    for (auto & elem : children) {
        Element::ptr& child = elem;
        if (child->name ==  name) chld.push_back(child);
    }

    return chld;
}

float XmlReader::Element::getFloatAttribute(const std::string& name) {
    return from_string<float>(getAttribute(name));
}

float XmlReader::Element::getFloatAttribute(const std::string& name, float defaultValue) {
    std::string value = getAttribute(name, "");

    if (value.empty())
        return defaultValue;

    return from_string<float>(value);
}

int XmlReader::Element::getIntAttribute(const std::string& name) {
    return from_string<int>(getAttribute(name));
}

bool XmlReader::Element::getBooleanAttribute(const std::string& name) {
    return from_string<bool>(getAttribute(name));
}

int XmlReader::Element::getIntAttribute(const std::string& name, int defaultValue) {
    if (!hasAttribute(name))
        return defaultValue;
    return from_string<int>(getAttribute(name));
}

bool XmlReader::Element::getBooleanAttribute(const std::string& name, bool defaultValue) {
    if (!hasAttribute(name))
        return defaultValue;

    return from_string< bool >(name);
}
std::string XmlReader::Element::get(const std::string& name) {
    if (!hasAttribute(name))
        gdx_log_error("gdx","Element %s doesn't have attribute or child: %s", name.c_str());
    return getAttribute(name, "");
}

std::string XmlReader::Element::get(const std::string& name, const std::string& defaultValue) {
    if (attributes.size() && attributes.count(name)) {
        return attributes[name];
    }
    
    Element::ptr child = getChildByName(name);
    if (!child)
        return defaultValue;
    const std::string& value = child->getText();
    if (value.empty())
        return defaultValue;

    return value;
}

int XmlReader::Element::getInt(const std::string& name) {
    std::string value = get(name, "");
    
    if (value.empty())
        gdx_log_error("gdx","Element %s doesn't have attribute or child: %s", this->name.c_str(), name.c_str());
    
    return from_string< int>(value);
}

int XmlReader::Element::getInt(const std::string& name, int defaultValue) {
    std::string value = get(name, "");
    
    if (value.empty())
        return defaultValue;
    
    return from_string< int>(value);
}

float XmlReader::Element::getFloat(const std::string& name) {
    std::string value = get(name, "");
    if (value.empty())
        gdx_log_error("gdx","Element %s doesn't have attribute or child: %s", this->name.c_str(), name.c_str());

    return from_string< float >(value);
}

float XmlReader::Element::getFloat(const std::string& name, float defaultValue) {
    std::string value = get(name, "");

    if (value.empty())
        return defaultValue;
    
    return from_string< float >(value);
}

bool XmlReader::Element::getBolean(const std::string& name) {
    std::string value = get(name, "");
    if (value.empty())
        gdx_log_error("gdx","Element %s doesn't have attribute or child: %s", this->name.c_str(), name.c_str());
    
    return from_string< bool >(value);
}
bool XmlReader::Element::getBoolean(const std::string& name, bool defaultValue) {
    std::string value = get(name, "");
    if (value.empty())
        return defaultValue;
    return from_string< bool >(value);
}

bool XmlReader::Element::hasAttribute(const std::string& attributeName)
{
    return attributes.count(attributeName);
}

int XmlReader::Element::getAttributeCount() const
{
    return attributes.size();
}

XmlReader::Element::AttributesMap::const_iterator XmlReader::Element::getAttributesEnd()
{
    return attributes.end();
}

XmlReader::Element::AttributesMap::const_iterator XmlReader::Element::getAttributesBegin()
{
    return attributes.begin();
}


