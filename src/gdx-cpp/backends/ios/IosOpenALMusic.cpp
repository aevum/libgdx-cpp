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
#include <OpenAL/alc.h>
#include <stdexcept>
#include <gdx-cpp/Gdx.hpp>

#import <Foundation/Foundation.h>

using namespace gdx::ios;

IosOpenALMusic::IosOpenALMusic(IosOpenALAudio * _audio, const FileHandle::ptr& _file) :
audio(_audio),
sourceID(-1),
sampleRate(0),
isLoopingVar(false),
isPlayingVar(false),
volume(1),
renderedSeconds(0),
channels(1),
file(_file),
paused(false)
{
    audio->music.push_back(this);
    sourceID = audio->obtainSource(true);
    
    CHECK_OPENAL_ERROR(alGenBuffers(GDX_IOS_OPENALMUSIC_BUFFER_COUNT, alBuffers));
    CHECK_OPENAL_ERROR(alSourcei(sourceID, AL_LOOPING, AL_FALSE));
    CHECK_OPENAL_ERROR(alSourcef(sourceID, AL_GAIN, volume));
}

bool IosOpenALMusic::isPaused() {
    return paused;
}

void IosOpenALMusic::play ()
{
    CHECK_OPENAL_ERROR(alSourcePlay(sourceID));    
    paused = false;
    isPlayingVar = true;
}

void IosOpenALMusic::pause ()
{
    if (sourceID != -1) CHECK_OPENAL_ERROR(alSourcePause(sourceID));
    paused = true;
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

void IosOpenALMusic::setup() {
    OSStatus    err;
    UInt32      size;
    
    err = ExtAudioFileOpenURL((CFURLRef)[NSURL fileURLWithPath:[NSString stringWithCString:file->path().c_str() encoding:NSUTF8StringEncoding]], &audioFile);
    
    if (err) {
		gdx_log_error("GdxIosAudio","GetOpenALAudioData: failed to open audioFile");
        ExtAudioFileDispose(audioFile);
        return;
    }
    
    AudioStreamBasicDescription fileFormat;
    size = sizeof(fileFormat);
    err = ExtAudioFileGetProperty(audioFile, kExtAudioFileProperty_FileDataFormat, &size, &fileFormat);
    if (err) {
		gdx_log_error("GdxIosAudio","GetOpenALAudioData: failed to get fileFormat");
        ExtAudioFileDispose(audioFile);
        return;
    }
    
    AudioStreamBasicDescription outputFormat;
    outputFormat.mSampleRate = fileFormat.mSampleRate;
    outputFormat.mChannelsPerFrame = fileFormat.mChannelsPerFrame;
    outputFormat.mFormatID = kAudioFormatLinearPCM;
    outputFormat.mBytesPerPacket = 2 * outputFormat.mChannelsPerFrame;
    outputFormat.mFramesPerPacket = 1;
    outputFormat.mBytesPerFrame = 2 * outputFormat.mChannelsPerFrame;
    outputFormat.mBitsPerChannel = 16;
    outputFormat.mFormatFlags = kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked | kAudioFormatFlagIsSignedInteger;
   
    err = ExtAudioFileSetProperty(audioFile, kExtAudioFileProperty_ClientDataFormat, sizeof(outputFormat), &outputFormat);
    
    if (err) {
		gdx_log_error("GdxIosAudio","GetOpenALAudioData: failed to set outputFormat");
        ExtAudioFileDispose(audioFile);
        return;
    }
    
    SInt64  fileLengthFrames = 0;
    size = sizeof(fileLengthFrames);
    err = ExtAudioFileGetProperty(audioFile, kExtAudioFileProperty_FileLengthFrames, &size, &fileLengthFrames);
    
    if (err) {
		gdx_log_error("GdxIosAudio","GetOpenALAudioData: failed to get fileLengthFrames");
        ExtAudioFileDispose(audioFile);
        return;
    }
    
    this->format = outputFormat.mChannelsPerFrame > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
    this->channels = outputFormat.mChannelsPerFrame;
    this->sampleRate = outputFormat.mSampleRate;
    
    int i;
    for (i = 0; i < GDX_IOS_OPENALMUSIC_BUFFER_COUNT; ++i) {
        if (!fill(alBuffers[i])) {
            break;
        }
    }
    
    CHECK_OPENAL_ERROR(alSourceQueueBuffers(sourceID, i, alBuffers));
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
    
    CHECK_OPENAL_ERROR(alDeleteBuffers(GDX_IOS_OPENALMUSIC_BUFFER_COUNT, alBuffers));
}

void IosOpenALMusic::reset() {
    
}

int IosOpenALMusic::read() {
    AudioBufferList dataBuffer;
    dataBuffer.mNumberBuffers = 1;
    dataBuffer.mBuffers[0].mDataByteSize = GDX_IOS_OPENALMUSIC_BUFFER_SIZE;
    dataBuffer.mBuffers[0].mNumberChannels = this->channels;
    dataBuffer.mBuffers[0].mData = musicBuffer;
    
    UInt32 frames = GDX_IOS_OPENALMUSIC_BUFFER_SIZE / 4;
    int err = ExtAudioFileRead(audioFile, (UInt32*)&frames, &dataBuffer);
    
    if (err) {
		gdx_log_error("GdxIosAudio","GetOpenALAudioData: failed to read audioFile");
        ExtAudioFileDispose(audioFile);
        return -1;
    }
    
    return frames * 4;
}

bool IosOpenALMusic::fill(int bufferID) {
    int readed = read();
    
    if (readed <= 0) {
        if (isLoopingVar) {
            reset();
            renderedSeconds = 0;
            readed = this->read();
            if (readed <= 0) return false;
        } else
            return false;
    }
     
    CHECK_OPENAL_ERROR(alBufferData(bufferID, format, musicBuffer, readed, sampleRate));
    
    return true;
}

void IosOpenALMusic::update()
{
    if (sourceID == -1 || !isPlayingVar || paused) return;
    
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

float IosOpenALMusic::getVolume() const {
    return this->volume;
}