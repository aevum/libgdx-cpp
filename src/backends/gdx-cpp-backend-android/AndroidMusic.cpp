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

#include "AndroidMusic.hpp"
#include "AndroidSystem.hpp"
#include <cassert>
#include <gdx-cpp/Gdx.hpp>

using namespace gdx::android;


gdx::android::AndroidMusic::AndroidMusic(jobject musicObj)
    : jniMusicObj(musicObj)
    , disposeJNI(NULL)
    , getPositionJNI(NULL)
    , isLoopingJNI(NULL)
    , isPlayingJNI(NULL)
    , pauseJNI(NULL)
    , playJNI(NULL)
    , setLoopingJNI(NULL)
    , setVolumeJNI(NULL)
    , stopJNI(NULL)
{ 
    
    JNIEnv* env = static_cast<gdx::android::AndroidSystem*>(gdx::system)->getJniEnv();
    jclass cls = env->GetObjectClass(jniMusicObj);

    disposeJNI = env->GetMethodID(cls, "dispose", "()V");
    playJNI = env->GetMethodID(cls, "play", "()V");
    stopJNI = env->GetMethodID(cls, "stop", "()V");
    isLoopingJNI = env->GetMethodID(cls, "isLooping", "()Z");
    isPlayingJNI = env->GetMethodID(cls, "isPlaying", "()Z");
    isPausedJNI = env->GetMethodID(cls, "isPaused", "()Z");
    setLoopingJNI = env->GetMethodID(cls, "setLooping", "(Z)V");
    setVolumeJNI = env->GetMethodID(cls, "setVolume", "(F)V");
    getPositionJNI = env->GetMethodID(cls, "getPosition", "()F");
    pauseJNI = env->GetMethodID(cls, "pause", "()V");
    
    assert(disposeJNI);
    assert(getPositionJNI);
    assert(isLoopingJNI);
    assert(isPlayingJNI);
    assert(isPausedJNI);
    assert(pauseJNI);
    assert(playJNI);
    assert(setLoopingJNI);
    assert(setVolumeJNI);
    assert(stopJNI);
}

void gdx::android::AndroidMusic::dispose()
{
    JNIEnv* env = static_cast<gdx::android::AndroidSystem*>(gdx::system)->getJniEnv();
    env->CallVoidMethod(jniMusicObj, disposeJNI);
    env->DeleteGlobalRef(jniMusicObj);
}

float gdx::android::AndroidMusic::getPosition()
{
    JNIEnv* env = static_cast<gdx::android::AndroidSystem*>(gdx::system)->getJniEnv();
    return env->CallFloatMethod(jniMusicObj, getPositionJNI);
}

bool gdx::android::AndroidMusic::isLooping()
{
    JNIEnv* env = static_cast<gdx::android::AndroidSystem*>(gdx::system)->getJniEnv();
    return env->CallBooleanMethod(jniMusicObj, isLoopingJNI);
}

bool gdx::android::AndroidMusic::isPlaying()
{
    JNIEnv* env = static_cast<gdx::android::AndroidSystem*>(gdx::system)->getJniEnv();
    return env->CallBooleanMethod(jniMusicObj, isPlayingJNI);
}

bool AndroidMusic::isPaused()
{
    JNIEnv* env = static_cast<gdx::android::AndroidSystem*>(gdx::system)->getJniEnv();
    return env->CallBooleanMethod(jniMusicObj, isPausedJNI);
}


void gdx::android::AndroidMusic::pause()
{
    JNIEnv* env = static_cast<gdx::android::AndroidSystem*>(gdx::system)->getJniEnv();
    env->CallVoidMethod(jniMusicObj, pauseJNI);
}

void gdx::android::AndroidMusic::play()
{
    JNIEnv* env = static_cast<gdx::android::AndroidSystem*>(gdx::system)->getJniEnv();
    env->CallVoidMethod(jniMusicObj, playJNI);
}

void gdx::android::AndroidMusic::setLooping(bool isLooping)
{
    JNIEnv* env = static_cast<gdx::android::AndroidSystem*>(gdx::system)->getJniEnv();
    env->CallVoidMethod(jniMusicObj, setLoopingJNI, isLooping);
}

void gdx::android::AndroidMusic::setVolume(float volume)
{
    JNIEnv* env = static_cast<gdx::android::AndroidSystem*>(gdx::system)->getJniEnv();
    env->CallVoidMethod(jniMusicObj, setVolumeJNI, volume);
}

void gdx::android::AndroidMusic::stop()
{
    JNIEnv* env = static_cast<gdx::android::AndroidSystem*>(gdx::system)->getJniEnv();
    env->CallVoidMethod(jniMusicObj, stopJNI);
}

gdx::android::AndroidMusic::~AndroidMusic()
{
    dispose();
}



