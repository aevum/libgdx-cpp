
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

#include "MD5AnimationInfo.hpp"

using namespace gdx_cpp::graphics::g3d::loaders::md5;

void MD5AnimationInfo::reset () {
    reset(maxFrame, maxTime);
}

void MD5AnimationInfo::reset (int maxFrame,float maxTime) {
    this.maxFrame = maxFrame;
    this.maxTime = maxTime;
    this.currFrame = 0;
    this.nextFrame = 1;
    this.lastTime = 0;
}

void MD5AnimationInfo::update (float delta) {
    lastTime += delta;

    if (lastTime >= maxTime) {
        currFrame++;
        nextFrame++;
        lastTime = 0;

        if (currFrame >= maxFrame) currFrame = 0;
        if (nextFrame >= maxFrame) nextFrame = 0;
    }
}

int MD5AnimationInfo::getCurrentFrame () {
    return currFrame;
}

int MD5AnimationInfo::getNextFrame () {
    return nextFrame;
}

float MD5AnimationInfo::getInterpolation () {
    return lastTime / maxTime;
}

