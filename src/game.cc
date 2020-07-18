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
    delete events;
    delete manager;
}

bool Game::loop() const {
    return isRunning;
}

void Game::init() {
    gfx = new Graphics(SCREEN_WIDTH, SCREEN_HEIGHT);
    events = new InputManager();
    manager = new EntityManager();
    Entity * map = manager->addEntity("Map", MAP_LAYER);
    map->addComponent<Floor>(SCREEN_WIDTH, SCREEN_HEIGHT - 5);
    map->getComponent<Floor>()->import("./maps/default.map");
    Entity * player = manager->addEntity("Player", PLAYER_LAYER);
    player->addComponent<Transform>(20, 5);
    player->addComponent<Appearance>('@');
    player->addComponent<Attributes>("Human", 20, 20, 15, 18);
    player->addComponent<Actions>();
    player->addComponent<Movement>(map->getComponent<Floor>());
    isRunning = true;
}

void Game::processInput() {
    events->update();
    while (events->getInputType() == TOTAL_COMMANDS) {
        std::cout << "Please enter a valid command." << std::endl;
        std::cout << "-- movement commands --------------------------------------------" << std::endl;
        std::cout << "  go North: " << events->getCommand(NORTH) << std::endl;
        std::cout << "  go South: " << events->getCommand(SOUTH) << std::endl;
        std::cout << "  go East:  " << events->getCommand(EAST) << std::endl;
        std::cout << "  go West:  " << events->getCommand(WEST) << std::endl;
        std::cout << "  go North-east: " << events->getCommand(NORTHEAST) << std::endl;
        std::cout << "  go North-west: " << events->getCommand(NORTHWEST) << std::endl;
        std::cout << "  go South-east: " << events->getCommand(SOUTHEAST) << std::endl;
        std::cout << "  go South-west: " << events->getCommand(SOUTHWEST) << std::endl;
        std::cout << "-- action commands ----------------------------------------------" << std::endl;
        std::cout << "  use potion:          " << events->getCommand(USE_POTION) << std::endl;
        std::cout << "  attack:              " << events->getCommand(ATTACK) << std::endl;
        std::cout << "  toggle stop enemies: " << events->getCommand(STOP_ENEMIES) << std::endl;
        std::cout << "  restart the game:    " << events->getCommand(RESTART_GAME) << std::endl;
        std::cout << "  quit the game:       " << events->getCommand(QUIT_GAME) << std::endl;
        std::cout << "-----------------------------------------------------------------" << std::endl;
        events->update();
    }
    if (events->getInputType() == QUIT_GAME) {
        isRunning = false;
    }
}

void Game::update() {
    manager->update(events);
}

void Game::render() {
    gfx->clear();
    manager->render(gfx);
    gfx->render();
}
