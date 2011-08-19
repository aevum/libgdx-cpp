
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

#ifndef GDX_CPP_SCENES_SCENE2D_ACTION_HPP_
#define GDX_CPP_SCENES_SCENE2D_ACTION_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {

class Action {
public:
    virtual   void setTarget (const Actor& actor) = 0;
    virtual   Actor& getTarget () = 0;
    virtual   void act (float delta) = 0;
    virtual   bool isDone () = 0;
    void finish ();
    void callActionCompletedListener ();
    virtual   Action& copy () = 0;
    Action& setCompletionListener (const final& OnActionCompleted);
    OnActionCompleted& getCompletionListener ();
    void reset ();

protected:


private:

};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d

#endif // GDX_CPP_SCENES_SCENE2D_ACTION_HPP_
