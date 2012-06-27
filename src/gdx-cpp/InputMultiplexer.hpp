
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

#ifndef GDX_CPP__INPUTMULTIPLEXER_HPP_
#define GDX_CPP__INPUTMULTIPLEXER_HPP_
#include <vector>

namespace gdx {

class InputProcessor;


class InputMultiplexer {
public:
    InputMultiplexer();
    void addProcessor ( gdx::InputProcessor* processor);
    void removeProcessor (InputProcessor* processor);
    bool keyDown (int keycode);
    bool keyUp (int keycode);
    bool keyTyped (char character);
    bool touchDown (int x,int y,int pointer,int button);
    bool touchUp (int x,int y,int pointer,int button);
    bool touchDragged (int x,int y,int pointer);
    bool touchMoved (int x,int y);
    bool scrolled (int amount);

protected:


private:
    std::vector<InputProcessor*> processors;
};

} // namespace gdx

#endif // GDX_CPP__INPUTMULTIPLEXER_HPP_
