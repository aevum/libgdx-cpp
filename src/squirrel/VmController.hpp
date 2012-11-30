/*
    Copyright 2012 aevum softwares aevum@aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
    
    @author Victor Vicente de Carvalho
*/


#ifndef GDX_VMCONTROLLER_HPP
#define GDX_VMCONTROLLER_HPP

#include <squirrel.h>
#include <string>
#include <sqrat/sqratTable.h>
#include <sqrat/sqratScript.h>
#include <sqrat/sqratFunction.h>
#include <sqrat/sqratTable.h>
#include <sqrat/sqratClass.h>

namespace gdx {

class VmController
{
public:
    VmController();
    virtual ~VmController();

    void loadScript(const std::string& script);

    Sqrat::Function getFunction(const std::string& functionName);

    HSQUIRRELVM getVm();
    Sqrat::Table getObjectMapTable();

    template<typename T>
    void setFunctionParam(const std::string& functionName, int funcId, const std::string& paramName, T param)
    {
        funcSetFunctionParam.Execute<const std::string&, int, const std::string&, T>( functionName, funcId, paramName, param );
    }
    
    template<typename T>
    T getFunctionParam(std::string& functionName, int funcId, std::string& paramName)
    {
        funcGetFunctionParam.Evaluate<T, const std::string&, int, const std::string&>( functionName, funcId, paramName);
    }

private:
    HSQUIRRELVM vm;
    Sqrat::Table objectMapTable;
    Sqrat::Table functionInstanceMapTable;
    Sqrat::Function funcSetFunctionParam;
    Sqrat::Function funcGetFunctionParam;
};

}

#endif // GDX_VMCONTROLLER_HPP
