
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

#include "MD5Renderer.hpp"

using namespace gdx_cpp::graphics::g3d::loaders::md5;

gdx_cpp::math::collision::BoundingBox& MD5Renderer::getBBox () {
    return mBBox;
}

float* MD5Renderer::getVertices (int idx) {
    return vertices[idx];
}

short* MD5Renderer::getIndices (int idx) {
    return indices[idx];
}

gdx_cpp::graphics::Mesh& MD5Renderer::getMesh () {
    return mesh;
}

void MD5Renderer::setSkeleton (const MD5Joints& skeleton) {
    mBBox.clr();
    for (int i = 0; i < model.meshes.length; i++) {
        MD5Mesh mesh = model.meshes[i];

        if (useJni) {
            mesh.calculateVerticesJni(skeleton, vertices[i]);
        } else {
            if (useNormals) {
                mesh.calculateVerticesN(skeleton, vertices[i], mBBox);
            } else {
                mesh.calculateVertices(skeleton, vertices[i], mBBox);
            }
        }

    }
}

void MD5Renderer::setUseJni (bool useJni) {
    this.useJni = useJni;
}

void MD5Renderer::calculateNormals (const MD5Joints& bindPoseSkeleton) {
    for (int i = 0; i < model.meshes.length; i++) {
        MD5Mesh mesh = model.meshes[i];
        mesh.calculateNormalsBind(bindPoseSkeleton, vertices[i]);
    }
}

void MD5Renderer::render () {
    for (int i = 0; i < model.meshes.length; i++) {
        this.mesh.setIndices(indices[i]);
        this.mesh.setVertices(vertices[i]);
        this.mesh.render(GL10.GL_TRIANGLES, 0, indices[i].length);
    }
}

void MD5Renderer::render () {
    for (int i = 0; i < model.meshes.length; i++) {
        if (materials[i] != null) {
            if (materials[i].Texture != null) {
                materials[i].Texture.bind();
            }
            materials[i].set(GL10.GL_FRONT);
        }

        this.mesh.setIndices(indices[i]);
        this.mesh.setVertices(vertices[i]);
        this.mesh.render(GL10.GL_TRIANGLES, 0, indices[i].length);
    }
}

void MD5Renderer::dispose () {
    mesh.dispose();
}

bool MD5Renderer::isJniUsed () {
    return useJni;
}

