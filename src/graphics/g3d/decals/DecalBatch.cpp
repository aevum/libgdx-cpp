
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

#include "DecalBatch.hpp"

using namespace gdx_cpp::graphics::g3d::decals;

gdx_cpp::utils::ArrayDecal>& DecalBatch::newObject () {
    return new Array<Decal>(false, 100);
}

void DecalBatch::setGroupStrategy (const GroupStrategy& groupStrategy) {
    this.groupStrategy = groupStrategy;
}

void DecalBatch::initialize (int size) {
    vertices = new float[size * Decal.SIZE];
    mesh = new Mesh(Mesh.VertexDataType.VertexArray, false, size * 4, size * 6, new VertexAttribute(
                        VertexAttributes.Usage.Position, 3, ShaderProgram.POSITION_ATTRIBUTE), new VertexAttribute(
                        VertexAttributes.Usage.ColorPacked, 4, ShaderProgram.COLOR_ATTRIBUTE), new VertexAttribute(
                        VertexAttributes.Usage.TextureCoordinates, 2, ShaderProgram.TEXCOORD_ATTRIBUTE + "0"));

    short[] indices = new short[size * 6];
    int v = 0;
    for (int i = 0; i < indices.length; i += 6, v += 4) {
        indices[i] = (short)(v);
        indices[i + 1] = (short)(v + 2);
        indices[i + 2] = (short)(v + 1);
        indices[i + 3] = (short)(v + 1);
        indices[i + 4] = (short)(v + 2);
        indices[i + 5] = (short)(v + 3);
    }
    mesh.setIndices(indices);
}

int DecalBatch::getSize () {
    return vertices.length / Decal.SIZE;
}

void DecalBatch::add (const Decal& decal) {
    DecalMaterial material = decal.getMaterial();
    int groupIndex = groupStrategy.decideGroup(decal);
    Array<Decal> targetGroup = groupList.get(groupIndex);
    if (targetGroup == null) {
        targetGroup = groupPool.obtain();
        targetGroup.clear();
        usedGroups.add(targetGroup);
        groupList.insert(groupIndex, targetGroup);
    }
    targetGroup.add(decal);
}

void DecalBatch::flush () {
    render();
    clear();
}

void DecalBatch::render () {
    groupStrategy.beforeGroups();
for (SortedIntList.Node<Array<Decal>> group : groupList) {
        groupStrategy.beforeGroup(group.index, group.value);
        ShaderProgram shader = groupStrategy.getGroupShader(group.index);
        render(shader, group.value);
        groupStrategy.afterGroup(group.index);
    }
    groupStrategy.afterGroups();
}

void DecalBatch::render (const gdx_cpp::graphics::glutils::ShaderProgram& shader,gdx_cpp::utils::ArrayDecal>& decals) {
    // batch vertices
    DecalMaterial lastMaterial = null;
    int idx = 0;
for (Decal decal : decals) {
        if (lastMaterial == null || !lastMaterial.equals(decal.getMaterial())) {
            if (idx > 0) {
                flush(shader, idx);
                idx = 0;
            }
            decal.material.set();
            lastMaterial = decal.material;
        }
        decal.update();
        System.arraycopy(decal.vertices, 0, vertices, idx, decal.vertices.length);
        idx += decal.vertices.length;
        // if our batch is full we have to flush it
        if (idx == vertices.length) {
            flush(shader, idx);
            idx = 0;
        }
    }
    // at the end if there is stuff left in the batch we render that
    if (idx > 0) {
        flush(shader, idx);
    }
}

void DecalBatch::flush (const gdx_cpp::graphics::glutils::ShaderProgram& shader,int verticesPosition) {
    mesh.setVertices(vertices, 0, verticesPosition);
    if (shader != null) {
        mesh.render(shader, GL10.GL_TRIANGLES, 0, verticesPosition / 4);
    } else {
        mesh.render(GL10.GL_TRIANGLES, 0, verticesPosition / 4);
    }
}

void DecalBatch::clear () {
    groupList.clear();
    groupPool.free(usedGroups);
    usedGroups.clear();
}

void DecalBatch::dispose () {
    clear();
    vertices = null;
    mesh.dispose();
}

