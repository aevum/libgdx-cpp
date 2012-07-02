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


#include "LinuxOpenALMusic.hpp"
#include "LinuxOpenALAudio.hpp"
#include <gdx-cpp/files/FileHandle.hpp>
#include <AL/al.h>
#include <stdexcept>

using namespace gdx::nix;

char LinuxOpenALMusic::tempBytes[bufferSize];

LinuxOpenALMusic::LinuxOpenALMusic(LinuxOpenALAudio * _audio, ref_ptr_maker< gdx::FileHandle >::shared_ptr_def _file) :
        isLoopingVar(false), isPlayingVar(false), sourceID(-1), format(0), sampleRate(0), volume(1), renderedSeconds(0), secondsPerBuffer(0),
        audio(_audio), file(_file), buffers(NULL)
{
    audio->music.push_back(this);
}

void LinuxOpenALMusic::setup (int _channels, int _sampleRate)
{
    this->format = _channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
    this->sampleRate = _sampleRate;
    secondsPerBuffer = (float)bufferSize / bytesPerSample / _channels / _sampleRate;
}

void LinuxOpenALMusic::play ()
{
    if (sourceID == -1) {
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
            if (!fill(bufferID)) break;
            alSourceQueueBuffers(sourceID, 1, &bufferID);
        }
        if (alGetError() != AL_NO_ERROR) {
            stop();
            return;
        }
    }
    alSourcePlay(sourceID);
    isPlayingVar = true;

}
void LinuxOpenALMusic::pause ()
{
    if (sourceID != -1) alSourcePause(sourceID);
    isPlayingVar = false;
}
void LinuxOpenALMusic::stop ()
{
    if (sourceID == -1) return;
    reset();
    audio->freeSource(sourceID);
    sourceID = -1;
    renderedSeconds = 0;
    isPlayingVar = false;
}
bool LinuxOpenALMusic::isPlaying ()
{
    if (sourceID == -1) return false;
    return isPlayingVar;
}
void LinuxOpenALMusic::setLooping (bool isLooping)
{
    isLoopingVar = isLooping;
}
bool LinuxOpenALMusic::isLooping ()
{
    return isLoopingVar;
}
void LinuxOpenALMusic::setVolume (float volume)
{
    this->volume = volume;
    if (sourceID != -1) alSourcef(sourceID, AL_GAIN, volume);
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
    alDeleteBuffers(bufferCount, buffers);
    delete [] buffers;
    buffers = NULL;
}
void LinuxOpenALMusic::update()
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
        if (fill(bufferID))
            alSourceQueueBuffers(sourceID, 1, &bufferID);
        else
            end = true;
    }
    int abq;
    alGetSourcei(sourceID, AL_BUFFERS_QUEUED, &abq);
    if (end && abq == 0) stop();

    // A buffer underflow will cause the source to stop.
    int ss;
    alGetSourcei(sourceID, AL_SOURCE_STATE, &ss);
    if (isPlayingVar && ss != AL_PLAYING) alSourcePlay(sourceID);
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
    alBufferData(bufferID, format, tempBytes, length, sampleRate);
    return true;
}
