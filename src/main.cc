#include "game.h"

int main(int argc, char *argv[]) {
    Game * game = new Game();
    game->init();

    game->render();
    game->processInput();
    while (game->loop()) {
        game->update();
        game->render();
        game->processInput();
    }

    delete game;

    return 0;
}