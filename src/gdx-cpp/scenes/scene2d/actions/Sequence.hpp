
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

#ifndef GDX_CPP_SCENES_SCENE2D_ACTIONS_SEQUENCE_HPP_
#define GDX_CPP_SCENES_SCENE2D_ACTIONS_SEQUENCE_HPP_

#include "gdx-cpp/scenes/scene2d/CompositeAction.hpp"
#include "gdx-cpp/scenes/scene2d/Action.hpp"
#include "ActionResetingPool.hpp"

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace actions {

class Sequence: public CompositeAction {
public:
    template<typename T, int size>
    static Sequence* operator() (T(&actions)[size]) {
        Sequence* sequence = pool.obtain();
        
        for (int i = 0; i < sequence->actions.size();  ++i) {
            delete sequence->actions[i];
        }
    
        for (int i = 0; i < size; i++)
            sequence->actions.push_back(actions[i]);
        
        return sequence;
    }
     
    void setTarget (const gdx_cpp::scenes::scene2d::Actor& actor);
    void act (float delta);
    bool isDone ();
    void finish ();
    gdx_cpp::scenes::scene2d::Action& copy ();
    Actor* getTarget ();

protected:
    Sequence* newObject ();
    Actor* target;
    int currAction;

    static ActionResetingPool<Sequence*> pool;
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace actions

#endif // GDX_CPP_SCENES_SCENE2D_ACTIONS_SEQUENCE_HPP_
