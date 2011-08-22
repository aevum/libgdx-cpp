
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_TOOLKIT<C, T EXTENDS C, L EXTENDS BASETABLELAYOUT>_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_TOOLKIT<C, T EXTENDS C, L EXTENDS BASETABLELAYOUT>_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace ui {
namespace tablelayout {

class Toolkit {
public:
    void addChild (const C& parent,const C& child,const std::string& layoutString);
    void removeChild (const C& parent,const C& child);
    int getMinWidth (const C& widget);
    int getMinHeight (const C& widget);
    int getPrefWidth (const C& widget);
    int getPrefHeight (const C& widget);
    int getMaxWidth (const C& widget);
    int getMaxHeight (const C& widget);
    void clearDebugRectangles (const L& layout);
    void addDebugRectangle (const L& layout,int type,int x,int y,int w,int h);
    C& newStack ();
    L& getLayout (const T& table);
    T& newTable (const T& parent);
    void setWidget (const L& layout,const Cell& cell,const C& widget);
    C& newWidget (const L& layout,const std::string& className);
    C& wrap (const Object& object);
    void setProperty (const L& layout,const C& object,const std::string& name,std::list<String>& values);
    void setTableProperty (const L& layout,const std::string& name,std::list<String>& values);
    void setCellProperty (const Cell& c,const std::string& name,std::list<String>& values);
    int width (const L& layout,const std::string& value);
    int width (float value);
    int height (const L& layout,const std::string& value);
    int height (float value);
    void addClassPrefix (const std::string& prefix);

protected:
    std::string& validateSize (const std::string& size);
    C& newInstance (const std::string& className);
    Object& convertType (const Object& parentObject,const Class& memberType,const std::string& memberName,const std::string& value);

private:
    void invokeMethod (const Object& object,const std::string& name,std::list<String>& values);
    Field& getField (const Class& type,const std::string& name);
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace ui
} // namespace tablelayout

#endif // GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_TOOLKIT<C, T EXTENDS C, L EXTENDS BASETABLELAYOUT>_HPP_
