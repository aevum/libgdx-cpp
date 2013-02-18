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
#include "AndroidSystem.hpp"
#include <string.h>

using namespace gdx::android;

jclass AndroidFileHandle::managerClass = nullptr;

AndroidFileHandle::AndroidFileHandle(const std::string& fileName, gdx::Files::FileType type)
    : FileHandle(fileName, type)
{
}

void AndroidFileHandle::bindClasses(JNIEnv* env)
{  
    managerClass =  reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/aevumlab/gdxcpp/ApplicationManager")));
    assert(managerClass);
}

int gdx::android::AndroidFileHandle::readBytes(gdx::FileHandle::buffer_ptr& c) const
{
    JNIEnv* env = static_cast<AndroidSystem*>(system)->getJniEnv();
    jstring strpath = env->NewStringUTF(this->file.getPath().c_str());
    
    jmethodID mid = env->GetStaticMethodID(managerClass, "readFile", "(Ljava/lang/String;I)[B");

    assert(mid);

    jbyteArray result = (jbyteArray) env->CallStaticObjectMethod(managerClass, mid, strpath, this->getType());
    jsize size = env->GetArrayLength(result);
    char* sbuffer = new char[size];
 
    env->GetByteArrayRegion(result, 0, size, (jbyte*) sbuffer);

    gdx::FileHandle::buffer_ptr swapable(sbuffer, shared_ptr_array_deleter());
    c.swap(swapable);

    return size;
}

bool AndroidFileHandle::exists() const
{
    JNIEnv* env = static_cast<AndroidSystem*>(system)->getJniEnv();
    jstring strpath = env->NewStringUTF(this->file.getPath().c_str());
    
    jmethodID mid = env->GetStaticMethodID(managerClass, "fileExists", "(Ljava/lang/String;I)Z");
    
    jboolean result = (jboolean) env->CallStaticBooleanMethod(managerClass, mid, strpath, this->getType());
    
    return result;
}

int AndroidFileHandle::write(const char* data, int length, bool append)
{
    gdx_log_debug("write", "1");
    JNIEnv* env = static_cast<AndroidSystem*>(system)->getJniEnv();
    gdx_log_debug("write", "2");
    jstring strpath = env->NewStringUTF(this->file.getPath().c_str());
    gdx_log_debug("write", "3");
    jmethodID mid = env->GetStaticMethodID(managerClass, "writeFile", "(Ljava/lang/String;[BZI)I");
    gdx_log_debug("write", "4");
    assert(mid);
    
    gdx_log_debug("write", "5");
    jbyteArray jbArray = env->NewByteArray(length);
    env->SetByteArrayRegion(jbArray, 0, length, (const jbyte*) data);
    
    gdx_log_debug("write", "6");
    jint result = env->CallStaticIntMethod(managerClass, mid, strpath, jbArray, append, this->getType());
    
    gdx_log_debug("write", "7");
    return result;    
}

