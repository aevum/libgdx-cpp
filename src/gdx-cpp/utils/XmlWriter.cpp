
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

#include <gdx-cpp/Gdx.hpp>
#include <stddef.h>
#include <algorithm>

#include "XmlReader.hpp"
#include "XmlWriter.hpp"

using namespace gdx;

XmlWriter::XmlWriter(std::ofstream& _writer)
 : writer(_writer)
{
}

void XmlWriter::_indent () {
    int count = indent;
    if (currentElement.empty()) count++;
    for (int i = 0; i < count; i++)
        writer << '\t';
}

XmlWriter& XmlWriter::element (const std::string& name) {
    if (startElementContent())
        writer << '\n';
    
    _indent();
    writer << '<';
    writer << name;
    currentElement = name;
    return *this;
}

XmlWriter& XmlWriter::element (const std::string& name ,const XmlReader::Element* text) {
    return element(name).text(text).pop();
}

bool XmlWriter::startElementContent () {
    if (currentElement.empty()) return false;
    indent++;
    stack.push_front(currentElement);
    currentElement.clear();;
    writer << ">";
    return true;
}

XmlWriter& XmlWriter::attribute (const std::string& name, const XmlReader::Element* value) {
    if (currentElement.empty()) gdx_log_error("gdx","Empty element");
    writer << (' ');
    writer << (name);
    writer << ("=\"");
    writer << (value == nullptr ? "null" : value->toString());
    writer << ('"');
    return *this;
}

XmlWriter& XmlWriter::text (const XmlReader::Element* text) {
    startElementContent();
    std::string string = (text == nullptr ? "null" : text->toString());
    indentNextClose = string.length() > 64;
    if (indentNextClose) {
        writer << ('\n');
        _indent();
    }
    writer << (string);
    if (indentNextClose) writer << ('\n');
    return *this;
}

XmlWriter& XmlWriter::pop () {
    if (!currentElement.empty()) {
        writer << ("/>\n");
        currentElement.empty();
    } else {
        indent = std::max(indent - 1, 0);
        if (indentNextClose) _indent();
        writer << ("</");
        writer << (stack.front());
        stack.pop_front();
        writer << (">\n");
    }
    indentNextClose = true;
    return *this;
}

void XmlWriter::close () {
    while (!stack.empty())
        pop();
    writer.close();
}

void XmlWriter::write (const char* cbuf, int off,int len){
    startElementContent();
    writer.write(&cbuf[off], len);
}

void XmlWriter::flush () {
    writer.flush();
}

