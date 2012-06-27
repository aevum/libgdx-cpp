
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_LIST_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_LIST_HPP_

namespace gdx {
namespace scenes {
namespace scene2d {
namespace ui {

class List {
public:
    void setStyle (const ListStyle& style);
    void layout ();
    void draw (const gdx::SpriteBatch& batch,float parentAlpha);
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    void touchDragged (float x,float y,int pointer);
    gdx::Actor& hit (float x,float y);
    void selected (const std::list<& list,int selectedIndex,const std::string& selection);
    int getSelectedIndex ();
    void setSelectedIndex (int index);
    std::string& getSelection ();
    void setSelection (int index);
    int setSelection (const std::string& item);
    void setItems ();
    std::string* getItems ();
    float getPrefWidth ();
    float getPrefHeight ();
    void setSelectionListener (const SelectionListener& listener);
    List (const Skin& skin);
    List (const ListStyle& style);
    List (const ListStyle& style,const std::string& name);

protected:
    ListStyle style ;
    String[] items ;
    float itemHeight = 0;
    float textOffsetX = 0;
    float textOffsetY = 0;
    int selected = 0;
    SelectionListener listener ;

private:

};

} // namespace gdx
} // namespace scenes
} // namespace scene2d
} // namespace ui

#endif // GDX_CPP_SCENES_SCENE2D_UI_LIST_HPP_
