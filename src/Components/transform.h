#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../entityManager.h"

class Transform : public Component {
public:
    Vec2 position;

    Transform(int posX, int posY) 
        : position{posX, posY} {}

    void init() override {}

    void update(InputManager * events) override {}

    void render(Graphics * gfx) override {}

    ~Transform() override {}
};

#endif
