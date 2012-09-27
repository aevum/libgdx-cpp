
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

#include "FourierTransform.hpp"
#include <vector>
#include <cmath>
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/math/MathUtils.hpp"
#include <stdexcept>
#include <sstream>

using namespace gdx;


const int FourierTransform::NONE = 0; //FINAL
/** A constant indicating a Hamming window should be used on sample buffers. */
const int FourierTransform::HAMMING = 1;
const int FourierTransform::LINAVG = 2;
const int FourierTransform::LOGAVG = 3;
const int FourierTransform::NOAVG = 4;
const float FourierTransform::TWO_PI = (float)(2 * PI);


FourierTransform::FourierTransform(int ts, float sr): timeSizeVar(ts), sampleRate((int)sr), real(), imag(),spectrum (), octaves(0), avgPerOctave(0)
{
    bandWidth = (2.0 / timeSizeVar) * ((float)sampleRate / 2.0);
    noAverages();
    allocateArrays();
    whichWindow = NONE;
}

void FourierTransform::setComplex (std::vector<float>& r,  std::vector<float>& i) {
    if (real.size() && imag.size() != i.size())
    {
        gdx_log_error("gdx","This won't work");
    } else {
        real.insert(real.end(), r.begin(), r.end());
        imag.insert(imag.end(), i.begin(), i.end());
    }
}

void FourierTransform::fillSpectrum () {
    for (int i = 0; i < spectrum.size(); i++) {
        spectrum[i] = (float)std::sqrt(real[i] * real[i] + imag[i] * imag[i]);
    }

    if (whichAverage == LINAVG) {
        int avgWidth = (int)spectrum.size() / averages.size();
        for (int i = 0; i < averages.size(); i++) {
            float avg = 0;
            int j;
            for (j = 0; j < avgWidth; j++) {
                int offset = j + i * avgWidth;
                if (offset < spectrum.size()) {
                    avg += spectrum[offset];
                } else {
                    break;
                }
            }
            avg /= j + 1;
            averages[i] = avg;
        }
    } else if (whichAverage == LOGAVG) {
        for (int i = 0; i < octaves; i++) {
            float lowFreq, hiFreq, freqStep;
            if (i == 0) {
                lowFreq = 0;
            } else {
                lowFreq = (sampleRate / 2) / (float)std::pow(2, octaves - i);
            }
            hiFreq = (sampleRate / 2) / (float)std::pow(2, octaves - i - 1);
            freqStep = (hiFreq - lowFreq) / avgPerOctave;
            float f = lowFreq;
            for (int j = 0; j < avgPerOctave; j++) {
                int offset = j + i * avgPerOctave;
                averages[offset] = calcAvg(f, f + freqStep);
                f += freqStep;
            }
        }
    }
}

void FourierTransform::noAverages () {
    averages = std::vector<float>(0);
    whichAverage = NOAVG;
}

void FourierTransform::linAverages (int numAvg) {
    if (numAvg > spectrum.size() / 2)
    {
        std::stringstream ss;
        ss << "The number of averages for this transform can be at most " << spectrum.size()/2 << ".";
        gdx_log_error("gdx",ss.str());
    } else {
        averages = std::vector<float>(numAvg);
    }
    whichAverage = LINAVG;
}

void FourierTransform::logAverages (int minBandwidth,int bandsPerOctave) {
    float nyq = (float)sampleRate / 2.0;
    octaves = 1;
    while ((nyq /= 2) > minBandwidth) {
        octaves++;
    }
    avgPerOctave = bandsPerOctave;
    averages = std::vector<float>(octaves * bandsPerOctave);
    whichAverage = LOGAVG;
}

void FourierTransform::window (int which) {
    if (which < 0 || which > 1) {
        gdx_log_error("gdx","Invalid window type.");
    } else {
        whichWindow = which;
    }
}

void FourierTransform::doWindow (std::vector<float>& samples) {
    switch (whichWindow) {
    case HAMMING:
        hamming(samples);
        break;
    }
}

void FourierTransform::hamming (std::vector<float>& samples) {
    for (int i = 0; i < samples.size(); i++) {
        samples[i] *= (0.54f - 0.46f * std::cos(TWO_PI * i / (samples.size() - 1)));
    }
}

int FourierTransform::timeSize () {
    return timeSizeVar;
}

int FourierTransform::specSize () {
    return spectrum.size();
}

float FourierTransform::getBand (int i) {
    if (i < 0) i = 0;
    if (i > spectrum.size() - 1) i = spectrum.size() - 1;
    return spectrum[i];
}

float FourierTransform::getBandWidth () {
    return bandWidth;
}

int FourierTransform::freqToIndex (float freq) {
    // special case: freq is lower than the bandwidth of spectrum[0]
    if (freq < getBandWidth() / 2) return 0;
    // special case: freq is within the bandwidth of spectrum[spectrum.length - 1]
    if (freq > sampleRate / 2 - getBandWidth() / 2) return spectrum.size() - 1;
    // all other cases
    float fraction = freq / (float)sampleRate;
    int i = std::floor(timeSizeVar * fraction + 0.5);
    return i;
}

float FourierTransform::indexToFreq (int i) {
    float bw = getBandWidth();
    // special case: the width of the first bin is half that of the others.
    // so the center frequency is a quarter of the way.
    if (i == 0) return bw * 0.25f;
    // special case: the width of the last bin is half that of the others.
    if (i == spectrum.size() - 1) {
        float lastBinBeginFreq = (sampleRate / 2) - (bw / 2);
        float binHalfWidth = bw * 0.25f;
        return lastBinBeginFreq + binHalfWidth;
    }
    // the center frequency of the ith band is simply i*bw
    // because the first band is half the width of all others.
    // treating it as if it wasn't offsets us to the middle
    // of the band.
    return i * bw;
}

float FourierTransform::getAverageCenterFrequency (int i) {
    if (whichAverage == LINAVG) {
        // an average represents a certain number of bands in the spectrum
        int avgWidth = (int)spectrum.size() / averages.size();
        // the "center" bin of the average, this is fudgy.
        int centerBinIndex = i * avgWidth + avgWidth / 2;
        return indexToFreq(centerBinIndex);

    } else if (whichAverage == LOGAVG) {
        // which "octave" is this index in?
        int octave = i / avgPerOctave;
        // which band within that octave is this?
        int offset = i % avgPerOctave;
        float lowFreq, hiFreq, freqStep;
        // figure out the low frequency for this octave
        if (octave == 0) {
            lowFreq = 0;
        } else {
            lowFreq = (sampleRate / 2) / (float)std::pow(2, octaves - octave);
        }
        // and the high frequency for this octave
        hiFreq = (sampleRate / 2) / (float)std::pow(2, octaves - octave - 1);
        // each average band within the octave will be this big
        freqStep = (hiFreq - lowFreq) / avgPerOctave;
        // figure out the low frequency of the band we care about
        float f = lowFreq + offset * freqStep;
        // the center of the band will be the low plus half the width
        return f + freqStep / 2;
    }

    return 0;
}

float FourierTransform::getFreq (float freq) {
    return getBand(freqToIndex(freq));
}

void FourierTransform::setFreq (float freq,float a) {
    setBand(freqToIndex(freq), a);
}

void FourierTransform::scaleFreq (float freq,float s) {
    scaleBand(freqToIndex(freq), s);
}

int FourierTransform::avgSize () {
    return averages.size();
}

float FourierTransform::getAvg (int i) {
    float ret;
    if (averages.size() > 0)
        ret = averages[i];
    else
        ret = 0;
    return ret;
}

float FourierTransform::calcAvg (float lowFreq,float hiFreq) {
    int lowBound = freqToIndex(lowFreq);
    int hiBound = freqToIndex(hiFreq);
    float avg = 0;
    for (int i = lowBound; i <= hiBound; i++) {
        avg += spectrum[i];
    }
    avg /= (hiBound - lowBound + 1);
    return avg;
}

void FourierTransform::forward (std::vector<float>& buffer, int startAt) {
    if (buffer.size() - startAt < timeSizeVar) {
        std::stringstream ss;
        ss << "GDX-CPP::AUDIO::ANALYSIS FourierTransform.cpp: " << "FourierTransform.forward: not enough samples in the buffer between "
        << startAt << " and " << buffer.size() << " to perform a transform.";
        gdx_log_error("gdx",ss.str());
    }

    // copy the section of samples we want to analyze
    std::vector<float> section = std::vector<float>(timeSizeVar);
    section.reserve(buffer.size());
    section.insert(section.end(), buffer.begin(), buffer.end());
    forward(section);
}

void FourierTransform::inverse (std::vector<float>& freqReal, std::vector<float>& freqImag, std::vector<float>& buffer) {
    setComplex(freqReal, freqImag);
    inverse(buffer);
}

std::vector<float> FourierTransform::getSpectrum () {
    return spectrum;
}

std::vector<float> FourierTransform::getRealPart () {
    return real;
}

std::vector<float> FourierTransform::getImaginaryPart () {
    return imag;
}

