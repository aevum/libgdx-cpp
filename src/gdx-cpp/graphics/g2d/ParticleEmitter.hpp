
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
#include <vector>
#include "Sprite.hpp"
#include <string>

namespace gdx {

class ParticleEmitter {
public:
    enum SpawnShape {
        point, line, square, ellipse
    };

    enum SpawnEllipseSide {
        both, top, bottom
    };

    class Particle : public Sprite {

    public:
        Particle (Sprite::ptr sprite);
        int life, currentLife;
        float scale, scaleDiff;
        float rotation, rotationDiff;
        float velocity, velocityDiff;
        float angle, angleDiff;
        float angleCos, angleSin;
        float transparency, transparencyDiff;
        float wind, windDiff;
        float gravity, gravityDiff;
        std::vector<float> tint;

    };

    class ParticleValue {
    public:
        ParticleValue();
        bool active;
        bool alwaysActive;

        void setAlwaysActive (bool alwaysActive);
        bool isAlwaysActive ();
        bool isActive ();
        void setActive (bool active);
        void save (std::ostream& output);
        void load (std::istream& reader);
        void load (ParticleValue& value);
    };

    class NumericValue : public ParticleValue {
    public:
        NumericValue();
        float getValue ();
        void setValue (float value);
        void save (std::ostream& output);
        void load (std::istream& reader);
        void load (NumericValue& value) ;

    private:
        float value;
    };

    class RangedNumericValue: public ParticleValue {
    public:
        RangedNumericValue();
        float newLowValue ();
        void setLow (float value);
        void setLow (float min, float max);
        float getLowMin ();
        void setLowMin (float lowMin);
        float getLowMax ();
        void setLowMax (float lowMax);
        void save (std::ostream& output);
        void load (std::istream& reader);
        void load (RangedNumericValue& value);
    private:
        float lowMin, lowMax;
    };

    class ScaledNumericValue : public RangedNumericValue {
    public:
        std::vector<float> timeline;

        ScaledNumericValue();
        float newHighValue ();
        void setHigh (float value);
        void setHigh (float min, float max);
        float getHighMin ();
        void setHighMin (float highMin);
        float getHighMax ();
        void setHighMax (float highMax);
        std::vector<float>& getScaling ();
        void setScaling (std::vector< float >& values);
        std::vector<float>& getTimeline ();
        void setTimeline (std::vector< float >& _timeline);
        bool isRelative ();
        void setRelative (bool relative);
        float getScale (float percent);
        void save (std::ostream& output);
        void load (std::istream& reader);
        void load (ScaledNumericValue& value);

    private:
        std::vector<float> scaling;
        float highMin, highMax;
        bool relative;
    };
    class GradientColorValue : public ParticleValue {
    public:
        std::vector<float> timeline;

        GradientColorValue ();
        std::vector<float>& getTimeline ();
        void setTimeline (std::vector<float>& timeline);
        std::vector<float>& getColors ();
        void setColors (std::vector<float>& colors);
        std::vector<float>& getColor (float percent);
        void save (std::ostream& output);
        void load (std::istream& reader);
        void load (GradientColorValue& value);

    private :
        std::vector<float> temp;
        std::vector<float> colors ;
    };


    class SpawnShapeValue : public ParticleValue
    {
    public :
        SpawnShapeValue();
        ParticleEmitter::SpawnShape shape;
        bool edges;
        ParticleEmitter::SpawnEllipseSide side;

        ParticleEmitter::SpawnShape getShape ();
        void setShape (ParticleEmitter::SpawnShape shape);
        bool isEdges ();
        void setEdges (bool edges);
        ParticleEmitter::SpawnEllipseSide getSide ();
        void setSide (ParticleEmitter::SpawnEllipseSide side);
        void save (std::ostream& output);
        void load (std::istream& reader);
        void load (SpawnShapeValue& value);

    };

    ~ParticleEmitter();
    ParticleEmitter();
    ParticleEmitter(std::istream& emitter);
    ParticleEmitter(ParticleEmitter& emitter);
    void setMaxParticleCount (int maxParticleCount);
    void addParticle ();
    void addParticles (int count);
    void update (float delta);
    void draw (gdx::SpriteBatch& spriteBatch);
    void draw (gdx::SpriteBatch& spriteBatch, float delta);
    void start ();
    void reset ();
    void setPosition (float x,float y);
    void setSprite (Sprite::ptr sprite);
    void allowCompletion ();
    Sprite::ptr getSprite ();
    std::string& getName ();
    void setName (std::string& name);
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
    std::string getImagePath ();
    void setImagePath (const std::string& imagePath);
    void setFlip (bool flipX,bool flipY);
    void save (std::ostream& output);
    void load (std::istream& reader);


    float duration, durationTimer;

protected:


private:
    void initialize ();
    void restart ();
    int nextClearBit();
    void activateParticle (int index);
    bool updateParticle (int index,float delta,int deltaMillis);

    const static int UPDATE_SCALE = 1 << 0;
    const static int UPDATE_ANGLE = 1 << 1;
    const static int UPDATE_ROTATION = 1 << 2;
    const static int UPDATE_VELOCITY = 1 << 3;
    const static int UPDATE_WIND = 1 << 4;
    const static int UPDATE_GRAVITY = 1 << 5;
    const static int UPDATE_TINT = 1 << 6;


    RangedNumericValue delayValue;
    ScaledNumericValue lifeOffsetValue;
    RangedNumericValue durationValue;
    ScaledNumericValue lifeValue;
    ScaledNumericValue emissionValue;
    ScaledNumericValue scaleValue;
    ScaledNumericValue rotationValue;
    ScaledNumericValue velocityValue;
    ScaledNumericValue angleValue;
    ScaledNumericValue windValue;
    ScaledNumericValue gravityValue;
    ScaledNumericValue transparencyValue;
    GradientColorValue tintValue;
    RangedNumericValue xOffsetValue;
    RangedNumericValue yOffsetValue;
    ScaledNumericValue spawnWidthValue;
    ScaledNumericValue spawnHeightValue;
    SpawnShapeValue spawnShapeValue;

    float accumulator;
    Sprite::ptr sprite;
    std::vector<Particle *> particles;
    int minParticleCount, maxParticleCount;
    float x, y;
    std::string name;
    std::string imagePath;
    int activeCount;
    std::vector<bool> active;
    bool firstUpdate;
    bool flipX, flipY;
    int updateFlags;
    bool allowCompletionVar;

    int emission, emissionDiff, emissionDelta;
    int lifeOffset, lifeOffsetDiff;
    int life, lifeDiff;
    int spawnWidth, spawnWidthDiff;
    int spawnHeight, spawnHeightDiff;
    float delay, delayTimer;

    bool attached;
    bool continuous;
    bool aligned;
    bool behind;
    bool additive;
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_PARTICLEEMITTER_HPP_
