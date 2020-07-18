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

std::string InputManager::getExtraInput() const {
    return extraInput;
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

CommandType InputManager::getExtraInputType() {
    for (int i = 0; i < TOTAL_COMMANDS; ++i) {
        if (extraInput == commands[i]) {
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
    extraInput = "";
}

void InputManager::update() {
    std::string line;
    std::getline(std::cin, line);

    input = line.substr(0, line.find(' '));
    extraInput = line.substr(line.find(' ')+1, line.length() - line.find(' '));
}
