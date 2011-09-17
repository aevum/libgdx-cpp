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


#ifndef LINUXAUDIODEVICE_HPP
#define LINUXAUDIODEVICE_HPP

#include "gdx-cpp/audio/AudioDevice.hpp"

namespace gdx_cpp {

namespace backends {

namespace nix {
  
class LinuxOpenALAudioDevice: public gdx_cpp::audio::AudioDevice
{

public:
    bool isMono ();
    void writeSamples (short * samples, int offset,int numSamples);
    void writeSamples (float * samples, int offset,int numSamples);
    int getLatency ();
    void dispose ();

protected:


private:
};
}
}
}

#endif // LINUXAUDIODEVICE_HPP
