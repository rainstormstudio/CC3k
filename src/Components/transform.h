#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../entityManager.h"
#include "floor.h"
#include "../math.h"

class Transform : public Component {
public:
    Vec2 position;

    Transform() : position{-1, -1} {}

    Transform(int posX, int posY) 
        : position{posX, posY} {}

    void init() override {
        if (position.x == -1 && position.y == -1) {
            Entity* floorEntity = owner->manager.getEntityByName("Map");
            Floor* floor = floorEntity->getComponent<Floor>();
            std::vector<Entity*> entities = owner->manager.getEntities();
            bool validPosition = false;
            int posX = 0;
            int posY = 0;
            while (!validPosition) {
                validPosition = true;
                posY = Math::random(1, floor->getMapHeight() - 1);
                posX = Math::random(1, floor->getMapWidth() - 1);
                if (!floor->isChamber(posX, posY)) {
                    validPosition = false;
                    continue;
                }
                for (auto& entity : entities) {
                    if (entity->hasComponent<Transform>()) {
                        Transform * entityTransform = entity->getComponent<Transform>();
                        if (entityTransform->position.x == posX && entityTransform->position.y == posY) {
                            validPosition = false;
                            break;
                        }
                    }
                }
            }
            position.x = posX;
            position.y = posY;            
        }
    }

    void update(InputManager * events) override {}

    void render(Graphics * gfx) override {}

    ~Transform() override {}
};

#endif
