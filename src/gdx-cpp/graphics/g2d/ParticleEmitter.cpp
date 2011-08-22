
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

#include "ParticleEmitter.hpp"

using namespace gdx_cpp::graphics::g2d;

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
    this.maxParticleCount = maxParticleCount;
    active = new BitSet(maxParticleCount);
    activeCount = 0;
    particles = new Particle[maxParticleCount];
}

void ParticleEmitter::addParticle () {
    int activeCount = this.activeCount;
    if (activeCount == maxParticleCount) return;
    BitSet active = this.active;
    int index = active.nextClearBit(0);
    activateParticle(index);
    active.set(index);
    this.activeCount = activeCount + 1;
}

void ParticleEmitter::addParticles (int count) {
    count = Math.min(count, maxParticleCount - activeCount);
    if (count == 0) return;
    BitSet active = this.active;
    for (int i = 0; i < count; i++) {
        int index = active.nextClearBit(0);
        activateParticle(index);
        active.set(index);
    }
    this.activeCount += count;
}

void ParticleEmitter::update (float delta) {
    accumulator += Math.min(delta * 1000, 250);
    if (accumulator < 1) return;
    int deltaMillis = (int)accumulator;
    accumulator -= deltaMillis;

    BitSet active = this.active;
    int activeCount = this.activeCount;
    int index = 0;
    while (true) {
        index = active.nextSetBit(index);
        if (index == -1) break;
        if (!updateParticle(index, delta, deltaMillis)) {
            active.clear(index);
            activeCount--;
        }
        index++;
    }
    this.activeCount = activeCount;

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
        if (!continuous || allowCompletion) return;
        restart();
    }

    emissionDelta += deltaMillis;
    float emissionTime = emission + emissionDiff * emissionValue.getScale(durationTimer / (float)duration);
    if (emissionTime > 0) {
        emissionTime = 1000 / emissionTime;
        if (emissionDelta >= emissionTime) {
            int emitCount = (int)(emissionDelta / emissionTime);
            emitCount = Math.min(emitCount, maxParticleCount - activeCount);
            emissionDelta -= emitCount * emissionTime;
            emissionDelta %= emissionTime;
            addParticles(emitCount);
        }
    }
    if (activeCount < minParticleCount) addParticles(minParticleCount - activeCount);
}

void ParticleEmitter::draw (const SpriteBatch& spriteBatch) {
    if (additive) spriteBatch.setBlendFunction(GL10.GL_SRC_ALPHA, GL10.GL_ONE);

    Particle[] particles = this.particles;
    BitSet active = this.active;
    int activeCount = this.activeCount;
    int index = 0;
    while (true) {
        index = active.nextSetBit(index);
        if (index == -1) break;
        particles[index].draw(spriteBatch);
        index++;
    }
    this.activeCount = activeCount;

    if (additive) spriteBatch.setBlendFunction(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleEmitter::draw (const SpriteBatch& spriteBatch,float delta) {
    accumulator += Math.min(delta * 1000, 250);
    if (accumulator < 1) {
        draw(spriteBatch);
        return;
    }
    int deltaMillis = (int)accumulator;
    accumulator -= deltaMillis;

    if (additive) spriteBatch.setBlendFunction(GL10.GL_SRC_ALPHA, GL10.GL_ONE);

    Particle[] particles = this.particles;
    BitSet active = this.active;
    int activeCount = this.activeCount;
    int index = 0;
    while (true) {
        index = active.nextSetBit(index);
        if (index == -1) break;
        if (updateParticle(index, delta, deltaMillis))
            particles[index].draw(spriteBatch);
        else {
            active.clear(index);
            activeCount--;
        }
        index++;
    }
    this.activeCount = activeCount;

    if (additive) spriteBatch.setBlendFunction(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);

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
        if (!continuous || allowCompletion) return;
        restart();
    }

    emissionDelta += deltaMillis;
    float emissionTime = emission + emissionDiff * emissionValue.getScale(durationTimer / (float)duration);
    if (emissionTime > 0) {
        emissionTime = 1000 / emissionTime;
        if (emissionDelta >= emissionTime) {
            int emitCount = (int)(emissionDelta / emissionTime);
            emitCount = Math.min(emitCount, maxParticleCount - activeCount);
            emissionDelta -= emitCount * emissionTime;
            emissionDelta %= emissionTime;
            addParticles(emitCount);
        }
    }
    if (activeCount < minParticleCount) addParticles(minParticleCount - activeCount);
}

void ParticleEmitter::start () {
    firstUpdate = true;
    allowCompletion = false;
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
    if (angleValue.active && angleValue.timeline.length > 1) updateFlags |= UPDATE_ANGLE;
    if (velocityValue.active && velocityValue.active) updateFlags |= UPDATE_VELOCITY;
    if (scaleValue.timeline.length > 1) updateFlags |= UPDATE_SCALE;
    if (rotationValue.active && rotationValue.timeline.length > 1) updateFlags |= UPDATE_ROTATION;
    if (windValue.active) updateFlags |= UPDATE_WIND;
    if (gravityValue.active) updateFlags |= UPDATE_GRAVITY;
    if (tintValue.timeline.length > 1) updateFlags |= UPDATE_TINT;
}

void ParticleEmitter::activateParticle (int index) {
    Particle particle = particles[index];
    if (particle == null) {
        particles[index] = particle = new Particle(sprite);
        particle.flip(flipX, flipY);
    }

    float percent = durationTimer / (float)duration;
    int updateFlags = this.updateFlags;

    float offsetTime = lifeOffset + lifeOffsetDiff * lifeOffsetValue.getScale(percent);
    particle.life = particle.currentLife = life + (int)(lifeDiff * lifeValue.getScale(percent));

    if (velocityValue.active) {
        particle.velocity = velocityValue.newLowValue();
        particle.velocityDiff = velocityValue.newHighValue();
        if (!velocityValue.isRelative()) particle.velocityDiff -= particle.velocity;
    }

    particle.angle = angleValue.newLowValue();
    particle.angleDiff = angleValue.newHighValue();
    if (!angleValue.isRelative()) particle.angleDiff -= particle.angle;
    float angle = 0;
    if ((updateFlags & UPDATE_ANGLE) == 0) {
        angle = particle.angle + particle.angleDiff * angleValue.getScale(0);
        particle.angle = angle;
        particle.angleCos = MathUtils.cosDeg(angle);
        particle.angleSin = MathUtils.sinDeg(angle);
    }

    float spriteWidth = sprite.getWidth();
    particle.scale = scaleValue.newLowValue() / spriteWidth;
    particle.scaleDiff = scaleValue.newHighValue() / spriteWidth;
    if (!scaleValue.isRelative()) particle.scaleDiff -= particle.scale;
    if ((updateFlags & UPDATE_SCALE) == 0) particle.setScale(particle.scale + particle.scaleDiff * scaleValue.getScale(0));

    if (rotationValue.active) {
        particle.rotation = rotationValue.newLowValue();
        particle.rotationDiff = rotationValue.newHighValue();
        if (!rotationValue.isRelative()) particle.rotationDiff -= particle.rotation;
        if ((updateFlags & UPDATE_ROTATION) == 0) {
            float rotation = particle.rotation + particle.rotationDiff * rotationValue.getScale(0);
            if (aligned) rotation += angle;
            particle.setRotation(rotation);
        }
    }

    if (windValue.active) {
        particle.wind = windValue.newLowValue();
        particle.windDiff = windValue.newHighValue();
        if (!windValue.isRelative()) particle.windDiff -= particle.wind;
    }

    if (gravityValue.active) {
        particle.gravity = gravityValue.newLowValue();
        particle.gravityDiff = gravityValue.newHighValue();
        if (!gravityValue.isRelative()) particle.gravityDiff -= particle.gravity;
    }

    if ((updateFlags & UPDATE_TINT) == 0) {
        float[] color = particle.tint;
        if (color == null) particle.tint = color = new float[3];
        float[] temp = tintValue.getColor(0);
        color[0] = temp[0];
        color[1] = temp[1];
        color[2] = temp[2];
    }

    particle.transparency = transparencyValue.newLowValue();
    particle.transparencyDiff = transparencyValue.newHighValue() - particle.transparency;

    // Spawn.
    float x = this.x;
    if (xOffsetValue.active) x += (int)xOffsetValue.newLowValue();
    float y = this.y;
    if (yOffsetValue.active) y += (int)yOffsetValue.newLowValue();
    switch (spawnShapeValue.shape) {
    case square: {
        int width = spawnWidth + (int)(spawnWidthDiff * spawnWidthValue.getScale(percent));
        int height = spawnHeight + (int)(spawnHeightDiff * spawnHeightValue.getScale(percent));
        x += MathUtils.random(width) - width / 2;
        y += MathUtils.random(height) - height / 2;
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
                spawnAngle = -MathUtils.random(179f);
                break;
            case bottom:
                spawnAngle = MathUtils.random(179f);
                break;
            default:
                spawnAngle = MathUtils.random(360f);
                break;
            }
            x += MathUtils.cosDeg(spawnAngle) * radiusX;
            y += MathUtils.sinDeg(spawnAngle) * radiusX / scaleY;
        } else {
            int radius2 = radiusX * radiusX;
            while (true) {
                int px = MathUtils.random(width) - radiusX;
                int py = MathUtils.random(width) - radiusX;
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
            float lineX = width * MathUtils.random();
            x += lineX;
            y += lineX * (height / (float)width);
        } else
            y += height * MathUtils.random();
        break;
    }
    }

    float spriteHeight = sprite.getHeight();
    particle.setBounds(x - spriteWidth / 2, y - spriteHeight / 2, spriteWidth, spriteHeight);
}

bool ParticleEmitter::updateParticle (int index,float delta,int deltaMillis) {
    Particle particle = particles[index];
    int life = particle.currentLife - deltaMillis;
    if (life <= 0) return false;
    particle.currentLife = life;

    float percent = 1 - particle.currentLife / (float)particle.life;
    int updateFlags = this.updateFlags;

    if ((updateFlags & UPDATE_SCALE) != 0)
        particle.setScale(particle.scale + particle.scaleDiff * scaleValue.getScale(percent));

    if ((updateFlags & UPDATE_VELOCITY) != 0) {
        float velocity = (particle.velocity + particle.velocityDiff * velocityValue.getScale(percent)) * delta;

        float velocityX, velocityY;
        if ((updateFlags & UPDATE_ANGLE) != 0) {
            float angle = particle.angle + particle.angleDiff * angleValue.getScale(percent);
            velocityX = velocity * MathUtils.cosDeg(angle);
            velocityY = velocity * MathUtils.sinDeg(angle);
            if ((updateFlags & UPDATE_ROTATION) != 0) {
                float rotation = particle.rotation + particle.rotationDiff * rotationValue.getScale(percent);
                if (aligned) rotation += angle;
                particle.setRotation(rotation);
            }
        } else {
            velocityX = velocity * particle.angleCos;
            velocityY = velocity * particle.angleSin;
            if (aligned || (updateFlags & UPDATE_ROTATION) != 0) {
                float rotation = particle.rotation + particle.rotationDiff * rotationValue.getScale(percent);
                if (aligned) rotation += particle.angle;
                particle.setRotation(rotation);
            }
        }

        if ((updateFlags & UPDATE_WIND) != 0)
            velocityX += (particle.wind + particle.windDiff * windValue.getScale(percent)) * delta;

        if ((updateFlags & UPDATE_GRAVITY) != 0)
            velocityY += (particle.gravity + particle.gravityDiff * gravityValue.getScale(percent)) * delta;

        particle.translate(velocityX, velocityY);
    } else {
        if ((updateFlags & UPDATE_ROTATION) != 0)
            particle.setRotation(particle.rotation + particle.rotationDiff * rotationValue.getScale(percent));
    }

    float[] color;
    if ((updateFlags & UPDATE_TINT) != 0)
        color = tintValue.getColor(percent);
    else
        color = particle.tint;
    particle.setColor(color[0], color[1], color[2],
                      particle.transparency + particle.transparencyDiff * transparencyValue.getScale(percent));

    return true;
}

void ParticleEmitter::setPosition (float x,float y) {
    if (attached) {
        float xAmount = x - this.x;
        float yAmount = y - this.y;
        BitSet active = this.active;
        int index = 0;
        while (true) {
            index = active.nextSetBit(index);
            if (index == -1) break;
            Particle particle = particles[index];
            particle.translate(xAmount, yAmount);
            index++;
        }
    }
    this.x = x;
    this.y = y;
}

void ParticleEmitter::setSprite (const Sprite& sprite) {
    this.sprite = sprite;
    if (sprite == null) return;
    float originX = sprite.getOriginX();
    float originY = sprite.getOriginY();
    Texture texture = sprite.getTexture();
    for (int i = 0, n = particles.length; i < n; i++) {
        Particle particle = particles[i];
        if (particle == null) break;
        particle.setTexture(texture);
        particle.setOrigin(originX, originY);
    }
}

void ParticleEmitter::allowCompletion () {
    allowCompletion = true;
    durationTimer = duration;
}

Sprite& ParticleEmitter::getSprite () {
    return sprite;
}

std::string& ParticleEmitter::getName () {
    return name;
}

void ParticleEmitter::setName (const std::string& name) {
    this.name = name;
}

ScaledNumericValue& ParticleEmitter::getLife () {
    return lifeValue;
}

ScaledNumericValue& ParticleEmitter::getScale () {
    return scaleValue;
}

ScaledNumericValue& ParticleEmitter::getRotation () {
    return rotationValue;
}

GradientColorValue& ParticleEmitter::getTint () {
    return tintValue;
}

ScaledNumericValue& ParticleEmitter::getVelocity () {
    return velocityValue;
}

ScaledNumericValue& ParticleEmitter::getWind () {
    return windValue;
}

ScaledNumericValue& ParticleEmitter::getGravity () {
    return gravityValue;
}

ScaledNumericValue& ParticleEmitter::getAngle () {
    return angleValue;
}

ScaledNumericValue& ParticleEmitter::getEmission () {
    return emissionValue;
}

ScaledNumericValue& ParticleEmitter::getTransparency () {
    return transparencyValue;
}

RangedNumericValue& ParticleEmitter::getDuration () {
    return durationValue;
}

RangedNumericValue& ParticleEmitter::getDelay () {
    return delayValue;
}

ScaledNumericValue& ParticleEmitter::getLifeOffset () {
    return lifeOffsetValue;
}

RangedNumericValue& ParticleEmitter::getXOffsetValue () {
    return xOffsetValue;
}

RangedNumericValue& ParticleEmitter::getYOffsetValue () {
    return yOffsetValue;
}

ScaledNumericValue& ParticleEmitter::getSpawnWidth () {
    return spawnWidthValue;
}

ScaledNumericValue& ParticleEmitter::getSpawnHeight () {
    return spawnHeightValue;
}

SpawnShapeValue& ParticleEmitter::getSpawnShape () {
    return spawnShapeValue;
}

bool ParticleEmitter::isAttached () {
    return attached;
}

void ParticleEmitter::setAttached (bool attached) {
    this.attached = attached;
}

bool ParticleEmitter::isContinuous () {
    return continuous;
}

void ParticleEmitter::setContinuous (bool continuous) {
    this.continuous = continuous;
}

bool ParticleEmitter::isAligned () {
    return aligned;
}

void ParticleEmitter::setAligned (bool aligned) {
    this.aligned = aligned;
}

bool ParticleEmitter::isAdditive () {
    return additive;
}

void ParticleEmitter::setAdditive (bool additive) {
    this.additive = additive;
}

bool ParticleEmitter::isBehind () {
    return behind;
}

void ParticleEmitter::setBehind (bool behind) {
    this.behind = behind;
}

int ParticleEmitter::getMinParticleCount () {
    return minParticleCount;
}

void ParticleEmitter::setMinParticleCount (int minParticleCount) {
    this.minParticleCount = minParticleCount;
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
    return Math.min(1, durationTimer / (float)duration);
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
    return active.length();
}

std::string& ParticleEmitter::getImagePath () {
    return imagePath;
}

void ParticleEmitter::setImagePath (const std::string& imagePath) {
    this.imagePath = imagePath;
}

void ParticleEmitter::setFlip (bool flipX,bool flipY) {
    this.flipX = flipX;
    this.flipY = flipY;
    if (particles == null) return;
    for (int i = 0, n = particles.length; i < n; i++) {
        Particle particle = particles[i];
        if (particle != null) particle.flip(flipX, flipY);
    }
}

void ParticleEmitter::save (const Writer& output) throws IOException {
    output.write(name + "\n");
    output.write("- Delay -\n");
    delayValue.save(output);
    output.write("- Duration - \n");
    durationValue.save(output);
    output.write("- Count - \n");
    output.write("min: " + minParticleCount + "\n");
    output.write("max: " + maxParticleCount + "\n");
    output.write("- Emission - \n");
    emissionValue.save(output);
    output.write("- Life - \n");
    lifeValue.save(output);
    output.write("- Life Offset - \n");
    lifeOffsetValue.save(output);
    output.write("- X Offset - \n");
    xOffsetValue.save(output);
    output.write("- Y Offset - \n");
    yOffsetValue.save(output);
    output.write("- Spawn Shape - \n");
    spawnShapeValue.save(output);
    output.write("- Spawn Width - \n");
    spawnWidthValue.save(output);
    output.write("- Spawn Height - \n");
    spawnHeightValue.save(output);
    output.write("- Scale - \n");
    scaleValue.save(output);
    output.write("- Velocity - \n");
    velocityValue.save(output);
    output.write("- Angle - \n");
    angleValue.save(output);
    output.write("- Rotation - \n");
    rotationValue.save(output);
    output.write("- Wind - \n");
    windValue.save(output);
    output.write("- Gravity - \n");
    gravityValue.save(output);
    output.write("- Tint - \n");
    tintValue.save(output);
    output.write("- Transparency - \n");
    transparencyValue.save(output);
    output.write("- Options - \n");
    output.write("attached: " + attached + "\n");
    output.write("continuous: " + continuous + "\n");
    output.write("aligned: " + aligned + "\n");
    output.write("additive: " + additive + "\n");
    output.write("behind: " + behind + "\n");
}

void ParticleEmitter::load (const BufferedReader& reader) throws IOException {
    try {
        name = readString(reader, "name");
        reader.readLine();
        delayValue.load(reader);
        reader.readLine();
        durationValue.load(reader);
        reader.readLine();
        setMinParticleCount(readInt(reader, "minParticleCount"));
        setMaxParticleCount(readInt(reader, "maxParticleCount"));
        reader.readLine();
        emissionValue.load(reader);
        reader.readLine();
        lifeValue.load(reader);
        reader.readLine();
        lifeOffsetValue.load(reader);
        reader.readLine();
        xOffsetValue.load(reader);
        reader.readLine();
        yOffsetValue.load(reader);
        reader.readLine();
        spawnShapeValue.load(reader);
        reader.readLine();
        spawnWidthValue.load(reader);
        reader.readLine();
        spawnHeightValue.load(reader);
        reader.readLine();
        scaleValue.load(reader);
        reader.readLine();
        velocityValue.load(reader);
        reader.readLine();
        angleValue.load(reader);
        reader.readLine();
        rotationValue.load(reader);
        reader.readLine();
        windValue.load(reader);
        reader.readLine();
        gravityValue.load(reader);
        reader.readLine();
        tintValue.load(reader);
        reader.readLine();
        transparencyValue.load(reader);
        reader.readLine();
        attached = readBoolean(reader, "attached");
        continuous = readBoolean(reader, "continuous");
        aligned = readBoolean(reader, "aligned");
        additive = readBoolean(reader, "additive");
        behind = readBoolean(reader, "behind");
    } catch (RuntimeException ex) {
        if (name == null) throw ex;
        throw new RuntimeException("Error parsing emitter: " + name, ex);
    }
}

void ParticleEmitter::setAlwaysActive (bool alwaysActive) {
    this.alwaysActive = alwaysActive;
}

bool ParticleEmitter::isAlwaysActive () {
    return alwaysActive;
}

bool ParticleEmitter::isActive () {
    return active;
}

void ParticleEmitter::setActive (bool active) {
    this.active = active;
}

void ParticleEmitter::save (const Writer& output) throws IOException {
    if (!alwaysActive)
        output.write("active: " + active + "\n");
    else
        active = true;
}

void ParticleEmitter::load (const BufferedReader& reader) throws IOException {
    if (!alwaysActive)
        active = readBoolean(reader, "active");
    else
        active = true;
}

void ParticleEmitter::load (const ParticleValue& value) {
    active = value.active;
    alwaysActive = value.alwaysActive;
}

float ParticleEmitter::getValue () {
    return value;
}

void ParticleEmitter::setValue (float value) {
    this.value = value;
}

void ParticleEmitter::save (const Writer& output) throws IOException {
    super.save(output);
    if (!active) return;
    output.write("value: " + value + "\n");
}

void ParticleEmitter::load (const BufferedReader& reader) throws IOException {
    super.load(reader);
    if (!active) return;
    value = readFloat(reader, "value");
}

void ParticleEmitter::load (const NumericValue& value) {
    super.load(value);
    this.value = value.value;
}

float ParticleEmitter::newLowValue () {
    return lowMin + (lowMax - lowMin) * MathUtils.random();
}

void ParticleEmitter::setLow (float value) {
    lowMin = value;
    lowMax = value;
}

void ParticleEmitter::setLow (float min,float max) {
    lowMin = min;
    lowMax = max;
}

float ParticleEmitter::getLowMin () {
    return lowMin;
}

void ParticleEmitter::setLowMin (float lowMin) {
    this.lowMin = lowMin;
}

float ParticleEmitter::getLowMax () {
    return lowMax;
}

void ParticleEmitter::setLowMax (float lowMax) {
    this.lowMax = lowMax;
}

void ParticleEmitter::save (const Writer& output) throws IOException {
    super.save(output);
    if (!active) return;
    output.write("lowMin: " + lowMin + "\n");
    output.write("lowMax: " + lowMax + "\n");
}

void ParticleEmitter::load (const BufferedReader& reader) throws IOException {
    super.load(reader);
    if (!active) return;
    lowMin = readFloat(reader, "lowMin");
    lowMax = readFloat(reader, "lowMax");
}

void ParticleEmitter::load (const RangedNumericValue& value) {
    super.load(value);
    lowMax = value.lowMax;
    lowMin = value.lowMin;
}

float ParticleEmitter::newHighValue () {
    return highMin + (highMax - highMin) * MathUtils.random();
}

void ParticleEmitter::setHigh (float value) {
    highMin = value;
    highMax = value;
}

void ParticleEmitter::setHigh (float min,float max) {
    highMin = min;
    highMax = max;
}

float ParticleEmitter::getHighMin () {
    return highMin;
}

void ParticleEmitter::setHighMin (float highMin) {
    this.highMin = highMin;
}

float ParticleEmitter::getHighMax () {
    return highMax;
}

void ParticleEmitter::setHighMax (float highMax) {
    this.highMax = highMax;
}

float* ParticleEmitter::getScaling () {
    return scaling;
}

void ParticleEmitter::setScaling () {
    this.scaling = values;
}

float* ParticleEmitter::getTimeline () {
    return timeline;
}

void ParticleEmitter::setTimeline () {
    this.timeline = timeline;
}

bool ParticleEmitter::isRelative () {
    return relative;
}

void ParticleEmitter::setRelative (bool relative) {
    this.relative = relative;
}

float ParticleEmitter::getScale (float percent) {
    int endIndex = -1;
    float[] timeline = this.timeline;
    int n = timeline.length;
    for (int i = 1; i < n; i++) {
        float t = timeline[i];
        if (t > percent) {
            endIndex = i;
            break;
        }
    }
    if (endIndex == -1) return scaling[n - 1];
    float[] scaling = this.scaling;
    int startIndex = endIndex - 1;
    float startValue = scaling[startIndex];
    float startTime = timeline[startIndex];
    return startValue + (scaling[endIndex] - startValue) * ((percent - startTime) / (timeline[endIndex] - startTime));
}

void ParticleEmitter::save (const Writer& output) throws IOException {
    super.save(output);
    if (!active) return;
    output.write("highMin: " + highMin + "\n");
    output.write("highMax: " + highMax + "\n");
    output.write("relative: " + relative + "\n");
    output.write("scalingCount: " + scaling.length + "\n");
    for (int i = 0; i < scaling.length; i++)
        output.write("scaling" + i + ": " + scaling[i] + "\n");
    output.write("timelineCount: " + timeline.length + "\n");
    for (int i = 0; i < timeline.length; i++)
        output.write("timeline" + i + ": " + timeline[i] + "\n");
}

void ParticleEmitter::load (const BufferedReader& reader) throws IOException {
    super.load(reader);
    if (!active) return;
    highMin = readFloat(reader, "highMin");
    highMax = readFloat(reader, "highMax");
    relative = readBoolean(reader, "relative");
    scaling = new float[readInt(reader, "scalingCount")];
    for (int i = 0; i < scaling.length; i++)
        scaling[i] = readFloat(reader, "scaling" + i);
    timeline = new float[readInt(reader, "timelineCount")];
    for (int i = 0; i < timeline.length; i++)
        timeline[i] = readFloat(reader, "timeline" + i);
}

void ParticleEmitter::load (const ScaledNumericValue& value) {
    super.load(value);
    highMax = value.highMax;
    highMin = value.highMin;
    scaling = new float[value.scaling.length];
    System.arraycopy(value.scaling, 0, scaling, 0, scaling.length);
    timeline = new float[value.timeline.length];
    System.arraycopy(value.timeline, 0, timeline, 0, timeline.length);
    relative = value.relative;
}

float* ParticleEmitter::getTimeline () {
    return timeline;
}

void ParticleEmitter::setTimeline () {
    this.timeline = timeline;
}

float* ParticleEmitter::getColors () {
    return colors;
}

void ParticleEmitter::setColors () {
    this.colors = colors;
}

float* ParticleEmitter::getColor (float percent) {
    int startIndex = 0, endIndex = -1;
    float[] timeline = this.timeline;
    int n = timeline.length;
    for (int i = 1; i < n; i++) {
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

void ParticleEmitter::save (const Writer& output) throws IOException {
    super.save(output);
    if (!active) return;
    output.write("colorsCount: " + colors.length + "\n");
    for (int i = 0; i < colors.length; i++)
        output.write("colors" + i + ": " + colors[i] + "\n");
    output.write("timelineCount: " + timeline.length + "\n");
    for (int i = 0; i < timeline.length; i++)
        output.write("timeline" + i + ": " + timeline[i] + "\n");
}

void ParticleEmitter::load (const BufferedReader& reader) throws IOException {
    super.load(reader);
    if (!active) return;
    colors = new float[readInt(reader, "colorsCount")];
    for (int i = 0; i < colors.length; i++)
        colors[i] = readFloat(reader, "colors" + i);
    timeline = new float[readInt(reader, "timelineCount")];
    for (int i = 0; i < timeline.length; i++)
        timeline[i] = readFloat(reader, "timeline" + i);
}

void ParticleEmitter::load (const GradientColorValue& value) {
    super.load(value);
    colors = new float[value.colors.length];
    System.arraycopy(value.colors, 0, colors, 0, colors.length);
    timeline = new float[value.timeline.length];
    System.arraycopy(value.timeline, 0, timeline, 0, timeline.length);
}

SpawnShape& ParticleEmitter::getShape () {
    return shape;
}

void ParticleEmitter::setShape (const SpawnShape& shape) {
    this.shape = shape;
}

bool ParticleEmitter::isEdges () {
    return edges;
}

void ParticleEmitter::setEdges (bool edges) {
    this.edges = edges;
}

SpawnEllipseSide& ParticleEmitter::getSide () {
    return side;
}

void ParticleEmitter::setSide (const SpawnEllipseSide& side) {
    this.side = side;
}

void ParticleEmitter::save (const Writer& output) throws IOException {
    super.save(output);
    if (!active) return;
    output.write("shape: " + shape + "\n");
    if (shape == SpawnShape.ellipse) {
        output.write("edges: " + edges + "\n");
        output.write("side: " + side + "\n");
    }
}

void ParticleEmitter::load (const BufferedReader& reader) throws IOException {
    super.load(reader);
    if (!active) return;
    shape = SpawnShape.valueOf(readString(reader, "shape"));
    if (shape == SpawnShape.ellipse) {
        edges = readBoolean(reader, "edges");
        side = SpawnEllipseSide.valueOf(readString(reader, "side"));
    }
}

void ParticleEmitter::load (const SpawnShapeValue& value) {
    super.load(value);
    shape = value.shape;
    edges = value.edges;
    side = value.side;
}

