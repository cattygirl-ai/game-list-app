#include "../include/Game.h"

int main(){
    Game* newGame = new Game(1,"Call of Duty","This is a game",10,"FPS",2012,"Activision");
    Game* newGame2 = new Game(2,"Call of Duty","This is a game",10,"FPS",2012,"Activision");
    bool areEqual = (newGame == newGame2);
    std::cout << "Game ID: " << std::to_string(newGame->getGameID()) << std::endl;
    std::cout << "Game 2 ID: " << std::to_string(newGame2->getGameID()) << std::endl;
    newGame->print_game_info();
    newGame2->print_game_info();
    std::cout << areEqual << std::endl;

    Game* newGame3 = new Game(1,"Diff game","This is a different game",10,"FPS",2012,"Activision");
    areEqual = (*newGame == *newGame3);
    std::cout << "Game 3 ID: " << std::to_string(newGame3->getGameID()) << std::endl;
    newGame3->print_game_info();
    std::cout << areEqual << std::endl;
    /*
    Game *newGame = new Game(); 
    newGame->setName("Call of Duty"); 
    newGame->setGenre("FPS"); 
    newGame->setYear(2012);
    newGame->setCompany("Activision");
    newGame->setDescription("A game for basic plebs.");
    newGame->setRating(5);


    printf("%s\n",newGame->getName().c_str()); 
    printf("%s\n",newGame->getGenre().c_str());
    printf("%d\n",newGame->getYear()); 
    printf("%s\n",newGame->getCompany().c_str()); 
    printf("%s\n", newGame->getDescription().c_str()); 
    printf("%d\n", newGame->getRating()); 


    Game bestGame("Animal Crossing", "The BEST game ever that only god tier gamers play.", 10, "fun", 2019, "Nintendo"); 

    printf("\n"); 

    printf("%s\n",bestGame.getName().c_str()); 
    printf("%s\n",bestGame.getGenre().c_str());
    printf("%d\n",bestGame.getYear()); 
    printf("%s\n",bestGame.getCompany().c_str()); 
    printf("%s\n", bestGame.getDescription().c_str()); 
    printf("%d\n", bestGame.getRating()); 
    */
    return 0; 
}