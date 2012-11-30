/*
    Copyright 2012 <copyright holder> <email>

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


#include "VmController.hpp"


using namespace gdx;

VmController::VmController()
:
    vm(sq_open(1024)), objectMapTable(Sqrat::Table(vm)),
    functionInstanceMapTable(Sqrat::Table(vm))
{
    Sqrat::RootTable(vm).Bind("gdx_object_map", objectMapTable);
    Sqrat::RootTable(vm).Bind("gdx_function_instance_map", functionInstanceMapTable);
}

HSQUIRRELVM VmController::getVm()
{
    return this->vm;
}

void VmController::loadScript(const std::string& script)
{
    Sqrat::Script script1(vm);
    script1.CompileString(script);
    script1.Run();
}

VmController::~VmController()
{
}


