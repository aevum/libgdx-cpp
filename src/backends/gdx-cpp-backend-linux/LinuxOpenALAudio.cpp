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


#include <AL/al.h>
#include <AL/alc.h>
#include <stddef.h>
#include <memory>
#include <string>

#include "LinuxOgg.hpp"
#include "LinuxOpenALAudio.hpp"
#include "LinuxOpenALMusic.hpp"
#include "gdx-cpp/Log.hpp"
#include "gdx-cpp/files/FileHandle.hpp"

namespace gdx {
class AudioDevice;
class AudioRecorder;
}  // namespace gdx

using namespace gdx::nix;

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
    CHECK_OPENAL_ERROR(alListenerfv(AL_ORIENTATION, orientation));
    ALfloat velocity[] = {0.0f, 0.0f, 0.0f};
    CHECK_OPENAL_ERROR(alListenerfv(AL_VELOCITY, velocity));
    ALfloat position[] = {0.0f, 0.0f, 0.0f};
    CHECK_OPENAL_ERROR(alListenerfv(AL_POSITION, position));
}

void LinuxOpenALAudio::createAl() {
    device = alcOpenDevice(NULL);
    if (device == NULL) {
        gdx_log_error("gdx","Could not open ALC device");
    }

    context = alcCreateContext(device, NULL);

    CHECK_OPENAL_ERROR(alcMakeContextCurrent(context));
}

gdx::Sound * LinuxOpenALAudio::newSound (const ref_ptr_maker< gdx::FileHandle >::shared_ptr_t file) {
//     if (file == NULL) gdx_log_error("gdx","file cannot be null.");
    std::string extension = file->extension();
    if (extension == "ogg")
      return new LinuxOggSound(this, file);
    else {
      gdx_log_error("gdx", "Unknown file extension for sound: ", file->name().c_str());
    }
}

gdx::Music * LinuxOpenALAudio::newMusic (const ref_ptr_maker< gdx::FileHandle >::shared_ptr_t file) {
    std::string extension = file->extension();
    if (extension == "ogg")
      return new LinuxOggMusic(this, file);
    else {
      gdx_log_error("gdx","Unknown file extension for sound: %s", file->name().c_str());
    }
}

int LinuxOpenALAudio::obtainSource (bool isMusic) {
    std::set<int>::iterator sit = idleSources.begin();
    std::set<int>::iterator send = idleSources.end();
    for (; sit != send; sit++) {
        int sourceID = *sit;
        int state;
        CHECK_OPENAL_ERROR(alGetSourcei(sourceID, AL_SOURCE_STATE, &state));
        if (state != AL_PLAYING && state != AL_PAUSED) {
            if (isMusic) idleSources.erase(sit);
            CHECK_OPENAL_ERROR(alSourceStop(sourceID));
            CHECK_OPENAL_ERROR(alSourcei(sourceID, AL_BUFFER, 0));
            return sourceID;
        }
    }
    return -1;
}

void LinuxOpenALAudio::freeSource (int sourceID) {
    CHECK_OPENAL_ERROR(alSourceStop(sourceID));
    CHECK_OPENAL_ERROR(alSourcei(sourceID, AL_BUFFER, 0));
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

gdx::AudioDevice* LinuxOpenALAudio::newAudioDevice (int samplingRate, bool isMono) {
    // BOZO - Write OpenAL device.
    return NULL;//new JavaSoundAudioDevice(samplingRate, isMono);
}

gdx::AudioRecorder* LinuxOpenALAudio::newAudioRecoder (int samplingRate, bool isMono) {
    return NULL;//new JavaSoundAudioRecorder(samplingRate, isMono);
}
