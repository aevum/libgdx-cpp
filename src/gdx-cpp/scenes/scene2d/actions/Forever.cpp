
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

#include "Forever.hpp"

using namespace gdx_cpp::scenes::scene2d::actions;

Forever& Forever::newObject () {
    return new Forever();
}

Forever& Forever::$ (const gdx_cpp::scenes::scene2d::Action& action) {
    Forever forever = pool.obtain();
    forever.action = action;
    return forever;
}

void Forever::setTarget (const gdx_cpp::scenes::scene2d::Actor& actor) {
    action.setTarget(actor);
    target = actor;
}

void Forever::act (float delta) {
    action.act(delta);
    if (action.isDone()) {
        Action oldAction = action;
        action = action.copy();
        oldAction.finish();
        action.setTarget(target);
    }
}

bool Forever::isDone () {
    return false;
}

void Forever::finish () {
    pool.free(this);
    action.finish();
    super.finish();
}

gdx_cpp::scenes::scene2d::Action& Forever::copy () {
    return $(action.copy());
}

gdx_cpp::scenes::scene2d::Actor& Forever::getTarget () {
    return target;
}

