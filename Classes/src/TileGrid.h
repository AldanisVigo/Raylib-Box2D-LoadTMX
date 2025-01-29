#ifndef TILEGRID_H
#define TILEGRID_H
#include <vector>
#include "Node.h"
#include "Tile.h"
#include "TilePalette.h"
#include "CursorController.h"

class TileGrid : public Node {
    public:
        Camera2D* camera;
        float tileSize;
        int cols;
        int rows;
        TilePalette* palette;
        vector<vector<Tile>> grid;
        TileGrid() {}
        TileGrid(Vector2,int,int,int,TilePalette *,Camera2D*);
        ~TileGrid();
        void draw();
        b2WorldId worldId;
};

#endif