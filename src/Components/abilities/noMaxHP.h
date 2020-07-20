#ifndef NOMAXHP_H
#define NOMAXHP_H

#include "../../entityManager.h"
#include "../attributes.h"

class NoMaxHP : public Component {
public:
    void init() override {}
    void update(InputManager * events) override {
        Attributes * attributes = owner->getComponent<Attributes>();
        if (attributes->getHP() < 100) {
            attributes->setMaxHP(200);
        } else {
            attributes->setMaxHP(attributes->getHP() * 2);
            if (attributes->getHP() > 999) {
                attributes->setMaxHP(999);
            }
        }
    }
    void render(Graphics * gfx) override {}
    ~NoMaxHP() override {}
};

#endif
