
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_CELL<C>_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_CELL<C>_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace ui {
namespace tablelayout {

class Cell {
public:
    Cell& setWidget (const C& widget);
    std::string& getName ();
    C& getWidget ();
    Cell& minSize (const std::string& size);
    Cell& minWidth (const std::string& minWidth);
    Cell& minHeight (const std::string& minHeight);
    Cell& minSize (int size);
    Cell& minWidth (int minWidth);
    Cell& minHeight (int minHeight);
    Cell& prefSize (const std::string& size);
    Cell& prefWidth (const std::string& prefWidth);
    Cell& prefHeight (const std::string& prefHeight);
    Cell& prefSize (int size);
    Cell& prefWidth (int prefWidth);
    Cell& prefHeight (int prefHeight);
    Cell& maxSize (const std::string& size);
    Cell& maxWidth (const std::string& maxWidth);
    Cell& maxHeight (const std::string& maxHeight);
    Cell& maxSize (int size);
    Cell& maxWidth (int maxWidth);
    Cell& maxHeight (int maxHeight);
    Cell& space (const std::string& space);
    Cell& space (const std::string& top,const std::string& left,const std::string& bottom,const std::string& right);
    Cell& spaceTop (const std::string& spaceTop);
    Cell& spaceLeft (const std::string& spaceLeft);
    Cell& spaceBottom (const std::string& spaceBottom);
    Cell& spaceRight (const std::string& spaceRight);
    Cell& space (int space);
    Cell& space (int top,int left,int bottom,int right);
    Cell& spaceTop (int spaceTop);
    Cell& spaceLeft (int spaceLeft);
    Cell& spaceBottom (int spaceBottom);
    Cell& spaceRight (int spaceRight);
    Cell& pad (const std::string& pad);
    Cell& pad (const std::string& top,const std::string& left,const std::string& bottom,const std::string& right);
    Cell& padTop (const std::string& padTop);
    Cell& padLeft (const std::string& padLeft);
    Cell& padBottom (const std::string& padBottom);
    Cell& padRight (const std::string& padRight);
    Cell& pad (int pad);
    Cell& pad (int top,int left,int bottom,int right);
    Cell& padTop (int padTop);
    Cell& padLeft (int padLeft);
    Cell& padBottom (int padBottom);
    Cell& padRight (int padRight);
    Cell& fill ();
    Cell& fillX ();
    Cell& fillY ();
    Cell& fill (float x,float y);
    Cell& fill (bool x,bool y);
    Cell& align (int align);
    Cell& align (const std::string& value);
    Cell& center ();
    Cell& top ();
    Cell& left ();
    Cell& bottom ();
    Cell& right ();
    Cell& expand ();
    Cell& expandX ();
    Cell& expandY ();
    Cell& expand (int x,int y);
    Cell& expand (bool x,bool y);
    Cell& ignore (bool ignore);
    Cell& ignore ();
    bool getIgnore ();
    Cell& colspan (int colspan);
    Cell& uniform ();
    Cell& uniformX ();
    Cell& uniformY ();
    Cell& uniform (bool x,bool y);
    int getWidgetX ();
    int getWidgetY ();
    int getWidgetWidth ();
    int getWidgetHeight ();
    int getColumn ();
    int getRow ();
    std::string& getMinWidth ();
    std::string& getMinHeight ();
    std::string& getPrefWidth ();
    std::string& getPrefHeight ();
    std::string& getMaxWidth ();
    std::string& getMaxHeight ();
    std::string& getSpaceTop ();
    std::string& getSpaceLeft ();
    std::string& getSpaceBottom ();
    std::string& getSpaceRight ();
    std::string& getPadTop ();
    std::string& getPadLeft ();
    std::string& getPadBottom ();
    std::string& getPadRight ();
    float getFillX ();
    float getFillY ();
    int getAlign ();
    int getExpandX ();
    int getExpandY ();
    int getColspan ();
    bool getUniformX ();
    bool getUniformY ();
    bool isEndRow ();

protected:


private:
    BaseTableLayout layout;
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace ui
} // namespace tablelayout

#endif // GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_CELL<C>_HPP_
