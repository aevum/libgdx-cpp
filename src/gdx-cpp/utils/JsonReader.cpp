
/* #line 1 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */

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


/* #line 36 "JsonReader.cpp" */
static const char _json_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	11, 2, 0, 2, 2, 0, 3, 2, 
	3, 9, 2, 3, 11, 2, 4, 9, 
	2, 4, 11, 2, 5, 9, 2, 5, 
	11, 2, 6, 9, 2, 6, 11, 2, 
	7, 9, 2, 7, 11
};

static const short _json_key_offsets[] = {
	0, 0, 19, 21, 23, 32, 35, 37, 
	41, 43, 55, 57, 59, 63, 82, 84, 
	86, 91, 102, 109, 118, 125, 128, 136, 
	138, 147, 151, 153, 160, 170, 178, 186, 
	194, 202, 207, 215, 223, 231, 236, 244, 
	252, 260, 265, 274, 295, 297, 299, 304, 
	324, 331, 334, 342, 344, 353, 357, 359, 
	366, 376, 384, 392, 400, 408, 413, 421, 
	429, 437, 442, 450, 458, 466, 471, 480, 
	483, 490, 496, 503, 508, 516, 524, 532, 
	540, 548, 551, 559, 567, 575, 578, 586, 
	594, 602, 605, 605
};

static const char _json_trans_keys[] = {
	32, 34, 36, 45, 48, 91, 95, 102, 
	110, 116, 123, 9, 13, 49, 57, 65, 
	90, 97, 122, 34, 92, 34, 92, 34, 
	47, 92, 98, 102, 110, 114, 116, 117, 
	48, 49, 57, 48, 57, 43, 45, 48, 
	57, 48, 57, 32, 34, 36, 44, 95, 
	125, 9, 13, 65, 90, 97, 122, 34, 
	92, 34, 92, 32, 58, 9, 13, 32, 
	34, 36, 45, 48, 91, 95, 102, 110, 
	116, 123, 9, 13, 49, 57, 65, 90, 
	97, 122, 34, 92, 34, 92, 32, 44, 
	125, 9, 13, 32, 34, 36, 95, 125, 
	9, 13, 65, 90, 97, 122, 32, 44, 
	58, 93, 125, 9, 13, 34, 47, 92, 
	98, 102, 110, 114, 116, 117, 32, 44, 
	58, 93, 125, 9, 13, 48, 49, 57, 
	32, 44, 46, 69, 101, 125, 9, 13, 
	48, 57, 32, 44, 69, 101, 125, 9, 
	13, 48, 57, 43, 45, 48, 57, 48, 
	57, 32, 44, 125, 9, 13, 48, 57, 
	32, 44, 46, 69, 101, 125, 9, 13, 
	48, 57, 32, 44, 58, 93, 97, 125, 
	9, 13, 32, 44, 58, 93, 108, 125, 
	9, 13, 32, 44, 58, 93, 115, 125, 
	9, 13, 32, 44, 58, 93, 101, 125, 
	9, 13, 32, 44, 125, 9, 13, 32, 
	44, 58, 93, 117, 125, 9, 13, 32, 
	44, 58, 93, 108, 125, 9, 13, 32, 
	44, 58, 93, 108, 125, 9, 13, 32, 
	44, 125, 9, 13, 32, 44, 58, 93, 
	114, 125, 9, 13, 32, 44, 58, 93, 
	117, 125, 9, 13, 32, 44, 58, 93, 
	101, 125, 9, 13, 32, 44, 125, 9, 
	13, 34, 47, 92, 98, 102, 110, 114, 
	116, 117, 32, 34, 36, 44, 45, 48, 
	91, 93, 95, 102, 110, 116, 123, 9, 
	13, 49, 57, 65, 90, 97, 122, 34, 
	92, 34, 92, 32, 44, 93, 9, 13, 
	32, 34, 36, 45, 48, 91, 93, 95, 
	102, 110, 116, 123, 9, 13, 49, 57, 
	65, 90, 97, 122, 32, 44, 58, 93, 
	125, 9, 13, 48, 49, 57, 32, 44, 
	46, 69, 93, 101, 9, 13, 48, 57, 
	32, 44, 69, 93, 101, 9, 13, 48, 
	57, 43, 45, 48, 57, 48, 57, 32, 
	44, 93, 9, 13, 48, 57, 32, 44, 
	46, 69, 93, 101, 9, 13, 48, 57, 
	32, 44, 58, 93, 97, 125, 9, 13, 
	32, 44, 58, 93, 108, 125, 9, 13, 
	32, 44, 58, 93, 115, 125, 9, 13, 
	32, 44, 58, 93, 101, 125, 9, 13, 
	32, 44, 93, 9, 13, 32, 44, 58, 
	93, 117, 125, 9, 13, 32, 44, 58, 
	93, 108, 125, 9, 13, 32, 44, 58, 
	93, 108, 125, 9, 13, 32, 44, 93, 
	9, 13, 32, 44, 58, 93, 114, 125, 
	9, 13, 32, 44, 58, 93, 117, 125, 
	9, 13, 32, 44, 58, 93, 101, 125, 
	9, 13, 32, 44, 93, 9, 13, 34, 
	47, 92, 98, 102, 110, 114, 116, 117, 
	32, 9, 13, 32, 44, 58, 93, 125, 
	9, 13, 32, 46, 69, 101, 9, 13, 
	32, 69, 101, 9, 13, 48, 57, 32, 
	9, 13, 48, 57, 32, 46, 69, 101, 
	9, 13, 48, 57, 32, 44, 58, 93, 
	97, 125, 9, 13, 32, 44, 58, 93, 
	108, 125, 9, 13, 32, 44, 58, 93, 
	115, 125, 9, 13, 32, 44, 58, 93, 
	101, 125, 9, 13, 32, 9, 13, 32, 
	44, 58, 93, 117, 125, 9, 13, 32, 
	44, 58, 93, 108, 125, 9, 13, 32, 
	44, 58, 93, 108, 125, 9, 13, 32, 
	9, 13, 32, 44, 58, 93, 114, 125, 
	9, 13, 32, 44, 58, 93, 117, 125, 
	9, 13, 32, 44, 58, 93, 101, 125, 
	9, 13, 32, 9, 13, 0
};

static const char _json_single_lengths[] = {
	0, 11, 2, 2, 7, 1, 0, 2, 
	0, 6, 2, 2, 2, 11, 2, 2, 
	3, 5, 5, 7, 5, 1, 6, 0, 
	5, 2, 0, 3, 6, 6, 6, 6, 
	6, 3, 6, 6, 6, 3, 6, 6, 
	6, 3, 7, 13, 2, 2, 3, 12, 
	5, 1, 6, 0, 5, 2, 0, 3, 
	6, 6, 6, 6, 6, 3, 6, 6, 
	6, 3, 6, 6, 6, 3, 7, 1, 
	5, 4, 3, 1, 4, 6, 6, 6, 
	6, 1, 6, 6, 6, 1, 6, 6, 
	6, 1, 0, 0
};

static const char _json_range_lengths[] = {
	0, 4, 0, 0, 1, 1, 1, 1, 
	1, 3, 0, 0, 1, 4, 0, 0, 
	1, 3, 1, 1, 1, 1, 1, 1, 
	2, 1, 1, 2, 2, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 4, 0, 0, 1, 4, 
	1, 1, 1, 1, 2, 1, 1, 2, 
	2, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 2, 2, 2, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 0, 0
};

static const short _json_index_offsets[] = {
	0, 0, 16, 19, 22, 31, 34, 36, 
	40, 42, 52, 55, 58, 62, 78, 81, 
	84, 89, 98, 105, 114, 121, 124, 132, 
	134, 142, 146, 148, 154, 163, 171, 179, 
	187, 195, 200, 208, 216, 224, 229, 237, 
	245, 253, 258, 267, 285, 288, 291, 296, 
	313, 320, 323, 331, 333, 341, 345, 347, 
	353, 362, 370, 378, 386, 394, 399, 407, 
	415, 423, 428, 436, 444, 452, 457, 466, 
	469, 476, 482, 488, 492, 499, 507, 515, 
	523, 531, 534, 542, 550, 558, 561, 569, 
	577, 585, 588, 589
};

static const unsigned char _json_indicies[] = {
	0, 2, 3, 4, 5, 7, 3, 8, 
	9, 10, 11, 0, 6, 3, 3, 1, 
	13, 14, 12, 16, 17, 15, 18, 18, 
	18, 18, 18, 18, 18, 18, 1, 19, 
	20, 1, 21, 1, 22, 22, 23, 1, 
	23, 1, 24, 25, 26, 27, 26, 28, 
	24, 26, 26, 1, 30, 31, 29, 33, 
	34, 32, 35, 36, 35, 1, 36, 37, 
	38, 39, 40, 42, 38, 43, 44, 45, 
	46, 36, 41, 38, 38, 1, 48, 49, 
	47, 51, 52, 50, 53, 27, 28, 53, 
	1, 27, 25, 26, 26, 28, 27, 26, 
	26, 1, 33, 1, 55, 1, 1, 33, 
	54, 56, 56, 56, 56, 56, 56, 56, 
	56, 1, 51, 58, 1, 1, 59, 51, 
	57, 60, 61, 1, 62, 63, 64, 65, 
	65, 66, 62, 1, 67, 1, 62, 63, 
	65, 65, 66, 62, 67, 1, 68, 68, 
	69, 1, 69, 1, 62, 63, 66, 62, 
	69, 1, 62, 63, 64, 65, 65, 66, 
	62, 61, 1, 51, 58, 1, 1, 70, 
	59, 51, 57, 51, 58, 1, 1, 71, 
	59, 51, 57, 51, 58, 1, 1, 72, 
	59, 51, 57, 51, 58, 1, 1, 73, 
	59, 51, 57, 74, 75, 76, 74, 1, 
	51, 58, 1, 1, 77, 59, 51, 57, 
	51, 58, 1, 1, 78, 59, 51, 57, 
	51, 58, 1, 1, 79, 59, 51, 57, 
	80, 81, 82, 80, 1, 51, 58, 1, 
	1, 83, 59, 51, 57, 51, 58, 1, 
	1, 84, 59, 51, 57, 51, 58, 1, 
	1, 85, 59, 51, 57, 86, 87, 88, 
	86, 1, 89, 89, 89, 89, 89, 89, 
	89, 89, 1, 90, 91, 92, 93, 94, 
	95, 97, 98, 92, 99, 100, 101, 102, 
	90, 96, 92, 92, 1, 104, 105, 103, 
	107, 108, 106, 109, 93, 98, 109, 1, 
	93, 91, 92, 94, 95, 97, 98, 92, 
	99, 100, 101, 102, 93, 96, 92, 92, 
	1, 107, 111, 1, 112, 1, 107, 110, 
	113, 114, 1, 115, 116, 117, 118, 119, 
	118, 115, 1, 120, 1, 115, 116, 118, 
	119, 118, 115, 120, 1, 121, 121, 122, 
	1, 122, 1, 115, 116, 119, 115, 122, 
	1, 115, 116, 117, 118, 119, 118, 115, 
	114, 1, 107, 111, 1, 112, 123, 1, 
	107, 110, 107, 111, 1, 112, 124, 1, 
	107, 110, 107, 111, 1, 112, 125, 1, 
	107, 110, 107, 111, 1, 112, 126, 1, 
	107, 110, 127, 128, 129, 127, 1, 107, 
	111, 1, 112, 130, 1, 107, 110, 107, 
	111, 1, 112, 131, 1, 107, 110, 107, 
	111, 1, 112, 132, 1, 107, 110, 133, 
	134, 135, 133, 1, 107, 111, 1, 112, 
	136, 1, 107, 110, 107, 111, 1, 112, 
	137, 1, 107, 110, 107, 111, 1, 112, 
	138, 1, 107, 110, 139, 140, 141, 139, 
	1, 142, 142, 142, 142, 142, 142, 142, 
	142, 1, 143, 143, 1, 16, 1, 1, 
	1, 1, 16, 144, 145, 146, 147, 147, 
	145, 1, 145, 147, 147, 145, 21, 1, 
	145, 145, 23, 1, 145, 146, 147, 147, 
	145, 20, 1, 16, 1, 1, 1, 148, 
	1, 16, 144, 16, 1, 1, 1, 149, 
	1, 16, 144, 16, 1, 1, 1, 150, 
	1, 16, 144, 16, 1, 1, 1, 151, 
	1, 16, 144, 152, 152, 1, 16, 1, 
	1, 1, 153, 1, 16, 144, 16, 1, 
	1, 1, 154, 1, 16, 144, 16, 1, 
	1, 1, 155, 1, 16, 144, 156, 156, 
	1, 16, 1, 1, 1, 157, 1, 16, 
	144, 16, 1, 1, 1, 158, 1, 16, 
	144, 16, 1, 1, 1, 159, 1, 16, 
	144, 160, 160, 1, 1, 1, 0
};

static const char _json_trans_targs[] = {
	1, 0, 2, 72, 5, 73, 76, 71, 
	77, 82, 86, 71, 3, 71, 4, 3, 
	71, 4, 3, 73, 76, 74, 8, 75, 
	9, 10, 18, 17, 90, 11, 12, 42, 
	11, 12, 42, 12, 13, 14, 20, 21, 
	22, 28, 16, 29, 34, 38, 16, 15, 
	16, 19, 15, 16, 19, 16, 18, 13, 
	15, 20, 17, 90, 22, 28, 16, 17, 
	23, 25, 90, 24, 26, 27, 30, 31, 
	32, 33, 16, 17, 90, 35, 36, 37, 
	16, 17, 90, 39, 40, 41, 16, 17, 
	90, 11, 43, 44, 48, 47, 49, 50, 
	56, 46, 91, 57, 62, 66, 46, 45, 
	46, 70, 45, 46, 70, 46, 48, 47, 
	91, 50, 56, 46, 47, 51, 53, 91, 
	52, 54, 55, 58, 59, 60, 61, 46, 
	47, 91, 63, 64, 65, 46, 47, 91, 
	67, 68, 69, 46, 47, 91, 45, 71, 
	72, 71, 6, 7, 78, 79, 80, 81, 
	71, 83, 84, 85, 71, 87, 88, 89, 
	71
};

static const char _json_trans_actions[] = {
	0, 0, 0, 1, 1, 1, 1, 21, 
	1, 1, 1, 17, 1, 28, 1, 0, 
	7, 0, 3, 0, 0, 0, 0, 0, 
	0, 0, 1, 0, 19, 1, 25, 1, 
	0, 5, 0, 0, 0, 0, 1, 1, 
	1, 1, 21, 1, 1, 1, 17, 1, 
	28, 1, 0, 7, 0, 0, 0, 5, 
	3, 0, 7, 31, 0, 0, 9, 9, 
	0, 0, 37, 0, 0, 0, 0, 0, 
	0, 0, 13, 13, 49, 0, 0, 0, 
	15, 15, 55, 0, 0, 0, 11, 11, 
	43, 3, 0, 0, 1, 0, 1, 1, 
	1, 21, 23, 1, 1, 1, 17, 1, 
	28, 1, 0, 7, 0, 0, 0, 7, 
	34, 0, 0, 9, 9, 0, 0, 40, 
	0, 0, 0, 0, 0, 0, 0, 13, 
	13, 52, 0, 0, 0, 15, 15, 58, 
	0, 0, 0, 11, 11, 46, 3, 0, 
	0, 9, 0, 0, 0, 0, 0, 0, 
	13, 0, 0, 0, 15, 0, 0, 0, 
	11
};

static const char _json_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	7, 9, 9, 9, 9, 7, 7, 7, 
	7, 13, 7, 7, 7, 15, 7, 7, 
	7, 11, 0, 0
};

static const int json_start = 1;
static const int json_first_final = 71;
static const int json_error = 0;

static const int json_en_object = 9;
static const int json_en_array = 43;
static const int json_en_main = 1;


/* #line 35 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */


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
    char* s = NULL, *p = (char*)data + offset,* pe = (char*)data + length,* eof = pe;

    std::list<std::string> names;

    bool needsUnescape = false;

    bool debug = false;

    if (debug) {
       gdx_log_debug("JsonReader","\n");
    }

    try {
        
/* #line 386 "JsonReader.cpp" */
	{
	cs = json_start;
	top = 0;
	}

/* #line 392 "JsonReader.cpp" */
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _json_trans_keys + _json_key_offsets[cs];
	_trans = _json_index_offsets[cs];

	_klen = _json_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _json_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += ((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _json_indicies[_trans];
	cs = _json_trans_targs[_trans];

	if ( _json_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _json_actions + _json_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 90 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
	{
                        s = p;
                        needsUnescape = false;
                }
	break;
	case 1:
/* #line 94 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
	{
                        needsUnescape = true;
                }
	break;
	case 2:
/* #line 97 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
	{
                        std::string name(s, p-s);
                        s = p;
                        if (needsUnescape) name = unescape(name);
                        if (debug)gdx_log_debug("JsonReader","name: %s", name.c_str());
                        names.push_back(name);
                }
	break;
	case 3:
/* #line 104 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
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
	case 4:
/* #line 117 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
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
	case 5:
/* #line 133 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
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
	case 6:
/* #line 145 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
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
	case 7:
/* #line 157 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","nulll: %s", name.c_str());
                        }
                        string(name, "");
                }
	break;
	case 8:
/* #line 169 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
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
				{stack[top++] = cs; cs = 9; goto _again;}}
                }
	break;
	case 9:
/* #line 182 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
	{
                        if (debug) {
                           gdx_log_debug("JsonReader","endObject");
                        }
                        pop();
                        {cs = stack[--top]; goto _again;}
                }
	break;
	case 10:
/* #line 189 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
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
				{stack[top++] = cs; cs = 43; goto _again;}}
                }
	break;
	case 11:
/* #line 202 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
	{
                        if (debug) {
                           gdx_log_debug("JsonReader","endArray");
                        }
                        pop();
                        {cs = stack[--top]; goto _again;}
                }
	break;
/* #line 625 "JsonReader.cpp" */
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	const char *__acts = _json_actions + _json_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 3:
/* #line 104 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
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
	case 4:
/* #line 117 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
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
	case 5:
/* #line 133 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
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
	case 6:
/* #line 145 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
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
	case 7:
/* #line 157 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */
	{
                        std::string name = "";
                        if (names.size() > 0) {
                            name = names.front();
                            names.pop_front();
                        }

                        if (debug) {
                           gdx_log_debug("JsonReader","nulll: %s", name.c_str());
                        }
                        string(name, "");
                }
	break;
/* #line 721 "JsonReader.cpp" */
		}
	}
	}

	_out: {}
	}

/* #line 234 "/data/git/libgdx-cpp/src/gdx-cpp/utils/JsonReader.rl" */


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

        if (element_type == JsonValue::json_json)
            gdx_log_error("gdx","Error parsing JSON, unmatched brace.");
        else
            gdx_log_error("gdx","Error parsing JSON, unmatched bracket.");
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
            
            int codepoint = strtol(value.substr(i, 4).c_str(), NULL, 16);            
            
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
            gdx_log_error("gdx","Illegal escaped character: \\" + c);
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