#ifndef TILE_H
#define TILE_H
#include "Sprite.h"
#include "CursorController.h"

class Tile {
    public:
        CursorController* cursorController;
        int tileId = -1;
        Sprite sprite;
        Texture2D texture;
        bool emptyTile;
        b2WorldId* worldId;
        Vector2 position;
        int tileSize;
        // Default constructor
        // Tile() : tileId(0), emptyTile(true), worldId(nullptr), position{0.0f, 0.0f} {
        //     sprite = Sprite();
        // }
        Tile(CursorController* cursorController);
        Tile(int tileId,Vector2 tilePos);
        Tile(Sprite sprite,int tileId,Vector2 tilePos);
        Tile(Tile*);
        ~Tile();
        void draw();
};

#endif