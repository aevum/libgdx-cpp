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


#ifndef EMSCRIPTEN_OGG_HPP
#define EMSCRIPTEN_OGG_HPP
#include "EmscriptenOpenALMusic.hpp"
#include "EmscriptenOpenALSound.hpp"
#include "gdx-cpp/utils/Buffer.hpp"


namespace gdx {
class FileHandle;

namespace scripten {
class EmscriptenOggInputStream;
class EmscriptenOpenALAudio;

class EmscriptenOggSound : public EmscriptenOpenALSound
{
public :
    EmscriptenOggSound(gdx::scripten::EmscriptenOpenALAudio* audio, const ref_ptr_maker< gdx::FileHandle >::shared_ptr_t file);
};

class EmscriptenOggMusic : public EmscriptenOpenALMusic
{
public :
    EmscriptenOggMusic(gdx::scripten::EmscriptenOpenALAudio* audio, const ref_ptr_maker< gdx::FileHandle >::shared_ptr_t file);
    ~EmscriptenOggMusic();
protected:
    int read (char * buffer, int bufferSize);
    void reset ();
private:
    EmscriptenOggInputStream * input;
};


}

}
#endif // EMSCRIPTEN_OGG_HPP
