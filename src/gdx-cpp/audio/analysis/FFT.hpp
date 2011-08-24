
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

#ifndef GDX_CPP_AUDIO_ANALYSIS_FFT_HPP_
#define GDX_CPP_AUDIO_ANALYSIS_FFT_HPP_

#include "FourierTransform.hpp"
#include <vector>

namespace gdx_cpp {
namespace audio {
namespace analysis {

class FFT : public FourierTransform{
public:
    FFT (int timeSize, float sampleRate);
    void scaleBand (int i,float s);
    void setBand (int i,float a);
    void forward (std::vector< float >& buffe);
    void forward (std::vector< float >& bufferReal, std::vector< float >& bufferImag);
    void inverse (std::vector< float >& buffer);
    static void main ();

protected:
    void allocateArrays ();

private:
    void fft ();
    void buildReverseTable ();
    void bitReverseSamples (std::vector< float > samples);
    void bitReverseComplex ();
    float sin (int i);
    float cos (int i);
    void buildTrigTables ();
    std::vector<float> sinlookup;
    std::vector<float> coslookup;
    std::vector<int> reverse;
};

} // namespace gdx_cpp
} // namespace audio
} // namespace analysis

#endif // GDX_CPP_AUDIO_ANALYSIS_FFT_HPP_
