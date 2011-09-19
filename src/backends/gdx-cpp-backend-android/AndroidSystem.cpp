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

#include "AndroidSystem.hpp"
#include "gdx-cpp/utils/Runnable.hpp"

#include <time.h>
#include <pthread.h>
#include <stdexcept>
#include <iostream>
#include <stdint.h>
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/Application.hpp>

#include <android/log.h>

using namespace gdx_cpp::backends::android;

class AndroidMutex : public gdx_cpp::implementation::Mutex {
public:
    AndroidMutex()
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
    ((Runnable*)runnable)->run();

    return NULL;
}

class AndroidThread : public gdx_cpp::implementation::Thread {
public:
    AndroidThread(Runnable* theRunnable)
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
        sleep(0);
    }

    virtual ~AndroidThread() {
        join();
        runnable->onRunnableStop();
    }    
    
private:
    Runnable* runnable;
    pthread_t thread;
};

gdx_cpp::implementation::Thread::ptr gdx_cpp::backends::android::AndroidSystem::AndroidThreadFactory::createThread(Runnable* t)
{
    return gdx_cpp::implementation::Thread::ptr(new AndroidThread(t));
}

gdx_cpp::implementation::Mutex::ptr gdx_cpp::backends::android::AndroidSystem::AndroidMutexFactory::createMutex()
{
    return gdx_cpp::implementation::Mutex::ptr(new AndroidMutex);
}

uint64_t gdx_cpp::backends::android::AndroidSystem::nanoTime()
{
    static timespec ts;
    ::clock_gettime(CLOCK_MONOTONIC, &ts);

//     __android_log_print(ANDROID_LOG_DEBUG, "nanoTime", "tv_sec: %llu, tv_usec: %llu, %llu", ts.tv_sec, ts.tv_nsec, (uint64_t)ts.tv_sec * 1000000000LL + (uint64_t)ts.tv_nsec);
    
    return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

std::string gdx_cpp::backends::android::AndroidSystem::canonicalize(const std::string& path)
{

}

void gdx_cpp::backends::android::AndroidSystem::checkDelete(const std::string& path)
{

}

void gdx_cpp::backends::android::AndroidSystem::checkRead(const std::string& path)
{

}

void gdx_cpp::backends::android::AndroidSystem::checkWrite(const std::string& path)
{

}

bool gdx_cpp::backends::android::AndroidSystem::createDirectory(const gdx_cpp::files::File& f)
{

}

bool gdx_cpp::backends::android::AndroidSystem::deleteFile(gdx_cpp::files::File& f)
{

}

int gdx_cpp::backends::android::AndroidSystem::getBooleanAttributes(const gdx_cpp::files::File& f)
{

}

std::string gdx_cpp::backends::android::AndroidSystem::getDefaultParent()
{

}

int64_t gdx_cpp::backends::android::AndroidSystem::getLength(gdx_cpp::files::File f)
{

}

char gdx_cpp::backends::android::AndroidSystem::getPathSeparator()
{
    return ':';
}

char gdx_cpp::backends::android::AndroidSystem::getSeparator()
{
    return '/';
}

bool gdx_cpp::backends::android::AndroidSystem::isAbsolute(const gdx_cpp::files::File& f)
{

}

bool gdx_cpp::backends::android::AndroidSystem::list(const gdx_cpp::files::File& f, std::vector< std::string >& paths)
{

}

std::string gdx_cpp::backends::android::AndroidSystem::normalize(const std::string& path)
{
    int n = path.length();
    std::string pathname = path;
    char prevChar = 0;
    for (int i = 0; i < n; i++) {
        char c = pathname[i];
        if ((prevChar == '/') && (c == '/'))
            return normalize(pathname, n, i - 1);
        prevChar = c;
    }
    if (prevChar == '/') return normalize(pathname, n, n - 1);
             return pathname;
}

std::string gdx_cpp::backends::android::AndroidSystem::normalize(const std::string& pathname, const int& len, const int& off)
{
    if (len == 0) return pathname;
    int n = len;
    while ((n > 0) && (pathname[n - 1] == '/')) n--;
           if (n == 0) return "/";
           std::string sb = "";
    if (off > 0) sb.append(pathname.substr(0, off));
           char prevChar = 0;
    for (int i = off; i < n; i++) {
        char c = pathname[i];
        if ((prevChar == '/') && (c == '/')) continue;
           sb.append(1, c);
        prevChar = c;
    }
    return sb;
}

int gdx_cpp::backends::android::AndroidSystem::prefixLength(const std::string& path)
{
    if(path.length() == 0) return 0;
    return (path[0] == '/') ? 1 : 0;
}

bool gdx_cpp::backends::android::AndroidSystem::renameFile(gdx_cpp::files::File& f1, const gdx_cpp::files::File& f2)
{

}

std::string gdx_cpp::backends::android::AndroidSystem::resolve(const std::string& parent, const std::string& child)
{

}

std::string gdx_cpp::backends::android::AndroidSystem::resolve(const gdx_cpp::files::File& f)
{

}
