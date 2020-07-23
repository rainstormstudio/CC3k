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
    std::vector<TreasureType> treasureTypes;

public:
    Game();
    ~Game();

    bool loop() const;
    void init();

    void initFloor();
    void nextFloor();

    void importPlayerRace();
    void importEnemyRace();
    void importTreasureConfig();
    void generateTreasure();
    void generateEnemies();

    void processInput();
    void update();
    void render();
};

#endif
