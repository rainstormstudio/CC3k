#ifndef POTION_H
#define POTION_H

#include "../entityManager.h"
#include "transform.h"
#include <string>

class Potion : public Component {
    std::string name;
    std::string effect;
    int effectValue;
public:
    Potion(std::string name, std::string effect, int effectValue) 
        : name{name}, effect{effect}, effectValue{effectValue} {}

    std::string getName() const { return name; }
    std::string getEffect() const { return effect; }
    int getEffectValue() const { return effectValue; }

    void init() override {}

    void update(InputManager * events) override {}

    void render(Graphics * gfx) override {}

    ~Potion() override {}
};

#endif
