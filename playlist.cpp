#include "playlist.h"
#include <iostream>

Playlist::Playlist(std::string& Nume) : nume(Nume) {}

std::string Playlist::toString() const {
    std::ostringstream str;

    str << "<-- Playlist: " << nume << " -->" << std::endl;
    int index=0;
    for (auto& s : songs) {
        str << "Index: " << index++ << std::endl;
        str << s;
        str << "\n";
    }

    return str.str();
}

std::ostream& operator<<(std::ostream& out, const Playlist& playlist)
{
	out << playlist.toString();
	return out;
}

void Playlist::append(Song &song) {
    Song s = Song(song);
    songs.emplace_back(song);
    this->size++;
}

void Playlist::append() {
    songs.emplace_back(Song());
    this->size++;
}

Playlist::~Playlist()
{

}

Playlist::Playlist() = default;