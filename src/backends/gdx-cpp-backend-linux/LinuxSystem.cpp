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
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/dir.h>

#include <gdx-cpp/Log.hpp>

using namespace gdx::nix;

std::string LinuxSystem::canonicalize(const std::string& path)    
{
    char buffer[32768];
    if(realpath(path.c_str(), buffer) == NULL) gdx_log_error("gdx","Error trying to canonicalize path: %s", path.c_str());
    return std::string(buffer);
}

void LinuxSystem::checkDelete(const std::string& path)
{
    int found;
    std::string testPath = path;
    while(testPath != "")
    {
       if (access(testPath.c_str(), W_OK) == 0) return;
       found = testPath.rfind(getSeparator());
       if(found == testPath.npos) break;
       else testPath = testPath.substr(0, found);
    }
    gdx_log_error("gdx","Delete permission denied on file: %s", path.c_str());
}

void LinuxSystem::checkRead(const std::string& path)
{
    int found;
    std::string testPath = path;
    while(testPath != "")
    {
       if (access(testPath.c_str(), W_OK) == 0) return;
       found = testPath.rfind(getSeparator());
       if(found == testPath.npos) break;
       else testPath = testPath.substr(0, found);
    }
    gdx_log_error("gdx","Read permission denied on file: %s", path.c_str());
}

bool LinuxSystem::createDirectory(const gdx::File& f)
{
    if(mkdir(f.getAbsolutePath().c_str(), S_IWUSR | S_IRUSR) == -1) return false;
    return true;
}

bool LinuxSystem::deleteFile(gdx::File& f)
{
    std::string cmd;
    if(remove(f.getCanonicalPath().c_str()) == -1) return false;
    return true;
}

int LinuxSystem::getBooleanAttributes(const gdx::File& f)
{
    int attribs = 0;
    struct stat fileStat;
    std::string absPath = f.getAbsolutePath();
    
    if(stat(absPath.c_str(), &fileStat) == -1)
    {
        return attribs;
    }

    attribs = attribs | this->BA_EXISTS;

    if(S_ISREG(fileStat.st_mode))
    {
        attribs = attribs | this->BA_REGULAR;
    }
    else if(S_ISDIR(fileStat.st_mode))
    {
        attribs = attribs | this->BA_DIRECTORY;
    }
    int pos = 0;
    while(pos < absPath.length()-1)
    {
        if(absPath[pos] == '/' && absPath[pos+1] == '.')
        {
          attribs = attribs | this->BA_HIDDEN;
          break;
        }
        pos++;
    }
    return attribs;
}

std::string LinuxSystem::getDefaultParent()
{
    return "/";
}

int64_t LinuxSystem::getLength(gdx::File f)
{
    std::ifstream test(f.getPath().c_str(), std::ios::in| std::ios::binary | std::ios::ate);
    std::ifstream::pos_type size;
    size = test.tellg();
    test.close();
    return (int64_t) size;
}

char LinuxSystem::getPathSeparator()
{
    return ':';
}

char LinuxSystem::getSeparator()
{
    return '/';
}

bool LinuxSystem::isAbsolute(const gdx::File& f)
{
    return (f.getPrefixLength() != 0);
}

void LinuxSystem::list(const gdx::File& f, std::vector< std::string > &paths)
{
    paths.resize(0);
    if(!f.isDirectory()) return;
    int count;
    std::string fname;
    struct direct **files;
    count = scandir(f.getCanonicalPath().c_str(), &files, NULL, NULL);
    if(count == -1) gdx_log_error("gdx","Cannot retrieve fileList in directory %s", f.getCanonicalPath().c_str());
    for(int i=0;i<count; ++i)
    {
        fname = std::string(files[i]->d_name);
        if(fname != "." && fname != "..") paths.push_back(fname);
        free(files[i]);
    }
    free(files);
}

    /* A normal Unix pathname contains no duplicate slashes and does not end
       with a slash.  It may be the empty string. */

    /* Normalize the given pathname, whose length is len, starting at the given
       offset; everything before this offset is already normal. */
std::string LinuxSystem::normalize(const std::string &pathname, const int &len, const int &off)
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

    /* Check that the given pathname is normal.  If not, invoke the real
       normalizer on the part of the pathname that requires normalization.
       This way we iterate through the whole pathname string only once. */
std::string LinuxSystem::normalize(const std::string &path)
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

int LinuxSystem::prefixLength(const std::string& path)
{
    if(path.length() == 0) return 0;
    return (path[0] == '/') ? 1 : 0;
}

bool LinuxSystem::renameFile(gdx::File& f1, const gdx::File& f2)
{
    std::string to;
    if(f2.exists()) to = f2.getCanonicalPath();
    else to = f2.getAbsolutePath();
    if(rename(f1.getCanonicalPath().c_str(), to.c_str()) == -1) return false;
    return true;
}

std::string LinuxSystem::resolve(const gdx::File& f)
{
    if (isAbsolute(f)) return f.getPath();
    char buffer[2048];
    if(getcwd(buffer, 2048) == NULL) gdx_log_error("gdx","Error trying to resolve path: %s", f.getPath().c_str());
    return resolve(std::string(buffer), f.getPath());
}

std::string LinuxSystem::resolve(const std::string& parent, const std::string& child)
{
    std::string nparent = normalize(parent);
    std::string nchild = normalize(child);
    if(nparent[nparent.length()-1] == getSeparator()) return (nparent + nchild);
    return nparent + getSeparator() + nchild;
}

void LinuxSystem::checkWrite(const std::string& path)
{
     int found;
     std::string testPath = path;
     while(testPath != "")
     {
        if (access(testPath.c_str(), W_OK) == 0) return;
        found = testPath.rfind(getSeparator());
        if(found == testPath.npos) break;
        else testPath = testPath.substr(0, found);
     }
     gdx_log_error("gdx","Write permission denied on file: %s", path.c_str());
}

class LinuxMutex : public gdx::Mutex {
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
    ((Runnable*)runnable)->run();

    return NULL;
}

class LinuxThread : public gdx::Thread {
public:
    LinuxThread(Runnable* theRunnable)
        : runnable(theRunnable),
thread(0) {
    }
    
    const std::string getThreadName() {
        return "TODO";
    }

    void start() {
        if (pthread_create(&thread, NULL, run_runnable, (void*) runnable) != 0) {
            gdx_log_error("gdx","pthread_create failed");
        }
    }

    void join() {
        if( pthread_join(thread, NULL) != 0) {
            gdx_log_error("gdx","pthread_join failed");
        }
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

gdx::Thread::ptr gdx::nix::LinuxSystem::LinuxThreadFactory::createThread(Runnable* t)
{
    return gdx::Thread::ptr(new LinuxThread(t));
}

gdx::Mutex::ptr gdx::nix::LinuxSystem::LinuxMutexFactory::createMutex()
{
    return gdx::Mutex::ptr(new LinuxMutex);
}

uint64_t gdx::nix::LinuxSystem::nanoTime()
{
    static timespec ts;
    ::clock_gettime(CLOCK_MONOTONIC_COARSE, &ts);

    return (uint64_t)ts.tv_sec * 1000000000LL + (uint64_t)ts.tv_nsec;
}

