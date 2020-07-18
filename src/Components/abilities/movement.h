#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../../entityManager.h"
#include "../transform.h"
#include "../floor.h"
#include "../actions.h"
#include <string>

const int deltaX[8] = {0, 0, 1, -1, 1, -1, 1, -1};
const int deltaY[8] = {-1, 1, 0, 0, -1, -1, 1, 1};

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
public:
    Movement(Floor * floor) : floor{floor} {}

    void init() override {
        direction = "";
    }
    
    void update(InputManager * events) override {
        Transform * transform = owner->getComponent<Transform>();
        if (events->getInputType() >= NORTH && events->getInputType() <= SOUTHWEST) {         
            direction = directions[events->getInputType()];
            Actions * action = owner->getComponent<Actions>();
            if (floor->isWall(
                transform->position.x + deltaX[events->getInputType()],
                transform->position.y + deltaY[events->getInputType()])) {
                action->setAction("PC tried to go " + direction + " but stoped by a wall.");
            } else {
                transform->position.x += deltaX[events->getInputType()];
                transform->position.y += deltaY[events->getInputType()];
                action->setAction("PC went " + direction);
            }
        } else {
            direction = "";
        }
    }

    void render(Graphics* gfx) override {
    }
};

#endif
