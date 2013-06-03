/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 *  @author aevum team
 */

#include <SDL/SDL_keyboard.h>
#include <SDL/SDL_keycode.h>
#include <gdx-cpp/InputProcessor.hpp>

#include "EmscriptenInput.hpp"
#include "gdx-cpp/Input.hpp"

using namespace gdx::scripten;

EmscriptenInput::EmscriptenInput() : processor(nullptr),
    _justTouched(false),
    touching(false),
    touchX(0),
    deltaX(0),
    touchY(0),
    deltaY(0)    
{
}

void gdx::scripten::EmscriptenInput::cancelVibrate()
{
}

float gdx::scripten::EmscriptenInput::getAccelerometerX()
{
    return 0;
}

float gdx::scripten::EmscriptenInput::getAccelerometerY()
{
    return 0;
}

float gdx::scripten::EmscriptenInput::getAccelerometerZ()
{
    return 0;
}

float gdx::scripten::EmscriptenInput::getAzimuth()
{
    return 0;
}

long int gdx::scripten::EmscriptenInput::getCurrentEventTime()
{
    return 0;
}

int gdx::scripten::EmscriptenInput::getDeltaX()
{
    return deltaX;
}

int gdx::scripten::EmscriptenInput::getDeltaX(int pointer)
{
    if (pointer == 0) {
        return deltaX;
    }
    return 0;
}

int gdx::scripten::EmscriptenInput::getDeltaY()
{
    return deltaY;
}

int gdx::scripten::EmscriptenInput::getDeltaY(int pointer)
{
    if (pointer == 0) {
        return deltaY;
    }
    return 0;
}

gdx::Input::Orientation gdx::scripten::EmscriptenInput::getNativeOrientation()
{
    return gdx::Input::Landscape;
}

float gdx::scripten::EmscriptenInput::getPitch()
{
    return 0;
}

float gdx::scripten::EmscriptenInput::getRoll()
{
    return 0;
}

int gdx::scripten::EmscriptenInput::getRotation()
{
    return 0;
}

void gdx::scripten::EmscriptenInput::getTextInput(const gdx::Input::TextInputListener& listener,
                                        const std::string& title, const std::string& text)
{

}

int gdx::scripten::EmscriptenInput::getX()
{
    return touchX;
}

int gdx::scripten::EmscriptenInput::getX(int pointer)
{
    return 0;
}

int gdx::scripten::EmscriptenInput::getY()
{
    return touchY;
}

int gdx::scripten::EmscriptenInput::getY(int pointer)
{
    return 0;
}

bool gdx::scripten::EmscriptenInput::isButtonPressed(int button)
{
    return false;
}

bool gdx::scripten::EmscriptenInput::isCursorCatched()
{
    return false;
}

bool gdx::scripten::EmscriptenInput::isKeyPressed(int key)
{
    return false;
}

bool gdx::scripten::EmscriptenInput::isPeripheralAvailable(int peripheral)
{
    return peripheral == Peripheral::HardwareKeyboard;
}

bool gdx::scripten::EmscriptenInput::isTouched()
{
    return touching;
}

bool gdx::scripten::EmscriptenInput::isTouched(int pointer)
{
    return pointer == 0 && touching;
}

bool gdx::scripten::EmscriptenInput::justTouched()
{
    return _justTouched;
}

void gdx::scripten::EmscriptenInput::setCatchBackKey(bool catchBack)
{

}

void gdx::scripten::EmscriptenInput::setCatchMenuKey(bool catchMenu)
{

}

void gdx::scripten::EmscriptenInput::setCursorCatched(bool catched)
{

}

void gdx::scripten::EmscriptenInput::setCursorPosition(int x, int y)
{

}

void gdx::scripten::EmscriptenInput::setInputProcessor(gdx::InputProcessor* processor)
{
    this->processor = processor;
}

void gdx::scripten::EmscriptenInput::setOnscreenKeyboardVisible(bool visible)
{
}

void gdx::scripten::EmscriptenInput::vibrate(int milliseconds)
{
}

void gdx::scripten::EmscriptenInput::vibrate(long int* pattern, int repeat)
{
}

void gdx::scripten::EmscriptenInput::processEvents(SDL_Event& evt)
{
    static struct transalte_button {
        int operator()(int sdl_button) {
            switch(sdl_button) {
            case 1:
                return gdx::Input::Button::LEFT;
            case 2:
                return gdx::Input::Button::MIDDLE;
            case 3:
                return gdx::Input::Button::RIGHT;
            default:
                return sdl_button;
            }
        }
    } tb;

    if (processor == nullptr) {
        return;
    }

    if (evt.type == SDL_MOUSEMOTION) {

        deltaX = evt.motion.xrel;
        deltaY = evt.motion.yrel;

        if (this->touching) {
            this->processor->touchDragged(evt.motion.x, evt.motion.y, tb(evt.button.button));
        } else {
            this->processor->touchMoved(evt.motion.x, evt.motion.y);
        }

    } else if (evt.type == SDL_MOUSEBUTTONDOWN) {
        this->touching = true;
        touchX = evt.motion.x;
        touchY = evt.motion.y;
        deltaX = evt.motion.xrel;
        deltaY = evt.motion.yrel;
        this->_justTouched = true;

        this->processor->touchDown(evt.motion.x, evt.motion.y, 0, tb(evt.button.button));

    } else if (evt.type == SDL_MOUSEBUTTONUP) {
        this->touching = false;
        touchY =touchX = 0;

        this->processor->touchUp(evt.motion.x, evt.motion.y, 0, tb(evt.button.button));
    }
    else if (evt.type == SDL_KEYDOWN) {
        if (gdx::Input::Keys::ESCAPE == getGdxEventKey(evt)) {
            this->processor->keyDown(getGdxEventKey(evt));
        }
    } else if (evt.type == SDL_KEYUP) {
        if (gdx::Input::Keys::ESCAPE != getGdxEventKey(evt)) {
            this->processor->keyUp(getGdxEventKey(evt));
        }
    }
}

void gdx::scripten::EmscriptenInput::reset()
{
    this->_justTouched = false;
}

int gdx::scripten::EmscriptenInput::getGdxEventKey(SDL_Event& eventkey) {
    switch ( eventkey.key.keysym.sym )
    {
    case SDLK_UNKNOWN:
        return gdx::Input::Keys::UNKNOWN;
//     case SDLK_FIRST:
//         return gdx::Input::Keys::FIRST;
    case SDLK_BACKSPACE:
        return gdx::Input::Keys::BACKSPACE;
    case SDLK_TAB:
        return gdx::Input::Keys::TAB;
    case SDLK_CLEAR:
        return gdx::Input::Keys::CLEAR;
//     case SDLK_RETURN:
//         return gdx::Input::Keys::RETURN;
//     case SDLK_PAUSE:
//         return gdx::Input::Keys::PAUSE;
    case SDLK_ESCAPE:
        return gdx::Input::Keys::ESCAPE;
    case SDLK_SPACE:
        return gdx::Input::Keys::SPACE;
//     case SDLK_EXCLAIM:
//         return gdx::Input::Keys::EXCLAIM;
//     case SDLK_QUOTEDBL:
//         return gdx::Input::Keys::QUOTEDBL;
//     case SDLK_HASH:
//         return gdx::Input::Keys::HASH;
//     case SDLK_DOLLAR:
//         return gdx::Input::Keys::DOLLAR;
//     case SDLK_AMPERSAND:
//         return gdx::Input::Keys::AMPERSAND;
//     case SDLK_QUOTE:
//         return gdx::Input::Keys::QUOTE;
//     case SDLK_LEFTPAREN:
//         return gdx::Input::Keys::LEFTPAREN;
//     case SDLK_RIGHTPAREN:
//         return gdx::Input::Keys::RIGHTPAREN;
//     case SDLK_ASTERISK:
//         return gdx::Input::Keys::ASTERISK;
    case SDLK_PLUS:
        return gdx::Input::Keys::PLUS;
    case SDLK_COMMA:
        return gdx::Input::Keys::COMMA;
    case SDLK_MINUS:
        return gdx::Input::Keys::MINUS;
    case SDLK_PERIOD:
        return gdx::Input::Keys::PERIOD;
    case SDLK_SLASH:
        return gdx::Input::Keys::SLASH;
    case SDLK_0:
        return gdx::Input::Keys::NUM_0;
    case SDLK_1:
        return gdx::Input::Keys::NUM_1;
    case SDLK_2:
        return gdx::Input::Keys::NUM_2;
    case SDLK_3:
        return gdx::Input::Keys::NUM_3;
    case SDLK_4:
        return gdx::Input::Keys::NUM_4;
    case SDLK_5:
        return gdx::Input::Keys::NUM_5;
    case SDLK_6:
        return gdx::Input::Keys::NUM_6;
    case SDLK_7:
        return gdx::Input::Keys::NUM_7;
    case SDLK_8:
        return gdx::Input::Keys::NUM_8;
    case SDLK_9:
        return gdx::Input::Keys::NUM_9;
    case SDLK_COLON:
        return gdx::Input::Keys::COLON;
    case SDLK_SEMICOLON:
        return gdx::Input::Keys::SEMICOLON;
//     case SDLK_LESS:
//         return gdx::Input::Keys::LESS;
    case SDLK_EQUALS:
        return gdx::Input::Keys::EQUALS;
//     case SDLK_GREATER:
//         return gdx::Input::Keys::GREATER;
//     case SDLK_QUESTION:
//         return gdx::Input::Keys::QUESTION;
    case SDLK_AT:
        return gdx::Input::Keys::AT;
    case SDLK_LEFTBRACKET:
        return gdx::Input::Keys::LEFT_BRACKET;
    case SDLK_BACKSLASH:
        return gdx::Input::Keys::BACKSLASH;
    case SDLK_RIGHTBRACKET:
        return gdx::Input::Keys::RIGHT_BRACKET;
//     case SDLK_CARET:
//         return gdx::Input::Keys::CARET;
//     case SDLK_UNDERSCORE:
//         return gdx::Input::Keys::UNDERSCORE;
//     case SDLK_BACKQUOTE:
//         return gdx::Input::Keys::BACKQUOTE;
    case SDLK_a:
        return gdx::Input::Keys::A;
    case SDLK_b:
        return gdx::Input::Keys::B;
    case SDLK_c:
        return gdx::Input::Keys::C;
    case SDLK_d:
        return gdx::Input::Keys::D;
    case SDLK_e:
        return gdx::Input::Keys::E;
    case SDLK_f:
        return gdx::Input::Keys::F;
    case SDLK_g:
        return gdx::Input::Keys::G;
    case SDLK_h:
        return gdx::Input::Keys::H;
    case SDLK_i:
        return gdx::Input::Keys::I;
    case SDLK_j:
        return gdx::Input::Keys::J;
    case SDLK_k:
        return gdx::Input::Keys::K;
    case SDLK_l:
        return gdx::Input::Keys::L;
    case SDLK_m:
        return gdx::Input::Keys::M;
    case SDLK_n:
        return gdx::Input::Keys::N;
    case SDLK_o:
        return gdx::Input::Keys::O;
    case SDLK_p:
        return gdx::Input::Keys::P;
    case SDLK_q:
        return gdx::Input::Keys::Q;
    case SDLK_r:
        return gdx::Input::Keys::R;
    case SDLK_s:
        return gdx::Input::Keys::S;
    case SDLK_t:
        return gdx::Input::Keys::T;
    case SDLK_u:
        return gdx::Input::Keys::U;
    case SDLK_v:
        return gdx::Input::Keys::V;
    case SDLK_w:
        return gdx::Input::Keys::W;
    case SDLK_x:
        return gdx::Input::Keys::X;
    case SDLK_y:
        return gdx::Input::Keys::Y;
    case SDLK_z:
        return gdx::Input::Keys::Z;
    case SDLK_DELETE:
        return gdx::Input::Keys::DEL;
//     case SDLK_WORLD_0:
//         return gdx::Input::Keys::WORLD_0;
//     case SDLK_WORLD_1:
//         return gdx::Input::Keys::WORLD_1;
//     case SDLK_WORLD_2:
//         return gdx::Input::Keys::WORLD_2;
//     case SDLK_WORLD_3:
//         return gdx::Input::Keys::WORLD_3;
//     case SDLK_WORLD_4:
//         return gdx::Input::Keys::WORLD_4;
//     case SDLK_WORLD_5:
//         return gdx::Input::Keys::WORLD_5;
//     case SDLK_WORLD_6:
//         return gdx::Input::Keys::WORLD_6;
//     case SDLK_WORLD_7:
//         return gdx::Input::Keys::WORLD_7;
//     case SDLK_WORLD_8:
//         return gdx::Input::Keys::WORLD_8;
//     case SDLK_WORLD_9:
//         return gdx::Input::Keys::WORLD_9;
//     case SDLK_WORLD_10:
//         return gdx::Input::Keys::WORLD_10;
//     case SDLK_WORLD_11:
//         return gdx::Input::Keys::WORLD_11;
//     case SDLK_WORLD_12:
//         return gdx::Input::Keys::WORLD_12;
//     case SDLK_WORLD_13:
//         return gdx::Input::Keys::WORLD_13;
//     case SDLK_WORLD_14:
//         return gdx::Input::Keys::WORLD_14;
//     case SDLK_WORLD_15:
//         return gdx::Input::Keys::WORLD_15;
//     case SDLK_WORLD_16:
//         return gdx::Input::Keys::WORLD_16;
//     case SDLK_WORLD_17:
//         return gdx::Input::Keys::WORLD_17;
//     case SDLK_WORLD_18:
//         return gdx::Input::Keys::WORLD_18;
//     case SDLK_WORLD_19:
//         return gdx::Input::Keys::WORLD_19;
//     case SDLK_WORLD_20:
//         return gdx::Input::Keys::WORLD_20;
//     case SDLK_WORLD_21:
//         return gdx::Input::Keys::WORLD_21;
//     case SDLK_WORLD_22:
//         return gdx::Input::Keys::WORLD_22;
//     case SDLK_WORLD_23:
//         return gdx::Input::Keys::WORLD_23;
//     case SDLK_WORLD_24:
//         return gdx::Input::Keys::WORLD_24;
//     case SDLK_WORLD_25:
//         return gdx::Input::Keys::WORLD_25;
//     case SDLK_WORLD_26:
//         return gdx::Input::Keys::WORLD_26;
//     case SDLK_WORLD_27:
//         return gdx::Input::Keys::WORLD_27;
//     case SDLK_WORLD_28:
//         return gdx::Input::Keys::WORLD_28;
//     case SDLK_WORLD_29:
//         return gdx::Input::Keys::WORLD_29;
//     case SDLK_WORLD_30:
//         return gdx::Input::Keys::WORLD_30;
//     case SDLK_WORLD_31:
//         return gdx::Input::Keys::WORLD_31;
//     case SDLK_WORLD_32:
//         return gdx::Input::Keys::WORLD_32;
//     case SDLK_WORLD_33:
//         return gdx::Input::Keys::WORLD_33;
//     case SDLK_WORLD_34:
//         return gdx::Input::Keys::WORLD_34;
//     case SDLK_WORLD_35:
//         return gdx::Input::Keys::WORLD_35;
//     case SDLK_WORLD_36:
//         return gdx::Input::Keys::WORLD_36;
//     case SDLK_WORLD_37:
//         return gdx::Input::Keys::WORLD_37;
//     case SDLK_WORLD_38:
//         return gdx::Input::Keys::WORLD_38;
//     case SDLK_WORLD_39:
//         return gdx::Input::Keys::WORLD_39;
//     case SDLK_WORLD_40:
//         return gdx::Input::Keys::WORLD_40;
//     case SDLK_WORLD_41:
//         return gdx::Input::Keys::WORLD_41;
//     case SDLK_WORLD_42:
//         return gdx::Input::Keys::WORLD_42;
//     case SDLK_WORLD_43:
//         return gdx::Input::Keys::WORLD_43;
//     case SDLK_WORLD_44:
//         return gdx::Input::Keys::WORLD_44;
//     case SDLK_WORLD_45:
//         return gdx::Input::Keys::WORLD_45;
//     case SDLK_WORLD_46:
//         return gdx::Input::Keys::WORLD_46;
//     case SDLK_WORLD_47:
//         return gdx::Input::Keys::WORLD_47;
//     case SDLK_WORLD_48:
//         return gdx::Input::Keys::WORLD_48;
//     case SDLK_WORLD_49:
//         return gdx::Input::Keys::WORLD_49;
//     case SDLK_WORLD_50:
//         return gdx::Input::Keys::WORLD_50;
//     case SDLK_WORLD_51:
//         return gdx::Input::Keys::WORLD_51;
//     case SDLK_WORLD_52:
//         return gdx::Input::Keys::WORLD_52;
//     case SDLK_WORLD_53:
//         return gdx::Input::Keys::WORLD_53;
//     case SDLK_WORLD_54:
//         return gdx::Input::Keys::WORLD_54;
//     case SDLK_WORLD_55:
//         return gdx::Input::Keys::WORLD_55;
//     case SDLK_WORLD_56:
//         return gdx::Input::Keys::WORLD_56;
//     case SDLK_WORLD_57:
//         return gdx::Input::Keys::WORLD_57;
//     case SDLK_WORLD_58:
//         return gdx::Input::Keys::WORLD_58;
//     case SDLK_WORLD_59:
//         return gdx::Input::Keys::WORLD_59;
//     case SDLK_WORLD_60:
//         return gdx::Input::Keys::WORLD_60;
//     case SDLK_WORLD_61:
//         return gdx::Input::Keys::WORLD_61;
//     case SDLK_WORLD_62:
//         return gdx::Input::Keys::WORLD_62;
//     case SDLK_WORLD_63:
//         return gdx::Input::Keys::WORLD_63;
//     case SDLK_WORLD_64:
//         return gdx::Input::Keys::WORLD_64;
//     case SDLK_WORLD_65:
//         return gdx::Input::Keys::WORLD_65;
//     case SDLK_WORLD_66:
//         return gdx::Input::Keys::WORLD_66;
//     case SDLK_WORLD_67:
//         return gdx::Input::Keys::WORLD_67;
//     case SDLK_WORLD_68:
//         return gdx::Input::Keys::WORLD_68;
//     case SDLK_WORLD_69:
//         return gdx::Input::Keys::WORLD_69;
//     case SDLK_WORLD_70:
//         return gdx::Input::Keys::WORLD_70;
//     case SDLK_WORLD_71:
//         return gdx::Input::Keys::WORLD_71;
//     case SDLK_WORLD_72:
//         return gdx::Input::Keys::WORLD_72;
//     case SDLK_WORLD_73:
//         return gdx::Input::Keys::WORLD_73;
//     case SDLK_WORLD_74:
//         return gdx::Input::Keys::WORLD_74;
//     case SDLK_WORLD_75:
//         return gdx::Input::Keys::WORLD_75;
//     case SDLK_WORLD_76:
//         return gdx::Input::Keys::WORLD_76;
//     case SDLK_WORLD_77:
//         return gdx::Input::Keys::WORLD_77;
//     case SDLK_WORLD_78:
//         return gdx::Input::Keys::WORLD_78;
//     case SDLK_WORLD_79:
//         return gdx::Input::Keys::WORLD_79;
//     case SDLK_WORLD_80:
//         return gdx::Input::Keys::WORLD_80;
//     case SDLK_WORLD_81:
//         return gdx::Input::Keys::WORLD_81;
//     case SDLK_WORLD_82:
//         return gdx::Input::Keys::WORLD_82;
//     case SDLK_WORLD_83:
//         return gdx::Input::Keys::WORLD_83;
//     case SDLK_WORLD_84:
//         return gdx::Input::Keys::WORLD_84;
//     case SDLK_WORLD_85:
//         return gdx::Input::Keys::WORLD_85;
//     case SDLK_WORLD_86:
//         return gdx::Input::Keys::WORLD_86;
//     case SDLK_WORLD_87:
//         return gdx::Input::Keys::WORLD_87;
//     case SDLK_WORLD_88:
//         return gdx::Input::Keys::WORLD_88;
//     case SDLK_WORLD_89:
//         return gdx::Input::Keys::WORLD_89;
//     case SDLK_WORLD_90:
//         return gdx::Input::Keys::WORLD_90;
//     case SDLK_WORLD_91:
//         return gdx::Input::Keys::WORLD_91;
//     case SDLK_WORLD_92:
//         return gdx::Input::Keys::WORLD_92;
//     case SDLK_WORLD_93:
//         return gdx::Input::Keys::WORLD_93;
//     case SDLK_WORLD_94:
//         return gdx::Input::Keys::WORLD_94;
//     case SDLK_WORLD_95:
//         return gdx::Input::Keys::WORLD_95;
    case SDLK_KP_0:
        return gdx::Input::Keys::NUM_0;
    case SDLK_KP_1:
        return gdx::Input::Keys::NUM_1;
    case SDLK_KP_2:
        return gdx::Input::Keys::NUM_2;
    case SDLK_KP_3:
        return gdx::Input::Keys::NUM_3;
    case SDLK_KP_4:
        return gdx::Input::Keys::NUM_4;
    case SDLK_KP_5:
        return gdx::Input::Keys::NUM_5;
    case SDLK_KP_6:
        return gdx::Input::Keys::NUM_6;
    case SDLK_KP_7:
        return gdx::Input::Keys::NUM_7;
    case SDLK_KP_8:
        return gdx::Input::Keys::NUM_8;
    case SDLK_KP_9:
        return gdx::Input::Keys::NUM_9;
    case SDLK_KP_PERIOD:
        return gdx::Input::Keys::PERIOD;
//     case SDLK_KP_DIVIDE:
//         return gdx::Input::Keys::KP_DIVIDE;
//     case SDLK_KP_MULTIPLY:
//         return gdx::Input::Keys::KP_MULTIPLY;
    case SDLK_KP_MINUS:
        return gdx::Input::Keys::MINUS;
    case SDLK_KP_PLUS:
        return gdx::Input::Keys::PLUS;
    case SDLK_KP_ENTER:
        return gdx::Input::Keys::ENTER;
    case SDLK_KP_EQUALS:
        return gdx::Input::Keys::EQUALS;
    case SDLK_UP:
        return gdx::Input::Keys::UP;
    case SDLK_DOWN:
        return gdx::Input::Keys::DOWN;
    case SDLK_RIGHT:
        return gdx::Input::Keys::RIGHT;
    case SDLK_LEFT:
        return gdx::Input::Keys::LEFT;
    case SDLK_INSERT:
        return gdx::Input::Keys::INSERT;
    case SDLK_HOME:
        return gdx::Input::Keys::HOME;
    case SDLK_END:
        return gdx::Input::Keys::END;
    case SDLK_PAGEUP:
        return gdx::Input::Keys::PAGE_UP;
    case SDLK_PAGEDOWN:
        return gdx::Input::Keys::PAGE_DOWN;
    case SDLK_F1:
        return gdx::Input::Keys::F1;
    case SDLK_F2:
        return gdx::Input::Keys::F2;
    case SDLK_F3:
        return gdx::Input::Keys::F3;
    case SDLK_F4:
        return gdx::Input::Keys::F4;
    case SDLK_F5:
        return gdx::Input::Keys::F5;
    case SDLK_F6:
        return gdx::Input::Keys::F6;
    case SDLK_F7:
        return gdx::Input::Keys::F7;
    case SDLK_F8:
        return gdx::Input::Keys::F8;
    case SDLK_F9:
        return gdx::Input::Keys::F9;
    case SDLK_F10:
        return gdx::Input::Keys::F10;
    case SDLK_F11:
        return gdx::Input::Keys::F11;
    case SDLK_F12:
        return gdx::Input::Keys::F12;
//     case SDLK_F13:
//         return gdx::Input::Keys::F13;
//     case SDLK_F14:
//         return gdx::Input::Keys::F14;
//     case SDLK_F15:
//         return gdx::Input::Keys::F15;
//     case SDLK_NUMLOCK:
//         return gdx::Input::Keys::NUMLOCK;
//     case SDLK_CAPSLOCK:
//         return gdx::Input::Keys::CAPSLOCK;
//     case SDLK_SCROLLOCK:
//         return gdx::Input::Keys::SCROLLOCK;
    case SDLK_RSHIFT:
        return gdx::Input::Keys::SHIFT_RIGHT;
    case SDLK_LSHIFT:
        return gdx::Input::Keys::SHIFT_LEFT;
    case SDLK_RCTRL:
        return gdx::Input::Keys::CONTROL_RIGHT;
    case SDLK_LCTRL:
        return gdx::Input::Keys::CONTROL_LEFT;
    case SDLK_RALT:
        return gdx::Input::Keys::ALT_RIGHT;
    case SDLK_LALT:
        return gdx::Input::Keys::ALT_LEFT;
//     case SDLK_RMETA:
//         return gdx::Input::Keys::RMETA;
//     case SDLK_LMETA:
//         return gdx::Input::Keys::LMETA;
//     case SDLK_LSUPER:
//         return gdx::Input::Keys::LSUPER;
//     case SDLK_RSUPER:
//         return gdx::Input::Keys::RSUPER;
//     case SDLK_MODE:
//         return gdx::Input::Keys::MODE;
//     case SDLK_COMPOSE:
//         return gdx::Input::Keys::COMPOSE;
//     case SDLK_HELP:
//         return gdx::Input::Keys::HELP;
//     case SDLK_PRINT:
//         return gdx::Input::Keys::PRINT;
//     case SDLK_SYSREQ:
//         return gdx::Input::Keys::SYSREQ;
//     case SDLK_BREAK:
//         return gdx::Input::Keys::BREAK;
    case SDLK_MENU:
        return gdx::Input::Keys::MENU;
    case SDLK_POWER:
        return gdx::Input::Keys::POWER;
//     case SDLK_EURO:
//         return gdx::Input::Keys::EURO;
//     case SDLK_UNDO:
//         return gdx::Input::Keys::UNDO;
    default:
        return gdx::Input::Keys::UNKNOWN;
    }
}

void gdx::scripten::EmscriptenInput::setKeyboardRepeat(int delay, int repeatInterval)
{
    //SDL_EnableKeyRepeat(delay, repeatInterval);
}


