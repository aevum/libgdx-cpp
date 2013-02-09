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


#include "IosOpenALAudio.hpp"
#include "IosOpenALSound.hpp"
#include "IosOpenALMusic.hpp"
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include "gdx-cpp/utils/Buffer.hpp"
#include <gdx-cpp/Log.hpp>
#include <stdexcept>
#include "gdx-cpp/files/FileHandle.hpp"
#include <iostream>
#import <AudioToolbox/AudioToolbox.h>
#import <Foundation/Foundation.h>

using namespace gdx::ios;

void OpenALInterruptionListener(void * inClientData, UInt32 inInterruptionState) {
   
    IosOpenALAudio* audio = (IosOpenALAudio *) inClientData;
    
    if (inInterruptionState == kAudioSessionBeginInterruption)
    {
        AudioSessionSetActive(false);
        alcMakeContextCurrent(NULL);
        alcSuspendContext(audio->getContext());
    }
    else if (inInterruptionState == kAudioSessionEndInterruption)
    {
        AudioSessionSetActive(true);
        alcMakeContextCurrent(audio->getContext());
        alcProcessContext(audio->getContext());
    }
}

ALCcontext_struct * IosOpenALAudio::getContext(){
    return this->context; 
}

IosOpenALAudio::IosOpenALAudio (int simultaneousSources)
{
    AudioSessionInitialize(NULL, NULL, OpenALInterruptionListener, this);
    
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

void IosOpenALAudio::createAl() {
    device = alcOpenDevice(NULL);
    if (device == NULL) {
        gdx_log_error("gdx","Could not open ALC device");
    }

    context = alcCreateContext(device, NULL);

    alcMakeContextCurrent(context);
}

//Copied from the Emo-Framework: http://code.google.com/p/emo-framework/
void* GetOpenALAudioData(CFURLRef fileURL, ALsizei* dataSize,
						 ALsizei *sampleRate, bool *loaded, int* channels) {
    OSStatus    err;
    UInt32      size;
    void*       data = NULL;
    
	*loaded = false;
	
    ExtAudioFileRef audioFile;
    err = ExtAudioFileOpenURL(fileURL, &audioFile);
    if (err) {
		gdx_log_error("GdxIosAudio","GetOpenALAudioData: failed to open audioFile");
        ExtAudioFileDispose(audioFile);
        return NULL;
    }
    
    AudioStreamBasicDescription fileFormat;
    size = sizeof(fileFormat);
    err = ExtAudioFileGetProperty(audioFile, kExtAudioFileProperty_FileDataFormat, &size, &fileFormat);
    if (err) {
		gdx_log_error("GdxIosAudio","GetOpenALAudioData: failed to get fileFormat");
        ExtAudioFileDispose(audioFile);
        return NULL;
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
    err = ExtAudioFileSetProperty(
								  audioFile, kExtAudioFileProperty_ClientDataFormat, sizeof(outputFormat), &outputFormat);
    if (err) {
		gdx_log_error("GdxIosAudio","GetOpenALAudioData: failed to set outputFormat");
        ExtAudioFileDispose(audioFile);
        return NULL;
    }
    
    SInt64  fileLengthFrames = 0;
    size = sizeof(fileLengthFrames);
    err = ExtAudioFileGetProperty(audioFile, kExtAudioFileProperty_FileLengthFrames, &size, &fileLengthFrames);
    
    if (err) {
		gdx_log_error("GdxIosAudio","GetOpenALAudioData: failed to get fileLengthFrames");
        ExtAudioFileDispose(audioFile);
        return NULL;
    }
    
    UInt32          bufferSize;
    AudioBufferList dataBuffer;
    bufferSize = fileLengthFrames * outputFormat.mBytesPerFrame;;
    data = malloc(bufferSize);
    dataBuffer.mNumberBuffers = 1;
    dataBuffer.mBuffers[0].mDataByteSize = bufferSize;
    dataBuffer.mBuffers[0].mNumberChannels = outputFormat.mChannelsPerFrame;
    dataBuffer.mBuffers[0].mData = data;
    
    err = ExtAudioFileRead(audioFile, (UInt32*)&fileLengthFrames, &dataBuffer);
    if (err) {
		gdx_log_error("GdxIosAudio","GetOpenALAudioData: failed to read audioFile");
        free(data);
        ExtAudioFileDispose(audioFile);
        return NULL;
    }
    
    *dataSize = (ALsizei)bufferSize;
    *sampleRate = (ALsizei)outputFormat.mSampleRate;
    *channels = outputFormat.mChannelsPerFrame;
    
	*loaded = true;
    
    return data;
}

gdx::Sound * IosOpenALAudio::newSound (const ref_ptr_maker< gdx::FileHandle >::shared_ptr_t file) {
    bool audioLoaded;
    void* audioData;
    ALsizei dataSize;
    ALsizei sampleRate;
    ALsizei channels;
    
    gdx_log_debug("IosOpenALAudio", "File is %s", file->path().c_str());
                  
    audioData = GetOpenALAudioData((CFURLRef)[NSURL fileURLWithPath:[NSString stringWithCString:file->path().c_str() encoding:NSUTF8StringEncoding]], &dataSize, &sampleRate, &audioLoaded, &channels);
    
    if (audioData != NULL) {
    
        IosOpenALSound* snd = new IosOpenALSound(this);
        snd->setup((char*) audioData, dataSize, channels , sampleRate);
        free(audioData);
        
        return snd;    
    }
    
    gdx_log_error("IosOpenALAudio", "Failed to load sound: %s", file->name().c_str());
    return nullptr;
}

gdx::Music * IosOpenALAudio::newMusic (const ref_ptr_maker< gdx::FileHandle >::shared_ptr_t file) {
   return new IosOpenALMusic(this, file);
}

int IosOpenALAudio::obtainSource (bool isMusic) {
    std::set<int>::iterator sit = idleSources.begin();
    std::set<int>::iterator send = idleSources.end();
    for (; sit != send; sit++) {
        int sourceID = *sit;
        int state;
        alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING && state != AL_PAUSED) {
            
            if (isMusic) {
                sit = idleSources.erase(sit);
            }
            
            alSourceStop(sourceID);
            alSourcei(sourceID, AL_BUFFER, 0);
            return sourceID;
        }
    }
    return -1;
}

void IosOpenALAudio::freeSource (int sourceID) {
    alSourceStop(sourceID);
    alSourcei(sourceID, AL_BUFFER, 0);
    idleSources.insert(sourceID);
}

void IosOpenALAudio::freeBuffer (int bufferID) {
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

void IosOpenALAudio::stopSourcesWithBuffer (int bufferID) {
    std::set<int>::iterator sit = idleSources.begin();
    std::set<int>::iterator send = idleSources.end();
    for (; sit != send; sit++) {
        int sourceID = *sit;int state;
        alGetSourcei(sourceID, AL_BUFFER, &state);
        if (state == bufferID) alSourceStop(sourceID);
    }
}

void IosOpenALAudio::update () {
    for (int i = 0; i < music.size(); i++)
        music[i]->update();
}

void IosOpenALAudio::dispose () {
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

gdx::AudioDevice* IosOpenALAudio::newAudioDevice (int samplingRate, bool isMono) {
    // BOZO - Write OpenAL device.
    return NULL;//new JavaSoundAudioDevice(samplingRate, isMono);
}

gdx::AudioRecorder* IosOpenALAudio::newAudioRecoder (int samplingRate, bool isMono) {
    return NULL;//new JavaSoundAudioRecorder(samplingRate, isMono);
}
