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


#ifndef LINUXOGG_HPP
#define LINUXOGG_HPP
#include "LinuxOpenALSound.hpp"
#include "LinuxOpenALMusic.hpp"


namespace gdx_cpp {
namespace files {
class FileHandle;
}

namespace backends {

namespace nix {
class LinuxOpenALAudio;
class LinuxOggInputStream;

class LinuxOggSound : public LinuxOpenALSound
{
public :
    LinuxOggSound(gdx_cpp::backends::nix::LinuxOpenALAudio* audio, const ref_ptr_maker< gdx_cpp::files::FileHandle >::type file);
};

class LinuxOggMusic : public LinuxOpenALMusic
{
public :
    LinuxOggMusic(gdx_cpp::backends::nix::LinuxOpenALAudio* audio, const ref_ptr_maker< gdx_cpp::files::FileHandle >::type file);
    ~LinuxOggMusic();
protected:
    int read (char * buffer, int bufferSize);
    void reset ();
private:
    LinuxOggInputStream * input;
};


}

}

}
#endif // LINUXOGG_HPP
