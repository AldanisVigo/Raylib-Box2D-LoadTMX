#include "CursorController.h"

CursorController::CursorController(){
    pointerTex = LoadTexture("../res/pointer_normal.png");
    pointerPressedTex = LoadTexture("../res/pointer_pressed.png");
    eraseTex = LoadTexture("../res/erase.png");
    drawTex = LoadTexture("../res/draw.png");
}

CursorController::~CursorController(){

}

void CursorController::draw(){
    Vector2 mousePos = GetMousePosition();
    switch(state){
        case CursorState::Pointer:
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                DrawTexture(pointerPressedTex,mousePos.x,mousePos.y,WHITE);
            }else{
                DrawTexture(pointerTex,mousePos.x,mousePos.y,WHITE);
            }
            break;
        case CursorState::Draw:
            DrawTexture(drawTex,mousePos.x,mousePos.y,WHITE);
            break;
        case CursorState::Erase:
            DrawTexture(eraseTex,mousePos.x,mousePos.y,WHITE);
            break;
        default:
            break;
    }
}