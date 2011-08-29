
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

#include "InputMultiplexer.hpp"
#include "InputProcessor.hpp"

using namespace gdx_cpp;

InputMultiplexer::InputMultiplexer()
 : processors(4)
{
}

void InputMultiplexer::addProcessor (InputProcessor* processor) {
    processors.push_back(processor);
}

void InputMultiplexer::removeProcessor (InputProcessor* processor) {
    processors.push_back(processor);
}

bool InputMultiplexer::keyDown (int keycode) {
    for (int i = 0, n = processors.size(); i < n; i++)
        if (processors[i]->keyDown(keycode)) return true;
    return false;
}

bool InputMultiplexer::keyUp (int keycode) {
    for (int i = 0, n = processors.size(); i < n; i++)
        if (processors[i]->keyUp(keycode)) return true;
    return false;
}

bool InputMultiplexer::keyTyped (char character) {
    for (int i = 0, n = processors.size(); i < n; i++)
        if (processors[i]->keyTyped(character)) return true;
    return false;
}

bool InputMultiplexer::touchDown (int x,int y,int pointer,int button) {
    for (int i = 0, n = processors.size(); i < n; i++)
        if (processors[i]->touchDown(x, y, pointer, button)) return true;
    return false;
}

bool InputMultiplexer::touchUp (int x,int y,int pointer,int button) {
    for (int i = 0, n = processors.size(); i < n; i++)
        if (processors[i]->touchUp(x, y, pointer, button)) return true;
    return false;
}

bool InputMultiplexer::touchDragged (int x,int y,int pointer) {
    for (int i = 0, n = processors.size(); i < n; i++)
        if (processors[i]->touchDragged(x, y, pointer)) return true;
    return false;
}

bool InputMultiplexer::touchMoved (int x,int y) {
    for (int i = 0, n = processors.size(); i < n; i++)
        if (processors[i]->touchMoved(x, y)) return true;
    return false;
}

bool InputMultiplexer::scrolled (int amount) {
    for (int i = 0, n = processors.size(); i < n; i++)
        if (processors[i]->scrolled(amount)) return true;
    return false;
}

