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

#include "LinuxFileHandle.hpp"
#include <cassert>
#include <sys/stat.h>

using namespace gdx_cpp::backends::nix;

LinuxFileHandle::LinuxFileHandle (const std::string &fileName, gdx_cpp::Files::FileType type)
  : FileHandle(fileName, type)
{
}

LinuxFileHandle::LinuxFileHandle (const gdx_cpp::files::File &file, gdx_cpp::Files::FileType type)
  : FileHandle(file, type)
{
}

int LinuxFileHandle::readBytes(gdx_cpp::files::FileHandle::buffer_ptr& c) const
{
    int buffer_length = length();
    char* buf = (char*) malloc(buffer_length);

    std::string filepath;
    if (type == gdx_cpp::Files::Internal && !file.exists()) {
        int found;
        filepath = "/" + file.getPath();
        
        while((found = filepath.find("//")) != filepath.npos)
            filepath.replace(found, 2, "/");
    } else {
        filepath = file.getPath();
    }

    FILE* f = fopen(filepath.c_str(), "r");

    assert(f);
    
    int position = 0;
    if (f) {
        
        int readed = 0;
        while ((readed = fread(buf + position, 1, buffer_length - position, f)) > 0)
        {
            position += readed;
        }

        fclose(f);
    }    
    
    buffer_ptr new_ptr = buffer_ptr(buf, shared_ptr_free_deleter());
    c.swap(new_ptr);
    return position;
}

int LinuxFileHandle::write(char* data, int lenght, bool append)
{
    return gdx_cpp::files::FileHandle::write(data, lenght, append);
}

void LinuxFileHandle::copyTo(gdx_cpp::files::FileHandle& dest)
{
    gdx_cpp::files::FileHandle::copyTo(dest);
}

int64_t LinuxFileHandle::length() const
{
    struct stat st;
    int res = stat(file.getPath().c_str(), &st);

    if (res) {

    }
    
    return st.st_size;
}


