#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "../entityManager.h"
#include "transform.h"
#include "graphics.h"

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
        gfx->draw(ch, transform->position.x, transform->position.y);
    }
};

#endif
