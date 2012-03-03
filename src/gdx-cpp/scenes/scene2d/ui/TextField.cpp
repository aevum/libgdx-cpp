
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

#include "TextField.hpp"

using namespace gdx_cpp::scenes::scene2d::ui;

void TextField::setStyle (const TextFieldStyle& style) {
    this.style = style;
}

void TextField::layout () {
}

void TextField::blink () {
    long time = System.nanoTime();
    if ((time - lastBlink) / 1000000000.0f > blinkTime) {
        cursorOn = !cursorOn;
        lastBlink = time;
    }
}

void TextField::calculateOffsets () {
    final NinePatch background = style.background;

    float position = glyphPositions.get(cursor);
    float distance = position - Math.abs(renderOffset);
    float visibleWidth = width - background.getLeftWidth() - background.getRightWidth();

    // check whether the cursor left the left or right side of
    // the visible area and adjust renderoffset.
    if (distance <= 0) {
        if (cursor > 0)
            renderOffset = -glyphPositions.get(cursor - 1);
        else
            renderOffset = 0;
    } else {
        if (distance > visibleWidth) {
            renderOffset -= distance - visibleWidth;
        }
    }

    // calculate first visible char based on render offset
    visibleTextStart = 0;
    textOffset = 0;
    float start = Math.abs(renderOffset);
    int len = glyphPositions.size;
    float startPos = 0;
    for (int i = 0; i < len; i++) {
        if (glyphPositions.items[i] >= start) {
            visibleTextStart = i;
            startPos = glyphPositions.items[i];
            textOffset = glyphPositions.items[visibleTextStart] - start;
            break;
        }
    }

    // calculate last visible char based on visible width and render offset
    visibleTextEnd = Math.min(text.length(), cursor + 1);
    for (; visibleTextEnd <= text.length(); visibleTextEnd++) {
        if (glyphPositions.items[visibleTextEnd] - startPos > visibleWidth) break;
    }
    visibleTextEnd = Math.max(0, visibleTextEnd - 1);

    // calculate selection x position and width
    if (hasSelection) {
        int minIndex = Math.min(cursor, selectionStart);
        int maxIndex = Math.max(cursor, selectionStart);
        float minX = Math.max(glyphPositions.get(minIndex), glyphPositions.get(visibleTextStart));
        float maxX = Math.min(glyphPositions.get(maxIndex), glyphPositions.get(visibleTextEnd));
        selectionX = minX;
        selectionWidth = maxX - minX;
    }
}

void TextField::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    final BitmapFont font = style.font;
    final Color fontColor = style.fontColor;
    final NinePatch background = style.background;
    final TextureRegion selection = style.selection;
    final NinePatch cursorPatch = style.cursor;

    batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);
    background.draw(batch, x, y, width, height);
    float textY = (int)(height / 2) + (int)(textBounds.height / 2) + font.getDescent() / 2;
    font.setColor(fontColor.r, fontColor.g, fontColor.b, fontColor.a * parentAlpha);
    calculateOffsets();

    if (hasSelection) {
        batch.draw(selection, x + selectionX + background.getLeftWidth() + renderOffset,
                   y + textY - textBounds.height - font.getDescent() / 2, selectionWidth, textBounds.height);
    }

    font.draw(batch, text, x + background.getLeftWidth() + textOffset, y + textY, visibleTextStart, visibleTextEnd);
    if (parent.keyboardFocusedActor == this) {
        blink();
        if (cursorOn) {
            cursorPatch.draw(batch, x + background.getLeftWidth() + glyphPositions.get(cursor) + renderOffset - 1, y + textY
                             - textBounds.height - font.getDescent(), cursorPatch.getTotalWidth(), textBounds.height + font.getDescent() / 2);
        }
    }
}

bool TextField::touchDown (float x,float y,int pointer) {
    if (pointer != 0) return false;
    parent.keyboardFocus(this);
    keyboard.show(true);
    x = x - renderOffset;
    for (int i = 0; i < glyphPositions.size; i++) {
        float pos = glyphPositions.items[i];
        if (pos > x) {
            cursor = Math.max(0, i - 1);
            return true;
        }
    }
    cursor = Math.max(0, glyphPositions.size - 1);
    return true;
}

void TextField::touchUp (float x,float y,int pointer) {
}

void TextField::touchDragged (float x,float y,int pointer) {
}

bool TextField::keyDown (int keycode) {
    final BitmapFont font = style.font;

    if (parent.keyboardFocusedActor == this) {
        // clipboard
        if (Gdx.input.isKeyPressed(Keys.CONTROL_LEFT) || Gdx.input.isKeyPressed(Keys.CONTROL_RIGHT)) {
            if (keycode == Keys.V) {
                String content = clipboard.getContents();
                if (content != null) {
                    StringBuilder builder = new StringBuilder();
                    for (int i = 0; i < content.length(); i++) {
                        char c = content.charAt(i);
                        if (font.containsCharacter(c)) {
                            builder.append(c);
                        }
                    }
                    content = builder.toString();
                    text = text.substring(0, cursor) + content + text.substring(cursor, text.length());
                    cursor += content.length();
                    font.computeGlyphAdvancesAndPositions(text, glyphAdvances, glyphPositions);
                }
            }
            if (keycode == Keys.C) {
                if (hasSelection) {
                    int minIndex = Math.min(cursor, selectionStart);
                    int maxIndex = Math.max(cursor, selectionStart);
                    clipboard.setContents(text.substring(minIndex, maxIndex));
                }
            }
        }
        // selection
        else if (Gdx.input.isKeyPressed(Keys.SHIFT_LEFT) || Gdx.input.isKeyPressed(Keys.SHIFT_RIGHT)) {
            if (keycode == Keys.LEFT) {
                if (!hasSelection) {
                    selectionStart = cursor;
                    hasSelection = true;
                }
                cursor--;
            }
            if (keycode == Keys.RIGHT) {
                if (!hasSelection) {
                    selectionStart = cursor;
                    hasSelection = true;
                }
                cursor++;
            }
            if (keycode == Keys.HOME) {
                if (!hasSelection) {
                    selectionStart = cursor;
                    hasSelection = true;
                }
                cursor = 0;
            }
            if (keycode == Keys.END) {
                if (!hasSelection) {
                    selectionStart = cursor;
                    hasSelection = true;
                }
                cursor = text.length();
            }

            cursor = Math.max(0, cursor);
            cursor = Math.min(text.length(), cursor);
        }
        // cursor movement or other keys (kill selection)
        else {
            if (keycode == Keys.LEFT) {
                cursor--;
                hasSelection = false;
            }
            if (keycode == Keys.RIGHT) {
                cursor++;
                ;
                hasSelection = false;
            }
            if (keycode == Keys.HOME) {
                cursor = 0;
                hasSelection = false;
            }
            if (keycode == Keys.END) {
                cursor = text.length();
                hasSelection = false;
            }

            cursor = Math.max(0, cursor);
            cursor = Math.min(text.length(), cursor);
        }

        return true;
    }
    return false;
}

bool TextField::keyTyped (char character) {
    final BitmapFont font = style.font;

    if (parent.keyboardFocusedActor == this) {
        if (character == 8 && (cursor > 0 || hasSelection)) {
            if (!hasSelection) {
                text = text.substring(0, cursor - 1) + text.substring(cursor);
                cursor--;
                font.computeGlyphAdvancesAndPositions(text, glyphAdvances, glyphPositions);
            } else {
                int minIndex = Math.min(cursor, selectionStart);
                int maxIndex = Math.max(cursor, selectionStart);

                text = (minIndex > 0 ? text.substring(0, minIndex) : "")
                       + (maxIndex < text.length() ? text.substring(maxIndex, text.length()) : "");
                cursor = minIndex;
                font.computeGlyphAdvancesAndPositions(text, glyphAdvances, glyphPositions);
                hasSelection = false;
            }
        }
        if (character == 127 && (cursor < text.length() || hasSelection)) {
            if (!hasSelection) {
                text = text.substring(0, cursor) + text.substring(cursor + 1);
                font.computeGlyphAdvancesAndPositions(text, glyphAdvances, glyphPositions);
            } else {
                int minIndex = Math.min(cursor, selectionStart);
                int maxIndex = Math.max(cursor, selectionStart);

                text = (minIndex > 0 ? text.substring(0, minIndex) : "")
                       + (maxIndex < text.length() ? text.substring(maxIndex, text.length()) : "");
                cursor = minIndex;
                font.computeGlyphAdvancesAndPositions(text, glyphAdvances, glyphPositions);
                hasSelection = false;
            }
        }
        if (font.containsCharacter(character)) {
            if (!hasSelection) {
                text = text.substring(0, cursor) + character + text.substring(cursor, text.length());
                cursor++;
                font.computeGlyphAdvancesAndPositions(text, glyphAdvances, glyphPositions);
            } else {
                int minIndex = Math.min(cursor, selectionStart);
                int maxIndex = Math.max(cursor, selectionStart);

                text = (minIndex > 0 ? text.substring(0, minIndex) : "")
                       + (maxIndex < text.length() ? text.substring(maxIndex, text.length()) : "");
                cursor = minIndex;
                text = text.substring(0, cursor) + character + text.substring(cursor, text.length());
                cursor++;
                font.computeGlyphAdvancesAndPositions(text, glyphAdvances, glyphPositions);
                hasSelection = false;
            }
        }
        if (listener != null) listener.keyTyped(this, character);
        return true;
    } else
        return false;
}

gdx_cpp::scenes::scene2d::Actor& TextField::hit (float x,float y) {
    return x > 0 && x < width && y > 0 && y < height ? this : null;
}

void TextField::keyTyped (const TextField& textField,char key);
}

/** Sets the {@link TextFieldListener}
 * @param listener the listener or null */
public void setTextFieldListener (TextFieldListener listener) {
    this.listener = listener;
}

/** Sets the text of this text field.
 * @param text the text */
public void setText (String text) {
    if (text == null) throw new IllegalArgumentException("text must not be null");

    BitmapFont font = style.font;

    this.text = text;
    this.cursor = 0;
    this.hasSelection = false;
    font.computeGlyphAdvancesAndPositions(text, this.glyphAdvances, this.glyphPositions);

    textBounds.set(font.getBounds(text));
    textBounds.height -= font.getDescent() * 2;
    font.computeGlyphAdvancesAndPositions(text, glyphAdvances, glyphPositions);
}

/** @return the text of this text field. Never null, might be an empty string. */
public String getText () {
    return text;
}

public float getPrefWidth () {
    return 150;
}

public float getPrefHeight () {
    NinePatch background = style.background;
    return background.getBottomHeight() + background.getTopHeight() + textBounds.height;
}

/** Returns the currently used {@link OnscreenKeyboard}. {@link TextField} instances use the {@link DefaultOnscreenKeyboard} by
 * default.
 * @return the OnscreenKeyboard. */
public OnscreenKeyboard getOnscreenKeyboard () {
    return keyboard;
}

/** Sets the {@link OnscreenKeyboard} to be used by this textfield
 * @param keyboard the OnscreenKeyboard */
public void setOnscreenKeyboard (OnscreenKeyboard keyboard) {
    this.keyboard = keyboard;
}

/** An interface for onscreen keyboards. Can invoke the default keyboard or render your own keyboard!
 * @author mzechner */
public interface OnscreenKeyboard {
    public void show (boolean visible);
}

/** The default {@link OnscreenKeyboard} used by all {@link TextField} instances. Just uses
 * {@link Input#setOnscreenKeyboardVisible(boolean)} as appropriate. Might overlap your actual rendering, so use with care!
 * @author mzechner */
public static class DefaultOnscreenKeyboard implements OnscreenKeyboard {
    @Override
    public void show (boolean visible) {
        Gdx.input.setOnscreenKeyboardVisible(visible);
    }

    void TextField::setTextFieldListener (const TextFieldListener& listener) {
        this.listener = listener;
    }

    void TextField::setText (const std::string& text) {
        if (text == null) throw new IllegalArgumentException("text must not be null");

        BitmapFont font = style.font;

        this.text = text;
        this.cursor = 0;
        this.hasSelection = false;
        font.computeGlyphAdvancesAndPositions(text, this.glyphAdvances, this.glyphPositions);

        textBounds.set(font.getBounds(text));
        textBounds.height -= font.getDescent() * 2;
        font.computeGlyphAdvancesAndPositions(text, glyphAdvances, glyphPositions);
    }

    std::string& TextField::getText () {
        return text;
    }

    float TextField::getPrefWidth () {
        return 150;
    }

    float TextField::getPrefHeight () {
        NinePatch background = style.background;
        return background.getBottomHeight() + background.getTopHeight() + textBounds.height;
    }

    OnscreenKeyboard& TextField::getOnscreenKeyboard () {
        return keyboard;
    }

    void TextField::setOnscreenKeyboard (const OnscreenKeyboard& keyboard) {
        this.keyboard = keyboard;
    }

    void TextField::show (bool visible);
}

/** The default {@link OnscreenKeyboard} used by all {@link TextField} instances. Just uses
 * {@link Input#setOnscreenKeyboardVisible(boolean)} as appropriate. Might overlap your actual rendering, so use with care!
 * @author mzechner */
public static class DefaultOnscreenKeyboard implements OnscreenKeyboard {
    @Override
    public void show (boolean visible) {
        Gdx.input.setOnscreenKeyboardVisible(visible);
    }

    void TextField::show (bool visible) {
        Gdx.input.setOnscreenKeyboardVisible(visible);
    }

    void TextField::setClipboard (const gdx_cpp::scenes::scene2d::ui::utils::Clipboard& clipboard) {
        this.clipboard = clipboard;
    }

    TextField::TextField (const Skin& skin) {
        this("", skin.getStyle(TextFieldStyle.class), null);
    }

    TextField::TextField (const std::string& text,const Skin& skin) {
        this(text, skin.getStyle(TextFieldStyle.class), null);
    }

    TextField::TextField (const TextFieldStyle& style) {
        this("", style, null);
    }

    TextField::TextField (const std::string& text,const TextFieldStyle& style) {
        this(text, style, null);
    }

    TextField::TextField (const std::string& text,const TextFieldStyle& style,const std::string& name) {
        super(name);
        setStyle(style);
        this.clipboard = Clipboard.getDefaultClipboard();
        setText(text);
    }

