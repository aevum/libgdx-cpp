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


#include <AL/al.h>
#include <gdx-cpp/Log.hpp>
#include <stddef.h>
#include <vector>

#include "LinuxOpenALAudio.hpp"
#include "LinuxOpenALMusic.hpp"
#include "backends/gdx-cpp-backend-linux/LinuxOpenALMusic.hpp"

using namespace gdx::nix;

char LinuxOpenALMusic::tempBytes[bufferSize];

LinuxOpenALMusic::LinuxOpenALMusic(LinuxOpenALAudio * _audio, ref_ptr_maker< gdx::FileHandle >::shared_ptr_t _file) :
        file(_file),
audio(_audio),
sourceID(-1),
format(0),
sampleRate(0),
isLoopingVar(false),
isPlayingVar(false),
isPausedVar(false),
volume(1),
renderedSeconds(0),
secondsPerBuffer(0)
{
    audio->music.push_back(this);
}

void LinuxOpenALMusic::setup (int _channels, int _sampleRate)
{
    sourceID = audio->obtainSource(true);
    
    this->sampleRate = _sampleRate;
    this->format = _channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;

    CHECK_OPENAL_ERROR(alGenBuffers(bufferCount, buffers));    
    CHECK_OPENAL_ERROR(alSourcei(sourceID, AL_LOOPING, AL_FALSE));    
    CHECK_OPENAL_ERROR(alSourcef(sourceID, AL_GAIN, volume));
            
    reset();

    int i;
    for (i = 0; i < bufferCount; ++i) {
        if (!fill(buffers[i])) {
            break;
        }            
    }
    
    CHECK_OPENAL_ERROR(alSourceQueueBuffers(sourceID, i, buffers));
}

void LinuxOpenALMusic::play ()
{
    CHECK_OPENAL_ERROR(alSourcePlay(sourceID));
    isPlayingVar = true;
    isPausedVar = false;
}

void LinuxOpenALMusic::pause ()
{
    if (sourceID != -1) {
        CHECK_OPENAL_ERROR(alSourcePause(sourceID));
        isPausedVar = true;
    }
    
}
void LinuxOpenALMusic::stop ()
{
    CHECK_OPENAL_ERROR(alSourceStop(sourceID));
    renderedSeconds = 0;
    isPlayingVar = false;
}

bool LinuxOpenALMusic::isPlaying ()
{
    return sourceID != -1 && isPlayingVar;
}

bool LinuxOpenALMusic::isPaused()
{
    return isPausedVar;
}


void LinuxOpenALMusic::setLooping (bool isLooping)
{
    isLoopingVar = isLooping;
    if (sourceID != -1) {
        CHECK_OPENAL_ERROR(alSourcei(sourceID, AL_LOOPING, isLooping ? AL_TRUE : AL_FALSE));
    }
}
bool LinuxOpenALMusic::isLooping ()
{
    return isLoopingVar;
}
void LinuxOpenALMusic::setVolume (float volume)
{
    this->volume = volume;
    if (sourceID != -1) CHECK_OPENAL_ERROR(alSourcef(sourceID, AL_GAIN, volume));
}
float LinuxOpenALMusic::getPosition ()
{
    if (sourceID == -1) return 0;
    ALfloat value;
    alGetSourcef(sourceID, AL_SEC_OFFSET, &value);
    return renderedSeconds + value;
}
void LinuxOpenALMusic::dispose ()
{    
    if (buffers == NULL) return;
    if (sourceID != -1) {
        reset();
        unsigned length = audio->music.size();
        for (unsigned i= 0; i < length ; i++ )
        {
            if (audio->music[i] == this)
            {
                audio->music.erase(audio->music.begin() + i);
                break;
            }
        }
        audio->freeSource(sourceID);
        sourceID = -1;
    }
    
    CHECK_OPENAL_ERROR(alDeleteBuffers(bufferCount, buffers));
}
void LinuxOpenALMusic::update()
{
    if (sourceID == -1 || !isPlayingVar || isPausedVar) return;
  
    //we query for processed buffers
    int processed = 0;
    CHECK_OPENAL_ERROR(alGetSourcei(sourceID, AL_BUFFERS_PROCESSED, &processed));

    //and unqueue them
    while (processed-- > 0) {
        unsigned bufferID;
        CHECK_OPENAL_ERROR(alSourceUnqueueBuffers(sourceID, 1, &bufferID));
        if (bufferID == AL_INVALID_VALUE) break;        
        
        //then request for more bytes
        if (!fill(bufferID)) {
            break;
        }
        
        CHECK_OPENAL_ERROR(alSourceQueueBuffers(sourceID, 1, (const ALuint*) &bufferID));
    }

     // if we do not have queued buffers anymore, then we can safely exit
    ALint queued = 0;
    CHECK_OPENAL_ERROR(alGetSourcei(sourceID, AL_BUFFERS_QUEUED, &queued));
    if (queued == 0) {
        stop();
    }

    // A buffer underflow will cause the source to stop.
    int ss;
    CHECK_OPENAL_ERROR(alGetSourcei(sourceID, AL_SOURCE_STATE, &ss));
    if (isPlayingVar && ss != AL_PLAYING) CHECK_OPENAL_ERROR(alSourcePlay(sourceID));
}

bool LinuxOpenALMusic::fill (int bufferID) {
    int length = this->read(tempBytes, bufferSize);
    if (length <= 0) {
        if (isLoopingVar) {
            reset();
            renderedSeconds = 0;
            length = this->read(tempBytes, bufferSize);
            if (length <= 0) return false;
        } else
            return false;
    }
    
    CHECK_OPENAL_ERROR(alBufferData(bufferID, format, tempBytes, length, sampleRate));
    return true;
}
