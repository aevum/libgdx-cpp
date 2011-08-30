/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#include "LinuxGraphics.hpp"

#include "LinuxGL10.hpp"
#include "LinuxGL11.hpp"
#include "LinuxGL20.hpp"
#include "LinuxGLU.hpp"

using namespace gdx_cpp::backends::nix;

gdx_cpp::backends::nix::LinuxGraphics::LinuxGraphics() :
gl10(new LinuxGL10)
,gl11(new LinuxGL11)
,gl20(new LinuxGL20)
,glu(new LinuxGLU)
{
}

gdx_cpp::graphics::GL10* gdx_cpp::backends::nix::LinuxGraphics::getGL10()
{
    return gl10;
}

gdx_cpp::graphics::GL11* gdx_cpp::backends::nix::LinuxGraphics::getGL11()
{
    return gl11;
}

gdx_cpp::graphics::GL20* gdx_cpp::backends::nix::LinuxGraphics::getGL20()
{
    return gl20;
}

gdx_cpp::graphics::GLU* gdx_cpp::backends::nix::LinuxGraphics::getGLU()
{
    return glu;
}


