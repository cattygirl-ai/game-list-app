/*
Author: Natalie Filep
Description of file contents: This class creates the database for the application
and includes various functions for getting data from it.
Date: 2022/10/22
*/
#include <iostream>
#include <vector>
#include "../include/sqlite3.h"
#include "../include/database.h"
#include "../include/pass_protect.h"

const database* database::_instance = NULL;

/*
Function Name: instance
Description: This function returns the reference to the database object, ensuring
there is at most 1.
Parameter Description: None
Return Description: A reference to the database instance.
*/
const database& database::instance()
{
  if (_instance == NULL)
    _instance = new database();

  return *_instance;
}

/*
Function Name: database
Description: A constructor which opens the database connection and creates the necessary tables.
Parameter Description: None
Return Description: None
*/
database::database()
{
    // 1. Attempt to open the database
    int rc = sqlite3_open(dbFileName, &db);
    
    if(rc != SQLITE_OK) {
        std::cout <<"Error opening the database: " << sqlite3_errmsg(db);
        exit(1);
    }

    // 2. Add all the tables
    char *zErrMsg = 0;
    std::string sql = "CREATE TABLE IF NOT EXISTS User (userID INTEGER PRIMARY KEY, username VARCHAR(30) NOT NULL UNIQUE, password VARCHAR(30) NOT NULL, points INT, bio VARCHAR(120), steamLink VARCHAR(120), discordLink VARCHAR(120));"
                        "CREATE TABLE IF NOT EXISTS Friend (userID INTEGER, friendID INTEGER, PRIMARY KEY(userID, friendID), FOREIGN KEY (userID) REFERENCES User(userID), FOREIGN KEY (friendID) REFERENCES User(userID));"
                        "CREATE TABLE IF NOT EXISTS Game (gameID INTEGER PRIMARY KEY, name VARCHAR(30) NOT NULL, description VARCHAR(120), rating INTEGER, genre VARCHAR(30), year INTEGER, company VARCHAR(30));"
                        "CREATE TABLE IF NOT EXISTS GameList (gameListID INTEGER PRIMARY KEY, listName VARCHAR(30) NOT NULL, userID INTEGER NOT NULL, FOREIGN KEY (userID) REFERENCES User(userID));"
                        "CREATE TABLE IF NOT EXISTS GameListEntry (gameListID INTEGER NOT NULL, gameID INTEGER NOT NULL, PRIMARY KEY(gameListID, gameID), FOREIGN KEY (gameListID) REFERENCES GameList(gameListID), FOREIGN KEY (gameID) REFERENCES Game(gameID));"
                        "CREATE TABLE IF NOT EXISTS Comment (commentID INTEGER PRIMARY KEY, commentText VARCHAR(120) NOT NULL, userID INTEGER NOT NULL, commentDate date, gameID INTEGER NOT NULL, FOREIGN KEY (userID) REFERENCES User(userID), FOREIGN KEY (gameID) REFERENCES Game(gameID));"
                        ;
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        std::cout <<"SQL Error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        exit(1);
    }
    std::cout <<"Construction finished" <<std::endl;
}

/*
Function Name: ~database
Description: A destructor that first uploads all the user data changed during this session
and then closes the connection to the database.
Parameter Description: None
Return Description: None
*/
database::~database()
{
    if(uploadUserData()){
        std::cout <<"User data successfully uploaded" <<std::endl;
    }else{
        std::cout <<"Issue, user data not uploaded properly" <<std::endl;
    }
    sqlite3_close(db);
}

bool database::uploadUserData() const{
    return false;
}

/*
Function Name: checkPassword
Description: This function checks the strength of the user's password, making sure it
is at least 8 characters long, includes at least 1 special character, 1 digit, 1 uppercase,
letter, 1 lowercase letter, and does NOT include the characters ', ", or = (to prevent SQL
injection attacks).
Parameter Description: A string containing the password to be checked.
Return Description: A boolean indicating whether the password is valid or not.
*/
bool database::checkPassword(std::string password) const{
    std::string specialChars = "!@#$%^&*()-+";
    std::string digits = "0123456789";
    std::string lowerChars = "abcdefghijklmnopqrstuvwxyz";
    std::string upperChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string illegalChars = "\'\"\\=";
    // If the password is less than 8 characters long, it fails
    if(password.size()<8){
        return false;
    }
    // Next, if there are no special characters, the password is invalid so we return
    // This is true when the first instance is equal to npos (the greatest value for an
    // element of size_t)
    if(password.find_first_of(specialChars) == std::string::npos)
            return false;
    // Check for at least 1 digit
    if(password.find_first_of(digits) == std::string::npos)
            return false;
    // Check for uppercase characters
    if(password.find_first_of(upperChars) == std::string::npos)
            return false;
    // Check for at least one lowercase character
    if(password.find_first_of(lowerChars) == std::string::npos)
            return false;
    // Lastly, check for any illegal characters
    if(password.find_first_of(illegalChars) != std::string::npos)
            return false;
    // If none of the conditions above failed, the password is valid
    return true;
}

/*
Function Name: createUser
Description: This function attempts to create a user with the given username and password.
If a user with the username already exists, false is returned.
Parameter Description: Two strings containing the username and password of the new user.
Return Description: A boolean indicating whether the user was successfully added to the
database or not.
*/
bool database::createUser (std::string username, std::string password) const{
    // We first check if a valid password is entered.
    if(!checkPassword(password)){
        std::cout <<"ERROR: The password is not strong enough."<< std::endl;
        return false;
    }
    char *zErrMsg = 0; 
    std::string encryptedPassword = pass_protect::encrypt(password);
    // Note that this type of insertion is prone to SQL injection
    // Optional to-do: escape every double quote
    std::string sql = "INSERT INTO User(userID, username, password, points, bio, steamLink, discordLink) VALUES (NULL,\"" + username + "\", \""+ encryptedPassword +"\", 0, \"\", \"\", \"\");";

    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    // If the unique constraint fails (there was already a user with this username),
    // an error message gets printed and false is returned.
    if(rc == SQLITE_CONSTRAINT_UNIQUE || rc == SQLITE_CONSTRAINT){
        std::cout <<zErrMsg<< std::endl;
        //std::cout <<"A user with this username already exists."<< std::endl;
        sqlite3_free(zErrMsg);
        return false;
    } // Any other errors also result in false being returned.
    else if(rc != SQLITE_OK) {
        std::cout <<"SQL Error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    }

    int id = getIDByUsername(username);
    if(id == -1){
        return false;
    }

    // Add 2 new default tables for this new user
    sql = "INSERT INTO GameList(gameListID,listName,userID) VALUES (NULL, \"Wishlist\", " + std::to_string(id) + "); INSERT INTO GameList(gameListID,listName,userID) VALUES (NULL, \"Favorites\"," + std::to_string(id) + ");";
    std::cout << sql <<std::endl;
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        std::cout <<"SQL Error: Default tables could not be created." << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}

/*
Function Name: login
Description: This function tries to login a user. If a user with the entered credentials
exists in the database, true is returned and they can successfully login.
Parameter Description: Two strings containing the username and password.
Return Description: An integer holding the userID. If the login was unsuccessful, 0 is returned.
*/
int database::login(std::string username, std::string password) const{
    char *zErrMsg = 0; 
    sqlite3_stmt *selectStmt;
    std::string realPassword;
    std::string encryptedPassword = pass_protect::encrypt(password);
    // If no user with this username exists, false is returned
    /*if(!searchForUser(username)){
        return false;
    }*/
    // std::string sql = "SELECT COUNT(*) FROM users WHERE username=\"" + username + "\" AND password=\""+ password +"\"";
    std::string sql = "SELECT userID, password FROM User WHERE username=\"" + username + "\";"; // Select the password matching the entered username

    // Get the text from the select statement
    int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), &selectStmt, nullptr);
    if(rc != SQLITE_OK) {
        std::cout <<"SQL Error: Could not prepare statement. " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return 0;
    }
    rc = sqlite3_step(selectStmt);
    if(rc == SQLITE_ROW) {
        // We store the result of the SELECT statement in a string...
        realPassword = (char*)sqlite3_column_text(selectStmt,1);
    } else {
        //std::cout <<"SQL Error: a row was not returned"<< std::endl;
        sqlite3_free(zErrMsg);
        return 0;
    }
    // ...and compare it to the password entered by the user.
    // If they match, the user can successfully login, so true is returned.
    // If not, the function returns false.
    if(encryptedPassword==realPassword){
        return sqlite3_column_int(selectStmt, 0);
    }
    return 0;
}

/*
Function Name: logout
Description: This function tries to logout a user. If the user's data during the session
was succesfully uploaded, true is returned. If an error occurs, false is returned.
Parameter Description: A vector (because we don't know how many update statements we may need)
containing the SQL update statements.
Return Description: A boolean indicating whether the user could successfully logout or not.
*/
bool database::logout(std::vector<std::string> queries) const{
    /*for(int i = 0; i < queries.size(); i++){
        std::cout << queries[i] << std::endl;
    }*/
    for(int i = 0; i < queries.size(); i++){
        std::cout << queries[i] << std::endl;
        char *zErrMsg = 0; 
        sqlite3_stmt *stmt;
        std::string sql = queries[i];

        int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    
        if(rc == SQLITE_CONSTRAINT_UNIQUE || rc == SQLITE_CONSTRAINT){
            std::cout <<"SQL Error: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
            return false;
        } // Any other errors also result in false being returned.
        else if(rc != SQLITE_OK) {
            std::cout <<"SQL Error: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
            return false;
        }
    }
    return true;
}

/*
Function Name: readAllUsers
Description: This prints out all the usernames and passwords. Used for debugging, will not
be used for the application as this is an obvious security breach.
Parameter Description: None
Return Description: None
*/
void database::readAllUsers() const{
    sqlite3_stmt *selectStmt;    
    std::string sql = "SELECT username, password FROM User";
    int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), &selectStmt, nullptr);

    std::cout<<"Username\t\t|\t\tPassword"<<std::endl;
    if (rc == SQLITE_OK) 
    {
        int ctotal = sqlite3_column_count(selectStmt);
        int res = 0;
        while ((rc = sqlite3_step(selectStmt)) == SQLITE_ROW) {
            std::string username = (char*)sqlite3_column_text(selectStmt, 0);
            std::string password = (char*)sqlite3_column_text(selectStmt, 1);
            std::cout<< username << "\t\t\t|\t\t\t" << password <<std::endl;
        }
    }
}

/*
Function Name: readAllGames
Description: This prints out all the games and thier ids and is used for debugging.
Parameter Description: None
Return Description: None
*/
void database::readAllGames() const{
    sqlite3_stmt *selectStmt;    
    std::string sql = "SELECT gameID, name FROM Game";
    int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), &selectStmt, nullptr);

    std::cout<<"ID\t\t|\t\tName"<<std::endl;
    if (rc == SQLITE_OK) 
    {
        int ctotal = sqlite3_column_count(selectStmt);
        int res = 0;
        while ((rc = sqlite3_step(selectStmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(selectStmt, 0);
            std::string name = (char*)sqlite3_column_text(selectStmt, 1);
            std::cout<< std::to_string(id) << "\t\t\t|\t\t\t" << name <<std::endl;
        }
    }
}

/*
Function Name: getUserData
Description: Returns the data of user with the matching username. If no such user exists,
an empty array is returned.
Parameter Description: A string containing the username to be searched for.
Return Description: An array of type boost::any (since there's mixed datatypes).
*/
std::vector<std::string> database::getUserData(std::string username) const{
    char *zErrMsg = 0;
    sqlite3_stmt *selectStmt;
    std::vector<std::string> userData;
    std::string sql = "SELECT * FROM User WHERE username=\"" + username + "\""; // Select the user info for the desired user

    // Prepare the statement
    int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), &selectStmt, nullptr);
    if(rc != SQLITE_OK) {
        std::cout <<"SQL Error: Could not prepare statement. " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return userData;
    }
    // Get the results of the query
    if((rc = sqlite3_step(selectStmt)) == SQLITE_ROW) {
        std::cout << "A user with this username ("<< username<<") has been found." << std::endl;
        for(int i = 0; i < sqlite3_data_count(selectStmt); i++){
            userData.push_back((char*)sqlite3_column_text(selectStmt, i));
        }
        return userData;
    }
    // If nothing is returned, we print a message saying there is no user matching the username
    std::cout << "No users match this username." << std::endl;
    sqlite3_free(selectStmt);
    // No user found, returning null array
    return userData;
}
/*
Function Name: getUserLists
Description: This returns all the lists the user has.
Parameter Description: String containing the username whose lists we want to get.
Return Description: A string vector containing the user's lists.
*/
std::vector<std::string> database::getUserLists(int userID) const{
    sqlite3_stmt *selectStmt;
    std::vector<std::string> lists;
    std::string sql = "SELECT listName FROM GameList WHERE userID=\"" + std::to_string(userID) + "\""; 
    int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), &selectStmt, nullptr);

    if (rc == SQLITE_OK) 
    {
        int ctotal = sqlite3_column_count(selectStmt);
        while ((rc = sqlite3_step(selectStmt)) == SQLITE_ROW) {
            std::string listname = (char*)sqlite3_column_text(selectStmt, 0);
            lists.push_back(listname);
        }
    }
    return lists;
}

/*
Function Name: searchForUser
Description: This function returns true if there's a user matching the provided username 
in the database, false if no matches are found.
Parameter Description: A string containing the username.
Return Description: A boolean indicating whether the user is in the database or not.
*/
int database::getIDByUsername(std::string username) const{
    char *zErrMsg = 0; 
    sqlite3_stmt *selectStmt;
    std::string sql = "SELECT userID FROM User WHERE username=\"" + username + "\";";
    int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), &selectStmt, nullptr);
    if(rc != SQLITE_OK) {
        std::cout <<"SQL Error: Could not prepare statement. " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return -1;
    }
    if((rc = sqlite3_step(selectStmt)) == SQLITE_ROW) {
        int userID = sqlite3_column_int(selectStmt,0);
        std::cout << "The user id matching "<< username << " is " << std::to_string(userID) << std::endl;
        return userID;
    }
    // Otherwise, no users matched that username.
    std::cout << "No id matches that username." << std::endl;
    sqlite3_free(selectStmt);
    return -1;
}

/*
Function Name: addGame
Description: This method adds a game to the games table in the database.
Parameter Description: A unique integer id of the game, strings containing its name, description, and genre, as
well as 2 ints containing the year the game was released and its rating /10.
Return Description: True if the game was successfully added, false if it was not.
*/
//bool addGame(std::string name, std::string description="", int rating=0, std::string genre="", std::string company="", int year=0) const;
bool database::addGame(std::string name, std::string description, int rating, std::string genre, std::string company, int year) const{
    char *zErrMsg = 0; 
    std::string sql = "INSERT INTO Game VALUES (NULL,\"" + name + "\", \"" + description + "\"," + std::to_string(rating) + ",\"" + genre + "\", \"" + company + "\", " + std::to_string(year) + ");";

    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    
    if(rc == SQLITE_CONSTRAINT_UNIQUE || rc == SQLITE_CONSTRAINT){
        std::cout <<"A game with this ID already exists."<< std::endl;
        sqlite3_free(zErrMsg);
        return false;
    } // Any other errors also result in false being returned.
    else if(rc != SQLITE_OK) {
        std::cout <<"SQL Error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}

// Checks whether the user already has a list with this name
bool database::hasList(std::string listName, int userID) const{
    char *zErrMsg = 0; 
    sqlite3_stmt *selectStmt;
    std::string sql = "SELECT COUNT(GameListID) FROM GameList WHERE listName=\"" + listName + "\" AND userID=" + std::to_string(userID) + ";";
    std::cout << "In hasList()..." << std::endl;
    std::cout << sql << std::endl;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), &selectStmt, nullptr);
    if(rc != SQLITE_OK) {
        std::cout <<"SQL Error: Could not prepare statement. " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    }
    // If the count of the resulting query was 0, a list with that name already exists
    if((rc = sqlite3_step(selectStmt)) == SQLITE_ROW) {
        if(sqlite3_column_int(selectStmt,0)==0){
            return false;
        }
    }
    // Otherwise, we did not have a list with that name
    sqlite3_free(selectStmt);
    return true;
}

bool database::addList(std::string listName, int userID) const{
    char *zErrMsg = 0; 
    bool test = hasList(listName, userID);
    std::cout << test << std::endl;
    if(!test){
        std::string sql = "INSERT INTO GameList VALUES (NULL,\"" + listName + "\"," + std::to_string(userID) + ");";

        int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
        
        if(rc != SQLITE_OK) {
            std::cout <<"SQL Error: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
            return false;
        }
        return true;
    }
    return false;
}

int database::getGameListID(std::string listName, int userID) const {
    char *zErrMsg = 0; 
    sqlite3_stmt *selectStmt;
    std::string sql = "SELECT gameListID FROM GameList WHERE listName=\"" + listName + "\" AND userID =" + std::to_string(userID) + ";";
    int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), &selectStmt, nullptr);
    if(rc != SQLITE_OK) {
        std::cout <<"SQL Error: Could not prepare statement. " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return -1;
    }
    if((rc = sqlite3_step(selectStmt)) == SQLITE_ROW) {
        int gameListID = sqlite3_column_int(selectStmt,0);
        std::cout << "The game list ID matching "<< listName << " is " << std::to_string(gameListID) << std::endl;
        return gameListID;
    }
    // Otherwise, no users matched that username.
    std::cout << "No id matches that username." << std::endl;
    sqlite3_free(selectStmt);
    return -1;
}

// Returns all the Game data from the list given the matching list name
std::vector<std::array<std::string,7>> database::getGameDataFromList(std::string listName, int userID) const {
    sqlite3_stmt *selectStmt;
    std::vector<std::array<std::string, 7>> games; //From Isaac: changed this for u :-)
    std::array<std::string, 7> gameData;

    int gameListID = getGameListID(listName, userID);
    std::string sql = "SELECT * FROM Game g INNER JOIN GameListEntry gle ON g.GameID=gle.GameID WHERE GameListID=\"" + std::to_string(gameListID) + "\";";
    int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), &selectStmt, nullptr);
    if (rc == SQLITE_OK) 
    {
        while ((rc = sqlite3_step(selectStmt)) == SQLITE_ROW) {
            // We put all the data for the individual game into an array
            for(int i = 0; i < sqlite3_data_count(selectStmt); i++){
                std::string s((char*)sqlite3_column_text(selectStmt, i));
                gameData[i] = s;
            }
            // We then add the game to the list
            games.push_back(gameData);
        }
    }

    return games;
}



/*
Function Name: addFriend
Description: This method adds a game to the games table in the database.
Parameter Description: A unique integer id of the game, strings containing its name, description, and genre, as
well as 2 ints containing the year the game was released and its rating /10.
Return Description: True if the game was successfully added, false if it was not.
*/
bool database::addFriend(int userID, int friendID) const{
    char *zErrMsg = 0;
    // First check if the friend exists...
    /*if(!searchForUser(friendname)){
        //...If the friend is not found, we return false
        return false;
    }*/
    //...Otherwise we proceed and attempt to add them to the table
    std::string sql = "INSERT INTO Friend VALUES (\"" + std::to_string(userID) + "\", \""+ std::to_string(friendID) +"\");";

    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    // Check whether the friend has already been added
    if(rc == SQLITE_CONSTRAINT_UNIQUE || rc == SQLITE_CONSTRAINT){
        std::cout <<"This friend has already been added."<< std::endl;
        sqlite3_free(zErrMsg);
        return false;
    } // Any other errors also result in false being returned.
    else if(rc != SQLITE_OK) {
        std::cout <<"SQL Error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}

/*
Function Name: hasFriend
Description: This method determines whether a user has a friend matching the given name.
Parameter Description: Two strings containing the usernames of the user and the friend.
Return Description: True if the user has a friend with that name, false if they don't.
*/
bool database::hasFriend(int userID, int friendID) const {
    char *zErrMsg = 0; 
    sqlite3_stmt *selectStmt;
    std::string sql = "SELECT COUNT(*) FROM Friend WHERE userID=\"" + std::to_string(userID) + "\" AND friendID=\""+ std::to_string(friendID) +"\";";
    int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), &selectStmt, nullptr);
    if(rc != SQLITE_OK) {
        std::cout <<"SQL Error: Could not prepare statement. " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    }
    // If the count of the resulting query was one, a friend matching the name was found and true is returned
    if((rc = sqlite3_step(selectStmt)) == SQLITE_ROW) {
        int numUser = sqlite3_column_int(selectStmt,0);
        if(numUser==1){
            return true;
        }
    }
    // Otherwise, the friend DID NOT have a friend with that username, so we return false
    sqlite3_free(selectStmt);
    return false;
}

/*
Function Name: removeFriend
Description: This method removes the friend with the specified name.
Parameter Description: Two strings containing the usernames of the user and the friend to remove.
Return Description: True if the friend was successfully removed, false if they could not be.
*/
bool database::removeFriend(int userID, int friendID) const {
    char *zErrMsg = 0;
    // First check if the user has this friend
    if(!hasFriend(userID, friendID)){
        return false;
    }
    std::string sql = "DELETE FROM Friend WHERE userID=\"" + std::to_string(userID) + "\" AND friendID=\""+ std::to_string(friendID) +"\";";

    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
     if(rc != SQLITE_OK) {
        std::cout <<"SQL Error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}

/*
Function Name: readFriends
Description: This prints out all the friends of the given user. Used for debugging.
Parameter Description: A string containing the username whose friends we wish to see.
Return Description: None
*/
void database::readFriends(int userID) const{
    sqlite3_stmt *selectStmt;    
    std::string sql = "SELECT friendID FROM friends WHERE userID=\"" + std::to_string(userID) + "\";";
    int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), &selectStmt, nullptr);

    std::cout<<"Friends"<<std::endl;
    std::cout<<"-------"<<std::endl;
    if (rc == SQLITE_OK) 
    {
        while ((rc = sqlite3_step(selectStmt)) == SQLITE_ROW) {
            std::string name = (char*)sqlite3_column_text(selectStmt, 0);
            std::cout<< name <<std::endl;
        }
    }
}
