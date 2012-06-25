
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

#include "KissFFT.hpp"
#include "kissfft/kiss_fftr.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

#define MAX_SHORT 32767.0f //TODO check this

using namespace gdx;



struct KissFFTO
{
        kiss_fftr_cfg config;
        kiss_fft_cpx* spectrum;
        int numSamples;
};

void KissFFT::spectrum (std::vector<short>& samples, std::vector<float>& spectrumP) {
    spectrum(handle, samples, spectrumP);
}

void KissFFT::dispose () {
    destroy(handle);
}

void KissFFT::getRealPart (std::vector<short>& real) {
    getRealPart(handle, real);
}

void KissFFT::getImagPart (std::vector<short>& imag) {
    getImagPart(handle, imag);
}

static inline float scale( kiss_fft_scalar val )
{
        if( val < 0 )
                return val * ( 1 / 32768.0f );
        else
                return val * ( 1 / 32767.0f );
}


KissFFTO* KissFFT::create  (int numSamples)
{
        KissFFTO* fft = new KissFFTO();
        fft->config = kiss_fftr_alloc(numSamples,0,NULL,NULL);
        fft->spectrum = (kiss_fft_cpx*)malloc(sizeof(kiss_fft_cpx) * numSamples);
        fft->numSamples = numSamples;
        return fft;
}

void KissFFT::destroy(KissFFTO* fft)
{
        free(fft->config);
        free(fft->spectrum);
        free(fft);
}

void KissFFT::getRealPart(KissFFTO* fft, std::vector<short>& target)
{
        for( int i = 0; i < fft->numSamples / 2; i++ )
                target[i] = fft->spectrum[i].r;
}

void KissFFT::getImagPart(KissFFTO* fft, std::vector<short>& target)
{
        for( int i = 0; i < fft->numSamples / 2; i++ )
                target[i] = fft->spectrum[i].i;
}


void KissFFT::spectrum(KissFFTO* fft, std::vector< short >& samples2, std::vector< float >& spectrum)
{
        
        kiss_fft_scalar* samples = (kiss_fft_scalar*) &samples[0];
        kiss_fftr( fft->config, samples, fft->spectrum );

        int len = fft->numSamples / 2 + 1;

        for( int i = 0; i < len; i++ )
        {
                float re = scale(fft->spectrum[i].r) * fft->numSamples;
                float im = scale(fft->spectrum[i].i) * fft->numSamples;

                if( i > 0 )
                        spectrum[i] = sqrtf(re*re + im*im) / (fft->numSamples / 2);
                else
                        spectrum[i] = sqrtf(re*re + im*im) / (fft->numSamples);
        }
}


