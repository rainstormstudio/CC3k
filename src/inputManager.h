#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include <string>
#include "types.h"
#include "SDL2/SDL.h"

const int KEY_TOTAL = 256;

class InputManager {
    SDL_Event event;
    std::vector<std::string> commands;

public:
    InputManager();
    void readConfig();
    bool isPressed(char key) const;
    std::string getInput() const;
    std::string getCommand(CommandType command) const;
    CommandType getInputType();
    void update();
};

#endif
