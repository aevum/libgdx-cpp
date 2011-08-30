
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

#include "Mpg123Decoder.hpp"
#include <vector>
#include <string>
#include "mpg123/mpg123.h"
#include <stdio.h>
#include <string.h>
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/Application.hpp"

using namespace gdx_cpp::audio::io;


struct Mp3File
{
        mpg123_handle* handle;
        int channels;
        long rate;
        float length;
        size_t buffer_size;
        unsigned char* buffer;
        int leftSamples;
        int offset;
};

Mpg123Decoder::Mpg123Decoder (std::string filename) {
    handle = openFile(filename);
    if (handle == NULL)
    {
      gdx_cpp::Gdx::app->error("GDX-CPP::AUDIO::IO Mpg123Decoder.cpp") << "couldn't open file '" << filename << "'";
    }
}

Mpg123Decoder::~Mpg123Decoder () {
  dispose();
}

int Mpg123Decoder::readSamples (std::vector< short >& samples) {
    int read = readSamples(handle, samples, samples.capacity());
//     samples.position(0);
    return read;
}

int Mpg123Decoder::skipSamples (int numSamples) {
    return skipSamples(handle, numSamples);
}

int Mpg123Decoder::getNumChannels () {
    return getNumChannels(handle);
}

int Mpg123Decoder::getRate () {
    return getRate(handle);
}

float Mpg123Decoder::getLength () {
    return getLength(handle);
}

void Mpg123Decoder::dispose () {
    closeFile(handle);
}

void cleanup( mpg123_handle *handle )
{
        mpg123_close(handle);
        mpg123_delete(handle);
        mpg123_exit();
}

Mp3File* Mpg123Decoder::openFile(std::string file)
{
        mpg123_handle *mh = NULL;
        int  channels = 0, encoding = 0;
        long rate = 0;
        int  err  = MPG123_OK;

        err = mpg123_init();
        const char* fileString =file.c_str();
        if( err != MPG123_OK || (mh = mpg123_new(NULL, &err)) == NULL
                        || mpg123_open(mh, fileString) != MPG123_OK
                        || mpg123_getformat(mh, &rate, &channels, &encoding) != MPG123_OK )
        {
                fprintf( stderr, "Trouble with mpg123: %s\n",
                                mh==NULL ? mpg123_plain_strerror(err) : mpg123_strerror(mh) );
                cleanup(mh);
                return 0;
        }

        if(encoding != MPG123_ENC_SIGNED_16)
        { /* Signed 16 is the default output format anyways; it would actually by only different if we forced it.
                      So this check is here just for this explanation. */
                cleanup(mh);
                return 0;
        }
        /* Ensure that this output format will not change (it could, when we allow it). */
        mpg123_format_none(mh);
        mpg123_format(mh, rate, channels, encoding);

        size_t buffer_size = mpg123_outblock( mh );
        unsigned char* buffer = (unsigned char*)malloc(buffer_size);
        size_t done = 0;
        int samples = 0;

        Mp3File* mp3 = new Mp3File();
        mp3->handle = mh;
        mp3->channels = channels;
        mp3->rate = rate;
        mp3->buffer = buffer;
        mp3->buffer_size = buffer_size;
        int length = mpg123_length( mh );
        if( length == MPG123_ERR )
                mp3->length = 0;
        else
                mp3->length = length / rate;

        return mp3;


}

static inline int readBuffer( Mp3File* mp3 )
{
        size_t done = 0;
        int err = mpg123_read( mp3->handle, mp3->buffer, mp3->buffer_size, &done );

        mp3->leftSamples = done / 2;
        mp3->offset = 0;

        if( err != MPG123_OK )
                return 0;
        else
                return done;
}

/*
 * Class:     com_badlogic_gdx_audio_io_Mpg123Decoder
 * Method:    readSamples
 * Signature: (ILjava/nio/ShortBuffer;I)I
 */
int Mpg123Decoder::readSamples(Mp3File* mp3, std::vector<short>& buffer, int numSamples)
{
        short* target = (short*)&buffer[0];

        int idx = 0;
        while( idx != numSamples )
        {
                if( mp3->leftSamples > 0 )
                {
                        short* src = ((short*)mp3->buffer) + mp3->offset;
                        for( ; idx < numSamples && mp3->offset < mp3->buffer_size / 2; mp3->leftSamples--, mp3->offset++, target++, src++, idx++ )
                        {
                                *target = *src;
                        }
                }
                else
                {
                        int result = readBuffer( mp3 );
                        if( result == 0 )
                                return 0;
                }

        }

        if( idx > numSamples )
                return 0;

        return idx;
}

int Mpg123Decoder::skipSamples(Mp3File* mp3, int numSamples)
{
        int idx = 0;
        while( idx != numSamples )
        {
                if( mp3->leftSamples > 0 )
                {
                        for( ; idx < numSamples && mp3->offset < mp3->buffer_size / 2; mp3->leftSamples--, mp3->offset++, idx++ );
                }
                else
                {
                        int result = readBuffer( mp3 );
                        if( result == 0 )
                                return 0;
                }

        }

        if( idx > numSamples )
                return 0;

        return idx;
}

/*
 * Class:     com_badlogic_gdx_audio_io_Mpg123Decoder
 * Method:    getNumChannels
 * Signature: (J)I
 */
int Mpg123Decoder::getNumChannels(Mp3File* mp3)
{
        return mp3->channels;
}

/*
 * Class:     com_badlogic_gdx_audio_io_Mpg123Decoder
 * Method:    getRate
 * Signature: (J)I
 */
int Mpg123Decoder::getRate(Mp3File* mp3)
{
        return mp3->rate;
}

/*
 * Class:     com_badlogic_gdx_audio_io_Mpg123Decoder
 * Method:    closeFile
 * Signature: (J)V
 */
void Mpg123Decoder::closeFile(Mp3File* mp3)
{
        free(mp3->buffer);
        cleanup(mp3->handle);
}

float Mpg123Decoder::getLength(Mp3File* mp3)
{
        return mp3->length;
}

