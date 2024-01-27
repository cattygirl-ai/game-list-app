/**
 * @author:molaleye
 *Description: Test class for GameList class 
 *@verison 1.0
 *@since 2022-11-10*/

#include "../include/GameList.h"

//TEST CLASS FOR GAMELIST
//CREATES 1 GAMELIST OBJECT AND 3 GAME OBJECTS
//TESTS THE FUNCTIONALITY OF THE GAMELIST FUNTIONS
int main(){
    GameList* list1 = new GameList("MyList2");
    std::cout << list1->getNumGames() << std::endl;
    std::cout << list1->getListName() << std::endl;
    
    Game* marioKart = new Game(1111,"Mario Kart", "Game",10,"multi",2000,"nintendo");
    list1->addGame(marioKart);
    list1->print_list();
    return 0;
}