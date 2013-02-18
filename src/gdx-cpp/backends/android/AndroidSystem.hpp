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

#ifndef GDX_CPP_BACKENDS_NIX_LINUXSYSTEM_HPP
#define GDX_CPP_BACKENDS_NIX_LINUXSYSTEM_HPP

#include <gdx-cpp/implementation/System.hpp>
#include <gdx-cpp/implementation/ThreadFactory.hpp>
#include <jni.h>

class Runnable;

namespace gdx {

namespace android {

class AndroidSystem  : public gdx::System
{
class AndroidThreadFactory : public gdx::ThreadFactory {
public: 
        Thread::ptr createThread(Runnable* t);
        Thread::ptr createThread(std::function< void() > func);
};

class AndroidMutexFactory : public gdx::MutexFactory {
public:
        Mutex::ptr createMutex();
};

public:
    uint64_t nanoTime();

    AndroidSystem();

    AndroidThreadFactory* getThreadFactory() {
        return &threadFactory;
    }

    AndroidMutexFactory* getMutexFactory() {
        return &mutexFactory;
    }

    std::string canonicalize(const std::string& path);
    void checkDelete(const std::string& path);
    void checkRead(const std::string& path);
    void checkWrite(const std::string& path);
    bool createDirectory(const gdx::File& f);
    bool deleteFile(File& f);
    int getBooleanAttributes(const gdx::File& f);
    std::string getDefaultParent();
    int64_t getLength(File f);
    char getPathSeparator();
    char getSeparator();
    bool isAbsolute(const gdx::File& f);
    void list(const gdx::File& f, std::vector< std::string >& paths);
    std::string normalize(const std::string& path);
    std::string normalize(const std::string &pathname, const int &len, const int &off);
    int prefixLength(const std::string& path);
    bool renameFile(File& f1, const gdx::File& f2);
    std::string resolve(const std::string& parent, const std::string& child);
    std::string resolve(const gdx::File& f);

    void setJavaVM(JavaVM* vm);
    
    JavaVM* const getJavaVM();
    JNIEnv* getJniEnv();
    
private:
    AndroidThreadFactory threadFactory;
    AndroidMutexFactory mutexFactory;

    JavaVM* vm;
};

}

}

#endif // GDX_CPP_BACKENDS_NIX_LINUXSYSTEM_HPP
