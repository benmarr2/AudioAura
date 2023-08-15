#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "raylib.h"

#define MAX_SONGS 350

typedef struct {
    Music songs[MAX_SONGS];
    int songCount;
    int currentSong;
} Playlist;

void InitPlaylist(Playlist *playlist);
void AddSong(Playlist *playlist, const char *songPath);
void NextSong(Playlist *playlist);
void PreviousSong(Playlist *playlist);

#endif // !PLAYLIST_H
