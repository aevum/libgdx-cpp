
/*
 *    Copyright 2011 Aevum Software aevum @ aevumlab.com
 * 
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 * 
 *        http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 * 
 *    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *    @author Ozires Bortolon de Faria ozires@aevumlab.com
 */

#include "GL20.hpp"

using namespace gdx;
using namespace std;

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#undef GL_ES_VERSION_2_0
#undef GL_DEPTH_BUFFER_BIT
#undef GL_STENCIL_BUFFER_BIT
#undef GL_COLOR_BUFFER_BIT
#undef GL_FALSE
#undef GL_TRUE
#undef GL_POINTS
#undef GL_LINES
#undef GL_LINE_LOOP
#undef GL_LINE_STRIP
#undef GL_TRIANGLES
#undef GL_TRIANGLE_STRIP
#undef GL_TRIANGLE_FAN
#undef GL_ZERO
#undef GL_ONE
#undef GL_SRC_COLOR
#undef GL_ONE_MINUS_SRC_COLOR
#undef GL_SRC_ALPHA
#undef GL_ONE_MINUS_SRC_ALPHA
#undef GL_DST_ALPHA
#undef GL_ONE_MINUS_DST_ALPHA
#undef GL_DST_COLOR
#undef GL_ONE_MINUS_DST_COLOR
#undef GL_SRC_ALPHA_SATURATE
#undef GL_FUNC_ADD
#undef GL_BLEND_EQUATION
#undef GL_BLEND_EQUATION_RGB
#undef GL_BLEND_EQUATION_ALPHA
#undef GL_FUNC_SUBTRACT
#undef GL_FUNC_REVERSE_SUBTRACT
#undef GL_BLEND_DST_RGB
#undef GL_BLEND_SRC_RGB
#undef GL_BLEND_DST_ALPHA
#undef GL_BLEND_SRC_ALPHA
#undef GL_CONSTANT_COLOR
#undef GL_ONE_MINUS_CONSTANT_COLOR
#undef GL_CONSTANT_ALPHA
#undef GL_ONE_MINUS_CONSTANT_ALPHA
#undef GL_BLEND_COLOR
#undef GL_ARRAY_BUFFER
#undef GL_ELEMENT_ARRAY_BUFFER
#undef GL_ARRAY_BUFFER_BINDING
#undef GL_ELEMENT_ARRAY_BUFFER_BINDING
#undef GL_STREAM_DRAW
#undef GL_STATIC_DRAW
#undef GL_DYNAMIC_DRAW
#undef GL_BUFFER_SIZE
#undef GL_BUFFER_USAGE
#undef GL_CURRENT_VERTEX_ATTRIB
#undef GL_FRONT
#undef GL_BACK
#undef GL_FRONT_AND_BACK
#undef GL_TEXTURE_2D
#undef GL_CULL_FACE
#undef GL_BLEND
#undef GL_DITHER
#undef GL_STENCIL_TEST
#undef GL_DEPTH_TEST
#undef GL_SCISSOR_TEST
#undef GL_POLYGON_OFFSET_FILL
#undef GL_SAMPLE_ALPHA_TO_COVERAGE
#undef GL_SAMPLE_COVERAGE
#undef GL_NO_ERROR
#undef GL_INVALID_ENUM
#undef GL_INVALID_VALUE
#undef GL_INVALID_OPERATION
#undef GL_OUT_OF_MEMORY
#undef GL_CW
#undef GL_CCW
#undef GL_LINE_WIDTH
#undef GL_ALIASED_POINT_SIZE_RANGE
#undef GL_ALIASED_LINE_WIDTH_RANGE
#undef GL_CULL_FACE_MODE
#undef GL_FRONT_FACE
#undef GL_DEPTH_RANGE
#undef GL_DEPTH_WRITEMASK
#undef GL_DEPTH_CLEAR_VALUE
#undef GL_DEPTH_FUNC
#undef GL_STENCIL_CLEAR_VALUE
#undef GL_STENCIL_FUNC
#undef GL_STENCIL_FAIL
#undef GL_STENCIL_PASS_DEPTH_FAIL
#undef GL_STENCIL_PASS_DEPTH_PASS
#undef GL_STENCIL_REF
#undef GL_STENCIL_VALUE_MASK
#undef GL_STENCIL_WRITEMASK
#undef GL_STENCIL_BACK_FUNC
#undef GL_STENCIL_BACK_FAIL
#undef GL_STENCIL_BACK_PASS_DEPTH_FAIL
#undef GL_STENCIL_BACK_PASS_DEPTH_PASS
#undef GL_STENCIL_BACK_REF
#undef GL_STENCIL_BACK_VALUE_MASK
#undef GL_STENCIL_BACK_WRITEMASK
#undef GL_VIEWPORT
#undef GL_SCISSOR_BOX
#undef GL_COLOR_CLEAR_VALUE
#undef GL_COLOR_WRITEMASK
#undef GL_UNPACK_ALIGNMENT
#undef GL_PACK_ALIGNMENT
#undef GL_MAX_TEXTURE_SIZE
#undef GL_MAX_VIEWPORT_DIMS
#undef GL_SUBPIXEL_BITS
#undef GL_RED_BITS
#undef GL_GREEN_BITS
#undef GL_BLUE_BITS
#undef GL_ALPHA_BITS
#undef GL_DEPTH_BITS
#undef GL_STENCIL_BITS
#undef GL_POLYGON_OFFSET_UNITS
#undef GL_POLYGON_OFFSET_FACTOR
#undef GL_TEXTURE_BINDING_2D
#undef GL_SAMPLE_BUFFERS
#undef GL_SAMPLES
#undef GL_SAMPLE_COVERAGE_VALUE
#undef GL_SAMPLE_COVERAGE_INVERT
#undef GL_NUM_COMPRESSED_TEXTURE_FORMATS
#undef GL_COMPRESSED_TEXTURE_FORMATS
#undef GL_DONT_CARE
#undef GL_FASTEST
#undef GL_NICEST
#undef GL_GENERATE_MIPMAP_HINT
#undef GL_BYTE
#undef GL_UNSIGNED_BYTE
#undef GL_SHORT
#undef GL_UNSIGNED_SHORT
#undef GL_INT
#undef GL_UNSIGNED_INT
#undef GL_FLOAT
#undef GL_FIXED
#undef GL_DEPTH_COMPONENT
#undef GL_ALPHA
#undef GL_RGB
#undef GL_RGBA
#undef GL_LUMINANCE
#undef GL_LUMINANCE_ALPHA
#undef GL_UNSIGNED_SHORT_4_4_4_4
#undef GL_UNSIGNED_SHORT_5_5_5_1
#undef GL_UNSIGNED_SHORT_5_6_5
#undef GL_FRAGMENT_SHADER
#undef GL_VERTEX_SHADER
#undef GL_MAX_VERTEX_ATTRIBS
#undef GL_MAX_VERTEX_UNIFORM_VECTORS
#undef GL_MAX_VARYING_VECTORS
#undef GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
#undef GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS
#undef GL_MAX_TEXTURE_IMAGE_UNITS
#undef GL_MAX_FRAGMENT_UNIFORM_VECTORS
#undef GL_SHADER_TYPE
#undef GL_DELETE_STATUS
#undef GL_LINK_STATUS
#undef GL_VALIDATE_STATUS
#undef GL_ATTACHED_SHADERS
#undef GL_ACTIVE_UNIFORMS
#undef GL_ACTIVE_UNIFORM_MAX_LENGTH
#undef GL_ACTIVE_ATTRIBUTES
#undef GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
#undef GL_SHADING_LANGUAGE_VERSION
#undef GL_CURRENT_PROGRAM
#undef GL_NEVER
#undef GL_LESS
#undef GL_EQUAL
#undef GL_LEQUAL
#undef GL_GREATER
#undef GL_NOTEQUAL
#undef GL_GEQUAL
#undef GL_ALWAYS
#undef GL_KEEP
#undef GL_REPLACE
#undef GL_INCR
#undef GL_DECR
#undef GL_INVERT
#undef GL_INCR_WRAP
#undef GL_DECR_WRAP
#undef GL_VENDOR
#undef GL_RENDERER
#undef GL_VERSION
#undef GL_EXTENSIONS
#undef GL_NEAREST
#undef GL_LINEAR
#undef GL_NEAREST_MIPMAP_NEAREST
#undef GL_LINEAR_MIPMAP_NEAREST
#undef GL_NEAREST_MIPMAP_LINEAR
#undef GL_LINEAR_MIPMAP_LINEAR
#undef GL_TEXTURE_MAG_FILTER
#undef GL_TEXTURE_MIN_FILTER
#undef GL_TEXTURE_WRAP_S
#undef GL_TEXTURE_WRAP_T
#undef GL_TEXTURE
#undef GL_TEXTURE_CUBE_MAP
#undef GL_TEXTURE_BINDING_CUBE_MAP
#undef GL_TEXTURE_CUBE_MAP_POSITIVE_X
#undef GL_TEXTURE_CUBE_MAP_NEGATIVE_X
#undef GL_TEXTURE_CUBE_MAP_POSITIVE_Y
#undef GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
#undef GL_TEXTURE_CUBE_MAP_POSITIVE_Z
#undef GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
#undef GL_MAX_CUBE_MAP_TEXTURE_SIZE
#undef GL_TEXTURE0
#undef GL_TEXTURE1
#undef GL_TEXTURE2
#undef GL_TEXTURE3
#undef GL_TEXTURE4
#undef GL_TEXTURE5
#undef GL_TEXTURE6
#undef GL_TEXTURE7
#undef GL_TEXTURE8
#undef GL_TEXTURE9
#undef GL_TEXTURE10
#undef GL_TEXTURE11
#undef GL_TEXTURE12
#undef GL_TEXTURE13
#undef GL_TEXTURE14
#undef GL_TEXTURE15
#undef GL_TEXTURE16
#undef GL_TEXTURE17
#undef GL_TEXTURE18
#undef GL_TEXTURE19
#undef GL_TEXTURE20
#undef GL_TEXTURE21
#undef GL_TEXTURE22
#undef GL_TEXTURE23
#undef GL_TEXTURE24
#undef GL_TEXTURE25
#undef GL_TEXTURE26
#undef GL_TEXTURE27
#undef GL_TEXTURE28
#undef GL_TEXTURE29
#undef GL_TEXTURE30
#undef GL_TEXTURE31
#undef GL_ACTIVE_TEXTURE
#undef GL_REPEAT
#undef GL_CLAMP_TO_EDGE
#undef GL_MIRRORED_REPEAT
#undef GL_FLOAT_VEC2
#undef GL_FLOAT_VEC3
#undef GL_FLOAT_VEC4
#undef GL_INT_VEC2
#undef GL_INT_VEC3
#undef GL_INT_VEC4
#undef GL_BOOL
#undef GL_BOOL_VEC2
#undef GL_BOOL_VEC3
#undef GL_BOOL_VEC4
#undef GL_FLOAT_MAT2
#undef GL_FLOAT_MAT3
#undef GL_FLOAT_MAT4
#undef GL_SAMPLER_2D
#undef GL_SAMPLER_CUBE
#undef GL_VERTEX_ATTRIB_ARRAY_ENABLED
#undef GL_VERTEX_ATTRIB_ARRAY_SIZE
#undef GL_VERTEX_ATTRIB_ARRAY_STRIDE
#undef GL_VERTEX_ATTRIB_ARRAY_TYPE
#undef GL_VERTEX_ATTRIB_ARRAY_NORMALIZED
#undef GL_VERTEX_ATTRIB_ARRAY_POINTER
#undef GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING
#undef GL_IMPLEMENTATION_COLOR_READ_TYPE
#undef GL_IMPLEMENTATION_COLOR_READ_FORMAT
#undef GL_COMPILE_STATUS
#undef GL_INFO_LOG_LENGTH
#undef GL_SHADER_SOURCE_LENGTH
#undef GL_SHADER_COMPILER
#undef GL_SHADER_BINARY_FORMATS
#undef GL_NUM_SHADER_BINARY_FORMATS
#undef GL_LOW_FLOAT
#undef GL_MEDIUM_FLOAT
#undef GL_HIGH_FLOAT
#undef GL_LOW_INT
#undef GL_MEDIUM_INT
#undef GL_HIGH_INT
#undef GL_FRAMEBUFFER
#undef GL_RENDERBUFFER
#undef GL_RGBA4
#undef GL_RGB5_A1
#undef GL_RGB565
#undef GL_DEPTH_COMPONENT16
#undef GL_STENCIL_INDEX
#undef GL_STENCIL_INDEX8
#undef GL_RENDERBUFFER_WIDTH
#undef GL_RENDERBUFFER_HEIGHT
#undef GL_RENDERBUFFER_INTERNAL_FORMAT
#undef GL_RENDERBUFFER_RED_SIZE
#undef GL_RENDERBUFFER_GREEN_SIZE
#undef GL_RENDERBUFFER_BLUE_SIZE
#undef GL_RENDERBUFFER_ALPHA_SIZE
#undef GL_RENDERBUFFER_DEPTH_SIZE
#undef GL_RENDERBUFFER_STENCIL_SIZE
#undef GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE
#undef GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME
#undef GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL
#undef GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE
#undef GL_COLOR_ATTACHMENT0
#undef GL_DEPTH_ATTACHMENT
#undef GL_STENCIL_ATTACHMENT
#undef GL_NONE
#undef GL_FRAMEBUFFER_COMPLETE
#undef GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
#undef GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
#undef GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS
#undef GL_FRAMEBUFFER_UNSUPPORTED
#undef GL_FRAMEBUFFER_BINDING
#undef GL_RENDERBUFFER_BINDING
#undef GL_MAX_RENDERBUFFER_SIZE
#undef GL_INVALID_FRAMEBUFFER_OPERATION
#undef GL_VERTEX_PROGRAM_POINT_SIZE

 const int GL20::GL_ES_VERSION_2_0 = 1;
 const int GL20::GL_DEPTH_BUFFER_BIT = 0x00000100;
 const int GL20::GL_STENCIL_BUFFER_BIT = 0x00000400;
 const int GL20::GL_COLOR_BUFFER_BIT = 0x00004000;
 const int GL20::GL_FALSE = 0;
 const int GL20::GL_TRUE = 1;
 const int GL20::GL_POINTS = 0x0000;
 const int GL20::GL_LINES = 0x0001;
 const int GL20::GL_LINE_LOOP = 0x0002;
 const int GL20::GL_LINE_STRIP = 0x0003;
 const int GL20::GL_TRIANGLES = 0x0004;
 const int GL20::GL_TRIANGLE_STRIP = 0x0005;
 const int GL20::GL_TRIANGLE_FAN = 0x0006;
 const int GL20::GL_ZERO = 0;
 const int GL20::GL_ONE = 1;
 const int GL20::GL_SRC_COLOR = 0x0300;
 const int GL20::GL_ONE_MINUS_SRC_COLOR = 0x0301;
 const int GL20::GL_SRC_ALPHA = 0x0302;
 const int GL20::GL_ONE_MINUS_SRC_ALPHA = 0x0303;
 const int GL20::GL_DST_ALPHA = 0x0304;
 const int GL20::GL_ONE_MINUS_DST_ALPHA = 0x0305;
 const int GL20::GL_DST_COLOR = 0x0306;
 const int GL20::GL_ONE_MINUS_DST_COLOR = 0x0307;
 const int GL20::GL_SRC_ALPHA_SATURATE = 0x0308;
 const int GL20::GL_FUNC_ADD = 0x8006;
 const int GL20::GL_BLEND_EQUATION = 0x8009;
 const int GL20::GL_BLEND_EQUATION_RGB = 0x8009;
 const int GL20::GL_BLEND_EQUATION_ALPHA = 0x883D;
 const int GL20::GL_FUNC_SUBTRACT = 0x800A;
 const int GL20::GL_FUNC_REVERSE_SUBTRACT = 0x800B;
 const int GL20::GL_BLEND_DST_RGB = 0x80C8;
 const int GL20::GL_BLEND_SRC_RGB = 0x80C9;
 const int GL20::GL_BLEND_DST_ALPHA = 0x80CA;
 const int GL20::GL_BLEND_SRC_ALPHA = 0x80CB;
 const int GL20::GL_CONSTANT_COLOR = 0x8001;
 const int GL20::GL_ONE_MINUS_CONSTANT_COLOR = 0x8002;
 const int GL20::GL_CONSTANT_ALPHA = 0x8003;
 const int GL20::GL_ONE_MINUS_CONSTANT_ALPHA = 0x8004;
 const int GL20::GL_BLEND_COLOR = 0x8005;
 const int GL20::GL_ARRAY_BUFFER = 0x8892;
 const int GL20::GL_ELEMENT_ARRAY_BUFFER = 0x8893;
 const int GL20::GL_ARRAY_BUFFER_BINDING = 0x8894;
 const int GL20::GL_ELEMENT_ARRAY_BUFFER_BINDING = 0x8895;
 const int GL20::GL_STREAM_DRAW = 0x88E0;
 const int GL20::GL_STATIC_DRAW = 0x88E4;
 const int GL20::GL_DYNAMIC_DRAW = 0x88E8;
 const int GL20::GL_BUFFER_SIZE = 0x8764;
 const int GL20::GL_BUFFER_USAGE = 0x8765;
 const int GL20::GL_CURRENT_VERTEX_ATTRIB = 0x8626;
 const int GL20::GL_FRONT = 0x0404;
 const int GL20::GL_BACK = 0x0405;
 const int GL20::GL_FRONT_AND_BACK = 0x0408;
 const int GL20::GL_TEXTURE_2D = 0x0DE1;
 const int GL20::GL_CULL_FACE = 0x0B44;
 const int GL20::GL_BLEND = 0x0BE2;
 const int GL20::GL_DITHER = 0x0BD0;
 const int GL20::GL_STENCIL_TEST = 0x0B90;
 const int GL20::GL_DEPTH_TEST = 0x0B71;
 const int GL20::GL_SCISSOR_TEST = 0x0C11;
 const int GL20::GL_POLYGON_OFFSET_FILL = 0x8037;
 const int GL20::GL_SAMPLE_ALPHA_TO_COVERAGE = 0x809E;
 const int GL20::GL_SAMPLE_COVERAGE = 0x80A0;
 const int GL20::GL_NO_ERROR = 0;
 const int GL20::GL_INVALID_ENUM = 0x0500;
 const int GL20::GL_INVALID_VALUE = 0x0501;
 const int GL20::GL_INVALID_OPERATION = 0x0502;
 const int GL20::GL_OUT_OF_MEMORY = 0x0505;
 const int GL20::GL_CW = 0x0900;
 const int GL20::GL_CCW = 0x0901;
 const int GL20::GL_LINE_WIDTH = 0x0B21;
 const int GL20::GL_ALIASED_POINT_SIZE_RANGE = 0x846D;
 const int GL20::GL_ALIASED_LINE_WIDTH_RANGE = 0x846E;
 const int GL20::GL_CULL_FACE_MODE = 0x0B45;
 const int GL20::GL_FRONT_FACE = 0x0B46;
 const int GL20::GL_DEPTH_RANGE = 0x0B70;
 const int GL20::GL_DEPTH_WRITEMASK = 0x0B72;
 const int GL20::GL_DEPTH_CLEAR_VALUE = 0x0B73;
 const int GL20::GL_DEPTH_FUNC = 0x0B74;
 const int GL20::GL_STENCIL_CLEAR_VALUE = 0x0B91;
 const int GL20::GL_STENCIL_FUNC = 0x0B92;
 const int GL20::GL_STENCIL_FAIL = 0x0B94;
 const int GL20::GL_STENCIL_PASS_DEPTH_FAIL = 0x0B95;
 const int GL20::GL_STENCIL_PASS_DEPTH_PASS = 0x0B96;
 const int GL20::GL_STENCIL_REF = 0x0B97;
 const int GL20::GL_STENCIL_VALUE_MASK = 0x0B93;
 const int GL20::GL_STENCIL_WRITEMASK = 0x0B98;
 const int GL20::GL_STENCIL_BACK_FUNC = 0x8800;
 const int GL20::GL_STENCIL_BACK_FAIL = 0x8801;
 const int GL20::GL_STENCIL_BACK_PASS_DEPTH_FAIL = 0x8802;
 const int GL20::GL_STENCIL_BACK_PASS_DEPTH_PASS = 0x8803;
 const int GL20::GL_STENCIL_BACK_REF = 0x8CA3;
 const int GL20::GL_STENCIL_BACK_VALUE_MASK = 0x8CA4;
 const int GL20::GL_STENCIL_BACK_WRITEMASK = 0x8CA5;
 const int GL20::GL_VIEWPORT = 0x0BA2;
 const int GL20::GL_SCISSOR_BOX = 0x0C10;
 const int GL20::GL_COLOR_CLEAR_VALUE = 0x0C22;
 const int GL20::GL_COLOR_WRITEMASK = 0x0C23;
 const int GL20::GL_UNPACK_ALIGNMENT = 0x0CF5;
 const int GL20::GL_PACK_ALIGNMENT = 0x0D05;
 const int GL20::GL_MAX_TEXTURE_SIZE = 0x0D33;
 const int GL20::GL_MAX_VIEWPORT_DIMS = 0x0D3A;
 const int GL20::GL_SUBPIXEL_BITS = 0x0D50;
 const int GL20::GL_RED_BITS = 0x0D52;
 const int GL20::GL_GREEN_BITS = 0x0D53;
 const int GL20::GL_BLUE_BITS = 0x0D54;
 const int GL20::GL_ALPHA_BITS = 0x0D55;
 const int GL20::GL_DEPTH_BITS = 0x0D56;
 const int GL20::GL_STENCIL_BITS = 0x0D57;
 const int GL20::GL_POLYGON_OFFSET_UNITS = 0x2A00;
 const int GL20::GL_POLYGON_OFFSET_FACTOR = 0x8038;
 const int GL20::GL_TEXTURE_BINDING_2D = 0x8069;
 const int GL20::GL_SAMPLE_BUFFERS = 0x80A8;
 const int GL20::GL_SAMPLES = 0x80A9;
 const int GL20::GL_SAMPLE_COVERAGE_VALUE = 0x80AA;
 const int GL20::GL_SAMPLE_COVERAGE_INVERT = 0x80AB;
 const int GL20::GL_NUM_COMPRESSED_TEXTURE_FORMATS = 0x86A2;
 const int GL20::GL_COMPRESSED_TEXTURE_FORMATS = 0x86A3;
 const int GL20::GL_DONT_CARE = 0x1100;
 const int GL20::GL_FASTEST = 0x1101;
 const int GL20::GL_NICEST = 0x1102;
 const int GL20::GL_GENERATE_MIPMAP_HINT = 0x8192;
 const int GL20::GL_BYTE = 0x1400;
 const int GL20::GL_UNSIGNED_BYTE = 0x1401;
 const int GL20::GL_SHORT = 0x1402;
 const int GL20::GL_UNSIGNED_SHORT = 0x1403;
 const int GL20::GL_INT = 0x1404;
 const int GL20::GL_UNSIGNED_INT = 0x1405;
 const int GL20::GL_FLOAT = 0x1406;
 const int GL20::GL_FIXED = 0x140C;
 const int GL20::GL_DEPTH_COMPONENT = 0x1902;
 const int GL20::GL_ALPHA = 0x1906;
 const int GL20::GL_RGB = 0x1907;
 const int GL20::GL_RGBA = 0x1908;
 const int GL20::GL_LUMINANCE = 0x1909;
 const int GL20::GL_LUMINANCE_ALPHA = 0x190A;
 const int GL20::GL_UNSIGNED_SHORT_4_4_4_4 = 0x8033;
 const int GL20::GL_UNSIGNED_SHORT_5_5_5_1 = 0x8034;
 const int GL20::GL_UNSIGNED_SHORT_5_6_5 = 0x8363;
 const int GL20::GL_FRAGMENT_SHADER = 0x8B30;
 const int GL20::GL_VERTEX_SHADER = 0x8B31;
 const int GL20::GL_MAX_VERTEX_ATTRIBS = 0x8869;
 const int GL20::GL_MAX_VERTEX_UNIFORM_VECTORS = 0x8DFB;
 const int GL20::GL_MAX_VARYING_VECTORS = 0x8DFC;
 const int GL20::GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = 0x8B4D;
 const int GL20::GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS = 0x8B4C;
 const int GL20::GL_MAX_TEXTURE_IMAGE_UNITS = 0x8872;
 const int GL20::GL_MAX_FRAGMENT_UNIFORM_VECTORS = 0x8DFD;
 const int GL20::GL_SHADER_TYPE = 0x8B4F;
 const int GL20::GL_DELETE_STATUS = 0x8B80;
 const int GL20::GL_LINK_STATUS = 0x8B82;
 const int GL20::GL_VALIDATE_STATUS = 0x8B83;
 const int GL20::GL_ATTACHED_SHADERS = 0x8B85;
 const int GL20::GL_ACTIVE_UNIFORMS = 0x8B86;
 const int GL20::GL_ACTIVE_UNIFORM_MAX_LENGTH = 0x8B87;
 const int GL20::GL_ACTIVE_ATTRIBUTES = 0x8B89;
 const int GL20::GL_ACTIVE_ATTRIBUTE_MAX_LENGTH = 0x8B8A;
 const int GL20::GL_SHADING_LANGUAGE_VERSION = 0x8B8C;
 const int GL20::GL_CURRENT_PROGRAM = 0x8B8D;
 const int GL20::GL_NEVER = 0x0200;
 const int GL20::GL_LESS = 0x0201;
 const int GL20::GL_EQUAL = 0x0202;
 const int GL20::GL_LEQUAL = 0x0203;
 const int GL20::GL_GREATER = 0x0204;
 const int GL20::GL_NOTEQUAL = 0x0205;
 const int GL20::GL_GEQUAL = 0x0206;
 const int GL20::GL_ALWAYS = 0x0207;
 const int GL20::GL_KEEP = 0x1E00;
 const int GL20::GL_REPLACE = 0x1E01;
 const int GL20::GL_INCR = 0x1E02;
 const int GL20::GL_DECR = 0x1E03;
 const int GL20::GL_INVERT = 0x150A;
 const int GL20::GL_INCR_WRAP = 0x8507;
 const int GL20::GL_DECR_WRAP = 0x8508;
 const int GL20::GL_VENDOR = 0x1F00;
 const int GL20::GL_RENDERER = 0x1F01;
 const int GL20::GL_VERSION = 0x1F02;
 const int GL20::GL_EXTENSIONS = 0x1F03;
 const int GL20::GL_NEAREST = 0x2600;
 const int GL20::GL_LINEAR = 0x2601;
 const int GL20::GL_NEAREST_MIPMAP_NEAREST = 0x2700;
 const int GL20::GL_LINEAR_MIPMAP_NEAREST = 0x2701;
 const int GL20::GL_NEAREST_MIPMAP_LINEAR = 0x2702;
 const int GL20::GL_LINEAR_MIPMAP_LINEAR = 0x2703;
 const int GL20::GL_TEXTURE_MAG_FILTER = 0x2800;
 const int GL20::GL_TEXTURE_MIN_FILTER = 0x2801;
 const int GL20::GL_TEXTURE_WRAP_S = 0x2802;
 const int GL20::GL_TEXTURE_WRAP_T = 0x2803;
 const int GL20::GL_TEXTURE = 0x1702;
 const int GL20::GL_TEXTURE_CUBE_MAP = 0x8513;
 const int GL20::GL_TEXTURE_BINDING_CUBE_MAP = 0x8514;
 const int GL20::GL_TEXTURE_CUBE_MAP_POSITIVE_X = 0x8515;
 const int GL20::GL_TEXTURE_CUBE_MAP_NEGATIVE_X = 0x8516;
 const int GL20::GL_TEXTURE_CUBE_MAP_POSITIVE_Y = 0x8517;
 const int GL20::GL_TEXTURE_CUBE_MAP_NEGATIVE_Y = 0x8518;
 const int GL20::GL_TEXTURE_CUBE_MAP_POSITIVE_Z = 0x8519;
 const int GL20::GL_TEXTURE_CUBE_MAP_NEGATIVE_Z = 0x851A;
 const int GL20::GL_MAX_CUBE_MAP_TEXTURE_SIZE = 0x851C;
 const int GL20::GL_TEXTURE0 = 0x84C0;
 const int GL20::GL_TEXTURE1 = 0x84C1;
 const int GL20::GL_TEXTURE2 = 0x84C2;
 const int GL20::GL_TEXTURE3 = 0x84C3;
 const int GL20::GL_TEXTURE4 = 0x84C4;
 const int GL20::GL_TEXTURE5 = 0x84C5;
 const int GL20::GL_TEXTURE6 = 0x84C6;
 const int GL20::GL_TEXTURE7 = 0x84C7;
 const int GL20::GL_TEXTURE8 = 0x84C8;
 const int GL20::GL_TEXTURE9 = 0x84C9;
 const int GL20::GL_TEXTURE10 = 0x84CA;
 const int GL20::GL_TEXTURE11 = 0x84CB;
 const int GL20::GL_TEXTURE12 = 0x84CC;
 const int GL20::GL_TEXTURE13 = 0x84CD;
 const int GL20::GL_TEXTURE14 = 0x84CE;
 const int GL20::GL_TEXTURE15 = 0x84CF;
 const int GL20::GL_TEXTURE16 = 0x84D0;
 const int GL20::GL_TEXTURE17 = 0x84D1;
 const int GL20::GL_TEXTURE18 = 0x84D2;
 const int GL20::GL_TEXTURE19 = 0x84D3;
 const int GL20::GL_TEXTURE20 = 0x84D4;
 const int GL20::GL_TEXTURE21 = 0x84D5;
 const int GL20::GL_TEXTURE22 = 0x84D6;
 const int GL20::GL_TEXTURE23 = 0x84D7;
 const int GL20::GL_TEXTURE24 = 0x84D8;
 const int GL20::GL_TEXTURE25 = 0x84D9;
 const int GL20::GL_TEXTURE26 = 0x84DA;
 const int GL20::GL_TEXTURE27 = 0x84DB;
 const int GL20::GL_TEXTURE28 = 0x84DC;
 const int GL20::GL_TEXTURE29 = 0x84DD;
 const int GL20::GL_TEXTURE30 = 0x84DE;
 const int GL20::GL_TEXTURE31 = 0x84DF;
 const int GL20::GL_ACTIVE_TEXTURE = 0x84E0;
 const int GL20::GL_REPEAT = 0x2901;
 const int GL20::GL_CLAMP_TO_EDGE = 0x812F;
 const int GL20::GL_MIRRORED_REPEAT = 0x8370;
 const int GL20::GL_FLOAT_VEC2 = 0x8B50;
 const int GL20::GL_FLOAT_VEC3 = 0x8B51;
 const int GL20::GL_FLOAT_VEC4 = 0x8B52;
 const int GL20::GL_INT_VEC2 = 0x8B53;
 const int GL20::GL_INT_VEC3 = 0x8B54;
 const int GL20::GL_INT_VEC4 = 0x8B55;
 const int GL20::GL_BOOL = 0x8B56;
 const int GL20::GL_BOOL_VEC2 = 0x8B57;
 const int GL20::GL_BOOL_VEC3 = 0x8B58;
 const int GL20::GL_BOOL_VEC4 = 0x8B59;
 const int GL20::GL_FLOAT_MAT2 = 0x8B5A;
 const int GL20::GL_FLOAT_MAT3 = 0x8B5B;
 const int GL20::GL_FLOAT_MAT4 = 0x8B5C;
 const int GL20::GL_SAMPLER_2D = 0x8B5E;
 const int GL20::GL_SAMPLER_CUBE = 0x8B60;
 const int GL20::GL_VERTEX_ATTRIB_ARRAY_ENABLED = 0x8622;
 const int GL20::GL_VERTEX_ATTRIB_ARRAY_SIZE = 0x8623;
 const int GL20::GL_VERTEX_ATTRIB_ARRAY_STRIDE = 0x8624;
 const int GL20::GL_VERTEX_ATTRIB_ARRAY_TYPE = 0x8625;
 const int GL20::GL_VERTEX_ATTRIB_ARRAY_NORMALIZED = 0x886A;
 const int GL20::GL_VERTEX_ATTRIB_ARRAY_POINTER = 0x8645;
 const int GL20::GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = 0x889F;
 const int GL20::GL_IMPLEMENTATION_COLOR_READ_TYPE = 0x8B9A;
 const int GL20::GL_IMPLEMENTATION_COLOR_READ_FORMAT = 0x8B9B;
 const int GL20::GL_COMPILE_STATUS = 0x8B81;
 const int GL20::GL_INFO_LOG_LENGTH = 0x8B84;
 const int GL20::GL_SHADER_SOURCE_LENGTH = 0x8B88;
 const int GL20::GL_SHADER_COMPILER = 0x8DFA;
 const int GL20::GL_SHADER_BINARY_FORMATS = 0x8DF8;
 const int GL20::GL_NUM_SHADER_BINARY_FORMATS = 0x8DF9;
 const int GL20::GL_LOW_FLOAT = 0x8DF0;
 const int GL20::GL_MEDIUM_FLOAT = 0x8DF1;
 const int GL20::GL_HIGH_FLOAT = 0x8DF2;
 const int GL20::GL_LOW_INT = 0x8DF3;
 const int GL20::GL_MEDIUM_INT = 0x8DF4;
 const int GL20::GL_HIGH_INT = 0x8DF5;
 const int GL20::GL_FRAMEBUFFER = 0x8D40;
 const int GL20::GL_RENDERBUFFER = 0x8D41;
 const int GL20::GL_RGBA4 = 0x8056;
 const int GL20::GL_RGB5_A1 = 0x8057;
 const int GL20::GL_RGB565 = 0x8D62;
 const int GL20::GL_DEPTH_COMPONENT16 = 0x81A5;
 const int GL20::GL_STENCIL_INDEX = 0x1901;
 const int GL20::GL_STENCIL_INDEX8 = 0x8D48;
 const int GL20::GL_RENDERBUFFER_WIDTH = 0x8D42;
 const int GL20::GL_RENDERBUFFER_HEIGHT = 0x8D43;
 const int GL20::GL_RENDERBUFFER_INTERNAL_FORMAT = 0x8D44;
 const int GL20::GL_RENDERBUFFER_RED_SIZE = 0x8D50;
 const int GL20::GL_RENDERBUFFER_GREEN_SIZE = 0x8D51;
 const int GL20::GL_RENDERBUFFER_BLUE_SIZE = 0x8D52;
 const int GL20::GL_RENDERBUFFER_ALPHA_SIZE = 0x8D53;
 const int GL20::GL_RENDERBUFFER_DEPTH_SIZE = 0x8D54;
 const int GL20::GL_RENDERBUFFER_STENCIL_SIZE = 0x8D55;
 const int GL20::GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE = 0x8CD0;
 const int GL20::GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME = 0x8CD1;
 const int GL20::GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL = 0x8CD2;
 const int GL20::GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE = 0x8CD3;
 const int GL20::GL_COLOR_ATTACHMENT0 = 0x8CE0;
 const int GL20::GL_DEPTH_ATTACHMENT = 0x8D00;
 const int GL20::GL_STENCIL_ATTACHMENT = 0x8D20;
 const int GL20::GL_NONE = 0;
 const int GL20::GL_FRAMEBUFFER_COMPLETE = 0x8CD5;
 const int GL20::GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT = 0x8CD6;
 const int GL20::GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = 0x8CD7;
 const int GL20::GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS = 0x8CD9;
 const int GL20::GL_FRAMEBUFFER_UNSUPPORTED = 0x8CDD;
 const int GL20::GL_FRAMEBUFFER_BINDING = 0x8CA6;
 const int GL20::GL_RENDERBUFFER_BINDING = 0x8CA7;
 const int GL20::GL_MAX_RENDERBUFFER_SIZE = 0x84E8;
 const int GL20::GL_INVALID_FRAMEBUFFER_OPERATION = GL_INVALID_FRAMEBUFFER_OPERATION;
 const int GL20::GL_VERTEX_PROGRAM_POINT_SIZE = 0x8642;

// Extensions
 const int GL20::GL_COVERAGE_BUFFER_BIT_NV = 0x8000;

void GL20::glAttachShader(int program, int shader) const
{
	::glAttachShader(program, shader);
}

void GL20::glBindAttribLocation(int program, int index, const string& name) const
{
	::glBindAttribLocation(program, index, name.c_str());
}

void GL20::glBindBuffer (int target,int buffer) const
{
	::glBindBuffer(target, buffer);
}

void GL20::glBindFramebuffer (int target,int framebuffer) const
{
	::glBindFramebuffer(target, framebuffer);
}

void GL20::glBindRenderbuffer (int target,int renderbuffer) const
{
	::glBindRenderbuffer(target, renderbuffer);
}
void GL20::glBlendColor (float red,float green,float blue,float alpha) const
{
	::glBlendColor(red, green, blue, alpha);
}
void GL20::glBlendEquation (int mode) const
{
	::glBlendEquation(mode);
}
void GL20::glBlendEquationSeparate (int modeRGB,int modeAlpha) const
{
	::glBlendEquationSeparate(modeRGB, modeAlpha);
}
void GL20::glBlendFuncSeparate (int srcRGB,int dstRGB,int srcAlpha,int dstAlpha) const
{
	::glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}
void GL20::glBufferData (int target,int size,const char* data,int usage) const
{
	::glBufferData(target, size, data, usage);
}
void GL20::glBufferSubData (int target,int offset,int size,const char* data) const
{
	::glBufferSubData(target, offset, size, data);
}
int GL20::glCheckFramebufferStatus (int target) const
{
	return ::glCheckFramebufferStatus(target);
}
void GL20::glCompileShader (int shader) const
{
	::glCompileShader(shader);
}
int GL20::glCreateProgram () const
{
	return ::glCreateProgram();
}
int GL20::glCreateShader (int type) const
{
	return ::glCreateShader(type);
}
void GL20::glDeleteBuffers(int n, unsigned int* buffers) const
{
	::glDeleteBuffers(n, buffers);
}
void GL20::glDeleteFramebuffers (int n,const unsigned int* framebuffers) const
{
	::glDeleteFramebuffers(n, framebuffers);
}
void GL20::glDeleteProgram (int program) const
{
	::glDeleteProgram(program);
}
void GL20::glDeleteRenderbuffers (int n,const unsigned int* renderbuffers) const
{
	::glDeleteRenderbuffers(n, renderbuffers);
}
void GL20::glDeleteShader (int shader) const
{
	::glDeleteShader(shader);
}
void GL20::glDetachShader (int program,int shader) const
{
	::glDetachShader(program, shader);
}
void GL20::glDisableVertexAttribArray (int index) const
{
	::glDisableVertexAttribArray(index);
}
void GL20::glDrawElements (int mode,int count,int type, const void* indices) const
{
	::glDrawElements(mode, count, type, indices);
}
void GL20::glEnableVertexAttribArray (int index) const
{
	::glEnableVertexAttribArray(index);
}
void GL20::glFramebufferRenderbuffer (int target,int attachment,int renderbuffertarget,int renderbuffer) const
{
	::glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}
void GL20::glFramebufferTexture2D (int target,int attachment,int textarget,int texture,int level) const
{
	::glFramebufferTexture2D(target, attachment, textarget, texture, level);
}
void GL20::glGenBuffers (int n, unsigned int* buffers) const
{

	::glGenBuffers(n, buffers);
}
void GL20::glGenerateMipmap (int target) const
{
	::glGenerateMipmap(target);
}
void GL20::glGenFramebuffers (int n, unsigned int* framebuffers) const
{
	::glGenFramebuffers(n, framebuffers);
}
void GL20::glGenRenderbuffers (int n, unsigned int* renderbuffers) const
{
	::glGenRenderbuffers(n, renderbuffers);
}

std::string GL20::glGetActiveAttrib (int program,int index, const int* size, const char* type) const
{
	GLint max_length;
	glGetProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max_length);
	char* buf = new char[max_length + 1];
	::glGetActiveAttrib(program, index, max_length + 1, NULL, (int *) size, (unsigned int*)type, buf);
	return buf;
}

std::string GL20::glGetActiveUniform (int program,int index,const int* size,const char* type) const
{
	GLint max_length;
	glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length);
	char* buf = new char[max_length + 1];
	::glGetActiveUniform(program, index, max_length + 1, NULL, (int*) size, (unsigned int*) type, buf);
	return buf;
}

void GL20::glGetAttachedShaders (int program,int maxcount, int* count, unsigned int* shaders) const
{
	::glGetAttachedShaders(program, maxcount, count, shaders);
}
int GL20::glGetAttribLocation (int program, const char* name) const
{
	return ::glGetAttribLocation(program, name);
}
void GL20::glGetBooleanv (unsigned int pname, unsigned char* params) const
{
	::glGetBooleanv(pname, params);
}
void GL20::glGetBufferParameteriv (unsigned int target, unsigned int pname, int* params) const
{
	::glGetBufferParameteriv(target, pname, params);
}
void GL20::glGetFloatv (int pname, float* params) const
{
	::glGetFloatv(pname, params);
}
void GL20::glGetFramebufferAttachmentParameteriv (int target,int attachment,int pname, int* params) const
{
	::glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}
void GL20::glGetProgramiv (int program, int pname, int* params) const
{
	::glGetProgramiv(program, pname, params);
}
std::string GL20::glGetProgramInfoLog (int program) const
{
	char buf[512];
	int length = 0;
	::glGetProgramInfoLog(program, 512, &length, buf);
	return string(buf);
}

void GL20::glGetRenderbufferParameteriv (int target,int pname, int* params) const
{
	::glGetRenderbufferParameteriv(target, pname, params);
}
void GL20::glGetShaderiv (int shader,int pname, int* params) const
{
	::glGetShaderiv(shader, pname, params);
}

std::string GL20::glGetShaderInfoLog (int shader) const
{
	int length = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
	char buf[length];
	::glGetShaderInfoLog(shader, length, NULL, buf);
	return buf;
}
void GL20::glGetShaderPrecisionFormat (int shadertype,int precisiontype, int* range, int* precision) const
{
	::glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
}
void GL20::glGetShaderSource (unsigned int shader,int bufsize, int* length, char* source) const
{
	::glGetShaderSource(shader, bufsize, length, source);
}
void GL20::glGetTexParameterfv (int target,int pname, float* params) const
{
	::glGetTexParameterfv(target, pname, params);
}
void GL20::glGetTexParameteriv (int target,int pname, int* params) const
{
	::glGetTexParameteriv(target, pname, params);
}
void GL20::glGetUniformfv (int program,int location, float* params) const
{
	::glGetUniformfv(program, location, params);
}
void GL20::glGetUniformiv (int program,int location, int* params) const
{
	::glGetUniformiv(program, location, params);
}
int GL20::glGetUniformLocation (int program,const std::string& name) const
{
	return ::glGetUniformLocation(program, name.c_str());
}
void GL20::glGetVertexAttribfv (int index,int pname, float* params) const
{
	::glGetVertexAttribfv(index, pname, params);
}
void GL20::glGetVertexAttribiv (int index,int pname, int* params) const
{
	::glGetVertexAttribiv(index, pname, params);
}
void GL20::glGetVertexAttribPointerv (int index,int pname, void* pointer) const
{
	::glGetVertexAttribPointerv(index, pname, &pointer);
}
bool GL20::glIsBuffer (int buffer) const
{
	return ::glIsBuffer(buffer);
}
bool GL20::glIsEnabled (int cap) const
{
	return ::glIsEnabled(cap);
}
bool GL20::glIsFramebuffer (int framebuffer) const
{
	return ::glIsFramebuffer(framebuffer);
}
bool GL20::glIsProgram (int program) const
{
	return ::glIsProgram(program);
}
bool GL20::glIsRenderbuffer (int renderbuffer) const
{
	return ::glIsRenderbuffer(renderbuffer);
}
bool GL20::glIsShader (int shader) const
{
	return ::glIsShader(shader);
}
bool GL20::glIsTexture (int texture) const
{
	return ::glIsTexture(texture);
}
void GL20::glLinkProgram (int program) const
{
	::glLinkProgram(program);
}
void GL20::glReleaseShaderCompiler () const
{
	::glReleaseShaderCompiler();
}
void GL20::glRenderbufferStorage (int target,int internalformat,int width,int height) const
{
	::glRenderbufferStorage(target, internalformat, width, height);
}
void GL20::glSampleCoverage (float value,bool invert) const
{
	::glSampleCoverage(value, invert);
}
void GL20::glShaderBinary (int n,const unsigned int* shaders, int binaryformat,const void* binary,int length) const
{
	::glShaderBinary(n, shaders, binaryformat, binary, length);
}

void GL20::glShaderSource (int shader, const std::string& shaderString) const
{
	int length = shaderString.size();
	const char* buf = shaderString.c_str();
	::glShaderSource(shader, 1, &buf, &length);
}
void GL20::glStencilFuncSeparate (int face,int func,int ref,int mask) const
{
	::glStencilFuncSeparate(face, func, ref, mask);
}
void GL20::glStencilMaskSeparate (int face,int mask) const
{
	::glStencilMaskSeparate(face, mask);
}
void GL20::glStencilOpSeparate (int face,int fail,int zfail,int zpass) const
{
	::glStencilOpSeparate(face, fail, zfail, zpass);
}
void GL20::glTexParameterfv (int target,int pname,const float* params) const
{
	::glTexParameterfv(target, pname, params);
}
void GL20::glTexParameteri (int target,int pname,int param) const
{
	::glTexParameteri(target, pname, param);
}
void GL20::glTexParameteriv (int target,int pname,const int* params) const
{
	::glTexParameteriv(target, pname, params);
}
void GL20::glUniform1f (int location,float x) const
{
	::glUniform1f(location, x);
}
void GL20::glUniform1fv (int location,int count,const float* v) const
{
	::glUniform1fv(location, count, v);
}
void GL20::glUniform1i (int location,int x) const
{
	::glUniform1i(location, x);
}
void GL20::glUniform1iv (int location,int count,const int* v) const
{
	::glUniform1iv(location, count, v);
}
void GL20::glUniform2f (int location,float x,float y) const
{
	::glUniform2f(location, x, y);
}
void GL20::glUniform2fv (int location,int count,const float* v) const
{
	::glUniform2fv(location, count, v);
}
void GL20::glUniform2i (int location,int x,int y) const
{
	::glUniform2i(location, x, y);
}
void GL20::glUniform2iv (int location,int count,const int* v) const
{
	::glUniform2iv(location, count, v);
}
void GL20::glUniform3f (int location,float x,float y,float z) const
{
	::glUniform3f(location, x, y, z);
}
void GL20::glUniform3fv (int location,int count,const float* v) const
{
	::glUniform3fv(location, count, v);
}
void GL20::glUniform3i (int location,int x,int y,int z) const
{
	::glUniform3i(location, x, y, z);
}
void GL20::glUniform3iv (int location,int count,const int* v) const
{
	::glUniform3iv(location, count, v);
}
void GL20::glUniform4f (int location,float x,float y,float z,float w) const
{
	::glUniform4f(location, x, y, z, w);
}
void GL20::glUniform4fv (int location,int count,const float* v) const
{
	::glUniform4fv(location, count, v);
}
void GL20::glUniform4i (int location,int x,int y,int z,int w) const
{
	::glUniform4i(location, x, y, z, w);
}
void GL20::glUniform4iv (int location,int count,const int* v) const
{
	::glUniform4iv(location, count, v);
}
void GL20::glUniformMatrix2fv (int location,int count,bool transpose,const float* value) const
{
	::glUniformMatrix2fv(location, count, transpose, value);
}
void GL20::glUniformMatrix3fv (int location,int count,bool transpose,const float* value) const
{
	::glUniformMatrix3fv(location, count, transpose, value);
}
void GL20::glUniformMatrix4fv (int location,int count,bool transpose,const float* value) const
{
	::glUniformMatrix4fv(location, count, transpose, value);
}
void GL20::glUseProgram (int program) const
{
	::glUseProgram(program);
}
void GL20::glValidateProgram (int program) const
{
	::glValidateProgram(program);
}
void GL20::glVertexAttrib1f (int indx,float x) const
{
	::glVertexAttrib1f(indx, x);
}
void GL20::glVertexAttrib1fv (int indx,const float* values) const
{
	::glVertexAttrib1fv(indx, values);
}
void GL20::glVertexAttrib2f (int indx,float x,float y) const
{
	::glVertexAttrib2f(indx, x, y);
}
void GL20::glVertexAttrib2fv (int indx,const float* values) const
{
	::glVertexAttrib2fv(indx, values);
}
void GL20::glVertexAttrib3f (int indx,float x,float y,float z) const
{
	::glVertexAttrib3f(indx, x, y, z);
}
void GL20::glVertexAttrib3fv (int indx,const float* values) const
{
	::glVertexAttrib3fv(indx, values);
}
void GL20::glVertexAttrib4f (int indx,float x,float y,float z,float w) const
{
	::glVertexAttrib4f(indx, x, y, z, w);
}
void GL20::glVertexAttrib4fv (int indx,const float* values) const
{
	::glVertexAttrib4fv(indx, values);
}
void GL20::glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,const void* ptr) const
{
	::glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
}
void GL20::glVertexAttribPointer (int indx,int size,int type,bool normalized,int stride,int ptr) const
{
	::glVertexAttribPointer(indx, size, type, normalized, stride, (void*)ptr);
}
