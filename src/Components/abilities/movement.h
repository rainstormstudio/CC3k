#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../../entityManager.h"
#include "../transform.h"
#include "../floor.h"
#include "../actions.h"
#include <string>
#include "../../math.h"

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
                    transform->position.x + deltaX[events->getInputType()],
                    transform->position.y + deltaY[events->getInputType()])) {
                    action->setAction("PC tried to go " + direction + " but stoped by a wall.");
                    direction = "";
                } else {
                    transform->position.x += deltaX[events->getInputType()];
                    transform->position.y += deltaY[events->getInputType()];
                    action->setAction("PC went " + direction);
                }
            } else {
                direction = "";
            }
        } else {
            int dir = Math::random(0, 7);
            while (floor->isWall(
                transform->position.x + deltaX[dir],
                transform->position.y + deltaY[dir])) {
                dir = Math::random(0, 7);
            }
            direction = directions[dir];
            transform->position.x += deltaX[dir];
            transform->position.y += deltaY[dir]; 
        }
    }

    void render(Graphics* gfx) override {
    }
};

#endif
