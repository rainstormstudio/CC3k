#include "entity.h"
#include "component.h"
#include "graphics.h"

Entity::Entity() {
    isActive = true;
}

Entity::Entity(std::string name, LayerType layer) 
    : name{name}, layer{layer} {
    isActive = true;
}

void Entity::update() {
    for (auto& component : components) {
        component->update();
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
