
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

#include "Animator.hpp"

using namespace gdx;

void Animator::setAnimation (const Animation& anim,const WrapMode& mode) {
    mCurrentAnim = anim;
    mWrapMode = mode;

    mAnimPos = mFrameDelta = 0.f;
    mCurrentFrameIdx = -1;
    mNextFrameIdx = -1;

    if (mCurrentAnim != null) {
        mAnimLen = mCurrentAnim.getLength();
    }
}

Animation& Animator::getCurrentAnimation () {
    return mCurrentAnim;
}

WrapMode& Animator::getCurrentWrapMode () {
    return mWrapMode;
}

void Animator::update (float dt) {
    if (mCurrentAnim != null) {
        if (mWrapMode != WrapMode.SingleFrame) {
            mAnimPos += dt;
            if (mAnimPos > mAnimLen) {
                if (mWrapMode == WrapMode.Loop) {
                    mAnimPos = 0.f;
                } else if (mWrapMode == WrapMode.Clamp) {
                    mAnimPos = mAnimLen;
                }
            }
        }
        // select the frames
        float animPos = mAnimPos / mAnimLen;
        int numFrames = mCurrentAnim.getNumFrames();

        int currentFrameIdx = Math.min(numFrames - 1, (int)(animPos * (float)numFrames));

        if (currentFrameIdx != mCurrentFrameIdx) {
            if (currentFrameIdx < numFrames - 1) {
                mNextFrameIdx = currentFrameIdx + 1;
            } else {
                switch (mWrapMode) {
                case Loop:
                case SingleFrame:
                    mNextFrameIdx = 0;
                    break;
                case Clamp:
                    mNextFrameIdx = currentFrameIdx;
                    break;
                }
            }

            mFrameDelta = 0.f;
            mCurrentFrameIdx = currentFrameIdx;
        }

        mFrameDelta += dt;

        setInterpolationFrames();

        interpolate();
    }
}

