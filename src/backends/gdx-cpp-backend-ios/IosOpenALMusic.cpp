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

using namespace gdx::ios;

IosOpenALMusic::IosOpenALMusic(IosOpenALAudio * _audio, int channels, void* buffer, int length, int _sampleRate) :
sourceID(-1),  isLoopingVar(false), format(channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16), sampleRate(_sampleRate), volume(1), 
audio(_audio), isPlayingVar(false), buffers(NULL), renderedSeconds(0),  secondsPerBuffer(0), musicBuffer(buffer), bufferLength(length)
{
    audio->music.push_back(this);
    
    secondsPerBuffer = (float)bufferSize / bytesPerSample / channels / sampleRate;
    
    sourceID = audio->obtainSource(true);
    if (sourceID == -1) return;
    if (buffers == NULL) {
        buffers =  new unsigned[bufferCount];
        alGenBuffers(bufferCount,  buffers);
        if (alGetError() != AL_NO_ERROR) throw std::runtime_error("Unabe to allocate audio buffers.");
    }
    
    alSourcei(sourceID, AL_LOOPING, AL_FALSE);
    
    alSourcef(sourceID, AL_GAIN, volume);
    
    for (int i = 0; i < bufferCount; i++) {
        ALuint bufferID = buffers[i];
        
        alBufferData(bufferID, format, musicBuffer, bufferLength, sampleRate);
        alSourceQueueBuffers(sourceID, 1, &bufferID);
    }
    
    if (alGetError() != AL_NO_ERROR) {
        stop();
        return;
    }
}

void IosOpenALMusic::play ()
{
    alSourcePlay(sourceID);
    isPlayingVar = true;
    
}

void IosOpenALMusic::pause ()
{
    if (sourceID != -1) alSourcePause(sourceID);
    isPlayingVar = false;
}

void IosOpenALMusic::stop ()
{
    alSourceStop(sourceID);
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
}

bool IosOpenALMusic::isLooping ()
{
    return isLoopingVar;
}

void IosOpenALMusic::setVolume (float volume)
{
    this->volume = volume;
    if (sourceID != -1) alSourcef(sourceID, AL_GAIN, volume);
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
    alDeleteBuffers(bufferCount, buffers);
    delete [] buffers;
    buffers = NULL;
}

void IosOpenALMusic::reset() {
    
}

void IosOpenALMusic::update()
{
    if (sourceID == -1) return;
    
    bool end = false;
    int buffers;
    alGetSourcei(sourceID, AL_BUFFERS_PROCESSED, &buffers);
    while (buffers-- > 0) {
        unsigned bufferID;
        alSourceUnqueueBuffers(sourceID, 1, &bufferID);
        if (bufferID == AL_INVALID_VALUE) break;
        renderedSeconds += secondsPerBuffer;
        if (end) continue;
        
        
        alBufferData(bufferID, format, musicBuffer, bufferLength, sampleRate);
        alSourceQueueBuffers(sourceID, 1, &bufferID);
    }

    int abq;
    alGetSourcei(sourceID, AL_BUFFERS_QUEUED, &abq);
    if (end && abq == 0) stop();
    
    // A buffer underflow will cause the source to stop.
    int ss;
    alGetSourcei(sourceID, AL_SOURCE_STATE, &ss);
    if (isPlayingVar && ss != AL_PLAYING) alSourcePlay(sourceID);
}
