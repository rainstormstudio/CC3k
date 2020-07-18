#include "game.h"
#include "config.h"
#include "entityManager.h"
#include "graphics.h"

Game::Game() {
    isRunning = false;
    gfx = nullptr;
}

Game::~Game() {
    delete gfx;
}

bool Game::loop() const {
    return isRunning;
}

void Game::init() {
    gfx = new Graphics(SCREEN_WIDTH, SCREEN_HEIGHT);
    manager = new EntityManager();
    isRunning = true;
}

void Game::processInput() {
    
}

void Game::update() {

}

void Game::render() {

}
