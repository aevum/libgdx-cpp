
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

#include <sstream>
#include <cassert>

#include "gdx-cpp/Gdx.hpp"
#include <stdexcept>

using namespace gdx_cpp::graphics;

VertexAttributes::VertexAttributes (const std::vector<VertexAttribute>& attributes)
        : attributes(attributes)
{
    if (attributes.size() == 0) {
        throw std::runtime_error("attributes must be >= 1");
    }

    checkValidity();
    vertexSize = calculateOffsets();
}

int VertexAttributes::calculateOffsets () {
    int count = 0;
    for (unsigned int i = 0; i < attributes.size(); i++) {
        VertexAttribute& attribute = attributes[i];
        attribute.offset = count;
        if (attribute.usage == VertexAttributes::Usage::ColorPacked)
            count += 4;
        else
            count += 4 * attribute.numComponents;
    }

    return count;
}

void VertexAttributes::checkValidity () {
    bool pos = false;
    bool cols = false;
    bool nors = false;

    for (unsigned int i = 0; i < attributes.size(); i++) {
        const VertexAttribute& attribute = attributes[i];
        if (attribute.usage == Usage::Position) {
            if (pos) {
                throw std::runtime_error("two position attributes were specified");
            }

            pos = true;
        }

        if (attribute.usage == Usage::Normal) {
            if (nors) {
                throw std::runtime_error("two normal attributes were specified");
            }
        }

        if (attribute.usage == Usage::Color || attribute.usage == Usage::ColorPacked) {
            if (attribute.numComponents != 4) {
                throw std::runtime_error("color attribute must have 4 components");
            }

            if (cols) {
                throw std::runtime_error("two color attributes were specified");
            }

            cols = true;
        }
    }

    if (pos == false) {
      throw std::runtime_error("no position attribute was specified");
    }
}

int VertexAttributes::size () {
    return attributes.size();
}

VertexAttribute& VertexAttributes::get (int index) {
    return attributes[index];
}

std::string VertexAttributes::toString () {
    std::stringstream builder;
    for (unsigned int i = 0; i < attributes.size(); i++) {
        builder << attributes[i].alias << ", " <<
        attributes[i].usage << ", " <<
        attributes[i].numComponents <<  ", " <<
        attributes[i].offset <<  std::endl;
    }
    return builder.str();
}

