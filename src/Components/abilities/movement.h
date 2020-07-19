#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../../entityManager.h"
#include "../transform.h"
#include "../floor.h"
#include "../actions.h"
#include <string>
#include "../../math.h"

const std::string directions[8] = {
    "North",
    "South",
    "East",
    "West",
    "North-East",
    "North-West",
    "South-East",
    "South-West",
};

class Movement : public Component {
    Floor * floor;
    std::string direction;
    bool hasControl;
public:
    Movement(Floor * floor, bool hasControl) 
        : floor{floor}, hasControl{hasControl} {}

    void init() override {
        direction = "";
    }
    
    void update(InputManager * events) override {
        Transform * transform = owner->getComponent<Transform>();
        if (hasControl) {
            if (events->getInputType() >= NORTH && events->getInputType() <= SOUTHWEST) {         
                direction = directions[events->getInputType()];
                Actions * action = owner->getComponent<Actions>();
                if (floor->isWall(
                    transform->position.x + Math::deltaX[events->getInputType()],
                    transform->position.y + Math::deltaY[events->getInputType()])) {
                    action->setAction("PC tried to go " + direction + " but stoped by a wall.");
                    direction = "";
                } else {
                    transform->position.x += Math::deltaX[events->getInputType()];
                    transform->position.y += Math::deltaY[events->getInputType()];
                    action->setAction("PC went " + direction + ".");
                }
            } else {
                direction = "";
            }
        } else {
            Entity* player = owner->manager.getEntityByName("Player");
            Transform * playerTransform = player->getComponent<Transform>();
            bool shouldMove = true;
            for (int i = 0; i < 8; i++) {
                if (playerTransform->position.x == transform->position.x + Math::deltaX[i]
                    && playerTransform->position.y == transform->position.y + Math::deltaY[i]) {
                    shouldMove = false;
                    break;
                }
            }
            if (shouldMove) {
                int dir = Math::random(0, 7);
                while (floor->isWall(
                    transform->position.x + Math::deltaX[dir],
                    transform->position.y + Math::deltaY[dir])) {
                    dir = Math::random(0, 7);
                }
                direction = directions[dir];
                transform->position.x += Math::deltaX[dir];
                transform->position.y += Math::deltaY[dir]; 
            }
        }
    }

    void render(Graphics* gfx) override {
    }

    ~Movement() override {}
};

#endif
