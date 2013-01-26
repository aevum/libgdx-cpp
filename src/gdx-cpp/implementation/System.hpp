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


#ifndef GDX_CPP_IMPLEMENTATION_SYSTEM_HPP
#define GDX_CPP_IMPLEMENTATION_SYSTEM_HPP

#include <gdx-cpp/files/File.hpp>
#include <stdint.h>
#include <sys/types.h>
#include <string>
#include <vector>

#include "MutexFactory.hpp"
#include "ThreadFactory.hpp"

namespace gdx {

class MutexFactory;
class ThreadFactory;

class System
{
public:

  /* -- Attribute accessors -- */

    /* Constants for simple boolean attributes */
    static const int BA_EXISTS;
    static const int BA_REGULAR;
    static const int BA_DIRECTORY;
    static const int BA_HIDDEN;

    virtual int getBooleanAttributes(const File &f) = 0;

    static const int ACCESS_READ;
    static const int ACCESS_WRITE;
    static const int ACCESS_EXECUTE;

    virtual char getSeparator() = 0;
    virtual char getPathSeparator() = 0;
    virtual std::string resolve(const std::string &parent, const std::string &child) = 0;
    virtual std::string normalize(const std::string &path) = 0;
    virtual int prefixLength(const std::string &path) = 0;
    virtual std::string getDefaultParent() = 0;
    virtual bool isAbsolute(const File &f) = 0;
    virtual std::string resolve(const File &f) = 0;
    virtual std::string canonicalize(const std::string &path) = 0; //throws IOException;
    virtual void checkRead(const std::string &path) = 0;
    virtual void list(const File &f, std::vector<std::string> &paths) = 0;
    virtual int64_t getLength(File f) = 0;
    virtual void checkDelete(const std::string &path) = 0;
    virtual bool deleteFile(File &f) = 0;
    virtual void checkWrite(const std::string &path) = 0;   
    virtual bool createDirectory(const File &f) = 0;
    virtual bool renameFile(File &f1, const File &f2) = 0;
    virtual uint64_t nanoTime() = 0;
    virtual MutexFactory* getMutexFactory() = 0;
    virtual ThreadFactory* getThreadFactory() = 0;
    virtual ~System() { }
};

}

#endif // GDX_CPP_IMPLEMENTATION_SYSTEM_HPP
