
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_TABLELAYOUTPARSER_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_TABLELAYOUTPARSER_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace ui {
namespace tablelayout {

class TableLayoutParser {
public:
    void parse (const BaseTableLayout& table,const std::string& input);

protected:


private:
    static char* init__tableLayout_actions_0 ();
    static short* init__tableLayout_key_offsets_0 ();
    static char* init__tableLayout_trans_keys_0 ();
    static char* init__tableLayout_single_lengths_0 ();
    static char* init__tableLayout_range_lengths_0 ();
    static short* init__tableLayout_index_offsets_0 ();
    static char* init__tableLayout_trans_targs_0 ();
    static short* init__tableLayout_trans_actions_0 ();
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace ui
} // namespace tablelayout

#endif // GDX_CPP_SCENES_SCENE2D_UI_TABLELAYOUT_TABLELAYOUTPARSER_HPP_
