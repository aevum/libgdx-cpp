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


#ifndef GDX_CPP_IMPLEMENTATION_MUTEXFACTORY_HPP
#define GDX_CPP_IMPLEMENTATION_MUTEXFACTORY_HPP

#include "Mutex.hpp"

namespace gdx {

class MutexFactory
{
public:
    typedef Mutex::ptr mutex_ptr;
    typedef Mutex mutex_t;
    virtual Mutex::ptr createMutex() = 0;
    
    virtual ~MutexFactory() { }
};

}

#endif // GDX_CPP_IMPLEMENTATION_MUTEXFACTORY_HPP
