#include <vector>
#include <string>

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
    ~Song();

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& out, const Song& offer);
private:
};
