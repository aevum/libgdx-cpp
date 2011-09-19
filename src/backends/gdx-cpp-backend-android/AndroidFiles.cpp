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

using namespace gdx_cpp;
using namespace gdx_cpp::files;
using namespace gdx_cpp::backends::android;

Files::fhandle_ptr gdx_cpp::backends::android::AndroidFiles::absolute(const std::string& path)
{
    assert(mngr);
    return gdx_cpp::Files::fhandle_ptr(new AndroidFileHandle(mngr, path, gdx_cpp::Files::Absolute));
}

Files::fhandle_ptr gdx_cpp::backends::android::AndroidFiles::external(const std::string& path)
{
    assert(mngr);
    return gdx_cpp::Files::fhandle_ptr(new AndroidFileHandle(mngr, path, gdx_cpp::Files::External));
}

std::string& gdx_cpp::backends::android::AndroidFiles::getExternalStoragePath()
{
    return externalPath;
}

Files::fhandle_ptr gdx_cpp::backends::android::AndroidFiles::getFileHandle(const std::string& path, gdx_cpp::Files::FileType type)
{
    assert(mngr);
    return gdx_cpp::Files::fhandle_ptr(new AndroidFileHandle(mngr,path, type));
}

Files::fhandle_ptr gdx_cpp::backends::android::AndroidFiles::internal(const std::string& path)
{
    Gdx::app->log("AndroidFiles", "manager is %p, path is %s", mngr, path.c_str());
    assert(mngr);
    return gdx_cpp::Files::fhandle_ptr(new AndroidFileHandle(mngr, path, gdx_cpp::Files::Internal));
}

bool gdx_cpp::backends::android::AndroidFiles::isExternalStorageAvailable()
{
    //TODO
    return false;
}

void backends::android::AndroidFiles::setAndroidAssetManager(AAssetManager* mngr)
{
    this->mngr = mngr;
}

