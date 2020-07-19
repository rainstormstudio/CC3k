#ifndef SELFHEALING_H
#define SELFHEALING_H

#include "../../entityManager.h"
#include "../attributes.h"

class SelfHealing : public Component {
    int healingFactor;
public:
    SelfHealing(int value) : healingFactor(value) {}
    void init() override {}
    void update(InputManager * events) override {
        Attributes * attributes = owner->getComponent<Attributes>();
        attributes->incHP(healingFactor);
    }
    void render(Graphics * gfx) override {}
    ~SelfHealing() override {}
};

#endif
