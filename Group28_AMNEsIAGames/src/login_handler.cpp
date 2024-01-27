/*
Author: Natalie Filep
Description of file contents: This class handles any login attempts made.
Date: 2022/10/22
*/
#include <iostream>
#include <vector>
#include "../include/User.h"
#include "../include/sqlite3.h"
#include "../include/login_handler.h"
#include "../include/database.h"

/*
Function Name: login_handler
Description: A constructor that initializes the number of login attempts to 0.
Parameter Description: None
Return Description: None
*/
login_handler::login_handler() {
    numLoginAttempts = 0;
}

/*
Function Name: ~login_handler
Description: A destructor that closes the database connection.
Parameter Description: None
Return Description: None
*/
login_handler::~login_handler() {
    sqlite3_close(db);
    std::cout <<"Login Handler Object destroyed" <<std::endl;
}

/*
Function Name: login
Description: Given a username and password, this method determines whether
the user exists and allows them to login if they have not already had 4
incorrect attempts.
Parameter Description: Two strings that hold the entered username and password.
Return Description: True if the user exists and they have not exceeded their 
maximum attempts, false if the user does not exist or if they have used too
many attempts.
*/
User* login_handler::login(std::string username, std::string password){
    int userID = database::instance().login(username, password);
    numLoginAttempts++; // Increase the number of login attempts

    // If the userID is 0, then the login has failed
    if(userID == 0) {
        // We check if they have any login attempts left
        if(numLoginAttempts > MAX_LOGIN_ATTEMPTS){
            std::cout <<"Login attempts exceeded" <<std::endl;
            exit(0); // If maximum number of login attempts are exceeded, the program exits
        }
        return NULL; // Since the login info is incorrect, NULL is returned
    }
    // Otherwise, we return a User object with their data
    std::vector<std::string> userData = database::instance().getUserData(username);
    /*for(int i = 0; i < userData.size(); i++){
        std::cout << std::to_string(i) << ": " << userData[i] <<std::endl;
    }*/
    User* user = new User(userID, username, password,std::stoi(userData[3]),userData[4],userData[5],userData[6]);

    // Then we add in their lists
    std::vector<std::string> userLists = database::instance().getUserLists(userID);
    for(int i = 0; i < userLists.size(); i++){
        user->addList(userLists[i]);
    }

    // Then we add in the games for each list

    // From Isaac: temporarily commented out :)
    std::vector<GameList*> lists = user->getLists();
    Game* game;
    for(int i = 0; i < lists.size(); i++){
        std::vector<std::array<std::string,7>> gamesInList = database::instance().getGameDataFromList(lists[i]->getListName(), userID);
        for(int j = 0; j < gamesInList.size(); j++){
            game = new Game(std::stoi(gamesInList[j][0]), gamesInList[j][1], gamesInList[j][2], std::stoi(gamesInList[j][3]), gamesInList[j][4], std::stoi(gamesInList[j][5]), gamesInList[j][6]);
            lists[i]->addGame(game);
        }
    }

    // Lastly, we should also add the users friends
    return user;
}

bool login_handler::logout(User* user) {
    bool logout_successful = false;
    std::vector<std::string> queries;

    // 1. We write the user data to the database
    int userID = user->getUserID();
    std::string userUpdateQuery = "UPDATE User SET points=" + std::to_string(user->getPoints()) + ", bio='" + user->getBio() + "', steamLink='" + user->getSteamLink() + "', discordLink='"+ user->getDiscordLink() + "' WHERE userID = " + std::to_string(userID) + ";";
    queries.push_back(userUpdateQuery);
    
    // 2. For each of the user's lists, we add it to the database
    std::vector<GameList*> lists = user->getLists();

    // Note: the index starts from 2 since the 2 default lists have already been added
    for(int i = 2; i < lists.size(); i++){
        queries.push_back("INSERT INTO GameList(gameListID,listName,userID) VALUES ("+std::to_string(lists[i]->getGameListID())+", '" + lists[i]->getListName() + "'," + std::to_string(userID) + ");");
    }

    // 3. Next, we add the games in each list
    for(int i = 0; i < lists.size(); i++){
        std::cout << "------" << lists[i]->getListName() << " has " << lists[i]->getNumGames() << " of games " <<std::endl;
        for(int j = 0; j < lists[i]->getNumGames(); i++){
            queries.push_back("INSERT INTO GameListEntry(gameListID,gameID) VALUES ('" + std::to_string(lists[i]->getGameListID()) + "'," + std::to_string(lists[i]->getGameAtIndex(j)->getGameID()) + ");");
        }
    }

    logout_successful = database::instance().logout(queries);
    delete user;
    return logout_successful;
}

/*
Function Name: createUser
Description: This method attempts to create a user with the given username and 
password.
Parameter Description: The username and password for the user to be created.
Return Description: True, if the user was successfully added to the database.
False, if the user could not be added.
*/
const bool login_handler::createUser(std::string username, std::string password){
    bool success = database::instance().createUser(username, password);
    return success;
}

/*
Function Name: getNumLoginAttempts
Description: This method returns the number of login attempts made so far.
Parameter Description: None
Return Description: An integer containing the number of login attempts made so far.
*/
int login_handler::getNumLoginAttempts(){
    return numLoginAttempts;
}
