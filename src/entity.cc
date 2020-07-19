#include "entity.h"
#include "component.h"
#include "entityManager.h"
#include "graphics.h"
#include "inputManager.h"

Entity::Entity(EntityManager & manager) : manager{manager} {
    isActive = true;
}

Entity::~Entity() {
    for (auto& component : components) {
        delete component;
    }
}

Entity::Entity(EntityManager & manager, std::string name, LayerType layer) 
    : manager{manager}, name{name}, layer{layer} {
    isActive = true;
}

void Entity::update(InputManager * events) {
    for (int i = 0; i < static_cast<int>(components.size()); ++i) {
        components[i]->update(events);
    }
}

void Entity::render(Graphics * gfx) {
    for (auto& component : components) {
        component->render(gfx);
    }
}

bool Entity::isAlive() const {
    return isActive;
}

void Entity::destroy() {
    isActive = false;
}
