#pragma once

#include <tuple>
#include <string>

#include "EntityManager.h"
#include "Components.h"

typedef std::tuple<
    CTransform,
    CBoundingBox,
    CLifeSpan,
    CInput,
    CAnimation,
    CGravity,
    CState>
    ComponentsTuple;

class Entity
{
    friend class EntityManager;

    std::string m_tag = "default";
    size_t m_id = 0;
    bool m_active = true;
    ComponentsTuple m_components;

public:
    // TODO: remove to private
    Entity(const std::string &tag, int id, bool active);

    bool isActive() const;
    const std::string &getTag() const;
    const size_t getId() const;
    void destroy();

    template <typename T, typename... TArgs>
    T addComponent(TArgs &&...mArgs)
    {
        auto &component = getComponent<T>();

        component = T(std::forward<TArgs>(mArgs)...);
        component.has = true;

        return component;
    }

    template <typename T>
    T &getComponent()
    {
        return std::get<T>(m_components);
    }

    template <typename T>
    const T &getComponent() const
    {
        return std::get<T>(m_components);
    }

    template <typename T>
    bool hasComponent() const
    {
        return getComponent<T>().has;
    }

    template <typename T>
    void removeComponent()
    {
        getComponent<T>() = T();
    }
};