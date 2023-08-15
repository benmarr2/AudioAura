#include "ui.h"

void InitUIWindowProperties(UI* windowProps){
    windowProps->windowWidth = 800;
    windowProps->windowHeight = 600;

    windowProps->benDebugWindowPosX = 1920 + (3440 - windowProps->windowWidth) / 2;
    windowProps->benDebugWindowPosY = (1440 - windowProps->windowHeight) / 2;

    windowProps->slider.width = windowProps->windowWidth;
    windowProps->slider.height = 40;
    windowProps->slider.x = 0;
    windowProps->slider.y = windowProps->windowHeight - windowProps->slider.height;

    windowProps->musicButton.width = 200;
    windowProps->musicButton.height = 40;
    windowProps->musicButton.x = windowProps->windowWidth/2.0 -windowProps->musicButton.width/2;
    windowProps->musicButton.y = 0;

    windowProps->playlistButton.width = 200;
    windowProps->playlistButton.height = 40;
    windowProps->playlistButton.x = 0;
    windowProps->playlistButton.y = 0;

    windowProps->playlistHolder.width = 200;
    windowProps->playlistHolder.height = 400;
    windowProps->playlistHolder.x = 0;
    windowProps->playlistHolder.y = 0;
}
