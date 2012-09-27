
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

#ifndef GDX_CPP_GRAPHICS_FPSLOGGER_HPP_
#define GDX_CPP_GRAPHICS_FPSLOGGER_HPP_

#include <stdint.h>
#include <gdx-cpp/Gdx.hpp>

namespace gdx {

class FPSLogger {
public:
    void log () {
        if ( gdx::system->nanoTime() - startTime > 1000000000 ) {
            gdx_log_info ( "FPSLogger", "fps: %u", gdx::graphics->getFramesPerSecond() );
            startTime = gdx::system->nanoTime();
        }
    }

    FPSLogger() : startTime(gdx::system->nanoTime()) { }

protected:
    uint64_t startTime;

private:

};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_FPSLOGGER_HPP_
