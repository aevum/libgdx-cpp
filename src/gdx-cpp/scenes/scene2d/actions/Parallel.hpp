
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

#ifndef GDX_CPP_SCENES_SCENE2D_ACTIONS_PARALLEL_HPP_
#define GDX_CPP_SCENES_SCENE2D_ACTIONS_PARALLEL_HPP_

#include "gdx-cpp/scenes/scene2d/CompositeAction.hpp"
#include "gdx-cpp/scenes/scene2d/Action.hpp"
#include "ActionResetingPool.hpp"

#include <vector>

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace actions {

class Parallel: public gdx_cpp::scenes::scene2d::CompositeAction {
public:
    template < Action*, int size >
    static Parallel* build(Action* (&actions)[size]) {
        Parallel* parallel = pool.obtain();
        parallel->actions.clear();
        if (parallel->finished.empty() || parallel->finished.size() < size)
            parallel->finished.resize(size);
        
        for (int i = 0; i < size; i++) {
            parallel->finished[i] = false;
            parallel->actions.push_back(actions[i]);
        }
        
        return parallel;
    }
    
    void setTarget (gdx_cpp::scenes::scene2d::Actor* actor);
    void act (float delta);
    bool isDone ();
    void finish ();
    Action* copy ();
    Actor* getTarget ();

protected:
    std::vector<bool> finished;
    Actor* target;

    static ActionResetingPool<Parallel> pool;
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace actions

#endif // GDX_CPP_SCENES_SCENE2D_ACTIONS_PARALLEL_HPP_
