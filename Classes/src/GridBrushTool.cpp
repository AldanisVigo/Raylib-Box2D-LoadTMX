#include "GridBrushTool.h"

GridBrushTool::GridBrushTool(CursorController* cc, Vector2 pos){
    positionOffset = Vector2{
        230.0f,
        30.0f,
    };

    pencilIcon = LoadTexture("../res/draw.png");
    eraserIcon = LoadTexture("../res/erase.png");
    cursorController = cc;
    position = Vector2Add(pos,positionOffset);
}

GridBrushTool::~GridBrushTool(){

}

void GridBrushTool::draw(){
    // Draw the pencil icon
    DrawTexture(pencilIcon,position.x,position.y,WHITE);

    // Draw the eraser icon next to it
    DrawTexture(eraserIcon,position.x + pencilIcon.width + 5.0f,position.y, WHITE);
    
    Vector2 mousePos = GetMousePosition();

    // Check if the mouse is over the pencil icon
    bool mouseInsidePencilButton = CheckCollisionPointRec(mousePos,Rectangle{
            position.x,
            position.y,
            (float)pencilIcon.width,
            (float)pencilIcon.height
    });

    // Check if the mouse is over the eraser icon
    bool mouseInsideEraserIcon = CheckCollisionPointRec(mousePos,Rectangle{
        position.x + pencilIcon.width + 5.0f,
        position.y,
        (float)eraserIcon.width,
        (float)eraserIcon.height
    });


    // If the user clicks on the pencil button
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseInsidePencilButton){
        // If the pencil brush is already selected
        if(cursorController->state == CursorState::Draw){
            // Deselect the pencil brush
            cursorController->state = CursorState::Pointer;
        }else{ // Otherwise select the pencil brush
            cursorController->state = CursorState::Draw;
        }
    }

    // If the user clicks on the eraser icon
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseInsideEraserIcon){
        // If the eraser brush is already selected
        if(cursorController->state == CursorState::Erase){
            // Deselect the eraser brush
            cursorController->state = CursorState::Pointer;
        }else{ // Otherwise select the eraser brush
            cursorController->state = CursorState::Erase;
        }
    }
}