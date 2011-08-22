
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

namespace gdx_cpp {
namespace scenes {
namespace scene2d {

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
    Actor& findActor (const std::string& name);
    std::list<Actor>& getActors ();
    std::list<Group>& getGroups ();
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
    void addActor (const Actor& actor);
    std::string& graphToString ();
    Group& getRoot ();
    gdx_cpp::graphics::g2d::SpriteBatch& getSpriteBatch ();
    gdx_cpp::graphics::Camera& getCamera ();
    void setCamera (const gdx_cpp::graphics::Camera& camera);
    Actor& getLastTouchedChild ();
    Actor& hit (float x,float y);
    void toStageCoordinates (int x,int y,const gdx_cpp::math::Vector2& out);
    void clear ();
    void removeActor (const Actor& actor);
    void unfocusAll ();

protected:
    Group root;
    SpriteBatch batch;

private:
    void graphToString (const StringBuilder& buffer,const Actor& actor,int level);
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d

#endif // GDX_CPP_SCENES_SCENE2D_STAGE_HPP_
