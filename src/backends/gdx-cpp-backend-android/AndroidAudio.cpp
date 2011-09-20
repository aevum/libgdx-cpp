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

gdx_cpp::audio::Music* gdx_cpp::backends::android::AndroidAudio::newMusic(const gdx_cpp::Files::fhandle_ptr file)
{
}

gdx_cpp::audio::Sound* gdx_cpp::backends::android::AndroidAudio::newSound(const gdx_cpp::Files::fhandle_ptr fileHandle)
{
}

void gdx_cpp::backends::android::AndroidAudio::setupJNI(JNIEnv* env, jobject& androidAudioObj)
{
    Gdx::app->log("AndroidAudio", "setupJNI: env is %p, object is %p", env, androidAudioObj);
    
    this->env = env;
    this->androidAudioObj = androidAudioObj;

    jclass cls = env->GetObjectClass(androidAudioObj);

    Gdx::app->log("AndroidAudio", "setupJNI: cls is %p", cls);

    newAudioDeviceJNI = env->GetMethodID(cls, "newAudioDevice", "(IZ)Lcom/badlogic/gdx/audio/AudioDevice;");
    newAudioRecoderJNI = env->GetMethodID(cls, "newAudioRecoder", "(IZ)Lcom/badlogic/gdx/audio/AudioRecorder;");
    newSoundJNI = env->GetMethodID(cls, "newSound", "(Ljava/lang/String;I)Lcom/badlogic/gdx/audio/Sound;");
    newMusicJNI = env->GetMethodID(cls, "newMusic", "(Ljava/lang/String;I)Lcom/badlogic/gdx/audio/Music;");

    Gdx::app->log("AndroidAudio", "setupJNI: newAudioDeviceJNI %d, "
                                  "newAudioRecorderJNI %d, newSoundJNI %d, newMusicJNI %d",
                  newAudioDeviceJNI, newAudioRecoderJNI, newSoundJNI, newMusicJNI );
    
    assert(newAudioDeviceJNI);
    assert(newAudioRecoderJNI);
    assert(newSoundJNI);
    assert(newMusicJNI);
}
