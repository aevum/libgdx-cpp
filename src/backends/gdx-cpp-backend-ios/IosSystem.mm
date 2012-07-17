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

#include "IosSystem.hpp"
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
#include "gdx-cpp/Log.hpp"

#import <mach/mach.h>
#import <mach/mach_time.h>

#import <UIKit/UIKit.h>

using namespace gdx::ios;

std::string IosSystem::canonicalize(const std::string& path)    
{
    char buffer[32768];
    if(realpath(path.c_str(), buffer) == NULL) throw std::runtime_error("Error trying to canonicalize path: " + path);
    return std::string(buffer);
}

void IosSystem::checkDelete(const std::string& path)
{
    unsigned int found;
    std::string testPath = path;
    while(testPath != "")
    {
       if (access(testPath.c_str(), W_OK) == 0) return;
       found = testPath.rfind(getSeparator());
       if(found == testPath.npos) break;
       else testPath = testPath.substr(0, found);
    }
    throw std::runtime_error("Delete permission denied on file: " + path);
}

void IosSystem::checkRead(const std::string& path)
{
    unsigned int found;
    std::string testPath = path;
    while(testPath != "")
    {
       if (access(testPath.c_str(), W_OK) == 0) return;
       found = testPath.rfind(getSeparator());
       if(found == testPath.npos) break;
       else testPath = testPath.substr(0, found);
    }
    throw std::runtime_error("Read permission denied on file: " + path);
}

bool IosSystem::createDirectory(const gdx::File& f)
{
    if(mkdir(f.getAbsolutePath().c_str(), S_IWUSR | S_IRUSR) == -1) return false;
    return true;
}

bool IosSystem::deleteFile(gdx::File& f)
{
    std::string cmd;
    if(remove(f.getCanonicalPath().c_str()) == -1) return false;
    return true;
}

int IosSystem::getBooleanAttributes(const gdx::File& f)
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
    unsigned int pos = 0;
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

std::string IosSystem::getDefaultParent()
{
    return "/";
}

int64_t IosSystem::getLength(gdx::File f)
{
    std::ifstream test(f.getPath().c_str(), std::ios::in| std::ios::binary | std::ios::ate);
    std::ifstream::pos_type size;
    size = test.tellg();
    test.close();
    return (int64_t) size;
}

char IosSystem::getPathSeparator()
{
    return ':';
}

char IosSystem::getSeparator()
{
    return '/';
}

bool IosSystem::isAbsolute(const gdx::File& f)
{
    return (f.getPrefixLength() != 0);
}

void IosSystem::list(const gdx::File& f, std::vector< std::string > &paths)
{
    throw std::runtime_error("Not implemented");
}

std::string IosSystem::normalize(const std::string &pathname, const int &len, const int &off)
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
std::string IosSystem::normalize(const std::string &path)
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

int IosSystem::prefixLength(const std::string& path)
{
    if(path.length() == 0) return 0;
    return (path[0] == '/') ? 1 : 0;
}

bool IosSystem::renameFile(gdx::File& f1, const gdx::File& f2)
{
    std::string to;
    if(f2.exists()) to = f2.getCanonicalPath();
    else to = f2.getAbsolutePath();
    if(rename(f1.getCanonicalPath().c_str(), to.c_str()) == -1) return false;
    return true;
}

std::string IosSystem::resolve(const gdx::File& f)
{
    if (isAbsolute(f)) return f.getPath();
	NSString *filePath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String: f.getName().c_str()] ofType:[NSString stringWithUTF8String:f.extension().c_str()]];
	if (filePath != nil) {
		return std::string([filePath UTF8String], [filePath length]);
	}
	
    gdx_log_error("gdx", "File %s not found", f.getName().c_str());
	throw std::runtime_error("File " + f.getName() + " not found");
}

std::string IosSystem::resolve(const std::string& parent, const std::string& child)
{
    std::string nparent = normalize(parent);
    std::string nchild = normalize(child);
    if(nparent[nparent.length()-1] == getSeparator()) return (nparent + nchild);
    return nparent + getSeparator() + nchild;
}

void IosSystem::checkWrite(const std::string& path)
{
     unsigned int found;
     std::string testPath = path;
     while(testPath != "")
     {
        if (access(testPath.c_str(), W_OK) == 0) return;
        found = testPath.rfind(getSeparator());
        if(found == testPath.npos) break;
        else testPath = testPath.substr(0, found);
     }
     throw std::runtime_error("Write permission denied on file: " + path);
}

class IosMutex : public gdx::Mutex {
public:
    IosMutex()
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

class IosThread : public gdx::Thread {
public:
    IosThread(Runnable* theRunnable)
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

    virtual ~IosThread() {
        join();
        runnable->onRunnableStop();
    }    
    
private:
    Runnable* runnable;
    pthread_t thread;
};

gdx::Thread::ptr gdx::ios::IosSystem::IosThreadFactory::createThread(Runnable* t)
{
    return gdx::Thread::ptr(new IosThread(t));
}

gdx::Mutex::ptr gdx::ios::IosSystem::IosMutexFactory::createMutex()
{
    return gdx::Mutex::ptr(new IosMutex);
}

uint64_t gdx::ios::IosSystem::nanoTime()
{
	static struct mach_timebase_info timebase_info;
	mach_timebase_info(&timebase_info);
	
    uint64_t thisTimestamp = mach_absolute_time();

	thisTimestamp *= timebase_info.numer;
	thisTimestamp /= timebase_info.denom;
	
    return thisTimestamp;
}

