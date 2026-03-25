#include "Entity.h"

Entity::Entity(const std::string &tag, int id, bool active)
    : m_tag(tag),
      m_active(active),
      m_id(id) {}

bool Entity::isActive() const
{
    return m_active;
}

const std::string &Entity::getTag() const
{
    return m_tag;
}

const size_t Entity::getId() const
{
    return m_id;
}

void Entity::destroy()
{
    m_active = false;
}
