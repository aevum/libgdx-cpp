
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

#include "CameraGroupStrategy.hpp"

using namespace gdx::g3d::decals;

gdx::ArrayDecal>& CameraGroupStrategy::newObject () {
    return new Array<Decal>();
}

int CameraGroupStrategy::compare (const Decal& o1,const Decal& o2) {
    float dist1 = camera.position.dst2(o1.position);
    float dist2 = camera.position.dst2(o2.position);
    return (int)Math.signum(dist2 - dist1);
}

void CameraGroupStrategy::setCamera (const gdx::Camera& camera) {
    this.camera = camera;
}

gdx::Camera& CameraGroupStrategy::getCamera () {
    return camera;
}

int CameraGroupStrategy::decideGroup (const Decal& decal) {
    return decal.getMaterial().isOpaque() ? GROUP_OPAQUE : GROUP_BLEND;
}

void CameraGroupStrategy::beforeGroup (int group,gdx::ArrayDecal>& contents) {
    if (group == GROUP_BLEND) {
        Gdx.gl.glEnable(GL10.GL_BLEND);
        contents.sort(cameraSorter);
    } else {
        for (int i = 0, n = contents.size; i < n; i++) {
            Decal decal = contents.get(i);
            Array<Decal> materialGroup = materialGroups.get(decal.material);
            if (materialGroup == null) {
                materialGroup = arrayPool.obtain();
                materialGroup.clear();
                usedArrays.add(materialGroup);
                materialGroups.put(decal.material, materialGroup);
            }
            materialGroup.add(decal);
        }

        contents.clear();
for (Array<Decal> materialGroup : materialGroups.values()) {
            contents.addAll(materialGroup);
        }

        materialGroups.clear();
        arrayPool.free(usedArrays);
        usedArrays.clear();
    }
}

void CameraGroupStrategy::afterGroup (int group) {
    if (group == GROUP_BLEND) {
        Gdx.gl.glDisable(GL10.GL_BLEND);
    }
}

void CameraGroupStrategy::beforeGroups () {
    Gdx.gl.glEnable(GL10.GL_TEXTURE_2D);
    if (shader != null) {
        shader.begin();
        shader.setUniformMatrix("u_projectionViewMatrix", camera.combined);
        shader.setUniformi("u_texture", 0);
    } else {
        Gdx.gl10.glMatrixMode(GL10.GL_PROJECTION);
        Gdx.gl10.glLoadMatrixf(camera.projection.val, 0);
        Gdx.gl10.glMatrixMode(GL10.GL_MODELVIEW);
        Gdx.gl10.glLoadMatrixf(camera.view.val, 0);
    }
}

void CameraGroupStrategy::afterGroups () {
    if (shader != null) {
        shader.end();
    }
    Gdx.gl.glDisable(GL10.GL_TEXTURE_2D);
}

void CameraGroupStrategy::createDefaultShader () {
    if (Gdx.graphics.isGL20Available()) {
        String vertexShader = "attribute vec4 " + ShaderProgram.POSITION_ATTRIBUTE + ";\n" //
                              + "attribute vec4 " + ShaderProgram.COLOR_ATTRIBUTE + ";\n" //
                              + "attribute vec2 " + ShaderProgram.TEXCOORD_ATTRIBUTE + "0;\n" //
                              + "uniform mat4 u_projectionViewMatrix;\n" //
                              + "varying vec4 v_color;\n" //
                              + "varying vec2 v_texCoords;\n" //
                              + "\n" //
                              + "void main()\n" //
                              + "{\n" //
                              + "   v_color = " + ShaderProgram.COLOR_ATTRIBUTE + ";\n" //
                              + "   v_texCoords = " + ShaderProgram.TEXCOORD_ATTRIBUTE + "0;\n" //
                              + "   gl_Position =  u_projectionViewMatrix * " + ShaderProgram.POSITION_ATTRIBUTE + ";\n" //
                              + "}\n";
        String fragmentShader = "#ifdef GL_ES\n" //
                                + "precision mediump float;\n" //
                                + "#endif\n" //
                                + "varying vec4 v_color;\n" //
                                + "varying vec2 v_texCoords;\n" //
                                + "uniform sampler2D u_texture;\n" //
                                + "void main()\n"//
                                + "{\n" //
                                + "  gl_FragColor = v_color * texture2D(u_texture, v_texCoords);\n" //
                                + "}";

        shader = new ShaderProgram(vertexShader, fragmentShader);
        if (shader.isCompiled() == false) throw new IllegalArgumentException("couldn't compile shader: " + shader.getLog());
    }
}

gdx::ShaderProgram& CameraGroupStrategy::getGroupShader (int group) {
    return shader;
}

