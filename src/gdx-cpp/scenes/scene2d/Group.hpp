
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

namespace gdx_cpp {
namespace scenes {
namespace scene2d {

class Group {
public:
    void act (float delta);
    void draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha);
    static void toChildCoordinates (const Actor& child,float x,float y,const gdx_cpp::math::Vector2& out);
    bool touchDown (float x,float y,int pointer);
    bool touchUp (float x,float y,int pointer);
    bool touchMoved (float x,float y);
    bool touchDragged (float x,float y,int pointer);
    bool scrolled (int amount);
    bool keyDown (int keycode);
    bool keyUp (int keycode);
    bool keyTyped (char character);
    Actor& hit (float x,float y);
    void addActor (const Actor& actor);
    void addActorAt (int index,const Actor& actor);
    void addActorBefore (const Actor& actorBefore,const Actor& actor);
    void addActorAfter (const Actor& actorAfter,const Actor& actor);
    void removeActor (const Actor& actor);
    void removeActorRecursive (const Actor& actor);
    Actor& findActor (const std::string& name);
    bool swapActor (int first,int second);
    bool swapActor (const Actor& first,const Actor& second);
    std::list<Actor>& getActors ();
    std::list<Group>& getGroups ();
    void focus (const Actor& actor,int pointer);
    void keyboardFocus (const Actor& actor);
    void scrollFocus (const Actor& actor);
    static void enableDebugging (const std::string& debugTextureFile);
    static void disableDebugging ();
    void clear ();
    void sortChildren (const Comparator<Actor>& comparator);
    void unfocusAll ();
    void unfocusAll (const Actor& actor);
    static Texture debugTexture;

protected:
    void updateTransform ();
    void setupTransform (const gdx_cpp::graphics::g2d::SpriteBatch& batch);
    void drawChildren (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha);
    void drawChild (const Actor& child,const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha);
    void resetTransform (const gdx_cpp::graphics::g2d::SpriteBatch& batch);
    Matrix3 transform;
    List<Actor> children;
    List<Actor> immutableChildren;
    List<Group> groups;
    List<Group> immutableGroups;

private:

};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d

#endif // GDX_CPP_SCENES_SCENE2D_GROUP_HPP_
