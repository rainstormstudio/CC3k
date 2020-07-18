#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "../entityManager.h"

class Attributes : public Component {
    std::string race;
    unsigned int hp;
    unsigned int maxHp;
    unsigned int atk;
    unsigned int def;
public:
    Attributes() : race{"Shade"}, hp{125}, maxHp{125}, atk{25}, def{25} {}
    Attributes(std::string race, unsigned int hp, unsigned int maxHp, 
                unsigned int atk, unsigned int def)
        : race{race}, hp{hp}, maxHp{maxHp}, 
            atk{atk}, def{def} {
    }

    unsigned int getHP() const { return hp; }
    unsigned int getMaxHP() const { return maxHp; }
    unsigned int getAtk() const { return atk; }
    unsigned int getDef() const { return def; }

    void incHP(int value) { 
        hp += value; 
        if (hp > maxHp) hp = maxHp;
    }

    void incMaxHP( int value) { maxHp += value; }

    void incAtk( int value) { atk += value; }

    void incDef( int value) { def += value; }

    void init() override {}
    void update(InputManager * events) override {}

    void render(Graphics * gfx) override {
        gfx->write("Race: " + race, 0, gfx->screen_height - 5);
        gfx->write("HP: " + std::to_string(hp), 0, gfx->screen_height - 4);
        gfx->write("Atk: " + std::to_string(atk), 0, gfx->screen_height - 3);
        gfx->write("Def: " + std::to_string(def), 0, gfx->screen_height - 2);
    }

    ~Attributes() override {}
};

#endif
