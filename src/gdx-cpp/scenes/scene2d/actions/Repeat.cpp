
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

#include "Repeat.hpp"

using namespace gdx_cpp::scenes::scene2d::actions;

ActionResetingPool<Repeat> Repeat::pool = ActionResetingPool<Repeat>(4, 100);

Repeat* Repeat::build (gdx_cpp::scenes::scene2d::Action* action,int times) {
    Repeat* repeat = pool.obtain();
    repeat->action = action;
    repeat->times = times;
    return repeat;
}

void Repeat::reset () {
    TemporalAction::reset();
    finishedTimes = 0;
    listener = NULL;
}

void Repeat::setTarget (gdx_cpp::scenes::scene2d::Actor* actor) {
    action->setTarget(actor);
    target = actor;
}

void Repeat::act (float delta) {
    action->act(delta);
    if (action->isDone()) {
        finishedTimes++;
        if (finishedTimes < times) {
            Action* oldAction = action;
            action = action->copy();
            oldAction->finish();
            action->setTarget(target);
        } else {
            callActionCompletedListener();
        }
    }
}

bool Repeat::isDone () {
    return finishedTimes >= times;
}

void Repeat::finish () {
    pool.free(this);
    action->finish();
    TemporalAction::finish();
}

gdx_cpp::scenes::scene2d::Action* Repeat::copy () {
    return Repeat::build(action->copy(), times);
}

gdx_cpp::scenes::scene2d::Actor* Repeat::getTarget () {
    return target;
}
