
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

#include "BoundGroup.hpp"

using namespace gdx_cpp::scenes::scene2d::actors;

bool BoundGroup::touchDown (float x,float y,int pointer) {
    if (focusedActor != null) {
        return super.touchDown(x, y, pointer);
    } else {
        if (!(x > 0 && y > 0 && x < width && y < height)) return false;
        return super.touchDown(x, y, pointer);
    }
}

bool BoundGroup::touchUp (float x,float y,int pointer) {
    if (focusedActor != null) {
        return super.touchUp(x, y, pointer);
    } else {
        if (!(x > 0 && y > 0 && x < width && y < height)) return false;
        return super.touchUp(x, y, pointer);
    }
}

bool BoundGroup::touchDragged (float x,float y,int pointer) {
    if (focusedActor != null) {
        return super.touchDragged(x, y, pointer);
    } else {
        if (!(x > 0 && y > 0 && x < width && y < height)) return false;
        return super.touchDragged(x, y, pointer);
    }
}

gdx_cpp::scenes::scene2d::Actor& BoundGroup::hit (float x,float y) {
    return x > 0 && y > 0 && x < width && y < height ? this : null;
}

