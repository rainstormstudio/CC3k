#ifndef ACTIONS_H
#define ACTIONS_H

#include "../entityManager.h"
#include <string>

class Actions : public Component {
    std::string action;

public:
    void init() override {
        action = "";
    }

    void update(InputManager * events) override {}

    void setAction(std::string done) {
        action = done;
    }

    void render(Graphics * gfx) override {
        gfx->write("Action: " + action, 0, gfx->screen_height - 1);
    }
};

#endif
