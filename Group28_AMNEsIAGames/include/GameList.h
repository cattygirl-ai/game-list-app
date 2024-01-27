/**
 * @author:molaleye
 * @author: Natalie Filep
 *Description: Gamelist class creates an application to create gamelists
 *Gamelist()constructor , initializes a GameList object
 *the getListName() returns  the listname
 *the addGame() adds a game to the list
 *the removeGame() removes a game from the list
 *the pinList() pins a list
 *the unpinList() unpins a list
 *the searchGame() searches for a game list
 *the compare_alpha() checks if the game names are in alphabetic order
 *the compare_desc() checks if the game names are in descending order
 *the sortList_in_alphabetical_order() sorts the list in alphabetic order and prints the game id and names
 *the sortList_in_desc_order() sorts the list in descending order and prints the game id and names
 *the print_list() prints the game id and names in the list
 *the ~Gamelist deconstuctor destroys the Gamelist object when done.
 *@version 2.0
 *@since 2022-11-29*/

// Checks if _GAMELIST_ IF DECLARED

#ifndef _GAMELIST_
// Defines_GAMELIST_ if above fails

#define _GAMELIST_

#include <string>
#include <iostream>
#include <array>
#include <iterator>
#include <algorithm>
#include "Game.h"

class GameList
{
public:
    static const int MAX_SIZE = 100;
    GameList(int gameListID, std::string listName);
    GameList(std::string listName);
    std::string getListName();
    void setListName(std::string name);
    int getNumGames();
    int getGameListID();
    void setGameListID(int id);
    Game* getGameAtIndex(int i);
    bool addGame(Game* game);
    bool removeGame(Game* game);
    void pinList();
    void unpinList();
    bool searchForGame(Game* game);
    //static bool compare_alpha(Game game_1, Game game_2);
    //static bool compare_desc(Game game_1, Game game_2);
    void print_list();
    //void sortList_in_alphabetical_order();
    //void sortList_in_desc_order();
    ~GameList();

private:
    std::array<Game*, MAX_SIZE> list;
    std::string listName;
    bool pinned;
    int gameListID;
    int findGame(int id);
    int numGames;
};

#endif //_GAMELIST_
