/**
 * @author:molaleye
 * @author: Natalie Filep
 * Description: This class represents a list of games the user has added. Each list has
 * a unique name and id.
 * @version 2.0
 * @since 2022-11-29*/

#include "../include/GameList.h"

GameList::GameList(int gameListID, std::string listName){
    this->gameListID = gameListID;
    this->listName = listName;
    this->numGames = 0;
}
/**
 * GameList constructor
 * Initializes GameList and gives it a name
 *@param listName
 */
GameList::GameList(std::string listName)
{
    this->listName = listName;
    this->numGames = 0;
}

/**
 * Returns a list Name
 *@return listName
 */
std::string GameList::getListName()
{
    return listName;
}

void GameList::setListName(std::string name) {
    listName = name;
}

int GameList::getGameListID(){
    return gameListID;
}

void GameList::setGameListID(int gameListID){
    this->gameListID = gameListID;
}

int GameList::getNumGames(){
    return numGames;
}

/**
 * @brief returns the Game object at the given index.
 * 
 * @param i The index of the Game we'd like to return.
 * @return Game* 
 */
Game* GameList::getGameAtIndex(int i){
    // Make sure the index is not out of bounds
    if(i < 0 || i > MAX_SIZE){
        return NULL;
    }
    // Return the game at index i
    return list[i];
}

/**
 * Returns the index of a given game within the list.
 * If the game is NOT in the list, -1 is returned.
 */
int GameList::findGame(int id)
{
    for (int i = 0; i < numGames; i++)
    {
        if (list[i]->getGameID() == id)
        {
            return i;
        }
    }
    return -1;
}

/**
 * Returns the index of a given game within the list.
 * If the game is NOT in the list, -1 is returned.
 */
bool GameList::searchForGame(Game* game)
{
    int id = findGame(game->getGameID());
    return (id != -1);
}

/**
 * adds a game to the list
 * @param game
 *@return True if the game could be added. False if the list is full or the game
 * is already included in the list.
 */
bool GameList::addGame(Game* game)
{
    int id = findGame(game->getGameID());
    // If the game is already in the list or the list is full,
    // the game cannot be added.
    if (id != -1 && numGames >= GameList::MAX_SIZE)
    {
        return false;
    }
    // Otherwise, increase the number of games and add it to the list.
    numGames++;
    list[numGames - 1] = game;
    return true;
}
/**
 * removes a game to the list
 * @param game
 *@return True if the game was successfully removed.
 */
bool GameList::removeGame(Game* game)
{
    int index = findGame(game->getGameID());
    // Game not in list so it cannot be removed.
    if (index == -1)
    {
        return false;
    }
    // Otherwise the game was found, so we remove it from the list.
    list[index] = NULL;
    numGames--;
    return true;
}
/**
 * pins the list
 *@return void
 */
void GameList::pinList()
{
    if (!pinned)
    {
        pinned = true;
    }
    else
    {
        std::cout << "list is already pinned" << std::endl;
    }
}
/**
 * unpins the list
 *@return void
 */
void GameList::unpinList()
{
    if (pinned == true)
    {
        pinned = false;
        std::cout << "list has been unpinned" << std::endl;
    }
    else
    {
        std::cout << "list was not pinned" << std::endl;
    }
}

/**
 * checks if the game in the list are sorted in alphabetical order
 *@return void
 */
/*static bool GameList::compare_alpha(Game game_1, Game game_2)
{
    return game_1.getName() < game_2.getName();
}*/
/**
 * checks if the game in the list are sorted in descending order
 *@return void
 */
/*static bool GameList::compare_desc(Game game_1, Game game_2)
{
    return game_1.getName() > game_2.getName();
}*/

/**
 * sorts the list in alphabetical order
 *@return void
 */
/*void GameList::sortList_in_alphabetical_order()
{
    std::sort(list.begin(), list.end(), compare_alpha);
    std::cout << "Sorted in Alphabetical Order\n";
    print_list();
}*/

/**
 * sorts the list in descending order
 *@return void
 */
/*void GameList::sortList_in_desc_order()
{
    std::sort(list.begin(), list.end(), compare_alpha);
    std::cout << "Sorted in Alphabetical Order\n";
    print_list();
}*/

/**
 * prints the list of games
 *@return void
 */
void GameList::print_list()
{
    for (int i = 0; i < numGames; i++)
    {
        std::cout << "Game ID : "<<list[i]->getGameID()<<" Name: "<<list[i]->getName() << std::endl;
    }
}

/**
 * Destructor
 * GameList object is destroyed
 */
GameList::~GameList()
{
}
