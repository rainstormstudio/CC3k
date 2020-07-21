#ifndef GAME_H
#define GAME_H

#include "types.h"

class Graphics;
class InputManager;
class EntityManager;

class Game {
private:
    GameState state;
    Graphics * gfx;
    InputManager * events;
    EntityManager * manager;
    std::vector<PlayerRace> playerRace;
    std::vector<EnemyRace> enemyRace;

public:
    Game();
    ~Game();

    bool loop() const;
    void init();
    void initFloor();
    void importPlayerRace();
    void importEnemyRace();
    void processInput();
    void update();
    void render();
};

#endif
