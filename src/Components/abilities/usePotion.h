#ifndef USEPOTION_H
#define USEPOTION_H

#include "../../entityManager.h"
#include "../transform.h"
#include "../attributes.h"
#include "../potion.h"
#include "../actions.h"
#include "../../math.h"

class UsePotion : public Component {
    bool successfulUse;
public:
    UsePotion() {}

    void init() override {}

    bool used() const { return successfulUse; }

    void update(InputManager * events) override {
        successfulUse = false;
        if (!owner->isAlive()) {
            return;
        }
        Transform * transform = owner->getComponent<Transform>();
        Attributes * attributes = owner->getComponent<Attributes>();
        Actions * actions = owner->getComponent<Actions>();
        if (events->getInputType() == USE_POTION) {
            events->update();
            int useX = transform->position.x + Math::deltaX[events->getInputType()];
            int useY = transform->position.y + Math::deltaY[events->getInputType()];
            auto items = owner->manager.getEntitiesByLayer(ITEM_LAYER);
            for (auto& item : items) {
                if (item->name.substr(0, 6) == "Potion") {
                    Transform * itemTransform = item->getComponent<Transform>();
                    Potion * itemPotion = item->getComponent<Potion>();
                    if (itemTransform->position.x == useX
                        && itemTransform->position.y == useY) {
                        if (itemPotion->getEffect() == "hp") {
                            attributes->incHP(itemPotion->getEffectValue());
                        } else if (itemPotion->getEffect() == "atk") {
                            attributes->incAtkBoost(itemPotion->getEffectValue());
                        } else if (itemPotion->getEffect() == "def") {
                            attributes->incDefBoost(itemPotion->getEffectValue());
                        }
                        actions->setAction("PC used " + itemPotion->getName() + " potion.");
                        item->destroy();
                        successfulUse = true;
                    }
                }
            }
            if (!successfulUse) {
                actions->setAction("There is no potion to be used at that direction.");
            }
        }
    }
};

#endif
