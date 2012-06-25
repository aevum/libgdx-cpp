
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

#include "PluggableGroupStrategy.hpp"

using namespace gdx::g3d::decals;

void PluggableGroupStrategy::beforeGroup (int group,gdx::ArrayDecal>& contents) {
    plugs.get(group).beforeGroup(contents);
}

void PluggableGroupStrategy::afterGroup (int group) {
    plugs.get(group).afterGroup();
}

void PluggableGroupStrategy::plugIn (const GroupPlug& plug,int group) {
    plugs.put(group, plug);
}

GroupPlug& PluggableGroupStrategy::unPlug (int group) {
    return plugs.remove(group);
}

