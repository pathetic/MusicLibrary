#ifndef MUSIC_LIBRARY_PLAYLIST_H
#define MUSIC_LIBRARY_PLAYLIST_H

#include "song.h"
#include <list>

class Playlist {
public:
    Playlist();
    explicit Playlist(std::string& nume);
    explicit Playlist(const char* nume);

    ~Playlist();

    void append(Song& s);
    void append();

    Song* FindSongByIsmn(std::string& ismn);
    Song* FindSongByIndex(size_t index);
    Song* FindSongByCriteriu(const std::function <bool (Song&)>& criteriu);

    bool ListenToSongByIsmn(std::string& ismn);
    
    bool DeleteSongByIsmn(std::string& ismn);
    bool DeleteSongByIndex(size_t index);
    bool DeleteSongByCriteriu(const std::function <bool (Song&)>& criteriu);

    void DisplaySongByCriteriu(const std::function <bool (Song&)>& criteriu);

    void UpdateSongByIsmn(std::string& ismn);
    void UpdateSongByIndex(size_t index);

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& out, const Playlist& p);

    void ReadSongs(std::istream&);
    void ReadSongs(const char*);
    void ReadSongs();
    void ReadSongs(const std::string&);

    void SaveSongs(std::ostream&);
    void SaveSongs(const std::string&);
    void SaveSongs(const char*);
    void SaveSongs();

    std::string nume; //folosit pt nume fisier
private:
    std::list<Song> songs;
    size_t size = 0;
};

#endif