#include "TileGrid.h"

TileGrid::TileGrid(Vector2 pos, int r, int c,int ts,TilePalette* p, Camera2D* cam) {
    camera = cam;
    palette = p;
    cols = static_cast<int>(c); // Number of columns
    rows = static_cast<int>(r); // Number of rows
    tileSize = ts;
    // Initialize the grid with rows and columns
    grid.resize(rows, std::vector<Tile>(cols, Tile(palette->cursorController)));
    position = Vector3{pos.x,pos.y,0.0f};
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            // Tile* curTile = new Tile(); // Use the default constructor
            
            // // Set it as an empty tile initially
            // curTile->emptyTile = false;

            // // Set the properties of each tile
            // curTile->worldId = &worldId;

            // // Put all tiles on the top left corner to start off
            // curTile->position = Vector2{
            //     position.x,
            //     position.y
            // };

            // curTile->tileId = 2;

            // curTile->sprite.texture = palette->palette[2]->sprite.texture;

            // curTile->tileSize = tileSize;
            Tile curTile = p->palette[0];
            curTile.tileSize = ts;

            // grid[r][c] = curTile;
            grid[r][c] = curTile;
        }
    }

    position = Vector3{pos.x, pos.y, 0.0f}; // Set grid position
}


TileGrid::~TileGrid(){

}

void TileGrid::draw() {


    // Check if the cursorController is in draw mode
    if(palette->cursorController->state == CursorState::Draw){
        // Check if there's a selected tile in the palette
        if(palette->selectedTileId != -1){
            // If so then check if the left mouse button is pressed
            // If so, then check if the left mouse button is pressed
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                Vector2 mousePos = GetMousePosition();
                // Convert the mouse position to world position relative to the camera
                Vector2 worldPos = GetScreenToWorld2D(mousePos, *camera);

                // Calculate the x and y coordinates of the tile on the grid
                int xCoord = static_cast<int>((worldPos.x - position.x) / tileSize);
                int yCoord = static_cast<int>((worldPos.y - position.y) / tileSize);

                // Check if the coordinates are within the bounds of the grid
                if(xCoord >= 0 && xCoord < cols && yCoord >= 0 && yCoord < rows) {
                    // Draw on the tile at the specified coordinates
                    cout << grid[xCoord][yCoord].tileId << endl;
                    grid[yCoord][xCoord].tileId = palette->selectedTileId;
                    grid[yCoord][xCoord].emptyTile = false;
                    grid[yCoord][xCoord].texture = palette->palette[palette->selectedTileId]->texture;
                    std::cout << "Drawing on tile at: " << xCoord << ", " << yCoord << std::endl;
                }
            }
        }
    }else if(palette->cursorController->state == CursorState::Erase){
        // Check if the cursorController is in draw mode
        // Check if there's a selected tile in the palette
        if(palette->selectedTileId != -1){
            cout << "Selected tile id: " << palette->selectedTileId << endl;
            // If so then check if the left mouse button is pressed
            // If so, then check if the left mouse button is pressed
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                Vector2 mousePos = GetMousePosition();
                // Convert the mouse position to world position relative to the camera
                Vector2 worldPos = GetScreenToWorld2D(mousePos, *camera);

                // Calculate the x and y coordinates of the tile on the grid
                int xCoord = static_cast<int>((worldPos.x - position.x) / tileSize);
                int yCoord = static_cast<int>((worldPos.y - position.y) / tileSize);

                // Check if the coordinates are within the bounds of the grid
                if(xCoord >= 0 && xCoord < cols && yCoord >= 0 && yCoord < rows) {
                    // Draw on the tile at the specified coordinates
                    cout << grid[xCoord][yCoord].tileId << endl;
                    grid[yCoord][xCoord].tileId = 0;
                    // grid[yCoord][xCoord].emptyTile = true;
                    grid[yCoord][xCoord].texture = palette->palette[0]->texture;
                    std::cout << "Erasing tile at: " << xCoord << ", " << yCoord << std::endl;
                }
            }
        }
    }


    // Iterate through each row of the grid
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            // Tile tile = grid[row][col];

            // Ensure the tile pointer is valid
            // if (tile) {
                // Get the grid's position using its node property
                // b2Vec2 tilePosition = b2Vec2{
                //     position.x + col * tileSize,
                //     position.y + row * tileSize
                // };

                grid[row][col].position = Vector2{
                    position.x + col * tileSize,
                    position.y + row * tileSize
                };

                // Assign the position to the tile's sprite
                // grid[row][col].sprite.position = tilePosition;

                // Assign the tile size to the tile's sprite
                // grid[row][col].sprite.size = b2Vec2{
                //     tileSize,
                //     tileSize
                // };


                // cout << palette->palette[grid[row][col].tileId]->texture.id << endl;

                // make sure the texture is the right one.
                // grid[row][col].sprite.texture = palette->palette[tile.tileId]->texture;

                grid[row][col].draw();
            // }
        }
    }

    // Optional debugging output
    // std::cout << "Grid Dimensions: " << grid.size() << " x " 
            //   << (grid.empty() ? 0 : grid[0].size()) << std::endl;
}