#pragma once

#include <vector>
#include <map>
#include <memory>
#include <iostream>

#include "Entity.h"

#define PLAYER_TAG "player"
#define TILE_TAG "tile"

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
    EntityVector m_entities;
    EntityMap m_entityMap;
    EntityVector m_entitiesToAdd;

    size_t m_totalEntities = 0;

    void removeDeadEntities(EntityVector &entities);

public:
    EntityManager() {}

    void init();
    void update();
    std::shared_ptr<Entity> addEntity(const std::string &tag);
    EntityVector &getEntities();
    EntityVector &getEntities(const std::string &tag);
};