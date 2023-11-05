#include <iostream>
#include "Games/Game.h"

int main(int argc, char* argv[]) 
{
    Game game;
    game.Initialize();
    game.Run();
    game.Destroy();
    return 0;
}