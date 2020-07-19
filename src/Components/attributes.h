#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "../entityManager.h"

class Attributes : public Component {
    std::string race;
    int hp;
    int maxHp;
    int atk;
    int def;
public:
    Attributes() : race{"Shade"}, hp{125}, maxHp{125}, atk{25}, def{25} {}
    Attributes(std::string race, int hp, int maxHp, 
                int atk, int def)
        : race{race}, hp{hp}, maxHp{maxHp}, 
            atk{atk}, def{def} {
    }

    std::string getRace() const { return race; }
    int getHP() const { return hp; }
    int getMaxHP() const { return maxHp; }
    int getAtk() const { return atk; }
    int getDef() const { return def; }

    void setHP(int value) { hp = value; }
    void setMaxHP(int value) { maxHp = value; }
    void setAtk(int value) { atk = value; }
    void setDef(int value) { def = value; }

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
        if (owner->name == "Player") {
            gfx->write("Race: " + race, 0, gfx->screen_height - 5);
            gfx->write("HP: " + std::to_string(hp), 0, gfx->screen_height - 4);
            gfx->write("Atk: " + std::to_string(atk), 0, gfx->screen_height - 3);
            gfx->write("Def: " + std::to_string(def), 0, gfx->screen_height - 2);
        }
    }

    ~Attributes() override {}
};

#endif
