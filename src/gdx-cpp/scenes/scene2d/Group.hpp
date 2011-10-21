
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

#ifndef GDX_CPP_SCENES_SCENE2D_GROUP_HPP_
#define GDX_CPP_SCENES_SCENE2D_GROUP_HPP_

#include <list>
#include <string>

#include "gdx-cpp/graphics/g2d/SpriteBatch.hpp"
#include "gdx-cpp/graphics/Texture.hpp"

#include "Actor.hpp"

#include "gdx-cpp/math/Matrix3.hpp"
#include "gdx-cpp/math/Matrix4.hpp"
#include "gdx-cpp/math/Vector2.hpp"

#include <tr1/unordered_map>

namespace gdx_cpp {
namespace scenes {
namespace scene2d {

class Group : public Actor {
public:
    ActorType getType() { return Actor_Group; }
    
    void act (float delta);
    void draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha);
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    bool touchMoved (float x,float y);
    void touchDragged (float x,float y,int pointer);
    bool scrolled (int amount);
    bool keyDown (int keycode);
    bool keyUp (int keycode);
    bool keyTyped (char character);
    Actor* hit (float x, float y);
    void addActor (const gdx_cpp::scenes::scene2d::Actor* actor);
    void addActorAt (int index, const gdx_cpp::scenes::scene2d::Actor* actor);
    void addActorBefore (const gdx_cpp::scenes::scene2d::Actor* actorBefore, const gdx_cpp::scenes::scene2d::Actor* actor);
    void addActorAfter (const gdx_cpp::scenes::scene2d::Actor* actorAfter, const gdx_cpp::scenes::scene2d::Actor* actor);
    void removeActor (const gdx_cpp::scenes::scene2d::Actor* actor);
    void removeActorRecursive (const gdx_cpp::scenes::scene2d::Actor* actor);
    Actor& findActor (const std::string& name);
    bool swapActor (int first,int second);
    bool swapActor (const gdx_cpp::scenes::scene2d::Actor* first, const gdx_cpp::scenes::scene2d::Actor* second);
    std::list<Actor>& getActors ();
    std::list<Group>& getGroups ();
    void focus (const gdx_cpp::scenes::scene2d::Actor* actor, int pointer);
    void keyboardFocus (const gdx_cpp::scenes::scene2d::Actor* actor);
    void scrollFocus (const gdx_cpp::scenes::scene2d::Actor* actor);
    void clear ();
    void sortChildren (const Comparator<Actor>& comparator);
    void unfocusAll ();
    void unfocusAll (const gdx_cpp::scenes::scene2d::Actor* actor);
    static void toChildCoordinates (const gdx_cpp::scenes::scene2d::Actor* child, float x, float y, const gdx_cpp::math::Vector2& out);
    void enableDebugging (const std::string& debugTextureFile);
    void disableDebugging ();
    Group ();
    Group (const std::string& name);

    static gdx_cpp::graphics::Texture::ptr debugTexture ;
    static bool debug;
    
    bool transform;
    Actor* lastTouchedChild ;
    Actor* focusedActor[20];
    Actor* keyboardFocusedActor;
    Actor* scrollFocusedActor;

protected:
    void drawChildren (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha);
    void drawChild (const Actor& child,const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha);
    void applyTransform (const gdx_cpp::graphics::g2d::SpriteBatch& batch);
    gdx_cpp::math::Matrix4& updateTransform ();
    void resetTransform (const gdx_cpp::graphics::g2d::SpriteBatch& batch);

    typedef std::vector<Actor*> ActorList;
    ActorList children;
    ActorList immutableChildren;
    std::list<Group*> groups;
    std::list<Group*> immutableGroups;

    std::tr1::unordered_map<std::string, Actor*> namesToActors;

    gdx_cpp::math::Matrix3 localTransform;
    gdx_cpp::math::Matrix3 worldTransform;
    gdx_cpp::math::Matrix4 batchTransform;
    gdx_cpp::math::Matrix4 oldBatchTransform;
    gdx_cpp::math::Vector2 point;

private:

};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d

#endif // GDX_CPP_SCENES_SCENE2D_GROUP_HPP_
