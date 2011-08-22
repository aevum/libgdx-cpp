
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

#include "Remove.hpp"

using namespace gdx_cpp::scenes::scene2d::actions;

Remove& Remove::newObject () {
    return new Remove();
}

Remove& Remove::$ () {
    Remove remove = pool.obtain();
    remove.removed = false;
    remove.target = null;
    return remove;
}

void Remove::setTarget (const gdx_cpp::scenes::scene2d::Actor& actor) {
    this.target = actor;
}

void Remove::act (float delta) {
    if (!removed) {
        target.markToRemove(true);
        removed = true;
        callActionCompletedListener();
    }
}

bool Remove::isDone () {
    return removed;
}

gdx_cpp::scenes::scene2d::Action& Remove::copy () {
    return $();
}

gdx_cpp::scenes::scene2d::Actor& Remove::getTarget () {
    return target;
}

