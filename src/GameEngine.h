#pragma once

#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

#include "Scene.h"
#include "Assets.h"

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine
{
protected:
    SceneMap m_scenes;
    sf::RenderWindow m_window;
    Assets m_assets;
    std::string m_currentScene;
    bool m_running = true;
    int m_simulationSpeed = 1;

    void init(const std::string &path);
    void update();

    void sUserInput();

    std::shared_ptr<Scene> currentScene();

public:
    GameEngine(const std::string &path);

    void changeScene(const std::string &sceneName, std::shared_ptr<Scene> scene,
                     bool endCurrentScene = false);

    void quit();
    void run();

    sf::RenderWindow &window();
    const Assets &assets() const;
    bool isRunning();
};