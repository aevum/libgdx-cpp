
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

using namespace gdx_cpp::scenes::scene2d::ui;

void Image::layout () {
    if (!invalidated) return;
    invalidated = false;

    float regionWidth, regionHeight;
    if (patch != null) {
        regionWidth = patch.getTotalWidth();
        regionHeight = patch.getTotalHeight();
    } else if (region != null) {
        regionWidth = region.getRegionWidth();
        regionHeight = region.getRegionHeight();
    } else
        return;

    switch (scaling) {
    case fill: {
        float widgetRatio = height / width;
        float regionRatio = regionHeight / regionWidth;
        float scale = regionRatio > widgetRatio ? width / regionWidth : height / regionHeight;
        imageWidth = regionWidth * scale;
        imageHeight = regionHeight * scale;
        break;
    }
    case fit: {
        float widgetRatio = height / width;
        float regionRatio = regionHeight / regionWidth;
        float scale = regionRatio < widgetRatio ? width / regionWidth : height / regionHeight;
        imageWidth = regionWidth * scale;
        imageHeight = regionHeight * scale;
        break;
    }
    case stretch:
        imageWidth = width;
        imageHeight = height;
        break;
    case stretchX:
        imageWidth = width;
        imageHeight = regionHeight;
        break;
    case stretchY:
        imageWidth = regionWidth;
        imageHeight = height;
        break;
    case none:
        imageWidth = regionWidth;
        imageHeight = regionHeight;
        break;
    }

    if ((align & Align.LEFT) != 0)
        imageX = 0;
    else if ((align & Align.RIGHT) != 0)
        imageX = (int)(width - imageWidth);
    else
        imageX = (int)(width / 2 - imageWidth / 2);

    if ((align & Align.TOP) != 0)
        imageY = (int)(height - imageHeight);
    else if ((align & Align.BOTTOM) != 0)
        imageY = 0;
    else
        imageY = (int)(height / 2 - imageHeight / 2);
}

void Image::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    if (invalidated) layout();
    batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);
    if (patch != null)
        patch.draw(batch, x + imageX, y + imageY, imageWidth, imageHeight);
    else if (region != null) //
        batch.draw(region, x + imageX, y + imageY, imageWidth, imageHeight);
}

void Image::setRegion (const gdx_cpp::graphics::g2d::TextureRegion& region) {
    this.region = region;
    patch = null;
    invalidate();
}

void Image::setPatch (const gdx_cpp::graphics::g2d::NinePatch& patch) {
    this.patch = patch;
    region = null;
    invalidate();
}

float Image::getMinWidth () {
    return 0;
}

float Image::getMinHeight () {
    return 0;
}

float Image::getPrefWidth () {
    return region.getRegionWidth();
}

float Image::getPrefHeight () {
    return region.getRegionHeight();
}

bool Image::touchDown (float x,float y,int pointer) {
    return false;
}

void Image::touchUp (float x,float y,int pointer) {
}

void Image::touchDragged (float x,float y,int pointer) {
}

Image::Image (const gdx_cpp::graphics::g2d::TextureRegion& region) {
    this(region, Scaling.none, null);
}

Image::Image (const gdx_cpp::graphics::g2d::TextureRegion& region,const Scaling& scaling) {
    this(region, scaling, null);
}

Image::Image (const gdx_cpp::graphics::g2d::TextureRegion& region,const Scaling& scaling,int align) {
    this(region, scaling, align, null);
}

Image::Image (const gdx_cpp::graphics::g2d::TextureRegion& region,const Scaling& scaling,const std::string& name) {
    this(region, scaling, Align.CENTER, null);
}

Image::Image (const gdx_cpp::graphics::g2d::TextureRegion& region,const Scaling& scaling,int align,const std::string& name) {
    setRegion(region);
    this.scaling = scaling;
    this.align = align;
}

Image::Image (const gdx_cpp::graphics::g2d::NinePatch& patch) {
    this(patch, Scaling.none, null);
}

Image::Image (const gdx_cpp::graphics::g2d::NinePatch& patch,const Scaling& scaling) {
    this(patch, scaling, null);
}

Image::Image (const gdx_cpp::graphics::g2d::NinePatch& patch,const Scaling& scaling,int align) {
    this(patch, scaling, align, null);
}

Image::Image (const gdx_cpp::graphics::g2d::NinePatch& patch,const Scaling& scaling,const std::string& name) {
    this(patch, scaling, Align.CENTER, null);
}

Image::Image (const gdx_cpp::graphics::g2d::NinePatch& patch,const Scaling& scaling,int align,const std::string& name) {
    setPatch(patch);
    this.scaling = scaling;
    this.align = align;
}

