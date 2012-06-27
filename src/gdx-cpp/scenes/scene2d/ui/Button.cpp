
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

#include "Button.hpp"

using namespace gdx::ui;

void Button::click (const gdx::Actor& actor) {
    isChecked = !isChecked;
    if (listener != null) listener.click(actor);
}

void Button::setStyle (const ButtonStyle& style) {
    this.style = style;
    setBackground(isPressed ? style.down : style.up);
}

void Button::setClickListener (const ClickListener& listener) {
    this.listener = listener;
}

void Button::setText (const std::string& text) {
    if (children.isEmpty()) {
        add(new Label(text, style));
        return;
    }
    for (int i = 0; i < children.size(); i++) {
        Actor child = children.get(i);
        if (child instanceof Label) {
            ((Label)child).setText(text);
            return;
        }
    }
    throw new GdxRuntimeException("No child label was found.");
}

std::string& Button::getText () {
    for (int i = 0; i < children.size(); i++) {
        Actor child = children.get(i);
        if (child instanceof Label) return ((Label)child).getText();
    }
    throw new GdxRuntimeException("No child label was found.");
}

void Button::draw (const gdx::SpriteBatch& batch,float parentAlpha) {
    float offsetX = 0, offsetY = 0;
    if (isPressed) {
        setBackground(style.down == null ? style.up : style.down);
        offsetX = style.pressedOffsetX;
        offsetY = style.pressedOffsetY;
    } else {
        if (style.checked == null)
            setBackground(style.up);
        else
            setBackground(isChecked ? style.checked : style.up);
        offsetX = style.unpressedOffsetX;
        offsetY = style.unpressedOffsetY;
    }
    for (int i = 0; i < children.size(); i++) {
        Actor child = children.get(i);
        child.x += offsetX;
        child.y += offsetY;
    }
    super.draw(batch, parentAlpha);
    for (int i = 0; i < children.size(); i++) {
        Actor child = children.get(i);
        child.x -= offsetX;
        child.y -= offsetY;
    }
}

Button::Button (const Skin& skin) {
    this(skin.getStyle(ButtonStyle.class), null);
}

Button::Button (const ButtonStyle& style) {
    this(style, null);
}

Button::Button (const gdx::Actor& child,const Skin& skin) {
    this(child, skin.getStyle(ButtonStyle.class));
}

Button::Button (const gdx::Actor& child,const ButtonStyle& style) {
    this(style, null);
    add(child);
}

Button::Button (const std::string& text,const Skin& skin) {
    this(skin.getStyle(ButtonStyle.class), null);
    setText(text);
}

Button::Button (const std::string& text,const ButtonStyle& style) {
    this(style, null);
    setText(text);
}

Button::Button (const std::string& text,const ButtonStyle& style,const std::string& name) {
    this(style, name);
    setText(text);
}

Button::Button (const ButtonStyle& style,const std::string& name) {
    super(name);
    setStyle(style);
    super.setClickListener(new ClickListener() {
        public void click (Actor actor) {
            isChecked = !isChecked;
            if (listener != null) listener.click(actor);
        }
    });
}

