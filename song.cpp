#include "song.h"
#include <sstream>
#include <iomanip>
#include <iostream>

Song::Song()
{
    char inp[MAX_LEN];
    
    std::cout << "Introdu ISMN-ul melodiei:\n";
    std::cin.getline(inp,MAX_LEN);
    this->ISMN = inp;
    
    
    std::cout << "Introdu titlul melodiei:\n";
    std::cin.getline(inp,MAX_LEN);
    this->Title = inp;
    
    
    std::cout << "Introdu albumul din care face parte melodia:\n";
    std::cin.getline(inp,MAX_LEN);
    this->Album = inp;
    

    int artistsNr,genresNr;

    std::cout << "Introdu numarul de artisti\n";
    std::cin >> artistsNr;
    std::cin.get();
    Artist.reserve(artistsNr); // alocam numarul de autori
    artistsNr++;

    for (int i = 1; i < artistsNr; i++) {
        std::cout << "Introdu artistul cu numarul " << i << "\n";
        std::cin.getline(inp,MAX_LEN);
        this->Artist.emplace_back(inp);
    }

    std::cout << "Introdu numarul de genuri\n";
    std::cin >> genresNr;
    std::cin.get();
    Genre.reserve(genresNr); // alocam numarul de genuri
    genresNr++;

    for (int i = 1; i < genresNr; i++) {
        std::cout << "Introdu genul cu numarul " << i << "\n";
        std::cin.getline(inp,MAX_LEN);
        this->Genre.emplace_back(inp);
    }

    std::cout << "Introdu numarul de streamuri\n";
    std::cin >> this->Streams;
    std::cin.get();

    std::cout << "Introdu rating-ul melodiei (1-5)\n";
    std::cin >> this->Rating;
    std::cin.get();

    std::cout << "Introdu durata melodiei (in secunde)\n";
    std::cin >> this->Duration;
    std::cin.get();

    std::cout << "Introdu anul lansarii melodiei\n";
    std::cin >> this->Year;
    std::cin.get();
}

Song::Song(std::string& ISMN, std::string& title, std::vector<std::string>& artists, std::vector<std::string>& genres, std::string& album, int streams, int rating, int duration, int year)
:ISMN(ISMN), Title(title), Album(album), Streams(streams), Rating(rating), Duration(duration), Year(year)
{
    for (const auto& str : artists) {
        Artist.emplace_back(str);
    }

    for (const auto& str : genres) {
        Genre.emplace_back(str);
    }
}

Song::~Song() {

}

std::string Song::toString() const
{
	std::ostringstream str;
	str << "Song: " << Title << " (ISMN: " << ISMN << ")" ":\n";

	str << "Artists: ";
    for (auto& aritstul : Artist) {
        str << aritstul << ", ";
    }
    str << "\n";
    str << "Duration: " << Duration << "\n";
    str << "Release year: " << Year << "\n";
    str << "Streams: " << Streams << "\n";
    str << "Rating: " << Rating << "\n";

    str << "Genres: ";
    for (auto& genresul : Genre) {
        str << genresul << ", ";
    }
    str << "\n";

    return str.str();
}

std::ostream& operator<<(std::ostream& out, const Song& song)
{
	out << song.toString();
	return out;
}