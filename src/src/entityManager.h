#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include "types.h"
#include "entity.h"
#include "component.h"
#include "graphics.h"

class EntityManager {
    std::vector<Entity*> entities;
public:
    void destroy();
    void update();
    void render(Graphics * gfx);
    Entity* addEntity(std::string name, LayerType layer);
    
    std::vector<Entity*> getEntitiesByLayer(LayerType layer) const;
    Entity* getEntityByName(std::string name) const;
    
    ~EntityManager();
};

#endif
