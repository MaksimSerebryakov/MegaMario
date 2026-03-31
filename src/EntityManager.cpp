#include "EntityManager.h"

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
    auto entity = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++, true));

    m_entitiesToAdd.push_back(entity);

    if (tag == PLAYER_TAG)
    {
        entity->addComponent<CInput>();
    }

    return entity;
}

EntityVector &EntityManager::getEntities()
{
    return m_entities;
}

EntityVector &EntityManager::getEntities(const std::string &tag)
{
    return m_entityMap[tag];
}

void EntityManager::update()
{
    for (auto e : m_entitiesToAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->getTag()].push_back(e);
    }

    m_entitiesToAdd.clear();

    removeDeadEntities(m_entities);

    for (auto &pair : m_entityMap)
    {
        removeDeadEntities(pair.second);
    }
}

void EntityManager::removeDeadEntities(EntityVector &vec)
{
    vec.erase(std::remove_if(vec.begin(), vec.end(), [](std::shared_ptr<Entity> e)
                             { return !e->isActive(); }),
              vec.end());
}