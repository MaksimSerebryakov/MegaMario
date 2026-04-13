#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Action.h"
#include "EntityManager.h"

#define SCENE_MENU "menu"
#define SCENE_PLAY "play"

class GameEngine;

typedef std::map<sf::Keyboard::Scancode, std::string> ActionMap;

class Scene
{
protected:
    GameEngine *m_gameEngine = nullptr;
    EntityManager m_entities;
    ActionMap m_actions;
    bool m_paused = false;
    bool m_hasEnded = false;
    size_t m_currentFrame = 0;

    virtual void onEnd() = 0;
    void setPaused(bool paused);

public:
    Scene();
    Scene(GameEngine *gameEngine);

    virtual void sDoAction(const Action &action) = 0;
    virtual void update() = 0;
    virtual void sRender() = 0;

    virtual void doAction(const Action &action);

    void simulate(const size_t frames);

    void registerAction(sf::Keyboard::Scancode inputKey, const std::string &actionName);

    size_t width() const;
    size_t height() const;
    size_t currentFrame() const;

    bool hasEnded() const;
    const ActionMap &getActionMap() const;
    void drawLine(const Vec2 &p1, const Vec2 &p2);

    virtual ~Scene() = default;
};