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

namespace gdx_cpp {

namespace backends {

namespace nix {

class LinuxSystem  : public gdx_cpp::implementation::System
{
class LinuxThreadFactory : public gdx_cpp::implementation::ThreadFactory {
public: 
        implementation::Thread::ptr createThread(Runnable* t);
};

class LinuxMutexFactory : public gdx_cpp::implementation::MutexFactory {
public:
        implementation::Mutex::ptr createMutex();
};

public:
    uint64_t nanoTime();

    LinuxThreadFactory* getThreadFactory() {
        return &threadFactory;
    }

    LinuxMutexFactory* getMutexFactory() {
        return &mutexFactory;
    }
    std::string canonicalize(const std::string& path);
    void checkDelete(const std::string& path);
    void checkRead(const std::string& path);
    bool createDirectory(const gdx_cpp::files::File& f);
    bool deleteFile(files::File& f);
    int getBooleanAttributes(const gdx_cpp::files::File& f);
    std::string getDefaultParent();
    int64_t getLength(files::File f);
    char getPathSeparator();
    char getSeparator();
    bool isAbsolute(const gdx_cpp::files::File& f);
    bool list(const gdx_cpp::files::File& f, std::vector< std::string > &paths);
    std::string normalize(const std::string &pathname, const int &len, const int &off);
    std::string normalize(const std::string &path);
    int prefixLength(const std::string& path);
    bool renameFile(files::File& f1, const gdx_cpp::files::File& f2);
    std::string resolve(const gdx_cpp::files::File& f);
    std::string resolve(const std::string& parent, const std::string& child);
    void checkWrite(const std::string& path);
    
private:
    LinuxThreadFactory threadFactory;
    LinuxMutexFactory mutexFactory;
};

}

}

}

#endif // GDX_CPP_BACKENDS_NIX_LINUXSYSTEM_HPP
