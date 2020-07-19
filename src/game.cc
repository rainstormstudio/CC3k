#include "game.h"
#include "config.h"
#include "entityManager.h"
#include "graphics.h"
#include "componentList.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>

Game::Game() {
    state = NO_GAME;
    gfx = nullptr;
    srand(time(NULL));
}

Game::~Game() {
    delete gfx;
    delete events;
    delete manager;
}

bool Game::loop() const {
    return state == IN_GAME;
}

void Game::init() {
    gfx = new Graphics(SCREEN_WIDTH, SCREEN_HEIGHT);
    gfx->drawImage("./assets/welcome.txt");
    events = new InputManager();
    manager = new EntityManager();
    importPlayerRace();
    gfx->write("Please choose your race", 0, gfx->screen_height - 5);
    for (unsigned int i = 0; i < playerRace.size(); ++i) {
        gfx->write(playerRace[i].name + "(" + playerRace[i].symbol + ")", i * 15, gfx->screen_height - 4);
    }
    gfx->render();
    bool successfulInput = false;
    std::string raceName;
    int playerHP;
    int playerMaxHP;
    int playerAtk;
    int playerDef;
    while (!successfulInput) {
        events->update();
        for (auto& race : playerRace) {
            if (race.symbol == events->getInput()) {
                raceName = race.name;
                playerHP = race.hp;
                playerMaxHP = race.maxHp;
                playerAtk = race.atk;
                playerDef = race.def;
                successfulInput = true;
            }
        }
        if (!successfulInput) {
            std::cout << "undefined symbol, please try again:" << std::endl;
        }
    }
    Entity * map = manager->addEntity("Map", MAP_LAYER); {
        map->addComponent<Floor>(SCREEN_WIDTH, SCREEN_HEIGHT - 5);
        map->getComponent<Floor>()->import("./maps/default.map");
    }
    Entity * player = manager->addEntity("Player", PLAYER_LAYER); {
        player->addComponent<Transform>(20, 5);
        player->addComponent<Appearance>('@');
        player->addComponent<Attributes>(raceName, playerHP, playerMaxHP, playerAtk, playerDef);
        player->addComponent<Actions>();
        player->addComponent<Movement>(true);
        player->addComponent<Attack>(true);
    }
    Entity * enemy = manager->addEntity("Enemy", ENEMY_LAYER); {
        enemy->addComponent<Transform>(16, 4);
        enemy->addComponent<Appearance>('H');
        enemy->addComponent<Attributes>("Human", 100, 100, 30, 20);
        enemy->addComponent<Movement>(false);
        enemy->addComponent<Attack>(false);
    }
    state = IN_GAME;
}

void Game::importPlayerRace() {
    std::string line;
    std::ifstream infile {"./configs/playerRace.conf"};
    if (infile.is_open()) {
        while (getline(infile, line)) {
            std::string raceName = "";
            std::string symbol;
            unsigned int hp;
            unsigned int maxHp;
            unsigned int atk;
            unsigned int def;
            raceName = line;
            getline(infile, line);
            symbol = line;
            getline(infile, line);
            hp = std::stoi(line);
            getline(infile, line);
            maxHp = std::stoi(line);
            getline(infile, line);
            atk = std::stoi(line);
            getline(infile, line);
            def = std::stoi(line);
            PlayerRace race = {raceName, symbol, hp, maxHp, atk, def};
            while (getline(infile, line) && line != "!") {
                race.skills.emplace_back(line);
            }
            playerRace.push_back(race);
        }
        infile.close();
    }
}

void Game::processInput() {
    switch (state) {
        case NO_GAME: {
            break;
        }
        case IN_GAME: {
            events->update();
            while (events->getInputType() == TOTAL_COMMANDS) {
                std::cout << "Please enter a valid command." << std::endl;
                std::cout << "-- movement commands --------------------------------------------" << std::endl;
                std::cout << "  go North: "             << events->getCommand(NORTH) << std::endl;
                std::cout << "  go South: "             << events->getCommand(SOUTH) << std::endl;
                std::cout << "  go East:  "             << events->getCommand(EAST) << std::endl;
                std::cout << "  go West:  "             << events->getCommand(WEST) << std::endl;
                std::cout << "  go North-east: "        << events->getCommand(NORTHEAST) << std::endl;
                std::cout << "  go North-west: "        << events->getCommand(NORTHWEST) << std::endl;
                std::cout << "  go South-east: "        << events->getCommand(SOUTHEAST) << std::endl;
                std::cout << "  go South-west: "        << events->getCommand(SOUTHWEST) << std::endl;
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
                state = NO_GAME;
            }
            break;
        }
        case WON_GAME: {
            break;
        }
        case LOST_GAME: {
            break;
        }
    }
    
}

void Game::update() {
    switch (state) {
        case NO_GAME: {
            break;
        }
        case IN_GAME: {
            manager->update(events);
            auto players = manager->getEntitiesByLayer(PLAYER_LAYER);
            if (players.empty()) {
                state = LOST_GAME;
            }
            break;
        }
        case WON_GAME: {
            break;
        }
        case LOST_GAME: {
            break;
        }
    }
}

void Game::render() {
    switch (state) {
        case NO_GAME: {
            break;
        }
        case IN_GAME: {
            gfx->clear();
            manager->render(gfx);
            gfx->render();
            break;
        }
        case WON_GAME: {
            break;
        }
        case LOST_GAME: {
            gfx->clear();
            gfx->drawImage("./assets/lost.txt");
            gfx->render();
            break;
        }
    }
}
