
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

#include "Image.hpp"

using namespace gdx;

void Image::draw (SpriteBatch& batch, float parentAlpha) {
    if (region->getTexture() != NULL) {
        batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);
        if (scaleX == 1 && scaleY == 1 && rotation == 0)
            batch.draw(*region, x, y, width, height);
        else
            batch.draw(*region, x, y, originX, originY, width, height, scaleX, scaleY, rotation);
    }
}

bool Image::touchDown (float x,float y,int pointer) {
    return x > 0 && y > 0 && x < width && y < height;
}

void Image::touchUp (float x,float y,int pointer) {
}

void Image::touchDragged (float x,float y,int pointer) {
}

Actor* Image::hit (float x,float y) {
    if (x > 0 && x < width) if (y > 0 && y < height)
        return this;

    return NULL;
}

Image::Image (const std::string& name)
 : Actor(name)
{    
}

Image::Image (const std::string& name,const Texture& texture)
: Actor(name)
, originX(texture.getWidth() / 2.0f)
, originY(originY = texture.getHeight() / 2.0f)
, width(texture.getWidth())
, height(texture.getHeight())
, region(TextureRegion::newFromTexture(texture))
{
}

Image::Image (const std::string& name,const TextureRegion& region)
: Actor(name)
, originX(texture.getWidth() / 2.0f)
, originY(originY = texture.getHeight() / 2.0f)
, width(texture.getWidth())
, height(texture.getHeight())
, region(TextureRegion::newFromRegion(region))
{
    super(name);
    width = Math.abs(region.getRegionWidth());
    height = Math.abs(region.getRegionHeight());
    originX = width / 2.0f;
    originY = height / 2.0f;
    this.region = new TextureRegion(region);
}

