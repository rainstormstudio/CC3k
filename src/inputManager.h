#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include <string>
#include "types.h"

const int KEY_TOTAL = 256;

class InputManager {
    std::vector<bool> keyInput;
    std::string input;
    std::vector<std::string> commands;

public:
    InputManager();
    void readConfig();
    bool isPressed(char key) const;
    std::string getInput() const;
    std::string getCommand(CommandType command) const;
    CommandType getInputType();
    void clear();
    void update();
};

#endif