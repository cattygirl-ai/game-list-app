#ifndef LOGIN_HANDLER_H
#define LOGIN_HANDLER_H
#include <iostream>
#include "../include/User.h"
#include "sqlite3.h"

class login_handler
{ 
    private:
        sqlite3 *db;
        int numLoginAttempts;
    public:
        const int MAX_LOGIN_ATTEMPTS = 4;
        login_handler();
        ~login_handler();
        User* login(std::string username, std::string password);
        bool logout(User* user);
        const bool createUser(std::string username, std::string password);
        int getNumLoginAttempts();
};
#endif
