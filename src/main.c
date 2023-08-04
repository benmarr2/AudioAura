#include <stdio.h>
#include <pthread.h>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "nfd.h"

#include "UI.h"

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
    UI UI;
    InitUIWindowProperties(&UI);


    pthread_t musicLoadThread;
    MusicLoadResult musicLoadResult = { false };

    InitWindow(UI.windowWidth, UI.windowHeight, "AudioAura");

    SetTargetFPS(60);

    SetWindowPosition(UI.benDebugWindowPosX, UI.benDebugWindowPosY);

    InitAudioDevice();

    while (!exitWindow) {
        
        if (IsKeyPressed(KEY_SPACE) || GuiButton(UI.musicButton, "Load Music")) {
            pthread_create(&musicLoadThread, NULL, load_music_thread, &musicLoadResult);
        }

        if (musicLoadResult.isLoaded) {
            UpdateMusicStream(musicLoadResult.music);

            float currentTime = GetMusicTimePlayed(musicLoadResult.music);
            float songLength = GetMusicTimeLength(musicLoadResult.music);

            float progress = (int)(currentTime / songLength * 100.0f);

            progress = GuiSlider(UI.slider, "Progress", NULL, &progress, 0, 100);
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
