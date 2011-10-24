
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

#ifndef GDX_CPP_SCENES_SCENE2D_STAGE_HPP_
#define GDX_CPP_SCENES_SCENE2D_STAGE_HPP_

#include <string>
#include <list>

#include "gdx-cpp/graphics/g2d/SpriteBatch.hpp"
#include "gdx-cpp/graphics/Camera.hpp"
#include "gdx-cpp/math/Vector2.hpp"
#include "Group.hpp"

namespace gdx_cpp {
namespace scenes {
namespace scene2d {

class Actor;
class Group;

class Stage {
public:
    void setViewport (float width,float height,bool stretch);
    float width ();
    float height ();
    int left ();
    float right ();
    float top ();
    float bottom ();
    float centerX ();
    float centerY ();
    bool isStretched ();
    Actor* findActor (const std::string& name);
    Group::ActorList getActors ();
    std::list<Group*> getGroups ();
    bool touchDown (int x,int y,int pointer,int button);
    bool touchUp (int x,int y,int pointer,int button);
    bool touchDragged (int x,int y,int pointer);
    bool touchMoved (int x,int y);
    bool scrolled (int amount);
    bool keyDown (int keycode);
    bool keyUp (int keycode);
    bool keyTyped (char character);
    void act (float delta);
    void draw ();
    void dispose ();
    void addActor (gdx_cpp::scenes::scene2d::Actor*const actor);
    std::string graphToString ();
    Group& getRoot ();
    graphics::g2d::SpriteBatch* getSpriteBatch ();
    graphics::Camera*const getCamera ();
    void setCamera (gdx_cpp::graphics::Camera* camera);
    Actor* getLastTouchedChild ();
    Actor* hit (float x, float y);
    void toStageCoordinates (int x, int y, gdx_cpp::math::Vector2& out);
    void clear ();
    void removeActor (gdx_cpp::scenes::scene2d::Actor* actor);
    void unfocusAll ();
    Stage (float width,float height,bool stretch);

    ~Stage();
    
protected:
    float _width ;
    float _height ;
    float _centerX ;
    float _centerY ;
    bool stretch ;
    Group root ;
    graphics::g2d::SpriteBatch* batch ;
    graphics::Camera* camera ;

    math::Vector2 point;
    math::Vector2 coords;
    math::Vector3 tmp;
private:
    void graphToString (std::stringstream& buffer, const gdx_cpp::scenes::scene2d::Actor* actor, int level);
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d

#endif // GDX_CPP_SCENES_SCENE2D_STAGE_HPP_
