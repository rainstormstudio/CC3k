#ifndef STEALHEALTH_H
#define STEALHEALTH_H

#include "../../entityManager.h"
#include "../attributes.h"
#include "attack.h"

class StealHealth : public Component {
    int stealFactor;
public:
    StealHealth(int value) : stealFactor(value) {}

    void init() override {}

    void update(InputManager * events) override {
        Attack* attack = owner->getComponent<Attack>();
        if (attack->attacked()) {
            Attributes * attributes = owner->getComponent<Attributes>();
            attributes->incHP(stealFactor);
        }
    }

    void render(Graphics * gfx) override {}

    ~StealHealth() override {}
};

#endif
