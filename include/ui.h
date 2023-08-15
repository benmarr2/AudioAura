#ifndef UI_Layout_H
#define UI_Layout_H

#include "raylib.h"
typedef struct{
    int windowWidth;
    int windowHeight;

    int benDebugWindowPosX;
    int benDebugWindowPosY;

    Rectangle musicButton;
    Rectangle slider;
    Rectangle playlistButton;
    Rectangle playlistHolder;

} UI;

void InitUIWindowProperties(UI* windowProps);

#endif // !UI_Layout_H
