#include "GameEngine.h"
#include "Scene_Menu.h"

GameEngine::GameEngine(const std::string &path)
{
    init(path);
}

void GameEngine::init(const std::string &path)
{
    m_assets.loadFromFile(path);

    m_window.create(sf::VideoMode({1280, 768}), "Mega Mario");
    m_window.setFramerateLimit(60);

    changeScene(SCENE_MENU, std::make_shared<Scene_Menu>(this));
}

void GameEngine::run()
{
    while (isRunning())
    {
        update();
    }
}

void GameEngine::update()
{
    sUserInput();

    m_scenes[m_currentScene]->update();
}

void GameEngine::sUserInput()
{
    while (std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            quit();
        }

        if (event->is<sf::Event::KeyPressed>())
        {
            const auto *keyPressed = event->getIf<sf::Event::KeyPressed>();

            if (currentScene()->getActionMap().find(keyPressed->scancode) ==
                currentScene()->getActionMap().end())
            {
                continue;
            }

            currentScene()->doAction(Action(currentScene()->getActionMap().at(keyPressed->scancode), "START"));
        }
    }
}

void GameEngine::changeScene(const std::string &sceneName, std::shared_ptr<Scene> scene,
                             bool endCurrentScene)
{
    if (m_scenes.find(sceneName) == m_scenes.end())
    {
        m_scenes[sceneName] = scene;
    }

    // Return window center to starting point TODO: mb need to solve that other way
    sf::View view = m_window.getView();
    view.setCenter({m_window.getSize().x / (float)2.0,
                    view.getCenter().y});
    m_window.setView(view);

    m_currentScene = sceneName;
}

bool GameEngine::isRunning()
{
    return m_running && m_window.isOpen();
}

const Assets &GameEngine::assets() const
{
    return m_assets;
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_scenes[m_currentScene];
}

sf::RenderWindow &GameEngine::window()
{
    return m_window;
}

void GameEngine::quit()
{
    m_window.close();
    m_running = false;
}