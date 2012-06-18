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

#include "AndroidSound.hpp"
#include "AndroidSystem.hpp"
#include <gdx-cpp/Gdx.hpp>
#include <cassert>

using namespace gdx_cpp::backends::android;

gdx_cpp::backends::android::AndroidSound::AndroidSound( jobject p_jniSound )
 : jniSound(p_jniSound)
{
    
    JNIEnv* env = static_cast<gdx_cpp::backends::android::AndroidSystem*>(gdx_cpp::Gdx::system)->getJniEnv();
    jclass cls = env->GetObjectClass(p_jniSound);
    
    disposeJNI = env->GetMethodID(cls, "dispose", "()V");
    playJNI = env->GetMethodID(cls, "play", "()V");
    playFloatJNI = env->GetMethodID(cls, "play", "(F)V");
    stopJNI = env->GetMethodID(cls, "stop", "()V");
    
    assert(disposeJNI);
    assert(playJNI);
    assert(playFloatJNI);
    assert(stopJNI);
}

void gdx_cpp::backends::android::AndroidSound::dispose()
{
    JNIEnv* env = static_cast<gdx_cpp::backends::android::AndroidSystem*>(gdx_cpp::Gdx::system)->getJniEnv();
    env->CallVoidMethod(jniSound, disposeJNI);
    env->DeleteGlobalRef(jniSound);
}

void gdx_cpp::backends::android::AndroidSound::play()
{
    JNIEnv* env = static_cast<gdx_cpp::backends::android::AndroidSystem*>(gdx_cpp::Gdx::system)->getJniEnv();
    env->CallVoidMethod(jniSound, playJNI);
}

void gdx_cpp::backends::android::AndroidSound::play(float volume)
{
    JNIEnv* env = static_cast<gdx_cpp::backends::android::AndroidSystem*>(gdx_cpp::Gdx::system)->getJniEnv();
    env->CallVoidMethod(jniSound, playFloatJNI, volume);
}

void gdx_cpp::backends::android::AndroidSound::stop()
{
    JNIEnv* env = static_cast<gdx_cpp::backends::android::AndroidSystem*>(gdx_cpp::Gdx::system)->getJniEnv();
    env->CallVoidMethod(jniSound, stopJNI);
}

gdx_cpp::backends::android::AndroidSound::~AndroidSound()
{
    dispose();
}

