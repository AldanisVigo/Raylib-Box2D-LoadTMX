#ifndef GRID_BRUSH_TOOL_H
#define GRID_BRUSH_TOOL_H
#include "CursorController.h"
#include <raymath.h>

class GridBrushTool {
    private:
        Texture2D pencilIcon;
        Texture2D eraserIcon;
    public:
        Vector2 positionOffset;
        CursorController* cursorController;
        Vector2 position;
        GridBrushTool(CursorController*,Vector2);
        ~GridBrushTool();
        void draw();
};

#endif