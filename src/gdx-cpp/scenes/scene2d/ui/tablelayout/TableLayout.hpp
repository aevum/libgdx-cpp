
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_TABLELAYOUT_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_TABLELAYOUT_HPP_

namespace gdx {
namespace scenes {
namespace scene2d {
namespace ui {
namespace tablelayout {

class TableLayout {
public:
    gdx::Actor& register (const gdx::Actor& actor);
    gdx::Actor& registerImage (const std::string& name);
    gdx::Actor& getWidget (const std::string& name);
    void layout ();
    void invalidate ();
    void invalidateHierarchy ();
    void drawDebug (const gdx::SpriteBatch& batch);
    TableLayout ();
    TableLayout (const LibgdxToolkit& toolkit);
    TextureAtlas atlas ;

protected:
    OR SERVICES ;
    OR PROFITS ;
    boolean needsLayout = true;
    Array<DebugRect> debugRects ;

private:
    ImmediateModeRenderer debugRenderer ;
};

} // namespace gdx
} // namespace scenes
} // namespace scene2d
} // namespace ui
} // namespace tablelayout

#endif // GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_TABLELAYOUT_HPP_
