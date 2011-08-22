
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

using namespace gdx_cpp::audio::analysis;

void DFT::allocateArrays () {
    spectrum = new float[timeSize / 2 + 1];
    real = new float[timeSize / 2 + 1];
    imag = new float[timeSize / 2 + 1];
}

void DFT::scaleBand (int i,float s) {
}

void DFT::setBand (int i,float a) {
}

void DFT::forward () {
    if (samples.length != timeSize) {
        throw new IllegalArgumentException(
            "DFT.forward: The length of the passed sample buffer must be equal to DFT.timeSize().");
    }
    doWindow(samples);
    int N = samples.length;
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

void DFT::inverse () {
    int N = buffer.length;
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
    int N = spectrum.length * timeSize;
    sinlookup = new float[N];
    coslookup = new float[N];
    for (int i = 0; i < N; i++) {
        sinlookup[i] = (float)Math.sin(i * TWO_PI / timeSize);
        coslookup[i] = (float)Math.cos(i * TWO_PI / timeSize);
    }
}

float DFT::sin (int i) {
    return sinlookup[i];
}

float DFT::cos (int i) {
    return coslookup[i];
}

