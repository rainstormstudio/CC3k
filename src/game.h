#ifndef GAME_H
#define GAME_H

#include "types.h"

class Graphics;
class InputManager;
class EntityManager;

class Game {
private:
    bool isRunning;
    Graphics * gfx;
    InputManager * events;
    EntityManager * manager;
    std::vector<PlayerRace> playerRace;

public:
    Game();
    ~Game();

    bool loop() const;
    void init();
    void importPlayerRace();
    void processInput();
    void update();
    void render();
};

#endif
