#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include <string>
#include "types.h"
#ifdef __linux__
#include "SDL2/SDL.h"
#elif __WIN32
#include "SDL.h"
#endif

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
