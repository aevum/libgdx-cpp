
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

#include "FPSLogger.hpp"

#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/Graphics.hpp"
#include "gdx-cpp/Application.hpp"
#include "gdx-cpp/implementation/System.hpp"

using namespace gdx_cpp::graphics;

void FPSLogger::log () {
    if (gdx_cpp::Gdx::system->nanoTime() - startTime > 1000000000) {
        gdx_cpp::Gdx::app->log("FPSLogger") << "fps: " + gdx_cpp::Gdx::graphics->getFramesPerSecond();
        startTime = gdx_cpp::Gdx::system->nanoTime();
    }
}

gdx_cpp::graphics::FPSLogger::FPSLogger() : startTime(gdx_cpp::Gdx::system->nanoTime())
{
}

