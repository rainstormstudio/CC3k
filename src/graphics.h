#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <vector>
#include <string>

class Graphics {
    std::vector<std::vector<char>> theDisplay;

public:
    int screen_width;
    int screen_height;

    Graphics(int width, int height);

    void clear();
    void render();

    void draw(char value, int x, int y);
    void drawImage(std::string filename);
    void write(std::string content, int x, int y);
};

#endif
