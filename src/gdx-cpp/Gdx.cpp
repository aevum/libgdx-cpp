
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

#include "Gdx.hpp"

using namespace gdx_cpp;

Application* Gdx::app = 0;
Graphics* Gdx::graphics = 0;
Audio* Gdx::audio = 0;
Input* Gdx::input = 0;
Files* Gdx::files = 0;
graphics::GLCommon* Gdx::gl = 0;
graphics::GL10* Gdx::gl10 = 0;
graphics::GL11* Gdx::gl11 = 0;
graphics::GL20* Gdx::gl20 = 0;
graphics::GLU* Gdx::glu = 0;
implementation::ThreadFactory* threadFactory = 0;
implementation::MutexFactory* mutexFactory = 0;