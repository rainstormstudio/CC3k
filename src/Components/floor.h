#ifndef FLOOR_H
#define FLOOR_H

#include "../entityManager.h"
#include <vector>
#include <fstream>
#include <string>

class Floor : public Component {
    int map_width;
    int map_height;
    int num;
    std::vector<std::vector<char>> map;

public:
    Floor(int width, int height) : map_width{width}, map_height{height} {
        num = 1;
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

    void reset() {
        num = 1;
        for (int i = 0; i < map_height; ++i) {
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

    void incNum() {
        ++num;
    }

    void import(std::string filename) {
        std::string line;
        std::ifstream infile {filename};
        if (infile.is_open()) {
            int row = 0;
            while (std::getline(infile, line)) {
                int len = line.length();
                for (int i = 0; i < len && i < map_width; ++i) {
                    map[row][i] = line[i];
                }
                ++row;
            }
            infile.close();
        }
    }

    bool isWall(int x, int y) {
        if (map[y][x] == '|' || map[y][x] == '-' || map[y][x] == ' ') {
            return true;
        } else {
            return false;
        }
    }

    void init() override {}
    void update(InputManager * events) override {}

    void render(Graphics * gfx) override {
        for (int i = 0; i < map_height; ++i) {
            for (int j = 0; j < map_width; ++j) {
                gfx->draw(map[i][j], i, j);
            }
        }
        gfx->write("Floor: " + std::to_string(num),
                    gfx->screen_width - 10,
                    gfx->screen_height - 5);
    }

    ~Floor() override {
        
    }
};

#endif
