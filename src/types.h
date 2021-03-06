#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <string>

struct Vec2 {
    int x = 0;
    int y = 0;

    Vec2(int x, int y) : x(x), y(y) {}

    Vec2 operator+(const Vec2 &v) {
        return Vec2(x + v.x, y + v.y);
    }

    Vec2 operator-(const Vec2 &v) {
        return Vec2(x - v.x, y - v.y);
    }

    Vec2 operator+=(const Vec2 &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vec2 operator-=(const Vec2 &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    bool operator==(const Vec2 &v) {
        return x == v.x && y == v.y;
    }

    bool operator!=(const Vec2 &v) {
        return !(x == v.x && y == v.y);
    }
};

struct Race {
    std::string name;
    std::string symbol;
    unsigned int hp;
    unsigned int maxHp;
    unsigned int atk;
    unsigned int def;
    std::vector<std::string> skills;
};

struct PlayerRace : public Race {
    PlayerRace(std::string name, std::string symbol, unsigned int hp, unsigned int maxHp, unsigned int atk, unsigned int def) 
        : Race{name, symbol, hp, maxHp, atk, def} {}
};

struct EnemyRace : public Race {
    unsigned int spawnWeight;
    EnemyRace(std::string name, std::string symbol, unsigned int spawnWeight, unsigned int hp, unsigned int maxHp, unsigned int atk, unsigned int def) 
        : Race{name, symbol, hp, maxHp, atk, def}, spawnWeight{spawnWeight} {}
};

struct TreasureType {
    std::string name;
    unsigned int spawnWeight;
    unsigned int value;
    bool pickable;
    std::vector<std::string> skills;
};

struct PotionType {
    std::string name;
    int spawnWeight;
    std::string effect;
    int effectValue;
};

enum LayerType {
    MAP_LAYER,
    ITEM_LAYER,
    ENEMY_LAYER,
    PLAYER_LAYER,
    UI_LAYER,
    TOTAL_LAYERS
};

enum CommandType {
    NORTH,
    SOUTH,
    EAST,
    WEST,
    NORTHEAST,
    NORTHWEST,
    SOUTHEAST,
    SOUTHWEST,
    USE_POTION,
    ATTACK,
    STOP_ENEMIES,
    RESTART_GAME,
    QUIT_GAME,
    TOTAL_COMMANDS
};

enum GameState {
    NO_GAME,
    IN_GAME,
    WON_GAME,
    LOST_GAME
};

#endif
