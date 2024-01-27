#ifndef USER_H
#define USER_H

//#include <stdio.h>
#include <iostream>
#include <vector>
#include "GameList.h"
#include "Subject.h"

/**
 * @brief User class that constructs new User objects for the AMNEsIA Games application. 
 */

class User : public Subject {

    private:  
        int userID;
        std::string username;  
        std::string password;
        int points; 
        std::string bio;
        std::string steam_acc_link;
        std::string discord_acc_link; 
        std::vector<GameList*> lists; 
        std::vector<User> friends;  
    public:
        User(int userID, std::string username, std::string password); 
        User(int userID, std::string username, std::string password, int points, std::string bio, std::string steam_acc_link, std::string discord_acc_link);
        bool addList(int gameListID, std::string listName);
        bool addList(std::string listName);
        bool addGameToList(std::string listName, Game* game);
        bool removeList(std::string listName); 
        int getUserID();
        std::string getUserName();
        int getPoints();
        int getGameID(); 
        void setPoints(int points);
        std::string getBio();
        void setBio(std::string bio);
        bool givePoints(std::string username, int points);
        std::string getSteamLink();
        std::string getDiscordLink();
        void setSteamLink(std::string link);
        void setDiscordLink(std::string link);
        void addFriend(std::string username);
        void removeFriend(std::string username);
        std::vector<GameList*> getLists();
        GameList* getList(std::string name);
        bool hasList(std::string listName);    
}; 
#endif

