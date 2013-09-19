/*
 *    Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *
 *    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *    @author Ozires Bortolon de Faria ozires@aevumlab.com
 */


#ifndef GDX_CPP_UTILS_RUNNABLE_HPP
#define GDX_CPP_UTILS_RUNNABLE_HPP

#include "gdx-cpp/internal/memory"
#include <functional>

class Runnable {
public:
    typedef ref_ptr_maker<Runnable>::shared_ptr_t ptr;
    
    virtual void run() = 0;
    virtual void onRunnableStop() = 0;
    
    virtual ~Runnable() { }
};

class RunnableFunctionExecutor : public Runnable {
public:
    RunnableFunctionExecutor(std::function< void() > func) : function(std::move(func)) { }
    virtual void onRunnableStop() override { }
    virtual void run() override { 
        function(); 
    }
private:
    std::function< void() > function;
};

#endif // GDX_CPP_UTILS_RUNNABLE_HPP