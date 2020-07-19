#ifndef ATTACK_H
#define ATTACK_H

#include "../../entityManager.h"
#include "../transform.h"
#include "../appearance.h"
#include "../attributes.h"
#include "../actions.h"
#include "../../math.h"
#include <cmath>

class Attack : public Component {
    bool hasControl;
    bool successfulAttack;
public:
    Attack(bool hasControl) : hasControl{hasControl}, successfulAttack{false} {}

    void init() override {}

    bool attacked() const {return successfulAttack;}

    void update(InputManager * events) override {
        successfulAttack = false;
        if (!owner->isAlive()) {
            return;
        }
        Transform * transform = owner->getComponent<Transform>();
        Attributes * attributes = owner->getComponent<Attributes>();
        Appearance * appearance = owner->getComponent<Appearance>();
        if (hasControl) {
            if (events->getInputType() == ATTACK) {
                int attackX = transform->position.x + Math::deltaX[events->getExtraInputType()];
                int attackY = transform->position.y + Math::deltaY[events->getExtraInputType()];
                auto entities = owner->manager.getEntitiesByLayer(ENEMY_LAYER);
                bool kill = false;
                int damage = 0;
                Actions * actions = owner->getComponent<Actions>();
                Appearance * entityAppearance = nullptr;
                Attributes * entityAttributes = nullptr;
                for (auto& entity : entities) {
                    Transform * entityTransform = entity->getComponent<Transform>();
                    entityAttributes = entity->getComponent<Attributes>();
                    entityAppearance = entity->getComponent<Appearance>();
                    damage = 0;
                    if (entityTransform->position.x == attackX
                        && entityTransform->position.y == attackY) {
                        damage = ceil(static_cast<float>((100.0/(100.0 + entityAttributes->getDef())) * attributes->getAtk()));
                        entityAttributes->incHP(-damage);
                        if (entityAttributes->getHP() <= 0) {
                            entity->destroy();
                            kill = true;
                        }
                        successfulAttack = true;
                        break;
                    }
                }
                if (successfulAttack) {
                    if (kill) {
                        actions->setAction("PC killed " + std::string(1, entityAppearance->getAppearance()) + ".");
                    } else {
                        actions->setAction("PC deals " + std::to_string(damage) + " damage to " 
                                            + std::string(1, entityAppearance->getAppearance()) 
                                            + " (" + std::to_string(entityAttributes->getHP()) + " HP).");
                    }
                } else {
                    actions->setAction("There is nothing to be attacked at that direction.");
                }
            }    
        } else {
            Entity* player = owner->manager.getEntityByName("Player");
            Transform * playerTransform = player->getComponent<Transform>();
            Attributes * playerAttributes = player->getComponent<Attributes>();
            Actions * playerActions = player->getComponent<Actions>();
            for (int i = 0; i < 8; ++i) {
                if (playerTransform->position.x == transform->position.x + Math::deltaX[i]
                    && playerTransform->position.y == transform->position.y + Math::deltaY[i]) {
                    successfulAttack = static_cast<bool>(Math::random(0, 1));
                    if (successfulAttack) {
                        int damage = ceil(static_cast<float>((100.0/(100.0 + playerAttributes->getDef())) * attributes->getAtk()));
                        playerAttributes->incHP(-damage);
                        bool kill = false;
                        if (playerAttributes->getHP() <= 0) {
                            player->destroy();
                            kill = true;
                        }
                        if (kill) {
                            playerActions->setAction(std::string(1, appearance->getAppearance()) + " killed PC.");
                        } else {
                            playerActions->setAction(
                                std::string(1, appearance->getAppearance()) + " deals "
                                + std::to_string(damage) + " damage to PC.");
                        }
                    } else {
                        playerActions->setAction(
                            std::string(1, appearance->getAppearance()) 
                            + " tried to attack PC but missed.");
                    }
                    break;
                }
            }
        }
    }

    void render(Graphics * gfx) override {}

    ~Attack() override {}
};

#endif
