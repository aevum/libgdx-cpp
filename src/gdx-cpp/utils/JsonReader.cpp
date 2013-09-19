


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

#include "JsonReader.hpp"
#include <stdexcept>
#include <list>
#include "StringConvertion.hpp"
#include <string.h>
#include "ArrayUtils.hpp"

#include "gdx-cpp/Gdx.hpp"

using namespace gdx;


static const int json_start = 1;
//static const int json_first_final = 71;
//tatic const int json_error = 0;

//static const int json_en_object = 9;
//static const int json_en_array = 43;
//static const int json_en_main = 1;


JsonReader::JsonReader()
{
}

JsonValue JsonReader::parse (const std::string& json) {
    return parse(json.c_str(), 0, json.length());
}

JsonValue JsonReader::parse (const gdx::FileHandle& file) {
    try {
        gdx::FileHandle::buffer_ptr buffer;
        int size = file.readBytes(buffer);

        return parse(buffer.get(), 0, size);
    } catch (...) {
        gdx_log_error("gdx","Error parsing file: %s", file.name().c_str());
    }
}

JsonValue JsonReader::parse(const char* data, int offset, int length)
{
    JsonReader reader;
    return reader.doParse(data,offset, length);
}

JsonValue JsonReader::doParse (const char* data, int offset, int length) {
    root = JsonValue();
    current = nullptr;
    elements.clear();

    unsigned int cs, top = 0;

    std::vector<int> stack;
    char* s = nullptr, *p = (char*)data + offset,* pe = (char*)data + length,* eof = pe;

    std::list<std::string> names;

    bool needsUnescape = false;

    bool debug = false;

    if (debug) {
       gdx_log_debug("JsonReader","\n");
    }

    try {
        
	{
	cs = json_start;
	top = 0;
	}

	{
	if ( p == pe )
		goto _test_eof;
	goto _resume;

_again:
	switch ( cs ) {
		case 1: goto st1;
		case 0: goto st0;
		case 2: goto st2;
		case 3: goto st3;
		case 71: goto st71;
		case 4: goto st4;
		case 72: goto st72;
		case 5: goto st5;
		case 73: goto st73;
		case 6: goto st6;
		case 74: goto st74;
		case 7: goto st7;
		case 8: goto st8;
		case 75: goto st75;
		case 76: goto st76;
		case 77: goto st77;
		case 78: goto st78;
		case 79: goto st79;
		case 80: goto st80;
		case 81: goto st81;
		case 82: goto st82;
		case 83: goto st83;
		case 84: goto st84;
		case 85: goto st85;
		case 86: goto st86;
		case 87: goto st87;
		case 88: goto st88;
		case 89: goto st89;
		case 9: goto st9;
		case 10: goto st10;
		case 11: goto st11;
		case 12: goto st12;
		case 13: goto st13;
		case 14: goto st14;
		case 15: goto st15;
		case 16: goto st16;
		case 17: goto st17;
		case 18: goto st18;
		case 90: goto st90;
		case 19: goto st19;
		case 20: goto st20;
		case 21: goto st21;
		case 22: goto st22;
		case 23: goto st23;
		case 24: goto st24;
		case 25: goto st25;
		case 26: goto st26;
		case 27: goto st27;
		case 28: goto st28;
		case 29: goto st29;
		case 30: goto st30;
		case 31: goto st31;
		case 32: goto st32;
		case 33: goto st33;
		case 34: goto st34;
		case 35: goto st35;
		case 36: goto st36;
		case 37: goto st37;
		case 38: goto st38;
		case 39: goto st39;
		case 40: goto st40;
		case 41: goto st41;
		case 42: goto st42;
		case 43: goto st43;
		case 44: goto st44;
		case 45: goto st45;
		case 46: goto st46;
		case 47: goto st47;
		case 48: goto st48;
		case 91: goto st91;
		case 49: goto st49;
		case 50: goto st50;
		case 51: goto st51;
		case 52: goto st52;
		case 53: goto st53;
		case 54: goto st54;
		case 55: goto st55;
		case 56: goto st56;
		case 57: goto st57;
		case 58: goto st58;
		case 59: goto st59;
		case 60: goto st60;
		case 61: goto st61;
		case 62: goto st62;
		case 63: goto st63;
		case 64: goto st64;
		case 65: goto st65;
		case 66: goto st66;
		case 67: goto st67;
		case 68: goto st68;
		case 69: goto st69;
		case 70: goto st70;
	default: break;
	}

	if ( ++p == pe )
		goto _test_eof;
_resume:
	switch ( cs )
	{
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	switch( (*p) ) {
		case 32: goto st1;
		case 34: goto st2;
		case 36: goto tr3;
		case 45: goto tr4;
		case 48: goto tr5;
		case 91: goto tr7;
		case 95: goto tr3;
		case 102: goto tr8;
		case 110: goto tr9;
		case 116: goto tr10;
		case 123: goto tr11;
	}
	if ( (*p) < 49 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto st1;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr3;
		} else if ( (*p) >= 65 )
			goto tr3;
	} else
		goto tr6;
	goto st0;
st0:
cs = 0;
	goto _out;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	switch( (*p) ) {
		case 34: goto tr13;
		case 92: goto tr14;
	}
	goto tr12;
tr12:
	{
                        s = p;
                        needsUnescape = false;
                }
	goto st3;
tr18:
	{
                        needsUnescape = true;
                }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	switch( (*p) ) {
		case 34: goto tr16;
		case 92: goto st4;
	}
	goto st3;
tr7:
	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","startArray: %s", name.c_str());
                        }
                        startArray(name);
                        {
					stack.resize(top + 1);
				{stack[top++] = 71; goto st43;}}
                }
	goto st71;
tr11:
	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","startObject: %s", name.c_str());
                        }
                        startObject(name);
                        {
					stack.resize(top + 1);
				{stack[top++] = 71; goto st9;}}
                }
	goto st71;
tr13:
	{
                        s = p;
                        needsUnescape = false;
                }
	{
                        std::string value(s, p-s);
                        s = p;
                        if (needsUnescape) value = unescape(value);
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug)gdx_log_debug("JsonReader","string: %s = %s", name.c_str(), value.c_str());;
                        string(name, value);
                }
	goto st71;
tr16:
	{
                        std::string value(s, p-s);
                        s = p;
                        if (needsUnescape) value = unescape(value);
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug)gdx_log_debug("JsonReader","string: %s = %s", name.c_str(), value.c_str());;
                        string(name, value);
                }
	goto st71;
tr145:
	{
                        std::string value(s, p-s);
                        s = p;
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }
                        if (debug)gdx_log_debug("JsonReader","number: %s = %s", name.c_str(), value.c_str());

                        if (value.find(".") != std::string::npos) {
                            number(name, from_string<float>(value));
                        } else {
                            number(name, from_string<int>(value));
                        }
                }
	goto st71;
tr152:
	{
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = false", name.c_str());
                        }
                        boolean(name, false);
                }
	goto st71;
tr156:
	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","nulll: %s", name.c_str());
                        }
                        
                        null(name);
                }
	goto st71;
tr160:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = true", name.c_str());
                        }
                        boolean(name, true);
                }
	goto st71;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:

	if ( (*p) == 32 )
		goto st71;
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st71;
	goto st0;
tr14:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:

	switch( (*p) ) {
		case 34: goto tr18;
		case 47: goto tr18;
		case 92: goto tr18;
		case 98: goto tr18;
		case 102: goto tr18;
		case 110: goto tr18;
		case 114: goto tr18;
	}
	if ( 116 <= (*p) && (*p) <= 117 )
		goto tr18;
	goto st0;
tr3:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st72;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:

	switch( (*p) ) {
		case 32: goto tr16;
		case 44: goto st0;
		case 58: goto st0;
		case 93: goto st0;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr16;
	goto st72;
tr4:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:

	if ( (*p) == 48 )
		goto st73;
	if ( 49 <= (*p) && (*p) <= 57 )
		goto st76;
	goto st0;
tr5:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st73;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:

	switch( (*p) ) {
		case 32: goto tr145;
		case 46: goto st6;
		case 69: goto st7;
		case 101: goto st7;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr145;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st74;
	goto st0;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	switch( (*p) ) {
		case 32: goto tr145;
		case 69: goto st7;
		case 101: goto st7;
	}
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st74;
	} else if ( (*p) >= 9 )
		goto tr145;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	switch( (*p) ) {
		case 43: goto st8;
		case 45: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st75;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st75;
	goto st0;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	if ( (*p) == 32 )
		goto tr145;
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st75;
	} else if ( (*p) >= 9 )
		goto tr145;
	goto st0;
tr6:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st76;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:

	switch( (*p) ) {
		case 32: goto tr145;
		case 46: goto st6;
		case 69: goto st7;
		case 101: goto st7;
	}
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st76;
	} else if ( (*p) >= 9 )
		goto tr145;
	goto st0;
tr8:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st77;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:

	switch( (*p) ) {
		case 32: goto tr16;
		case 44: goto st0;
		case 58: goto st0;
		case 93: goto st0;
		case 97: goto st78;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr16;
	goto st72;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	switch( (*p) ) {
		case 32: goto tr16;
		case 44: goto st0;
		case 58: goto st0;
		case 93: goto st0;
		case 108: goto st79;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr16;
	goto st72;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	switch( (*p) ) {
		case 32: goto tr16;
		case 44: goto st0;
		case 58: goto st0;
		case 93: goto st0;
		case 115: goto st80;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr16;
	goto st72;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	switch( (*p) ) {
		case 32: goto tr16;
		case 44: goto st0;
		case 58: goto st0;
		case 93: goto st0;
		case 101: goto st81;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr16;
	goto st72;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	if ( (*p) == 32 )
		goto tr152;
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr152;
	goto st0;
tr9:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st82;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:

	switch( (*p) ) {
		case 32: goto tr16;
		case 44: goto st0;
		case 58: goto st0;
		case 93: goto st0;
		case 117: goto st83;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr16;
	goto st72;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	switch( (*p) ) {
		case 32: goto tr16;
		case 44: goto st0;
		case 58: goto st0;
		case 93: goto st0;
		case 108: goto st84;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr16;
	goto st72;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	switch( (*p) ) {
		case 32: goto tr16;
		case 44: goto st0;
		case 58: goto st0;
		case 93: goto st0;
		case 108: goto st85;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr16;
	goto st72;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	if ( (*p) == 32 )
		goto tr156;
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr156;
	goto st0;
tr10:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st86;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:

	switch( (*p) ) {
		case 32: goto tr16;
		case 44: goto st0;
		case 58: goto st0;
		case 93: goto st0;
		case 114: goto st87;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr16;
	goto st72;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	switch( (*p) ) {
		case 32: goto tr16;
		case 44: goto st0;
		case 58: goto st0;
		case 93: goto st0;
		case 117: goto st88;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr16;
	goto st72;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	switch( (*p) ) {
		case 32: goto tr16;
		case 44: goto st0;
		case 58: goto st0;
		case 93: goto st0;
		case 101: goto st89;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr16;
	goto st72;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
	if ( (*p) == 32 )
		goto tr160;
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr160;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	switch( (*p) ) {
		case 32: goto st9;
		case 34: goto st10;
		case 36: goto tr26;
		case 44: goto st17;
		case 95: goto tr26;
		case 125: goto tr28;
	}
	if ( (*p) < 65 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto st9;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr26;
	} else
		goto tr26;
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	switch( (*p) ) {
		case 34: goto tr30;
		case 92: goto tr31;
	}
	goto tr29;
tr29:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st11;
tr89:

	{
                        needsUnescape = true;
                }
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:

	switch( (*p) ) {
		case 34: goto tr33;
		case 92: goto st42;
	}
	goto st11;
tr30:

	{
                        s = p;
                        needsUnescape = false;
                }

	{
                        std::string name(s, p-s);
                        s = p;
                        if (needsUnescape) name = unescape(name);
                        if (debug)gdx_log_debug("JsonReader","name: %s", name.c_str());
                        names.push_back(name);
                }
	goto st12;
tr33:

	{
                        std::string name(s, p-s);
                        s = p;
                        if (needsUnescape) name = unescape(name);
                        if (debug)gdx_log_debug("JsonReader","name: %s", name.c_str());
                        names.push_back(name);
                }
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:

	switch( (*p) ) {
		case 32: goto st12;
		case 58: goto st13;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st12;
	goto st0;
tr55:

	{
                        std::string name(s, p-s);
                        s = p;
                        if (needsUnescape) name = unescape(name);
                        if (debug)gdx_log_debug("JsonReader","name: %s", name.c_str());
                        names.push_back(name);
                }
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:

	switch( (*p) ) {
		case 32: goto st13;
		case 34: goto st14;
		case 36: goto tr38;
		case 45: goto tr39;
		case 48: goto tr40;
		case 91: goto tr42;
		case 95: goto tr38;
		case 102: goto tr43;
		case 110: goto tr44;
		case 116: goto tr45;
		case 123: goto tr46;
	}
	if ( (*p) < 49 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto st13;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr38;
		} else if ( (*p) >= 65 )
			goto tr38;
	} else
		goto tr41;
	goto st0;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	switch( (*p) ) {
		case 34: goto tr48;
		case 92: goto tr49;
	}
	goto tr47;
tr47:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st15;
tr56:

	{
                        needsUnescape = true;
                }
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:

	switch( (*p) ) {
		case 34: goto tr51;
		case 92: goto st19;
	}
	goto st15;
tr42:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","startArray: %s", name.c_str());
                        }
                        startArray(name);
                        {
					stack.resize(top + 1);
				{stack[top++] = 16; goto st43;}}
                }
	goto st16;
tr46:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","startObject: %s", name.c_str());
                        }
                        startObject(name);
                        {
					stack.resize(top + 1);
				{stack[top++] = 16; goto st9;}}
                }
	goto st16;
tr48:

	{
                        s = p;
                        needsUnescape = false;
                }

	{
                        std::string value(s, p-s);
                        s = p;
                        if (needsUnescape) value = unescape(value);
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug)gdx_log_debug("JsonReader","string: %s = %s", name.c_str(), value.c_str());;
                        string(name, value);
                }
	goto st16;
tr51:

	{
                        std::string value(s, p-s);
                        s = p;
                        if (needsUnescape) value = unescape(value);
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug)gdx_log_debug("JsonReader","string: %s = %s", name.c_str(), value.c_str());;
                        string(name, value);
                }
	goto st16;
tr62:

	{
                        std::string value(s, p-s);
                        s = p;
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }
                        if (debug)gdx_log_debug("JsonReader","number: %s = %s", name.c_str(), value.c_str());

                        if (value.find(".") != std::string::npos) {
                            number(name, from_string<float>(value));
                        } else {
                            number(name, from_string<int>(value));
                        }
                }
	goto st16;
tr74:

	{
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = false", name.c_str());
                        }
                        boolean(name, false);
                }
	goto st16;
tr80:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","nulll: %s", name.c_str());
                        }
                        
                        null(name);
                }
	goto st16;
tr86:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = true", name.c_str());
                        }
                        boolean(name, true);
                }
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:

	switch( (*p) ) {
		case 32: goto st16;
		case 44: goto st17;
		case 125: goto tr28;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st16;
	goto st0;
tr58:

	{
                        std::string value(s, p-s);
                        s = p;
                        if (needsUnescape) value = unescape(value);
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug)gdx_log_debug("JsonReader","string: %s = %s", name.c_str(), value.c_str());;
                        string(name, value);
                }
	goto st17;
tr63:

	{
                        std::string value(s, p-s);
                        s = p;
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }
                        if (debug)gdx_log_debug("JsonReader","number: %s = %s", name.c_str(), value.c_str());

                        if (value.find(".") != std::string::npos) {
                            number(name, from_string<float>(value));
                        } else {
                            number(name, from_string<int>(value));
                        }
                }
	goto st17;
tr75:

	{
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = false", name.c_str());
                        }
                        boolean(name, false);
                }
	goto st17;
tr81:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","nulll: %s", name.c_str());
                        }
                        
                        null(name);
                }
	goto st17;
tr87:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = true", name.c_str());
                        }
                        boolean(name, true);
                }
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:

	switch( (*p) ) {
		case 32: goto st17;
		case 34: goto st10;
		case 36: goto tr26;
		case 95: goto tr26;
		case 125: goto tr28;
	}
	if ( (*p) < 65 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto st17;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr26;
	} else
		goto tr26;
	goto st0;
tr26:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:

	switch( (*p) ) {
		case 32: goto tr33;
		case 44: goto st0;
		case 58: goto tr55;
		case 93: goto st0;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr33;
	goto st18;
tr28:

	{
                        if (debug) {
                           gdx_log_debug("JsonReader","endObject");
                        }
                        pop();
                        {cs = stack[--top];goto _again;}
                }
	goto st90;
tr59:

	{
                        std::string value(s, p-s);
                        s = p;
                        if (needsUnescape) value = unescape(value);
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug)gdx_log_debug("JsonReader","string: %s = %s", name.c_str(), value.c_str());;
                        string(name, value);
                }

	{
                        if (debug) {
                           gdx_log_debug("JsonReader","endObject");
                        }
                        pop();
                        {cs = stack[--top];goto _again;}
                }
	goto st90;
tr66:

	{
                        std::string value(s, p-s);
                        s = p;
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }
                        if (debug)gdx_log_debug("JsonReader","number: %s = %s", name.c_str(), value.c_str());

                        if (value.find(".") != std::string::npos) {
                            number(name, from_string<float>(value));
                        } else {
                            number(name, from_string<int>(value));
                        }
                }

	{
                        if (debug) {
                           gdx_log_debug("JsonReader","endObject");
                        }
                        pop();
                        {cs = stack[--top];goto _again;}
                }
	goto st90;
tr76:

	{
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = false", name.c_str());
                        }
                        boolean(name, false);
                }

	{
                        if (debug) {
                           gdx_log_debug("JsonReader","endObject");
                        }
                        pop();
                        {cs = stack[--top];goto _again;}
                }
	goto st90;
tr82:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","nulll: %s", name.c_str());
                        }
                        
                        null(name);
                }

	{
                        if (debug) {
                           gdx_log_debug("JsonReader","endObject");
                        }
                        pop();
                        {cs = stack[--top];goto _again;}
                }
	goto st90;
tr88:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = true", name.c_str());
                        }
                        boolean(name, true);
                }

	{
                        if (debug) {
                           gdx_log_debug("JsonReader","endObject");
                        }
                        pop();
                        {cs = stack[--top];goto _again;}
                }
	goto st90;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:

	goto st0;
tr49:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:

	switch( (*p) ) {
		case 34: goto tr56;
		case 47: goto tr56;
		case 92: goto tr56;
		case 98: goto tr56;
		case 102: goto tr56;
		case 110: goto tr56;
		case 114: goto tr56;
	}
	if ( 116 <= (*p) && (*p) <= 117 )
		goto tr56;
	goto st0;
tr38:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:

	switch( (*p) ) {
		case 32: goto tr51;
		case 44: goto tr58;
		case 58: goto st0;
		case 93: goto st0;
		case 125: goto tr59;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr51;
	goto st20;
tr39:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:

	if ( (*p) == 48 )
		goto st22;
	if ( 49 <= (*p) && (*p) <= 57 )
		goto st28;
	goto st0;
tr40:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st22;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:

	switch( (*p) ) {
		case 32: goto tr62;
		case 44: goto tr63;
		case 46: goto st23;
		case 69: goto st25;
		case 101: goto st25;
		case 125: goto tr66;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr62;
	goto st0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st24;
	goto st0;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	switch( (*p) ) {
		case 32: goto tr62;
		case 44: goto tr63;
		case 69: goto st25;
		case 101: goto st25;
		case 125: goto tr66;
	}
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st24;
	} else if ( (*p) >= 9 )
		goto tr62;
	goto st0;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	switch( (*p) ) {
		case 43: goto st26;
		case 45: goto st26;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st27;
	goto st0;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st27;
	goto st0;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 32: goto tr62;
		case 44: goto tr63;
		case 125: goto tr66;
	}
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st27;
	} else if ( (*p) >= 9 )
		goto tr62;
	goto st0;
tr41:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st28;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:

	switch( (*p) ) {
		case 32: goto tr62;
		case 44: goto tr63;
		case 46: goto st23;
		case 69: goto st25;
		case 101: goto st25;
		case 125: goto tr66;
	}
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st28;
	} else if ( (*p) >= 9 )
		goto tr62;
	goto st0;
tr43:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st29;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:

	switch( (*p) ) {
		case 32: goto tr51;
		case 44: goto tr58;
		case 58: goto st0;
		case 93: goto st0;
		case 97: goto st30;
		case 125: goto tr59;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr51;
	goto st20;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 32: goto tr51;
		case 44: goto tr58;
		case 58: goto st0;
		case 93: goto st0;
		case 108: goto st31;
		case 125: goto tr59;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr51;
	goto st20;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 32: goto tr51;
		case 44: goto tr58;
		case 58: goto st0;
		case 93: goto st0;
		case 115: goto st32;
		case 125: goto tr59;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr51;
	goto st20;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 32: goto tr51;
		case 44: goto tr58;
		case 58: goto st0;
		case 93: goto st0;
		case 101: goto st33;
		case 125: goto tr59;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr51;
	goto st20;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 32: goto tr74;
		case 44: goto tr75;
		case 125: goto tr76;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr74;
	goto st0;
tr44:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st34;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:

	switch( (*p) ) {
		case 32: goto tr51;
		case 44: goto tr58;
		case 58: goto st0;
		case 93: goto st0;
		case 117: goto st35;
		case 125: goto tr59;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr51;
	goto st20;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	switch( (*p) ) {
		case 32: goto tr51;
		case 44: goto tr58;
		case 58: goto st0;
		case 93: goto st0;
		case 108: goto st36;
		case 125: goto tr59;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr51;
	goto st20;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	switch( (*p) ) {
		case 32: goto tr51;
		case 44: goto tr58;
		case 58: goto st0;
		case 93: goto st0;
		case 108: goto st37;
		case 125: goto tr59;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr51;
	goto st20;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 32: goto tr80;
		case 44: goto tr81;
		case 125: goto tr82;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr80;
	goto st0;
tr45:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st38;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:

	switch( (*p) ) {
		case 32: goto tr51;
		case 44: goto tr58;
		case 58: goto st0;
		case 93: goto st0;
		case 114: goto st39;
		case 125: goto tr59;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr51;
	goto st20;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	switch( (*p) ) {
		case 32: goto tr51;
		case 44: goto tr58;
		case 58: goto st0;
		case 93: goto st0;
		case 117: goto st40;
		case 125: goto tr59;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr51;
	goto st20;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 32: goto tr51;
		case 44: goto tr58;
		case 58: goto st0;
		case 93: goto st0;
		case 101: goto st41;
		case 125: goto tr59;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr51;
	goto st20;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 32: goto tr86;
		case 44: goto tr87;
		case 125: goto tr88;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr86;
	goto st0;
tr31:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st42;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:

	switch( (*p) ) {
		case 34: goto tr89;
		case 47: goto tr89;
		case 92: goto tr89;
		case 98: goto tr89;
		case 102: goto tr89;
		case 110: goto tr89;
		case 114: goto tr89;
	}
	if ( 116 <= (*p) && (*p) <= 117 )
		goto tr89;
	goto st0;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	switch( (*p) ) {
		case 32: goto st43;
		case 34: goto st44;
		case 36: goto tr92;
		case 44: goto st47;
		case 45: goto tr94;
		case 48: goto tr95;
		case 91: goto tr97;
		case 93: goto tr98;
		case 95: goto tr92;
		case 102: goto tr99;
		case 110: goto tr100;
		case 116: goto tr101;
		case 123: goto tr102;
	}
	if ( (*p) < 49 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto st43;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr92;
		} else if ( (*p) >= 65 )
			goto tr92;
	} else
		goto tr96;
	goto st0;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	switch( (*p) ) {
		case 34: goto tr104;
		case 92: goto tr105;
	}
	goto tr103;
tr103:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st45;
tr142:

	{
                        needsUnescape = true;
                }
	goto st45;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:

	switch( (*p) ) {
		case 34: goto tr107;
		case 92: goto st70;
	}
	goto st45;
tr97:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","startArray: %s", name.c_str());
                        }
                        startArray(name);
                        {
					stack.resize(top + 1);
				{stack[top++] = 46; goto st43;}}
                }
	goto st46;
tr102:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","startObject: %s", name.c_str());
                        }
                        startObject(name);
                        {
					stack.resize(top + 1);
				{stack[top++] = 46; goto st9;}}
                }
	goto st46;
tr104:

	{
                        s = p;
                        needsUnescape = false;
                }

	{
                        std::string value(s, p-s);
                        s = p;
                        if (needsUnescape) value = unescape(value);
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug)gdx_log_debug("JsonReader","string: %s = %s", name.c_str(), value.c_str());;
                        string(name, value);
                }
	goto st46;
tr107:

	{
                        std::string value(s, p-s);
                        s = p;
                        if (needsUnescape) value = unescape(value);
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug)gdx_log_debug("JsonReader","string: %s = %s", name.c_str(), value.c_str());;
                        string(name, value);
                }
	goto st46;
tr115:

	{
                        std::string value(s, p-s);
                        s = p;
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }
                        if (debug)gdx_log_debug("JsonReader","number: %s = %s", name.c_str(), value.c_str());

                        if (value.find(".") != std::string::npos) {
                            number(name, from_string<float>(value));
                        } else {
                            number(name, from_string<int>(value));
                        }
                }
	goto st46;
tr127:

	{
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = false", name.c_str());
                        }
                        boolean(name, false);
                }
	goto st46;
tr133:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","nulll: %s", name.c_str());
                        }
                        
                        null(name);
                }
	goto st46;
tr139:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = true", name.c_str());
                        }
                        boolean(name, true);
                }
	goto st46;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:

	switch( (*p) ) {
		case 32: goto st46;
		case 44: goto st47;
		case 93: goto tr98;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st46;
	goto st0;
tr111:

	{
                        std::string value(s, p-s);
                        s = p;
                        if (needsUnescape) value = unescape(value);
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug)gdx_log_debug("JsonReader","string: %s = %s", name.c_str(), value.c_str());;
                        string(name, value);
                }
	goto st47;
tr116:

	{
                        std::string value(s, p-s);
                        s = p;
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }
                        if (debug)gdx_log_debug("JsonReader","number: %s = %s", name.c_str(), value.c_str());

                        if (value.find(".") != std::string::npos) {
                            number(name, from_string<float>(value));
                        } else {
                            number(name, from_string<int>(value));
                        }
                }
	goto st47;
tr128:

	{
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = false", name.c_str());
                        }
                        boolean(name, false);
                }
	goto st47;
tr134:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","nulll: %s", name.c_str());
                        }
                        
                        null(name);
                }
	goto st47;
tr140:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = true", name.c_str());
                        }
                        boolean(name, true);
                }
	goto st47;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:

	switch( (*p) ) {
		case 32: goto st47;
		case 34: goto st44;
		case 36: goto tr92;
		case 45: goto tr94;
		case 48: goto tr95;
		case 91: goto tr97;
		case 93: goto tr98;
		case 95: goto tr92;
		case 102: goto tr99;
		case 110: goto tr100;
		case 116: goto tr101;
		case 123: goto tr102;
	}
	if ( (*p) < 49 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto st47;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr92;
		} else if ( (*p) >= 65 )
			goto tr92;
	} else
		goto tr96;
	goto st0;
tr92:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st48;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:

	switch( (*p) ) {
		case 32: goto tr107;
		case 44: goto tr111;
		case 58: goto st0;
		case 93: goto tr112;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr107;
	goto st48;
tr98:

	{
                        if (debug) {
                           gdx_log_debug("JsonReader","endArray");
                        }
                        pop();
                        {cs = stack[--top];goto _again;}
                }
	goto st91;
tr112:

	{
                        std::string value(s, p-s);
                        s = p;
                        if (needsUnescape) value = unescape(value);
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug)gdx_log_debug("JsonReader","string: %s = %s", name.c_str(), value.c_str());;
                        string(name, value);
                }

	{
                        if (debug) {
                           gdx_log_debug("JsonReader","endArray");
                        }
                        pop();
                        {cs = stack[--top];goto _again;}
                }
	goto st91;
tr119:

	{
                        std::string value(s, p-s);
                        s = p;
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }
                        if (debug)gdx_log_debug("JsonReader","number: %s = %s", name.c_str(), value.c_str());

                        if (value.find(".") != std::string::npos) {
                            number(name, from_string<float>(value));
                        } else {
                            number(name, from_string<int>(value));
                        }
                }

	{
                        if (debug) {
                           gdx_log_debug("JsonReader","endArray");
                        }
                        pop();
                        {cs = stack[--top];goto _again;}
                }
	goto st91;
tr129:

	{
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = false", name.c_str());
                        }
                        boolean(name, false);
                }

	{
                        if (debug) {
                           gdx_log_debug("JsonReader","endArray");
                        }
                        pop();
                        {cs = stack[--top];goto _again;}
                }
	goto st91;
tr135:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","nulll: %s", name.c_str());
                        }
                        
                        null(name);
                }

	{
                        if (debug) {
                           gdx_log_debug("JsonReader","endArray");
                        }
                        pop();
                        {cs = stack[--top];goto _again;}
                }
	goto st91;
tr141:

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = true", name.c_str());
                        }
                        boolean(name, true);
                }

	{
                        if (debug) {
                           gdx_log_debug("JsonReader","endArray");
                        }
                        pop();
                        {cs = stack[--top];goto _again;}
                }
	goto st91;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:

	goto st0;
tr94:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st49;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:

	if ( (*p) == 48 )
		goto st50;
	if ( 49 <= (*p) && (*p) <= 57 )
		goto st56;
	goto st0;
tr95:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st50;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:

	switch( (*p) ) {
		case 32: goto tr115;
		case 44: goto tr116;
		case 46: goto st51;
		case 69: goto st53;
		case 93: goto tr119;
		case 101: goto st53;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr115;
	goto st0;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st52;
	goto st0;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	switch( (*p) ) {
		case 32: goto tr115;
		case 44: goto tr116;
		case 69: goto st53;
		case 93: goto tr119;
		case 101: goto st53;
	}
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st52;
	} else if ( (*p) >= 9 )
		goto tr115;
	goto st0;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	switch( (*p) ) {
		case 43: goto st54;
		case 45: goto st54;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st55;
	goto st0;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st55;
	goto st0;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	switch( (*p) ) {
		case 32: goto tr115;
		case 44: goto tr116;
		case 93: goto tr119;
	}
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st55;
	} else if ( (*p) >= 9 )
		goto tr115;
	goto st0;
tr96:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st56;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:

	switch( (*p) ) {
		case 32: goto tr115;
		case 44: goto tr116;
		case 46: goto st51;
		case 69: goto st53;
		case 93: goto tr119;
		case 101: goto st53;
	}
	if ( (*p) > 13 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st56;
	} else if ( (*p) >= 9 )
		goto tr115;
	goto st0;
tr99:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st57;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:

	switch( (*p) ) {
		case 32: goto tr107;
		case 44: goto tr111;
		case 58: goto st0;
		case 93: goto tr112;
		case 97: goto st58;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr107;
	goto st48;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	switch( (*p) ) {
		case 32: goto tr107;
		case 44: goto tr111;
		case 58: goto st0;
		case 93: goto tr112;
		case 108: goto st59;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr107;
	goto st48;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 32: goto tr107;
		case 44: goto tr111;
		case 58: goto st0;
		case 93: goto tr112;
		case 115: goto st60;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr107;
	goto st48;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	switch( (*p) ) {
		case 32: goto tr107;
		case 44: goto tr111;
		case 58: goto st0;
		case 93: goto tr112;
		case 101: goto st61;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr107;
	goto st48;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 32: goto tr127;
		case 44: goto tr128;
		case 93: goto tr129;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr127;
	goto st0;
tr100:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st62;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:

	switch( (*p) ) {
		case 32: goto tr107;
		case 44: goto tr111;
		case 58: goto st0;
		case 93: goto tr112;
		case 117: goto st63;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr107;
	goto st48;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	switch( (*p) ) {
		case 32: goto tr107;
		case 44: goto tr111;
		case 58: goto st0;
		case 93: goto tr112;
		case 108: goto st64;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr107;
	goto st48;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 32: goto tr107;
		case 44: goto tr111;
		case 58: goto st0;
		case 93: goto tr112;
		case 108: goto st65;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr107;
	goto st48;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 32: goto tr133;
		case 44: goto tr134;
		case 93: goto tr135;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr133;
	goto st0;
tr101:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st66;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:

	switch( (*p) ) {
		case 32: goto tr107;
		case 44: goto tr111;
		case 58: goto st0;
		case 93: goto tr112;
		case 114: goto st67;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr107;
	goto st48;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	switch( (*p) ) {
		case 32: goto tr107;
		case 44: goto tr111;
		case 58: goto st0;
		case 93: goto tr112;
		case 117: goto st68;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr107;
	goto st48;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	switch( (*p) ) {
		case 32: goto tr107;
		case 44: goto tr111;
		case 58: goto st0;
		case 93: goto tr112;
		case 101: goto st69;
		case 125: goto st0;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr107;
	goto st48;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	switch( (*p) ) {
		case 32: goto tr139;
		case 44: goto tr140;
		case 93: goto tr141;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr139;
	goto st0;
tr105:

	{
                        s = p;
                        needsUnescape = false;
                }
	goto st70;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:

	switch( (*p) ) {
		case 34: goto tr142;
		case 47: goto tr142;
		case 92: goto tr142;
		case 98: goto tr142;
		case 102: goto tr142;
		case 110: goto tr142;
		case 114: goto tr142;
	}
	if ( 116 <= (*p) && (*p) <= 117 )
		goto tr142;
	goto st0;
	}
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
	_test_eof78: cs = 78; goto _test_eof; 
	_test_eof79: cs = 79; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 
	_test_eof85: cs = 85; goto _test_eof; 
	_test_eof86: cs = 86; goto _test_eof; 
	_test_eof87: cs = 87; goto _test_eof; 
	_test_eof88: cs = 88; goto _test_eof; 
	_test_eof89: cs = 89; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof90: cs = 90; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 
	_test_eof40: cs = 40; goto _test_eof; 
	_test_eof41: cs = 41; goto _test_eof; 
	_test_eof42: cs = 42; goto _test_eof; 
	_test_eof43: cs = 43; goto _test_eof; 
	_test_eof44: cs = 44; goto _test_eof; 
	_test_eof45: cs = 45; goto _test_eof; 
	_test_eof46: cs = 46; goto _test_eof; 
	_test_eof47: cs = 47; goto _test_eof; 
	_test_eof48: cs = 48; goto _test_eof; 
	_test_eof91: cs = 91; goto _test_eof; 
	_test_eof49: cs = 49; goto _test_eof; 
	_test_eof50: cs = 50; goto _test_eof; 
	_test_eof51: cs = 51; goto _test_eof; 
	_test_eof52: cs = 52; goto _test_eof; 
	_test_eof53: cs = 53; goto _test_eof; 
	_test_eof54: cs = 54; goto _test_eof; 
	_test_eof55: cs = 55; goto _test_eof; 
	_test_eof56: cs = 56; goto _test_eof; 
	_test_eof57: cs = 57; goto _test_eof; 
	_test_eof58: cs = 58; goto _test_eof; 
	_test_eof59: cs = 59; goto _test_eof; 
	_test_eof60: cs = 60; goto _test_eof; 
	_test_eof61: cs = 61; goto _test_eof; 
	_test_eof62: cs = 62; goto _test_eof; 
	_test_eof63: cs = 63; goto _test_eof; 
	_test_eof64: cs = 64; goto _test_eof; 
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 72: 
	case 77: 
	case 78: 
	case 79: 
	case 80: 
	case 82: 
	case 83: 
	case 84: 
	case 86: 
	case 87: 
	case 88: 

	{
                        std::string value(s, p-s);
                        s = p;
                        if (needsUnescape) value = unescape(value);
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug)gdx_log_debug("JsonReader","string: %s = %s", name.c_str(), value.c_str());;
                        string(name, value);
                }
	break;
	case 73: 
	case 74: 
	case 75: 
	case 76: 

	{
                        std::string value(s, p-s);
                        s = p;
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }
                        if (debug)gdx_log_debug("JsonReader","number: %s = %s", name.c_str(), value.c_str());

                        if (value.find(".") != std::string::npos) {
                            number(name, from_string<float>(value));
                        } else {
                            number(name, from_string<int>(value));
                        }
                }
	break;
	case 89: 

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = true", name.c_str());
                        }
                        boolean(name, true);
                }
	break;
	case 81: 

	{
                        std::string name;
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","number: %s = false", name.c_str());
                        }
                        boolean(name, false);
                }
	break;
	case 85: 

	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","nulll: %s", name.c_str());
                        }
                        
                        null(name);
                }
	break;

	}
	}

	_out: {}
	}




    } catch (std::runtime_error& ex) {

    }

    if (p < pe) {
        
        int lineNumber = 1;
        for (char* aux = p; aux < pe; aux++)
            if (*aux == '\n') lineNumber++;
        gdx_log_error("gdx","Error parsing JSON on line %d near: %s", lineNumber, std::string(p, pe - p).c_str());
    } else if (elements.size() != 0) {
        int element_type = elements.front()->getType();

        elements.clear();

        if (element_type == JsonValue::json_json) {
            gdx_log_error("gdx","Error parsing JSON, unmatched brace.");
        }
        else {
            gdx_log_error("gdx","Error parsing JSON, unmatched bracket.");
        }
    }

    return root;
}
void JsonReader::startObject (const std::string& name) {
    if (current) {
        elements.push_back(set(name, JsonValue::item_map()));        
    } else {
        root = JsonValue::item_map();
        elements.push_back(&root);
    }

    current = elements.back();
}

void JsonReader::startArray (const std::string& name) {
    if (current) {        
        elements.push_back(set(name, JsonValue::array()));
    } else {
        root = JsonValue::array();
        elements.push_back(&root);
    }
    
    current = elements.back();
}

void JsonReader::pop () {
    elements.pop_back();
    current = elements.size() > 0 ? elements.back() : &root;
}

void JsonReader::string (const std::string& name,const std::string& value) {
    set(name, value);
}

void JsonReader::number (const std::string& name, float value) {
    set(name, value);
}

void JsonReader::boolean (const std::string& name, bool value) {
    set(name, value);
}

void JsonReader::number(const std::string& name, int value)
{
    set(name, value);
}

void JsonReader::null(const std::string& name)
{
    set(name, JsonValue());
}

std::string JsonReader::unescape (const std::string& value) {
    int length = value.length();
    std::stringstream buffer;
    for (int i = 0; i < length;) {
        char c = value[i++];
        if (c != '\\') {
            buffer << c;
            continue;
        }
        if (i == length) break;
        c = value[i++];
        if (c == 'u') {
            char result[5] = { 0, 0, 0, 0 ,0 };
            
            int codepoint = strtol(value.substr(i, 4).c_str(), nullptr, 16);            
            
            if (codepoint <= 0x7f) {
                result[0] = static_cast<char>(codepoint);
            } else if (codepoint <= 0x7FF) {
                result[1] = static_cast<char>(0x80 | (0x3f & codepoint));
                result[0] = static_cast<char>(0xC0 | (codepoint >> 6));
            } else if (codepoint <= 0xFFFF) {
                result[2] = static_cast<char>(0x80 | (0x3f & codepoint));
                result[1] = (0x80 | static_cast<char>((0x3f & (codepoint >> 6))));
                result[0] = (0xE0 | static_cast<char>(codepoint >> 12));
            } else if (codepoint <= 0x10FFFF) {
                result[3] = static_cast<char>(0x80 | (0x3f & codepoint));
                result[2] = static_cast<char>(0x80 | (0x3f & (codepoint >> 6)));
                result[1] = static_cast<char>(0x80 | (0x3f & (codepoint >> 12)));
                result[0] = static_cast<char>(0xF0 | (codepoint >> 18));
            }
                                    
            buffer << result;
            i += 4;
            continue;
        }
        switch (c) {
        case '"':
        case '\\':
        case '/':
            break;
        case 'b':
            c = '\b';
            break;
        case 'f':
            c = '\f';
            break;
        case 'n':
            c = '\n';
            break;
        case 'r':
            c = '\r';
            break;
        case 't':
            c = '\t';
            break;
        default:
            gdx_log_error("gdx","Illegal escaped character: %c" , c);
        }

        buffer << c;
    }
    return buffer.str();
}

JsonValue* JsonReader::set(const std::string& name, const JsonValue& value)
{
    if (current->getType() == gdx::JsonValue::json_list) {
        (*current).as_array().push_back(value);
        return &(*current).as_array().back();
    } else if (current->getType() == gdx::JsonValue::json_json) {
        (*current)[name] = value;
        return &(*current)[name];
    } else {
        (*current) = value;
        return current;
    }
}
