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
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 *  @author aevum team
 */

//dummy definitions so places that don't include all files wont complain
namespace gdx_cpp {
    namespace graphics {
        namespace g2d {
        }
        namespace glutils {
        }
    }
    namespace files {}
    namespace audio {}
    namespace math {}
    namespace utils {}
}

#define GDX_CPP_NAMESPACES \
using namespace gdx_cpp;\
using namespace gdx_cpp::graphics;\
using namespace gdx_cpp::graphics::g2d;\
using namespace gdx_cpp::graphics::glutils;\
using namespace gdx_cpp::audio;\
using namespace gdx_cpp::math;\
using namespace gdx_cpp::utils;\
using namespace gdx_cpp::files
