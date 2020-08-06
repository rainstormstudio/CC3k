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
    gfx = new Graphics("cc3k", 0, "./assets/fonts/Monaco.ttf", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_ROWS, SCREEN_COLS);
    gfx->importTxt("./assets/welcome.txt", false);
    events = new InputManager();
    manager = new EntityManager();
    importPlayerRace();
    importEnemyRace();
    importTreasureConfig();
    importPotionConfig();
    
    initFloor();
    
    state = IN_GAME;
}

void Game::initFloor() {
    gfx->write("Please choose your race", 0, gfx->getScreenRows() - 5);
    int deltaHeight = 5;
    for (unsigned int i = 0; i < playerRace.size(); ++i) {
        if ((i * 15) % 75 == 0) {
            deltaHeight --;
        }
        gfx->write(playerRace[i].name + "(" + playerRace[i].symbol + ")", (i * 15) % 75, gfx->getScreenRows() - deltaHeight);
    }
    gfx->write("or type q to quit the game.", 0, gfx->getScreenRows() - 1);
    gfx->render();
    bool successfulInput = false;
    std::string raceName = "";
    int playerHP = 0;
    int playerMaxHP = 0;
    int playerAtk = 0;
    int playerDef = 0;
    std::vector<std::string> skills;
    while (!successfulInput) {
        events->update();
        for (auto& race : playerRace) {
            if (race.symbol == events->getInput()) {
                raceName = race.name;
                playerHP = race.hp;
                playerMaxHP = race.maxHp;
                playerAtk = race.atk;
                playerDef = race.def;
                skills = race.skills;
                successfulInput = true;
            }
        }
        if (events->getInputType() == QUIT_GAME) {
            state = NO_GAME;
            return;
        }
        if (!successfulInput) {
            std::cout << "undefined symbol, please try again:" << std::endl;
        }
    }
    Entity* map = manager->addEntity("Map", MAP_LAYER); {
        map->addComponent<Floor>(SCREEN_WIDTH, SCREEN_HEIGHT - 5);
        map->getComponent<Floor>()->import("./maps/default.map");
    }
    Entity* player = manager->addEntity("Player", PLAYER_LAYER); {
        player->addComponent<Transform>();
        player->addComponent<Appearance>('@', 0, 0, 0, 255, 79, 255, 240, 255);
        player->addComponent<Attributes>(raceName, playerHP, playerMaxHP, playerAtk, playerDef);
        player->addComponent<Wallet>();
        player->addComponent<Actions>();
        player->addComponent<Movement>(true);
        player->addComponent<Attack>(true);
        for (int i = 0; i < static_cast<int>(skills.size()); ++i) {
            if (skills[i].substr(0, 11) == "SelfHealing") {
                int value = std::stoi(skills[i].substr(12, skills[i].size() - 12));
                player->addComponent<SelfHealing>(value);
            } else if (skills[i] == "NoMaxHP") {
                player->addComponent<NoMaxHP>();
            } else if (skills[i].substr(0, 11) == "StealHealth") {
                int value = std::stoi(skills[i].substr(12, skills[i].size() - 12));
                player->addComponent<StealHealth>(value);
            }
        }
    }

    Entity* stairs = manager->addEntity("Stairs", ITEM_LAYER); {
        stairs->addComponent<Transform>();
        stairs->addComponent<Appearance>('\\');
    }

    generatePotions();
    generateTreasure();
    generateEnemies();
}

void Game::nextFloor() {
    manager->destroyByLayer(ITEM_LAYER);
    manager->destroyByLayer(ENEMY_LAYER);
    Entity* map = manager->getEntityByName("Map");
    Floor* floor = map->getComponent<Floor>();
    floor->incNum();
    if (floor->getNum() == 5) {
        state = WON_GAME;
        return;
    }
    Entity* player = manager->getEntityByName("Player");
    Transform* playerTransform = player->getComponent<Transform>();
    Actions* playerActions = player->getComponent<Actions>();
    playerActions->resetAction();
    playerActions->setAction("PC went to the next floor.");
    playerTransform->randomPosition();
    Entity* stairs = manager->addEntity("Stairs", ITEM_LAYER); {
        stairs->addComponent<Transform>();
        stairs->addComponent<Appearance>('\\');
    }
    generatePotions();
    generateTreasure();
    generateEnemies();
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
    } else {
        std::cout << "Error importing player race config file." << std::endl;
    }
}

void Game::importEnemyRace() {
    std::string line;
    std::ifstream infile {"./configs/enemyRace.conf"};
    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            std::string raceName = "";
            std::string symbol;
            unsigned int spawnWeight;
            unsigned int hp;
            unsigned int maxHp;
            unsigned int atk;
            unsigned int def;
            raceName = line;
            getline(infile, line);
            symbol = line;
            getline(infile, line);
            spawnWeight = std::stoi(line);
            getline(infile, line);
            hp = std::stoi(line);
            getline(infile, line);
            maxHp = std::stoi(line);
            getline(infile, line);
            atk = std::stoi(line);
            getline(infile, line);
            def = std::stoi(line);
            EnemyRace race = {raceName, symbol, spawnWeight, hp, maxHp, atk, def};
            while (getline(infile, line) && line != "!") {
                race.skills.emplace_back(line);
            }
            enemyRace.push_back(race);
        }
        infile.close();
    } else {
        std::cout << "Error importing enemy race config file." << std::endl;
    }
}

void Game::importTreasureConfig() {
    std::string line;
    std::ifstream infile {"./configs/treasure.conf"};
    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            std::string treasureName = "";
            unsigned int spawnWeight;
            unsigned int value;
            bool pickable;
            treasureName = line;
            getline(infile, line);
            spawnWeight = std::stoi(line);
            getline(infile, line);
            value = std::stoi(line);
            getline(infile, line);
            pickable = static_cast<bool>(std::stoi(line));
            TreasureType type = {treasureName, spawnWeight, value, pickable};
            while (getline(infile, line) && line != "!") {
                type.skills.emplace_back(line);
            }
            treasureTypes.push_back(type);
        }
        infile.close();
    } else {
        std::cout << "Error importing treasure config file." << std::endl;
    }
}

void Game::importPotionConfig() {
    std::string line;
    std::ifstream infile {"./configs/potion.conf"};
    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            std::string potionName = "";
            int spawnWeight = 0;
            std::string effect = "";
            int effectValue = 0;
            potionName = line;
            getline(infile, line);
            spawnWeight = std::stoi(line);
            getline(infile, line);
            effect = line.substr(0, line.find(' '));
            effectValue = std::stoi(line.substr(line.find(' ')+1, line.length() - line.find(' ')));
            PotionType type = {potionName, spawnWeight, effect, effectValue};
            potionTypes.push_back(type);
        }
        infile.close();
    } else {
        std::cout << "Error importing potion config file." << std::endl;
    }
}

void Game::generateTreasure() {
    int treausreWeightTotal = 0;
    for (unsigned int i = 0; i < treasureTypes.size(); ++i) {
        treausreWeightTotal += treasureTypes[i].spawnWeight;
    }
    for (int i = 0; i < 10; ++i) {
        int picked = Math::random(1, treausreWeightTotal);
        TreasureType * pickedTreasure = nullptr;
        for (unsigned int j = 0; j < treasureTypes.size(); ++j) {
            picked -= treasureTypes[j].spawnWeight;
            if (picked <= 0) {
                pickedTreasure = &treasureTypes[j];
                break;
            }
        }
        Entity* treasure = manager->addEntity("Treasure" + std::to_string(i), ITEM_LAYER); {
            treasure->addComponent<Transform>();
            treasure->addComponent<Appearance>('G', 236, 165, 49, 255, 254, 255, 123, 255);
            treasure->addComponent<Treasure>(pickedTreasure->name, pickedTreasure->value, pickedTreasure->pickable);
        }
    }
}

void Game::generatePotions() {
    int potionWeightTotal = 0;
    for (unsigned int i = 0; i < potionTypes.size(); ++i) {
        potionWeightTotal += potionTypes[i].spawnWeight;
    }
    for (int i = 0; i < 10; ++i) {
        int picked = Math::random(1, potionWeightTotal);
        PotionType * pickedPotion = nullptr;
        for (unsigned int j = 0; j < potionTypes.size(); ++j) {
            picked -= potionTypes[j].spawnWeight;
            if (picked <= 0) {
                pickedPotion = &potionTypes[j];
                break;
            }
        }
        Entity *potion = manager->addEntity("Potion" + std::to_string(i), ITEM_LAYER); {
            potion->addComponent<Transform>();
            potion->addComponent<Appearance>('P', 67, 88, 255, 255, 162, 255, 249, 255);
            potion->addComponent<Potion>(pickedPotion->name, pickedPotion->effect, pickedPotion->effectValue);
        }
    }
}

void Game::generateEnemies() {
    int enemyWeightTotal = 0;
    for (int i = 0; i < static_cast<int>(enemyRace.size()); ++i) {
        enemyWeightTotal += enemyRace[i].spawnWeight;
    }
    for (int i = 0; i < 20; ++i) {
        int picked = Math::random(1, enemyWeightTotal);
        EnemyRace * pickedEnemy = nullptr;
        for (int j = 0; j < static_cast<int>(enemyRace.size()); ++j) {
            picked -= enemyRace[j].spawnWeight;
            if (picked <= 0) {
                pickedEnemy = &enemyRace[j];
                break;
            }
        }
        Entity* enemy = manager->addEntity("Enemy" + std::to_string(i), ENEMY_LAYER); {
            enemy->addComponent<Transform>();
            enemy->addComponent<Appearance>(pickedEnemy->symbol[0], 255, 0, 0, 255, 255, 158, 146, 255);
            enemy->addComponent<Attributes>(pickedEnemy->name, 
                                            pickedEnemy->hp, 
                                            pickedEnemy->maxHp, 
                                            pickedEnemy->atk, 
                                            pickedEnemy->def);
            enemy->addComponent<Movement>(false);
            enemy->addComponent<Attack>(false);
            for (int j = 0; j < static_cast<int>(pickedEnemy->skills.size()); ++j) {
                // TODO: add enemy skills here
            }
        }
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
            } else if (events->getInputType() == RESTART_GAME) {
                manager->destroy();
                gfx->clear();
                gfx->importTxt("./assets/restart.txt", false);
                initFloor();
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
            auto stairs = manager->getEntityByName("Stairs");
            state = NO_GAME;
            for (auto player : players) {
                state = IN_GAME;
                Transform * playerTransform = player->getComponent<Transform>();
                Transform * stairsTransform = stairs->getComponent<Transform>();
                if (playerTransform->position == stairsTransform->position) {
                    nextFloor();
                }
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
            gfx->clear();
            gfx->importTxt("./assets/victory.txt", false);
            gfx->render();
            break;
        }
        case LOST_GAME: {
            gfx->clear();
            gfx->importTxt("./assets/lost.txt", false);
            gfx->render();
            break;
        }
    }
}
