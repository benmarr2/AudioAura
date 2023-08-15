#include "playlist.h"

void InitPlaylist(Playlist *playlist) {
    // Initialize playlist
    playlist->songCount = 0;
    playlist->currentSong = -1;
}

void AddSong(Playlist *playlist, const char *songPath) {
    if (playlist->songCount < MAX_SONGS) {
        playlist->songs[playlist->songCount] = LoadMusicStream(songPath);
        playlist->songCount++;
    }
}

void NextSong(Playlist *playlist) {
    if (playlist->currentSong < playlist->songCount - 1) {
        StopMusicStream(playlist->songs[playlist->currentSong]);
        playlist->currentSong++;
        PlayMusicStream(playlist->songs[playlist->currentSong]);
    }
}

void PreviousSong(Playlist *playlist) {
    if (playlist->currentSong > 0) {
        StopMusicStream(playlist->songs[playlist->currentSong]);
        playlist->currentSong--;
        PlayMusicStream(playlist->songs[playlist->currentSong]);
    }
}

