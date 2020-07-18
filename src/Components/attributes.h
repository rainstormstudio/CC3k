#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "../entityManager.h"

class Attributes : public Component {
    std::string race;
    unsigned int hp;
    unsigned int atk;
    unsigned int def;
public:
    Attributes(std::string race, unsigned int hp, unsigned int atk, unsigned int def)
        : race{race}, hp{hp}, atk{atk}, def{def} {
    }

    unsigned int getHP() const { return hp; }
    unsigned int getAtk() const { return atk; }
    unsigned int getDef() const { return def; }

    void incHP(unsigned int value) { hp += value; }
    void decHP(unsigned int value) { hp -= value; }

    void incAtk(unsigned int value) { atk += value; }
    void decAtk(unsigned int value) { atk -= value; }

    void incDef(unsigned int value) { def += value; }
    void decDef(unsigned int value) { def -= value; }

    void init() override {}
    void update() override {}

    void render(Graphics * gfx) override {
        gfx->write("Race: " + race, 0, gfx->screen_height - 5);
        gfx->write("HP: " + std::to_string(hp), 0, gfx->screen_height - 4);
        gfx->write("Atk: " + std::to_string(atk), 0, gfx->screen_height - 3);
        gfx->write("Def: " + std::to_string(def), 0, gfx->screen_height - 2);
    }
};

#endif
