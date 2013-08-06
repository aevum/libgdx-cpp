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


#include "AL/al.h"
#include "EmscriptenOpenALAudio.hpp"
#include "EmscriptenOpenALSound.hpp"

using namespace gdx::scripten;

EmscriptenOpenALSound::EmscriptenOpenALSound(EmscriptenOpenALAudio * _audio) : bufferID(-1),
audio(_audio)
{

}

void EmscriptenOpenALSound::setup (char* buffer, int size, int channels, int sampleRate) {
    if (bufferID == (uint) -1) {
        alGenBuffers(1, &bufferID);
    }
    alBufferData(bufferID, channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, buffer, size, sampleRate);
    
}

void EmscriptenOpenALSound::play () {
    play(1);
}

void EmscriptenOpenALSound::play (float volume) {
    int sourceID = audio->obtainSource(false);
    if (sourceID == -1) return;
    alSourcei(sourceID, AL_BUFFER, bufferID);
    alSourcei(sourceID, AL_LOOPING, AL_FALSE);
    alSourcef(sourceID, AL_GAIN, volume);
    alSourcePlay(sourceID);    
}

void EmscriptenOpenALSound::loop () {
    int sourceID = audio->obtainSource(false);
    if (sourceID == -1) return;
    alSourcei(sourceID, AL_BUFFER, bufferID);
    alSourcei(sourceID, AL_LOOPING, AL_TRUE);
    alSourcePlay(sourceID);
}

void EmscriptenOpenALSound::stop () {
    audio->stopSourcesWithBuffer(bufferID);
}

void EmscriptenOpenALSound::dispose () {
    if (bufferID == (uint)-1) return;
    audio->freeBuffer(bufferID);
    alDeleteBuffers(1, &bufferID);
    bufferID = -1;
}
