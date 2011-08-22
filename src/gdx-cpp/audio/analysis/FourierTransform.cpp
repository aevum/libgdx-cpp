
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

using namespace gdx_cpp::audio::analysis;

void FourierTransform::setComplex () {
    if (real.length != r.length && imag.length != i.length) {
        throw new IllegalArgumentException("This won't work");
    } else {
        System.arraycopy(r, 0, real, 0, r.length);
        System.arraycopy(i, 0, imag, 0, i.length);
    }
}

void FourierTransform::fillSpectrum () {
    for (int i = 0; i < spectrum.length; i++) {
        spectrum[i] = (float)Math.sqrt(real[i] * real[i] + imag[i] * imag[i]);
    }

    if (whichAverage == LINAVG) {
        int avgWidth = (int)spectrum.length / averages.length;
        for (int i = 0; i < averages.length; i++) {
            float avg = 0;
            int j;
            for (j = 0; j < avgWidth; j++) {
                int offset = j + i * avgWidth;
                if (offset < spectrum.length) {
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
                lowFreq = (sampleRate / 2) / (float)Math.pow(2, octaves - i);
            }
            hiFreq = (sampleRate / 2) / (float)Math.pow(2, octaves - i - 1);
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
    averages = new float[0];
    whichAverage = NOAVG;
}

void FourierTransform::linAverages (int numAvg) {
    if (numAvg > spectrum.length / 2) {
        throw new IllegalArgumentException("The number of averages for this transform can be at most " + spectrum.length / 2
                                           + ".");
    } else {
        averages = new float[numAvg];
    }
    whichAverage = LINAVG;
}

void FourierTransform::logAverages (int minBandwidth,int bandsPerOctave) {
    float nyq = (float)sampleRate / 2f;
    octaves = 1;
    while ((nyq /= 2) > minBandwidth) {
        octaves++;
    }
    avgPerOctave = bandsPerOctave;
    averages = new float[octaves * bandsPerOctave];
    whichAverage = LOGAVG;
}

void FourierTransform::window (int which) {
    if (which < 0 || which > 1) {
        throw new IllegalArgumentException("Invalid window type.");
    } else {
        whichWindow = which;
    }
}

void FourierTransform::doWindow () {
    switch (whichWindow) {
    case HAMMING:
        hamming(samples);
        break;
    }
}

void FourierTransform::hamming () {
    for (int i = 0; i < samples.length; i++) {
        samples[i] *= (0.54f - 0.46f * Math.cos(TWO_PI * i / (samples.length - 1)));
    }
}

int FourierTransform::timeSize () {
    return timeSize;
}

int FourierTransform::specSize () {
    return spectrum.length;
}

float FourierTransform::getBand (int i) {
    if (i < 0) i = 0;
    if (i > spectrum.length - 1) i = spectrum.length - 1;
    return spectrum[i];
}

float FourierTransform::getBandWidth () {
    return bandWidth;
}

int FourierTransform::freqToIndex (float freq) {
    // special case: freq is lower than the bandwidth of spectrum[0]
    if (freq < getBandWidth() / 2) return 0;
    // special case: freq is within the bandwidth of spectrum[spectrum.length - 1]
    if (freq > sampleRate / 2 - getBandWidth() / 2) return spectrum.length - 1;
    // all other cases
    float fraction = freq / (float)sampleRate;
    int i = Math.round(timeSize * fraction);
    return i;
}

float FourierTransform::indexToFreq (int i) {
    float bw = getBandWidth();
    // special case: the width of the first bin is half that of the others.
    // so the center frequency is a quarter of the way.
    if (i == 0) return bw * 0.25f;
    // special case: the width of the last bin is half that of the others.
    if (i == spectrum.length - 1) {
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
        int avgWidth = (int)spectrum.length / averages.length;
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
            lowFreq = (sampleRate / 2) / (float)Math.pow(2, octaves - octave);
        }
        // and the high frequency for this octave
        hiFreq = (sampleRate / 2) / (float)Math.pow(2, octaves - octave - 1);
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
    return averages.length;
}

float FourierTransform::getAvg (int i) {
    float ret;
    if (averages.length > 0)
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

void FourierTransform::forward (int startAt) {
    if (buffer.length - startAt < timeSize) {
        throw new IllegalArgumentException("FourierTransform.forward: not enough samples in the buffer between " + startAt
                                           + " and " + buffer.length + " to perform a transform.");
    }

    // copy the section of samples we want to analyze
    float[] section = new float[timeSize];
    System.arraycopy(buffer, startAt, section, 0, section.length);
    forward(section);
}

void FourierTransform::inverse () {
    setComplex(freqReal, freqImag);
    inverse(buffer);
}

float* FourierTransform::getSpectrum () {
    return spectrum;
}

float* FourierTransform::getRealPart () {
    return real;
}

float* FourierTransform::getImaginaryPart () {
    return imag;
}

