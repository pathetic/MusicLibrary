#include <cstring>
#include <iostream>
#include "menu.h"

void menu::ClearScreen() {
#ifdef WINDOWS
    system("cls");
#else
    system("clear");
#endif
}

menu::command menu::ParseCommand(std::string cmd) {
    return ParseCommand(cmd.c_str());
}

menu::command menu::ParseCommand(const char *cmd) {
    if (strcmp(cmd,"add")==0)
        return add;
    if (strcmp(cmd,"delete")==0)
        return del;
    if (strcmp(cmd,"list")==0)
        return list;
    if (strcmp(cmd,"search")==0)
        return search;
    if (strcmp(cmd,"save")==0)
        return save;
    if (strcmp(cmd,"quit")==0)
        return quit;
    if (strcmp(cmd,"clear")==0)
        return clear;
    if (strcmp(cmd,"load")==0)
        return load;
    if (strcmp(cmd,"help")==0)
        return help;
    return NaC;
}

#define MAX_STR_LEN 100

menu::command menu::GetUserCommand() {
    char inp[MAX_STR_LEN];
    std::cout<<"Introdu comanda ta\n";
    std::cin.getline(inp,MAX_STR_LEN);
    return ParseCommand(inp);
}

void menu::DisplayHelpMessage() {
    std::cout << "Scrie o comanda pentru a interactiona cu programul\n" <<
    "Comenziile prezente momentan sunt:\n" <<
    "add, delete, list, search, listen, load, save, quit, help\n";
}

void menu::AfisareDeleteOptiuni() {
    int optiune;
    do {
        std::cout << "0. Back\n" <<
        "1. Delete dupa index\n" <<
        "2. Delete dupa ISMN\n" <<
        "3. Delete dupa Artist\n";
        std::cin >> optiune;
        ClearScreen();
        std::cin.ignore();
    } while(optiune < 0 || optiune > 3);

    bool ret;
    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            int index;
            std::cin >> index;
            std::cin.ignore();
            ret = playlist.DeleteSongByIndex(index);
        }
            break;
        case 2:
        {
            std::string ismn;
            std::cin >> ismn;
            ret = playlist.DeleteSongByIsmn(ismn);
        }
            break;
        case 3:
        {
            char inp[MAX_STR_LEN];
            std::cin.getline(inp,MAX_STR_LEN);
            std::string tmp = inp;
            ret = playlist.DeleteSongByCriteriu([&tmp](Song& song){
                for (auto& artist: song.Artist)
                    if (artist == tmp) return true;
                return false;
            });
        }
    }

    ret ? std::cout << "Nu au fost gasite melodii care sa satisfaca conditia\n" : std::cout<<"Melodii sterse cu succes\n";
    //TODO: delete dupa ce a selectat userul
}

void menu::AfisareSearchOptiuni() {
    int optiune;
    do {
        std::cout << "0. Back\n" <<
                  "1. Search dupa index\n" <<
                  "2. Search dupa ISMN\n" <<
                  "3. Search dupa Artist\n" <<
                  "4. Search dupa Gen\n" <<
                  "5. Search dupa Album\n";
        std::cin >> optiune;
        ClearScreen();
        std::cin.ignore();
    } while(optiune < 0 || optiune > 5);

    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            int index;
            std::cin>>index;
            std::cin.ignore();
            playlist.DisplaySongByCriteriu([&index](Song& song){
                if (index--==0) return true;
                return false;
            });
        }
            break;
        case 2:
        {
            std::string ismn;
            std::cin >> ismn;
            playlist.DisplaySongByCriteriu([&ismn](Song& song){
                return song.ISMN == ismn;
            });
        }
            break;
        case 3:
        {
            char inp[MAX_STR_LEN];
            std::cin.getline(inp,MAX_STR_LEN);
            std::string tmp = inp;
            playlist.DisplaySongByCriteriu([&tmp](Song& song){
                for (auto& artist : song.Artist)
                    if (artist==tmp) return true;
                return false;
            });
        }
            break;
        case 4:
        {
            char inp[MAX_STR_LEN];
            std::cin.getline(inp,MAX_STR_LEN);
            std::string tmp = inp;
            playlist.DisplaySongByCriteriu([&tmp](Song& song){
                for (auto& gen : song.Genre)
                    if (gen==tmp) return true;
                return false;
            });
        }
            break;
        case 5:
        {
            char inp[MAX_STR_LEN];
            std::cin.getline(inp,MAX_STR_LEN);
            std::string tmp = inp;
            playlist.DisplaySongByCriteriu([&tmp](Song& song){
                return song.Album == tmp;
            });
        }
            break;
    }

    //TODO: search dupa ce a selectat userul
}

void menu::AfisareListenOptiuni() {
    int optiune;
    do {
        std::cout << "0. Back\n" <<
                  "1. Asculta dupa ISMN\n";
        std::cin >> optiune;
        ClearScreen();
        std::cin.ignore();
    } while(optiune < 0 || optiune > 1);

    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            std::string ismn;
            std::cin >> ismn;
            playlist.ListenToSongByIsmn(ismn) ? std::cout << "Melodia nu a fost gasita\n"
            : std :: cout << "Ai ascultat melodia cu succes\n";
        }
    }
}

void menu::StartLoop() {
    while (true) {
        auto cmd = GetUserCommand();
        switch (cmd) {
            case list:
                std::cout << playlist;
                break;
            case clear:
                ClearScreen();
                break;
            case help:
                DisplayHelpMessage();
                break;
            case add:
                playlist.append();
                break;
            case save:
                playlist.SaveSongs();
                break;
            case load:
                playlist.ReadSongs();
            case quit:
                return;
            case del:
                AfisareDeleteOptiuni();
                break;
            case search:
                AfisareSearchOptiuni();
                break;
            case listen:
                AfisareListenOptiuni();
            default:
                break;
        }
    }
}