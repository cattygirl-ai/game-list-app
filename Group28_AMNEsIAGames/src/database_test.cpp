#include "../include/database.h"
//#include "login_handler.h"

int main() {
    bool test;
    
    // 1. Create a user with a valid password
    test = database::instance().createUser("Champagnepapi", "Inmyfeelings1!");
    if(test){
        std::cout << "----PASS: test 1, create a user with a valid password." << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }
    /*
    // 2. Attempt to create a user that already exists
    test = database::instance().createUser("user1", "passworD1!");
    if(!test){
        std::cout << "----PASS: test 2, try to create a user that already exists" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }

    // 3. Attempt to create a user with an invalid password (not long enough)
    test = database::instance().createUser("newUser", "pasD1!");
    if(!test){
        std::cout << "----PASS, cannot create a user whose password is too short" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }

    // 4. Attempt to create a user with an invalid password (no lowercase character)
    test = database::instance().createUser("newUser", "ABCDEFGH1!");
    if(!test){
        std::cout << "----PASS, could not create a password without lowercase characters" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }

    // 5. Attempt to create a user with an invalid password (no uppercase character)
    test = database::instance().createUser("newUser", "abcdefgh1!");
    if(!test){
        std::cout << "----PASS, cannot create a password without an uppercase character" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }

    // 6a. Attempt to create a user with an invalid password (contains illegal character)
    test = database::instance().createUser("newUser", "abcdefgh=1!");
    if(!test){
        std::cout << "----PASS, illegal character" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }

    // 6b. Attempt to create a user with an invalid password (contains illegal character)
    test = database::instance().createUser("newUser", "abc'defgh1!");
    if(!test){
        std::cout << "----PASS, illegal character" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }
    
    // 6c. Attempt to create a user with an invalid password (contains illegal character)
    test = database::instance().createUser("newUser", "abcd\"efgh1!");
    if(!test){
        std::cout << "----PASS, illegal character" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }

    // 7. Attempt to create a user with an invalid password (contains no digit)
    test = database::instance().createUser("newUser", "abcdefghA!");
    if(!test){
        std::cout << "----PASS, no digit" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }

    // 8. Attempt to create a user with an invalid password (contains no special character)
    test = database::instance().createUser("newUser", "password1");
    if(!test){
        std::cout << "----PASS, no special character" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }

    database::instance().readAllUsers();

    // 9. Attempt to login to an existing account
    test = database::instance().login("user1", "passworD1!");
    if(test){
        std::cout << "----PASS, logged in" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }

    // 10a. Attempt to login to an existing account, but uses incorrect password.
    test = database::instance().login("newUser", "wrong");
    if(!test){
        std::cout << "----PASS, prohibited login" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }

    // 10b. Attempt to login to an existing account, but uses incorrect username.
    test = database::instance().login("noSuchUser", "wrong");
    if(!test){
        std::cout << "----PASS, prohibited login" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }

    
    // 11a. Search for an existing user:
    std::array<boost::any, 6> userQuery = database::instance().getUserData("user1");
    if(!(userQuery[0].empty())){
        std::cout << "----PASS, user found" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }
    // 11b. Search for a user not in the database:
    userQuery = database::instance().getUserData("noSuchUser");
    if((userQuery[0].empty())){
        std::cout << "----PASS, user not found" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }
    */
    database::instance().readAllUsers();

    // 12a. Add a game to the database (only use 2 params)
    test = database::instance().addGame("Mario Party 2");
    if(test){
        std::cout << "----PASS, game added" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }
    // 12b. Add a game to the database (use all params). Note, 2 games can have the same name.
    test = database::instance().addGame("Mario Party", "This is a fun multiplayer Nintendo game", 5, "Multiplayer", "Nintendo", 2010);
    if(test){
        std::cout << "----PASS, game added" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }
    // 12c. Try to add a game with an already existing ID
    test = database::instance().addGame("New Game");
    if(!test){
        std::cout << "----PASS, game could not be added" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }
    // 13a. Try to give the user a new friend.
    // database::instance().createUser();
    test = database::instance().addFriend(1, 2);
    if(test){
        std::cout << "----PASS, friend added" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }
    database::instance().readFriends(1);
    /*
    // 13b. Try to add a friend already in the friends list
    test = database::instance().addFriend("user1", "friend");
    if(!test){
        std::cout << "----PASS, friend already added" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }
    database::instance().readAllUsers();

    // 13c. Try to add a friend not in the database
    test = database::instance().addFriend("user1", "noSuchUser");
    if(!test){
        std::cout << "----PASS, this friend is imaginary" << std::endl;
    }else{
        std::cout << "Fail" << std::endl;
    }

    // 14a. Remove the friend we added.
    test = database::instance().removeFriend("user1", "friend");
    if(test){
        std::cout << "----PASS, this friend is imaginary" << std::endl;
    }else{
        std::cout << "Failed to remove friend that is in list." << std::endl;
    }

    // 14b. Remove a friend that is not in the friends list.
    test = database::instance().removeFriend("user1", "noSuchUser");
    if(!test){
        std::cout << "----PASS" << std::endl;
    }else{
        std::cout << "Failed to remove friends." << std::endl;
    }
*/
    return 0;
}
