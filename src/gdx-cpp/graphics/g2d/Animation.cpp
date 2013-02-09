
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

Animation::Animation( float frameDuration, const std::vector< TextureRegion >& keyFrames )
 : frameDuration(frameDuration),
keyFrames(keyFrames)
{
}


const TextureRegion& Animation::getKeyFrame (float stateTime, bool looping) {
    int frameNumber = (int)(stateTime / frameDuration);

    if (!looping) {
        frameNumber = std::min((float) keyFrames.size() - 1, (float) frameNumber);
    } else {
        frameNumber = frameNumber % keyFrames.size();
    }
    return keyFrames[frameNumber];
}

