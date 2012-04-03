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
#include <gdx-cpp/Gdx.hpp>
#include <cassert>
#include <jni.h>
#include "AndroidSystem.hpp"
#include <string.h>

using namespace gdx_cpp::backends::android;

AndroidFileHandle::AndroidFileHandle(const std::string& fileName, gdx_cpp::Files::FileType type)
    : FileHandle(fileName, type)
{
}

int gdx_cpp::backends::android::AndroidFileHandle::readBytes(gdx_cpp::files::FileHandle::buffer_ptr& c) const
{
    JNIEnv* env = static_cast<AndroidSystem*>(Gdx::system)->getJniEnv();
    jstring strpath = env->NewStringUTF(this->file.getPath().c_str());

    jclass managerClass = env->FindClass("com/aevumlab/gdxcpp/ApplicationManager");

    assert(managerClass);
    
    jmethodID mid = env->GetStaticMethodID(managerClass, "readFile", "(Ljava/lang/String;I)[B");

    assert(mid);

    jbyteArray result = (jbyteArray) env->CallStaticObjectMethod(managerClass, mid, strpath, this->getType());

    jbyte* buffer = env->GetByteArrayElements(result, NULL);
    jsize size = env->GetArrayLength(result);

    assert(buffer);
    assert(size);
    
    char* sbuffer = new char[size];
    memcpy(sbuffer, buffer, size);

    gdx_cpp::files::FileHandle::buffer_ptr swapable(sbuffer, shared_ptr_array_deleter());
    c.swap(swapable);

    return size;
}

