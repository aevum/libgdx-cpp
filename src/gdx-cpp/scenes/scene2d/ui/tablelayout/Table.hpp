
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_TABLE_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_TABLE_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace ui {
namespace tablelayout {

class Table {
public:
    void draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha);
    float getPrefWidth ();
    float getPrefHeight ();
    float getMinWidth ();
    float getMinHeight ();
    float getMaxWidth ();
    float getMaxHeight ();
    void setBackground (const gdx_cpp::graphics::g2d::NinePatch& background);
    void enableClipping (const gdx_cpp::scenes::scene2d::Stage& stage);
    void setClickListener (const gdx_cpp::scenes::scene2d::ui::ClickListener& listener);
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    void click ();
    gdx_cpp::scenes::scene2d::Actor& hit (float x,float y);
    TableLayout& getTableLayout ();
    void clear ();
    gdx_cpp::scenes::scene2d::Actor& register (const std::string& name,const gdx_cpp::scenes::scene2d::Actor& widget);
    Cell& add (const gdx_cpp::scenes::scene2d::Actor& actor);
    Cell& stack ();
    Cell& row ();
    void parse (const gdx_cpp::files::FileHandle& tableDescriptionFile);
    void parse (const std::string& tableDescription);
    Cell& columnDefaults (int column);
    Cell& defaults ();
    void layout ();
    void invalidate ();
    void invalidateHierarchy ();
    void reset ();
    gdx_cpp::scenes::scene2d::Actor& getWidget (const std::string& name);
    std::list<Actor>& getWidgets ();
    std::list<Actor>& getWidgets (const std::string& namePrefix);
    Cell& getCell (const gdx_cpp::scenes::scene2d::Actor& actor);
    Cell& getCell (const std::string& name);
    std::list<Cell>& getAllCells ();
    std::list<Cell>& getAllCells (const std::string& namePrefix);
    std::list<Cell>& getCells ();
    void setActor (const std::string& name,const gdx_cpp::scenes::scene2d::Actor& actor);
    Table& size (const std::string& width,const std::string& height);
    Table& width (const std::string& width);
    Table& height (const std::string& height);
    Table& size (int width,int height);
    Table& width (int width);
    Table& height (int height);
    Table& pad (const std::string& pad);
    Table& pad (const std::string& top,const std::string& left,const std::string& bottom,const std::string& right);
    Table& padTop (const std::string& padTop);
    Table& padLeft (const std::string& padLeft);
    Table& padBottom (const std::string& padBottom);
    Table& padRight (const std::string& padRight);
    Table& pad (int pad);
    Table& pad (int top,int left,int bottom,int right);
    Table& padTop (int padTop);
    Table& padLeft (int padLeft);
    Table& padBottom (int padBottom);
    Table& padRight (int padRight);
    Table& align (int align);
    Table& align (const std::string& value);
    Table& center ();
    Table& top ();
    Table& left ();
    Table& bottom ();
    Table& right ();
    Table& debug ();
    Table& debug (int debug);
    Table& debug (const std::string& value);
    int getDebug ();
    std::string& getHeight ();
    std::string& getPadTop ();
    std::string& getPadLeft ();
    std::string& getPadBottom ();
    std::string& getPadRight ();
    int getAlign ();
    void drawDebug (const gdx_cpp::scenes::scene2d::Stage& stage);
    Table ();
    Table (const TableLayout& layout);
    Table (const std::string& name);
    Table (const TableLayout& layout,const std::string& name);
    boolean isPressed ;

protected:
    OR SERVICES ;
    OR PROFITS ;
    boolean sizeInvalid = true;
    NinePatch backgroundPatch ;

private:
    void calculateScissors (const gdx_cpp::math::Matrix4& transform);
    void computeSize ();
    void drawDebug (std::list<Actor>& actors,const gdx_cpp::graphics::g2d::SpriteBatch& batch);
    TableLayout layout ;
    ClickListener listener ;
    Stage stage ;
    Rectangle tableBounds = new Rectangle();
    Rectangle scissors = new Rectangle();
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace ui
} // namespace tablelayout

#endif // GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_TABLE_HPP_
