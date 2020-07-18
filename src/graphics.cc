#include "graphics.h"

Graphics::Graphics(int width, int height)
    : screen_width{width}, screen_height{height} {
    theDisplay = std::vector<std::vector<char>>(screen_height);
    for (int i = 0; i < screen_height; ++i) {
        theDisplay[i] = std::vector<char>(screen_width);
        for (int j = 0; j < screen_width; ++j) {
            theDisplay[i][j] = ' ';
        }
    }
}

void Graphics::clear() {
    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            theDisplay[i][j] = ' ';
        }
    }
}

void Graphics::render() {
    for (int i = 0; i < screen_height; ++i) {
        for (int j = 0; j < screen_width; ++j) {
            std::cout << theDisplay[i][j];
        }
        std::cout << std::endl;
    }
}

void Graphics::draw(char value, int x, int y) {
    theDisplay[x][y] = value;
}

void Graphics::write(std::string content, int x, int y) {
    int len = content.length();
    for (int i = 0; i < len && x + i < screen_width; ++i) {
        theDisplay[y][x + i] = content[i];
    }
}
