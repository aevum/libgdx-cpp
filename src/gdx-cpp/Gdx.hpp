
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

#ifndef GDX_CPP__GDX_HPP_
#define GDX_CPP__GDX_HPP_

namespace gdx_cpp {

class Application;
class Graphics;
class Audio;
class Input;
class Files;

namespace graphics {
    class GLCommon;
    class GL10;
    class GL11;
    class GL20;
    class GLU;
}

namespace implementation {
    class System;
    class ThreadFactory;
    class MutexFactory;
}

class Gdx {
public:
    static Application* app;
    static Graphics* graphics;
    static Audio* audio;
    static Input* input;
    static Files* files;
    static graphics::GLCommon* gl;
    static graphics::GL10* gl10;
    static graphics::GL11* gl11;
    static graphics::GL20* gl20;
    static graphics::GLU* glu;

    static implementation::System* system;

    static void initializeSystem(implementation::System* system);
    static void initialize(Application* application, Graphics* graphics,
                           Audio* audio, Input* input, Files* files);
};

} // namespace gdx_cpp

#endif // GDX_CPP__GDX_HPP_
