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


#ifndef LINUXMUSIC_HPP
#define LINUXMUSIC_HPP

#include "gdx-cpp/audio/Music.hpp"
#include <gdx-cpp/utils/Aliases.hpp>

namespace gdx_cpp {
namespace files {
class FileHandle;
}


namespace backends {

namespace nix {
class   LinuxOpenALAudio;

class LinuxOpenALMusic : public gdx_cpp::audio::Music
{
public:
    LinuxOpenALMusic(gdx_cpp::backends::nix::LinuxOpenALAudio* _audio, ref_ptr_maker< gdx_cpp::files::FileHandle >::type file);

    void setup (int _channels, int _sampleRate);
    
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
    virtual int read (char * buffer, int bufferSize) = 0;
    virtual void reset () = 0;
    ref_ptr_maker< gdx_cpp::files::FileHandle >::type file;
private:
    const static int bufferSize = 40960;
    const static int bufferCount = 3;
    const static int bytesPerSample = 2;
    static char tempBytes [];

    LinuxOpenALAudio * audio;
    unsigned int  * buffers;
    int sourceID;
    int format, sampleRate;
    bool isLoopingVar, isPlayingVar;
    float volume;
    float renderedSeconds, secondsPerBuffer;

    bool fill(int bufferID);

};

}

}

}

#endif // LINUXMUSIC_HPP
