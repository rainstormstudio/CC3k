#ifndef FLOOR_H
#define FLOOR_H

#include "../entityManager.h"
#include <vector>
#include <string>

class Floor : public Component {
    int map_width;
    int map_height;
    std::vector<std::vector<char>> map;

public:
    Floor(int width, int height) : map_width{width}, map_height{height} {
        map = std::vector<std::vector<char>>(map_height);
        for (int i = 0; i < map_height; ++i) {
            map[i] = std::vector<char>(map_width);
            for (int j = 0; j < map_width; ++j) {
                map[i][j] = ' ';
            }
        }
        for (int j = 0; j < map_width; ++j) {
            map[0][j] = '-';
        }
        for (int j = 0; j < map_width; ++j) {
            map[map_height-1][j] = '-';
        }
        for (int i = 0; i < map_height; ++i) {
            map[i][0] = '|';
        }
        for (int i = 0; i < map_height; ++i) {
            map[i][map_width-1] = '|';
        }
    }

    void import(std::string filename) {

    }

    void init() override {}
    void update() override {}

    void render(Graphics * gfx) override {
        for (int i = 0; i < map_height; ++i) {
            for (int j = 0; j < map_width; ++j) {
                gfx->draw(map[i][j], i, j);
            }
        }
    }
};

#endif
