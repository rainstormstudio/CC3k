#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <map>
#include <string>
#include "types.h"
#include <typeinfo>

class Component;
class EntityManager;
class Graphics;
class InputManager;

class Entity {
    bool isActive;
    std::map<const std::type_info*, Component*> componentTypes;
public:
    EntityManager& manager;
    
    std::vector<Component*> components;
    std::string name;
    LayerType layer;

    Entity(EntityManager & manager);
    Entity(EntityManager & manager, std::string name, LayerType layer);
    
    ~Entity();
    
    void update(InputManager * events);
    void render(Graphics * gfx);

    bool isAlive() const;
    void destroy();

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... args) {
        T* component = new T(std::forward<TArgs>(args)...);
        component->owner = this;
        components.emplace_back(component);
        componentTypes[&typeid(*component)] = component;
        component->init();
        return *component;
    }

    template <typename T>
    bool hasComponent() const {
        return static_cast<bool>(componentTypes.count(&typeid(T)));
    }

    template <typename T>
    T* getComponent() {
        return static_cast<T*>(componentTypes[&typeid(T)]);
    }
};

#endif
