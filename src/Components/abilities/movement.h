#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../../entityManager.h"
#include "../transform.h"

const int deltaX[8] = {0, 0, 1, -1, 1, -1, 1, -1};
const int deltaY[8] = {-1, 1, 0, 0, -1, -1, 1, 1};

class Movement : public Component {
public:
    Movement() {}

    void init() override {}
    
    void update(InputManager * events) override {
        Transform * transform = owner->getComponent<Transform>();
        if (events->getInputType() >= NORTH && events->getInputType() <= SOUTHWEST) {
            transform->position.x += deltaX[events->getInputType()];
            transform->position.y += deltaY[events->getInputType()];
        }
    }

    void render(Graphics* gfx) override {}
};

#endif
