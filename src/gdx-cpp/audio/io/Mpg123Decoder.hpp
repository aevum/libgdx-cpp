
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

#ifndef GDX_CPP_AUDIO_IO_MPG123DECODER_HPP_
#define GDX_CPP_AUDIO_IO_MPG123DECODER_HPP_

#include <vector>
#include <string>
#include "Decoder.hpp"

struct Mp3File;
namespace gdx {

class Mpg123Decoder : public Decoder {
public:
    Mpg123Decoder (std::string filename);
    ~Mpg123Decoder();
    int readSamples (std::vector< short >& samples);
    int skipSamples (int numSamples);
    int getNumChannels ();
    int getRate ();
    float getLength ();
    void dispose ();

protected:


private:
    Mp3File* handle;    
    Mp3File* openFile (std::string file);
    int getNumChannels (Mp3File* mp3);
    int getRate (Mp3File* mp3);
    float getLength (Mp3File* mp3);
    int readSamples (Mp3File* mp3, std::vector< short >& buffer, int numSamples);
    int skipSamples (Mp3File* mp3, int numSamples);
    void closeFile (Mp3File* mp3);
};

} // namespace gdx

#endif // GDX_CPP_AUDIO_IO_MPG123DECODER_HPP_
