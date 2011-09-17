#ifndef __ogg_h__
#define __ogg_h__

#include <string>
#include <iostream>

#include <AL/al.h>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

#include "gdx-cpp/utils/Buffer.hpp"


#define BUFFER_SIZE (4096 * 4)

namespace gdx_cpp {
namespace backends {

namespace nix {


class LinuxOggInputStream
{
public:

    void open(std::string path);
    void release();
    int read(char* pcm, int max);
    int getChannels();
    int getSampleRate();

protected:

private:

    FILE*           oggFile;
    OggVorbis_File  oggStream;
    vorbis_info*    vorbisInfo;
    vorbis_comment* vorbisComment;

    ALuint buffers[2];
    ALuint source;
    ALenum format;


};

}

}

}


#endif // __ogg_h__
