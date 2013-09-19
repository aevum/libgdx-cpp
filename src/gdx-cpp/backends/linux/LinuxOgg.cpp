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


#include <cassert>
#include <cstdlib>
#include <memory>

#include "LinuxOgg.hpp"
#include "LinuxOggInputStream.hpp"
#include "LinuxOpenALMusic.hpp"
#include "LinuxOpenALSound.hpp"
#include "gdx-cpp/files/FileHandle.hpp"

using namespace gdx::nix;

LinuxOggSound::LinuxOggSound(gdx::nix::LinuxOpenALAudio* audio, const ref_ptr_maker< gdx::FileHandle >::shared_ptr_t file): LinuxOpenALSound(audio)
{
    LinuxOggInputStream input;
    input.open(file->path());
    char* buffer = (char *) malloc(16384);
    int bufSize = 16384;
    int size = 0;
    int i = 0;

    while ((size = input.read(&buffer[i], 16384)) > 0) {
        i += size;
        if (i == bufSize) {
            buffer = (char *) realloc(buffer, bufSize * 2);
            assert(buffer);
            bufSize *= 2;
        }
    }

    setup(buffer, i, input.getChannels(), input.getSampleRate());
    free(buffer);
}


LinuxOggMusic::LinuxOggMusic(gdx::nix::LinuxOpenALAudio* audio, const ref_ptr_maker< gdx::FileHandle >::shared_ptr_t file):
        LinuxOpenALMusic(audio, file)
{
    input = new LinuxOggInputStream();
    input->open(file->path());
    setup(input->getChannels(), input->getSampleRate());
}

LinuxOggMusic::~LinuxOggMusic()
{
    delete input;
}

int LinuxOggMusic::read (char * buffer, int bufferSize)
{  
    return input->read(buffer, bufferSize);
}
void LinuxOggMusic::reset ()
{
    if (input == nullptr) return;
    input->reset();
}
