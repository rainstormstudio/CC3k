#include "game.h"
#include "config.h"
#include "entityManager.h"
#include "graphics.h"
#include "componentList.h"

Game::Game() {
    isRunning = false;
    gfx = nullptr;
}

Game::~Game() {
    delete gfx;
    delete manager;
}

bool Game::loop() const {
    return isRunning;
}

void Game::init() {
    gfx = new Graphics(SCREEN_WIDTH, SCREEN_HEIGHT);
    manager = new EntityManager();
    Entity * player = manager->addEntity("Player", PLAYER_LAYER);
    player->addComponent<Transform>(20, 5);
    player->addComponent<Appearance>('@');
    player->addComponent<Attributes>("Human", 20, 15, 18);
    Entity * map = manager->addEntity("Map", MAP_LAYER);
    map->addComponent<Floor>(SCREEN_WIDTH, SCREEN_HEIGHT - 5);
    map->getComponent<Floor>()->import("./maps/default.map");
    isRunning = true;
}

void Game::processInput() {
    char ch;
    std::cin >> ch;
}

void Game::update() {
    manager->update();
}

void Game::render() {
    manager->render(gfx);
    gfx->render();
}
