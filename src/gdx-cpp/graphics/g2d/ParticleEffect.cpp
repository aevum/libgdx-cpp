
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

#include <stddef.h>
#include <iostream>
#include <memory>

#include "ParticleEffect.hpp"
#include "ParticleEmitter.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"
#include "gdx-cpp/graphics/g2d/Sprite.hpp"

using namespace gdx;

ParticleEffect::ParticleEffect () {
    emitters.reserve(8);
}

ParticleEffect::ParticleEffect (ParticleEffect& effect) {
    emitters.resize(effect.emitters.size());
    for (unsigned int i = 0, n = effect.emitters.size(); i < n; i++)
        emitters[i] = new ParticleEmitter(*effect.emitters[i]);
}

ParticleEffect::~ParticleEffect () {
    for (unsigned int i = 0, n = emitters.size(); i < n; i++)
    {
        if (emitters[i] != NULL) {
            delete emitters[i];
        }
    }
}

void ParticleEffect::start () {
    for (unsigned int i = 0, n = emitters.size(); i < n; i++)
        emitters[i]->start();
}

void ParticleEffect::update (float delta) {
    for (unsigned int i = 0, n = emitters.size(); i < n; i++)
        emitters[i]->update(delta);
}

void ParticleEffect::draw (SpriteBatch& spriteBatch) {
    for (unsigned int i = 0, n = emitters.size(); i < n; i++)
        emitters[i]->draw(spriteBatch);
}

void ParticleEffect::draw (SpriteBatch& spriteBatch, float delta) {
    for (unsigned int i = 0, n = emitters.size(); i < n; i++)
        emitters[i]->draw(spriteBatch, delta);
}

void ParticleEffect::allowCompletion () {
    for (unsigned int i = 0, n = emitters.size(); i < n; i++)
        emitters[i]->allowCompletion();
}

bool ParticleEffect::isComplete () {
    for (unsigned int i = 0, n = emitters.size(); i < n; i++) {
        ParticleEmitter * emitter = emitters[i];
        if (emitter->isContinuous()) return false;
        if (!emitter->isComplete()) return false;
    }
    return true;
}

void ParticleEffect::setDuration (int duration) {
    for (unsigned int i = 0, n = emitters.size(); i < n; i++) {
        ParticleEmitter * emitter = emitters[i];
        emitter->setContinuous(false);
        emitter->duration = duration;
        emitter->durationTimer = 0;
    }
}

void ParticleEffect::setPosition (float x,float y) {
    for (unsigned int i = 0, n = emitters.size(); i < n; i++)
        emitters[i]->setPosition(x, y);
}

void ParticleEffect::setFlip (bool flipX,bool flipY) {
    for (unsigned int i = 0, n = emitters.size(); i < n; i++)
        emitters[i]->setFlip(flipX, flipY);
}

std::vector< ParticleEmitter * >& ParticleEffect::getEmitters () {
    return emitters;
}

ParticleEmitter* ParticleEffect::findEmitter (const std::string& name) {
    for (unsigned int i = 0, n = emitters.size(); i < n; i++) {
        if (emitters[i]->getName() == name) return emitters[i];
    }
    return NULL;
}

void ParticleEffect::save (const File& file) {
//     Writer output = NULL;
//     try {
//         output = new FileWriter(file);
//         int index = 0;
//         for (unsigned int i = 0, n = emitters.size(); i < n; i++) {
//             ParticleEmitter  * emitter = emitters[i];
//             if (index++ > 0) output.write("\n\n");
//             emitter.save(output);
//             output.write("- Image Path -\n");
//             output.write(emitter.getImagePath() + "\n");
//         }
//     } catch (IOException ex) {
//         throw new GdxRuntimeException("Error saving effect: " + file, ex);
//     }
//     finally {
//         try {
//             if (output != null) output.close();
//         } catch (IOException ex) {
//         }
//     }
}
void ParticleEffect::load (std::string file)
{
    loadEmittersTest(file);
    loadEmitterImagesTest();
}
void ParticleEffect::load (const FileHandle& effectFile,const FileHandle& imagesDir) {
    loadEmitters(effectFile);
    loadEmitterImages(imagesDir);
}

void ParticleEffect::load (const FileHandle& effectFile,const TextureAtlas& atlas) {
    loadEmitters(effectFile);
    loadEmitterImages(atlas);
}

void ParticleEffect::loadEmitters (const FileHandle& effectFile) {
//     InputStream input = effectFile.read();
//     emitters.clear();
//     BufferedReader reader = null;
//     try {
//         reader = new BufferedReader(new InputStreamReader(input), 512);
//         while (true) {
//             ParticleEmitter emitter = new ParticleEmitter(reader);
//             reader.readLine();
//             emitter.setImagePath(reader.readLine());
//             emitters.add(emitter);
//             if (reader.readLine() == null) break;
//             if (reader.readLine() == null) break;
//         }
//     } catch (IOException ex) {
//         throw new GdxRuntimeException("Error loading effect: " + effectFile, ex);
//     }
//     finally {
//         try {
//             if (reader != null) reader.close();
//         } catch (IOException ex) {
//         }
//     }
}

void ParticleEffect::loadEmitterImages (const TextureAtlas& atlas) {
//     for (unsigned int i = 0, n = emitters.size; i < n; i++) {
//         ParticleEmitter emitter = emitters.get(i);
//         String imagePath = emitter.getImagePath();
//         if (imagePath == null) continue;
//         String imageName = new File(imagePath.replace('\\', '/')).getName();
//         int lastDotIndex = imageName.lastIndexOf('.');
//         if (lastDotIndex != -1) imageName = imageName.substring(0, lastDotIndex);
//         Sprite sprite = atlas.createSprite(imageName);
//         if (sprite == null) throw new IllegalArgumentException("SpriteSheet missing image: " + imageName);
//         emitter.setSprite(sprite);
//     }
}

void ParticleEffect::loadEmitterImages (const FileHandle& imagesDir) {
//     for (unsigned int i = 0, n = emitters.size; i < n; i++) {
//         ParticleEmitter emitter = emitters.get(i);
//         String imagePath = emitter.getImagePath();
//         if (imagePath == null) continue;
//         String imageName = new File(imagePath.replace('\\', '/')).getName();
//         emitter.setSprite(new Sprite(loadTexture(imagesDir.child(imageName))));
//     }
}

void ParticleEffect::loadEmittersTest (std::string file) {
    emitters.clear();
        std::istream * reader = new std::ifstream(file.c_str());
        std::string by;
        while (true) {
            ParticleEmitter * emitter = new ParticleEmitter(*reader);
            std::getline(*reader, by);
            std::getline(*reader, by);
            emitter->setImagePath("");
            emitters.push_back(emitter);
            std::getline(*reader, by);
            std::getline(*reader, by);
            if (reader->eof()) break;
        }
}


void ParticleEffect::loadEmitterImagesTest () {
    for (unsigned int i = 0, n = emitters.size(); i < n; i++) {
        ParticleEmitter * emitter = emitters[i];

        Pixmap::ptr pixmap = Pixmap::newFromRect(16, 16, Pixmap::Format::RGBA8888, Pixmap::PixmapType::PixmapType_Gdx2d);
        
        pixmap->setColor(1 ,1 ,1 ,0.5f);
        pixmap->fill();

        Texture::ptr texture = Texture::ptr(new Texture(pixmap, false));
        texture->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);

        Sprite::ptr sprite =  Sprite::ptr(new Sprite(texture, 16, 16));
        emitter->setSprite(sprite);
    }
}

Texture::ptr ParticleEffect::loadTexture (const FileHandle::ptr file) {
    return Texture::newFromFile(file, NULL, false);
}

void ParticleEffect::dispose () {
//     for (unsigned int i = 0, n = emitters.size(); i < n; i++) {
//         ParticleEmitter * emitter = emitters[i];
//         emitter->getSprite()->getTexture()->dispose();
//     }
}

