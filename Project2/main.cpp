#include "game.h"

int main()
{  
    sf::Texture spritesheet;
    srand(time(nullptr));
    if (!spritesheet.loadFromFile(SPRITESHEET_FILE))
    {
        std::cerr << "no se pudo cargar el archivo de sprites\n";
        exit(-1);
    }
    Game game(spritesheet);
    game.run();
    return 0;
}
