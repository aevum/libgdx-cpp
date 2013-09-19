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

class Runnable;

namespace gdx {

namespace nix {

class LinuxSystem  : public gdx::System
{
class LinuxThreadFactory : public gdx::ThreadFactory {
public: 
        Thread::ptr createThread(Runnable* t) override;
        Thread::ptr createThread(std::function< void() > func) override;
        
};

class LinuxMutexFactory : public gdx::MutexFactory {
public:
        Mutex::ptr createMutex() override;
};

public:
    uint64_t nanoTime() override;

    LinuxThreadFactory* getThreadFactory() override {
        return &threadFactory;
    }

    LinuxMutexFactory* getMutexFactory() override {
        return &mutexFactory;
    }
    std::string canonicalize(const std::string& path) override;
    void checkDelete(const std::string& path) override;
    void checkRead(const std::string& path) override;
    bool createDirectory(const gdx::File& f) override;
    bool deleteFile(File& f) override;
    int getBooleanAttributes(const gdx::File& f) override;
    std::string getDefaultParent() override;
    int64_t getLength(File f) override;
    char getPathSeparator() override;
    char getSeparator() override;
    bool isAbsolute(const gdx::File& f) override;
    void list(const gdx::File& f, std::vector< std::string > &paths) override;
    std::string normalize(const std::string &pathname, const int &len, const int &off);
    std::string normalize(const std::string &path) override;
    int prefixLength(const std::string& path) override;
    bool renameFile(File& f1, const gdx::File& f2) override;
    std::string resolve(const gdx::File& f) override;
    std::string resolve(const std::string& parent, const std::string& child) override;
    void checkWrite(const std::string& path) override;
    
private:
    LinuxThreadFactory threadFactory;
    LinuxMutexFactory mutexFactory;
};

}

}

#endif // GDX_CPP_BACKENDS_NIX_LINUXSYSTEM_HPP
