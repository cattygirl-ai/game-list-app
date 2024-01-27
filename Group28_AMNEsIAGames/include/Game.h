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

// Checks if _GAME_ IF DECLARED
#ifndef GAME_H
// Defines_GAMELIST_ if above fails
#define GAME_H

#include <vector>
#include <iostream>
#include "Comment.h"

class Game{
    private:
        int gameID;
        std::string name;  // name of the game
        std::string description; //game description
        int rating; //game ratings
        std::string genre; //genre of the game
        int year; // year the game was created
        std::string company;  // name of the company   
        //vector<Comment> comments;  // an array of comments

    public:
        Game();
        Game(int id, std::string name, std::string description, int rating, std::string genre, int year, std::string company);
        ~Game();
        int getGameID() const;
        std::string getName();
        int getRating();
        std::string getGenre();
        int getYear();
        std::string getDescription();
        std::string getCompany();
        
        void setName(std::string name);
        void setGenre(std::string genre);
        void setRating(int rating);
        void setYear(int year);
        void setDescription(std::string description);
        void setCompany(std::string company);
        void print_game_info();
        bool operator==(const Game& other); // Overloading the equality operator
        // Wishlist methods
        // void addComment(Comment c); // game
        // void removeComment(int id);
        void playGame(); // written as an empty method that prints the output, like "launching game" 
        void quitGame(); // written as an empty method that prints the output, "exiting game"
};
#endif//_GAME_
