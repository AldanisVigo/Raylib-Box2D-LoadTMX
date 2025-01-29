#ifndef CURSOR_CONTROLLER_H
#define CURSOR_CONTROLLER_H
#include <raylib.h>

enum CursorState {
    Pointer,
    Erase,
    Draw
};

class CursorController {
    public:
        Texture2D pointerTex;
        Texture2D pointerPressedTex;
        Texture2D eraseTex;
        Texture2D drawTex;
        CursorState state = CursorState::Pointer;
        CursorController();
        ~CursorController();
        void draw();
};

#endif