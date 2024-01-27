/**
 *@author: Tina Agbamuche
  @author:Mary Olaleye
 *Description: This class lets users, know what a game is about (e.g. date created, genre etc.) so that they can know if it fits their interests
 *Game()constructor , initializes a Game object
 *the getGameID() returns the game ID
 *the getName() returns the game name
 *the getCompany() returns the company that made the game
 *the getYear() returns the year game was released
 *the getGenre() returns the game genre
 *the getRating() returns the game rating
 *the getDescription() returns the game description
 *the print_game_info() prints information about the game
 *the ~Game deconstuctor destroys the Game object when done.
 *@version 2.0
 *@since 2022-11-29*/
#include "../include/Game.h"

// API fetcher handler If the information is not available (ex. problems with pulling data from API), display a placeholder value for those fields (pass)

// default constructor gets values of the variable.

Game::Game()
{
    this->name = "";
    this->description = "";
    this->rating = 0;
    this->genre = "";
    this->year = 0; // use this-> to set the member variables of the class
    this->company = "";
}
// constructor that takes parameters
Game::Game(int gameID, std::string name, std::string description, int rating, std::string genre, int year, std::string company)
{
    // this->gameID= gameID++; //needs to be fixed, dont pass as a parameter. because the user is not setting it in constructor
    this->gameID = gameID;
    this->name = name;
    this->description = description;
    this->rating = rating;
    this->genre = genre;
    this->year = year;
    this->company = company;
}

Game::~Game()
{
}

// database has to be up to date. method addGame. method returns a bool that checks if game was successfully added

/*
const bool Game::addGame(int gameID, std::string name, std::string description, int rating, std::string genre, int year, std::string company)
{
    bool perfecto = database::instance().addGame(gameID, name, description, rating, genre, year);
    return true;
}
*/

void Game::setName(std::string newName)
{
    this->name = newName;
}

void Game::setGenre(std::string newGenre)
{
    this->genre = newGenre;
}
void Game::setYear(int newYear)
{
    this->year = newYear;
}
void Game::setCompany(std::string newCompany)
{
    this->company = newCompany;
}

void Game::setDescription(std::string newDescription)
{
    this->description = newDescription;
}

void Game::setRating(int newRating)
{
    this->rating = newRating;
}

/*
the setter functions shouldn't really be linked to anything
they just take a value and assign it to the corresponding instance variable in the object   */

// GETTER FUNCTIONS
int Game::getGameID() const
{
    return gameID;
}

std::string Game::getCompany()
{
    return company;
}

int Game::getYear()
{
    return year;
}

std::string Game::getName()
{ // returns the name of the game
    return name;
}

std::string Game::getGenre()
{ // returns the genre of the game
    return genre;
}
// deleted year and company

int Game::getRating()
{ // returns the game ratings. collected from an API
    return rating;
}

std::string Game::getDescription()
{ // returns the game description
    return description;
}

bool Game::operator==(const Game &other)
{
    // std::cout << "--Game ID: " << std::to_string(this->getGameID()) << std::endl;
    // std::cout << "--Other Game ID: " << std::to_string(other.getGameID()) << std::endl;
    return (this->getGameID() == other.getGameID());
}

void Game::print_game_info()
{    // prints information about the game
    std::cout << "Game Information" << std::endl;
    std::cout << "ID : " << getGameID() << std::endl;
    std::cout << "Name : " << getName() << std::endl;
    std::cout << "Description: " << getDescription() << std::endl;
    std::cout << "Rating : " << getRating() << std::endl;
    std::cout << "Genre: " << getGenre() << std::endl;
    std::cout << "Year : " << getYear() << std::endl;
    std::cout << "Company : " << getCompany() << std::endl;
}
/*
int Game::getID()
{ // returns the year game was created
    return gameID;
}
*/

// TEST CASE

/*
1. Click on a game to display more information about it (pass)
2. If the information is not available (ex. problems with pulling data from API), display a placeholder value for those fields (pass)
*/