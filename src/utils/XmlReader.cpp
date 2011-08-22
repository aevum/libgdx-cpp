
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

#include "XmlReader.hpp"

using namespace gdx_cpp::utils;

Element& XmlReader::parse (const std::string& xml) {
    char[] data = xml.toCharArray();
    return parse(data, 0, data.length);
}

Element& XmlReader::parse (const Reader& reader) throws IOException {
    char[] data = new char[1024];
    int offset = 0;
    while (true) {
        int length = reader.read(data, offset, data.length - offset);
        if (length == -1) break;
        if (length == 0) {
            char[] newData = new char[data.length * 2];
            System.arraycopy(data, 0, newData, 0, data.length);
            data = newData;
        } else
            offset += length;
    }
    return parse(data, 0, offset);
}

Element& XmlReader::parse (const InputStream& input) throws IOException {
    return parse(new InputStreamReader(input, "ISO-8859-1"));
}

Element& XmlReader::parse (const gdx_cpp::files::FileHandle& file) throws IOException {
    return parse(file.read());
}

Element& XmlReader::parse (int offset,int length) {
    int cs, p = offset, pe = length;

    int s = 0;
    String attributeName = null;
    boolean hasBody = false;

    // line 3 "Xml.java"
    {
        cs = xml_start;
    }

    // line 7 "Xml.java"
    {
        int _klen;
        int _trans = 0;
        int _acts;
        int _nacts;
        int _keys;
        int _goto_targ = 0;

_goto:
        while (true) {
            switch (_goto_targ) {
            case 0:
                if (p == pe) {
                    _goto_targ = 4;
                    continue _goto;
                }
                if (cs == 0) {
                    _goto_targ = 5;
                    continue _goto;
                }
            case 1:
_match:
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
                                break _match;
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
                                break _match;
                            }
                        }
                        _trans += _klen;
                    }
                } while (false);

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
                                    text(new String(data, s, p - s - 2));
                                } else
                                    while (data[p] != '>')
                                        p++;
                                {
                                    cs = 15;
                                    _goto_targ = 2;
                                    if (true) continue _goto;
                                }
                            }
                            hasBody = true;
                            open(new String(data, s, p - s));
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
                                if (true) continue _goto;
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
                                if (true) continue _goto;
                            }
                        }
                        break;
                        case 4:
                            // line 114 "Xml.rl"
                        {
                            if (hasBody) {
                                cs = 15;
                                _goto_targ = 2;
                                if (true) continue _goto;
                            }
                        }
                        break;
                        case 5:
                            // line 117 "Xml.rl"
                        {
                            attributeName = new String(data, s, p - s);
                        }
                        break;
                        case 6:
                            // line 120 "Xml.rl"
                        {
                            attribute(attributeName, new String(data, s, p - s));
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
                            boolean entityFound = false;
                            while (current != end) {
                                if (data[current++] != '&') continue;
                                int entityStart = current;
                                while (current != end) {
                                    if (data[current++] != ';') continue;
                                    textBuffer.append(data, s, entityStart - s - 1);
                                    String name = new String(data, entityStart, current - entityStart - 1);
                                    String value = entity(name);
                                    textBuffer.append(value != null ? value : name);
                                    s = current;
                                    entityFound = true;
                                    break;
                                }
                            }
                            if (entityFound) {
                                if (s < end) textBuffer.append(data, s, end - s);
                                text(textBuffer.toString());
                                textBuffer.setLength(0);
                            } else
                                text(new String(data, s, end - s));
                        }
                        break;
                        // line 190 "Xml.java"
                        }
                    }
                }

            case 2:
                if (cs == 0) {
                    _goto_targ = 5;
                    continue _goto;
                }
                if (++p != pe) {
                    _goto_targ = 1;
                    continue _goto;
                }
            case 4:
            case 5:
            }
            break;
        }
    }

    // line 170 "Xml.rl"

    if (p < pe) {
        int lineNumber = 1;
        for (int i = 0; i < p; i++)
            if (data[i] == '\n') lineNumber++;
        throw new IllegalArgumentException("Error parsing XML on line " + lineNumber + " near: "
                                           + new String(data, p, Math.min(32, pe - p)));
    } else if (elements.size != 0) {
        Element element = elements.peek();
        elements.clear();
        throw new IllegalArgumentException("Error parsing XML, unclosed element: " + element.getName());
    }
    Element root = this.root;
    this.root = null;
    return root;
}

char* XmlReader::init__xml_actions_0 () {
    return new byte[] {0, 1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 2, 0, 6, 2, 1, 4, 2, 2, 4};
}

char* XmlReader::init__xml_key_offsets_0 () {
    return new byte[] {0, 0, 4, 9, 14, 20, 26, 30, 35, 36, 37, 42, 46, 50, 51, 52, 56, 57, 62, 67, 73, 79, 83, 88, 89, 90, 95,
                       99, 103, 104, 108, 109, 110, 111, 112, 115
                      };
}

char* XmlReader::init__xml_trans_keys_0 () {
    return new char[] {32, 60, 9, 13, 32, 47, 62, 9, 13, 32, 47, 62, 9, 13, 32, 47, 61, 62, 9, 13, 32, 47, 61, 62, 9, 13, 32,
                       61, 9, 13, 32, 34, 39, 9, 13, 34, 34, 32, 47, 62, 9, 13, 32, 62, 9, 13, 32, 62, 9, 13, 39, 39, 32, 60, 9, 13, 60, 32,
                       47, 62, 9, 13, 32, 47, 62, 9, 13, 32, 47, 61, 62, 9, 13, 32, 47, 61, 62, 9, 13, 32, 61, 9, 13, 32, 34, 39, 9, 13, 34,
                       34, 32, 47, 62, 9, 13, 32, 62, 9, 13, 32, 62, 9, 13, 60, 32, 47, 9, 13, 62, 62, 39, 39, 32, 9, 13, 0
                      };
}

char* XmlReader::init__xml_single_lengths_0 () {
    return new byte[] {0, 2, 3, 3, 4, 4, 2, 3, 1, 1, 3, 2, 2, 1, 1, 2, 1, 3, 3, 4, 4, 2, 3, 1, 1, 3, 2, 2, 1, 2, 1, 1, 1, 1, 1,
                       0
                      };
}

char* XmlReader::init__xml_range_lengths_0 () {
    return new byte[] {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1,
                       0
                      };
}

short* XmlReader::init__xml_index_offsets_0 () {
    return new short[] {0, 0, 4, 9, 14, 20, 26, 30, 35, 37, 39, 44, 48, 52, 54, 56, 60, 62, 67, 72, 78, 84, 88, 93, 95, 97,
                        102, 106, 110, 112, 116, 118, 120, 122, 124, 127
                       };
}

char* XmlReader::init__xml_indicies_0 () {
    return new byte[] {0, 2, 0, 1, 2, 1, 1, 2, 3, 5, 6, 7, 5, 4, 9, 10, 1, 11, 9, 8, 13, 1, 14, 1, 13, 12, 15, 16, 15, 1, 16,
                       17, 18, 16, 1, 20, 19, 22, 21, 9, 10, 11, 9, 1, 23, 24, 23, 1, 25, 11, 25, 1, 20, 26, 22, 27, 29, 30, 29, 28, 32, 31,
                       30, 34, 1, 30, 33, 36, 37, 38, 36, 35, 40, 41, 1, 42, 40, 39, 44, 1, 45, 1, 44, 43, 46, 47, 46, 1, 47, 48, 49, 47, 1,
                       51, 50, 53, 52, 40, 41, 42, 40, 1, 54, 55, 54, 1, 56, 42, 56, 1, 57, 1, 57, 34, 57, 1, 1, 58, 59, 58, 51, 60, 53, 61,
                       62, 62, 1, 1, 0
                      };
}

char* XmlReader::init__xml_trans_targs_0 () {
    return new byte[] {1, 0, 2, 3, 3, 4, 11, 34, 5, 4, 11, 34, 5, 6, 7, 6, 7, 8, 13, 9, 10, 9, 10, 12, 34, 12, 14, 14, 16, 15,
                       17, 16, 17, 18, 30, 18, 19, 26, 28, 20, 19, 26, 28, 20, 21, 22, 21, 22, 23, 32, 24, 25, 24, 25, 27, 28, 27, 29, 31, 35,
                       33, 33, 34
                      };
}

char* XmlReader::init__xml_trans_actions_0 () {
    return new byte[] {0, 0, 0, 1, 0, 3, 3, 20, 1, 0, 0, 9, 0, 11, 11, 0, 0, 0, 0, 1, 17, 0, 13, 5, 23, 0, 1, 0, 1, 0, 0, 0,
                       15, 1, 0, 0, 3, 3, 20, 1, 0, 0, 9, 0, 11, 11, 0, 0, 0, 0, 1, 17, 0, 13, 5, 23, 0, 0, 0, 7, 1, 0, 0
                      };
}

void XmlReader::open (const std::string& name) {
    Element child = new Element(name);
    Element parent = current;
    if (parent != null) parent.addChild(child);
    elements.add(child);
    current = child;
}

void XmlReader::attribute (const std::string& name,const std::string& value) {
    current.setAttribute(name, value);
}

std::string& XmlReader::entity (const std::string& name) {
    if (name.equals("lt")) return "<";
    if (name.equals("gt")) return ">";
    if (name.equals("amp")) return "&";
    if (name.equals("apos")) return "'";
    if (name.equals("quot")) return "\"";
    return null;
}

void XmlReader::text (const std::string& text) {
    String existing = current.getText();
    current.setText(existing != null ? existing + text : text);
}

void XmlReader::close () {
    root = elements.pop();
    current = elements.size > 0 ? elements.peek() : null;
}

std::string& XmlReader::getName () {
    return name;
}

std::string& XmlReader::getAttribute (const std::string& name) {
    if (attributes == null) throw new GdxRuntimeException("Element " + name + " doesn't have attribute: " + name);
    String value = attributes.get(name);
    if (value == null) throw new GdxRuntimeException("Element " + name + " doesn't have attribute: " + name);
    return value;
}

std::string& XmlReader::getAttribute (const std::string& name,const std::string& defaultValue) {
    if (attributes == null) return defaultValue;
    String value = attributes.get(name);
    if (value == null) return defaultValue;
    return value;
}

void XmlReader::setAttribute (const std::string& name,const std::string& value) {
    if (attributes == null) attributes = new ObjectMap(8);
    attributes.put(name, value);
}

int XmlReader::getChildCount () {
    if (children == null) return 0;
    return children.size;
}

Element& XmlReader::getChild (int i) {
    if (children == null) throw new GdxRuntimeException("Element has no children: " + name);
    return children.get(i);
}

void XmlReader::addChild (const Element& element) {
    if (children == null) children = new Array(8);
    children.add(element);
}

std::string& XmlReader::getText () {
    return text;
}

void XmlReader::setText (const std::string& text) {
    this.text = text;
}

std::string& XmlReader::toString () {
    return toString("");
}

std::string& XmlReader::toString (const std::string& indent) {
    StringBuilder buffer = new StringBuilder(128);
    buffer.append(indent);
    buffer.append('<');
    buffer.append(name);
    if (attributes != null) {
for (Entry<String, String> entry : attributes.entries()) {
            buffer.append(' ');
            buffer.append(entry.key);
            buffer.append("=\"");
            buffer.append(entry.value);
            buffer.append('\"');
        }
    }
    if (children == null && (text == null || text.length() == 0))
        buffer.append("/>");
    else {
        buffer.append(">\n");
        String childIndent = indent + '\t';
        if (text != null && text.length() > 0) {
            buffer.append(childIndent);
            buffer.append(text);
            buffer.append('\n');
        }
        if (children != null) {
for (Element child : children) {
                buffer.append(child.toString(childIndent));
                buffer.append('\n');
            }
        }
        buffer.append(indent);
        buffer.append("</");
        buffer.append(name);
        buffer.append('>');
    }
    return buffer.toString();
}

Element& XmlReader::getChildByName (const std::string& name) {
    if (children == null) return null;
    for (int i = 0; i < children.size; i++) {
        Element element = children.get(i);
        if (element.name.equals(name)) return element;
    }
    return null;
}

Element& XmlReader::getChildByNameRecursive (const std::string& name) {
    if (children == null) return null;
    for (int i = 0; i < children.size; i++) {
        Element element = children.get(i);
        if (element.name.equals(name)) return element;
        Element found = element.getChildByNameRecursive(name);
        if (found != null) return found;
    }
    return null;
}

Array<Element>& XmlReader::getChildrenByName (const std::string& name) {
    Array<Element> children = new Array<Element>();
    if (this.children == null) return children;
    for (int i = 0; i < this.children.size; i++) {
        Element child = this.children.get(i);
        if (child.name.equals(name)) children.add(child);
    }
    return children;
}

float XmlReader::getFloatAttribute (const std::string& name) {
    return Float.parseFloat(getAttribute(name));
}

float XmlReader::getFloatAttribute (const std::string& name,float defaultValue) {
    String value = getAttribute(name, null);
    if (value == null) return defaultValue;
    return Float.parseFloat(value);
}

int XmlReader::getIntAttribute (const std::string& name) {
    return Integer.parseInt(getAttribute(name));
}

int XmlReader::getIntAttribute (const std::string& name,int defaultValue) {
    String value = getAttribute(name, null);
    if (value == null) return defaultValue;
    return Integer.parseInt(value);
}

bool XmlReader::getBooleanAttribute (const std::string& name) {
    return Boolean.parseBoolean(getAttribute(name));
}

bool XmlReader::getBooleanAttribute (const std::string& name,bool defaultValue) {
    String value = getAttribute(name, null);
    if (value == null) return defaultValue;
    return Boolean.parseBoolean(value);
}

std::string& XmlReader::get (const std::string& name) {
    String value = get(name, null);
    if (value == null) throw new GdxRuntimeException("Element " + this.name + " doesn't have attribute or child: " + name);
    return value;
}

std::string& XmlReader::get (const std::string& name,const std::string& defaultValue) {
    if (attributes != null) {
        String value = attributes.get(name);
        if (value != null) return value;
    }
    Element child = getChildByName(name);
    if (child == null) return defaultValue;
    String value = child.getText();
    if (value == null) return defaultValue;
    return value;
}

int XmlReader::getInt (const std::string& name) {
    String value = get(name, null);
    if (value == null) throw new GdxRuntimeException("Element " + this.name + " doesn't have attribute or child: " + name);
    return Integer.parseInt(value);
}

int XmlReader::getInt (const std::string& name,int defaultValue) {
    String value = get(name, null);
    if (value == null) return defaultValue;
    return Integer.parseInt(value);
}

float XmlReader::getFloat (const std::string& name) {
    String value = get(name, null);
    if (value == null) throw new GdxRuntimeException("Element " + this.name + " doesn't have attribute or child: " + name);
    return Float.parseFloat(value);
}

float XmlReader::getFloat (const std::string& name,float defaultValue) {
    String value = get(name, null);
    if (value == null) return defaultValue;
    return Float.parseFloat(value);
}

bool XmlReader::getBolean (const std::string& name) {
    String value = get(name, null);
    if (value == null) throw new GdxRuntimeException("Element " + this.name + " doesn't have attribute or child: " + name);
    return Boolean.parseBoolean(value);
}

bool XmlReader::getBoolean (const std::string& name,bool defaultValue) {
    String value = get(name, null);
    if (value == null) return defaultValue;
    return Boolean.parseBoolean(value);
}

