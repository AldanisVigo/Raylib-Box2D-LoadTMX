#ifndef TILEPALETTE_H
#define TILEPALETTE_H
#include "Node.h"
#include "Tile.h"
#include "GridBrushTool.h"
#include <vector>
#include <string>
#include <sstream>
#include <box2d.h>
#include <raymath.h>

class TilePalette : public Node {
    private: 
        Texture2D background;
        Texture2D menuHeader;
        Texture2D dismissButton;
        Texture2D tilePaletteIcon;
        bool dragging = false;
        Vector2 dragginOffset = Vector2{0,0};
        bool hidden = false;
        Vector2 tileSize = Vector2{32.0f,32.0f};
        Texture2D defaultTileTexture;
    public:
        int selectedTileId = -1;
        CursorController* cursorController;
        GridBrushTool* gridBrushTool;
        b2WorldId* worldId;
        vector<Tile*> palette;
        void draw();
        TilePalette(b2WorldId*,CursorController*,Vector2 pos);
        TilePalette();
        ~TilePalette();
        Vector2 paletteTileSize = Vector2{
            16.0f,
            16.0f
        };
        Vector2 paletteTilesPadding = Vector2{
            10.0f,
            10.0f
        };
        Vector2 paletteTilesSpacing = Vector2{
            2.0f,
            2.0f
        };
};

#endif