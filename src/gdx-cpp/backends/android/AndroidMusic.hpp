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
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 *  @author aevum team
 */

#ifndef GDX_CPP_BACKENDS_ANDROID_ANDROIDMUSIC_HPP
#define GDX_CPP_BACKENDS_ANDROID_ANDROIDMUSIC_HPP

#include <gdx-cpp/audio/Music.hpp>
#include <jni.h>

namespace gdx {

namespace android {

class AndroidMusic : public Music
{
public:
    AndroidMusic(jobject musicObj);
    void dispose();
    float getPosition();
    bool isLooping();
    bool isPlaying();
    bool isPaused();
    void pause();
    void play();
    void setLooping(bool isLooping);
    void setVolume(float volume);
    void stop();
    virtual float getVolume() const;
    ~AndroidMusic();
    
protected:
    jobject jniMusicObj;
    
    jmethodID disposeJNI;
    jmethodID getPositionJNI;
    jmethodID isLoopingJNI;
    jmethodID isPlayingJNI;
    jmethodID isPausedJNI;
    jmethodID pauseJNI;
    jmethodID playJNI;
    jmethodID setLoopingJNI;
    jmethodID setVolumeJNI;
    jmethodID stopJNI;
    jmethodID getVolumeJNI;
};

}

}

#endif // GDX_CPP_BACKENDS_ANDROID_ANDROIDMUSIC_HPP
