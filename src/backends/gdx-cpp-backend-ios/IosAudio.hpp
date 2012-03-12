/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 */

#ifndef gdx_cpp_IosAudio_hpp
#define gdx_cpp_IosAudio_hpp

#include <gdx-cpp/Audio.hpp>
#include <gdx-cpp/files/FileHandle.hpp>

namespace gdx_cpp {
namespace backends {
namespace ios {
            
class IosAudio : public gdx_cpp::Audio {
public:        
    virtual gdx_cpp::audio::AudioDevice * newAudioDevice (int samplingRate, bool isMono);
    virtual gdx_cpp::audio::AudioRecorder * newAudioRecoder (int samplingRate, bool isMono);
    
    virtual gdx_cpp::audio::Sound * newSound (const ref_ptr_maker< gdx_cpp::files::FileHandle >::type fileHandle);
    virtual gdx_cpp::audio::Music * newMusic (const ref_ptr_maker< gdx_cpp::files::FileHandle >::type file);
};

}       
}
}


#endif
