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

#include "LinuxFiles.hpp"
#include "LinuxFileHandle.hpp"

using namespace gdx_cpp::backends::nix;

gdx_cpp::files::FileHandle::ptr LinuxFiles::getFileHandle (const std::string &fileName, gdx_cpp::Files::FileType type)
{
    return gdx_cpp::files::FileHandle::ptr(new LinuxFileHandle(fileName, type));
}

gdx_cpp::files::FileHandle::ptr LinuxFiles::internal (const std::string &path)
{
    return gdx_cpp::files::FileHandle::ptr(new LinuxFileHandle(path, gdx_cpp::Files::Internal));
}

gdx_cpp::files::FileHandle::ptr LinuxFiles::external (const std::string &path)
{
    return gdx_cpp::files::FileHandle::ptr(new LinuxFileHandle(path, gdx_cpp::Files::External));
}

gdx_cpp::files::FileHandle::ptr LinuxFiles::absolute (const std::string &path)
{
    return gdx_cpp::files::FileHandle::ptr(new LinuxFileHandle(path, gdx_cpp::Files::Absolute));
}

std::string LinuxFiles::getExternalStoragePath ()
{
    if(externalPath != "") return externalPath;
    char buffer[36768];
    getcwd(buffer, 36768);
    externalPath = std::string(buffer) + "/";
    return externalPath;
}

bool LinuxFiles::isExternalStorageAvailable ()
{
    return true;
}
