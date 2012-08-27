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


#include "IosOpenALMusic.hpp"
#include "IosOpenALAudio.hpp"
#include <gdx-cpp/files/FileHandle.hpp>


#include <OpenAL/al.h>
#include <stdexcept>


#define GDX_IOS_OPENALMUSIC_BUFFER_SIZE 40960.0f
#define GDX_IOS_OPENALMUSIC_BUFFER_COUNT 1
#define GDX_IOS_OPENALMUSIC_BYTES_PER_SAMPLE 2.0f

using namespace gdx::ios;


IosOpenALMusic::IosOpenALMusic(IosOpenALAudio * _audio, int channels, void* buffer, int length, int _sampleRate) :
audio(_audio),
musicBuffer(buffer),
bufferLength(length),
sourceID(-1),
sampleRate(_sampleRate),
isLoopingVar(false),
isPlayingVar(false),
volume(1),
renderedSeconds(0),
secondsPerBuffer(0),
alBuffer(0)
{
    audio->music.push_back(this);
    
    sourceID = audio->obtainSource(true);
        
    this->format = channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
    
    CHECK_OPENAL_ERROR(alGenBuffers(GDX_IOS_OPENALMUSIC_BUFFER_COUNT, &alBuffer));
    
    CHECK_OPENAL_ERROR(alSourcei(sourceID, AL_LOOPING, AL_FALSE));
    
    CHECK_OPENAL_ERROR(alSourcef(sourceID, AL_GAIN, volume));   
    
    CHECK_OPENAL_ERROR(alBufferData(alBuffer, format, musicBuffer, bufferLength, sampleRate));
    
    CHECK_OPENAL_ERROR(alSourceQueueBuffers(sourceID, 1, &alBuffer));
}

void IosOpenALMusic::play ()
{
    CHECK_OPENAL_ERROR(alSourcePlay(sourceID));
    isPlayingVar = true;
    
}

void IosOpenALMusic::pause ()
{
    if (sourceID != -1) CHECK_OPENAL_ERROR(alSourcePause(sourceID));
    isPlayingVar = false;
}

void IosOpenALMusic::stop ()
{
    CHECK_OPENAL_ERROR(alSourceStop(sourceID));
    renderedSeconds = 0;
    isPlayingVar = false; 
}

bool IosOpenALMusic::isPlaying ()
{
    return sourceID != -1 && isPlayingVar;
}

void IosOpenALMusic::setLooping (bool isLooping)
{
    isLoopingVar = isLooping;
    if (sourceID != -1) {
        CHECK_OPENAL_ERROR(alSourcei(sourceID, AL_LOOPING, isLooping ? AL_TRUE : AL_FALSE));
    }
}

bool IosOpenALMusic::isLooping ()
{
    return isLoopingVar;
}

void IosOpenALMusic::setVolume (float volume)
{
    this->volume = volume;
    if (sourceID != -1) CHECK_OPENAL_ERROR(alSourcef(sourceID, AL_GAIN, volume));
}

float IosOpenALMusic::getPosition ()
{
    if (sourceID == -1) return 0;
    ALfloat value;
    alGetSourcef(sourceID, AL_SEC_OFFSET, &value);
    return renderedSeconds + value;
}

void IosOpenALMusic::dispose ()
{   
    if (alBuffer == 0) return;
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
    
    CHECK_OPENAL_ERROR(alDeleteBuffers(GDX_IOS_OPENALMUSIC_BUFFER_COUNT, &alBuffer));
}

void IosOpenALMusic::reset() {
    
}

void IosOpenALMusic::update()
{
    if (sourceID == -1) return;
    
    bool end = false;
    int buffers;
    CHECK_OPENAL_ERROR(alGetSourcei(sourceID, AL_BUFFERS_PROCESSED, &buffers));
    while (buffers-- > 0) {
        unsigned bufferID;
        (alSourceUnqueueBuffers(sourceID, 1, &bufferID));
        if (bufferID == AL_INVALID_VALUE) break;
        renderedSeconds += secondsPerBuffer;
        if (end) continue;
        
        
        CHECK_OPENAL_ERROR(alBufferData(bufferID, format, musicBuffer, bufferLength, sampleRate));
        CHECK_OPENAL_ERROR(alSourceQueueBuffers(sourceID, 1, &bufferID));
    }

    int abq;
    CHECK_OPENAL_ERROR(alGetSourcei(sourceID, AL_BUFFERS_QUEUED, &abq));
    if (end && abq == 0) stop();
    
    // A buffer underflow will cause the source to stop.
    int ss;
    CHECK_OPENAL_ERROR(alGetSourcei(sourceID, AL_SOURCE_STATE, &ss));
    if (isPlayingVar && ss != AL_PLAYING) CHECK_OPENAL_ERROR(alSourcePlay(sourceID));
}
