#ifndef TREASURE_H
#define TREASURE_H

#include "../entityManager.h"
#include "wallet.h"

class Treasure : public Component {
    std::string name;
    int value;
    bool pickable;
public:
    Treasure(std::string name, int value, bool pickable) : name{name}, value{value}, pickable{pickable} {}

    int getValue() const { return value; }
    bool isPickable() const { return pickable; }

    void init() override {}

    void update(InputManager * events) override {

    }

    void render(Graphics * gfx) override {}

    ~Treasure() override {}
};

#endif
