#include "song.h"
#include <list>

class Playlist {
public:
    Playlist();
    Playlist(std::string& nume);

    ~Playlist();

    void append(Song& s);
    void append();

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& out, const Playlist& p);

    std::string nume;
private:
    std::list<Song> songs;
    size_t size = 0;
};