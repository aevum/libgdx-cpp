/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License") = 0;
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

#ifndef GDX_CPP_GRAPHICS_G2D_SVG_SVGPIXMAPINTERFACE_H
#define GDX_CPP_GRAPHICS_G2D_SVG_SVGPIXMAPINTERFACE_H

#include "gdx-cpp/graphics/Color.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"
#include <vector>
#include "gdx-cpp/utils/SvgRendererHandler.hpp"

namespace gdx {

/** Pixmap + SvgRendererHandler glue code :)
 */
class SvgPixmapInterface : public Pixmap, public virtual SvgRendererHandler
{
public:
    virtual void fill(Color color) = 0;    
    virtual void setStrokeWidth(int) = 0;
};

}

#endif // GDX_CPP_GRAPHICS_G2D_SVG_SVGPIXMAPINTERFACE_H
