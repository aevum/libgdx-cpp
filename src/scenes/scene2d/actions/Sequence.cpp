
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

#include "Sequence.hpp"

using namespace gdx_cpp::scenes::scene2d::actions;

Sequence& Sequence::newObject () {
    return new Sequence();
}

Sequence& Sequence::$ () {
    Sequence sequence = pool.obtain();
    sequence.actions.clear();
    int len = actions.length;
    for (int i = 0; i < len; i++)
        sequence.actions.add(actions[i]);
    return sequence;
}

void Sequence::setTarget (const gdx_cpp::scenes::scene2d::Actor& actor) {
    this.target = actor;
    if (actions.size() > 0) actions.get(0).setTarget(target);
    this.currAction = 0;
}

void Sequence::act (float delta) {
    if (actions.size() == 0) {
        currAction = 1;
        return;
    }

    if (currAction >= actions.size()) {
        callActionCompletedListener();
        return;
    }

    actions.get(currAction).act(delta);
    if (actions.get(currAction).isDone()) {
        actions.get(currAction).callActionCompletedListener();
        currAction++;
        if (currAction < actions.size()) actions.get(currAction).setTarget(target);
    }
}

bool Sequence::isDone () {
    return currAction >= actions.size();
}

void Sequence::finish () {
    pool.free(this);
    super.finish();
}

gdx_cpp::scenes::scene2d::Action& Sequence::copy () {
    Sequence action = pool.obtain();
    action.actions.clear();
    int len = actions.size();
    for (int i = 0; i < len; i++) {
        action.actions.add(actions.get(i).copy());
    }
    return action;
}

gdx_cpp::scenes::scene2d::Actor& Sequence::getTarget () {
    return target;
}

