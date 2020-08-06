#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "../entityManager.h"

class Attributes : public Component {
    std::string race;
    int hp;
    int maxHp;
    int atk;
    int atkBoost;
    int def;
    int defBoost;
public:
    Attributes() 
        : race{"Shade"}, hp{125}, maxHp{125}, atk{25}, atkBoost{0}, def{25}, defBoost{0} {}
    Attributes(std::string race, int hp, int maxHp, 
                int atk, int def)
        : race{race}, hp{hp}, maxHp{maxHp}, 
            atk{atk}, atkBoost{0}, def{def}, defBoost{0} {
    }

    std::string getRace() const { return race; }
    int getHP() const { return hp; }
    int getMaxHP() const { return maxHp; }
    int getAtk() const { return atk + atkBoost; }
    int getDef() const { return def + defBoost; }

    void clearBoost() {
        atkBoost = 0;
        defBoost = 0;
    }

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

    void incAtkBoost(int value) { atkBoost += value; }
    void incDefBoost(int value) { defBoost += value; }

    void init() override {}
    void update(InputManager * events) override {}

    void render(Graphics * gfx) override {
        if (owner->name == "Player") {
            gfx->write("Race: " + race, 0, gfx->getScreenRows() - 6);
            gfx->write("HP: " + std::to_string(hp), 0, gfx->getScreenRows() - 5, 36, 255, 33, 255);
            gfx->write("Atk: " + std::to_string(atk), 0, gfx->getScreenRows() - 4, 255, 97, 79, 255);
            gfx->write("Def: " + std::to_string(def), 0, gfx->getScreenRows() - 3, 255, 130, 30, 255);
        }
    }

    ~Attributes() override {}
};

#endif
