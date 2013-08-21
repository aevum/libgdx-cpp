
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

#include "FFT.hpp"
#include <vector>
#include "gdx-cpp/Gdx.hpp"
#include <cmath>
#include "gdx-cpp/math/MathUtils.hpp"
#include <stdexcept>

using namespace gdx;


FFT::FFT(int ts, float sr): FourierTransform(ts, sr)
{
    if ((ts & (ts - 1)) != 0)
    {
        gdx_log_error("gdx","FFT: timeSize must be a power of two.");
    }
    buildReverseTable();
    buildTrigTables();
}

void FFT::allocateArrays () {
    spectrum = std::vector<float>(timeSizeVar / 2 + 1);
    real = std::vector<float>(timeSizeVar);
    imag = std::vector<float>(timeSizeVar);
}

void FFT::scaleBand (int i,float s) {
    if (s < 0) {
       gdx_log_error("gdx","Can't scale a frequency band by a negative value.");
    }
    if (spectrum[i] != 0) {
        real[i] /= spectrum[i];
        imag[i] /= spectrum[i];
        spectrum[i] *= s;
        real[i] *= spectrum[i];
        imag[i] *= spectrum[i];
    }
    if (i != 0 && i != timeSizeVar / 2) {
        real[timeSizeVar - i] = real[i];
        imag[timeSizeVar - i] = -imag[i];
    }
}

void FFT::setBand (int i,float a) {
    if (a < 0) {
        gdx_log_error("gdx","Can't set a frequency band to a negative value.");
    }
    if (real[i] == 0 && imag[i] == 0) {
        real[i] = a;
        spectrum[i] = a;
    } else {
        real[i] /= spectrum[i];
        imag[i] /= spectrum[i];
        spectrum[i] = a;
        real[i] *= spectrum[i];
        imag[i] *= spectrum[i];
    }
    if (i != 0 && i != timeSizeVar / 2) {
        real[timeSizeVar - i] = real[i];
        imag[timeSizeVar - i] = -imag[i];
    }
}

void FFT::fft () {
    for (int halfSize = 1; halfSize < real.size(); halfSize *= 2) {
        // float k = -(float)Math.PI/halfSize;
        // phase shift step
        // float phaseShiftStepR = (float)Math.cos(k);
        // float phaseShiftStepI = (float)Math.sin(k);
        // using lookup table
        float phaseShiftStepR = cos(halfSize);
        float phaseShiftStepI = sin(halfSize);
        // current phase shift
        float currentPhaseShiftR = 1.0f;
        float currentPhaseShiftI = 0.0f;
        for (int fftStep = 0; fftStep < halfSize; fftStep++) {
            for (int i = fftStep; i < real.size(); i += 2 * halfSize) {
                int off = i + halfSize;
                float tr = (currentPhaseShiftR * real[off]) - (currentPhaseShiftI * imag[off]);
                float ti = (currentPhaseShiftR * imag[off]) + (currentPhaseShiftI * real[off]);
                real[off] = real[i] - tr;
                imag[off] = imag[i] - ti;
                real[i] += tr;
                imag[i] += ti;
            }
            float tmpR = currentPhaseShiftR;
            currentPhaseShiftR = (tmpR * phaseShiftStepR) - (currentPhaseShiftI * phaseShiftStepI);
            currentPhaseShiftI = (tmpR * phaseShiftStepI) + (currentPhaseShiftI * phaseShiftStepR);
        }
    }
}

void FFT::forward (std::vector<float>& buffer) {
    if (buffer.size() != timeSizeVar) {
        gdx_log_error("gdx","FFT.forward: The length of the passed sample buffer must be equal to timeSize().");
    }
    doWindow(buffer);
    // copy samples to real/imag in bit-reversed order
    bitReverseSamples(buffer);
    // perform the fft
    fft();
    // fill the spectrum buffer with amplitudes
    fillSpectrum();
}

void FFT::forward (std::vector<float>& buffReal, std::vector<float>& buffImag) {
    if (buffReal.size() != timeSizeVar || buffImag.size() != timeSizeVar) {
       gdx_log_error("gdx","FFT.forward: The length of the passed buffers must be equal to timeSize().");
    }
    setComplex(buffReal, buffImag);
    bitReverseComplex();
    fft();
    fillSpectrum();
}

void FFT::inverse (std::vector<float>& buffer) {
    if (buffer.size() > real.size()) {
        gdx_log_error("gdx","FFT.inverse: the passed array's length must equal FFT.timeSize().");
    }
    // conjugate
    for (int i = 0; i < timeSizeVar; i++) {
        imag[i] *= -1;
    }
    bitReverseComplex();
    fft();
    // copy the result in real into buffer, scaling as we do
    for (int i = 0; i < buffer.size(); i++) {
        buffer[i] = real[i] / real.size();
    }
}

void FFT::buildReverseTable () {
    int N = timeSizeVar;
    reverse = std::vector<int>(N);

    // set up the bit reversing table
    reverse[0] = 0;
    for (int limit = 1, bit = N / 2; limit < N; limit <<= 1, bit >>= 1)
        for (int i = 0; i < limit; i++)
            reverse[i + limit] = reverse[i] + bit;
}

void FFT::bitReverseSamples (std::vector<float> samples) {
    for (int i = 0; i < samples.size(); i++) {
        real[i] = samples[reverse[i]];
        imag[i] = 0.0f;
    }
}

void FFT::bitReverseComplex () {
    std::vector<float> revReal = std::vector<float>(real.size());
    std::vector<float> revImag = std::vector<float>(imag.size());
    for (int i = 0; i < real.size(); i++) {
        revReal[i] = real[reverse[i]];
        revImag[i] = imag[reverse[i]];
    }
    real = revReal;
    imag = revImag;
}

float FFT::sin (int i) {
    return sinlookup[i];
}

float FFT::cos (int i) {
    return coslookup[i];
}

void FFT::buildTrigTables () {
    int N = timeSizeVar;
    sinlookup = std::vector<float>(N);
    coslookup = std::vector<float>(N);
    for (int i = 0; i < N; i++) {
        sinlookup[i] = (float)std::sin(-(float)gdx::detail::PI / i);
        coslookup[i] = (float)std::cos(-(float)gdx::detail::PI / i);
    }
}
