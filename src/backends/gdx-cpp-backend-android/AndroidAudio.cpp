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

#include "AndroidAudio.hpp"
#include <gdx-cpp/audio/AudioDevice.hpp>
#include <gdx-cpp/audio/AudioRecorder.hpp>
#include <gdx-cpp/audio/Sound.hpp>
#include <gdx-cpp/audio/Music.hpp>
#include <cassert>
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/files/FileHandle.hpp>
#include "AndroidSound.hpp"
#include "AndroidMusic.hpp"
#include <stdexcept>

using namespace gdx_cpp::backends::android;


gdx_cpp::backends::android::AndroidAudio::AndroidAudio()
: env(NULL)
{    
}

gdx_cpp::audio::AudioDevice* gdx_cpp::backends::android::AndroidAudio::newAudioDevice(int samplingRate, bool isMono)
{
}

gdx_cpp::audio::AudioRecorder* gdx_cpp::backends::android::AndroidAudio::newAudioRecoder(int samplingRate, bool isMono)
{
}

gdx_cpp::audio::Music* gdx_cpp::backends::android::AndroidAudio::newMusic(const gdx_cpp::files::FileHandle::ptr file)
{
    jstring strpath = env->NewStringUTF(file->path().c_str());
    jobject jobjMusic = env->CallObjectMethod(androidAudioObj, newMusicJNI, strpath, Files::Internal);

    if (jobjMusic != NULL) {
        jobjMusic = env->NewGlobalRef(jobjMusic);

        return new AndroidMusic(env, jobjMusic);
    }
    
    throw std::runtime_error("Could not load file: " + file->path());
}

gdx_cpp::audio::Sound* gdx_cpp::backends::android::AndroidAudio::newSound(const gdx_cpp::files::FileHandle::ptr fileHandle)
{
    jstring strpath = env->NewStringUTF(fileHandle->path().c_str());
    jobject jobjSound = env->CallObjectMethod(androidAudioObj, newSoundJNI, strpath, Files::Internal);

    if (jobjSound != NULL) {
        jobjSound = env->NewGlobalRef(jobjSound);

        return new AndroidSound(env, jobjSound);
    }

    throw std::runtime_error("Could not load file: " + fileHandle->path());
}

void gdx_cpp::backends::android::AndroidAudio::setupJNI(JNIEnv* env, jobject androidAudioObj)
{
    this->env = env;
    this->androidAudioObj = androidAudioObj;
    env->NewGlobalRef(androidAudioObj);

    jclass cls = env->GetObjectClass(androidAudioObj);

    newAudioDeviceJNI = env->GetMethodID(cls, "newAudioDevice", "(IZ)Lcom/badlogic/gdx/audio/AudioDevice;");
    newAudioRecoderJNI = env->GetMethodID(cls, "newAudioRecoder", "(IZ)Lcom/badlogic/gdx/audio/AudioRecorder;");
    newSoundJNI = env->GetMethodID(cls, "newSound", "(Ljava/lang/String;I)Lcom/badlogic/gdx/audio/Sound;");
    newMusicJNI = env->GetMethodID(cls, "newMusic", "(Ljava/lang/String;I)Lcom/badlogic/gdx/audio/Music;");

    assert(newAudioDeviceJNI);
    assert(newAudioRecoderJNI);
    assert(newSoundJNI);
    assert(newMusicJNI);
}

gdx_cpp::backends::android::AndroidAudio::~AndroidAudio()
{
    env->DeleteGlobalRef(androidAudioObj);
}

