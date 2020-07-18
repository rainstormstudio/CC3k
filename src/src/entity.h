#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <map>
#include <string>
#include "types.h"

class Component;
class Graphics;

class Entity {
    bool isActive;
    std::vector<Component*> components;
    std::map<const std::type_info*, Component*> componentTypes;
public:
    std::string name;
    LayerType layer;

    Entity();
    Entity(std::string name, LayerType layer);
    void update();
    void render(Graphics * gfx);

    bool isAlive() const;
    void destroy();

    template <typename T, typename... Targs>
    T& addComponent(Targs&&... args);

    template <typename T>
    bool hasComponent() const;

    template <typename T>
    T* getComponent();
};

#endif
