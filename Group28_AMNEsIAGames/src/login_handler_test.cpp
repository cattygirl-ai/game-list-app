#include "../include/login_handler.h"

int main(){
    login_handler lh;
    bool test;
    
    // 1. Create a user with a valid password.
    test = lh.createUser("Champagnepapi", "Inmyfeelings1!");
    if(test){
        std::cout <<"PASS: user successfully created" <<std::endl;
    } else {
        std::cout <<"FAIL: user could not be created" <<std::endl;
    }
    // 2. Login correctly
    User* user = lh.login("Champagnepapi", "Inmyfeelings1!");
    if(user != NULL){
        std::cout <<"PASS: login worked" <<std::endl;
    }
    else{
        std::cout <<"FAIL: could not login" <<std::endl;
    }
    test = user->addList("MyList1");
    if(test){
        std::cout <<"PASS: the list was successfully added" <<std::endl;
    }
    else{
        std::cout <<"FAIL: the list could not be added" <<std::endl;
    }
    // Try to add the same list twice
    test = user->addList("MyList1");
    if(test){
        std::cout <<"PASS: the list was NOT added because it's already in the database" <<std::endl;
    }
    else{
        std::cout <<"FAIL: " <<std::endl;
    }
    Game* marioKart = new Game(1111,"Mario Kart", "Game",10,"multi",2000,"nintendo");
    
    std::vector<GameList*> lists = user->getLists();
    test = user->addGameToList("Wishlist", marioKart);

    if(test){
        std::cout <<"PASS: game successfully added to " << lists[0]->getListName() <<std::endl;
    }
    else{
        std::cout <<"FAIL: could not add the game" <<std::endl;
    }

    std::cout <<"\nPrinting lists..." <<std::endl;
    for(int i = 0; i < lists.size(); i++){
        std::cout << lists[i]->getListName() << " has " << lists[i]->getNumGames() << std::endl;
        lists[i]->print_list();
    }
    std::cout <<"Finished printing\n" <<std::endl;

    test = lh.logout(user);
    if(test){
        std::cout <<"PASS: logout worked" <<std::endl;
    }
    else{
        std::cout <<"FAIL: could not logout" <<std::endl;
    }
    /*
    // 3. Attempt login with an incorrect password
    if(!lh.login("Ewere", "wrong")){
        std::cout <<"PASS" <<std::endl;
    }
    else{
        std::cout <<"FAIL: was able to login using the wrong password" <<std::endl;
    }
    // 3. Login with an incorrect username
    if(!lh.login("user2", "wrong")){
        std::cout <<"PASS: incorrect username and password" <<std::endl;
    }
    else{
        std::cout <<"FAIL: should not have logged in" <<std::endl;
    }
    // 4. Try logging in multiple times with the wrong username and get locked out
    for(int i = 0; i < 5; i++){
        test = lh.login("user2", "wrongAgain");
    }
    if(!test){
        std::cout <<"PASS: max attempts exceeded" <<std::endl;
    }
    else{
        std::cout <<"FAIL: too many allowed attempts" <<std::endl;
    }
    */
   return 0;
}