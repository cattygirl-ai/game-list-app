#include "../include/User.h"

/**
* @brief Construct a new User object with a username and password. 
* 
* @param username The user's username.  
* @param password The user's password.  
*/
User::User(int userID, std::string username, std::string password){
    this->userID = userID;
    this->username = username; 
    this->password = password; 
    this->points = 0;
    this->bio = "";
    this->steam_acc_link = "";
    this->discord_acc_link = "";
}

/**
         * @brief Construct a new User object with a username, password and social media links. 
         * @param userID The user's unique ID.
         * @param username The user's username.
         * @param password The user's password. 
         * @param points The user's in-app points/credits which can be used to purchase games and be transferred to other users. 
         * @param bio The user's biography which will be displayed on their profile. 
         * @param steam_acc_link The user's steam account link.
         * @param discord_acc_link The user's discord account link. 
*/
/*
    Function Name: User
    Description: This is an overloaded constructor which takes sets more parameter variables. Used by the
    database when creating a User ibject to return from searchForUser.
    Parameter Description: Strings containing the username, password, bio, and social media account links.
    Also, an integer for their points.
    Return Description: None
*/
User::User(int userID, std::string username, std::string password, int points, std::string bio, std::string steam_acc_link, std::string discord_acc_link){
    this->userID = userID; 
    this->username = username; 
    this->password = password; 
    this->points = points;
    this->bio = bio;
    this->steam_acc_link = steam_acc_link;
    this->discord_acc_link = discord_acc_link;
}

bool User::hasList(std::string listName) {
    for(int i = 0; i < lists.size(); i++){
        if(lists[i]->getListName() == listName){
            return true;
        }
    }
    return false;
}
GameList* User::getList(std::string name){
    for(int i = 0; i < lists.size(); i++){
        if(name == lists.at(i)->getListName()){
            return lists.at(i); 
        }
    }  
    return NULL;   
}

/**
         * @brief Add a new list to ther user's list of games lists. 
         * 
         * @param listName The name of the new list.  
         * @return true if the list is added successfully. 
         * @return false if the list already exists/cannot be added. 
         */
bool User::addList(int gameListID, std::string listName){
    if(hasList(listName)){
        return false;    
    }
    GameList* newList = new GameList(gameListID, listName);
    lists.push_back(newList); 
    return true; 
}

bool User::addGameToList(std::string listName, Game* game){
    GameList* listToAdd = getList(listName);
    if(listToAdd != NULL) {
        bool gameAdded = listToAdd->addGame(game);
        return gameAdded;
    }
    return false;
}

bool User::addList(std::string listName){
    if(hasList(listName)){
        return false;    
    }
    GameList* newList = new GameList(listName);
    lists.push_back(newList); 
    return true; 
}

/**
         * @brief Remove/delete a list from the user's list of games. 
         * 
         * @param listName The name of the list to be deleted.
         * @return true if the lists is deleted successfully. 
         * @return false if the list does not exist/cannot be deleted.
         */
bool User::removeList(std::string listName){  
    for(int i = 0; i < lists.size(); i++){
        if(lists.at(i)->getListName().compare(listName) == 0){ 
            lists.erase(lists.begin() + i); //delete the element at index i from the vector 
            return true; 
        } 
    }
    return false;
}

int User::getUserID(){
    return this->userID;
}

/**
         * @brief Get the user's points.  
         * 
         * @return The number of points the user has. 
         */
int User::getPoints(){
    return points; 
}

/**
* @brief Set the user's number of points.
* 
* @param points The number of points to be added to the user.
* @return The new number of points the user has.  
*/
void User::setPoints(int points){
    this->points = getPoints() + points; 
}

std::string User::getBio() {
    return this->bio;
}
void User::setBio(std::string bio) {
    this->bio = bio;
}
/**
         * @brief Get the user's username.
         * 
         * @return The user's username. 
         */
std::string User::getUserName(){
    return username; 
}

/**
         * @brief Transfer points from one user to another.  
         * 
         * @param username The user to transfer points too.  
         * @param points The number of points to transfer to the user. 
         * @return true if the user transferring has a sufficient number of points to transfer and the tranfer is completed successfully. 
         * @return false if the user transferring has an insufficient number of points and the transfer is unable to be completed. 
         */
bool User::givePoints(std::string username, int points){
    for(int i = 0; i < friends.size(); i++){
        if(friends.at(i).getUserName().compare(username) == 0){
            if(getPoints() >= points){
                friends.at(i).setPoints(points);
            }else{
                false; 
            }
        }else{
            return false; 
        }
    }
    return true;        
}

std::string User::getSteamLink() {
    return this->steam_acc_link;
}
std::string User::getDiscordLink() {
    return this->discord_acc_link;
}

/**
* @brief Set the user's steam link.  
* 
* @param link The user's steam link. 
*/
void User::setSteamLink(std::string link){
    steam_acc_link = link; 
}

/**
* @brief Set the user's discord link.
* 
* @param link The user's discord link. 
*/
void User::setDiscordLink(std::string link){
    discord_acc_link = link; 
}

/**
         * @brief Add a friend to the user's list of friends. 
         * 
         * @param username The username of the friend to be added. 
         */
//void User::addFriend(std::string username){    
    //User *newUser = database::instance().searchForUser(username);
    //friends.push_back(&newUser);  

//}

/**
* @brief Remove a friend from a user's list of friends. 
* 
* @param username The username of the friend to be removed. 
*/
void User::removeFriend(std::string username){
    for(int i = 0; i < friends.size(); i++){
        if(friends.at(i).getUserName().compare(username) == 0){
            friends.erase(friends.begin() + i); //delete the element at index i from the vector
        }
    } 
}
        /**
         * @brief Get the user's list of games lists. 
         * 
         * @return The user's list of games lists. 
         */
std::vector<GameList*> User::getLists(){
    return lists; 
}
