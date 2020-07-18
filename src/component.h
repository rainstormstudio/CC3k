#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;
class Graphics;

class Component {
public:
    Entity * owner;
    virtual void init();
    virtual void update();
    virtual void render(Graphics * gfx);
};

#endif
