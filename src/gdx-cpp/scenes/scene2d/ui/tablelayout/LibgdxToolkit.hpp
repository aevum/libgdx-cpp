
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

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace ui {
namespace tablelayout {

class LibgdxToolkit {
public:
    gdx_cpp::scenes::scene2d::Actor& wrap (const Object& object);
    gdx_cpp::scenes::scene2d::Actor& newWidget (const TableLayout& layout,const std::string& className);
    TableLayout& getLayout (const Table& table);
    gdx_cpp::scenes::scene2d::Actor& newStack ();
    void setProperty (const TableLayout& layout,const gdx_cpp::scenes::scene2d::Actor& object,const std::string& name,std::list<String>& values);
    void addChild (const gdx_cpp::scenes::scene2d::Actor& parent,const gdx_cpp::scenes::scene2d::Actor& child,const std::string& layoutString);
    void removeChild (const gdx_cpp::scenes::scene2d::Actor& parent,const gdx_cpp::scenes::scene2d::Actor& child);
    int getMinWidth (const gdx_cpp::scenes::scene2d::Actor& actor);
    int getMinHeight (const gdx_cpp::scenes::scene2d::Actor& actor);
    int getPrefWidth (const gdx_cpp::scenes::scene2d::Actor& actor);
    int getPrefHeight (const gdx_cpp::scenes::scene2d::Actor& actor);
    int getMaxWidth (const gdx_cpp::scenes::scene2d::Actor& actor);
    int getMaxHeight (const gdx_cpp::scenes::scene2d::Actor& actor);
    void clearDebugRectangles (const TableLayout& layout);
    void addDebugRectangle (const TableLayout& layout,int type,int x,int y,int w,int h);
    void registerFont (const std::string& name,const gdx_cpp::graphics::g2d::BitmapFont& font);
    gdx_cpp::graphics::g2d::BitmapFont& getFont (const std::string& name);
    LibgdxToolkit instance = new LibgdxToolkit();
    BitmapFont defaultFont ;

protected:
    OR SERVICES ;
    OR PROFITS ;

private:
    HashMap<String, BitmapFont> fonts = new HashMap();
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace ui
} // namespace tablelayout

#endif // GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_LIBGDXTOOLKIT_HPP_
