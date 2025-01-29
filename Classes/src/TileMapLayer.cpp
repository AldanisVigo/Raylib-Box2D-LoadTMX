#include "TileMapLayer.h"

TileMapLayer::TileMapLayer(Vector2 pos,float tSize,int rows,int cols,TilePalette* p,Camera2D* c){
    palette = p;
    defaultTileTexture = LoadTexture("../sprites/tilepaletteicon.png");
    cout << "Initializing a TileMapLayer tile size : " << tSize << " And dimmensions" << rows << " , " << cols << endl;
    position = Vector3{
        pos.x,
        pos.y,
        0.0f
    };

    tileSize = tSize;

    tileGrid = new TileGrid(Vector2{position.x, position.y},rows,cols,tileSize,palette,c);
    tileGrid->cols = cols;
    tileGrid->rows = rows;
    tileGrid->position = position;
    tileGrid->name = "TileGrid";
    tileGrid->tileSize = tSize;
    FillGridWithEmptyTiles();
}

TileMapLayer::~TileMapLayer(){

}

void TileMapLayer::draw(){
    // Make the tileGrid draw call
    tileGrid->draw();
}

void TileMapLayer::FillGridWithEmptyTiles(){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            tileGrid->grid[r][c].emptyTile = true;
        }
    }
}

/*
    Iterates through a .tmx file retrieves the tile id's and builds the TileGrid for this TileMapLayer
    using the tiles in the availableTiles in the TileMapLayer
*/
void TileMapLayer::PopulateWithTMXAt(char* path){
    auto map = LoadTmx::tilemap(path);

    // Set the grid cols and rows for the TileMapLayer
    rows = map.size() + 1;
    cols = map[0].size();

    // Resize the grid to fit all the tiles
    tileGrid->grid.resize(rows, vector<Tile>(cols,Tile(palette->cursorController)));

    // Iterate through the map's tiles
    for(std::size_t row{}; row < rows;row++){
        for(std::size_t col{}; col < cols;col++){
            // Grab the id of the current tile
            int tileId = map[row][col];

            if (palette->palette.size() - 1 >= tileId){
                // Grab the tile from the tile palette
                Tile* selectedTile = palette->palette.at(tileId);
                
                // Add the tile to the grid
                tileGrid->grid.at(row).at(col) = selectedTile;
            }else{
                // Create an empty tile for now
                Tile emptyTile = Tile(tileId,Vector2{0,0});
                emptyTile.emptyTile = true;
                
                // Point the tile to an empty tile for now
                tileGrid->grid.at(row).at(col) = &emptyTile;

                // Let the user know that the tile is not available
                cout << "The tile with ID: " << tileId <<  "at (" << row << "," << col << ") not present in the available tiles. Please add the tiles first." << endl;
            }
        }
    }
}

