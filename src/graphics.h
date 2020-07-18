#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <vector>
#include <string>

class Graphics {
    int screen_width;
    int screen_height;
    std::vector<std::vector<char>> theDisplay;

public:
    Graphics(int width, int height);

    void clear();
    void render();

    void draw(char value, int x, int y);
    void write(std::string content, int x, int y);
};

#endif
