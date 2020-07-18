#include "entity.h"
#include "component.h"
#include "graphics.h"

Entity::Entity() {
    isActive = true;
}

Entity::Entity(std::string name, LayerType layer) 
    : name{name}, layer{layer} {

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

template <typename T, typename... Targs>
T& Entity::addComponent(Targs&&... args) {
    T* component = new T(std::forward<T>(args)...);
    component->owner = this;
    components.emplace_back(component);
    componentTypes[&typeid(*component)] = component;
    component->init();
    return *component;
}

template <typename T>
bool Entity::hasComponent() const {
    return static_cast<bool>(componentTypes.count(&typeid(T)));
}

template <typename T>
T* Entity::getComponent() {
    return static_cast<T*>(componentTypes[&typeid(T)]);
}
