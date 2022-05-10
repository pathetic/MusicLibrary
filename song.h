#ifndef MUSIC_LIBRARY_SONG_H
#define MUSIC_LIBRARY_SONG_H

#include <vector>
#include <string>
#include "json.hpp"

#define MAX_LEN 100

class Song {
public:
    std::string ISMN; // International Standard Music Number
    std::string Title;
    std::vector<std::string> Artist;
    std::vector<std::string> Genre;
    std::string Album;
    int Streams;
    int Rating;
    int Duration;
    int Year;

    Song();
    Song(std::string& ISMN, std::string& title, std::vector<std::string>& artists, std::vector<std::string>& genres, std::string& album, int streams, int rating, int duration, int year);
    Song(nlohmann::json& json);
    ~Song();

    void listen();

    std::string toString() const;
    nlohmann::json getJson() const;

    void setISMN(std::string ISMN);
    void setTitle(std::string title);
    void setAlbum(std::string album);
    void setStreams(int streams);
    void setRating(int rating);
    void setDuration(int duration);
    void setYear(int year);

    friend std::ostream& operator<<(std::ostream& out, const Song& offer);
private:
};

#endif