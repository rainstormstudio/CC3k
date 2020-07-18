#include "game.h"

int main(int argc, char *argv[]) {
    Game * game = new Game();
    game->init();

    while (game->loop()) {
        game->update();
        game->render();
        game->processInput();
    }

    return 0;
}