#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "../entityManager.h"
#include "../graphics.h"
#include "transform.h"

class Appearance : public Component {
    char ch;
public:
    Appearance(char ch) : ch{ch} {}
    char getAppearance() const { return ch; }
    void setAppearance(char newChar) { ch = newChar; }

    void init() override {}
    void update() override {

    }
    void render(Graphics * gfx) override {
        Transform * transform = owner->getComponent<Transform>();
        gfx->draw(ch, transform->position.y, transform->position.x);
    }
};

#endif
