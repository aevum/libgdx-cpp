
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

using namespace gdx_cpp::utils;
using namespace gdx_cpp;

const char JsonReader::_json_actions[61] = { 0, 1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 1, 10, 1, 11, 2, 0, 2, 2, 0, 3, 2, 3, 9,
        2, 3, 11, 2, 4, 9, 2, 4, 11, 2, 5, 9, 2, 5, 11, 2, 6, 9, 2, 6, 11, 2, 7, 9, 2, 7, 11
    };

const short JsonReader::_json_key_offsets[92] = {0, 0, 19, 21, 23, 32, 35, 37, 41, 43, 55, 57, 59, 63, 82, 84, 86, 91, 102, 109, 118, 125, 128, 136,
138, 147, 151, 153, 160, 170, 178, 186, 194, 202, 207, 215, 223, 231, 236, 244, 252, 260, 265, 274, 295, 297, 299, 304,
324, 331, 334, 342, 344, 353, 357, 359, 366, 376, 384, 392, 400, 408, 413, 421, 429, 437, 442, 450, 458, 466, 471, 480,
483, 490, 496, 503, 508, 516, 524, 532, 540, 548, 551, 559, 567, 575, 578, 586, 594, 602, 605, 605    };

const char JsonReader::_json_trans_keys[606] = { 32, 34, 36, 45, 48, 91, 95, 102, 110, 116, 123, 9, 13, 49, 57, 65, 90, 97, 122, 34, 92, 34, 92, 34, 47,
    92, 98, 102, 110, 114, 116, 117, 48, 49, 57, 48, 57, 43, 45, 48, 57, 48, 57, 32, 34, 36, 44, 95, 125, 9, 13, 65, 90, 97,
    122, 34, 92, 34, 92, 32, 58, 9, 13, 32, 34, 36, 45, 48, 91, 95, 102, 110, 116, 123, 9, 13, 49, 57, 65, 90, 97, 122, 34,
    92, 34, 92, 32, 44, 125, 9, 13, 32, 34, 36, 95, 125, 9, 13, 65, 90, 97, 122, 32, 44, 58, 93, 125, 9, 13, 34, 47, 92, 98,
    102, 110, 114, 116, 117, 32, 44, 58, 93, 125, 9, 13, 48, 49, 57, 32, 44, 46, 69, 101, 125, 9, 13, 48, 57, 32, 44, 69,
    101, 125, 9, 13, 48, 57, 43, 45, 48, 57, 48, 57, 32, 44, 125, 9, 13, 48, 57, 32, 44, 46, 69, 101, 125, 9, 13, 48, 57,
    32, 44, 58, 93, 97, 125, 9, 13, 32, 44, 58, 93, 108, 125, 9, 13, 32, 44, 58, 93, 115, 125, 9, 13, 32, 44, 58, 93, 101,
    125, 9, 13, 32, 44, 125, 9, 13, 32, 44, 58, 93, 117, 125, 9, 13, 32, 44, 58, 93, 108, 125, 9, 13, 32, 44, 58, 93, 108,
    125, 9, 13, 32, 44, 125, 9, 13, 32, 44, 58, 93, 114, 125, 9, 13, 32, 44, 58, 93, 117, 125, 9, 13, 32, 44, 58, 93, 101,
    125, 9, 13, 32, 44, 125, 9, 13, 34, 47, 92, 98, 102, 110, 114, 116, 117, 32, 34, 36, 44, 45, 48, 91, 93, 95, 102, 110,
    116, 123, 9, 13, 49, 57, 65, 90, 97, 122, 34, 92, 34, 92, 32, 44, 93, 9, 13, 32, 34, 36, 45, 48, 91, 93, 95, 102, 110,
    116, 123, 9, 13, 49, 57, 65, 90, 97, 122, 32, 44, 58, 93, 125, 9, 13, 48, 49, 57, 32, 44, 46, 69, 93, 101, 9, 13, 48,
    57, 32, 44, 69, 93, 101, 9, 13, 48, 57, 43, 45, 48, 57, 48, 57, 32, 44, 93, 9, 13, 48, 57, 32, 44, 46, 69, 93, 101, 9,
    13, 48, 57, 32, 44, 58, 93, 97, 125, 9, 13, 32, 44, 58, 93, 108, 125, 9, 13, 32, 44, 58, 93, 115, 125, 9, 13, 32, 44,
    58, 93, 101, 125, 9, 13, 32, 44, 93, 9, 13, 32, 44, 58, 93, 117, 125, 9, 13, 32, 44, 58, 93, 108, 125, 9, 13, 32, 44,
    58, 93, 108, 125, 9, 13, 32, 44, 93, 9, 13, 32, 44, 58, 93, 114, 125, 9, 13, 32, 44, 58, 93, 117, 125, 9, 13, 32, 44,
    58, 93, 101, 125, 9, 13, 32, 44, 93, 9, 13, 34, 47, 92, 98, 102, 110, 114, 116, 117, 32, 9, 13, 32, 44, 58, 93, 125, 9,
    13, 32, 46, 69, 101, 9, 13, 32, 69, 101, 9, 13, 48, 57, 32, 9, 13, 48, 57, 32, 46, 69, 101, 9, 13, 48, 57, 32, 44, 58,
    93, 97, 125, 9, 13, 32, 44, 58, 93, 108, 125, 9, 13, 32, 44, 58, 93, 115, 125, 9, 13, 32, 44, 58, 93, 101, 125, 9, 13,
    32, 9, 13, 32, 44, 58, 93, 117, 125, 9, 13, 32, 44, 58, 93, 108, 125, 9, 13, 32, 44, 58, 93, 108, 125, 9, 13, 32, 9, 13,
    32, 44, 58, 93, 114, 125, 9, 13, 32, 44, 58, 93, 117, 125, 9, 13, 32, 44, 58, 93, 101, 125, 9, 13, 32, 9, 13, 0
    };

const char JsonReader::_json_single_lengths[92] = {0, 11, 2, 2, 7, 1, 0, 2, 0, 6, 2, 2, 2, 11, 2, 2, 3, 5, 5, 7, 5, 1, 6, 0, 5, 2, 0, 3, 6, 6, 6, 6, 6, 3,
6, 6, 6, 3, 6, 6, 6, 3, 7, 13, 2, 2, 3, 12, 5, 1, 6, 0, 5, 2, 0, 3, 6, 6, 6, 6, 6, 3, 6, 6, 6, 3, 6, 6, 6, 3, 7, 1, 5,
4, 3, 1, 4, 6, 6, 6, 6, 1, 6, 6, 6, 1, 6, 6, 6, 1, 0, 0    };

const char JsonReader::_json_range_lengths[92] = {0, 4, 0, 0, 1, 1, 1, 1, 1, 3, 0, 0, 1, 4, 0, 0, 1, 3, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 4, 0, 0, 1, 4, 1, 1, 1, 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0    };

const short JsonReader::_json_index_offsets[591] = {0, 0, 16, 19, 22, 31, 34, 36, 40, 42, 52, 55, 58, 62, 78, 81, 84, 89, 98, 105, 114, 121, 124, 132, 134,
142, 146, 148, 154, 163, 171, 179, 187, 195, 200, 208, 216, 224, 229, 237, 245, 253, 258, 267, 285, 288, 291, 296, 313,
320, 323, 331, 333, 341, 345, 347, 353, 362, 370, 378, 386, 394, 399, 407, 415, 423, 428, 436, 444, 452, 457, 466, 469,
476, 482, 488, 492, 499, 507, 515, 523, 531, 534, 542, 550, 558, 561, 569, 577, 585, 588, 589    };

const char JsonReader::_json_trans_targs[591] = {1, 2, 72, 5, 73, 71, 72, 77, 82, 86, 71, 1, 76, 72, 72, 0, 71, 4, 3, 71, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    0, 73, 76, 0, 74, 0, 8, 8, 75, 0, 75, 0, 9, 10, 18, 17, 18, 90, 9, 18, 18, 0, 12, 42, 11, 12, 42, 11, 12, 13, 12, 0, 13,
    14, 20, 21, 22, 16, 20, 29, 34, 38, 16, 13, 28, 20, 20, 0, 16, 19, 15, 16, 19, 15, 16, 17, 90, 16, 0, 17, 10, 18, 18,
    90, 17, 18, 18, 0, 12, 0, 13, 0, 0, 12, 18, 15, 15, 15, 15, 15, 15, 15, 15, 0, 16, 17, 0, 0, 90, 16, 20, 22, 28, 0, 16,
    17, 23, 25, 25, 90, 16, 0, 24, 0, 16, 17, 25, 25, 90, 16, 24, 0, 26, 26, 27, 0, 27, 0, 16, 17, 90, 16, 27, 0, 16, 17,
    23, 25, 25, 90, 16, 28, 0, 16, 17, 0, 0, 30, 90, 16, 20, 16, 17, 0, 0, 31, 90, 16, 20, 16, 17, 0, 0, 32, 90, 16, 20, 16,
    17, 0, 0, 33, 90, 16, 20, 16, 17, 90, 16, 0, 16, 17, 0, 0, 35, 90, 16, 20, 16, 17, 0, 0, 36, 90, 16, 20, 16, 17, 0, 0,
    37, 90, 16, 20, 16, 17, 90, 16, 0, 16, 17, 0, 0, 39, 90, 16, 20, 16, 17, 0, 0, 40, 90, 16, 20, 16, 17, 0, 0, 41, 90, 16,
    20, 16, 17, 90, 16, 0, 11, 11, 11, 11, 11, 11, 11, 11, 0, 43, 44, 48, 47, 49, 50, 46, 91, 48, 57, 62, 66, 46, 43, 56,
    48, 48, 0, 46, 70, 45, 46, 70, 45, 46, 47, 91, 46, 0, 47, 44, 48, 49, 50, 46, 91, 48, 57, 62, 66, 46, 47, 56, 48, 48, 0,
    46, 47, 0, 91, 0, 46, 48, 50, 56, 0, 46, 47, 51, 53, 91, 53, 46, 0, 52, 0, 46, 47, 53, 91, 53, 46, 52, 0, 54, 54, 55, 0,
    55, 0, 46, 47, 91, 46, 55, 0, 46, 47, 51, 53, 91, 53, 46, 56, 0, 46, 47, 0, 91, 58, 0, 46, 48, 46, 47, 0, 91, 59, 0, 46,
    48, 46, 47, 0, 91, 60, 0, 46, 48, 46, 47, 0, 91, 61, 0, 46, 48, 46, 47, 91, 46, 0, 46, 47, 0, 91, 63, 0, 46, 48, 46, 47,
    0, 91, 64, 0, 46, 48, 46, 47, 0, 91, 65, 0, 46, 48, 46, 47, 91, 46, 0, 46, 47, 0, 91, 67, 0, 46, 48, 46, 47, 0, 91, 68,
    0, 46, 48, 46, 47, 0, 91, 69, 0, 46, 48, 46, 47, 91, 46, 0, 45, 45, 45, 45, 45, 45, 45, 45, 0, 71, 71, 0, 71, 0, 0, 0,
    0, 71, 72, 71, 6, 7, 7, 71, 0, 71, 7, 7, 71, 74, 0, 71, 71, 75, 0, 71, 6, 7, 7, 71, 76, 0, 71, 0, 0, 0, 78, 0, 71, 72,
    71, 0, 0, 0, 79, 0, 71, 72, 71, 0, 0, 0, 80, 0, 71, 72, 71, 0, 0, 0, 81, 0, 71, 72, 71, 71, 0, 71, 0, 0, 0, 83, 0, 71,
    72, 71, 0, 0, 0, 84, 0, 71, 72, 71, 0, 0, 0, 85, 0, 71, 72, 71, 71, 0, 71, 0, 0, 0, 87, 0, 71, 72, 71, 0, 0, 0, 88, 0,
    71, 72, 71, 0, 0, 0, 89, 0, 71, 72, 71, 71, 0, 0, 0, 0
    };

const char JsonReader::_json_trans_actions[591] = {0, 0, 1, 1, 1, 21, 1, 1, 1, 1, 17, 0, 1, 1, 1, 0, 28, 1, 1, 7, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 19, 0, 1, 1, 0, 25, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 21, 1, 1, 1, 1, 17,
0, 1, 1, 1, 0, 28, 1, 1, 7, 0, 0, 0, 0, 19, 0, 0, 0, 0, 1, 1, 19, 0, 1, 1, 0, 5, 0, 5, 0, 0, 5, 0, 3, 3, 3, 3, 3, 3, 3,
3, 0, 7, 7, 0, 0, 31, 7, 0, 0, 0, 0, 9, 9, 0, 0, 0, 37, 9, 0, 0, 0, 9, 9, 0, 0, 37, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 37,
9, 0, 0, 9, 9, 0, 0, 0, 37, 9, 0, 0, 7, 7, 0, 0, 0, 31, 7, 0, 7, 7, 0, 0, 0, 31, 7, 0, 7, 7, 0, 0, 0, 31, 7, 0, 7, 7, 0,
0, 0, 31, 7, 0, 13, 13, 49, 13, 0, 7, 7, 0, 0, 0, 31, 7, 0, 7, 7, 0, 0, 0, 31, 7, 0, 7, 7, 0, 0, 0, 31, 7, 0, 15, 15,
55, 15, 0, 7, 7, 0, 0, 0, 31, 7, 0, 7, 7, 0, 0, 0, 31, 7, 0, 7, 7, 0, 0, 0, 31, 7, 0, 11, 11, 43, 11, 0, 3, 3, 3, 3, 3,
3, 3, 3, 0, 0, 0, 1, 0, 1, 1, 21, 23, 1, 1, 1, 1, 17, 0, 1, 1, 1, 0, 28, 1, 1, 7, 0, 0, 0, 0, 23, 0, 0, 0, 0, 1, 1, 1,
21, 23, 1, 1, 1, 1, 17, 0, 1, 1, 1, 0, 7, 7, 0, 34, 0, 7, 0, 0, 0, 0, 9, 9, 0, 0, 40, 0, 9, 0, 0, 0, 9, 9, 0, 40, 0, 9,
0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 40, 9, 0, 0, 9, 9, 0, 0, 40, 0, 9, 0, 0, 7, 7, 0, 34, 0, 0, 7, 0, 7, 7, 0, 34, 0, 0, 7, 0,
7, 7, 0, 34, 0, 0, 7, 0, 7, 7, 0, 34, 0, 0, 7, 0, 13, 13, 52, 13, 0, 7, 7, 0, 34, 0, 0, 7, 0, 7, 7, 0, 34, 0, 0, 7, 0,
7, 7, 0, 34, 0, 0, 7, 0, 15, 15, 58, 15, 0, 7, 7, 0, 34, 0, 0, 7, 0, 7, 7, 0, 34, 0, 0, 7, 0, 7, 7, 0, 34, 0, 0, 7, 0,
11, 11, 46, 11, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 7, 0, 9, 0, 0, 0, 9, 0, 9, 0, 0, 9, 0, 0, 9, 9, 0,
0, 9, 0, 0, 0, 9, 0, 0, 7, 0, 0, 0, 0, 0, 7, 0, 7, 0, 0, 0, 0, 0, 7, 0, 7, 0, 0, 0, 0, 0, 7, 0, 7, 0, 0, 0, 0, 0, 7, 0,
13, 13, 0, 7, 0, 0, 0, 0, 0, 7, 0, 7, 0, 0, 0, 0, 0, 7, 0, 7, 0, 0, 0, 0, 0, 7, 0, 15, 15, 0, 7, 0, 0, 0, 0, 0, 7, 0, 7,
0, 0, 0, 0, 0, 7, 0, 7, 0, 0, 0, 0, 0, 7, 0, 11, 11, 0, 0, 0, 0    };

const char JsonReader::_json_eof_actions[92] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 9, 9,
9, 9, 7, 7, 7, 7, 13, 7, 7, 7, 15, 7, 7, 7, 11, 0, 0 };

const int JsonReader::json_start = 1;
const int JsonReader::json_first_final = 71;
const int JsonReader::json_error = 0;

const int JsonReader::json_en_object = 9;
const int JsonReader::json_en_array = 43;
const int JsonReader::json_en_main = 1;

JsonValue* JsonReader::root = 0;
JsonValue* JsonReader::current = 0;
std::list< JsonValue* > JsonReader::elements;

JsonReader::JsonReader()
{
}

JsonValue::ptr JsonReader::parse (const std::string& json) {
    return parse(json.c_str(), 0, json.length());
}

JsonValue::ptr JsonReader::parse (const gdx_cpp::files::FileHandle& file) {
    try {
        gdx_cpp::files::FileHandle::buffer_ptr buffer;
        int size = file.readBytes(buffer);
        
        return parse(buffer.get(), 0, size);
    } catch (...) {
        throw std::runtime_error("Error parsing file: " + file.name());
    }
}

JsonValue::ptr JsonReader::parse (const char* data, int offset, int length) {
    elements.clear();
    
    unsigned int cs, p = offset, pe = length, eof = pe, top = 0;
    std::vector<int> stack(4);
    int s = 0;
    std::list<std::string> names;
    
    bool needsUnescape = false;
    
    bool debug = false;
    
    if (debug) {
        Gdx::app->log("JsonReader","\n");
    }

    try {

        // line 3 "JsonReader.java"
        {
            cs = json_start;
            top = 0;
        }

        // line 8 "JsonReader.java"
        {
            int _klen;
            int _trans = 0;
            int _acts;
            int _nacts;
            int _keys;
            int _goto_targ = 0;

_goto:
            while (true) {
                switch (_goto_targ) {
                case 0:
                    if (p == pe) {
                        _goto_targ = 4;
                        goto _goto;
                    }
                    if (cs == 0) {
                        _goto_targ = 5;
                        goto _goto;
                    }
                case 1:
                    do {
                        _keys = _json_key_offsets[cs];
                        _trans = _json_index_offsets[cs];
                        _klen = _json_single_lengths[cs];
                        if (_klen > 0) {
                            int _lower = _keys;
                            int _mid;
                            int _upper = _keys + _klen - 1;
                            while (true) {
                                if (_upper < _lower) break;

                                _mid = _lower + ((_upper - _lower) >> 1);
                                if (data[p] < _json_trans_keys[_mid])
                                    _upper = _mid - 1;
                                else if (data[p] > _json_trans_keys[_mid])
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
                        if (_klen > 0) {
                            int _lower = _keys;
                            int _mid;
                            int _upper = _keys + (_klen << 1) - 2;
                            while (true) {
                                if (_upper < _lower) break;

                                _mid = _lower + (((_upper - _lower) >> 1) & ~1);
                                if (data[p] < _json_trans_keys[_mid])
                                    _upper = _mid - 2;
                                else if (data[p] > _json_trans_keys[_mid + 1])
                                    _lower = _mid + 2;
                                else {
                                    _trans += ((_mid - _keys) >> 1);
                                    goto _match;
                                }
                            }
                            _trans += _klen;
                        }
                    } while (false);
_match:
                    cs = _json_trans_targs[_trans];

                    if (_json_trans_actions[_trans] != 0) {
                        _acts = _json_trans_actions[_trans];
                        _nacts = (int)_json_actions[_acts++];
                        while (_nacts-- > 0) {
                            switch (_json_actions[_acts++]) {
                            case 0:
                                // line 99 "JsonReader.rl"
                            {
                                s = p;
                                needsUnescape = false;
                            }
                            break;
                            case 1:
                                // line 103 "JsonReader.rl"
                            {
                                needsUnescape = true;
                            }
                            break;
                            case 2:
                                // line 106 "JsonReader.rl"
                            {
                                std::string name(data, s, p - s);
                                s = p;
                                if (needsUnescape) name = unescape(name);
                                if (debug) {
                                    Gdx::app->log("JsonReader","name: %s", name.c_str());
                                }
                                names.push_back(name);
                            }
                            break;
                            case 3:
                                // line 113 "JsonReader.rl"
                            {
                                std::string value(&data[s], p-s);
                                s = p;
                                if (needsUnescape) value = unescape(value);

                                std::string name = "";
                                if (names.size() > 0) {
                                    name = names.front();
                                    names.pop_front();
                                }
                                
                                if (debug) {
                                    Gdx::app->log("JsonReader","string: %s = %s", name.c_str(), value.c_str());
                                }
                                
                                string(name, value);
                            }
                            break;
                            case 4:
                                // line 121 "JsonReader.rl"
                            {
                                std::string value(&data[s], p-s);
                                s = p;
                                std::string name = "";
                                if (names.size() > 0) {
                                    name = names.front();
                                    names.pop_front();
                                }
                                
                                if (debug) {
                                    Gdx::app->log("JsonReader","number: %s = %s", name.c_str(), value.c_str());
                                }

                                if (value.find(".") != std::string::npos) {
                                    number(name, utils::from_string<float>(value));
                                } else {
                                    number(name, utils::from_string<int>(value));
                                }
                            }
                            break;
                            case 5:
                                // line 128 "JsonReader.rl"
                            {
                                std::string name = "";
                                if (names.size() > 0) {
                                    name = names.front();
                                    names.pop_front();
                                }
                                
                                if (debug) {
                                    Gdx::app->log("JsonReader","number: %s = true", name.c_str());
                                }
                                boolean(name, true);
                            }
                            break;
                            case 6:
                                // line 133 "JsonReader.rl"
                            {
                                std::string name = "";
                                if (names.size() > 0) {
                                    name = names.front();
                                    names.pop_front();
                                }
                                
                                if (debug) {
                                    Gdx::app->log("JsonReader","number: %s = false", name.c_str());
                                }
                                boolean(name, false);
                            }
                            break;
                            case 7:
                                // line 138 "JsonReader.rl"
                            {
                                std::string name = "";
                                if (names.size() > 0) {
                                    name = names.front();
                                    names.pop_front();
                                }
                                
                                if (debug) {
                                    Gdx::app->log("JsonReader","nulll: %s", name.c_str());
                                }
                                string(name, "");
                            }
                            break;
                            case 8:
                                // line 143 "JsonReader.rl"
                            {
                                std::string name = "";
                                if (names.size() > 0) {
                                    name = names.front();
                                    names.pop_front();
                                }
                                
                                if (debug) {
                                    Gdx::app->log("JsonReader","startObject: %s", name.c_str());                                    
                                }
                                
                                startObject(name);
                                {
                                    if (top == stack.size()) {
                                        stack.resize(stack.size() * 2);
                                    }
                                    {
                                        stack[top++] = cs;
                                        cs = 9;
                                        _goto_targ = 2;
                                        if (true) {
                                            goto _goto;
                                        }
                                    }
                                }
                            }
                            break;
                            case 9:
                                // line 149 "JsonReader.rl"
                            {
                                if (debug) {
                                    Gdx::app->log("JsonReader","endObject");
                                }
                                pop();
                                {
                                    cs = stack[--top];
                                    _goto_targ = 2;
                                    if (true) {
                                        goto _goto;
                                    }
                                }
                            }
                            break;
                            case 10:
                                // line 154 "JsonReader.rl"
                            {
                                std::string name = "";
                                if (names.size() > 0) {
                                    name = names.front();
                                    names.pop_front();
                                }
                                
                                if (debug) {
                                    Gdx::app->log("JsonReader","startArray: %s", name.c_str());
                                }
                                
                                startArray(name);
                                {
                                    if (top == stack.size()) {
                                        stack.resize(stack.size() * 2);
                                    }
                                    {
                                        stack[top++] = cs;
                                        cs = 43;
                                        _goto_targ = 2;
                                        if (true) goto _goto;
                                    }
                                }
                            }
                            break;
                            case 11:
                                // line 160 "JsonReader.rl"
                            {
                                if (debug) {
                                    Gdx::app->log("JsonReader","endtArray");
                                }
                                
                                pop();
                                {
                                    cs = stack[--top];
                                    _goto_targ = 2;
                                    if (true) {
                                        goto _goto;
                                    }
                                }
                            }
                            break;
                            // line 201 "JsonReader.java"
                            }
                        }
                    }

                case 2:
                    if (cs == 0) {
                        _goto_targ = 5;
                        goto _goto;
                    }
                    if (++p != pe) {
                        _goto_targ = 1;
                        goto _goto;
                    }
                case 4:
                    if (p == eof) {
                        int __acts = _json_eof_actions[cs];
                        int __nacts = (int)_json_actions[__acts++];
                        while (__nacts-- > 0) {
                            switch (_json_actions[__acts++]) {
                            case 3:
                                // line 113 "JsonReader.rl"
                            {
                                std::string value(&data[s], p-s);
                                s = p;
                                if (needsUnescape) value = unescape(value);
                                std::string name = "";
                                if (names.size() > 0) {
                                    name = names.front();
                                    names.pop_front();
                                }
                                
                                if (debug) {
                                    Gdx::app->log("JsonReader","string: %s = %s", name.c_str(), value.c_str());
                                }
                                string(name, value);
                            }
                            break;
                            case 4:
                                // line 121 "JsonReader.rl"
                            {
                                std::string value(&data[s], p-s);
                                s = p;

                                std::string name = "";
                                if (names.size() > 0) {
                                    name = names.front();
                                    names.pop_front();
                                }
                                if (debug) {
                                    Gdx::app->log("JsonReader","number: %s = %s", name.c_str(), value.c_str());
                                }
                                if (value.find(".") != std::string::npos) {
                                    number(name, utils::from_string< float >(value));
                                } else {
                                    number(name, utils::from_string< int >(value));
                                }
                            }
                            break;
                            case 5:
                                // line 128 "JsonReader.rl"
                            {
                                std::string name = "";
                                if (names.size() > 0) {
                                    name = names.front();
                                    names.pop_front();
                                }
                                if (debug) {
                                    Gdx::app->log("JsonReader","boolean: %s = true", name.c_str());
                                }
                                boolean(name, true);
                            }
                            break;
                            case 6:
                                // line 133 "JsonReader.rl"
                            {
                                std::string name = "";
                                if (names.size() > 0) {
                                    name = names.front();
                                    names.pop_front();
                                }
                                
                                if (debug) {
                                    Gdx::app->log("JsonReader","boolean: %s = false", name.c_str());
                                }
                                boolean(name, false);
                            }
                            break;
                            case 7:
                                // line 138 "JsonReader.rl"
                            {
                                std::string name = "";
                                if (names.size() > 0) {
                                    name = names.front();
                                    names.pop_front();
                                }
                                if (debug) {
                                    Gdx::app->log("JsonReader","null: %s", name.c_str());
                                }
                                string(name, "");
                            }
                            break;
                            // line 267 "JsonReader.java"
                            }
                        }
                    }

                case 5:
                    break;
                }
                break;
            }
        }

        // line 190 "JsonReader.rl"

    } catch (std::runtime_error& ex) {
        
    }

    if (p < pe) {
        int lineNumber = 1;
        for (unsigned int i = 0; i < p; i++)
            if (data[i] == '\n') lineNumber++;
        throw std::runtime_error("Error parsing JSON on line " + utils::to_string(lineNumber) + " near: " + std::string(data, p, pe - p));
    } else if (elements.size() != 0) {
        int element_type = elements.front()->item_type;
        
        std::list< JsonValue* >::iterator it = elements.begin();
        std::list< JsonValue* >::iterator end = elements.end();

        for (; it != end; ++it) {
            delete *it;
        }

        elements.clear();
        
        if (element_type == json_json)
            throw std::runtime_error("Error parsing JSON, unmatched brace.");
        else
            throw std::runtime_error("Error parsing JSON, unmatched bracket.");
    }
    
    JsonValue* _root = root;
    root = NULL;

    return std::tr1::shared_ptr< JsonValue >(_root);
}

void JsonReader::set (const std::string& name, gdx_cpp::utils::JsonValue* value) {
    switch (current->item_type) {
        case json_json:
            ((JsonValue::item_map&)(*current))[name] = value;
            break;
        case json_list:
            ((JsonValue::array&)*current).push_back(value);
            break;
        default:
            current = value;
            break;
    }    
}

void JsonReader::startObject (const std::string& name) {
    JsonValue* value = JsonValue::newNodeAsJson();
    
    if (current != NULL) {
        set(name, value);
    }
    
    elements.push_back(value);
    current = value;
}

void JsonReader::startArray (const std::string& name) {
    JsonValue* array_item = JsonValue::newNodeAsArray();
    
    if (current != NULL) {
        set(name, array_item);
    }
    
    elements.push_back(array_item);
    current = array_item;
}

void JsonReader::pop () {
    root = elements.back();
    elements.pop_back();
    current = elements.size() > 0 ? elements.back() : NULL;
}

void JsonReader::string (const std::string& name,const std::string& value) {
    set(name, JsonValue::newNodeAsString(new std::string(value)));
}

void JsonReader::number (const std::string& name, float value) {
    set(name, JsonValue::newNodeAsFloat(new float(value)));
}

void JsonReader::boolean (const std::string& name, bool value) {
    set(name, JsonValue::newNodeAsBool(new bool(value)));
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
            buffer << utils::from_string< int >(value.substr(i, i + 4));
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
            throw std::runtime_error("Illegal escaped character: \\" + c);
        }
        
        buffer << c;
    }
    return buffer.str();
}

void JsonReader::number(const std::string& name, int value)
{
    set(name, JsonValue::newNodeAsInt(new int(value)));
}

