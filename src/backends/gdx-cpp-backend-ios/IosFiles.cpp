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
 */

#include "IosFiles.hpp"
#include "IosFileHandle.hpp"

using namespace gdx::ios;

gdx::FileHandle::ptr IosFiles::getFileHandle (const std::string &fileName, gdx::Files::FileType type)
{
    return gdx::FileHandle::ptr(new IosFileHandle(fileName, type));
}

gdx::FileHandle::ptr IosFiles::internal (const std::string &path)
{
    return gdx::FileHandle::ptr(new IosFileHandle(path, gdx::Files::Internal));
}

gdx::FileHandle::ptr IosFiles::external (const std::string &path)
{
    return gdx::FileHandle::ptr(new IosFileHandle(path, gdx::Files::External));
}

gdx::FileHandle::ptr IosFiles::absolute (const std::string &path)
{
    return gdx::FileHandle::ptr(new IosFileHandle(path, gdx::Files::Absolute));
}

std::string IosFiles::getExternalStoragePath ()
{
    return "";
}

bool IosFiles::isExternalStorageAvailable ()
{
    return true;
}
