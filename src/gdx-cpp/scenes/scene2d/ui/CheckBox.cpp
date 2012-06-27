
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

#include "CheckBox.hpp"

using namespace gdx::ui;

void CheckBox::click () {
    super.click();
    image.setRegion(isChecked ? ((CheckBoxStyle)style).checkboxOn : ((CheckBoxStyle)style).checkboxOff);
}

CheckBox::CheckBox (const std::string& text,const CheckBoxStyle& style) {
    this(text, style, null);
}

CheckBox::CheckBox (const std::string& text,const Skin& skin) {
    this(text, skin.getStyle(CheckBoxStyle.class), null);
}

CheckBox::CheckBox (const std::string& text,const CheckBoxStyle& style,const std::string& name) {
    super(style, name);
    add(image = new Image(style.checkboxOff));
    add(new Label(text, style));
}

