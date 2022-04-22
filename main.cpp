#include "playlist.h"
#include <iostream>
 
#ifdef _WIN32 || _WIN64
	#define clear() system("cls");
	#define pause() system("pause");
#else
	#define clear() system("clear");
	#define pause() system("read -p \"Press enter to continue...\"");
#endif

int main()
{
    clear();
    Song songul;
    std::cout << songul << "\n";

    std::string titlul = "playlist.txt";

    Playlist p(titlul);
    
    p.append(songul);
    p.append(songul);

    std::cout << p;
    return 0;
}