#include "playlist.h"
#include <functional>
#include <iostream>
#include "fstream"

Playlist::Playlist(std::string& Nume) : nume(Nume) {}
Playlist::Playlist(const char* Nume) : nume(Nume) {}

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

Song* Playlist::FindSongByIsmn(std::string &ismn) {
    for (auto& song : songs)
        if (song.ISMN == ismn) return &song;
    return nullptr;
}

Song *Playlist::FindSongByIndex(size_t index) {
    int _index=0;
    for (auto& song : songs) {
        if (_index==index) return &song;
        _index++;
    }
    return nullptr;
}

Song *Playlist::FindSongByCriteriu(const std::function <bool (Song&)>& criteriu) {
    for (auto& song : songs)
        if (criteriu(song)) return &song;
    return nullptr;
}

bool Playlist::ListenToSongByIsmn(std::string& ismn){
    for (auto& song : songs)
        if (song.ISMN == ismn)
        {
            song.listen();
            return true;
        }
    return false;
}

bool Playlist::DeleteSongByIsmn(std::string &ismn) {
    for (auto i = songs.begin(); i!=songs.end(); i++) {
        if (i->ISMN == ismn) {
            songs.erase(i);
            this->size--;
            return false;
        }
    }
    return true;
}

bool Playlist::DeleteSongByIndex(size_t index) {
    if (index>this->size) return true;
    auto i=songs.begin();
    for (; index!=0; index--,i++) {}
    this->size--;
    songs.erase(i);
    return false;
}

bool Playlist::DeleteSongByCriteriu(const std::function <bool (Song&)>& criteriu) {
    auto i=songs.begin();
    for (auto& song : songs) {
        if (criteriu(song)) {
            songs.erase(i);
            this->size--;
            return false;
        }
        i++;
    }
    return true;
}

void Playlist::DisplaySongByCriteriu(const std::function <bool (Song&)>& criteriu) {
    int index=0;
    for (auto& song : songs) {
        //modifica ca la ambele sa fie << overloading
        if (criteriu(song))
        {
            std::cout<<"Index: "<<index<<"\n";
            std::cout<<song;
        }
        index++;
    }
}

void Playlist::ReadSongs(std::istream& stream) {
    nlohmann::json json;
    stream >> json;

    nlohmann::json outJson;
    for (auto& it : json["Songs"]) {
        outJson = nlohmann::json::parse(it.dump());
        songs.emplace_back(outJson);
    }

    this->size = json["size"];
}

void Playlist::ReadSongs(const std::string& file) {
    std::fstream stream;
    stream.open(file, std::fstream::in);
    if (stream.fail()) return;
    ReadSongs(stream);
}

void Playlist::ReadSongs(const char* file) {
    std::fstream stream;
    stream.open(file, std::fstream::in);
    if (stream.fail()) return;
    ReadSongs(stream);
}

void Playlist::ReadSongs() {
    ReadSongs(this->nume);
}

void Playlist::SaveSongs(std::ostream& stream) {
    nlohmann::json json;
    for (Song& song : songs) {
        json["Songs"].push_back(song.getJson());
    }
    json["size"] = this->size;

    stream<<json;
}

void Playlist::SaveSongs(const char* file) {
    std::fstream stream;
    stream.open(file, std::fstream::out);
    SaveSongs(stream);
}

void Playlist::SaveSongs(const std::string& file) {
    std::fstream stream;
    stream.open(file, std::fstream::out);
    SaveSongs(stream);
}

void Playlist::SaveSongs() {
    SaveSongs(this->nume);
}

Playlist::~Playlist()
{
    this->songs.clear();
}

Playlist::Playlist() = default;