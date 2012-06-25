
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

#include "EmptyNinePatch.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"
#include "gdx-cpp/graphics/Texture.hpp"
#include "TextureRegion.hpp"

using namespace gdx;

EmptyNinePatch* EmptyNinePatch::instance = 0;
TextureRegion::ptr EmptyNinePatch::region;
std::vector<TextureRegion::ptr> EmptyNinePatch::emptyPatches;

EmptyNinePatch::EmptyNinePatch() : NinePatch(emptyPatches)
{
}


EmptyNinePatch::~EmptyNinePatch(){
  delete instance;
}
  
class EmpytTextureRegion : public TextureRegion {
public :
    EmpytTextureRegion(Texture::ptr tex) : TextureRegion(tex) { }

    int getRegionWidth () {
        return 0;
    }

    int getRegionHeight () {
        return 0;
    }
};
  
EmptyNinePatch& EmptyNinePatch::getInstance () {
    if (instance == NULL) {
        // This is kind of gross...
        Texture::ptr texture(new Texture(2, 2, Pixmap::Format::RGBA8888, Pixmap::Gdx2d));
 

        region = TextureRegion::ptr(new EmpytTextureRegion(texture));
        emptyPatches.reserve(9);
        emptyPatches[0] = region;
        emptyPatches[1] = region;
        emptyPatches[2] = region;
        emptyPatches[3] = region;
        emptyPatches[4] = region;
        emptyPatches[5] = region;
        emptyPatches[6] = region;
        emptyPatches[7] = region;
        emptyPatches[8] = region;
        
        instance = new EmptyNinePatch();
    }
    return *instance;
}

int EmptyNinePatch::getRegionWidth () {
    return 0;
}

int EmptyNinePatch::getRegionHeight () {
    return 0;
}

TextureRegion::ptr EmptyNinePatch::getRegion () {
    getInstance();
    return region;
}

void EmptyNinePatch::draw (const SpriteBatch& batch,float x,float y,float width,float height) {
}

