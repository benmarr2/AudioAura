#include <stdio.h>
#include <pthread.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "nfd.h"

#include "ui.h"
#include "playlist.h"

typedef struct {
    bool isLoaded;
    Music music;
    char songPath[1024];
} MusicLoadResult;

void* load_music_thread(void* arg) {
    MusicLoadResult* result = (MusicLoadResult*)arg;

    nfdchar_t *outPath = NULL;
    nfdresult_t nfdResult = NFD_OpenDialog("*", NULL, &outPath);

    if (nfdResult == NFD_OKAY && outPath != NULL) {
        result->music = LoadMusicStream(outPath);
        PlayMusicStream(result->music);
        result->isLoaded = true;
        strncpy(result->songPath, outPath, sizeof(result->songPath) - 1); // safely copy the path to result
    }

    return NULL;
}

int main(){

    UI UI;
    InitUIWindowProperties(&UI);


    pthread_t musicLoadThread;
    MusicLoadResult musicLoadResult = { false };

    InitWindow(UI.windowWidth, UI.windowHeight, "AudioAura");

    SetTargetFPS(60);

    SetWindowPosition(UI.benDebugWindowPosX, UI.benDebugWindowPosY);

    InitAudioDevice();
    Playlist Playlist;
    InitPlaylist(&Playlist);

    while (!WindowShouldClose()) {
        
        if (IsKeyPressed(KEY_SPACE) || GuiButton(UI.musicButton, "Load Music") || GuiButton(UI.playlistButton,  "Add to Playlist")) {
            pthread_create(&musicLoadThread, NULL, load_music_thread, &musicLoadResult);
            AddSong(&Playlist, musicLoadResult.songPath);
        }

        if (musicLoadResult.isLoaded) {
            UpdateMusicStream(musicLoadResult.music);

            float currentTime = GetMusicTimePlayed(musicLoadResult.music);
            float songLength = GetMusicTimeLength(musicLoadResult.music);

            float progress = (int)(currentTime / songLength * 100.0f);

            progress = GuiSliderBar(UI.slider, "Progress", NULL, &progress, 0, 100);

            GuiListView(UI.playlistHolder, "List", &Playlist.songCount, &Playlist.currentSong);

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
