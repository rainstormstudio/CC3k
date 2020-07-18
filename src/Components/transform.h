#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../entityManager.h"

class Transform : public Component {
public:
    Vec2 position;
    Vec2 velocity;

    Transform(int posX, int posY) 
        : position{posX, posY}, velocity{0, 0} {}

    void init() override {}

    void update() override {
        position += velocity;
    }

    void render(Graphics * gfx) override {}
};

#endif
