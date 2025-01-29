#include "Tile.h"

Tile::Tile(CursorController* cc){
    cursorController = cc;
    tileId = 0;
    emptyTile = true;
    worldId = nullptr;
    position = Vector2{0.0f, 0.0f};
    sprite = Sprite();
}

Tile::Tile(int tileId,Vector2 tilePos){
    sprite = Sprite();
    sprite.position = b2Vec2{
        tilePos.x,
        tilePos.y
    };
}

Tile::Tile(Sprite tileSprite,int tid,Vector2 tilePos){
    sprite = tileSprite;
    tileId = tid;
    position = tilePos;
}

Tile::Tile(Tile* t){
    tileId = t->tileId;
    sprite = t->sprite;
    emptyTile = t->emptyTile;
}

Tile::~Tile() {

}

void Tile::draw() {

    // Tile s = palette->palette[tileId];
    sprite.drawGridTileSprite(tileSize,position,tileId);
    // if(!emptyTile){
    //     sprite.draw();
    // }else{
    //     // Skip the draw call
    //     // sprite.drawBodyless(1,16);
    // }
}