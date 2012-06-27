
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

#ifndef GDX_CPP_GRAPHICS_G2D_TILED_TILEMAPRENDERER_HPP_
#define GDX_CPP_GRAPHICS_G2D_TILED_TILEMAPRENDERER_HPP_

namespace gdx {

class TileMapRenderer: public Disposable {
public:
    void render ();
    void render (float x,float y,float width,float height);
    void render (const OrthographicCamera& cam);
    void render (const OrthographicCamera& cam);
    void render (float x,float y,float width,float height);
    Matrix4& getProjectionMatrix ();
    Matrix4& getTransformMatrix ();
    int getRow (int worldY);
    int getCol (int worldX);
    int getInitialRow ();
    int getInitialCol ();
    int getLastRow ();
    int getLastCol ();
    float getUnitsPerTileX ();
    float getUnitsPerTileY ();
    int getMapHeightUnits ();
    int getMapWidthUnits ();
    void dispose ();

protected:


private:
    void init (const TileAtlas& atlas,int tileWidth,int tileHeight,float unitsPerTileX,float unitsPerTileY,const IntArray& blendedTiles,int tilesPerBlockX,int tilesPerBlockY,const ShaderProgram& shader);
    int addBlock (int blockRow,int blockCol,bool blended);
    int getLayerWidthInBlocks (int layer,int row);
    int getLayerHeightInBlocks (int layer);
    static int parseIntWithDefault (const std::string& string,int defaultValue);
    static IntArray& createFromCSV (const std::string& values);
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_TILED_TILEMAPRENDERER_HPP_
