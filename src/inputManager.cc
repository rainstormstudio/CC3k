#include "inputManager.h"
#include <iostream>
#include <fstream>

InputManager::InputManager() {
    keyInput = std::vector<bool>(KEY_TOTAL);
    commands = std::vector<std::string>(TOTAL_COMMANDS);
    clear();
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
    return keyInput[key];
}

std::string InputManager::getInput() const { 
    return input;
}

std::string InputManager::getCommand(CommandType command) const {
    return commands[command];
}

CommandType InputManager::getInputType() {
    for (int i = 0; i < TOTAL_COMMANDS; ++i) {
        if (input == commands[i]) {
            return static_cast<CommandType>(i);
        }
    }
    return TOTAL_COMMANDS;
}

void InputManager::clear() {
    for (int i = 0; i < KEY_TOTAL; ++i) {
        keyInput[i] = false;
    }
    input = "";
}

void InputManager::update() {
    std::getline(std::cin, input);
}
