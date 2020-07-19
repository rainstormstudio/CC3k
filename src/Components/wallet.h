#ifndef WALLET_H
#define WALLET_H

#include "../entityManager.h"

class Wallet : public Component {
    int gold;
public:
    Wallet() : gold{0} {}

    int getGold() const { return gold; }
    void setGold(int value) { gold = value; }
    void incGold(int value) { gold += value; }

    void init() override {}

    void update(InputManager * events) override {}

    void render(Graphics * gfx) override {
        if (owner->name == "Player") {
            gfx->write("Gold: " + std::to_string(gold), 20, gfx->screen_height - 5);
        }
    }
};

#endif
