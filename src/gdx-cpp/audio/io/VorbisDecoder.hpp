
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#ifndef GDX_CPP_AUDIO_IO_VORBISDECODER_HPP_
#define GDX_CPP_AUDIO_IO_VORBISDECODER_HPP_

#include <vector>
#include <string>
#include "Decoder.hpp"
#include <cassert>

struct OggFile;

namespace gdx_cpp {
namespace audio {
namespace io {

class VorbisDecoder : public Decoder {
public:
    VorbisDecoder (std::string filename);
    ~VorbisDecoder ();
    void dispose ();
    float getLength ();
    int getNumChannels ();
    int getRate ();
    int readSamples (std::vector< short >& samples);
    int skipSamples (int numSamples);

protected:

private:
    OggFile* handle;

    OggFile* openFile(std::string filename);
    int getNumChannels(OggFile* file);
    int getRate(OggFile* file);
    float getLength(OggFile* file);
    int readSamples(OggFile* file, std::vector< short >& samples, int numSamples);
    int skipSamples(OggFile* file, int numSamples);
    void closeFile(OggFile* file);
};

} // namespace gdx_cpp
} // namespace audio
} // namespace io

#endif // GDX_CPP_AUDIO_IO_VORBISDECODER_HPP_
