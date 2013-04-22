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

#include <gdx-cpp/Gdx.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <cassert>

#include "LinuxFileHandle.hpp"
#include "gdx-cpp/files/FileHandle.hpp"

using namespace gdx::nix;

LinuxFileHandle::LinuxFileHandle (const std::string &fileName, gdx::Files::FileType type)
    : FileHandle(fileName, type)
{
}

LinuxFileHandle::LinuxFileHandle (const gdx::File &file, gdx::Files::FileType type)
    : FileHandle(file, type)
{
}

int LinuxFileHandle::readBytes(gdx::FileHandle::buffer_ptr& c) const
{
    int buffer_length = length();
    char* buf = (char*) malloc(buffer_length);

    std::string filepath;
    if (type == gdx::Files::Internal && !file.exists()) {
        unsigned found;
        filepath = "/" + file.getPath();

        while((found = filepath.find("//")) != filepath.npos)
            filepath.replace(found, 2, "/");
    } else {
        filepath = file.getPath();
    }

    FILE* f = fopen(filepath.c_str(), "r");

    if (f == NULL) {
        gdx_log_error("gdx","File not found: %s", path().c_str());
    }

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

int LinuxFileHandle::write(const char* data, int length, bool append)
{
    FILE* f = fopen(file.getPath().c_str(), append ? "a" : "w");

    if (f == NULL) {
        gdx_log_error("gdx","File not found: %s", path().c_str());
    }

    int written =fwrite(data, 1, length, f);
    fclose(f);

    assert(written == length);

    return written;
}

void LinuxFileHandle::copyTo(gdx::FileHandle& dest)
{
    gdx::FileHandle::copyTo(dest);
}

int64_t LinuxFileHandle::length() const
{
    struct stat st;
    int res = stat(file.getPath().c_str(), &st);

    if (res) {

    }

    return st.st_size;
}


