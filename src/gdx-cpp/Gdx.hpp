
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

#ifndef GDX_CPP_GDX_HPP_
#define GDX_CPP_GDX_HPP_

#include <string>

#include "Application.hpp"
#include "Audio.hpp"
#include "Files.hpp"
#include "Graphics.hpp"
#include "Input.hpp"
#include "Log.hpp"
#include "backend.hpp"
#include "implementation/System.hpp"

namespace gdx {

class GL10;
class GL11;
class GL20;
class GLCommon;
class GLU;
class System;
class Application;
class Audio;
class Files;
class Graphics;
class Input;
class Log;

extern Application* app;
extern Graphics* graphics;
extern Audio* audio;
extern Input* input;
extern Files* files; 
extern GLCommon* gl;
extern GL10* gl10;
extern GL11* gl11;
extern GL20* gl20;
extern GLU* glu;

extern System* system;

void initializeSystem(System* system, Log* log);
void initialize(Application* application, Graphics* graphics,
                        Audio* audio, Input* input, Files* files);

void internal_log_error(const std::string& tag, const std::string& line, const std::string& file, const char* format, ...);
void internal_log_info(const std::string& tag, const std::string& line, const std::string& file, const char* format, ...);
void internal_log_debug(const std::string& tag, const std::string& line, const std::string& file,const char* format, ...);

} // namespace gdx

#endif // GDX_CPP_GDX_HPP_
