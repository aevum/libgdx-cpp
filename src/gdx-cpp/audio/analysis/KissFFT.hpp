
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

#ifndef GDX_CPP_AUDIO_ANALYSIS_KISSFFT_HPP_
#define GDX_CPP_AUDIO_ANALYSIS_KISSFFT_HPP_

#include "gdx-cpp/utils/Disposable.hpp"
#include <vector>
#include "kissfft/kiss_fftr.h"

struct KissFFTO;

namespace gdx {

class KissFFT: public Disposable {
public:
    void spectrum (std::vector<short>& samples, std::vector<float>& spectrum);
    void dispose ();
    void getRealPart (std::vector<short>& real);
    void getImagPart (std::vector<short>& imag);

protected:


private:
    KissFFTO* handle;
    KissFFTO* create  (int numSamples);
    void destroy(KissFFTO* fft);
    void getRealPart(KissFFTO* fft, std::vector<short>& target);
    void getImagPart(KissFFTO* fft, std::vector<short>& target);
    void spectrum(KissFFTO* fft, std::vector< short >& samples2, std::vector< float >& spectrum);
};

} // namespace gdx

#endif // GDX_CPP_AUDIO_ANALYSIS_KISSFFT_HPP_
