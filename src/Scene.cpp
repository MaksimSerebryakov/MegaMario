#include <array>

#include "Scene.h"
#include "GameEngine.h"

Scene::Scene() {}

Scene::Scene(GameEngine *gameEngine)
    : m_gameEngine{gameEngine} {}

void Scene::setPaused(bool paused)
{
    m_paused = paused;
}

void Scene::registerAction(sf::Keyboard::Scancode inputKey, const std::string &actionName)
{
    m_actions[inputKey] = actionName;
}

void Scene::doAction(const Action &action) {}

const ActionMap &Scene::getActionMap() const
{
    return m_actions;
}

size_t Scene::width() const
{
    if (m_gameEngine == nullptr)
    {
        return 0;
    }

    return m_gameEngine->window().getSize().x;
}

size_t Scene::height() const
{
    if (m_gameEngine == nullptr)
    {
        return 0;
    }

    return m_gameEngine->window().getSize().y;
}

size_t Scene::currentFrame() const
{
    return m_currentFrame;
}

bool Scene::hasEnded() const
{
    return m_hasEnded;
}

void Scene::drawLine(const Vec2 &p1, const Vec2 &p2)
{
    std::array line = {
        sf::Vertex{sf::Vector2f(p1.x, p1.y)},
        sf::Vertex{sf::Vector2f(p2.x, p2.y)}
    };

    m_gameEngine->window().draw(line.data(), line.size(), sf::PrimitiveType::Lines);
}