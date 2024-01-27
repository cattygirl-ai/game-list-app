#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <iostream>
#include <array>
#include <sqlite3.h>

class database
{
  public:
    virtual ~database();
    static const database& instance();
    bool createUser(std::string username, std::string password) const;
    int login(std::string username, std::string password) const;
    bool logout(std::vector<std::string> queries) const;
    std::vector<std::string> getUserData(std::string username) const;
    std::vector<std::string> getUserLists(int userID) const;
    std::vector<std::array<std::string,7>> getGameDataFromList(std::string listName, int userID) const;
    int getIDByUsername(std::string username) const;
    bool addGame(std::string name, std::string description="", int rating=0, std::string genre="", std::string company="", int year=0) const;
    bool addFriend(int userID, int friendID) const;
    bool addList(std::string listName, int userID) const;
    int getGameListID(std::string listName, int userID) const;
    bool removeFriend(int userID, int friendID) const;

    // Used for debugging
    void readAllUsers() const;
    void readAllGames() const;
    void readFriends(int userID) const;
  protected:
    database();
  private:
    database(const database& other) { };
    database& operator=(const database& other) { };
    sqlite3 *db;
    const char *dbFileName = "amnesiaGames.db";
    static const database* _instance;
    bool checkPassword(std::string password) const;
    bool hasList(std::string listName, int userID) const;
    bool hasFriend(int username, int friendname) const;
    bool uploadUserData() const;
};
#endif