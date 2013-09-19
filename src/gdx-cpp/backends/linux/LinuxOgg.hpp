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
#include "LinuxOpenALMusic.hpp"
#include "LinuxOpenALSound.hpp"
#include "gdx-cpp/utils/Buffer.hpp"


namespace gdx {
class FileHandle;

namespace nix {
class LinuxOggInputStream;
class LinuxOpenALAudio;

class LinuxOggSound : public LinuxOpenALSound
{
public :
    LinuxOggSound(gdx::nix::LinuxOpenALAudio* audio, const ref_ptr_maker< gdx::FileHandle >::shared_ptr_t file);
};

class LinuxOggMusic : public LinuxOpenALMusic
{
public :
    LinuxOggMusic(gdx::nix::LinuxOpenALAudio* audio, const ref_ptr_maker< gdx::FileHandle >::shared_ptr_t file);
    ~LinuxOggMusic();
protected:
    int read (char * buffer, int bufferSize) override;
    void reset () override;
private:
    LinuxOggInputStream * input;
};


}

}
#endif // LINUXOGG_HPP
