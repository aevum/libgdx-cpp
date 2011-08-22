
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

#include "Skin.hpp"

using namespace gdx_cpp::scenes::scene2d::ui;

void Skin::parseSkin (const gdx_cpp::files::FileHandle& skinFile) {
    try {
        XmlReader xml = new XmlReader();
        Element skin = xml.parse(skinFile);
        parseLibrary(skin);
        parseWidgetStyles(skin.getChildByName("widgetStyles"));
    } catch (Exception e) {
        throw new GdxRuntimeException("Couldn't parse skinFile", e);
    }
}

void Skin::parseWidgetStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
    parseButtonStyles(styles);
    parseCheckBoxStyles(styles);
    parseLabelStyles(styles);
    parseSliderStyles(styles);
    parseToggleButtonStyles(styles);
    parseListStyles(styles);
    parsePaneStyles(styles);
    parseScrollPaneStyles(styles);
    parseSplitPaneStyles(styles);
    parseTextFieldStyles(styles);
    parseComboBoxStyles(styles);
    parseWindowStyles(styles);
    parseImageButtonStyles(styles);
    parseImageToggleButtonStyles(styles);
}

void Skin::error (const std::string& msg,const gdx_cpp::utils::XmlReader::Element& element) {
    throw new GdxRuntimeException(msg + ", element: " + element.toString());
}

void Skin::parseWindowStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
for (Element style : styles.getChildrenByName("window")) {
        String name = style.getAttribute("name");
        NinePatch background = getNinePatch(style.getAttribute("background"));
        BitmapFont font = getFont(style.getAttribute("titleFont"));
        Color fontColor = getColor(style.getAttribute("titleFontColor"));

        if (name == null) error("No name given for window style", style);
        if (background == null) error("No 'background' nine-patch given for window style", style);
        if (font == null) error("No 'font' given for window style", style);
        if (fontColor == null) error("No 'fontColor' given for window style", style);

        windowStyles.put(name, new WindowStyle(font, fontColor, background));
    }
}

void Skin::parseComboBoxStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
for (Element style : styles.getChildrenByName("combobox")) {
        String name = style.getAttribute("name");
        NinePatch background = getNinePatch(style.getAttribute("background"));
        NinePatch listBackground = getNinePatch(style.getAttribute("listBackground"));
        NinePatch listSelection = getNinePatch(style.getAttribute("listSelection"));
        BitmapFont font = getFont(style.getAttribute("font"));
        Color fontColor = getColor(style.getAttribute("fontColor"));

        if (name == null) error("No name given for combobox style", style);
        if (background == null) error("No 'background' nine-patch given for combobox style", style);
        if (listBackground == null) error("No 'listBackground' nine-patch given for combobox style", style);
        if (listSelection == null) error("No 'listSelection' nine-patch given for combobox style", style);
        if (font == null) error("No 'font' given for combobox style", style);
        if (fontColor == null) error("No 'fontColor' given for combobox style", style);

        comboBoxStyles.put(name, new ComboBoxStyle(font, fontColor, background, listBackground, listSelection));
    }
}

void Skin::parseTextFieldStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
for (Element style : styles.getChildrenByName("textfield")) {
        String name = style.getAttribute("name");
        NinePatch background = getNinePatch(style.getAttribute("background"));
        NinePatch cursor = getNinePatch(style.getAttribute("cursor"));
        BitmapFont font = getFont(style.getAttribute("font"));
        Color fontColor = getColor(style.getAttribute("fontColor"));
        TextureRegion selection = getRegion(style.getAttribute("selection"));

        if (name == null) error("No name given for textfield style", style);
        if (background == null) error("No 'background' nine-patch given for textfield style", style);
        if (cursor == null) error("No 'cursor' nine-patch given for textfield style", style);
        if (font == null) error("No 'font' given for textfield style", style);
        if (fontColor == null) error("No 'fontColor' given for textfield stye", style);
        if (selection == null) error("No 'selection' region given for textfield style", style);

        textFieldStyles.put(name, new TextFieldStyle(font, fontColor, cursor, selection, background));
    }
}

void Skin::parseSplitPaneStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
for (Element style : styles.getChildrenByName("splitpane")) {
        String name = style.getAttribute("name");
        NinePatch handle = getNinePatch(style.getAttribute("handle"));

        if (name == null) error("No name given for splitpane style", style);
        if (handle == null) error("No 'handle' given for splitpane style", style);

        splitPaneStyles.put(name, new SplitPaneStyle(handle));
    }
}

void Skin::parseScrollPaneStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
for (Element style : styles.getChildrenByName("scrollpane")) {
        String name = style.getAttribute("name");
        NinePatch background = getNinePatch(style.getAttribute("background"));
        NinePatch hScroll = getNinePatch(style.getAttribute("hScroll"));
        NinePatch hScrollKnob = getNinePatch(style.getAttribute("hScrollKnob"));
        NinePatch vScroll = getNinePatch(style.getAttribute("vScroll"));
        NinePatch vScrollKnob = getNinePatch(style.getAttribute("vScrollKnob"));

        if (name == null) error("No name given for scrollpane style", style);
        if (background == null) error("No 'background' given for scrollpane style", style);
        if (hScroll == null) error("No 'hScroll' given for scrollpane style", style);
        if (hScrollKnob == null) error("No 'hScrollKnob' given for scrollpane style", style);
        if (vScroll == null) error("No 'vScroll' given for scrollpane style", style);
        if (vScrollKnob == null) error("No 'vScrollKnob' given for scrollpane style", style);

        scrollPaneStyles.put(name, new ScrollPaneStyle(background, hScroll, hScrollKnob, vScroll, vScrollKnob));
    }
}

void Skin::parsePaneStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
for (Element style : styles.getChildrenByName("pane")) {
        String name = style.getAttribute("name");
        NinePatch patch = getNinePatch(style.getAttribute("background"));

        if (name == null) error("No name given for pane style", style);
        if (patch == null) error("No 'background' given for pane style", style);

        paneStyles.put(name, new PaneStyle(patch));
    }
}

void Skin::parseListStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
for (Element style : styles.getChildrenByName("list")) {
        String name = style.getAttribute("name");
        BitmapFont font = getFont(style.getAttribute("font"));
        Color fontColorUnselected = getColor(style.getAttribute("fontColorUnselected"));
        Color fontColorSelected = getColor(style.getAttribute("fontColorSelected"));
        NinePatch selectedPatch = getNinePatch(style.getAttribute("selected"));

        if (name == null) error("No name given for list style", style);
        if (font == null) error("No font given for list style", style);
        if (fontColorUnselected == null) error("No 'fontColorUnselected' given for list style", style);
        if (fontColorSelected == null) error("No 'fontColorSelected' given for list style", style);
        if (selectedPatch == null) error("No 'selected' nine-patch given for list style", style);

        listStyles.put(name, new ListStyle(font, fontColorSelected, fontColorUnselected, selectedPatch));
    }
}

void Skin::parseImageToggleButtonStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
for (Element style : styles.getChildrenByName("imagetogglebutton")) {
        String name = style.getAttribute("name");
        NinePatch down = getNinePatch(style.getAttribute("down"));
        NinePatch up = getNinePatch(style.getAttribute("up"));

        if (name == null) error("No name given for togglebutton style", style);
        if (down == null) error("No 'down' nine-patch given for togglebutton style", style);
        if (up == null) error("No 'up' nine-patch given for togglebutton style", style);

        imageToggleButtonStyles.put(name, new ImageToggleButtonStyle(down, up));
    }
}

void Skin::parseToggleButtonStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
for (Element style : styles.getChildrenByName("togglebutton")) {
        String name = style.getAttribute("name");
        NinePatch down = getNinePatch(style.getAttribute("down"));
        NinePatch up = getNinePatch(style.getAttribute("up"));
        BitmapFont font = getFont(style.getAttribute("font"));
        Color fontColor = getColor(style.getAttribute("fontColor"));

        if (name == null) error("No name given for togglebutton style", style);
        if (down == null) error("No 'down' nine-patch given for togglebutton style", style);
        if (up == null) error("No 'up' nine-patch given for togglebutton style", style);
        if (font == null) error("No 'font' given for togglebutton style", style);
        if (fontColor == null) error("No 'fontColor' given for togglebutton style", style);

        toggleButtonStyles.put(name, new ToggleButtonStyle(font, fontColor, down, up));
    }
}

void Skin::parseSliderStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
for (Element style : styles.getChildrenByName("slider")) {
        String name = style.getAttribute("name");
        NinePatch sliderPatch = getNinePatch(style.getAttribute("slider"));
        TextureRegion knobPatch = getRegion(style.getAttribute("knob"));

        if (name == null) error("No name given for slider style", style);
        if (sliderPatch == null) error("No 'slider' nine-patch given for slider style", style);
        if (knobPatch == null) error("No 'knob' region given for slider style", style);
        sliderStyles.put(name, new SliderStyle(sliderPatch, knobPatch));
    }
}

void Skin::parseCheckBoxStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
for (Element style : styles.getChildrenByName("checkbox")) {
        String name = style.getAttribute("name");
        BitmapFont font = getFont(style.getAttribute("font"));
        Color fontColor = getColor(style.getAttribute("fontColor"));
        TextureRegion checked = getRegion(style.getAttribute("checked"));
        TextureRegion unchecked = getRegion(style.getAttribute("unchecked"));

        if (name == null) error("No name given for checkbox style", style);
        if (font == null) error("No 'font' given for checkbox style", style);
        if (fontColor == null) error("No 'fontColor' given for checkbox style", style);
        if (checked == null) error("No 'checked' region given for checkbox style", style);
        if (unchecked == null) error("No 'unchecked' region given for checkbox style", style);

        checkBoxStyles.put(name, new CheckBoxStyle(font, fontColor, checked, unchecked));
    }
}

void Skin::parseImageButtonStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
for (Element style : styles.getChildrenByName("imagebutton")) {
        String name = style.getAttribute("name");
        NinePatch down = getNinePatch(style.getAttribute("down"));
        NinePatch up = getNinePatch(style.getAttribute("up"));

        if (name == null) error("No name given for button style", style);
        if (down == null) error("No 'down' nine-patch given for button style", style);
        if (up == null) error("No 'up' nine-patch given for button style", style);

        imageButtonStyles.put(name, new ImageButtonStyle(down, up));
    }
}

void Skin::parseButtonStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
for (Element style : styles.getChildrenByName("button")) {
        String name = style.getAttribute("name");
        NinePatch down = getNinePatch(style.getAttribute("down"));
        NinePatch up = getNinePatch(style.getAttribute("up"));
        BitmapFont font = getFont(style.getAttribute("font"));
        Color fontColor = getColor(style.getAttribute("fontColor"));

        if (name == null) error("No name given for button style", style);
        if (down == null) error("No 'down' nine-patch given for button style", style);
        if (up == null) error("No 'up' nine-patch given for button style", style);
        if (font == null) error("No 'font' nine-patch given for button style", style);
        if (fontColor == null) error("No 'fontColor' given for button style", style);

        buttonStyles.put(name, new ButtonStyle(font, fontColor, down, up));
    }
}

void Skin::parseLabelStyles (const gdx_cpp::utils::XmlReader::Element& styles) {
for (Element style : styles.getChildrenByName("label")) {
        String name = style.getAttribute("name");
        BitmapFont font = getFont(style.getAttribute("font"));
        Color fontColor = getColor(style.getAttribute("fontColor"));

        if (name == null) error("No name given for label style", style);
        if (font == null) error("No 'font' given for label style", style);
        if (fontColor == null) error("No 'fontColor' given for label style", style);

        labelStyles.put(style.getAttribute("name"), new LabelStyle(font, fontColor));
    }
}

void Skin::parseLibrary (const gdx_cpp::utils::XmlReader::Element& skin) {
    Element library = skin.getChildByName("library");
    parseColors(library);
    parseNinePatches(library);
    parseRegions(library);
    parseFonts(library);
}

void Skin::parseColors (const gdx_cpp::utils::XmlReader::Element& library) {
for (Element color : library.getChildrenByName("color")) {
        Color col = new Color(color.getFloatAttribute("r"), color.getFloatAttribute("g"), color.getFloatAttribute("b"),
                              color.getFloatAttribute("a"));
        colors.put(color.getAttribute("name"), col);
    }
}

void Skin::parseFonts (const gdx_cpp::utils::XmlReader::Element& library) {
for (Element font : library.getChildrenByName("font")) {
        BitmapFont bitmapFont = new BitmapFont(Gdx.files.internal(font.getAttribute("file")), false);
        fonts.put(font.getAttribute("name"), bitmapFont);
    }
}

void Skin::parseRegions (const gdx_cpp::utils::XmlReader::Element& library) {
for (Element region : library.getChildrenByName("region")) {
        regions.put(region.getAttribute("name"), parseRegion(region));
    }
}

void Skin::parseNinePatches (const gdx_cpp::utils::XmlReader::Element& library) {
for (Element ninePatch : library.getChildrenByName("ninepatch")) {
        ninePatches.put(ninePatch.getAttribute("name"), parseNinePatch(ninePatch));
    }
}

gdx_cpp::graphics::g2d::NinePatch& Skin::parseNinePatch (const gdx_cpp::utils::XmlReader::Element& ninePatch) {
    TextureRegion[] regions = new TextureRegion[9];
    Array<Element> patches = ninePatch.getChildrenByName("region");
    if (regions.length != 9) error("Nine-patch definition has to have 9 regions", ninePatch);
    for (int i = 0; i < regions.length; i++) {
        regions[i] = parseRegion(patches.get(i));
    }
    return new NinePatch(regions);
}

gdx_cpp::graphics::g2d::TextureRegion& Skin::parseRegion (const gdx_cpp::utils::XmlReader::Element& region) {
    return new TextureRegion(texture, region.getIntAttribute("x"), region.getIntAttribute("y"),
                             region.getIntAttribute("width"), region.getIntAttribute("height"));
}

gdx_cpp::graphics::Color& Skin::getColor (const std::string& name) {
    return colors.get(name);
}

void Skin::addColor (const std::string& name,const gdx_cpp::graphics::Color& color) {
    colors.put(name, color);
}

gdx_cpp::graphics::g2d::NinePatch& Skin::getNinePatch (const std::string& name) {
    return ninePatches.get(name);
}

void Skin::addNinePatch (const std::string& name,const gdx_cpp::graphics::g2d::NinePatch& ninePatch) {
    ninePatches.put(name, ninePatch);
}

gdx_cpp::graphics::g2d::TextureRegion& Skin::getRegion (const std::string& name) {
    return regions.get(name);
}

void Skin::addRegion (const std::string& name,const gdx_cpp::graphics::g2d::TextureRegion& region) {
    regions.put(name, region);
}

gdx_cpp::graphics::g2d::BitmapFont& Skin::getFont (const std::string& name) {
    return fonts.get(name);
}

void Skin::addFont (const std::string& name,const gdx_cpp::graphics::g2d::BitmapFont& font) {
    fonts.put(name, font);
}

gdx_cpp::scenes::scene2d::ui::Button::ButtonStyle& Skin::getButtonStyle (const std::string& name) {
    return buttonStyles.get(name);
}

void Skin::addButtonStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::Button::ButtonStyle& style) {
    buttonStyles.put(name, style);
}

gdx_cpp::scenes::scene2d::ui::ImageButton::ImageButtonStyle& Skin::getImageButtonStyle (const std::string& name) {
    return imageButtonStyles.get(name);
}

void Skin::addImageButtonStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::ImageButton::ImageButtonStyle& style) {
    imageButtonStyles.put(name, style);
}

gdx_cpp::scenes::scene2d::ui::ImageToggleButton::ImageToggleButtonStyle& Skin::getImageToggleButtonStyle (const std::string& name) {
    return imageToggleButtonStyles.get(name);
}

void Skin::addImageToggleButtonStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::ImageToggleButton::ImageToggleButtonStyle& style) {
    imageToggleButtonStyles.put(name, style);
}

gdx_cpp::scenes::scene2d::ui::CheckBox::CheckBoxStyle& Skin::getCheckBoxStyle (const std::string& name) {
    return checkBoxStyles.get(name);
}

void Skin::addCheckBoxStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::CheckBox::CheckBoxStyle& style) {
    checkBoxStyles.put(name, style);
}

gdx_cpp::scenes::scene2d::ui::ComboBox::ComboBoxStyle& Skin::getComboBoxStyle (const std::string& name) {
    return comboBoxStyles.get(name);
}

void Skin::addComboBoxStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::ComboBox::ComboBoxStyle& style) {
    comboBoxStyles.put(name, style);
}

gdx_cpp::scenes::scene2d::ui::Label::LabelStyle& Skin::getLabelStyle (const std::string& name) {
    return labelStyles.get(name);
}

void Skin::addLabelStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::Label::LabelStyle& style) {
    labelStyles.put(name, style);
}

gdx_cpp::scenes::scene2d::ui::List::ListStyle& Skin::getListStyle (const std::string& name) {
    return listStyles.get(name);
}

void Skin::addListStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::List::ListStyle& style) {
    listStyles.put(name, style);
}

gdx_cpp::scenes::scene2d::ui::Pane::PaneStyle& Skin::getPaneStyle (const std::string& name) {
    return paneStyles.get(name);
}

void Skin::addPaneStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::Pane::PaneStyle& style) {
    paneStyles.put(name, style);
}

gdx_cpp::scenes::scene2d::ui::ScrollPane::ScrollPaneStyle& Skin::getScrollPaneStyle (const std::string& name) {
    return scrollPaneStyles.get(name);
}

void Skin::addScrollPaneStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::ScrollPane::ScrollPaneStyle& style) {
    scrollPaneStyles.put(name, style);
}

gdx_cpp::scenes::scene2d::ui::Slider::SliderStyle& Skin::getSliderStyle (const std::string& name) {
    return sliderStyles.get(name);
}

void Skin::addSliderStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::Slider::SliderStyle& style) {
    sliderStyles.put(name, style);
}

gdx_cpp::scenes::scene2d::ui::SplitPane::SplitPaneStyle& Skin::getSplitPaneStyle (const std::string& name) {
    return splitPaneStyles.get(name);
}

void Skin::addSplitPaneStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::SplitPane::SplitPaneStyle& style) {
    splitPaneStyles.put(name, style);
}

gdx_cpp::scenes::scene2d::ui::TextField::TextFieldStyle& Skin::getTextFieldStyle (const std::string& name) {
    return textFieldStyles.get(name);
}

void Skin::addTextFieldStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::TextField::TextFieldStyle& style) {
    textFieldStyles.put(name, style);
}

gdx_cpp::scenes::scene2d::ui::ToggleButton::ToggleButtonStyle& Skin::getToggleButtonStyle (const std::string& name) {
    return toggleButtonStyles.get(name);
}

void Skin::addToggleButtonStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::ToggleButton::ToggleButtonStyle& style) {
    toggleButtonStyles.put(name, style);
}

gdx_cpp::scenes::scene2d::ui::Window::WindowStyle& Skin::getWindowStyle (const std::string& name) {
    return windowStyles.get(name);
}

void Skin::addWindowStyle (const std::string& name,const gdx_cpp::scenes::scene2d::ui::Window::WindowStyle& style) {
    windowStyles.put(name, style);
}

ImageButton& Skin::newImageButton (const std::string& name,const gdx_cpp::graphics::g2d::TextureRegion& image) {
    return newImageButton(name, image, "default");
}

ImageButton& Skin::newImageButton (const std::string& name,const gdx_cpp::graphics::g2d::TextureRegion& image,const std::string& style) {
    return new ImageButton(name, image, imageButtonStyles.get(style));
}

ImageToggleButton& Skin::newImageToggleButton (const std::string& name,const gdx_cpp::graphics::g2d::TextureRegion& image) {
    return newImageToggleButton(name, image, "default");
}

ImageToggleButton& Skin::newImageToggleButton (const std::string& name,const gdx_cpp::graphics::g2d::TextureRegion& image,const std::string& style) {
    return new ImageToggleButton(name, image, imageToggleButtonStyles.get(style));
}

Button& Skin::newButton (const std::string& name,const std::string& label) {
    return newButton(name, label, "default");
}

Button& Skin::newButton (const std::string& name,const std::string& label,const std::string& style) {
    return new Button(name, label, buttonStyles.get(style));
}

ToggleButton& Skin::newToggleButton (const std::string& name,const std::string& label) {
    return newToggleButton(name, label, "default");
}

ToggleButton& Skin::newToggleButton (const std::string& name,const std::string& label,const std::string& style) {
    return new ToggleButton(name, label, toggleButtonStyles.get(style));
}

CheckBox& Skin::newCheckBox (const std::string& name,const std::string& label) {
    return new CheckBox(name, label, checkBoxStyles.get("default"));
}

CheckBox& Skin::newCheckBox (const std::string& name,const std::string& label,const std::string& style) {
    return new CheckBox(name, label, checkBoxStyles.get(style));
}

Label& Skin::newLabel (const std::string& name,const std::string& label) {
    return new Label(name, label, labelStyles.get("default"));
}

Label& Skin::newLabel (const std::string& name,const std::string& label,const std::string& style) {
    return new Label(name, label, labelStyles.get(style));
}

Slider& Skin::newSlider (const std::string& name,float prefWidth,float min,float max,float step) {
    return newSlider(name, prefWidth, min, max, step, "default");
}

Slider& Skin::newSlider (const std::string& name,float prefWidth,float min,float max,float step,const std::string& style) {
    return new Slider(name, prefWidth, min, max, step, sliderStyles.get(style));
}

std::list<& Skin::newList (const std::string& name) {
    return newList(name, entries, "default");
}

std::list<& Skin::newList (const std::string& name,const std::string& style) {
    return new List(name, entries, listStyles.get(style));
}

Pane& Skin::newPane (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,int prefWidth,int prefHeight) {
    return newPane(name, stage, prefWidth, prefHeight, "default");
}

Pane& Skin::newPane (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,int prefWidth,int prefHeight,const std::string& style) {
    return new Pane(name, stage, prefWidth, prefHeight, paneStyles.get(style));
}

ScrollPane& Skin::newScrollPane (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,const gdx_cpp::scenes::scene2d::Actor& widget,int prefWidth,int prefHeight) {
    return newScrollPane(name, stage, widget, prefWidth, prefHeight, "default");
}

ScrollPane& Skin::newScrollPane (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,const gdx_cpp::scenes::scene2d::Actor& widget,int prefWidth,int prefHeight,const std::string& style) {
    return new ScrollPane(name, stage, widget, prefWidth, prefHeight, scrollPaneStyles.get(style));
}

SplitPane& Skin::newSplitPane (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,const gdx_cpp::scenes::scene2d::Actor& firstWidget,const gdx_cpp::scenes::scene2d::Actor& secondWidget,bool vertical,int prefWidth,int prefHeight,const std::string& style) {
    return new SplitPane(name, stage, firstWidget, secondWidget, vertical, prefWidth, prefHeight, splitPaneStyles.get(style));
}

TextField& Skin::newTextField (const std::string& name,float prefWidth) {
    return newTextField(name, prefWidth, "default");
}

TextField& Skin::newTextField (const std::string& name,float prefWidth,const std::string& style) {
    return new TextField(name, prefWidth, textFieldStyles.get(style));
}

ComboBox& Skin::newComboBox (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage) {
    return newComboBox(name, entries, stage, "default");
}

ComboBox& Skin::newComboBox (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,const std::string& style) {
    return new ComboBox(name, entries, stage, comboBoxStyles.get(style));
}

Window& Skin::newWindow (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,const std::string& title,int width,int height) {
    return newWindow(name, stage, title, width, height, "default");
}

Window& Skin::newWindow (const std::string& name,const gdx_cpp::scenes::scene2d::Stage& stage,const std::string& title,int width,int height,const std::string& style) {
    return new Window(name, stage, title, width, height, windowStyles.get(style));
}

void Skin::dispose () {
    texture.dispose();
for (BitmapFont font : fonts.values()) {
        font.dispose();
    }
}

gdx_cpp::graphics::Texture& Skin::getTexture () {
    return texture;
}

