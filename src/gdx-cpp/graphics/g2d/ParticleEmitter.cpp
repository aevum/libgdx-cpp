
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

#include "gdx-cpp/gl.hpp"
#include <ctype.h>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>

#include "ParticleEmitter.hpp"
#include "SpriteBatch.hpp"
#include "gdx-cpp/Log.hpp"
#include "gdx-cpp/graphics/Texture.hpp"
#include "gdx-cpp/graphics/g2d/Sprite.hpp"
#include "gdx-cpp/math/MathUtils.hpp"

using namespace gdx;


ParticleEmitter::ParticleEmitter(): duration(1),
durationTimer(0),
accumulator(0),
minParticleCount(0),
maxParticleCount(4),
x(0),
y(0),
activeCount(0),
firstUpdate(false),
flipX(false),
flipY(false),
updateFlags(0),
allowCompletionVar(false),
emission(0),
emissionDiff(0),
emissionDelta(0),
lifeOffset(0),
lifeOffsetDiff(0),
life(0),
lifeDiff(0),
spawnWidth(0),
spawnWidthDiff(0),
spawnHeight(0),
spawnHeightDiff(0),
delay(0),
delayTimer(0),
attached(false),
continuous(false),
aligned(false),
behind(false),
additive(true)
{
    initialize();
}

ParticleEmitter::ParticleEmitter(std::istream& reader): duration(1),
durationTimer(0),
accumulator(0),
minParticleCount(0),
maxParticleCount(4),
x(0),
y(0),
activeCount(0),
firstUpdate(false),
flipX(false),
flipY(false),
updateFlags(0),
allowCompletionVar(false),
emission(0),
emissionDiff(0),
emissionDelta(0),
lifeOffset(0),
lifeOffsetDiff(0),
life(0),
lifeDiff(0),
spawnWidth(0),
spawnWidthDiff(0),
spawnHeight(0),
spawnHeightDiff(0),
delay(0),
delayTimer(0),
attached(false),
continuous(false),
aligned(false),
behind(false),
additive(true)
{
    initialize();
    load(reader);
}

ParticleEmitter::ParticleEmitter(ParticleEmitter& emitter): duration(1),
durationTimer(0),
accumulator(0),
minParticleCount(0),
maxParticleCount(4),
x(0),
y(0),
activeCount(0),
firstUpdate(false),
flipX(false),
flipY(false),
updateFlags(0),
allowCompletionVar(false),
emission(0),
emissionDiff(0),
emissionDelta(0),
lifeOffset(0),
lifeOffsetDiff(0),
life(0),
lifeDiff(0),
spawnWidth(0),
spawnWidthDiff(0),
spawnHeight(0),
spawnHeightDiff(0),
delay(0),
delayTimer(0),
attached(false),
continuous(false),
aligned(false),
behind(false),
additive(true)
{
    sprite = emitter.sprite;
    name = emitter.name;
    setMaxParticleCount(emitter.maxParticleCount);
    minParticleCount = emitter.minParticleCount;
    delayValue.load(emitter.delayValue);
    durationValue.load(emitter.durationValue);
    emissionValue.load(emitter.emissionValue);
    lifeValue.load(emitter.lifeValue);
    lifeOffsetValue.load(emitter.lifeOffsetValue);
    scaleValue.load(emitter.scaleValue);
    rotationValue.load(emitter.rotationValue);
    velocityValue.load(emitter.velocityValue);
    angleValue.load(emitter.angleValue);
    windValue.load(emitter.windValue);
    gravityValue.load(emitter.gravityValue);
    transparencyValue.load(emitter.transparencyValue);
    tintValue.load(emitter.tintValue);
    xOffsetValue.load(emitter.xOffsetValue);
    yOffsetValue.load(emitter.yOffsetValue);
    spawnWidthValue.load(emitter.spawnWidthValue);
    spawnHeightValue.load(emitter.spawnHeightValue);
    spawnShapeValue.load(emitter.spawnShapeValue);
    attached = emitter.attached;
    continuous = emitter.continuous;
    aligned = emitter.aligned;
    behind = emitter.behind;
    additive = emitter.additive;
}



ParticleEmitter::~ParticleEmitter()
{
    for (unsigned int i = 0; i < particles.size(); i ++)
    {
        if (particles[i] != NULL)
        {
          delete particles[i];
        }
    }
}

void ParticleEmitter::initialize () {
    durationValue.setAlwaysActive(true);
    emissionValue.setAlwaysActive(true);
    lifeValue.setAlwaysActive(true);
    scaleValue.setAlwaysActive(true);
    transparencyValue.setAlwaysActive(true);
    spawnShapeValue.setAlwaysActive(true);
    spawnWidthValue.setAlwaysActive(true);
    spawnHeightValue.setAlwaysActive(true);
}

void ParticleEmitter::setMaxParticleCount (int maxParticleCount) {
    this->maxParticleCount = maxParticleCount;
    active.clear();
    active.resize(maxParticleCount);
    activeCount = 0;
    for (unsigned i = 0 ; i < particles.size(); i++)
    {
        if (particles[i] != NULL)
        {
            delete particles[i];
        }
    }
    particles.clear();
    particles.resize(maxParticleCount);
}

int ParticleEmitter::nextClearBit()
{
    for (unsigned i =0; i< active.size(); i++)
    {
        if (!active[i])
        {
            return i;
        }
    }
    return -1;
}

void ParticleEmitter::addParticle () {
    int activeCount = this->activeCount;
    if (activeCount == maxParticleCount) return;
    int index = nextClearBit();
    activateParticle(index);
    this->active[index] = true;
    this->activeCount = activeCount + 1;
}

void ParticleEmitter::addParticles (int count) {
    count = std::min(count, maxParticleCount - activeCount);
    if (count == 0) return;
    for (unsigned int i = 0; i < count; i++) {
        int index = nextClearBit();
        activateParticle(index);
        this->active[index] = true;
    }
    this->activeCount += count;
}

void ParticleEmitter::update (float delta) {
    accumulator += std::min(delta * 1000, 250.f);
    if (accumulator < 1) return;
    int deltaMillis = (int)accumulator;
    accumulator -= deltaMillis;

    int activeCount = this->activeCount;
    for (unsigned index = 0; index < active.size(); index++) {
        if (active[index])
        {
            if (!updateParticle(index, delta, deltaMillis)) {
                active[index] = false;
                activeCount--;
            }
        }
    }
    this->activeCount = activeCount;

    if (delayTimer < delay) {
        delayTimer += deltaMillis;
        return;
    }

    if (firstUpdate) {
        firstUpdate = false;
        addParticle();
    }

    if (durationTimer < duration)
        durationTimer += deltaMillis;
    else {
        if (!continuous || allowCompletionVar) return;
        restart();
    }

    emissionDelta += deltaMillis;
    float emissionTime = emission + emissionDiff * emissionValue.getScale(durationTimer / (float)duration);
    if (emissionTime > 0) {
        emissionTime = 1000 / emissionTime;
        if (emissionDelta >= emissionTime) {
            int emitCount = (int)(emissionDelta / emissionTime);
            emitCount = std::min(emitCount, maxParticleCount - activeCount);
            emissionDelta -= emitCount * emissionTime;
            emissionDelta = std::fmod((float) emissionDelta,  emissionTime);
            addParticles(emitCount);
        }
    }
    if (activeCount < minParticleCount) addParticles(minParticleCount - activeCount);
}

void ParticleEmitter::draw (SpriteBatch& spriteBatch) {
    if (additive) spriteBatch.setBlendFunction(GL10::GL_SRC_ALPHA, GL10::GL_ONE);

    for (unsigned index = 0; index < active.size(); index++) {
        if (active[index])
        {
            particles[index]->draw(spriteBatch);
        }
    }

    if (additive) spriteBatch.setBlendFunction(GL10::GL_SRC_ALPHA, GL10::GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleEmitter::draw (SpriteBatch& spriteBatch,float delta) {
    accumulator += std::min(delta * 1000, 250.f);
    if (accumulator < 1) {
        draw(spriteBatch);
        return;
    }
    int deltaMillis = (int)accumulator;
    accumulator -= deltaMillis;

    if (additive) spriteBatch.setBlendFunction(GL10::GL_SRC_ALPHA, GL10::GL_ONE);

    for (unsigned int index = 0; index < active.size(); index++) {
        if (active[index])
        {
            if (updateParticle(index, delta, deltaMillis))
            {
                particles[index]->draw(spriteBatch);
            }
            else
            {
                active[index] = false;
                activeCount--;
            }
        }
    }

    if (additive) spriteBatch.setBlendFunction(GL10::GL_SRC_ALPHA, GL10::GL_ONE_MINUS_SRC_ALPHA);

    if (delayTimer < delay) {
        delayTimer += deltaMillis;
        return;
    }

    if (firstUpdate) {
        firstUpdate = false;
        addParticle();
    }

    if (durationTimer < duration)
        durationTimer += deltaMillis;
    else {
        if (!continuous || allowCompletionVar) return;
        restart();
    }

    emissionDelta += deltaMillis;
    float emissionTime = emission + emissionDiff * emissionValue.getScale(durationTimer / (float)duration);
    if (emissionTime > 0) {
        emissionTime = 1000 / emissionTime;
        if (emissionDelta >= emissionTime) {
            int emitCount = (int)(emissionDelta / emissionTime);
            emitCount = std::min(emitCount, maxParticleCount - activeCount);
            emissionDelta -= emitCount * emissionTime;
            emissionDelta = std::fmod((float)emissionDelta,  emissionTime);
            addParticles(emitCount);
        }
    }
    if (activeCount < minParticleCount) addParticles(minParticleCount - activeCount);
}

void ParticleEmitter::start () {
    firstUpdate = true;
    allowCompletionVar = false;
    restart();
}

void ParticleEmitter::reset () {
    emissionDelta = 0;
    durationTimer = 0;
    start();
}

void ParticleEmitter::restart () {
    delay = delayValue.active ? delayValue.newLowValue() : 0;
    delayTimer = 0;

    durationTimer -= duration;
    duration = durationValue.newLowValue();

    emission = (int)emissionValue.newLowValue();
    emissionDiff = (int)emissionValue.newHighValue();
    if (!emissionValue.isRelative()) emissionDiff -= emission;

    life = (int)lifeValue.newLowValue();
    lifeDiff = (int)lifeValue.newHighValue();
    if (!lifeValue.isRelative()) lifeDiff -= life;

    lifeOffset = lifeOffsetValue.active ? (int)lifeOffsetValue.newLowValue() : 0;
    lifeOffsetDiff = (int)lifeOffsetValue.newHighValue();
    if (!lifeOffsetValue.isRelative()) lifeOffsetDiff -= lifeOffset;

    spawnWidth = (int)spawnWidthValue.newLowValue();
    spawnWidthDiff = (int)spawnWidthValue.newHighValue();
    if (!spawnWidthValue.isRelative()) spawnWidthDiff -= spawnWidth;

    spawnHeight = (int)spawnHeightValue.newLowValue();
    spawnHeightDiff = (int)spawnHeightValue.newHighValue();
    if (!spawnHeightValue.isRelative()) spawnHeightDiff -= spawnHeight;

    updateFlags = 0;
    if (angleValue.active && angleValue.timeline.size() > 1) updateFlags |= UPDATE_ANGLE;
    if (velocityValue.active && velocityValue.active) updateFlags |= UPDATE_VELOCITY;
    if (scaleValue.timeline.size() > 1) updateFlags |= UPDATE_SCALE;
    if (rotationValue.active && rotationValue.timeline.size() > 1) updateFlags |= UPDATE_ROTATION;
    if (windValue.active) updateFlags |= UPDATE_WIND;
    if (gravityValue.active) updateFlags |= UPDATE_GRAVITY;
    if (tintValue.timeline.size() > 1) updateFlags |= UPDATE_TINT;
}

void ParticleEmitter::activateParticle (int index) {
    Particle * particle = particles[index];
    if (particle == NULL) {
        particles[index] = particle = new Particle(sprite);
        particle->flip(flipX, flipY);
    }

    float percent = durationTimer / (float)duration;
    int updateFlags = this->updateFlags;

    float offsetTime = lifeOffset + lifeOffsetDiff * lifeOffsetValue.getScale(percent);
    particle->life = particle->currentLife = life + (int)(lifeDiff * lifeValue.getScale(percent));

    if (velocityValue.active) {
        particle->velocity = velocityValue.newLowValue();
        particle->velocityDiff = velocityValue.newHighValue();
        if (!velocityValue.isRelative()) particle->velocityDiff -= particle->velocity;
    }

    particle->angle = angleValue.newLowValue();
    particle->angleDiff = angleValue.newHighValue();
    if (!angleValue.isRelative()) particle->angleDiff -= particle->angle;
    float angle = 0;
    if ((updateFlags & UPDATE_ANGLE) == 0) {
        angle = particle->angle + particle->angleDiff * angleValue.getScale(0);
        particle->angle = angle;
        particle->angleCos = gdx::cosDeg(angle);
        particle->angleSin = gdx::sinDeg(angle);
    }

    float spriteWidth = sprite->getWidth();
    particle->scale = scaleValue.newLowValue() / spriteWidth;
    particle->scaleDiff = scaleValue.newHighValue() / spriteWidth;
    if (!scaleValue.isRelative()) particle->scaleDiff -= particle->scale;
    if ((updateFlags & UPDATE_SCALE) == 0) particle->setScale(particle->scale + particle->scaleDiff * scaleValue.getScale(0));

    if (rotationValue.active) {
        particle->rotation = rotationValue.newLowValue();
        particle->rotationDiff = rotationValue.newHighValue();
        if (!rotationValue.isRelative()) particle->rotationDiff -= particle->rotation;
        if ((updateFlags & UPDATE_ROTATION) == 0) {
            float rotation = particle->rotation + particle->rotationDiff * rotationValue.getScale(0);
            if (aligned) rotation += angle;
            particle->setRotation(rotation);
        }
    }

    if (windValue.active) {
        particle->wind = windValue.newLowValue();
        particle->windDiff = windValue.newHighValue();
        if (!windValue.isRelative()) particle->windDiff -= particle->wind;
    }

    if (gravityValue.active) {
        particle->gravity = gravityValue.newLowValue();
        particle->gravityDiff = gravityValue.newHighValue();
        if (!gravityValue.isRelative()) particle->gravityDiff -= particle->gravity;
    }

    if ((updateFlags & UPDATE_TINT) == 0) {
        if (particle->tint.size() == 0) particle->tint.resize(3);
        std::vector<float>& temp = tintValue.getColor(0);
        particle->tint[0] = temp[0];
        particle->tint[1] = temp[1];
        particle->tint[2] = temp[2];
    }

    particle->transparency = transparencyValue.newLowValue();
    particle->transparencyDiff = transparencyValue.newHighValue() - particle->transparency;

    // Spawn.
    float x = this->x;
    if (xOffsetValue.active) x += (int)xOffsetValue.newLowValue();
    float y = this->y;
    if (yOffsetValue.active) y += (int)yOffsetValue.newLowValue();
    switch (spawnShapeValue.shape) {
    case square: {
        int width = spawnWidth + (int)(spawnWidthDiff * spawnWidthValue.getScale(percent));
        int height = spawnHeight + (int)(spawnHeightDiff * spawnHeightValue.getScale(percent));
        x += gdx::random(width) - width / 2;
        y += gdx::random(height) - height / 2;
        break;
    }
    case ellipse: {
        int width = spawnWidth + (int)(spawnWidthDiff * spawnWidthValue.getScale(percent));
        int height = spawnHeight + (int)(spawnHeightDiff * spawnHeightValue.getScale(percent));
        int radiusX = width / 2;
        int radiusY = height / 2;
        if (radiusX == 0 || radiusY == 0) break;
        float scaleY = radiusX / (float)radiusY;
        if (spawnShapeValue.edges) {
            float spawnAngle;
            switch (spawnShapeValue.side) {
            case top:
                spawnAngle = -gdx::random(179.f);
                break;
            case bottom:
                spawnAngle = gdx::random(179.f);
                break;
            default:
                spawnAngle = gdx::random(360.f);
                break;
            }
            x += gdx::cosDeg(spawnAngle) * radiusX;
            y += gdx::sinDeg(spawnAngle) * radiusX / scaleY;
        } else {
            int radius2 = radiusX * radiusX;
            while (true) {
                int px = gdx::random(width) - radiusX;
                int py = gdx::random(width) - radiusX;
                if (px * px + py * py <= radius2) {
                    x += px;
                    y += py / scaleY;
                    break;
                }
            }
        }
        break;
    }
    case line: {
        int width = spawnWidth + (int)(spawnWidthDiff * spawnWidthValue.getScale(percent));
        int height = spawnHeight + (int)(spawnHeightDiff * spawnHeightValue.getScale(percent));
        if (width != 0) {
            float lineX = width * gdx::random();
            x += lineX;
            y += lineX * (height / (float)width);
        } else
            y += height * gdx::random();
        break;
    }
    case point:
    default:
        break;
    }

    float spriteHeight = sprite->getHeight();
    particle->setBounds(x - spriteWidth / 2, y - spriteHeight / 2, spriteWidth, spriteHeight);
}

bool ParticleEmitter::updateParticle (int index,float delta,int deltaMillis) {
    Particle * particle = particles[index];
    int life = particle->currentLife - deltaMillis;
    if (life <= 0) return false;
    particle->currentLife = life;

    float percent = 1 - particle->currentLife / (float)particle->life;
    int updateFlags = this->updateFlags;

    if ((updateFlags & UPDATE_SCALE) != 0)
        particle->setScale(particle->scale + particle->scaleDiff * scaleValue.getScale(percent));

    if ((updateFlags & UPDATE_VELOCITY) != 0) {
        float velocity = (particle->velocity + particle->velocityDiff * velocityValue.getScale(percent)) * delta;

        float velocityX, velocityY;
        if ((updateFlags & UPDATE_ANGLE) != 0) {
            float angle = particle->angle + particle->angleDiff * angleValue.getScale(percent);
            velocityX = velocity * gdx::cosDeg(angle);
            velocityY = velocity * gdx::sinDeg(angle);
            if ((updateFlags & UPDATE_ROTATION) != 0) {
                float rotation = particle->rotation + particle->rotationDiff * rotationValue.getScale(percent);
                if (aligned) rotation += angle;
                particle->setRotation(rotation);
            }
        } else {
            velocityX = velocity * particle->angleCos;
            velocityY = velocity * particle->angleSin;
            if (aligned || (updateFlags & UPDATE_ROTATION) != 0) {
                float rotation = particle->rotation + particle->rotationDiff * rotationValue.getScale(percent);
                if (aligned) rotation += particle->angle;
                particle->setRotation(rotation);
            }
        }

        if ((updateFlags & UPDATE_WIND) != 0)
            velocityX += (particle->wind + particle->windDiff * windValue.getScale(percent)) * delta;

        if ((updateFlags & UPDATE_GRAVITY) != 0)
            velocityY += (particle->gravity + particle->gravityDiff * gravityValue.getScale(percent)) * delta;

        particle->translate(velocityX, velocityY);
    } else {
        if ((updateFlags & UPDATE_ROTATION) != 0)
            particle->setRotation(particle->rotation + particle->rotationDiff * rotationValue.getScale(percent));
    }

    std::vector<float> * color;
    if ((updateFlags & UPDATE_TINT) != 0)
        color = &tintValue.getColor(percent);
    else
        color = &particle->tint;
    particle->setColor((*color)[0], (*color)[1], (*color)[2],
                       particle->transparency + particle->transparencyDiff * transparencyValue.getScale(percent));

    return true;
}

void ParticleEmitter::setPosition (float x,float y) {
    if (attached) {
        float xAmount = x - this->x;
        float yAmount = y - this->y;
        for (unsigned index= 0; index <active.size(); index++) {
            if (active[index]) {
                Particle * particle = particles[index];
                particle->translate(xAmount, yAmount);
                index++;
            }
        }
    }
    this->x = x;
    this->y = y;
}

void ParticleEmitter::setSprite (gdx::Sprite::ptr sprite) {
    this->sprite = sprite;
    if (!sprite) return;
    float originX = sprite->getOriginX();
    float originY = sprite->getOriginY();
    Texture::ptr texture = sprite->getTexture();
    for (unsigned int i = 0, n = particles.size(); i < n; i++) {
        Particle * particle = particles[i];
        if (particle == NULL) break;
        particle->setTexture(texture);
        particle->setOrigin(originX, originY);
    }
}

void ParticleEmitter::allowCompletion () {
    allowCompletionVar = true;
    durationTimer = duration;
}

gdx::Sprite::ptr ParticleEmitter::getSprite () {
    return sprite;
}

std::string& ParticleEmitter::getName () {
    return name;
}

void ParticleEmitter::setName (std::string& name) {
    this->name = name;
}

ParticleEmitter::ScaledNumericValue& ParticleEmitter::getLife () {
    return lifeValue;
}

ParticleEmitter::ScaledNumericValue& ParticleEmitter::getScale () {
    return scaleValue;
}

ParticleEmitter::ScaledNumericValue& ParticleEmitter::getRotation () {
    return rotationValue;
}

ParticleEmitter::GradientColorValue& ParticleEmitter::getTint () {
    return tintValue;
}

ParticleEmitter::ScaledNumericValue& ParticleEmitter::getVelocity () {
    return velocityValue;
}

ParticleEmitter::ScaledNumericValue& ParticleEmitter::getWind () {
    return windValue;
}

ParticleEmitter::ScaledNumericValue& ParticleEmitter::getGravity () {
    return gravityValue;
}

ParticleEmitter::ScaledNumericValue& ParticleEmitter::getAngle () {
    return angleValue;
}

ParticleEmitter::ScaledNumericValue& ParticleEmitter::getEmission () {
    return emissionValue;
}

ParticleEmitter::ScaledNumericValue& ParticleEmitter::getTransparency () {
    return transparencyValue;
}

ParticleEmitter::RangedNumericValue& ParticleEmitter::getDuration () {
    return durationValue;
}

ParticleEmitter::RangedNumericValue& ParticleEmitter::getDelay () {
    return delayValue;
}

ParticleEmitter::ScaledNumericValue& ParticleEmitter::getLifeOffset () {
    return lifeOffsetValue;
}

ParticleEmitter::RangedNumericValue& ParticleEmitter::getXOffsetValue () {
    return xOffsetValue;
}

ParticleEmitter::RangedNumericValue& ParticleEmitter::getYOffsetValue () {
    return yOffsetValue;
}

ParticleEmitter::ScaledNumericValue& ParticleEmitter::getSpawnWidth () {
    return spawnWidthValue;
}

ParticleEmitter::ScaledNumericValue& ParticleEmitter::getSpawnHeight () {
    return spawnHeightValue;
}

ParticleEmitter::SpawnShapeValue& ParticleEmitter::getSpawnShape () {
    return spawnShapeValue;
}

bool ParticleEmitter::isAttached () {
    return attached;
}

void ParticleEmitter::setAttached (bool attached) {
    this->attached = attached;
}

bool ParticleEmitter::isContinuous () {
    return continuous;
}

void ParticleEmitter::setContinuous (bool continuous) {
    this->continuous = continuous;
}

bool ParticleEmitter::isAligned () {
    return aligned;
}

void ParticleEmitter::setAligned (bool aligned) {
    this->aligned = aligned;
}

bool ParticleEmitter::isAdditive () {
    return additive;
}

void ParticleEmitter::setAdditive (bool additive) {
    this->additive = additive;
}

bool ParticleEmitter::isBehind () {
    return behind;
}

void ParticleEmitter::setBehind (bool behind) {
    this->behind = behind;
}

int ParticleEmitter::getMinParticleCount () {
    return minParticleCount;
}

void ParticleEmitter::setMinParticleCount (int minParticleCount) {
    this->minParticleCount = minParticleCount;
}

int ParticleEmitter::getMaxParticleCount () {
    return maxParticleCount;
}

bool ParticleEmitter::isComplete () {
    if (delayTimer < delay) return false;
    return durationTimer >= duration && activeCount == 0;
}

float ParticleEmitter::getPercentComplete () {
    if (delayTimer < delay) return 0;
    return std::min(1.f, durationTimer / (float)duration);
}

float ParticleEmitter::getX () {
    return x;
}

float ParticleEmitter::getY () {
    return y;
}

int ParticleEmitter::getActiveCount () {
    return activeCount;
}

int ParticleEmitter::getDrawCount () {
    int result = 0;
    for (unsigned int i = 0; i < active.size(); i++)
    {
        if (active[i])
        {
            result++;
        }
    }
    return result;
}

std::string ParticleEmitter::getImagePath () {
    return imagePath;
}

void ParticleEmitter::setImagePath (const std::string& imagePath) {
    this->imagePath = imagePath;
}

void ParticleEmitter::setFlip (bool flipX,bool flipY) {
    this->flipX = flipX;
    this->flipY = flipY;
    if (particles.size() == 0) return;
    for (unsigned int i = 0, n = particles.size(); i < n; i++) {
        Particle * particle = particles[i];
        if (particle != NULL) particle->flip(flipX, flipY);
    }
}

// trim from start
inline std::string& ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
inline std::string& rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
inline std::string& trim(std::string &s) {
    return ltrim(rtrim(s));
}

std::string readString (std::istream& reader, const std::string& name) {
    std::string line;
    std::getline(reader, line);
    std::size_t found;
    if (line.length() == 0 ) gdx_log_error("gdx", "Missing value: %s", name.c_str());
    found = line.find(":", 0);
    if (found == std::string::npos)
        found = -1;
    std::string result = line.substr(int(found) + 1);
    return trim(result);
}

bool readBoolean (std::istream& reader, const std::string& name) { //TODO GAMBIS?
    std::string value = readString(reader, name);
    if (value == "1" || value == "true" | value == "TRUE")
    {
        return true;
    }else if (value == "0" || value == "false" | value == "FALSE")
    {
      return false;
    }
    gdx_log_error("gdx","Invalid boolean value for: ", name.c_str());
}

int readInt (std::istream& reader, const std::string& name) {
    return atoi(readString(reader, name).c_str());
}

float readFloat (std::istream& reader, const std::string& name) {
    return atof(readString(reader, name).c_str());
}


void ParticleEmitter::save (std::ostream& output) {
    output << name << std::endl;
    output << "- Delay -" << std::endl;
    delayValue.save(output);
    output << "- Duration -" << std::endl;
    durationValue.save(output);
    output << "- Count - " << std::endl;
    output << "min: " << minParticleCount << std::endl;
    output << "max: " << maxParticleCount << std::endl;
    output << "- Emission - " << std::endl;
    emissionValue.save(output);
    output << "- Life - " << std::endl;
    lifeValue.save(output);
    output << "- Life Offset - " << std::endl;
    lifeOffsetValue.save(output);
    output << "- X Offset - " << std::endl;
    xOffsetValue.save(output);
    output << "- Y Offset - " << std::endl;
    yOffsetValue.save(output);
    output << "- Spawn Shape - " << std::endl;
    spawnShapeValue.save(output);
    output << "- Spawn Width - " << std::endl;
    spawnWidthValue.save(output);
    output << "- Spawn Height - " << std::endl;
    spawnHeightValue.save(output);
    output << "- Scale - " << std::endl;
    scaleValue.save(output);
    output << "- Velocity - " << std::endl;
    velocityValue.save(output);
    output << "- Angle - " << std::endl;
    angleValue.save(output);
    output << "- Rotation - " << std::endl;
    rotationValue.save(output);
    output << "- Wind - " << std::endl;
    windValue.save(output);
    output << "- Gravity - " << std::endl;
    gravityValue.save(output);
    output << "- Tint - " << std::endl;
    tintValue.save(output);
    output << "- Transparency - " << std::endl;
    transparencyValue.save(output);
    output << "- Options - " << std::endl;
    output << "attached: " << attached << std::endl;
    output << "continuous: " << continuous << std::endl;
    output << "aligned: " << aligned << std::endl;
    output << "additive: " << additive << std::endl;
    output << "behind: " << behind << std::endl;
}

void ParticleEmitter::load (std::istream& reader) {
        std::string by;
        name = readString(reader, "name");
        std::getline(reader, by);
        delayValue.load(reader);
        std::getline(reader, by);
        durationValue.load(reader);
        std::getline(reader, by);
        setMinParticleCount(readInt(reader, "minParticleCount"));
        setMaxParticleCount(readInt(reader, "maxParticleCount"));
        std::getline(reader, by);
        emissionValue.load(reader);
        std::getline(reader, by);
        lifeValue.load(reader);
        std::getline(reader, by);
        lifeOffsetValue.load(reader);
        std::getline(reader, by);
        xOffsetValue.load(reader);
        std::getline(reader, by);
        yOffsetValue.load(reader);
        std::getline(reader, by);
        spawnShapeValue.load(reader);
        std::getline(reader, by);
        spawnWidthValue.load(reader);
        std::getline(reader, by);
        spawnHeightValue.load(reader);
        std::getline(reader, by);
        scaleValue.load(reader);
        std::getline(reader, by);
        velocityValue.load(reader);
        std::getline(reader, by);
        angleValue.load(reader);
        std::getline(reader, by);
        rotationValue.load(reader);
        std::getline(reader, by);
        windValue.load(reader);
        std::getline(reader, by);
        gravityValue.load(reader);
        std::getline(reader, by);
        tintValue.load(reader);
        std::getline(reader, by);
        transparencyValue.load(reader);
        std::getline(reader, by);
        attached = readBoolean(reader, "attached");
        continuous = readBoolean(reader, "continuous");
        aligned = readBoolean(reader, "aligned");
        additive = readBoolean(reader, "additive");
        behind = readBoolean(reader, "behind");
}

//------------------------Particle-----------------------------------
ParticleEmitter::Particle::Particle(Sprite::ptr s) : Sprite(s),
life(0),
currentLife(0),
scale(0),
scaleDiff(0),
rotation(0),
rotationDiff(0),
velocity(0),
velocityDiff(0),
angle(0),
angleDiff(0),
angleCos(0),
angleSin(0),
transparency(0),
transparencyDiff(0),
wind(0),
windDiff(0),
gravity(0),
gravityDiff(0)
{

}
//------------------------ParticleValue-----------------------------------
ParticleEmitter::ParticleValue::ParticleValue():active(false),
alwaysActive(false)
{

}

void ParticleEmitter::ParticleValue::setAlwaysActive (bool _alwaysActive) {
    this->alwaysActive = _alwaysActive;
}

bool ParticleEmitter::ParticleValue::isAlwaysActive () {
    return alwaysActive;
}

bool ParticleEmitter::ParticleValue::isActive () {
    return active;
}

void ParticleEmitter::ParticleValue::setActive (bool _active) {
    this->active = _active;
}

void ParticleEmitter::ParticleValue::save (std::ostream& output) {
    if (!alwaysActive)
        output << "active: " << active << std::endl;
    else
        active = true;
}

void ParticleEmitter::ParticleValue::load (std::istream& reader) {
    if (!alwaysActive)
        active = readBoolean(reader, "active");
    else
        active = true;
}

void ParticleEmitter::ParticleValue::load (ParticleValue& value) {
    active = value.active;
    alwaysActive = value.alwaysActive;
}

//------------------------NumericValue-----------------------------------

ParticleEmitter::NumericValue::NumericValue():value(0)
{

}

float ParticleEmitter::NumericValue::getValue () {
    return value;
}

void ParticleEmitter::NumericValue::setValue (float value) {
    this->value = value;
}

void ParticleEmitter::NumericValue::save (std::ostream& output) {
    ParticleEmitter::ParticleValue::save(output);
    if (!active) return;
    output << "value: " << value << std::endl;
}

void ParticleEmitter::NumericValue::load (std::istream& reader) {
    ParticleEmitter::ParticleValue::load(reader);
    if (!active) return;
    value = readFloat(reader, "value");
}

void ParticleEmitter::NumericValue::load (NumericValue& value) {
    ParticleEmitter::ParticleValue::load(value);
    this->value = value.value;
}


//----------------RangedNumericValue--------------------------------------
ParticleEmitter::RangedNumericValue::RangedNumericValue():lowMin(0),
lowMax(0)
{

}

float ParticleEmitter::RangedNumericValue::newLowValue () {
    return lowMin + (lowMax - lowMin) * gdx::random();
}

void ParticleEmitter::RangedNumericValue::setLow (float value) {
    lowMin = value;
    lowMax = value;
}

void ParticleEmitter::RangedNumericValue::setLow (float min,float max) {
    lowMin = min;
    lowMax = max;
}

float ParticleEmitter::RangedNumericValue::getLowMin () {
    return lowMin;
}

void ParticleEmitter::RangedNumericValue::setLowMin (float lowMin) {
    this->lowMin = lowMin;
}

float ParticleEmitter::RangedNumericValue::getLowMax () {
    return lowMax;
}

void ParticleEmitter::RangedNumericValue::setLowMax (float lowMax) {
    this->lowMax = lowMax;
}

void ParticleEmitter::RangedNumericValue::save (std::ostream& output) {
    ParticleEmitter::ParticleValue::save(output);
    if (!active) return;
    output << "lowMin: " << lowMin << std::endl;
    output << "lowMax: " << lowMax << std::endl;
}

void ParticleEmitter::RangedNumericValue::load (std::istream& reader) {
    ParticleEmitter::ParticleValue::load(reader);
    if (!active) return;
    lowMin = readFloat(reader, "lowMin");
    lowMax = readFloat(reader, "lowMax");
}

void ParticleEmitter::RangedNumericValue::load (RangedNumericValue& value) {
    ParticleEmitter::ParticleValue::load(value);
    lowMax = value.lowMax;
    lowMin = value.lowMin;
}

//---------------------------ParticleEmitter::ScaledNumericValue--------------------------

ParticleEmitter::ScaledNumericValue::ScaledNumericValue() : highMin(0),
highMax(0),
relative(false)
{
  timeline.push_back(0.f);
  scaling.push_back(1.f);

}

float ParticleEmitter::ScaledNumericValue::newHighValue () {
    return highMin + (highMax - highMin) * gdx::random();
}

void ParticleEmitter::ScaledNumericValue::setHigh (float value) {
    highMin = value;
    highMax = value;
}

void ParticleEmitter::ScaledNumericValue::setHigh (float min,float max) {
    highMin = min;
    highMax = max;
}

float ParticleEmitter::ScaledNumericValue::getHighMin () {
    return highMin;
}

void ParticleEmitter::ScaledNumericValue::setHighMin (float highMin) {
    this->highMin = highMin;
}

float ParticleEmitter::ScaledNumericValue::getHighMax () {
    return highMax;
}

void ParticleEmitter::ScaledNumericValue::setHighMax (float highMax) {
    this->highMax = highMax;
}

std::vector<float>& ParticleEmitter::ScaledNumericValue::getScaling () {
    return scaling;
}

void ParticleEmitter::ScaledNumericValue::setScaling (std::vector<float>& values) {
    this->scaling = values;
}

std::vector<float>& ParticleEmitter::ScaledNumericValue::getTimeline () {
    return timeline;
}

void ParticleEmitter::ScaledNumericValue::setTimeline (std::vector<float>& _timeline) {
    this->timeline = _timeline;
}

bool ParticleEmitter::ScaledNumericValue::isRelative () {
    return relative;
}

void ParticleEmitter::ScaledNumericValue::setRelative (bool relative) {
    this->relative = relative;
}

float ParticleEmitter::ScaledNumericValue::getScale (float percent) {
    int endIndex = -1;
    int n = timeline.size();
    for (unsigned int i = 1; i < n; i++) {
        float t = timeline[i];
        if (t > percent) {
            endIndex = i;
            break;
        }
    }
    if (endIndex == -1) return scaling[n - 1];
    int startIndex = endIndex - 1;
    float startValue = scaling[startIndex];
    float startTime = timeline[startIndex];
    return startValue + (scaling[endIndex] - startValue) * ((percent - startTime) / (timeline[endIndex] - startTime));
}

void ParticleEmitter::ScaledNumericValue::save (std::ostream& output) {
    RangedNumericValue::save(output);
    if (!active) return;
    output << "highMin: " << highMin << std::endl;
    output << "highMax: " << highMax << std::endl;
    output << "relative: " << relative << std::endl;
    output << "scalingCount: " << scaling.size() << std::endl;
    for (unsigned int i = 0; i < scaling.size(); i++)
        output << "scaling" << i << ": " << scaling[i] << std::endl;
    output << "timelineCount: " << timeline.size() << std::endl;
    for (unsigned int i = 0; i < timeline.size(); i++)
        output << "timeline" << i << ": " << timeline[i] << std::endl;
}

void ParticleEmitter::ScaledNumericValue::load (std::istream& reader) {
    RangedNumericValue::load(reader);
    if (!active) return;
    highMin = readFloat(reader, "highMin");
    highMax = readFloat(reader, "highMax");
    relative = readBoolean(reader, "relative");
    scaling.clear();
    scaling.resize(readInt(reader, "scalingCount"));
    for (unsigned int i = 0; i < scaling.size(); i++)
        scaling[i] = readFloat(reader, "scaling" + i);
    timeline.clear();
    timeline.resize(readInt(reader, "timelineCount"));
    for (unsigned int i = 0; i < timeline.size(); i++)
        timeline[i] = readFloat(reader, "timeline" + i);
}

void ParticleEmitter::ScaledNumericValue::load (ParticleEmitter::ScaledNumericValue& value) {
    RangedNumericValue::load(value);
    highMax = value.highMax;
    highMin = value.highMin;
    scaling = value.scaling;
    timeline = value.timeline;
    relative = value.relative;
}
//----------------------------------GradientColorValue---------------------------
ParticleEmitter::GradientColorValue::GradientColorValue()
{
  colors.push_back(1);
  colors.push_back(1);
  colors.push_back(1);
  timeline.push_back(0);
  alwaysActive = true;
  temp.resize(4);

}
std::vector<float>& ParticleEmitter::GradientColorValue::getTimeline () {
    return timeline;
}

void ParticleEmitter::GradientColorValue::setTimeline (std::vector<float>& _timeline) {
    this->timeline = _timeline;
}

std::vector<float>& ParticleEmitter::GradientColorValue::getColors () {
    return colors;
}

void ParticleEmitter::GradientColorValue::setColors (std::vector<float>& _colors) {
    this->colors = _colors;
}

std::vector<float>& ParticleEmitter::GradientColorValue::getColor (float percent) {
    int startIndex = 0, endIndex = -1;
    int n = timeline.size();
    for (unsigned int i = 1; i < n; i++) {
        float t = timeline[i];
        if (t > percent) {
            endIndex = i;
            break;
        }
        startIndex = i;
    }
    float startTime = timeline[startIndex];
    startIndex *= 3;
    float r1 = colors[startIndex];
    float g1 = colors[startIndex + 1];
    float b1 = colors[startIndex + 2];
    if (endIndex == -1) {
        temp[0] = r1;
        temp[1] = g1;
        temp[2] = b1;
        return temp;
    }
    float factor = (percent - startTime) / (timeline[endIndex] - startTime);
    endIndex *= 3;
    temp[0] = r1 + (colors[endIndex] - r1) * factor;
    temp[1] = g1 + (colors[endIndex + 1] - g1) * factor;
    temp[2] = b1 + (colors[endIndex + 2] - b1) * factor;
    return temp;
}

void ParticleEmitter::GradientColorValue::save (std::ostream& output) {
    ParticleEmitter::ParticleValue::save(output);
    if (!active) return;
    output << "colorsCount: " + colors.size() << std::endl;
    for (unsigned int i = 0; i < colors.size(); i++)
        output << "colors" << i << ": " << colors[i] << std::endl;
    output << "timelineCount: " + timeline.size() << std::endl;
    for (unsigned int i = 0; i < timeline.size(); i++)
        output << "timeline" << i << ": " << timeline[i] << std::endl;
}

void ParticleEmitter::GradientColorValue::load (std::istream& reader) {
    ParticleEmitter::ParticleValue::load(reader);
    if (!active) return;
    colors.clear();
    colors.resize(readInt(reader, "colorsCount"));
    for (unsigned int i = 0; i < colors.size(); i++)
        colors[i] = readFloat(reader, "colors" + i);
    timeline.clear();
    timeline.resize(readInt(reader, "timelineCount"));
    for (unsigned int i = 0; i < timeline.size(); i++)
        timeline[i] = readFloat(reader, "timeline" + i);
}

void ParticleEmitter::GradientColorValue::load (GradientColorValue& value) {
    ParticleEmitter::ParticleValue::load(value);
    colors = value.colors;
    timeline = value.timeline;
}

//---------------------------------SpawnShapeValue-------------------------------
ParticleEmitter::SpawnShapeValue::SpawnShapeValue() : shape(ParticleEmitter::point),
edges(false),
side(ParticleEmitter::both)
{

}

ParticleEmitter::SpawnShape ParticleEmitter::SpawnShapeValue::getShape ()
{
    return shape;
}

void ParticleEmitter::SpawnShapeValue::setShape (ParticleEmitter::SpawnShape shape) {
    this->shape = shape;
}

bool ParticleEmitter::SpawnShapeValue::isEdges () {
    return edges;
}

void ParticleEmitter::SpawnShapeValue::setEdges (bool edges) {
    this->edges = edges;
}

ParticleEmitter::SpawnEllipseSide ParticleEmitter::SpawnShapeValue::getSide () {
    return side;
}

void ParticleEmitter::SpawnShapeValue::setSide (ParticleEmitter::SpawnEllipseSide side) {
    this->side = side;
}

void ParticleEmitter::SpawnShapeValue::save (std::ostream& output) {
    ParticleEmitter::ParticleValue::save(output);
    if (!active) return;
    output << "shape: " << shape << std::endl;
    if (shape == ParticleEmitter::ellipse) {
        output << "edges: " << edges << std::endl;
        output << "side: " << side << std::endl;
    }
}

void ParticleEmitter::SpawnShapeValue::load (std::istream& reader) {
    ParticleEmitter::ParticleValue::load(reader);
    if (!active) return;
    shape = (ParticleEmitter::SpawnShape) readInt(reader, "shape");
    if (shape == ParticleEmitter::ellipse) {
        edges = readBoolean(reader, "edges");
        side = (ParticleEmitter::SpawnEllipseSide) readInt(reader, "side");
    }
}

void ParticleEmitter::SpawnShapeValue::load (ParticleEmitter::SpawnShapeValue& value) {
    ParticleEmitter::ParticleValue::load(value);
    shape = value.shape;
    edges = value.edges;
    side = value.side;
}

