
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

#include "VertexAttributes.hpp"

using namespace gdx_cpp::graphics;

int VertexAttributes::calculateOffsets () {
    int count = 0;
    for (int i = 0; i < attributes.length; i++) {
        VertexAttribute attribute = attributes[i];
        attribute.offset = count;
        if (attribute.usage == VertexAttributes.Usage.ColorPacked)
            count += 4;
        else
            count += 4 * attribute.numComponents;
    }

    return count;
}

void VertexAttributes::checkValidity () {
    boolean pos = false;
    boolean cols = false;
    boolean nors = false;

    for (int i = 0; i < attributes.length; i++) {
        VertexAttribute attribute = attributes[i];
        if (attribute.usage == Usage.Position) {
            if (pos) throw new IllegalArgumentException("two position attributes were specified");
            pos = true;
        }

        if (attribute.usage == Usage.Normal) {
            if (nors) throw new IllegalArgumentException("two normal attributes were specified");
        }

        if (attribute.usage == Usage.Color || attribute.usage == Usage.ColorPacked) {
            if (attribute.numComponents != 4) throw new IllegalArgumentException("color attribute must have 4 components");

            if (cols) throw new IllegalArgumentException("two color attributes were specified");
            cols = true;
        }
    }

    if (pos == false) throw new IllegalArgumentException("no position attribute was specified");
}

int VertexAttributes::size () {
    return attributes.length;
}

VertexAttribute& VertexAttributes::get (int index) {
    return attributes[index];
}

std::string& VertexAttributes::toString () {
    StringBuilder builder = new StringBuilder();
    for (int i = 0; i < attributes.length; i++) {
        builder.append(attributes[i].alias);
        builder.append(", ");
        builder.append(attributes[i].usage);
        builder.append(", ");
        builder.append(attributes[i].numComponents);
        builder.append(", ");
        builder.append(attributes[i].offset);
        builder.append("\n");
    }
    return builder.toString();
}

