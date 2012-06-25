/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 */

#include "IosAudio.hpp"
#include <gdx-cpp/audio/Sound.hpp>
#include <gdx-cpp/audio/Music.hpp>
#include <gdx-cpp/Gdx.hpp>
#include <stdexcept>

#import <AVFoundation/AVFoundation.h>


using namespace gdx::ios;

class AvAudioPlayerSound : public gdx::Sound {
public:
    AvAudioPlayerSound(NSURL* url) {
        NSError* error;
        audioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error];
        [url dealloc];
    }
    
    virtual   void play (){
        [audioPlayer play];
    }
    
    virtual   void play (float volume){
        [audioPlayer setVolume:volume];
        play();
    }
    
    virtual   void stop () {
        [audioPlayer stop];
    }
    
    virtual   void dispose () {
        [audioPlayer release];
    }
    
private:
    AVAudioPlayer *audioPlayer;
};


class AvAudioPlayerMusic : public gdx::Music {
public:
    
    AvAudioPlayerMusic(NSURL* url) {
        NSError* error;
        audioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error];
        [url dealloc];
    }
    
    virtual void play () {
        [audioPlayer play];
    }
    
    virtual void pause () {
        
    }
    
    virtual void stop () {
        [audioPlayer stop];
    }
    
    virtual bool isPlaying () {
        return [audioPlayer isPlaying];
    }
    
    virtual void setLooping (bool isLooping) {
        audioPlayer.numberOfLoops = isLooping ? -1 : 1;
    }
    
    virtual bool isLooping () {
        return audioPlayer.numberOfLoops == -1;
    }
    
    virtual void setVolume (float volume) {
        audioPlayer.volume = volume;
    }
    
    virtual float getPosition () {
        NSLog(@"AVAudioMusic:getPosition is currently not implemented ");
        return 0;
    }
    
    virtual void dispose () {
        [audioPlayer release];
    }
    
private:
    AVAudioPlayer *audioPlayer;
};

gdx::Sound* IosAudio::newSound(const ref_ptr_maker<gdx::FileHandle>::type fileHandle) {
    
    std::string path = fileHandle->path();  
    
    NSURL* file = [[NSURL alloc] initWithString:[NSString stringWithCString:path.c_str() encoding:NSASCIIStringEncoding]];
    
    return new AvAudioPlayerSound(file);
}

gdx::Music* IosAudio::newMusic(const ref_ptr_maker<gdx::FileHandle>::type file) {
    std::string path = file->path();  
    
    NSURL* fileUrl = [[NSURL alloc] initWithString:[NSString stringWithCString:path.c_str() encoding:NSASCIIStringEncoding]];
    
    return new AvAudioPlayerMusic(fileUrl);
}


gdx::AudioDevice * IosAudio::newAudioDevice (int samplingRate, bool isMono){
    throw std::runtime_error("Not implemented");
}

gdx::AudioRecorder *  IosAudio::newAudioRecoder (int samplingRate, bool isMono) {
    throw std::runtime_error("Not implemented");
}

