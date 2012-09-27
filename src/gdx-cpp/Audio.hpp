/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License") = 0;
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#ifndef GDX_CPP_AUDIO_H
#define GDX_CPP_AUDIO_H

#include "gdx-cpp/internal/memory"

namespace gdx {
class FileHandle;
class AudioDevice;
class AudioRecorder;
class Sound;
class Music;


class Audio {
public:
    virtual gdx::AudioDevice * newAudioDevice (int samplingRate, bool isMono) = 0;
    virtual gdx::AudioRecorder * newAudioRecoder (int samplingRate, bool isMono) = 0;

    virtual gdx::Sound * newSound (const ref_ptr_maker< gdx::FileHandle >::shared_ptr_t fileHandle) = 0;
    virtual gdx::Music * newMusic (const ref_ptr_maker< gdx::FileHandle >::shared_ptr_t file) = 0;
    
    virtual ~Audio() { }
};
}

#endif // GDX_CPP_AUDIO_H
