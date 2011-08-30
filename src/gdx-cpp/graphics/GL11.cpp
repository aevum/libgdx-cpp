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
 */

#include "GL11.hpp"

using namespace gdx_cpp::graphics;

const int GL11::GL_OES_VERSION_1_0 = 1;
const int GL11::GL_MAX_ELEMENTS_VERTICES = 0x80E8;
const int GL11::GL_MAX_ELEMENTS_INDICES = 0x80E9;
const int GL11::GL_POLYGON_SMOOTH_HINT = 0x0C53;
const int GL11::GL_VERSION_ES_CM_1_0 = 1;
const int GL11::GL_VERSION_ES_CL_1_0 = 1;
const int GL11::GL_VERSION_ES_CM_1_1 = 1;
const int GL11::GL_VERSION_ES_CL_1_1 = 1;
const int GL11::GL_CLIP_PLANE0 = 0x3000;
const int GL11::GL_CLIP_PLANE1 = 0x3001;
const int GL11::GL_CLIP_PLANE2 = 0x3002;
const int GL11::GL_CLIP_PLANE3 = 0x3003;
const int GL11::GL_CLIP_PLANE4 = 0x3004;
const int GL11::GL_CLIP_PLANE5 = 0x3005;
const int GL11::GL_CURRENT_COLOR = 0x0B00;
const int GL11::GL_CURRENT_NORMAL = 0x0B02;
const int GL11::GL_CURRENT_TEXTURE_COORDS = 0x0B03;
const int GL11::GL_POINT_SIZE = 0x0B11;
const int GL11::GL_POINT_SIZE_MIN = 0x8126;
const int GL11::GL_POINT_SIZE_MAX = 0x8127;
const int GL11::GL_POINT_FADE_THRESHOLD_SIZE = 0x8128;
const int GL11::GL_POINT_DISTANCE_ATTENUATION = 0x8129;
const int GL11::GL_LINE_WIDTH = 0x0B21;
const int GL11::GL_CULL_FACE_MODE = 0x0B45;
const int GL11::GL_FRONT_FACE = 0x0B46;
const int GL11::GL_SHADE_MODEL = 0x0B54;
const int GL11::GL_DEPTH_RANGE = 0x0B70;
const int GL11::GL_DEPTH_WRITEMASK = 0x0B72;
const int GL11::GL_DEPTH_CLEAR_VALUE = 0x0B73;
const int GL11::GL_DEPTH_FUNC = 0x0B74;
const int GL11::GL_STENCIL_CLEAR_VALUE = 0x0B91;
const int GL11::GL_STENCIL_FUNC = 0x0B92;
const int GL11::GL_STENCIL_VALUE_MASK = 0x0B93;
const int GL11::GL_STENCIL_FAIL = 0x0B94;
const int GL11::GL_STENCIL_PASS_DEPTH_FAIL = 0x0B95;
const int GL11::GL_STENCIL_PASS_DEPTH_PASS = 0x0B96;
const int GL11::GL_STENCIL_REF = 0x0B97;
const int GL11::GL_STENCIL_WRITEMASK = 0x0B98;
const int GL11::GL_MATRIX_MODE = 0x0BA0;
const int GL11::GL_VIEWPORT = 0x0BA2;
const int GL11::GL_MODELVIEW_STACK_DEPTH = 0x0BA3;
const int GL11::GL_PROJECTION_STACK_DEPTH = 0x0BA4;
const int GL11::GL_TEXTURE_STACK_DEPTH = 0x0BA5;
const int GL11::GL_MODELVIEW_MATRIX = 0x0BA6;
const int GL11::GL_PROJECTION_MATRIX = 0x0BA7;
const int GL11::GL_TEXTURE_MATRIX = 0x0BA8;
const int GL11::GL_ALPHA_TEST_FUNC = 0x0BC1;
const int GL11::GL_ALPHA_TEST_REF = 0x0BC2;
const int GL11::GL_BLEND_DST = 0x0BE0;
const int GL11::GL_BLEND_SRC = 0x0BE1;
const int GL11::GL_LOGIC_OP_MODE = 0x0BF0;
const int GL11::GL_SCISSOR_BOX = 0x0C10;
const int GL11::GL_COLOR_CLEAR_VALUE = 0x0C22;
const int GL11::GL_COLOR_WRITEMASK = 0x0C23;
const int GL11::GL_MAX_CLIP_PLANES = 0x0D32;
const int GL11::GL_POLYGON_OFFSET_UNITS = 0x2A00;
const int GL11::GL_POLYGON_OFFSET_FACTOR = 0x8038;
const int GL11::GL_TEXTURE_BINDING_2D = 0x8069;
const int GL11::GL_VERTEX_ARRAY_SIZE = 0x807A;
const int GL11::GL_VERTEX_ARRAY_TYPE = 0x807B;
const int GL11::GL_VERTEX_ARRAY_STRIDE = 0x807C;
const int GL11::GL_NORMAL_ARRAY_TYPE = 0x807E;
const int GL11::GL_NORMAL_ARRAY_STRIDE = 0x807F;
const int GL11::GL_COLOR_ARRAY_SIZE = 0x8081;
const int GL11::GL_COLOR_ARRAY_TYPE = 0x8082;
const int GL11::GL_COLOR_ARRAY_STRIDE = 0x8083;
const int GL11::GL_TEXTURE_COORD_ARRAY_SIZE = 0x8088;
const int GL11::GL_TEXTURE_COORD_ARRAY_TYPE = 0x8089;
const int GL11::GL_TEXTURE_COORD_ARRAY_STRIDE = 0x808A;
const int GL11::GL_VERTEX_ARRAY_POINTER = 0x808E;
const int GL11::GL_NORMAL_ARRAY_POINTER = 0x808F;
const int GL11::GL_COLOR_ARRAY_POINTER = 0x8090;
const int GL11::GL_TEXTURE_COORD_ARRAY_POINTER = 0x8092;
const int GL11::GL_SAMPLE_BUFFERS = 0x80A8;
const int GL11::GL_SAMPLES = 0x80A9;
const int GL11::GL_SAMPLE_COVERAGE_VALUE = 0x80AA;
const int GL11::GL_SAMPLE_COVERAGE_INVERT = 0x80AB;
const int GL11::GL_GENERATE_MIPMAP_HINT = 0x8192;
const int GL11::GL_GENERATE_MIPMAP = 0x8191;
const int GL11::GL_ACTIVE_TEXTURE = 0x84E0;
const int GL11::GL_CLIENT_ACTIVE_TEXTURE = 0x84E1;
const int GL11::GL_ARRAY_BUFFER = 0x8892;
const int GL11::GL_ELEMENT_ARRAY_BUFFER = 0x8893;
const int GL11::GL_ARRAY_BUFFER_BINDING = 0x8894;
const int GL11::GL_ELEMENT_ARRAY_BUFFER_BINDING = 0x8895;
const int GL11::GL_VERTEX_ARRAY_BUFFER_BINDING = 0x8896;
const int GL11::GL_NORMAL_ARRAY_BUFFER_BINDING = 0x8897;
const int GL11::GL_COLOR_ARRAY_BUFFER_BINDING = 0x8898;
const int GL11::GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING = 0x889A;
const int GL11::GL_STATIC_DRAW = 0x88E4;
const int GL11::GL_DYNAMIC_DRAW = 0x88E8;
const int GL11::GL_BUFFER_SIZE = 0x8764;
const int GL11::GL_BUFFER_USAGE = 0x8765;
const int GL11::GL_SUBTRACT = 0x84E7;
const int GL11::GL_COMBINE = 0x8570;
const int GL11::GL_COMBINE_RGB = 0x8571;
const int GL11::GL_COMBINE_ALPHA = 0x8572;
const int GL11::GL_RGB_SCALE = 0x8573;
const int GL11::GL_ADD_SIGNED = 0x8574;
const int GL11::GL_INTERPOLATE = 0x8575;
const int GL11::GL_CONSTANT = 0x8576;
const int GL11::GL_PRIMARY_COLOR = 0x8577;
const int GL11::GL_PREVIOUS = 0x8578;
const int GL11::GL_OPERAND0_RGB = 0x8590;
const int GL11::GL_OPERAND1_RGB = 0x8591;
const int GL11::GL_OPERAND2_RGB = 0x8592;
const int GL11::GL_OPERAND0_ALPHA = 0x8598;
const int GL11::GL_OPERAND1_ALPHA = 0x8599;
const int GL11::GL_OPERAND2_ALPHA = 0x859A;
const int GL11::GL_ALPHA_SCALE = 0x0D1C;
const int GL11::GL_SRC0_RGB = 0x8580;
const int GL11::GL_SRC1_RGB = 0x8581;
const int GL11::GL_SRC2_RGB = 0x8582;
const int GL11::GL_SRC0_ALPHA = 0x8588;
const int GL11::GL_SRC1_ALPHA = 0x8589;
const int GL11::GL_SRC2_ALPHA = 0x858A;
const int GL11::GL_DOT3_RGB = 0x86AE;
const int GL11::GL_DOT3_RGBA = 0x86AF;
const int GL11::GL_POINT_SIZE_ARRAY_OES = 0x8B9C;
const int GL11::GL_POINT_SIZE_ARRAY_TYPE_OES = 0x898A;
const int GL11::GL_POINT_SIZE_ARRAY_STRIDE_OES = 0x898B;
const int GL11::GL_POINT_SIZE_ARRAY_POINTER_OES = 0x898C;
const int GL11::GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES = 0x8B9F;
const int GL11::GL_POINT_SPRITE_OES = 0x8861;
const int GL11::GL_COORD_REPLACE_OES = 0x8862;
const int GL11::GL_OES_point_size_array = 1;
const int GL11::GL_OES_point_sprite = 1;
