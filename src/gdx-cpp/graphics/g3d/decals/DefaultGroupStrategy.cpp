
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

#include "DefaultGroupStrategy.hpp"

using namespace gdx::g3d::decals;

int DefaultGroupStrategy::decideGroup (const Decal& decal) {
    return decal.getMaterial().isOpaque() ? GROUP_OPAQUE : GROUP_BLEND;
}

void DefaultGroupStrategy::beforeGroup (int group,gdx::ArrayDecal>& contents) {
    if (group == GROUP_BLEND) {
        Gdx.gl10.glEnable(GL10.GL_BLEND);
    }
}

void DefaultGroupStrategy::afterGroup (int group) {
    if (group == GROUP_BLEND) {
        Gdx.gl10.glDisable(GL10.GL_BLEND);
    }
}

void DefaultGroupStrategy::beforeGroups () {
    Gdx.gl10.glEnable(GL10.GL_TEXTURE_2D);
}

void DefaultGroupStrategy::afterGroups () {
    Gdx.gl10.glDisable(GL10.GL_TEXTURE_2D);
}

gdx::ShaderProgram& DefaultGroupStrategy::getGroupShader (int group) {
    return null;
}

