#include <stdio.h>
#include <pthread.h>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "nfd.h"

typedef struct {
    bool isLoaded;
    Music music;
} MusicLoadResult;

void* load_music_thread(void* arg) {
    MusicLoadResult* result = (MusicLoadResult*)arg;

    nfdchar_t *outPath = NULL;
    nfdresult_t nfdResult = NFD_OpenDialog("*", NULL, &outPath);

    if (nfdResult == NFD_OKAY && outPath != NULL) {
        result->music = LoadMusicStream(outPath);
        PlayMusicStream(result->music);
        result->isLoaded = true;
    }

    return NULL;
}

int main(){
    bool exitWindow = false;
    int windowWidth = 800;
    int windowHeight = 600; 

    pthread_t musicLoadThread;
    MusicLoadResult musicLoadResult = { false };

    InitWindow(windowWidth, windowHeight, "AudioAura");

    SetTargetFPS(60);

    SetWindowPosition((1920 + (3440 - windowWidth) / 2), (1440 - windowHeight) / 2);

    InitAudioDevice();

    Rectangle rect;
    rect.x = windowWidth/2.0;
    rect.y = windowHeight/2.0;

    rect.width = 100;
    rect.height = 100;

    while (!exitWindow) {
        
        if (IsKeyPressed(KEY_SPACE) || GuiButton((Rectangle) {0, 0, 200, 40},"Load Music")) {
            pthread_create(&musicLoadThread, NULL, load_music_thread, &musicLoadResult);
        }

        if (musicLoadResult.isLoaded) {
            UpdateMusicStream(musicLoadResult.music);
        }

        BeginDrawing();

        ClearBackground(GRAY);

        EndDrawing();
    }

    pthread_join(musicLoadThread, NULL);

    UnloadMusicStream(musicLoadResult.music);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}
