
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

namespace gdx_cpp {
namespace audio {
namespace analysis {

class FourierTransform {
public:
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
    virtual   void forward () = 0;
    void forward (int startAt);
    virtual   void inverse () = 0;
    void inverse ();
    float* getSpectrum ();
    float* getRealPart ();
    float* getImaginaryPart ();

protected:
    virtual   void allocateArrays () = 0;
    void setComplex ();
    void fillSpectrum ();
    void doWindow ();
    void hamming ();

private:

};

} // namespace gdx_cpp
} // namespace audio
} // namespace analysis

#endif // GDX_CPP_AUDIO_ANALYSIS_FOURIERTRANSFORM_HPP_
