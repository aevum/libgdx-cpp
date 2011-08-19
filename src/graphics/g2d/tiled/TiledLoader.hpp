
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

#ifndef GDX_CPP_GRAPHICS_G2D_TILED_TILEDLOADER_HPP_
#define GDX_CPP_GRAPHICS_G2D_TILED_TILEDLOADER_HPP_

namespace gdx_cpp {
namespace graphics {
namespace g2d {
namespace tiled {

class TiledLoader {
public:
    static TiledMap& createMap (const gdx_cpp::files::FileHandle& tmxFile);

protected:
    void open (const std::string& name);
    void attribute (const std::string& name,const std::string& value);
    void text (const std::string& text);
    void close ();

private:
    void putProperty (const Property& property);
    void fromCSV ();
    void arrangeData ();
    void unZlib ();
    void unGZip ();
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d
} // namespace tiled

#endif // GDX_CPP_GRAPHICS_G2D_TILED_TILEDLOADER_HPP_
