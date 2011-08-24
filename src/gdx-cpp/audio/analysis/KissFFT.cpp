
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

using namespace gdx_cpp::audio::analysis;

void KissFFT::spectrum (const ShortBuffer& samples,const FloatBuffer& spectrum) {
    spectrum(handle, samples, spectrum);
}

void KissFFT::dispose () {
    destroy(handle);
}

void KissFFT::getRealPart (const ShortBuffer& real) {
    getRealPart(handle, real);
}

void KissFFT::getImagPart (const ShortBuffer& imag) {
    getImagPart(handle, imag);
}

// void KissFFT::main () {
// final float frequency = 440;
// float increment = (float)(2 * Math.PI) * frequency / 44100; // angular increment for each sample
// float angle = 0;
// short samples[] = new short[1024];
//
// for (int i = 0; i < samples.length; i++) {
// float value = (float)Math.sin(angle);
// samples[i] = (short)(value * 32767);
// angle += increment;
// }
//
// ShortBuffer samplesBuffer = AudioTools.allocateShortBuffer(1024, 1);
// ShortBuffer realBuffer = AudioTools.allocateShortBuffer(512, 1);
// ShortBuffer imagBuffer = AudioTools.allocateShortBuffer(512, 1);
// samplesBuffer.put(samples);
// FloatBuffer spectrum = AudioTools.allocateFloatBuffer(513, 1);
// KissFFT fft = new KissFFT(1024);
//
// fft.spectrum(samplesBuffer, spectrum);
//
// fft.getRealPart(realBuffer);
// fft.getImagPart(imagBuffer);
// short[] re = new short[512];
// short[] im = new short[512];
// float[] sp = new float[513];
// realBuffer.position(0);
// realBuffer.get(re);
// imagBuffer.position(0);
// imagBuffer.get(im);
// spectrum.position(0);
// spectrum.get(sp);
//
// for (int i = 0; i < 30; i++) {
// System.out.println(sp[i]);
// }
// }

