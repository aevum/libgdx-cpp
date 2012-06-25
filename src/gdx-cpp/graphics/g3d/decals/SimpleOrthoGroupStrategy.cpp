
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

#include "SimpleOrthoGroupStrategy.hpp"

using namespace gdx::g3d::decals;

int SimpleOrthoGroupStrategy::decideGroup (const Decal& decal) {
    return decal.getMaterial().isOpaque() ? GROUP_OPAQUE : GROUP_BLEND;
}

void SimpleOrthoGroupStrategy::beforeGroup (int group,gdx::ArrayDecal>& contents) {
    if (group == GROUP_BLEND) {
        Sort.instance().sort(contents, comparator);
        Gdx.gl10.glEnable(GL10.GL_BLEND);
        // no need for writing into the z buffer if transparent decals are the last thing to be rendered
        // and they are rendered back to front
        Gdx.gl10.glDepthMask(false);
    } else {
        // FIXME sort by material
    }
}

void SimpleOrthoGroupStrategy::afterGroup (int group) {
    if (group == GROUP_BLEND) {
        Gdx.gl10.glDepthMask(true);
        Gdx.gl10.glDisable(GL10.GL_BLEND);
    }
}

void SimpleOrthoGroupStrategy::beforeGroups () {
    Gdx.gl10.glEnable(GL10.GL_TEXTURE_2D);
}

void SimpleOrthoGroupStrategy::afterGroups () {
    Gdx.gl10.glDisable(GL10.GL_TEXTURE_2D);
}

int SimpleOrthoGroupStrategy::compare (const Decal& a,const Decal& b) {
    return a.getZ() - b.getZ() < 0 ? -1 : 1;
}

gdx::ShaderProgram& SimpleOrthoGroupStrategy::getGroupShader (int group) {
    return null;
}

