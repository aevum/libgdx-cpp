
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

#include "JsonWriter.hpp"

using namespace gdx_cpp::utils;

JsonWriter& JsonWriter::object () throws IOException {
    if (current != null) {
        if (!current.array) throw new RuntimeException("Current item must be an array.");
        if (!current.needsComma)
            current.needsComma = true;
        else
            writer.write(",");
    }
    stack.push(current = new JsonObject(false));
    return this;
}

JsonWriter& JsonWriter::array () throws IOException {
    if (current != null) {
        if (!current.array) throw new RuntimeException("Current item must be an array.");
        if (!current.needsComma)
            current.needsComma = true;
        else
            writer.write(",");
    }
    stack.push(current = new JsonObject(true));
    return this;
}

JsonWriter& JsonWriter::add (const Object& value) throws IOException {
    if (!current.array) throw new RuntimeException("Current item must be an array.");
    if (!current.needsComma)
        current.needsComma = true;
    else
        writer.write(",");
    if (value == null || value instanceof Number || value instanceof Boolean)
        writer.write(String.valueOf(value));
    else {
        writer.write("\"");
        writer.write(value.toString());
        writer.write("\"");
    }
    return this;
}

JsonWriter& JsonWriter::object (const std::string& name) throws IOException {
    if (current == null || current.array) throw new RuntimeException("Current item must be an object.");
    if (!current.needsComma)
        current.needsComma = true;
    else
        writer.write(",");
    writer.write("\"");
    writer.write(name);
    writer.write("\":");
    stack.push(current = new JsonObject(false));
    return this;
}

JsonWriter& JsonWriter::array (const std::string& name) throws IOException {
    if (current == null || current.array) throw new RuntimeException("Current item must be an object.");
    if (!current.needsComma)
        current.needsComma = true;
    else
        writer.write(",");
    writer.write("\"");
    writer.write(name);
    writer.write("\":");
    stack.push(current = new JsonObject(true));
    return this;
}

JsonWriter& JsonWriter::set (const std::string& name,const Object& value) throws IOException {
    if (current == null || current.array) throw new RuntimeException("Current item must be an object.");
    if (!current.needsComma)
        current.needsComma = true;
    else
        writer.write(",");
    writer.write("\"");
    writer.write(name);
    if (value == null || value instanceof Number || value instanceof Boolean) {
        writer.write("\":");
        writer.write(String.valueOf(value));
    } else {
        writer.write("\":\"");
        writer.write(value.toString());
        writer.write("\"");
    }
    return this;
}

JsonWriter& JsonWriter::pop () throws IOException {
    stack.pop().close();
    current = stack.peek();
    return this;
}

void JsonWriter::write (int off,int len) throws IOException {
    writer.write(cbuf, off, len);
}

void JsonWriter::flush () throws IOException {
    writer.flush();
}

void JsonWriter::close () throws IOException {
    while (!stack.isEmpty())
        pop();
    writer.close();
}

