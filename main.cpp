#include "game.h"

int main(int argc, char *args[])
{
    class Game game;

    game.init();

    while (!game.ifShouldExit())
    {
        game.process();
    }

    game.quit();
}
