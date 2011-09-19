/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License")
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#include "LinuxOpenALAudio.hpp"
#include "LinuxOpenALAudioDevice.hpp"
#include "LinuxOpenALAudioRecorder.hpp"
#include "LinuxOpenALSound.hpp"
#include "LinuxOpenALMusic.hpp"
#include <AL/al.h>
#include <AL/alc.h>
#include "gdx-cpp/utils/Buffer.hpp"
#include <stdexcept>
#include "gdx-cpp/files/FileHandle.hpp"
#include <iostream>
#include "LinuxOgg.hpp"

using namespace gdx_cpp::backends::nix;

LinuxOpenALAudio::LinuxOpenALAudio (int simultaneousSources)
{
    createAl();

    for (int i = 0; i < simultaneousSources; i++) {
        ALuint sourceID;
        alGenSources(1 , & sourceID);
        if (alGetError() != AL_NO_ERROR) break;
        allSources.insert(sourceID);
    }
    idleSources = allSources;

    ALfloat orientation[] = {0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f};
    alListenerfv(AL_ORIENTATION, orientation);
    ALfloat velocity[] = {0.0f, 0.0f, 0.0f};
    alListenerfv(AL_VELOCITY, velocity);
    ALfloat position[] = {0.0f, 0.0f, 0.0f};
    alListenerfv(AL_POSITION, position);
}

void LinuxOpenALAudio::createAl() {
    device = alcOpenDevice(NULL);
    if (device == NULL) {
        throw std::runtime_error("Could not open ALC device");
    }

    context = alcCreateContext(device, NULL);

    alcMakeContextCurrent(context);
}

gdx_cpp::audio::Sound * LinuxOpenALAudio::newSound (const ref_ptr_maker< gdx_cpp::files::FileHandle >::type file) {
//     if (file == NULL) throw std::runtime_error("file cannot be null.");
    std::string extension = file->extension();
    if (extension == "ogg")
      return new LinuxOggSound(this, file);
    else {
      std::stringstream ss;
      ss << "Unknown file extension for sound: " << file->name();
      throw std::runtime_error(ss.str());
    }
}

gdx_cpp::audio::Music * LinuxOpenALAudio::newMusic (const ref_ptr_maker< gdx_cpp::files::FileHandle >::type file) {
    std::string extension = file->extension();
    if (extension == "ogg")
      return new LinuxOggMusic(this, file);
    else {
      std::stringstream ss;
      ss << "Unknown file extension for sound: " << file->name();
      throw std::runtime_error(ss.str());
    }
}

int LinuxOpenALAudio::obtainSource (bool isMusic) {
    std::set<int>::iterator sit = idleSources.begin();
    std::set<int>::iterator send = idleSources.end();
    for (; sit != send; sit++) {
        int sourceID = *sit;
        int state;
        alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING && state != AL_PAUSED) {
            if (isMusic) idleSources.erase(sit);
            alSourceStop(sourceID);
            alSourcei(sourceID, AL_BUFFER, 0);
            return sourceID;
        }
    }
    return -1;
}

void LinuxOpenALAudio::freeSource (int sourceID) {
    alSourceStop(sourceID);
    alSourcei(sourceID, AL_BUFFER, 0);
    idleSources.insert(sourceID);
}

void LinuxOpenALAudio::freeBuffer (int bufferID) {
    std::set<int>::iterator sit = idleSources.begin();
    std::set<int>::iterator send = idleSources.end();
    for (; sit != send; sit++) {
        int sourceID = *sit;
        int state;
        alGetSourcei(sourceID, AL_BUFFER, &state);
        if (state == bufferID) {
            alSourceStop(sourceID);
            alSourcei(sourceID, AL_BUFFER, 0);
        }
    }
}

void LinuxOpenALAudio::stopSourcesWithBuffer (int bufferID) {
    std::set<int>::iterator sit = idleSources.begin();
    std::set<int>::iterator send = idleSources.end();
    for (; sit != send; sit++) {
        int sourceID = *sit;int state;
        alGetSourcei(sourceID, AL_BUFFER, &state);
        if (state == bufferID) alSourceStop(sourceID);
    }
}

void LinuxOpenALAudio::update () {
    for (int i = 0; i < music.size(); i++)
        music[i]->update();
}

void LinuxOpenALAudio::dispose () {
    std::set<int>::iterator sit = idleSources.begin();
    std::set<int>::iterator send = idleSources.end();
    for (; sit != send; sit++) {
        ALuint sourceID = *sit;
        int state;
        alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
        if (state != AL_STOPPED) alSourceStop(sourceID);
        alDeleteSources(1, &sourceID);
    }

    if (context != NULL) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(context);
        context = NULL;
    }
    if (device != NULL) {
        bool result = alcCloseDevice(device);
        device = NULL;
    }
}

gdx_cpp::audio::AudioDevice* LinuxOpenALAudio::newAudioDevice (int samplingRate, bool isMono) {
    // BOZO - Write OpenAL device.
    return NULL;//new JavaSoundAudioDevice(samplingRate, isMono);
}

gdx_cpp::audio::AudioRecorder* LinuxOpenALAudio::newAudioRecoder (int samplingRate, bool isMono) {
    return NULL;//new JavaSoundAudioRecorder(samplingRate, isMono);
}
