#ifndef GAME_H
#define GAME_H

class Graphics;
class EntityManager;

class Game {
private:
    bool isRunning;
    Graphics * gfx;
    EntityManager * manager;

public:
    Game();
    ~Game();

    bool loop() const;
    void init();
    void processInput();
    void update();
    void render();
};

#endif
