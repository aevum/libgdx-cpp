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

#include "AndroidFileHandle.hpp"
#include <cassert>

using namespace gdx_cpp::backends::android;

AndroidFileHandle::AndroidFileHandle(AAssetManager* mngr, const std::string& fileName, gdx_cpp::Files::FileType type)
    : FileHandle(fileName, type)
    , manager(mngr)
{
}

int gdx_cpp::backends::android::AndroidFileHandle::readBytes(gdx_cpp::files::FileHandle::char_ptr& c)
{
    AAsset* asset = AAssetManager_open(this->manager, this->file.getPath().c_str(), AASSET_MODE_UNKNOWN);

    assert(asset);

    off_t start, length;
    int fd = AAsset_openFileDescriptor(asset, &start, &length);
    
    assert(0 <= fd);
    
    off_t bufferSize = AAsset_getLength(asset);
    char* buffer = new char[bufferSize];

    int numBytesRead = AAsset_read(asset, buffer, bufferSize); 

    char_ptr new_ptr = char_ptr(buffer, shared_ptr_array_deleter());
    c.swap(new_ptr);
    
    AAsset_close(asset);

    return numBytesRead;
}

