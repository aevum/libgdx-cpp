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

namespace gdx {
class FileHandle;

namespace ios {
class   IosOpenALAudio;

class IosOpenALMusic : public gdx::Music
{
public:
    IosOpenALMusic(IosOpenALAudio * _audio, int format, void* buffer, int length, int _sampleRate);
   
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
    
protected:
    virtual void reset ();

private:
    IosOpenALAudio * audio;
    unsigned int alBuffer;
    void* musicBuffer;
    int bufferLength;
    int sourceID;
    int format, sampleRate;
    bool isLoopingVar, isPlayingVar;
    float volume;
    float renderedSeconds, secondsPerBuffer;
};

}

}

#endif // IosMUSIC_HPP
