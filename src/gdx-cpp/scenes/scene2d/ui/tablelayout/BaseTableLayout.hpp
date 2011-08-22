
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_BASETABLELAYOUT<C, T EXTENDS C, L EXTENDS BASETABLELAYOUT, K EXTENDS TOOLKIT>_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_BASETABLELAYOUT<C, T EXTENDS C, L EXTENDS BASETABLELAYOUT, K EXTENDS TOOLKIT>_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace ui {
namespace tablelayout {

class BaseTableLayout {
public:
    void invalidate ();
    void invalidateHierarchy ();
    void setLayoutSize (int tableLayoutX,int tableLayoutY,int tableLayoutWidth,int tableLayoutHeight);
    C& register (const std::string& name,const C& widget);
    void parse (const std::string& tableDescription);
    Cell<C>& add (const C& widget);
    Cell& row ();
    Cell& columnDefaults (int column);
    void reset ();
    void clear ();
    C& getWidget (const std::string& name);
    std::list<C>& getWidgets ();
    std::list<C>& getWidgets (const std::string& namePrefix);
    Cell& getCell (const C& widget);
    Cell& getCell (const std::string& name);
    std::list<Cell>& getAllCells ();
    std::list<Cell>& getAllCells (const std::string& namePrefix);
    std::list<Cell>& getCells ();
    void setWidget (const std::string& name,const C& widget);
    void setParent (const BaseTableLayout& parent);
    void setToolkit (const K& toolkit);
    T& getTable ();
    void setTable (const T& table);
    int getLayoutX ();
    int getLayoutY ();
    int getLayoutWidth ();
    int getLayoutHeight ();
    int getMinWidth ();
    int getMinHeight ();
    int getPrefWidth ();
    int getPrefHeight ();
    Cell& defaults ();
    K& getToolkit ();
    L& size (const std::string& width,const std::string& height);
    L& width (const std::string& width);
    L& height (const std::string& height);
    L& size (int width,int height);
    L& width (int width);
    L& height (int height);
    L& pad (const std::string& pad);
    L& pad (const std::string& top,const std::string& left,const std::string& bottom,const std::string& right);
    L& padTop (const std::string& padTop);
    L& padLeft (const std::string& padLeft);
    L& padBottom (const std::string& padBottom);
    L& padRight (const std::string& padRight);
    L& pad (int pad);
    L& pad (int top,int left,int bottom,int right);
    L& padTop (int padTop);
    L& padLeft (int padLeft);
    L& padBottom (int padBottom);
    L& padRight (int padRight);
    L& align (int align);
    L& align (const std::string& value);
    L& center ();
    L& top ();
    L& left ();
    L& bottom ();
    L& right ();
    L& debug (int debug);
    L& debug (const std::string& value);
    int getDebug ();
    std::string& getWidth ();
    std::string& getHeight ();
    std::string& getPadTop ();
    std::string& getPadLeft ();
    std::string& getPadBottom ();
    std::string& getPadRight ();
    int getAlign ();
    void layout ();

protected:


private:
    void endRow ();
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace ui
} // namespace tablelayout

#endif // GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_BASETABLELAYOUT<C, T EXTENDS C, L EXTENDS BASETABLELAYOUT, K EXTENDS TOOLKIT>_HPP_
