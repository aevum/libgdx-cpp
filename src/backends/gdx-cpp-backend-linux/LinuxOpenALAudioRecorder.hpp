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


#ifndef AUDIORECORDER_HPP
#define AUDIORECORDER_HPP

#include "gdx-cpp/audio/AudioRecorder.hpp"

namespace gdx_cpp {

namespace backends {

namespace nix {
  
class LinuxOpenALAudioRecorder : gdx_cpp::audio::AudioRecorder
{
public:
    void read (int offset,int numSamples);
    void dispose ();

protected:


private:
};

}
  
}
  
}
#endif // AUDIORECORDER_HPP
