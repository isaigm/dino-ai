#include "../include/game.h"
#include <iostream>

int main()
{  
    srand(time(nullptr));   
    Game game;
    game.run();
    return 0;
}
