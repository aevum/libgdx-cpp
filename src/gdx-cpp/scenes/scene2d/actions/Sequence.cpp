
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
#include <cstdarg>

using namespace gdx::actions;

ActionResetingPool<Sequence> Sequence::pool = ActionResetingPool<Sequence>(4, 100);

void Sequence::setTarget (gdx::Actor* actor) {
    this->target = actor;
    if (actions.size() > 0) actions[0]->setTarget(target);
    this->currAction = 0;
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

    actions[currAction]->act(delta);
    
    if (actions[currAction]->isDone()) {
        actions[currAction]->callActionCompletedListener();
        currAction++;
        if (currAction < actions.size()) actions[currAction]->setTarget(target);
    }
}

bool Sequence::isDone () {
    return currAction >= actions.size();
}

void Sequence::finish () {
    pool.free(this);
    CompositeAction::finish();
}

gdx::Action* Sequence::copy () {
    Sequence* action = pool.obtain();

    action->actions.clear();

    std::vector<Action*>::iterator it = actions.begin();
    std::vector<Action*>::iterator end = actions.end();
    
    for (; it != end; ++it) {
        action->actions.push_back((*it)->copy());
    }
    
    return action;
}

gdx::Actor* Sequence::getTarget () {
    return target;
}

Sequence::Sequence()
: target(0)
, currAction(0)
{
}