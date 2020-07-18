#ifndef TYPES_H
#define TYPES_H

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

enum LayerType {
    MAP_LAYER,
    ITEM_LAYER,
    ENEMY_LAYER,
    PLAYER_LAYER,
    UI_LAYER,
    TOTAL_LAYERS
};

#endif
