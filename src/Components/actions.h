#ifndef ACTIONS_H
#define ACTIONS_H

#include "../entityManager.h"
#include <string>

class Actions : public Component {
    std::string action;

public:
    void init() override {
        action = "Player character has spawned.";
    }

    void update(InputManager * events) override {}

    void resetAction() {
        action = "";
    }

    void setAction(std::string done) {
        action += done + " ";
    }

    void render(Graphics * gfx) override {
        gfx->writeln("Action: " + action, 0, gfx->getScreenRows() - 2, gfx->getScreenCols(), 79, 132, 255, 255);
        action = "";
    }

    ~Actions() override {}
};

#endif
