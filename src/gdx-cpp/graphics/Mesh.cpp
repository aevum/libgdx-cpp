
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

#include "Mesh.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/Graphics.hpp"
#include "gdx-cpp/graphics/GL10.hpp"
#include "gdx-cpp/graphics/GL11.hpp"
#include "gdx-cpp/graphics/GL20.hpp"
#include "gdx-cpp/graphics/glutils/VertexData.hpp"
#include "gdx-cpp/graphics/glutils/VertexArray.hpp"
#include "gdx-cpp/graphics/glutils/IndexData.hpp"
#include "gdx-cpp/graphics/glutils/VertexBufferObject.hpp"
#include "gdx-cpp/graphics/glutils/VertexBufferObjectSubData.hpp"
#include "gdx-cpp/graphics/glutils/IndexBufferObject.hpp"
#include "gdx-cpp/graphics/glutils/IndexBufferObjectSubData.hpp"
#include "gdx-cpp/graphics/glutils/ShaderProgram.hpp"
#include "gdx-cpp/math/collision/BoundingBox.hpp"
#include "gdx-cpp/gl.hpp"

#include <stdexcept>
#include <iostream>

using namespace gdx;

bool Mesh::forceVBO = false;
Mesh::MeshMap Mesh::meshes;

Mesh::Mesh(bool isStatic, int maxVertices, int maxIndices, const std::vector< VertexAttribute >& attributes)
: vertices(0),
autoBind(true),
disposed(false)
{
    if (gl20 != NULL || gl11 != NULL || Mesh::forceVBO) {
        vertices = new VertexBufferObject(isStatic, maxVertices, attributes);
        indices = new IndexBufferObject(isStatic, maxIndices);
        isVertexArray = false;
    } else {
        vertices = new VertexArray(maxVertices, attributes);
        indices = new IndexBufferObject(maxIndices);
        isVertexArray = true;
    }
    
    addManagedMesh(app, this);
}

void Mesh::setVertices (const std::vector<float>& vertices) {
    this->vertices->setVertices(&vertices[0], 0, vertices.size());
}

void Mesh::setVertices (const std::vector<float>& vertices, int offset,int count) {
    this->vertices->setVertices(&vertices[0], offset, count);
}

void Mesh::getVertices (std::vector<float>& vertices) {
    if (vertices.size() < getNumVertices() * getVertexSize() / 4)
    {
        std::stringstream ss;
        ss <<"not enough room in vertices array, has " << vertices.size() << " floats, needs "
        << getNumVertices() * getVertexSize() / 4;
        
        throw std::runtime_error(ss.str());
    }
    
    int pos = getVerticesBuffer().position();
    
    getVerticesBuffer().position(0);
    getVerticesBuffer().get(vertices, 0, getNumVertices() * getVertexSize() / 4);
    getVerticesBuffer().position(pos);
}

void Mesh::setIndices (std::vector<short>& indices) {
    this->indices->setIndices(indices, 0, indices.size());
}

void Mesh::setIndices (std::vector<short>& indices, int offset,int count) {
    this->indices->setIndices(indices, offset, count);
}

void Mesh::getIndices (std::vector<short>& indices) {
    if (indices.size() < getNumIndices())
    {
        std::stringstream ss;
        ss << "not enough room in indices array, has " << indices.size() << " floats, needs "
        << getNumIndices();
        throw std::runtime_error(ss.str());
    }

    short_buffer& indices_buffer = getIndicesBuffer();
    int pos = indices_buffer.position();
    
    indices_buffer.position(0);
    indices_buffer.get(indices, 0, getNumIndices());
    indices_buffer.position(pos);
}

unsigned int Mesh::getNumIndices () {
    return indices->getNumIndices();
}

unsigned int Mesh::getNumVertices () {
    return vertices->getNumVertices();
}

int Mesh::getMaxVertices () {
    return vertices->getNumMaxVertices();
}

int Mesh::getMaxIndices () {
    return indices->getNumMaxIndices();
}

int Mesh::getVertexSize () {
    return vertices->getAttributes().vertexSize;
}

void Mesh::setAutoBind (bool autoBind) {
    this->autoBind = autoBind;
}

void Mesh::bind () {
    if (graphics->isGL20Available())
        throw std::runtime_error("can't use this render method with OpenGL ES 2.0");
    vertices->bind();
    if (!isVertexArray && indices->getNumIndices() > 0) indices->bind();
}

void Mesh::unbind () {
    if (graphics->isGL20Available())
        throw std::runtime_error("can't use this render method with OpenGL ES 2.0");
    vertices->unbind();
    if (!isVertexArray && indices->getNumIndices() > 0) indices->unbind();
}

void Mesh::bind (ShaderProgram& shader) {
    if (!graphics->isGL20Available())
        throw std::runtime_error("can't use this render method with OpenGL ES 1.x");

    ((VertexBufferObject*)vertices)->bind(shader);
    if (indices->getNumIndices() > 0) indices->bind();
}

void Mesh::unbind (ShaderProgram& shader) {
    if (!graphics->isGL20Available()) throw std::runtime_error("can't use this render method with OpenGL ES 1.x");

    ((VertexBufferObject*)vertices)->unbind(shader);
    if (indices->getNumIndices() > 0) indices->unbind();
}

void Mesh::render (int primitiveType) {
    render(primitiveType, 0, indices->getNumMaxIndices() > 0 ? getNumIndices() : getNumVertices());
}

void Mesh::render (int primitiveType,int offset,int count) {
    if (graphics->isGL20Available()) throw std::runtime_error("can't use this render method with OpenGL ES 2.0");

    if (autoBind) bind();

    if (isVertexArray) {
        if (indices->getNumIndices() > 0) {
            short_buffer& buffer = indices->getBuffer();
            int oldPosition = buffer.position();
            int oldLimit = buffer.limit();
            buffer.position(offset);
            buffer.limit(offset + count);
            gl10->glDrawElements(primitiveType, count, GL_UNSIGNED_SHORT, (void *) ((char*)buffer + offset));
            buffer.position(oldPosition);
            buffer.limit(oldLimit);
        } else
            gl10->glDrawArrays(primitiveType, offset, count);
    } else {
        if (indices->getNumIndices() > 0) {
            int newoffset = offset * 2;
            gl11->glDrawElements(primitiveType, count, GL_UNSIGNED_SHORT, (void *) (intptr_t) newoffset );
        }
        else
            gl11->glDrawArrays(primitiveType, offset, count);
    }

    if (autoBind) unbind();
}

void Mesh::render (ShaderProgram& shader,int primitiveType) {
    render(shader, primitiveType, 0, indices->getNumMaxIndices() > 0 ? getNumIndices() : getNumVertices());
}

void Mesh::render (ShaderProgram& shader,int primitiveType,int offset,int count) {
    if (!graphics->isGL20Available()) throw std::runtime_error("can't use this render method with OpenGL ES 1.x");

    if (autoBind) bind(shader);

    if (indices->getNumIndices() > 0)
        gl20->glDrawElements(primitiveType, count, GL_UNSIGNED_SHORT, offset * 2);
    else
        gl20->glDrawArrays(primitiveType, offset, count);

    if (autoBind) unbind(shader);
}

void Mesh::dispose () {
    if (!disposed) {
        if (meshes.count(app) > 0 && meshes[app].count(this))
            meshes[app].erase(this);
        vertices->dispose();
        indices->dispose();
    }
}

VertexAttribute* const Mesh::getVertexAttribute (int usage) {
    VertexAttributes& attributes = vertices->getAttributes();
    int len = attributes.size();
    for (int i = 0; i < len; i++) {
        if (attributes.get(i).usage == usage){
            return &attributes.get(i);
        }
    }

    return NULL;
}

VertexAttributes& Mesh::getVertexAttributes () {
    return vertices->getAttributes();
}

float_buffer& Mesh::getVerticesBuffer () {
    return vertices->getBuffer();
}

void Mesh::calculateBoundingBox (BoundingBox& bbox) {
    int numVertices = getNumVertices();
    if (numVertices == 0) throw std::runtime_error("No vertices defined");

    float_buffer verts = vertices->getBuffer();
    bbox.inf();
    VertexAttribute& posAttrib = *getVertexAttribute(VertexAttributes::Usage::Position);
    int offset = posAttrib.offset / 4;
    int vertexSize = vertices->getAttributes().vertexSize / 4;
    int idx = offset;

    switch (posAttrib.numComponents) {
    case 1:
        for (int i = 0; i < numVertices; i++) {
            bbox.ext(verts.get(idx), 0, 0);
            idx += vertexSize;
        }
        break;
    case 2:
        for (int i = 0; i < numVertices; i++) {
            bbox.ext(verts.get(idx), verts.get(idx + 1), 0);
            idx += vertexSize;
        }
        break;
    case 3:
        for (int i = 0; i < numVertices; i++) {
            bbox.ext(verts.get(idx), verts.get(idx + 1), verts.get(idx + 2));
            idx += vertexSize;
        }
        break;
    }
}

short_buffer& Mesh::getIndicesBuffer () {
    return indices->getBuffer();
}

void Mesh::addManagedMesh (Application* app, Mesh* mesh) {
    meshes[app].insert(mesh);
}

void Mesh::invalidateAllMeshes (Application* app) {
    MeshMap::value_type::second_type::iterator it = meshes[app].begin();
    MeshMap::value_type::second_type::iterator end = meshes[app].end();
    
    for (; it != end; ++it) {
        if ((*it)->vertices->getKind() ==  VertexData::Kind::VertexBufferObject) {
            (((VertexBufferObject*)(*it)->vertices))->invalidate();
            (*it)->indices->invalidate();
        }
    }
}

void Mesh::clearAllMeshes (Application* app) {
    meshes.erase(app);
}

std::string Mesh::getManagedStatus () {
    std::stringstream  builder;
    builder << "Managed meshes/app: { ";

    MeshMap::iterator it = meshes.begin();
    MeshMap::iterator end = meshes.end();
    
    for (; it != end; ++it) {
        builder << it->second.size();
        builder << " ";
    }
    builder << "}";
    return builder.str();
}

void Mesh::scale (float scaleX,float scaleY,float scaleZ) {
    VertexAttribute& posAttr = *getVertexAttribute(VertexAttributes::Usage::Position);
    int offset = posAttr.offset / 4;
    int numComponents = posAttr.numComponents;
    int numVertices = getNumVertices();
    int vertexSize = getVertexSize() / 4;

    std::vector<float> vertices(numVertices * vertexSize);
    getVertices(vertices);

    int idx = offset;
    switch (numComponents) {
    case 1:
        for (int i = 0; i < numVertices; i++) {
            vertices[idx] *= scaleX;
            idx += vertexSize;
        }
        break;
    case 2:
        for (int i = 0; i < numVertices; i++) {
            vertices[idx] *= scaleX;
            vertices[idx + 1] *= scaleY;
            idx += vertexSize;
        }
        break;
    case 3:
        for (int i = 0; i < numVertices; i++) {
            vertices[idx] *= scaleX;
            vertices[idx + 1] *= scaleY;
            vertices[idx + 2] *= scaleZ;
            idx += vertexSize;
        }
        break;
    }

    setVertices(vertices);
}
Mesh::Mesh(int type, bool isStatic, int maxVertices, int maxIndices, const std::vector< VertexAttribute >& attributes)
: vertices(0),
autoBind(true),
disposed(false)
{
    if (type == VertexDataType::VertexArray && graphics->isGL20Available())
        type = VertexDataType::VertexBufferObject;

    if (type == VertexDataType::VertexBufferObject) {
        vertices = new VertexBufferObject(isStatic, maxVertices, attributes);
        indices = new IndexBufferObject(isStatic, maxIndices);
        isVertexArray = false;
    } else if (type == VertexDataType::VertexBufferObjectSubData) {
        vertices = new VertexBufferObjectSubData(isStatic, maxVertices, attributes);
        indices = new IndexBufferObjectSubData(isStatic, maxIndices);
        isVertexArray = false;
    } else {
        vertices = new VertexArray(maxVertices, attributes);
        indices = new IndexBufferObject(maxIndices);
        isVertexArray = true;
    }
    addManagedMesh(app, this);
}

void Mesh::setVertices(const float* vertices, int size) {
    this->vertices->setVertices(vertices, 0, size);
}

Mesh::~Mesh()
{
    dispose();
    delete vertices;
    delete indices;
}
