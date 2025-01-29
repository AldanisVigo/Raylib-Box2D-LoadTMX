#ifndef TILEMAP_LAYER_H
#define TILEMAP_LAYER_H
#include "Tile.h"
#include <loadtmx.hpp>
#include "TileGrid.h"
#include "TilePalette.h"
#include "CursorController.h"

class TileMapLayer: public Node{
    private:
        int rows;
        int cols;
        float tileSize;
    public:
        Texture2D defaultTileTexture;
        TilePalette* palette;
        TileMapLayer(Vector2,float,int,int,TilePalette*,Camera2D*);
        ~TileMapLayer();
        void PopulateWithTMXAt(char*);
        void FillGridWithEmptyTiles();
        TileGrid* tileGrid;
        void draw();
};

#endif