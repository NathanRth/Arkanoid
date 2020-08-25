#include <SDL.h>

#include "game.h"

using namespace std;

int main()
{
    Game game("./levels/", "./sprites.bmp", "./ascii.bmp");
    Code quit = MENU;
    while (quit != EXIT && game.menu())
        quit = game.gameLoop();

    SDL_Quit();

    return 0;
}
