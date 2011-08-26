
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
#include "gdx-cpp/graphics/glutils/VertexData.hpp"
#include "gdx-cpp/graphics/glutils/IndexData.hpp"
#include <stdexcept>

using namespace gdx_cpp::graphics;

bool Mesh::forceVBO = false;

Mesh::Mesh(bool isStatic, int maxVertices, int maxIndices, std::vector< gdx_cpp::graphics::VertexAttribute > attributes)
: vertices(0)
{
    if (gdx_cpp::Gdx::gl20 != NULL || gdx_cpp::Gdx::gl11 != NULL || Mesh::forceVBO) {
        vertices = new glutils::VertexBufferObject(isStatic, maxVertices, attributes);
        indices = new glutils::IndexBufferObject(isStatic, maxIndices);
        isVertexArray = false;
    } else {
        vertices = new glutils::VertexArray(maxVertices, attributes);
        indices = new glutils::IndexBufferObject(maxIndices);
        isVertexArray = true;
    }
    
    addManagedMesh(gdx_cpp::Gdx::app, this);
}


void Mesh::setVertices () {
    this->vertices->setVertices(vertices, 0, vertices.length);
}

void Mesh::setVertices (int offset,int count) {
    this->vertices->setVertices(vertices, offset, count);
}

void Mesh::getVertices () {
    if (vertices.length < getNumVertices() * getVertexSize() / 4)
        throw std::runtime_error("not enough room in vertices array, has " + vertices.length + " floats, needs "
                                           + getNumVertices() * getVertexSize() / 4);
    int pos = getVerticesBuffer().position();
    
    getVerticesBuffer().position(0);
    getVerticesBuffer().get(vertices, 0, getNumVertices() * getVertexSize() / 4);
    getVerticesBuffer().position(pos);
}

void Mesh::setIndices () {
    this.indices.setIndices(indices, 0, indices.length);
}

void Mesh::setIndices (int offset,int count) {
    this.indices.setIndices(indices, offset, count);
}

void Mesh::getIndices () {
    if (indices.length < getNumIndices())
        throw new IllegalArgumentException("not enough room in indices array, has " + indices.length + " floats, needs "
                                           + getNumIndices());
    int pos = getIndicesBuffer().position();
    getIndicesBuffer().position(0);
    getIndicesBuffer().get(indices, 0, getNumIndices());
    getIndicesBuffer().position(pos);
}

int Mesh::getNumIndices () {
    return indices.getNumIndices();
}

int Mesh::getNumVertices () {
    return vertices.getNumVertices();
}

int Mesh::getMaxVertices () {
    return vertices.getNumMaxVertices();
}

int Mesh::getMaxIndices () {
    return indices.getNumMaxIndices();
}

int Mesh::getVertexSize () {
    return vertices.getAttributes().vertexSize;
}

void Mesh::setAutoBind (bool autoBind) {
    this.autoBind = autoBind;
}

void Mesh::bind () {
    if (Gdx.graphics.isGL20Available()) throw new IllegalStateException("can't use this render method with OpenGL ES 2.0");
    vertices.bind();
    if (!isVertexArray && indices.getNumIndices() > 0) indices.bind();
}

void Mesh::unbind () {
    if (Gdx.graphics.isGL20Available()) throw new IllegalStateException("can't use this render method with OpenGL ES 2.0");
    vertices.unbind();
    if (!isVertexArray && indices.getNumIndices() > 0) indices.unbind();
}

void Mesh::bind (const gdx_cpp::graphics::glutils::ShaderProgram& shader) {
    if (!Gdx.graphics.isGL20Available()) throw new IllegalStateException("can't use this render method with OpenGL ES 1.x");

    ((VertexBufferObject)vertices).bind(shader);
    if (indices.getNumIndices() > 0) indices.bind();
}

void Mesh::unbind (const gdx_cpp::graphics::glutils::ShaderProgram& shader) {
    if (!Gdx.graphics.isGL20Available()) throw new IllegalStateException("can't use this render method with OpenGL ES 1.x");

    ((VertexBufferObject)vertices).unbind(shader);
    if (indices.getNumIndices() > 0) indices.unbind();
}

void Mesh::render (int primitiveType) {
    render(primitiveType, 0, indices.getNumMaxIndices() > 0 ? getNumIndices() : getNumVertices());
}

void Mesh::render (int primitiveType,int offset,int count) {
    if (Gdx.graphics.isGL20Available()) throw new IllegalStateException("can't use this render method with OpenGL ES 2.0");

    if (autoBind) bind();

    if (isVertexArray) {
        if (indices.getNumIndices() > 0) {
            ShortBuffer buffer = indices.getBuffer();
            int oldPosition = buffer.position();
            int oldLimit = buffer.limit();
            buffer.position(offset);
            buffer.limit(offset + count);
            Gdx.gl10.glDrawElements(primitiveType, count, GL10.GL_UNSIGNED_SHORT, buffer);
            buffer.position(oldPosition);
            buffer.limit(oldLimit);
        } else
            Gdx.gl10.glDrawArrays(primitiveType, offset, count);
    } else {
        if (indices.getNumIndices() > 0)
            Gdx.gl11.glDrawElements(primitiveType, count, GL10.GL_UNSIGNED_SHORT, offset * 2);
        else
            Gdx.gl11.glDrawArrays(primitiveType, offset, count);
    }

    if (autoBind) unbind();
}

void Mesh::render (const gdx_cpp::graphics::glutils::ShaderProgram& shader,int primitiveType) {
    render(shader, primitiveType, 0, indices.getNumMaxIndices() > 0 ? getNumIndices() : getNumVertices());
}

void Mesh::render (const gdx_cpp::graphics::glutils::ShaderProgram& shader,int primitiveType,int offset,int count) {
    if (!Gdx.graphics.isGL20Available()) throw new IllegalStateException("can't use this render method with OpenGL ES 1.x");

    if (autoBind) bind(shader);

    if (indices.getNumIndices() > 0)
        Gdx.gl20.glDrawElements(primitiveType, count, GL10.GL_UNSIGNED_SHORT, offset * 2);
    else
        Gdx.gl20.glDrawArrays(primitiveType, offset, count);

    if (autoBind) unbind(shader);
}

void Mesh::dispose () {
    refCount--;
    if (refCount > 0) return;
    if (meshes.get(Gdx.app) != null) meshes.get(Gdx.app).remove(this);
    vertices.dispose();
    indices.dispose();
}

VertexAttribute& Mesh::getVertexAttribute (int usage) {
    VertexAttributes attributes = vertices.getAttributes();
    int len = attributes.size();
    for (int i = 0; i < len; i++)
        if (attributes.get(i).usage == usage) return attributes.get(i);

    return null;
}

VertexAttributes& Mesh::getVertexAttributes () {
    return vertices.getAttributes();
}

FloatBuffer& Mesh::getVerticesBuffer () {
    return vertices.getBuffer();
}

gdx_cpp::math::collision::BoundingBox& Mesh::calculateBoundingBox () {
    BoundingBox bbox = new BoundingBox();
    calculateBoundingBox(bbox);
    return bbox;
}

void Mesh::calculateBoundingBox (const gdx_cpp::math::collision::BoundingBox& bbox) {
    final int numVertices = getNumVertices();
    if (numVertices == 0) throw new GdxRuntimeException("No vertices defined");

    final FloatBuffer verts = vertices.getBuffer();
    bbox.inf();
    final VertexAttribute posAttrib = getVertexAttribute(Usage.Position);
    final int offset = posAttrib.offset / 4;
    final int vertexSize = vertices.getAttributes().vertexSize / 4;
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

ShortBuffer& Mesh::getIndicesBuffer () {
    return indices.getBuffer();
}

void Mesh::addManagedMesh (const gdx_cpp::Application& app, gdx_cpp::graphics::Mesh* mesh) {
    List<Mesh> managedResources = meshes.get(app);
    if (managedResources == null) managedResources = new ArrayList<Mesh>();
    managedResources.add(mesh);
    meshes.put(app, managedResources);
}

void Mesh::invalidateAllMeshes (const gdx_cpp::Application& app) {
    List<Mesh> meshesList = meshes.get(app);
    if (meshesList == null) return;
    for (int i = 0; i < meshesList.size(); i++) {
        if (meshesList.get(i).vertices instanceof VertexBufferObject) {
            ((VertexBufferObject)meshesList.get(i).vertices).invalidate();
            meshesList.get(i).indices.invalidate();
        }
    }
}

void Mesh::clearAllMeshes (const gdx_cpp::Application& app) {
    meshes.remove(app);
}

std::string& Mesh::getManagedStatus () {
    StringBuilder builder = new StringBuilder();
    int i = 0;
    builder.append("Managed meshes/app: { ");
for (Application app : meshes.keySet()) {
        builder.append(meshes.get(app).size());
        builder.append(" ");
    }
    builder.append("}");
    return builder.toString();
}

void Mesh::scale (float scaleX,float scaleY,float scaleZ) {
    VertexAttribute posAttr = getVertexAttribute(Usage.Position);
    int offset = posAttr.offset / 4;
    int numComponents = posAttr.numComponents;
    int numVertices = getNumVertices();
    int vertexSize = getVertexSize() / 4;

    float[] vertices = new float[numVertices * vertexSize];
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
