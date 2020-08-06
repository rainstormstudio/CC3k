#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "../entityManager.h"
#include "transform.h"

class Appearance : public Component {
    char ch;
    Uint8 r, g, b, a;
    Uint8 br, bg, bb, ba;
public:
    Appearance() : ch{0} {}
    Appearance(char ch) : ch{ch} {
        r = 255;
        g = 255;
        b = 255;
        a = 255;
        br = 0;
        bg = 0;
        bb = 0;
        ba = 255;
    }
    Appearance(char ch, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 br, Uint8 bg, Uint8 bb, Uint8 ba) 
        : ch{ch}, r{r}, g{g}, b{b}, a{a}, br{br}, bg{bg}, bb{bb}, ba{ba} {}
    char getAppearance() const { return ch; }
    void setAppearance(char newChar) { ch = newChar; }

    void init() override {}
    void update(InputManager * events) override {}
    
    void render(Graphics * gfx) override {
        Transform * transform = owner->getComponent<Transform>();
        gfx->setCh(ch, transform->position.x, transform->position.y);
        gfx->setBackColor(br, bg, bb, ba, transform->position.x, transform->position.y);
        gfx->setForeColor(r, g, b, a, transform->position.x, transform->position.y);
    }

    ~Appearance() override {}
};

#endif
