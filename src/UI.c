#include "UI.h"

void InitUIWindowProperties(UI* windowProps){
    windowProps->windowWidth = 800;
    windowProps->windowHeight = 600;

    windowProps->benDebugWindowPosX = 1920 + (3440 - windowProps->windowWidth) / 2;
    windowProps->benDebugWindowPosY = (1440 - windowProps->windowHeight) / 2;

    windowProps->slider.width = 200;
    windowProps->slider.height = 40;
    windowProps->slider.x = windowProps->windowWidth/2.0 - windowProps->slider.width;
    windowProps->slider.y = windowProps->windowHeight - windowProps->slider.height;

    windowProps->musicButton.width = 200;
    windowProps->musicButton.height = 40;
    windowProps->musicButton.x = windowProps->windowWidth/2.0 -windowProps->musicButton.width/2;
    windowProps->musicButton.y = 0;
}
