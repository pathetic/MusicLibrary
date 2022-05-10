#include <iostream>
#include "fstream"
#include "song.h"
#include "playlist.h"
#include "json.hpp"
#include "menu.h"

#define NUME_DB "db.json"

int main() {
    menu::GetInstance().playlist.nume = NUME_DB;
    menu::GetInstance().playlist.ReadSongs();
    menu::GetInstance().DisplayHelpMessage();
    menu::GetInstance().StartLoop();

    return 0;
}
