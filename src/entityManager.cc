#include "entityManager.h"

void EntityManager::destroy() {
    for (unsigned int i = 0; i < entities.size(); ++i) {
        delete entities[i];
        entities.erase(entities.begin() + i);
        i--;
    }
}

void EntityManager::destroyByLayer(LayerType layer) {
    for (unsigned int i = 0; i < entities.size(); ++i) {
        if (entities[i]->layer == layer) {
            delete entities[i];
            entities.erase(entities.begin() + i);
            i--;
        }
    }
}

void EntityManager::update(InputManager * events) {
    for (unsigned int i = 0; i < entities.size(); ++i) {
        entities[i]->update(events);
    }
    for (unsigned int i = 0; i < entities.size(); ++i) {
        if (!entities[i]->isAlive()) {
            delete entities[i];
            entities.erase(entities.begin() + i);
            i--;
        }
    }
}

void EntityManager::render(Graphics* gfx) {
    for (int layer = 0; layer < TOTAL_LAYERS; ++layer) {
        for (auto& entity : getEntitiesByLayer(static_cast<LayerType>(layer))) {
            entity->render(gfx);
        }
    }
}

Entity* EntityManager::addEntity(std::string name, LayerType layer) {
    Entity *entity = new Entity(*this, name, layer);
    entities.emplace_back(entity);
    return entity;
}

std::vector<Entity*> EntityManager::getEntities() const {
    return entities;
}

std::vector<Entity*> EntityManager::getEntitiesByLayer(LayerType layer) const {
    std::vector<Entity*> theEntities;
    for (auto& entity: entities){
        if (entity->layer == layer){
            theEntities.emplace_back(entity);
        }
    }
    return theEntities;
}

Entity* EntityManager::getEntityByName(std::string name) const {
    for (auto& entity: entities) {
        if (entity->name == name) {
            return entity;
        }
    }
    return nullptr;
}

EntityManager::~EntityManager() {
    for (auto& entity : entities) {
        delete entity;
    }
}
