
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

#ifndef GDX_CPP_GRAPHICS_G2D_PARTICLEEMITTER_HPP_
#define GDX_CPP_GRAPHICS_G2D_PARTICLEEMITTER_HPP_

namespace gdx_cpp {
namespace graphics {
namespace g2d {

class ParticleEmitter {
public:
    void setMaxParticleCount (int maxParticleCount);
    void addParticle ();
    void addParticles (int count);
    void update (float delta);
    void draw (const SpriteBatch& spriteBatch);
    void draw (const SpriteBatch& spriteBatch,float delta);
    void start ();
    void reset ();
    void setPosition (float x,float y);
    void setSprite (const Sprite& sprite);
    void allowCompletion ();
    Sprite& getSprite ();
    std::string& getName ();
    void setName (const std::string& name);
    ScaledNumericValue& getLife ();
    ScaledNumericValue& getScale ();
    ScaledNumericValue& getRotation ();
    GradientColorValue& getTint ();
    ScaledNumericValue& getVelocity ();
    ScaledNumericValue& getWind ();
    ScaledNumericValue& getGravity ();
    ScaledNumericValue& getAngle ();
    ScaledNumericValue& getEmission ();
    ScaledNumericValue& getTransparency ();
    RangedNumericValue& getDuration ();
    RangedNumericValue& getDelay ();
    ScaledNumericValue& getLifeOffset ();
    RangedNumericValue& getXOffsetValue ();
    RangedNumericValue& getYOffsetValue ();
    ScaledNumericValue& getSpawnWidth ();
    ScaledNumericValue& getSpawnHeight ();
    SpawnShapeValue& getSpawnShape ();
    bool isAttached ();
    void setAttached (bool attached);
    bool isContinuous ();
    void setContinuous (bool continuous);
    bool isAligned ();
    void setAligned (bool aligned);
    bool isAdditive ();
    void setAdditive (bool additive);
    bool isBehind ();
    void setBehind (bool behind);
    int getMinParticleCount ();
    void setMinParticleCount (int minParticleCount);
    int getMaxParticleCount ();
    bool isComplete ();
    float getPercentComplete ();
    float getX ();
    float getY ();
    int getActiveCount ();
    int getDrawCount ();
    std::string& getImagePath ();
    void setImagePath (const std::string& imagePath);
    void setFlip (bool flipX,bool flipY);
    void save (const Writer& output);
    void load (const BufferedReader& reader);
    void setAlwaysActive (bool alwaysActive);
    bool isAlwaysActive ();
    bool isActive ();
    void setActive (bool active);
    void save (const Writer& output);
    void load (const BufferedReader& reader);
    void load (const ParticleValue& value);
    float getValue ();
    void setValue (float value);
    void save (const Writer& output);
    void load (const BufferedReader& reader);
    void load (const NumericValue& value);
    float newLowValue ();
    void setLow (float value);
    void setLow (float min,float max);
    float getLowMin ();
    void setLowMin (float lowMin);
    float getLowMax ();
    void setLowMax (float lowMax);
    void save (const Writer& output);
    void load (const BufferedReader& reader);
    void load (const RangedNumericValue& value);
    float newHighValue ();
    void setHigh (float value);
    void setHigh (float min,float max);
    float getHighMin ();
    void setHighMin (float highMin);
    float getHighMax ();
    void setHighMax (float highMax);
    float* getScaling ();
    void setScaling ();
    float* getTimeline ();
    void setTimeline ();
    bool isRelative ();
    void setRelative (bool relative);
    float getScale (float percent);
    void save (const Writer& output);
    void load (const BufferedReader& reader);
    void load (const ScaledNumericValue& value);
    float* getTimeline ();
    void setTimeline ();
    float* getColors ();
    void setColors ();
    float* getColor (float percent);
    void save (const Writer& output);
    void load (const BufferedReader& reader);
    void load (const GradientColorValue& value);
    SpawnShape& getShape ();
    void setShape (const SpawnShape& shape);
    bool isEdges ();
    void setEdges (bool edges);
    SpawnEllipseSide& getSide ();
    void setSide (const SpawnEllipseSide& side);
    void save (const Writer& output);
    void load (const BufferedReader& reader);
    void load (const SpawnShapeValue& value);

protected:


private:
    void initialize ();
    void restart ();
    void activateParticle (int index);
    bool updateParticle (int index,float delta,int deltaMillis);
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_PARTICLEEMITTER_HPP_
