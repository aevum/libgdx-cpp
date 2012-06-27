
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

#include "MD5Animator.hpp"

using namespace gdx::g3d::md5;

void MD5Animator::setSkeleton (const MD5Joints& skeleton) {
    mSkeleton = skeleton;
}

MD5Joints& MD5Animator::getSkeleton () {
    return mSkeleton;
}

void MD5Animator::setAnimation (const gdx::g3d::Animation& anim,const WrapMode& wrapMode) {
    super.setAnimation(anim, wrapMode);

    if (anim != null) {
        mCurrentFrame = mSkeleton = mNextFrame = ((MD5Animation)anim).frames[0];
    }
}

void MD5Animator::setInterpolationFrames () {
    mCurrentFrame = ((MD5Animation)mCurrentAnim).frames[mCurrentFrameIdx];
    mNextFrame = ((MD5Animation)mCurrentAnim).frames[mNextFrameIdx];
}

void MD5Animator::interpolate () {
    MD5Animation.interpolate(mCurrentFrame, mNextFrame, mSkeleton, mFrameDelta);
}

