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


#ifndef GDX_CPP_IMPLEMENTATION_THREAD_HPP
#define GDX_CPP_IMPLEMENTATION_THREAD_HPP

#include "gdx-cpp/utils/Runnable.hpp"
#include "gdx-cpp/internal/memory"

#include <string>

namespace gdx {

class Thread : public std::enable_shared_from_this< Thread >
{
public:
    typedef ref_ptr_maker<Thread>::shared_ptr_t ptr;
    
    virtual void start() = 0;
    virtual void yield() = 0;
    virtual void sleep(long millis) = 0;
    virtual void join() = 0;
    
    virtual const std::string getThreadName() = 0;
    
    virtual ~Thread() { }
};

}

#endif // GDX_CPP_IMPLEMENTATION_THREAD_HPP
