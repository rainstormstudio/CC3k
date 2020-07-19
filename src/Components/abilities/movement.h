#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../../entityManager.h"
#include "../transform.h"
#include "../floor.h"
#include "../actions.h"
#include <string>
#include <vector>
#include "../../math.h"

const std::string directions[8] = {
    "North",
    "South",
    "East",
    "West",
    "North-East",
    "North-West",
    "South-East",
    "South-West"
};

class Movement : public Component {
    std::string direction;
    bool hasControl;
public:
    Movement(bool hasControl) 
        : hasControl{hasControl} {}

    void init() override {
        direction = "";
    }
    
    void update(InputManager * events) override {
        Transform * transform = owner->getComponent<Transform>();
        Entity* map = owner->manager.getEntityByName("Map");
        Floor * floor = map->getComponent<Floor>();
        if (hasControl) {
            if (events->getInputType() >= NORTH && events->getInputType() <= SOUTHWEST) {         
                direction = directions[events->getInputType()];
                Actions * action = owner->getComponent<Actions>();
                std::vector<Entity*> enemies = owner->manager.getEntitiesByLayer(ENEMY_LAYER);
                bool collision = false;
                int dirX = transform->position.x + Math::deltaX[events->getExtraInputType()];
                int dirY = transform->position.y + Math::deltaY[events->getExtraInputType()];
                for (auto& enemy : enemies) {
                    Transform* enemyTransform = enemy->getComponent<Transform>();
                    if (enemyTransform->position.x == dirX && enemyTransform->position.y == dirY) {
                        collision = true;
                        break;
                    }
                }
                if (floor->isWall(dirX, dirY)) {
                    action->setAction("PC tried to go " + direction + " but stopped by a wall.");
                    direction = "";
                } else if (collision) {
                    action->setAction("PC tried to go " + direction + " but stopped by the enemy");
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
                int dirX = transform->position.x + Math::deltaX[dir];
                int dirY = transform->position.y + Math::deltaY[dir];

                std::vector<Entity*> entities = owner->manager.getEntitiesByLayer(ENEMY_LAYER);
                bool collision = false;
                for (auto& entity : entities) {
                    if (entity != owner) {
                        Transform* entityTransform = entity->getComponent<Transform>();
                        if (entityTransform->position.x == dirX && entityTransform->position.y == dirY) {
                            collision = true;
                            break;
                        }
                    }
                }
                if (!collision) {
                    transform->position.x += Math::deltaX[dir];
                    transform->position.y += Math::deltaY[dir]; 
                }
            }
        }
    }

    void render(Graphics* gfx) override {
    }

    ~Movement() override {}
};

#endif
