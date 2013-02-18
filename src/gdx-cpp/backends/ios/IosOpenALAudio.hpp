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


#ifndef IosAUDIO_HPP
#define IosAUDIO_HPP

#include <gdx-cpp/Audio.hpp>
#include <set>
#include <vector>
#include <gdx-cpp/Log.hpp>

#define CHECK_OPENAL_ERROR(func) do { \
  func;\
  ALenum al_error = alGetError(); \
  if (al_error != AL_NO_ERROR) { \
    gdx_log_error("IosMusic", "Error [%d] %s", al_error, alGetString(al_error));\
  }\
} while (false)


struct ALCdevice_struct;
class ALCcontext_struct;

namespace gdx {
class FileHandle;

class Music;
class Sound;
class Device;
class Recorder;   
    
namespace ios {
  class IosOpenALMusic;

class IosOpenALAudio : public gdx::Audio
{


public:
    gdx::AudioDevice * newAudioDevice (int samplingRate, bool isMono);
    gdx::AudioRecorder * newAudioRecoder (int samplingRate, bool isMono);
    gdx::Sound * newSound (const ref_ptr_maker< gdx::FileHandle >::shared_ptr_t file);
    gdx::Music * newMusic (const ref_ptr_maker< gdx::FileHandle >::shared_ptr_t file);

    IosOpenALAudio (int simultaneousSources = 16);
    
    int obtainSource (bool isMusic);
    void freeSource (int sourceID);
    void freeBuffer (int bufferID);
    void stopSourcesWithBuffer (int bufferID);
    void update ();
    void dispose ();
    void setup();
    
    std::vector<IosOpenALMusic * > music;

    ALCcontext_struct * getContext();
private :
    void createAl();
    std::set<int> idleSources, allSources;
    ALCdevice_struct * device;
    ALCcontext_struct * context;

};

}

}
#endif // IosAUDIO_HPP
