
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

namespace gdx {
namespace scenes {
namespace scene2d {

class Group : public Actor {
public:
    typedef std::vector<Actor*> ActorList;
    ActorType getType() const { return Actor_Group; }
    
    void act (float delta);
    void draw (gdx::SpriteBatch& batch, float parentAlpha);
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    bool touchMoved (float x,float y);
    void touchDragged (float x,float y,int pointer);
    bool scrolled (int amount);
    bool keyDown (int keycode);
    bool keyUp (int keycode);
    bool keyTyped (char character);
    Actor* hit (float x, float y);
    void addActor (gdx::Actor* actor);
    void addActorAt (int index, gdx::Actor* actor);
    void addActorBefore (const gdx::Actor* actorBefore, gdx::Actor* actor);
    void addActorAfter (const gdx::Actor* actorAfter, gdx::Actor* actor);
    void removeActor (gdx::Actor* actor);
    void removeActorRecursive (gdx::Actor* actor);
    Actor* findActor (const std::string& name);
    bool swapActor (int first,int second);
    bool swapActor (gdx::Actor* first, gdx::Actor* second);
    Group::ActorList getActors ();
    std::list< Group* > getGroups ();
    void focus (gdx::Actor* actor, int pointer);
    void keyboardFocus (gdx::Actor* actor);
    void scrollFocus (gdx::Actor* actor);
    void clear ();
    void sortChildren (bool (*comparator)(Actor* a, Actor* b));
    void unfocusAll ();
    void unfocusAll (const gdx::Actor* actor);
    static void toChildCoordinates (gdx::Actor* const child, float x, float y, gdx::Vector2& out);
    void enableDebugging (const std::string& debugTextureFile);
    void disableDebugging ();
    Group ();
    Group (const std::string& name);

    static gdx::Texture::ptr debugTexture ;
    static bool debug;
    
    bool transform;
    Actor* lastTouchedChild ;
    Actor* focusedActor[20];
    Actor* keyboardFocusedActor;
    Actor* scrollFocusedActor;

protected:
    void drawChildren (gdx::SpriteBatch& batch, float parentAlpha);
    void drawChild (gdx::Actor* child, gdx::SpriteBatch& batch, float parentAlpha);
    void applyTransform (gdx::SpriteBatch& batch);
    gdx::Matrix4& updateTransform ();
    void resetTransform (gdx::SpriteBatch& batch);
    
    ActorList children;
    ActorList immutableChildren;
    std::list<Group*> groups;
    std::list<Group*> immutableGroups;

    std::tr1::unordered_map<std::string, Actor*> namesToActors;

    gdx::Matrix3 localTransform;
    gdx::Matrix3 worldTransform;
    gdx::Matrix4 batchTransform;
    gdx::Matrix4 oldBatchTransform;
    gdx::Vector2 point;

private:

};

} // namespace gdx
} // namespace scenes
} // namespace scene2d

#endif // GDX_CPP_SCENES_SCENE2D_GROUP_HPP_
