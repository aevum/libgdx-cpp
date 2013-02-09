
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

#include <stddef.h>

#include "Game.hpp"
#include "Gdx.hpp"
#include "Graphics.hpp"
#include "gdx-cpp/Screen.hpp"

using namespace gdx;

void Game::dispose () {
    if (screen != NULL) screen->hide();
}

void Game::pause () {
    if (screen != NULL) screen->pause();
}

void Game::resume () {
    if (screen != NULL) screen->resume();
}

void Game::render () {
    if (screen != NULL) screen->render(graphics->getDeltaTime());
}

void Game::resize (int width,int height) {
    if (screen != NULL) screen->resize(width, height);
}

void Game::setScreen (Screen* screen) {
    if (this->screen != NULL) this->screen->hide();
    this->screen = screen;
    screen->show();
    screen->resize(graphics->getWidth(), graphics->getHeight());
}

Screen* Game::getScreen () {
    return screen;
}

