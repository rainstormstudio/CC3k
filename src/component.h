#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;
class Graphics;
class InputManager;

class Component {
public:
    Entity * owner;
    virtual void init() {}
    virtual void update(InputManager * events) {}
    virtual void render(Graphics * gfx) {}
    virtual ~Component() {}
};

#endif
