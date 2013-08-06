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

#include <unistd.h>

#include "EmscriptenFileHandle.hpp"
#include "EmscriptenFiles.hpp"
#include "gdx-cpp/files/FileHandle.hpp"

using namespace gdx::scripten;

gdx::FileHandle::ptr EmscriptenFiles::getFileHandle (const std::string &fileName, gdx::Files::FileType type)
{
    return gdx::FileHandle::ptr(new EmscriptenFileHandle(fileName, type));
}

gdx::FileHandle::ptr EmscriptenFiles::internal (const std::string &path)
{
    return gdx::FileHandle::ptr(new EmscriptenFileHandle(path, gdx::Files::Internal));
}

gdx::FileHandle::ptr EmscriptenFiles::external (const std::string &path)
{
    return gdx::FileHandle::ptr(new EmscriptenFileHandle(path, gdx::Files::External));
}

gdx::FileHandle::ptr EmscriptenFiles::absolute (const std::string &path)
{
    return gdx::FileHandle::ptr(new EmscriptenFileHandle(path, gdx::Files::Absolute));
}

std::string EmscriptenFiles::getExternalStoragePath ()
{
    if(externalPath != "") return externalPath;
    char buffer[36768];
    getcwd(buffer, 36768);
    externalPath = std::string(buffer) + "/";
    return externalPath;
}

bool EmscriptenFiles::isExternalStorageAvailable ()
{
    return true;
}

ref_ptr_maker< gdx::FileHandle >::shared_ptr_t EmscriptenFiles::internal_private(const std::string& path)
{
    return internal(path);
}
