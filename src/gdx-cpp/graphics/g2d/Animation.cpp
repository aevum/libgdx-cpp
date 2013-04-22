
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

#include <algorithm>

#include "Animation.hpp"
#include "gdx-cpp/graphics/g2d/TextureRegion.hpp"

using namespace gdx;

Animation::Animation ( float frameDuration, const std::vector< TextureRegion >& keyFrames )
    : Animation ( frameDuration, keyFrames, NORMAL )
{
}

Animation::Animation ( float frameDuration, const std::vector< TextureRegion >& keyFrames, int playType )
    : frameDuration ( frameDuration ),
      animationDuration ( keyFrames.size() * frameDuration ),
      keyFrames ( keyFrames ),
      playMode ( playType )
{

}


const TextureRegion& Animation::getKeyFrame ( float stateTime, bool looping )
{
    if ( looping && ( playMode == NORMAL || playMode == REVERSED ) ) {
        if ( playMode == NORMAL ) {
            playMode = LOOP;
        } else {
            playMode = LOOP_REVERSED;
        }
    } else if ( !looping && ! ( playMode == NORMAL || playMode == REVERSED ) ) {
        if ( playMode == LOOP_REVERSED ) {
            playMode = REVERSED;
        } else {
            playMode = LOOP;
        }
    }
    return keyFrames[ getKeyFrameIndex ( stateTime )];
}

const TextureRegion& Animation::getKeyFrame ( float stateTime )
{
    int frameNumber = getKeyFrameIndex ( stateTime );
    return keyFrames[frameNumber];
}

int Animation::getKeyFrameIndex ( float stateTime )
{
    unsigned int frameNumber = ( int ) ( stateTime / frameDuration );
    if ( keyFrames.size() == 1 ) {
        return 0;
    }
    switch ( playMode ) {
    case NORMAL: {
        frameNumber = std::min ( keyFrames.size() - 1, ( size_t ) frameNumber );
    }
    break;
    case LOOP: {
        frameNumber = frameNumber % keyFrames.size();
    }
    break;
    case LOOP_PINGPONG: {
        frameNumber = frameNumber % ( ( keyFrames.size() * 2 ) - 2 );
        if ( frameNumber >= keyFrames.size() ) {
            frameNumber = keyFrames.size() - 2 - ( frameNumber - keyFrames.size() );
        }
    }
    break;
    case LOOP_RANDOM: {
        frameNumber = rand() % ( keyFrames.size() - 1 );
    }
    break;
    case REVERSED: {
        frameNumber = std::max ((int) keyFrames.size() - frameNumber - 1, 0u );
    }
    break;
    case LOOP_REVERSED: {
        frameNumber = frameNumber % keyFrames.size();
        frameNumber = keyFrames.size() - frameNumber - 1;
    }
    break;

    default: {
        // play normal otherwise
        frameNumber = std::min ( keyFrames.size() - 1, ( size_t ) frameNumber );
    }
    break;
    }

    return frameNumber;
}

void Animation::setPlayMode ( int playMode )
{
    this->playMode = playMode;
}

bool Animation::isAnimationFinished ( float stateTime ) const
{
    if ( playMode != NORMAL && playMode != REVERSED ) {
        return false;
    }
    unsigned int frameNumber = ( int ) ( stateTime / frameDuration );
    return keyFrames.size() - 1 < frameNumber;
}



