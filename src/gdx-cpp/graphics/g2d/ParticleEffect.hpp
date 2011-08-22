
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

#ifndef GDX_CPP_GRAPHICS_G2D_PARTICLEEFFECT_HPP_
#define GDX_CPP_GRAPHICS_G2D_PARTICLEEFFECT_HPP_

namespace gdx_cpp {
namespace graphics {
namespace g2d {

class ParticleEffect: public gdx_cpp::utils::Disposable {
public:
    void start ();
    void update (float delta);
    void draw (const SpriteBatch& spriteBatch);
    void draw (const SpriteBatch& spriteBatch,float delta);
    void allowCompletion ();
    bool isComplete ();
    void setDuration (int duration);
    void setPosition (float x,float y);
    void setFlip (bool flipX,bool flipY);
    gdx_cpp::utils::ArrayParticleEmitter>& getEmitters ();
    ParticleEmitter& findEmitter (const std::string& name);
    void save (const File& file);
    void load (const gdx_cpp::files::FileHandle& effectFile,const gdx_cpp::files::FileHandle& imagesDir);
    void load (const gdx_cpp::files::FileHandle& effectFile,const TextureAtlas& atlas);
    void loadEmitters (const gdx_cpp::files::FileHandle& effectFile);
    void loadEmitterImages (const TextureAtlas& atlas);
    void loadEmitterImages (const gdx_cpp::files::FileHandle& imagesDir);
    void dispose ();

protected:
    gdx_cpp::graphics::Texture& loadTexture (const gdx_cpp::files::FileHandle& file);

private:
    Array<ParticleEmitter> emitters;
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_PARTICLEEFFECT_HPP_
