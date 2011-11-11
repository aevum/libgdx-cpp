
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

void JsonWriter::setOutputType (const OutputType& outputType) {
    this.outputType = outputType;
}

JsonWriter& JsonWriter::name (const std::string& name) throws IOException {
    if (current == null || current.array) throw new IllegalStateException("Current item must be an object.");
    if (!current.needsComma)
        current.needsComma = true;
    else
        writer.write(',');
    writer.write(outputType.quoteName(name));
    writer.write(':');
    named = true;
    return this;
}

JsonWriter& JsonWriter::object () throws IOException {
    if (current != null) {
        if (current.array) {
            if (!current.needsComma)
                current.needsComma = true;
            else
                writer.write(',');
        } else {
            if (!named && !current.array) throw new IllegalStateException("Name must be set.");
            named = false;
        }
    }
    stack.add(current = new JsonObject(false));
    return this;
}

JsonWriter& JsonWriter::array () throws IOException {
    if (current != null) {
        if (current.array) {
            if (!current.needsComma)
                current.needsComma = true;
            else
                writer.write(',');
        } else {
            if (!named && !current.array) throw new IllegalStateException("Name must be set.");
            named = false;
        }
    }
    stack.add(current = new JsonObject(true));
    return this;
}

JsonWriter& JsonWriter::value (const Object& value) throws IOException {
    if (current != null) {
        if (current.array) {
            if (!current.needsComma)
                current.needsComma = true;
            else
                writer.write(',');
        } else {
            if (!named) throw new IllegalStateException("Name must be set.");
            named = false;
        }
    }
    if (value == null || value instanceof Number || value instanceof Boolean) {
        writer.write(String.valueOf(value));
    } else {
        writer.write(outputType.quoteValue(value.toString()));
    }
    return this;
}

JsonWriter& JsonWriter::object (const std::string& name) throws IOException {
    return name(name).object();
}

JsonWriter& JsonWriter::array (const std::string& name) throws IOException {
    return name(name).array();
}

JsonWriter& JsonWriter::set (const std::string& name,const Object& value) throws IOException {
    return name(name).value(value);
}

JsonWriter& JsonWriter::pop () throws IOException {
    if (named) throw new IllegalStateException("Expected an object, array, or value since a name was set.");
    stack.pop().close();
    current = stack.size == 0 ? null : stack.peek();
    return this;
}

void JsonWriter::write (int off,int len) throws IOException {
    writer.write(cbuf, off, len);
}

void JsonWriter::flush () throws IOException {
    writer.flush();
}

void JsonWriter::close () throws IOException {
    while (stack.size > 0)
        pop();
    writer.close();
}

std::string& JsonWriter::quoteValue (const std::string& value) {
    value = value.replace("\\", "\\\\");
    if (this == OutputType.minimal && !value.equals("true") && !value.equals("false") && !value.equals("null")
            && minimalPattern.matcher(value).matches()) return value;
    return '"' + value + '"';
}

std::string& JsonWriter::quoteName (const std::string& value) {
    value = value.replace("\\", "\\\\");
    switch (this) {
    case minimal:
        if (minimalPattern.matcher(value).matches()) return value;
        return '"' + value + '"';
    case javascript:
        if (javascriptPattern.matcher(value).matches()) return value;
        return '"' + value + '"';
    default:
        return '"' + value + '"';
    }
}

JsonWriter::JsonWriter (const Writer& writer) {
    this.writer = writer;
}

