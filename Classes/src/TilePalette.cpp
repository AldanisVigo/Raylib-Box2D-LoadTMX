#include "TilePalette.h"

TilePalette::TilePalette(){
    tilePaletteIcon = LoadTexture("../sprites/tilepaletteicon.png");
}

TilePalette::TilePalette(b2WorldId* wid,CursorController* cc,Vector2 pos) {
    position = Vector3{pos.x,pos.y,0.0f};
    gridBrushTool = new GridBrushTool(cc,Vector2{pos.x,pos.y});
    cursorController = cc;
    background = LoadTexture("../sprites/tilePaletteBackground.png");
    menuHeader = LoadTexture("../sprites/tilePaletteMenuBackground.png");
    dismissButton = LoadTexture("../sprites/tilePaletteDismissButtonBackground.png");
    tilePaletteIcon = LoadTexture("../sprites/tilepaletteicon.png");
    
    // Ensure there's a res directory
    if(!DirectoryExists("../res")) {
        MakeDirectory("../res");
    }

    // Check if there's a palette data file available
    if(FileExists("../res/palette.dat")) {

        // Load the palette data file into a string
        string paletteData = LoadFileText("../res/palette.dat");

        // Create a string stream to break the palette data file into individual entries
        stringstream entryStream(paletteData);

        // Iterate through each line in the palette data file
        string entry;
        int lineNumber = 0;
        string tilesetTexturePath;
        while (getline(entryStream, entry)) {
            // The first line of the file is the path to the atlas
            if(lineNumber == 0){
                tilesetTexturePath = entry;
                lineNumber++;
                continue;
            }

            // The second line of the file is the tileSize
            if(lineNumber == 1){
                tileSize = Vector2{
                    (float) atof(entry.c_str()),
                    (float) atof(entry.c_str())
                };
                lineNumber++;
                continue;
            }

            // Create a string stream to break the line data into segments
            stringstream segmentStream(entry);

            // Create an empty tile for this data segment
            Tile* newTile = new Tile(-1,{0.0f,0.0f});

            // Separate each line by the | character
            string segment;
            while(getline(segmentStream, segment, '|')) {
                // Create a string stream to break the segment into key-value pairs
                stringstream propertyStream(segment);
                string propertyPart;
                vector<string> valuePair;

                //Pull both parts of the value pair
                while(getline(propertyStream,propertyPart,'=')) {
                    valuePair.push_back(propertyPart);
                }

                //Grab the key
                string key = valuePair.at(0);

                //Grab the value
                string value = valuePair.at(1);

                // If the current key is tileId
                if(key == "tileId"){
                    // Convert the value to an int and assign it to the new tile's tileId property
                    newTile->tileId = atoi(value.c_str());
                    
                    // Grab the atlas texture from the filesystem
                    Texture2D newTileAtlasTex = LoadTexture(tilesetTexturePath.c_str());

                    newTile->position = Vector2{
                        position.x + (paletteTilesSpacing.x * (lineNumber - 2)) + paletteTilesPadding.x + (lineNumber - 2 * tileSize.x),
                        position.y + paletteTilesPadding.y
                    };

                    // 3 - Conver the image back to a texture and assign it to the new tile's sprite texture
                    newTile->sprite.texture = newTileAtlasTex;
                }
            }

            // Assign the world id
            newTile->worldId = wid;

            // Add the new tile to the palette
            palette.push_back(newTile);
            lineNumber++;
        }
    }
}

TilePalette::~TilePalette(){
    // TODO: Load default background, menu header and dismiss button textures
}

void TilePalette::draw(){
    Vector2 mousePos = GetMousePosition();
    Vector2 dismissButtonPadding = Vector2{
        2.0f,
        2.0f
    };
    float sHeight = GetScreenHeight();

    bool mouseInsideDismissButton = CheckCollisionPointRec(mousePos,Rectangle{
            position.x + menuHeader.width - dismissButton.width - dismissButtonPadding.x,
            position.y + dismissButtonPadding.y,
            (float)dismissButton.width,
            (float)dismissButton.height
        });

    bool mouseInsideMenuHeader = CheckCollisionPointRec(mousePos,Rectangle{
            position.x,
            position.y,
            (float)menuHeader.width,
            (float)menuHeader.height
        });

    bool mouseInsideTilePaletteIcon = CheckCollisionPointRec(mousePos,Rectangle{
        20.0f,
        sHeight - tilePaletteIcon.height - 20.0f,
        (float)tilePaletteIcon.width,
        (float)tilePaletteIcon.height
    });

    // If the left mouse button is pressed inside the menu header of the palette
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        cout << dragging << mouseInsideDismissButton << endl;
        if(mouseInsideMenuHeader && !dragging && !mouseInsideDismissButton){
            dragging = true;
            dragginOffset = Vector2Subtract(mousePos,Vector2{position.x,position.y});
        }else{
            dragginOffset = Vector2{0,0};
        }
    }

    // Check for close button
    if(hidden){
        // Check for clicks to unhide the tilePalette window
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseInsideTilePaletteIcon){
            hidden = false;
        }

        // Show button to open the palette window
        
        DrawTexture(
            tilePaletteIcon,
            20.0f,
            sHeight - tilePaletteIcon.height - 20.0f,
            WHITE
        );

    }else{

        if (dragging){
            cursorController->state = CursorState::Pointer;
            cout << "Adjusting window pos based on mouse offset " << dragginOffset.x << "," << dragginOffset.y << endl;
            position.x = (mousePos.x - dragginOffset.x);
            position.y = (mousePos.y - dragginOffset.y);

            if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) dragging = false;
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseInsideDismissButton){
            cursorController->state = CursorState::Pointer;
            hidden = true;
        }

        //Draw the background
        DrawTexture(background,position.x,position.y,WHITE);

        // Draw the menu header
        DrawTexture(menuHeader,position.x,position.y,WHITE);

        // Draw the dismiss button
        DrawTexture(
            dismissButton,
            position.x + menuHeader.width - dismissButton.width - dismissButtonPadding.x,
            position.y + dismissButtonPadding.y,WHITE
        );

        if(palette.size() > 0){
            int tileIdx = 0;
            int tilesPerRow = 10;
            int curColumn = 0;
            for (Tile* tile : palette) {
                if (tile) {
                    Sprite* spritePtr = &tile->sprite;
                    if(spritePtr != nullptr){
                        if(curColumn < tilesPerRow){
                            curColumn++;
                        }else{
                            curColumn = 1;
                        }

                        tile->sprite.position = b2Vec2{
                            position.x + (paletteTilesSpacing.x * curColumn) + paletteTilesPadding.x + (curColumn * paletteTileSize.x),
                            position.y + paletteTilesPadding.y + menuHeader.height + (tileIdx / tilesPerRow * paletteTileSize.y)
                        };

                        tile->sprite.drawPaletteTileSprite(tileIdx,paletteTileSize.y);
                        
                        if(selectedTileId == tile->tileId){
                            DrawRectangleLines(
                                position.x + (paletteTilesSpacing.x * curColumn) + paletteTilesPadding.x + (curColumn * paletteTileSize.x),
                                position.y + paletteTilesPadding.y + menuHeader.height + (tileIdx / tilesPerRow * paletteTileSize.y),
                                paletteTileSize.x,
                                paletteTileSize.y,
                                ORANGE
                            );
                        }

                        // Check if the cursorController is in Pointer mode
                        if(cursorController->state == CursorState::Pointer || cursorController->state == CursorState::Draw){
                            // If so check if the mouse is over this tile and the left mouse button is pressed
                            bool mouseIsInsideTile = CheckCollisionPointRec(GetMousePosition(),Rectangle{
                                // position.x + (paletteTilesSpacing.x * tileIdx) + paletteTilesPadding.x + (tileIdx * tileSize.x),
                                // position.y + paletteTilesPadding.y + menuHeader.height,
                                position.x + (paletteTilesSpacing.x * curColumn) + paletteTilesPadding.x + (curColumn * paletteTileSize.x),
                                position.y + paletteTilesPadding.y + menuHeader.height + (tileIdx / tilesPerRow * paletteTileSize.y),
                                paletteTileSize.x,
                                paletteTileSize.y
                            });

                            // If the tile is already selected
                            if(selectedTileId == tile->tileId && mouseIsInsideTile && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                                selectedTileId = -1; // Deselect the tile
                            } else if(mouseIsInsideTile && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && selectedTileId != tile->tileId){
                                // If so then set the selected tile to this tile.
                                selectedTileId = tile->tileId;
                            }
                        }
                    }

                    tileIdx++;
                }
            }
        }

        gridBrushTool->position = Vector2Add(Vector2{position.x,position.y},gridBrushTool->positionOffset);
        // Draw the grid brush tool
        gridBrushTool->draw();
    }
}