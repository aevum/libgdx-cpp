
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

#include "TileMapRenderer.hpp"

using namespace gdx_cpp::graphics::g2d::tiled;

void TileMapRenderer::init (const TileAtlas& atlas,int tileWidth,int tileHeight,float unitsPerTileX,float unitsPerTileY,const gdx_cpp::utils::IntArray& blendedTiles,int tilesPerBlockX,int tilesPerBlockY,const gdx_cpp::graphics::glutils::ShaderProgram& shader) {
    this.atlas = atlas;
    this.tileWidth = tileWidth;
    this.tileHeight = tileHeight;
    this.unitsPerTileX = unitsPerTileX;
    this.unitsPerTileY = unitsPerTileY;

    this.blendedTiles = blendedTiles;
    this.tilesPerBlockX = tilesPerBlockX;
    this.tilesPerBlockY = tilesPerBlockY;

    unitsPerBlockX = unitsPerTileX * tilesPerBlockX;
    unitsPerBlockY = unitsPerTileY * tilesPerBlockY;

    isSimpleTileAtlas = atlas instanceof SimpleTileAtlas;

    int layer, row, col;

    allLayers = new int[map.length];

    // Calculate maximum cache size and map height in pixels, fill allLayers array
    int maxCacheSize = 0;
    int maxHeight = 0;
    int maxWidth = 0;
    for (layer = 0; layer < map.length; layer++) {
        allLayers[layer] = layer;
        if (map[layer].length > maxHeight) maxHeight = map[layer].length;
        for (row = 0; row < map[layer].length; row++) {
            if (map[layer][row].length > maxWidth) maxWidth = map[layer][row].length;
            for (col = 0; col < map[layer][row].length; col++)
                if (map[layer][row][col] != 0) maxCacheSize++;
        }
    }
    mapHeightUnits = (int)(maxHeight * unitsPerTileY);
    mapWidthUnits = (int)(maxWidth * unitsPerTileX);

    if (shader == null)
        cache = new SpriteCache(maxCacheSize, false);
    else
        cache = new SpriteCache(maxCacheSize, shader, false);

    normalCacheId = new int[map.length][][];
    blendedCacheId = new int[map.length][][];
    for (layer = 0; layer < map.length; layer++) {
        normalCacheId[layer] = new int[(int)MathUtils.ceil((float)map[layer].length / tilesPerBlockY)][];
        blendedCacheId[layer] = new int[(int)MathUtils.ceil((float)map[layer].length / tilesPerBlockY)][];
        for (row = 0; row < normalCacheId[layer].length; row++) {
            normalCacheId[layer][row] = new int[(int)MathUtils.ceil((float)map[layer][row].length / tilesPerBlockX)];
            blendedCacheId[layer][row] = new int[(int)MathUtils.ceil((float)map[layer][row].length / tilesPerBlockX)];
            for (col = 0; col < normalCacheId[layer][row].length; col++) {
                if (isSimpleTileAtlas) {
                    // Everything considered blended
                    blendedCacheId[layer][row][col] = addBlock(map[layer], row, col, false);
                } else {
                    normalCacheId[layer][row][col] = addBlock(map[layer], row, col, false);
                    blendedCacheId[layer][row][col] = addBlock(map[layer], row, col, true);
                }
            }
        }
    }
}

int TileMapRenderer::addBlock (int blockRow,int blockCol,bool blended) {
    cache.beginCache();

    int firstCol = blockCol * tilesPerBlockX;
    int firstRow = blockRow * tilesPerBlockY;
    int lastCol = firstCol + tilesPerBlockX;
    int lastRow = firstRow + tilesPerBlockY;

    for (int row = firstRow; row < lastRow && row < layer.length; row++) {
        for (int col = firstCol; col < lastCol && col < layer[row].length; col++) {
            int tile = layer[row][col];
            if (tile != 0) {
                if (blended == blendedTiles.contains(tile)) {
                    TextureRegion reg = atlas.getRegion(tile);
                    if (reg != null) {
                        if (!isSimpleTileAtlas) {
                            AtlasRegion region = (AtlasRegion)reg;
                            cache.add(region, col * unitsPerTileX, (layer.length - row - 1) * unitsPerTileY, (float)region.offsetX
                                      * unitsPerTileX / tileWidth, (float)(region.offsetY) * unitsPerTileY / (float)tileHeight,
                                      region.packedWidth, region.packedHeight, unitsPerTileX / (float)tileWidth, unitsPerTileY
                                      / (float)tileHeight, (region.rotate) ? 90 : 0);
                        } else {
                            cache.add(reg, col * unitsPerTileX, (layer.length - row - 1) * unitsPerTileY, 0, 0, reg.getRegionWidth(),
                                      reg.getRegionHeight(), unitsPerTileX / tileWidth, unitsPerTileY / tileHeight, 0);
                        }
                    }
                }
            }
        }
    }

    return cache.endCache();
}

void TileMapRenderer::render () {
    render(0, 0, (int)getMapWidthUnits(), (int)(getMapHeightUnits()));
}

void TileMapRenderer::render (float x,float y,float width,float height) {
    render(x, y, width, height, allLayers);
}

void TileMapRenderer::render (const gdx_cpp::graphics::OrthographicCamera& cam) {
    render(cam, allLayers);
}

void TileMapRenderer::render (const gdx_cpp::graphics::OrthographicCamera& cam) {
    getProjectionMatrix().set(cam.combined);
    tmp.set(0, 0, 0);
    cam.unproject(tmp);
    render(tmp.x, tmp.y, cam.viewportWidth * cam.zoom, cam.viewportHeight * cam.zoom, layers);
}

void TileMapRenderer::render (float x,float y,float width,float height) {
    lastRow = (int)((mapHeightUnits - (y - height + overdrawY)) / (unitsPerBlockY));
    initialRow = (int)((mapHeightUnits - (y - overdrawY)) / (unitsPerBlockY));
    initialRow = (initialRow > 0) ? initialRow : 0; // Clamp initial Row > 0

    lastCol = (int)((x + width + overdrawX) / (unitsPerBlockX));
    initialCol = (int)((x - overdrawX) / (unitsPerBlockX));
    initialCol = (initialCol > 0) ? initialCol : 0; // Clamp initial Col > 0

    Gdx.gl.glBlendFunc(GL11.GL_SRC_ALPHA, GL11.GL_ONE_MINUS_SRC_ALPHA);

    cache.begin();
    if (isSimpleTileAtlas) {
        // Without this special case the top left corner doesn't work properly on mutilayered maps
        Gdx.gl.glEnable(GL10.GL_BLEND);
        for (currentLayer = 0; currentLayer < layers.length; currentLayer++) {
            for (currentRow = initialRow; currentRow <= lastRow && currentRow < getLayerHeightInBlocks(currentLayer); currentRow++) {
                for (currentCol = initialCol; currentCol <= lastCol
                        && currentCol < getLayerWidthInBlocks(currentLayer, currentRow); currentCol++) {
                    cache.draw(blendedCacheId[layers[currentLayer]][currentRow][currentCol]);
                }
            }
        }
    } else {
        for (currentLayer = 0; currentLayer < layers.length; currentLayer++) {
            for (currentRow = initialRow; currentRow <= lastRow && currentRow < getLayerHeightInBlocks(currentLayer); currentRow++) {
                for (currentCol = initialCol; currentCol <= lastCol
                        && currentCol < getLayerWidthInBlocks(currentLayer, currentRow); currentCol++) {
                    Gdx.gl.glDisable(GL10.GL_BLEND);
                    cache.draw(normalCacheId[layers[currentLayer]][currentRow][currentCol]);
                    Gdx.gl.glEnable(GL10.GL_BLEND);
                    cache.draw(blendedCacheId[layers[currentLayer]][currentRow][currentCol]);
                }
            }
        }
    }
    cache.end();
    Gdx.gl.glDisable(GL10.GL_BLEND);
}

int TileMapRenderer::getLayerWidthInBlocks (int layer,int row) {
    int normalCacheWidth = 0;
    if (normalCacheId != null && normalCacheId[layer] != null && normalCacheId[layer][row] != null) {
        normalCacheWidth = normalCacheId[layer][row].length;
    }

    int blendedCacheWidth = 0;
    if (blendedCacheId != null && blendedCacheId[layer] != null && blendedCacheId[layer][row] != null) {
        blendedCacheWidth = blendedCacheId[layer][row].length;
    }

    return Math.max(normalCacheWidth, blendedCacheWidth);
}

int TileMapRenderer::getLayerHeightInBlocks (int layer) {
    int normalCacheHeight = 0;
    if (normalCacheId != null && normalCacheId[layer] != null) {
        normalCacheHeight = normalCacheId[layer].length;
    }

    int blendedCacheHeight = 0;
    if (blendedCacheId != null && blendedCacheId[layer] != null) {
        blendedCacheHeight = blendedCacheId[layer].length;
    }

    return Math.max(normalCacheHeight, blendedCacheHeight);
}

gdx_cpp::math::Matrix4& TileMapRenderer::getProjectionMatrix () {
    return cache.getProjectionMatrix();
}

gdx_cpp::math::Matrix4& TileMapRenderer::getTransformMatrix () {
    return cache.getTransformMatrix();
}

int TileMapRenderer::getRow (int worldY) {
    return (int)(worldY / unitsPerTileY);
}

int TileMapRenderer::getCol (int worldX) {
    return (int)(worldX / unitsPerTileX);
}

int TileMapRenderer::getInitialRow () {
    return initialRow;
}

int TileMapRenderer::getInitialCol () {
    return initialCol;
}

int TileMapRenderer::getLastRow () {
    return lastRow;
}

int TileMapRenderer::getLastCol () {
    return lastCol;
}

float TileMapRenderer::getUnitsPerTileX () {
    return unitsPerTileX;
}

float TileMapRenderer::getUnitsPerTileY () {
    return unitsPerTileY;
}

int TileMapRenderer::getMapHeightUnits () {
    return mapHeightUnits;
}

int TileMapRenderer::getMapWidthUnits () {
    return mapWidthUnits;
}

int TileMapRenderer::parseIntWithDefault (const std::string& string,int defaultValue) {
    if (string == null) return defaultValue;
    try {
        return Integer.parseInt(string);
    } catch (NumberFormatException e) {
        return defaultValue;
    }
}

void TileMapRenderer::dispose () {
    cache.dispose();
}

gdx_cpp::utils::IntArray& TileMapRenderer::createFromCSV (const std::string& values) {
    IntArray list = new IntArray(false, (values.length() + 1) / 2);
    StringTokenizer st = new StringTokenizer(values, ",");
    while (st.hasMoreTokens()) {
        list.add(Integer.parseInt(st.nextToken()));
    }
    list.shrink();
    return list;
}

