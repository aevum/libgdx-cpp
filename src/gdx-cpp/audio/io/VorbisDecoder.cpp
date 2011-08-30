
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

#include "VorbisDecoder.hpp"
#include "vorbis/ogg.h"
#include "vorbis/ivorbiscodec.h"
#include "vorbis/ivorbisfile.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/Application.hpp"

using namespace gdx_cpp::audio::io;

struct OggFile
{
    OggVorbis_File* ogg;
    int channels;
    int rate;
    float length;
    int bitstream;
};

VorbisDecoder::VorbisDecoder (std::string filename) {
    handle = openFile(filename);
    if (handle == NULL)
    {
      gdx_cpp::Gdx::app->error("GDX-CPP::AUDIO::IO VorbisDecoder.cpp") << "couldn't open file '" << filename << "'";
    }
}

VorbisDecoder::~VorbisDecoder () {
  dispose();
}

void VorbisDecoder::dispose () {
    closeFile(handle);
}

float VorbisDecoder::getLength () {
    return getLength(handle);
}

int VorbisDecoder::getNumChannels () {
    return getNumChannels(handle);
}

int VorbisDecoder::getRate () {
    return getRate(handle);
}

int VorbisDecoder::readSamples (std::vector<short>& samples) {
    int read = readSamples(handle, samples, samples.capacity());//TODO check capacity
//     samples.position(0);
    return read;
}

int VorbisDecoder::skipSamples (int numSamples) {
    return skipSamples(handle, numSamples);
}

OggFile* VorbisDecoder::openFile(std::string filename)
{
    OggVorbis_File* ogg = new OggVorbis_File();
    FILE* file = fopen(filename.c_str(), "rb" );

    if ( file == 0 )
    {
        delete ogg;
        return 0;
    }

    if ( ov_open( file, ogg, NULL, 0 ) != 0 )
    {
        fclose( file );
        delete ogg;
        return 0;
    }

    vorbis_info *info = ov_info( ogg, -1 );
    int channels = info->channels;
    int rate = info->rate;
    float length = (float)ov_time_total(ogg, -1 ) / 1000.0f;

    OggFile* oggFile = new OggFile();
    oggFile->ogg = ogg;
    oggFile->channels = channels;
    oggFile->rate = rate;
    oggFile->length = length;

    return oggFile;
}

int VorbisDecoder::getNumChannels(OggFile* file)
{
    return file->channels;
}

int VorbisDecoder::getRate(OggFile* file)
{
    return file->rate;
}

float VorbisDecoder::getLength(OggFile* file)
{
    return file->length;
}

int VorbisDecoder::readSamples(OggFile* file, std::vector<short>& samplesVector, int numSamples)
{
    char* samples = (char*)&samplesVector[0];

    int toRead = 2 * numSamples;
    int read = 0;

    while ( read != toRead )
    {
        int ret = ov_read( file->ogg, samples + read, toRead - read, &file->bitstream );
        if ( ret == OV_HOLE )
            continue;
        if ( ret == OV_EBADLINK || ret == OV_EINVAL || ret == 0 )
            return read / 2;
        read+=ret;
    }

    return read / 2;
}

static char buffer[10000];

int VorbisDecoder::skipSamples(OggFile* file, int numSamples)
{
    int toRead = 2 * numSamples;
    int read = 0;

    while ( read != toRead )
    {
        int ret = ov_read( file->ogg, buffer, (toRead - read)>10000?10000:(toRead-read), &file->bitstream );
        if ( ret == OV_HOLE )
            continue;
        if ( ret == OV_EBADLINK || ret == OV_EINVAL || ret == 0 )
            return read / 2;
        read+=ret;
    }

    return read / 2;
}

/*
 * Class:     com_badlogic_gdx_audio_io_VorbisDecoder
 * Method:    closeFile
 * Signature: (J)V
 */
void VorbisDecoder::closeFile(OggFile* file)
{
    ov_clear(file->ogg);
    free(file->ogg);
    free(file);
}
