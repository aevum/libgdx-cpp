/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 */

#ifndef GDX_CPP_UTILS_APPLICATIONLISTENERDECORATOR_HPP
#define GDX_CPP_UTILS_APPLICATIONLISTENERDECORATOR_HPP

#include "gdx-cpp/ApplicationListener.hpp"
#include <cassert>

namespace gdx {

/**Simple decorator to delay the ApplicationListener creation.
This is useful if you don't want to use some early system-dependant classes
(like SpriteBatch) as pointers. Pass this as an argument for the createApplication method.

This decorator *should* be inlined when used, so the performance hit is minimal

*/
template <typename RealApplication>
class ApplicationListenerDecorator : public ApplicationListener
{
public:
    ApplicationListenerDecorator() : app(0) {
    }

    void create() {
        app = new RealApplication;
        app->create();
    }
    
    void dispose() {
        assert(app);
        app->dispose();
    }
    void pause() {
        assert(app);
        app->dispose();
    }
    
    void render() {
        assert(app);
        app->render();
    }
    
    void resize(int width, int height) {
        assert(app);
        app->resize(width,height);
    }
    
    void resume() {
        assert(app);
        app->resume();
    }

    virtual ~ApplicationListenerDecorator() {
        delete app;
    }
    
protected:
    RealApplication* app;
};

}

#endif // GDX_CPP_UTILS_APPLICATIONLISTENERDECORATOR_HPP
