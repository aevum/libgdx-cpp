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


#ifndef IosMUSIC_HPP
#define IosMUSIC_HPP

#include "gdx-cpp/audio/Music.hpp"
#include <gdx-cpp/internal/memory>
#include <gdx-cpp/files/FileHandle.hpp>
#import <AudioToolbox/AudioToolbox.h>

#define GDX_IOS_OPENALMUSIC_BUFFER_COUNT 4
#define GDX_IOS_OPENALMUSIC_BUFFER_SIZE 65536

namespace gdx {
class FileHandle;

namespace ios {
class   IosOpenALAudio;

class IosOpenALMusic : public gdx::Music
{
public:
    IosOpenALMusic(IosOpenALAudio * _audio, const FileHandle::ptr& filehandle);
   
    void play ();
    void pause ();
    void stop ();
    bool isPlaying ();
    void setLooping (bool isLooping);
    bool isLooping ();
    void setVolume (float volume);
    float getPosition ();
    void dispose ();
    void update ();
    void setup();
    bool isPaused();
    float getVolume() const;
    
protected:
    virtual void reset ();
    bool fill(int bufferID);
    int read();
    
private:
    IosOpenALAudio * audio;
    
    unsigned int alBuffers[GDX_IOS_OPENALMUSIC_BUFFER_COUNT];
    void* musicBuffer[GDX_IOS_OPENALMUSIC_BUFFER_SIZE];
    
    int sourceID;
    int channels;
    int format, sampleRate;
    bool isLoopingVar, isPlayingVar;
    float volume;
    float renderedSeconds;
    bool paused;
    ExtAudioFileRef audioFile;
    FileHandle::ptr file;
};

}

}

#endif // IosMUSIC_HPP
