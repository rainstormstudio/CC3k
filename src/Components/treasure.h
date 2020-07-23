#ifndef TREASURE_H
#define TREASURE_H

#include "../entityManager.h"
#include "wallet.h"
#include "actions.h"
#include "transform.h"

class Treasure : public Component {
    std::string name;
    int value;
    bool pickable;
public:
    Treasure(std::string name, int value, bool pickable) : name{name}, value{value}, pickable{pickable} {}

    int getValue() const { return value; }
    bool isPickable() const { return pickable; }
    void setPickable(bool value) { pickable = value; }

    void init() override {}

    void update(InputManager * events) override {
        if (pickable) {
            Entity * player = owner->manager.getEntityByName("Player");
            Transform * playerTransform = player->getComponent<Transform>();
            Wallet * playerWallet = player->getComponent<Wallet>();
            Actions * playerActions = player->getComponent<Actions>();
            Transform * transform = owner->getComponent<Transform>();
            if (playerTransform->position == transform->position) {
                playerWallet->incGold(value);
                playerActions->setAction("PC got " + std::to_string(value) + " gold.");
                owner->destroy();
            }
        }
    }

    void render(Graphics * gfx) override {}

    ~Treasure() override {}
};

#endif
