/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#include "LinuxOpenALSound.hpp"
#include "gdx-cpp/files/FileHandle.hpp"
#include "AL/al.h"
#include "LinuxOpenALAudio.hpp"
#include "gdx-cpp/utils/Buffer.hpp"

using namespace gdx::nix;

class LinuxOpenALAudio;

LinuxOpenALSound::LinuxOpenALSound(LinuxOpenALAudio * _audio) : bufferID(-1),
audio(_audio)
{

}

void LinuxOpenALSound::setup (char* buffer, int size, int channels, int sampleRate) {
    if (bufferID == -1) {
        alGenBuffers(1, &bufferID);
    }
    alBufferData(bufferID, channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, buffer, size, sampleRate);
    
}

void LinuxOpenALSound::play () {
    play(1);
}

void LinuxOpenALSound::play (float volume) {
    int sourceID = audio->obtainSource(false);
    if (sourceID == -1) return;
    alSourcei(sourceID, AL_BUFFER, bufferID);
    alSourcei(sourceID, AL_LOOPING, AL_FALSE);
    alSourcef(sourceID, AL_GAIN, volume);
    alSourcePlay(sourceID);    
}

void LinuxOpenALSound::loop () {
    int sourceID = audio->obtainSource(false);
    if (sourceID == -1) return;
    alSourcei(sourceID, AL_BUFFER, bufferID);
    alSourcei(sourceID, AL_LOOPING, AL_TRUE);
    alSourcePlay(sourceID);
}

void LinuxOpenALSound::stop () {
    audio->stopSourcesWithBuffer(bufferID);
}

void LinuxOpenALSound::dispose () {
    if (bufferID == -1) return;
    audio->freeBuffer(bufferID);
    alDeleteBuffers(1, &bufferID);
    bufferID = -1;
}
