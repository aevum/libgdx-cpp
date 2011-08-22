
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

#include "ParticleEffect.hpp"

using namespace gdx_cpp::graphics::g2d;

void ParticleEffect::start () {
    for (int i = 0, n = emitters.size; i < n; i++)
        emitters.get(i).start();
}

void ParticleEffect::update (float delta) {
    for (int i = 0, n = emitters.size; i < n; i++)
        emitters.get(i).update(delta);
}

void ParticleEffect::draw (const SpriteBatch& spriteBatch) {
    for (int i = 0, n = emitters.size; i < n; i++)
        emitters.get(i).draw(spriteBatch);
}

void ParticleEffect::draw (const SpriteBatch& spriteBatch,float delta) {
    for (int i = 0, n = emitters.size; i < n; i++)
        emitters.get(i).draw(spriteBatch, delta);
}

void ParticleEffect::allowCompletion () {
    for (int i = 0, n = emitters.size; i < n; i++)
        emitters.get(i).allowCompletion();
}

bool ParticleEffect::isComplete () {
    for (int i = 0, n = emitters.size; i < n; i++) {
        ParticleEmitter emitter = emitters.get(i);
        if (emitter.isContinuous()) return false;
        if (!emitter.isComplete()) return false;
    }
    return true;
}

void ParticleEffect::setDuration (int duration) {
    for (int i = 0, n = emitters.size; i < n; i++) {
        ParticleEmitter emitter = emitters.get(i);
        emitter.setContinuous(false);
        emitter.duration = duration;
        emitter.durationTimer = 0;
    }
}

void ParticleEffect::setPosition (float x,float y) {
    for (int i = 0, n = emitters.size; i < n; i++)
        emitters.get(i).setPosition(x, y);
}

void ParticleEffect::setFlip (bool flipX,bool flipY) {
    for (int i = 0, n = emitters.size; i < n; i++)
        emitters.get(i).setFlip(flipX, flipY);
}

gdx_cpp::utils::ArrayParticleEmitter>& ParticleEffect::getEmitters () {
    return emitters;
}

ParticleEmitter& ParticleEffect::findEmitter (const std::string& name) {
    for (int i = 0, n = emitters.size; i < n; i++) {
        ParticleEmitter emitter = emitters.get(i);
        if (emitter.getName().equals(name)) return emitter;
    }
    return null;
}

void ParticleEffect::save (const File& file) {
    Writer output = null;
    try {
        output = new FileWriter(file);
        int index = 0;
        for (int i = 0, n = emitters.size; i < n; i++) {
            ParticleEmitter emitter = emitters.get(i);
            if (index++ > 0) output.write("\n\n");
            emitter.save(output);
            output.write("- Image Path -\n");
            output.write(emitter.getImagePath() + "\n");
        }
    } catch (IOException ex) {
        throw new GdxRuntimeException("Error saving effect: " + file, ex);
    }
    finally {
        try {
            if (output != null) output.close();
        } catch (IOException ex) {
        }
    }
}

void ParticleEffect::load (const gdx_cpp::files::FileHandle& effectFile,const gdx_cpp::files::FileHandle& imagesDir) {
    loadEmitters(effectFile);
    loadEmitterImages(imagesDir);
}

void ParticleEffect::load (const gdx_cpp::files::FileHandle& effectFile,const TextureAtlas& atlas) {
    loadEmitters(effectFile);
    loadEmitterImages(atlas);
}

void ParticleEffect::loadEmitters (const gdx_cpp::files::FileHandle& effectFile) {
    InputStream input = effectFile.read();
    emitters.clear();
    BufferedReader reader = null;
    try {
        reader = new BufferedReader(new InputStreamReader(input), 512);
        while (true) {
            ParticleEmitter emitter = new ParticleEmitter(reader);
            reader.readLine();
            emitter.setImagePath(reader.readLine());
            emitters.add(emitter);
            if (reader.readLine() == null) break;
            if (reader.readLine() == null) break;
        }
    } catch (IOException ex) {
        throw new GdxRuntimeException("Error loading effect: " + effectFile, ex);
    }
    finally {
        try {
            if (reader != null) reader.close();
        } catch (IOException ex) {
        }
    }
}

void ParticleEffect::loadEmitterImages (const TextureAtlas& atlas) {
    for (int i = 0, n = emitters.size; i < n; i++) {
        ParticleEmitter emitter = emitters.get(i);
        String imagePath = emitter.getImagePath();
        if (imagePath == null) continue;
        String imageName = new File(imagePath.replace('\\', '/')).getName();
        int lastDotIndex = imageName.lastIndexOf('.');
        if (lastDotIndex != -1) imageName = imageName.substring(0, lastDotIndex);
        Sprite sprite = atlas.createSprite(imageName);
        if (sprite == null) throw new IllegalArgumentException("SpriteSheet missing image: " + imageName);
        emitter.setSprite(sprite);
    }
}

void ParticleEffect::loadEmitterImages (const gdx_cpp::files::FileHandle& imagesDir) {
    for (int i = 0, n = emitters.size; i < n; i++) {
        ParticleEmitter emitter = emitters.get(i);
        String imagePath = emitter.getImagePath();
        if (imagePath == null) continue;
        String imageName = new File(imagePath.replace('\\', '/')).getName();
        emitter.setSprite(new Sprite(loadTexture(imagesDir.child(imageName))));
    }
}

gdx_cpp::graphics::Texture& ParticleEffect::loadTexture (const gdx_cpp::files::FileHandle& file) {
    return new Texture(file, false);
}

void ParticleEffect::dispose () {
    for (int i = 0, n = emitters.size; i < n; i++) {
        ParticleEmitter emitter = emitters.get(i);
        emitter.getSprite().getTexture().dispose();
    }
}

