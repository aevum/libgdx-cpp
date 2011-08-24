
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

#ifndef GDX_CPP_AUDIO_ANALYSIS_FOURIERTRANSFORM_HPP_
#define GDX_CPP_AUDIO_ANALYSIS_FOURIERTRANSFORM_HPP_

#include <vector>

namespace gdx_cpp {
namespace audio {
namespace analysis {

class FourierTransform {
public:
    FourierTransform(int ts, float sr);
    void noAverages ();
    void linAverages (int numAvg);
    void logAverages (int minBandwidth,int bandsPerOctave);
    void window (int which);
    int timeSize ();
    int specSize ();
    float getBand (int i);
    float getBandWidth ();
    virtual   void setBand (int i,float a) = 0;
    virtual   void scaleBand (int i,float s) = 0;
    int freqToIndex (float freq);
    float indexToFreq (int i);
    float getAverageCenterFrequency (int i);
    float getFreq (float freq);
    void setFreq (float freq,float a);
    void scaleFreq (float freq,float s);
    int avgSize ();
    float getAvg (int i);
    float calcAvg (float lowFreq,float hiFreq);
    virtual void forward (std::vector< float >& buffer) = 0;
    void forward (std::vector< float >& buffer, int startAt);
    virtual void inverse (std::vector< float >& freqReal, std::vector< float >& freqImag, std::vector< float >& buffer) = 0;
    void inverse (std::vector< float >& buffer);
    std::vector< float > getSpectrum ();
    std::vector< float > getRealPart ();
    std::vector< float > getImaginaryPart ();

protected:
    virtual   void allocateArrays () = 0;
    void setComplex (std::vector< float >& r, std::vector< float >& i);
    void fillSpectrum ();
    void doWindow (std::vector< float >& samples);
    void hamming (std::vector< float >& samples);

    const static int NONE;
    /** A constant indicating a Hamming window should be used on sample buffers. */
    const static int HAMMING;
    const static int LINAVG;
    const static int LOGAVG;
    const static int NOAVG;
    const static float TWO_PI;

    int timeSizeVar;
    int sampleRate;
    float bandWidth;
    int whichWindow;
    std::vector<float> real;
    std::vector<float> imag;
    std::vector<float> spectrum;
    std::vector<float> averages;
    int whichAverage;
    int octaves;
    int avgPerOctave;

private:

};

} // namespace gdx_cpp
} // namespace audio
} // namespace analysis

#endif // GDX_CPP_AUDIO_ANALYSIS_FOURIERTRANSFORM_HPP_
