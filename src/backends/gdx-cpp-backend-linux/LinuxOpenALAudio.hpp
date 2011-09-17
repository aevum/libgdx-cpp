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


#ifndef LINUXAUDIO_HPP
#define LINUXAUDIO_HPP
#include <gdx-cpp/Audio.hpp>
#include <set>
#include <vector>

struct ALCdevice_struct;
class ALCcontext_struct;

namespace gdx_cpp {
namespace files {
class FileHandle;
}

namespace audio{
class Music;
class Sound;
class Device;
class Recorder;
}

namespace backends {

namespace nix {
  class LinuxOpenALMusic;

class LinuxOpenALAudio : public gdx_cpp::Audio
{


public:
    gdx_cpp::audio::AudioDevice * newAudioDevice (int samplingRate, bool isMono);
    gdx_cpp::audio::AudioRecorder * newAudioRecoder (int samplingRate, bool isMono);
    gdx_cpp::audio::Sound * newSound (const ref_ptr_maker< gdx_cpp::files::FileHandle >::type file);
    gdx_cpp::audio::Music * newMusic (const ref_ptr_maker< gdx_cpp::files::FileHandle >::type file);

    LinuxOpenALAudio (int simultaneousSources = 16);
    
    int obtainSource (bool isMusic);
    void freeSource (int sourceID);
    void freeBuffer (int bufferID);
    void stopSourcesWithBuffer (int bufferID);
    void update ();
    void dispose ();

    std::vector<LinuxOpenALMusic * > music;

private :
    void createAl();
    std::set<int> idleSources, allSources;
    ALCdevice_struct * device;
    ALCcontext_struct * context;

};

}

}

}
#endif // LINUXAUDIO_HPP
