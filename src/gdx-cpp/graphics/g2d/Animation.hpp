
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

#ifndef GDX_CPP_GRAPHICS_G2D_ANIMATION_HPP_
#define GDX_CPP_GRAPHICS_G2D_ANIMATION_HPP_
#include <vector>

#include "TextureRegion.hpp"

namespace gdx {

class Animation {
public:
	const static int NORMAL = 0;
	const static int REVERSED = 1;
	const static int LOOP = 2;
	const static int LOOP_REVERSED = 3;
	const static int LOOP_PINGPONG = 4;
	const static int LOOP_RANDOM = 5;
	
    Animation (float frameDuration, const std::vector<TextureRegion>& keyFrames);
	Animation (float frameDuration, const std::vector<TextureRegion>& keyFrames, int playType);
	
    const TextureRegion& getKeyFrame(float stateTime, bool looping);
	const TextureRegion& getKeyFrame(float stateTime);
	int getKeyFrameIndex(float stateTime);
	void setPlayMode(int playMode);
	bool isAnimationFinished(float stateTime) const;
    
    float frameDuration;
	float animationDuration;
protected:
    std::vector<TextureRegion> keyFrames;

private:
	int playMode;
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_ANIMATION_HPP_
