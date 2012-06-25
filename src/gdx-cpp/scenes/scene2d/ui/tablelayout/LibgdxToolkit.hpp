
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_LIBGDXTOOLKIT_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_LIBGDXTOOLKIT_HPP_

namespace gdx {
namespace scenes {
namespace scene2d {
namespace ui {
namespace tablelayout {

class LibgdxToolkit {
public:
    gdx::Actor& wrap (const Object& object);
    gdx::Actor& newWidget (const TableLayout& layout,const std::string& className);
    TableLayout& getLayout (const Table& table);
    gdx::Actor& newStack ();
    void setProperty (const TableLayout& layout,const gdx::Actor& object,const std::string& name,std::list<String>& values);
    void addChild (const gdx::Actor& parent,const gdx::Actor& child,const std::string& layoutString);
    void removeChild (const gdx::Actor& parent,const gdx::Actor& child);
    int getMinWidth (const gdx::Actor& actor);
    int getMinHeight (const gdx::Actor& actor);
    int getPrefWidth (const gdx::Actor& actor);
    int getPrefHeight (const gdx::Actor& actor);
    int getMaxWidth (const gdx::Actor& actor);
    int getMaxHeight (const gdx::Actor& actor);
    void clearDebugRectangles (const TableLayout& layout);
    void addDebugRectangle (const TableLayout& layout,int type,int x,int y,int w,int h);
    void registerFont (const std::string& name,const gdx::BitmapFont& font);
    gdx::BitmapFont& getFont (const std::string& name);
    LibgdxToolkit instance = new LibgdxToolkit();
    BitmapFont defaultFont ;

protected:
    OR SERVICES ;
    OR PROFITS ;

private:
    HashMap<String, BitmapFont> fonts = new HashMap();
};

} // namespace gdx
} // namespace scenes
} // namespace scene2d
} // namespace ui
} // namespace tablelayout

#endif // GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_LIBGDXTOOLKIT_HPP_
