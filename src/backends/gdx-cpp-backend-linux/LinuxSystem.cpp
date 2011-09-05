/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 *  @author aevum team
 */

#include "LinuxSystem.hpp"
#include "gdx-cpp/utils/Runnable.hpp"

#include <time.h>
#include <pthread.h>
#include <stdexcept>
#include <iostream>

using namespace gdx_cpp::backends::nix;

std::string LinuxSystem::canonicalize(std::string& path)
{

}

void LinuxSystem::checkDelete(const std::string& path)
{

}

void LinuxSystem::checkRead(const std::string& path)
{

}

bool LinuxSystem::createDirectory(const gdx_cpp::files::File& f)
{

}

bool LinuxSystem::deleteFile(gdx_cpp::files::File& f)
{

}

int LinuxSystem::getBooleanAttributes(const gdx_cpp::files::File& f)
{

}

std::string LinuxSystem::getDefaultParent()
{

}

int64_t LinuxSystem::getLength(gdx_cpp::files::File f)
{

}

char LinuxSystem::getPathSeparator()
{

}

char LinuxSystem::getSeparator()
{

}

bool LinuxSystem::isAbsolute(const gdx_cpp::files::File& f)
{

}

void LinuxSystem::list(const gdx_cpp::files::File& f, const std::vector< std::string > paths)
{

}

std::string LinuxSystem::normalize(const std::string& path)
{

}

int LinuxSystem::prefixLength(const std::string& path)
{

}

bool LinuxSystem::rename(gdx_cpp::files::File& f1, const gdx_cpp::files::File& f2)
{

}

std::string LinuxSystem::resolve(const gdx_cpp::files::File& f)
{

}

std::string LinuxSystem::resolve(const std::string& parent, const std::string& child)
{

}

void LinuxSystem::checkWrite(const std::string& path)
{

}

class LinuxMutex : public gdx_cpp::implementation::Mutex {
public:
    LinuxMutex()
    {
        pthread_mutex_init(&mutex, NULL);
    }
    
    void lock(){
        pthread_mutex_lock(&mutex);
    }

   void unlock() {
       pthread_mutex_unlock(&mutex);
   }

protected:
    pthread_mutex_t mutex;
};

void* run_runnable(void* runnable) {
    std::cout << "chamou runnable" << std::endl;
    ((Runnable*)runnable)->run();

    return NULL;
}

class LinuxThread : public gdx_cpp::implementation::Thread {
public:
    LinuxThread(Runnable* theRunnable)
        : runnable(theRunnable)
        , thread(0) {
    }
    
    const std::string getThreadName() {
        return "TODO";
    }

    void start() {
        if (pthread_create(&thread, NULL, run_runnable, (void*) runnable) != 0) {
            throw std::runtime_error("pthread_create failed");
        }
    }

    void join() {
        std::cout << "antes do join" << std::endl;
        if( pthread_join(thread, NULL) != 0) {
            throw std::runtime_error("pthread_join failed");
        }
        std::cout << "depois do join" << std::endl;
    }

    void sleep(long int millis) {
        usleep(millis * 1000);
    }

    void yield() {
        pthread_yield();
    }

    virtual ~LinuxThread() {
        join();
        runnable->onRunnableStop();
    }    
    
private:
    Runnable* runnable;
    pthread_t thread;
};

gdx_cpp::implementation::Thread::ptr gdx_cpp::backends::nix::LinuxSystem::LinuxThreadFactory::createThread(Runnable* t)
{
    return gdx_cpp::implementation::Thread::ptr(new LinuxThread(t));
}

gdx_cpp::implementation::Mutex::ptr gdx_cpp::backends::nix::LinuxSystem::LinuxMutexFactory::createMutex()
{
    return gdx_cpp::implementation::Mutex::ptr(new LinuxMutex);
}

int64_t gdx_cpp::backends::nix::LinuxSystem::nanoTime()
{
    timespec ts;
    ::clock_gettime(CLOCK_REALTIME, &ts);

    return ts.tv_sec * 1000000000 + ts.tv_nsec;
}

