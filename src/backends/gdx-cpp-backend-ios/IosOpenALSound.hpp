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

#ifndef IosSOUND_HPP
#define IosSOUND_HPP

#include "gdx-cpp/audio/Sound.hpp"
#include "gdx-cpp/utils/Buffer.hpp"
#include <OpenAL/al.h>

namespace gdx {
namespace ios {
class   IosOpenALAudio;

class IosOpenALSound : public gdx::Sound
{
public:
    
    IosOpenALSound (IosOpenALAudio * audio);

    void setup (char * buffer, int size, int channels, int sampleRate);

    void play ();

    void play (float volume);

    void loop ();

    void stop ();

    void dispose ();

protected:


private:
    ALuint bufferID;
    IosOpenALAudio * audio;

};
}

}
#endif // IosSOUND_HPP
