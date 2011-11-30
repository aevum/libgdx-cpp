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

#include "AndroidFiles.hpp"

#include <gdx-cpp/files/FileHandle.hpp>
#include "AndroidFileHandle.hpp"
#include <cassert>
#include <gdx-cpp/Gdx.hpp>

using namespace gdx_cpp;
using namespace gdx_cpp::files;
using namespace gdx_cpp::backends::android;

AndroidFiles::AndroidFiles()
{
}

files::FileHandle::ptr gdx_cpp::backends::android::AndroidFiles::absolute(const std::string& path)
{
    return gdx_cpp::files::FileHandle::ptr(new AndroidFileHandle(path, gdx_cpp::Files::Absolute));
}

files::FileHandle::ptr gdx_cpp::backends::android::AndroidFiles::external(const std::string& path)
{
    return gdx_cpp::files::FileHandle::ptr(new AndroidFileHandle(path, gdx_cpp::Files::External));
}

std::string gdx_cpp::backends::android::AndroidFiles::getExternalStoragePath()
{
    return externalPath;
}

files::FileHandle::ptr gdx_cpp::backends::android::AndroidFiles::getFileHandle(const std::string& path, gdx_cpp::Files::FileType type)
{
    return gdx_cpp::files::FileHandle::ptr(new AndroidFileHandle(path, type));
}

files::FileHandle::ptr gdx_cpp::backends::android::AndroidFiles::internal(const std::string& path)
{   
    return gdx_cpp::files::FileHandle::ptr(new AndroidFileHandle(path, gdx_cpp::Files::Internal));
}

bool gdx_cpp::backends::android::AndroidFiles::isExternalStorageAvailable()
{
    //TODO
    return false;
}

