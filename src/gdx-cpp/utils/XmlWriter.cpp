
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

#include "XmlWriter.hpp"

using namespace gdx_cpp::utils;

void XmlWriter::indent () throws IOException {
    int count = indent;
    if (currentElement != null) count++;
    for (int i = 0; i < count; i++)
        writer.write('\t');
}

XmlWriter& XmlWriter::element (const std::string& name) throws IOException {
    if (startElementContent()) writer.write('\n');
    indent();
    writer.write('<');
    writer.write(name);
    currentElement = name;
    return this;
}

XmlWriter& XmlWriter::element (const std::string& name,const Object& text) throws IOException {
    return element(name).text(text).pop();
}

bool XmlWriter::startElementContent () throws IOException {
    if (currentElement == null) return false;
    indent++;
    stack.push(currentElement);
    currentElement = null;
    writer.write(">");
    return true;
}

XmlWriter& XmlWriter::attribute (const std::string& name,const Object& value) throws IOException {
    if (currentElement == null) throw new IllegalStateException();
    writer.write(' ');
    writer.write(name);
    writer.write("=\"");
    writer.write(value == null ? "null" : value.toString());
    writer.write('"');
    return this;
}

XmlWriter& XmlWriter::text (const Object& text) throws IOException {
    startElementContent();
    String string = text == null ? "null" : text.toString();
    indentNextClose = string.length() > 64;
    if (indentNextClose) {
        writer.write('\n');
        indent();
    }
    writer.write(string);
    if (indentNextClose) writer.write('\n');
    return this;
}

XmlWriter& XmlWriter::pop () throws IOException {
    if (currentElement != null) {
        writer.write("/>\n");
        currentElement = null;
    } else {
        indent = Math.max(indent - 1, 0);
        if (indentNextClose) indent();
        writer.write("</");
        writer.write(stack.pop());
        writer.write(">\n");
    }
    indentNextClose = true;
    return this;
}

void XmlWriter::close () throws IOException {
    while (!stack.isEmpty())
        pop();
    writer.close();
}

void XmlWriter::write (int off,int len) throws IOException {
    startElementContent();
    writer.write(cbuf, off, len);
}

void XmlWriter::flush () throws IOException {
    writer.flush();
}

