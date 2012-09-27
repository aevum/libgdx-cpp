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
 */

#ifndef GDX_CPP_UTILS_SYNCHRONIZED_HPP
#define GDX_CPP_UTILS_SYNCHRONIZED_HPP

#include "LockGuard.hpp"
#include "gdx-cpp/implementation/Mutex.hpp"
#include "gdx-cpp/implementation/MutexFactory.hpp"
#include "gdx-cpp/internal/memory"

class Mutex;
class Mutex;
template <typename Object, typename MutexType>
class synchronized {
    typedef lock_guard<MutexType> lock_type;
    typedef typename ref_ptr_maker<Object>::shared_ptr_t obj_ptr;
public:
    synchronized(obj_ptr obj, MutexType& mutex) :
        ref_object(obj), lock(mutex)
    {
    }

    synchronized(const synchronized<Object, MutexType>& other) :
        ref_object(other.ref_object), lock(other.lock.getMutex())
    {        
    }
    synchronized(const Object& obj, MutexType& mutex) :
    ref_object(new Object(obj)), lock(mutex)
    {
    }

    Object* operator ->() {
        //OMG proxy rules!
        return ref_object;
    }

    Object& operator *() {
        return *ref_object.get();
    }
    
protected:
    obj_ptr ref_object;
    lock_type lock;
};

template <typename T>
struct gdx_sync {
    typedef synchronized<T, gdx::Mutex> type;
};

template <typename MutexFactory>
struct Synchronizable {
    typedef lock_guard<typename MutexFactory::mutex_t> lock_holder;
    
    Synchronizable(MutexFactory* const fact) :
        mutex(fact->createMutex())
    {        
    }
    
    template <typename T>
    synchronized<T, typename MutexFactory::mutex_t> synchronize(T& obj) {
        return synchronized<T, typename MutexFactory::mutex_t>(obj, *mutex);
    }

    lock_holder synchronize() {
        return lock_holder(*mutex);
    }
    
    virtual ~Synchronizable() { }

private:
    typename MutexFactory::mutex_ptr mutex;
};

namespace gdx {
    
typedef Synchronizable<MutexFactory> Synchronizable;

}
#endif
class Mutex;
