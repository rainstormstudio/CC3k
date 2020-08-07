#include "inputManager.h"
#include <iostream>
#include <fstream>

InputManager::InputManager() {
    commands = std::vector<std::string>(TOTAL_COMMANDS);
    readConfig();
}

void InputManager::readConfig() {
    std::string line;
    std::ifstream infile {"./configs/command.conf"};
    if (infile.is_open()) {
        int count = 0;
        while (std::getline(infile, line) && count < TOTAL_COMMANDS) {
            commands[count] = line;
            ++count;
        }
        infile.close();
    }
}

bool InputManager::isPressed(char key) const {
    return SDL_GetKeyName(event.key.keysym.sym)[0] == key;
}

std::string InputManager::getInput() const { 
    return SDL_GetKeyName(event.key.keysym.sym);
}

std::string InputManager::getCommand(CommandType command) const {
    return commands[command];
}

CommandType InputManager::getInputType() {
    if (event.type == SDL_QUIT) {
        return QUIT_GAME;
    }
    for (int i = 0; i < TOTAL_COMMANDS; ++i) {
        if (SDL_GetKeyName(event.key.keysym.sym) == commands[i]) {
            return static_cast<CommandType>(i);
        }
    }
    return TOTAL_COMMANDS;
}

void InputManager::update() {
    while (!(SDL_PollEvent(&event) != 0 && (event.type == SDL_QUIT || event.type == SDL_KEYDOWN)));
}
