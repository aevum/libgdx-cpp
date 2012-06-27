
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

using namespace gdx::actions;

ActionResetingPool<Remove> Remove::pool = ActionResetingPool<Remove>(4, 100);

Remove::Remove()
: target(0),
removed(false)
{
}

Remove* Remove::build () {
    Remove* remove = pool.obtain();
    remove->removed = false;
    remove->target = NULL;
    return remove;
}

void Remove::setTarget (gdx::Actor* actor) {
    this->target = actor;
}

void Remove::act (float delta) {
    if (!removed) {
        target->markToRemove(true);
        removed = true;
        callActionCompletedListener();
    }
}

bool Remove::isDone () {
    return removed;
}

gdx::Action* Remove::copy () {
    return Remove::build();
}

gdx::Actor* Remove::getTarget () {
    return target;
}

