
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_SKIN_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_SKIN_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace ui {

class Skin: public gdx_cpp::utils::Disposable {
public:
    void parseSkin (const gdx_cpp::files::FileHandle& skinFile);
    gdx_cpp::graphics::Color& getColor (const std::string& name);
    void addColor (const std::string& name,const gdx_cpp::graphics::Color& color);
    gdx_cpp::graphics::g2d::NinePatch& getNinePatch (const std::string& name);
    void addNinePatch (const std::string& name,const gdx_cpp::graphics::g2d::NinePatch& ninePatch);
    gdx_cpp::graphics::g2d::TextureRegion& getRegion (const std::string& name);
    void addRegion (const std::string& name,const gdx_cpp::graphics::g2d::TextureRegion& region);
    gdx_cpp::graphics::g2d::BitmapFont& getFont (const std::string& name);
    void addFont (const std::string& name,const gdx_cpp::graphics::g2d::BitmapFont& font);
    gdx_cpp::scenes::scene2d::ui::Button::ButtonStyle& getButtonStyle (const std::string& name);
    void addButtonStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::Button::ButtonStyle& style);
    gdx_cpp::scenes::scene2d::ui::ImageButton::ImageButtonStyle& getImageButtonStyle (const std::string& name);
    void addImageButtonStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::ImageButton::ImageButtonStyle& style);
    gdx_cpp::scenes::scene2d::ui::ImageToggleButton::ImageToggleButtonStyle& getImageToggleButtonStyle (const std::string& name);
    void addImageToggleButtonStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::ImageToggleButton::ImageToggleButtonStyle& style);
    gdx_cpp::scenes::scene2d::ui::CheckBox::CheckBoxStyle& getCheckBoxStyle (const std::string& name);
    void addCheckBoxStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::CheckBox::CheckBoxStyle& style);
    gdx_cpp::scenes::scene2d::ui::ComboBox::ComboBoxStyle& getComboBoxStyle (const std::string& name);
    void addComboBoxStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::ComboBox::ComboBoxStyle& style);
    gdx_cpp::scenes::scene2d::ui::Label::LabelStyle& getLabelStyle (const std::string& name);
    void addLabelStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::Label::LabelStyle& style);
    gdx_cpp::scenes::scene2d::ui::List::ListStyle& getListStyle (const std::string& name);
    void addListStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::List::ListStyle& style);
    gdx_cpp::scenes::scene2d::ui::Pane::PaneStyle& getPaneStyle (const std::string& name);
    void addPaneStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::Pane::PaneStyle& style);
    gdx_cpp::scenes::scene2d::ui::ScrollPane::ScrollPaneStyle& getScrollPaneStyle (const std::string& name);
    void addScrollPaneStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::ScrollPane::ScrollPaneStyle& style);
    gdx_cpp::scenes::scene2d::ui::Slider::SliderStyle& getSliderStyle (const std::string& name);
    void addSliderStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::Slider::SliderStyle& style);
    gdx_cpp::scenes::scene2d::ui::SplitPane::SplitPaneStyle& getSplitPaneStyle (const std::string& name);
    void addSplitPaneStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::SplitPane::SplitPaneStyle& style);
    gdx_cpp::scenes::scene2d::ui::TextField::TextFieldStyle& getTextFieldStyle (const std::string& name);
    void addTextFieldStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::TextField::TextFieldStyle& style);
    gdx_cpp::scenes::scene2d::ui::ToggleButton::ToggleButtonStyle& getToggleButtonStyle (const std::string& name);
    void addToggleButtonStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::ToggleButton::ToggleButtonStyle& style);
    gdx_cpp::scenes::scene2d::ui::Window::WindowStyle& getWindowStyle (const std::string& name);
    void addWindowStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::Window::WindowStyle& style);
    ImageButton& newImageButton (const std::string& name,const gdx_cpp::graphics::g2d::TextureRegion& image);
    ImageButton& newImageButton (const std::string& name,const gdx_cpp::graphics::g2d::TextureRegion& image,const std::string& style);
    ImageToggleButton& newImageToggleButton (const std::string& name,const gdx_cpp::graphics::g2d::TextureRegion& image);
    ImageToggleButton& newImageToggleButton (const std::string& name,const gdx_cpp::graphics::g2d::TextureRegion& image,const std::string& style);
    Button& newButton (const std::string& name,const std::string& label);
    Button& newButton (const std::string& name,const std::string& label,const std::string& style);
    ToggleButton& newToggleButton (const std::string& name,const std::string& label);
    ToggleButton& newToggleButton (const std::string& name,const std::string& label,const std::string& style);
    CheckBox& newCheckBox (const std::string& name,const std::string& label);
    CheckBox& newCheckBox (const std::string& name,const std::string& label,const std::string& style);
    Label& newLabel (const std::string& name,const std::string& label);
    Label& newLabel (const std::string& name,const std::string& label,const std::string& style);
    Slider& newSlider (const std::string& name,float prefWidth,float min,float max,float step);
    Slider& newSlider (const std::string& name,float prefWidth,float min,float max,float step,const std::string& style);
    std::list<& newList (const std::string& name);
    std::list<& newList (const std::string& name,const std::string& style);
    Pane& newPane (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,int prefWidth,int prefHeight);
    Pane& newPane (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,int prefWidth,int prefHeight,const std::string& style);
    ScrollPane& newScrollPane (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,const gdx_cpp::scenes::scene2d::Actor& widget,int prefWidth,int prefHeight);
    ScrollPane& newScrollPane (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,const gdx_cpp::scenes::scene2d::Actor& widget,int prefWidth,int prefHeight,const std::string& style);
    SplitPane& newSplitPane (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,const gdx_cpp::scenes::scene2d::Actor& firstWidget,const gdx_cpp::scenes::scene2d::Actor& secondWidget,bool vertical,int prefWidth,int prefHeight,const std::string& style);
    TextField& newTextField (const std::string& name,float prefWidth);
    TextField& newTextField (const std::string& name,float prefWidth,const std::string& style);
    ComboBox& newComboBox (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage);
    ComboBox& newComboBox (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,const std::string& style);
    Window& newWindow (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,const std::string& title,int width,int height);
    Window& newWindow (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,const std::string& title,int width,int height,const std::string& style);
    void dispose ();
    gdx_cpp::graphics::Texture& getTexture ();

protected:
    void parseWidgetStyles (const gdx_cpp::utils::XmlReader::Element& styles);

private:
    void error (const std::string& msg,const gdx_cpp::utils::XmlReader::Element& element);
    void parseWindowStyles (const gdx_cpp::utils::XmlReader::Element& styles);
    void parseComboBoxStyles (const gdx_cpp::utils::XmlReader::Element& styles);
    void parseTextFieldStyles (const gdx_cpp::utils::XmlReader::Element& styles);
    void parseSplitPaneStyles (const gdx_cpp::utils::XmlReader::Element& styles);
    void parseScrollPaneStyles (const gdx_cpp::utils::XmlReader::Element& styles);
    void parsePaneStyles (const gdx_cpp::utils::XmlReader::Element& styles);
    void parseListStyles (const gdx_cpp::utils::XmlReader::Element& styles);
    void parseImageToggleButtonStyles (const gdx_cpp::utils::XmlReader::Element& styles);
    void parseToggleButtonStyles (const gdx_cpp::utils::XmlReader::Element& styles);
    void parseSliderStyles (const gdx_cpp::utils::XmlReader::Element& styles);
    void parseCheckBoxStyles (const gdx_cpp::utils::XmlReader::Element& styles);
    void parseImageButtonStyles (const gdx_cpp::utils::XmlReader::Element& styles);
    void parseButtonStyles (const gdx_cpp::utils::XmlReader::Element& styles);
    void parseLabelStyles (const gdx_cpp::utils::XmlReader::Element& styles);
    void parseLibrary (const gdx_cpp::utils::XmlReader::Element& skin);
    void parseColors (const gdx_cpp::utils::XmlReader::Element& library);
    void parseFonts (const gdx_cpp::utils::XmlReader::Element& library);
    void parseRegions (const gdx_cpp::utils::XmlReader::Element& library);
    void parseNinePatches (const gdx_cpp::utils::XmlReader::Element& library);
    gdx_cpp::graphics::g2d::NinePatch& parseNinePatch (const gdx_cpp::utils::XmlReader::Element& ninePatch);
    gdx_cpp::graphics::g2d::TextureRegion& parseRegion (const gdx_cpp::utils::XmlReader::Element& region);
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace ui

#endif // GDX_CPP_SCENES_SCENE2D_UI_SKIN_HPP_
