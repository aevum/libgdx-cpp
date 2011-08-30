
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

#include "DFT.hpp"
#include <vector>
#include "gdx-cpp/Gdx.hpp"
#include <cmath>
#include <stdexcept>

using namespace gdx_cpp::audio::analysis;

DFT::DFT(int ts, float sr): FourierTransform(ts, sr)
{
    if (ts % 2 != 0)
    {
      throw std::runtime_error("DFT: timeSize must be even.");
    }
    buildTrigTables();
}


void DFT::allocateArrays () {
    spectrum = std::vector<float>(timeSizeVar / 2 + 1);
    real = std::vector<float>(timeSizeVar / 2 + 1);
    imag = std::vector<float>(timeSizeVar / 2 + 1);
}

void DFT::scaleBand (int i,float s) {
}

void DFT::setBand (int i,float a) {
}

void DFT::forward (std::vector<float>& samples) {
    if (samples.size() != timeSizeVar)
    {
        throw std::runtime_error("DFT.forward: The length of the passed sample buffer must be equal to DFT.timeSize().");
    }
    doWindow(samples);
    int N = samples.size();
    for (int f = 0; f <= N / 2; f++) {
        real[f] = 0.0f;
        imag[f] = 0.0f;
        for (int t = 0; t < N; t++) {
            real[f] += samples[t] * cos(t * f);
            imag[f] += samples[t] * -sin(t * f);
        }
    }
    fillSpectrum();
}

void DFT::inverse (std::vector<float>& buffer) {
    int N = buffer.size();
    real[0] /= N;
    imag[0] = -imag[0] / (N / 2);
    real[N / 2] /= N;
    imag[N / 2] = -imag[0] / (N / 2);
    for (int i = 0; i < N / 2; i++) {
        real[i] /= (N / 2);
        imag[i] = -imag[i] / (N / 2);
    }
    for (int t = 0; t < N; t++) {
        buffer[t] = 0.0f;
        for (int f = 0; f < N / 2; f++) {
            buffer[t] += real[f] * cos(t * f) + imag[f] * sin(t * f);
        }
    }
}

void DFT::buildTrigTables () {
    int N = spectrum.size() * timeSizeVar;
    sinlookup = std::vector<float>(N);
    coslookup = std::vector<float>(N);
    for (int i = 0; i < N; i++) {
        sinlookup[i] = (float)std::sin(i * TWO_PI / timeSizeVar);
        coslookup[i] = (float)std::cos(i * TWO_PI / timeSizeVar);
    }
}

float DFT::sin (int i) {
    return sinlookup[i];
}

float DFT::cos (int i) {
    return coslookup[i];
}

