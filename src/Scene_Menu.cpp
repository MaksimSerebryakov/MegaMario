#include "Scene_Menu.h"
#include "Scene_play.h"
#include "GameEngine.h"

Scene_Menu::Scene_Menu(GameEngine *gameEngine)
    : Scene(gameEngine),
      m_menuText(m_font)
{
    init();
}

void Scene_Menu::init()
{
    registerAction(sf::Keyboard::Scancode::W, "UP");
    registerAction(sf::Keyboard::Scancode::S, "DOWN");
    registerAction(sf::Keyboard::Scancode::D, "PLAY");
    registerAction(sf::Keyboard::Scancode::Escape, "QUIT");

    // TODO: load all text from config
    m_title = "MegaMario";

    m_menuStrings.push_back("LEVEL 1");
    m_menuStrings.push_back("LEVEL 2");
    m_menuStrings.push_back("LEVEL 3");

    m_hint = "UP:W  DOWN:S  PLAY:D  EXIT:ESC";

    m_menuText.setFont(m_gameEngine->assets().getFont("8bit"));
    m_menuText.setCharacterSize(48);
    m_menuText.setFillColor(sf::Color::Black);
}

void Scene_Menu::update()
{
    m_currentFrame++;
    sRender();
}

void Scene_Menu::onEnd()
{
    m_gameEngine->quit();
}

void Scene_Menu::sDoAction(const Action &action)
{
    // Since we have only 2 Action types now, we can use if/else, not if(action_start), if(action_end)
    if (action.type() == ACTION_TYPE_START)
    {
        if (action.name() == "DOWN")
        {
            ++m_selectedLevelIndex %= 3;
        }
        if (action.name() == "UP")
        {
            m_selectedLevelIndex = (m_selectedLevelIndex + 2) % 3;
        }
        if (action.name() == "QUIT")
        {
            onEnd();
        }
        if (action.name() == "PLAY")
        {
            m_gameEngine->changeScene(SCENE_PLAY,
                                      std::make_shared<Scene_Play>("text.txt", m_gameEngine));
        }
    }
}

void Scene_Menu::drawText(const std::string &str, sf::Vector2f pos,
                          const sf::Color &color)
{
    m_menuText.setString(str);
    m_menuText.setPosition(pos);
    m_menuText.setFillColor(color);

    m_gameEngine->window().draw(m_menuText);
}

void Scene_Menu::sRender()
{
    m_gameEngine->window().clear(sf::Color(194, 187, 235));

    m_menuText.setCharacterSize(48);
    drawText(m_title, sf::Vector2f(10, 10));

    for (int i = 0; i < m_menuStrings.size(); i++)
    {
        sf::Color lineColor = i == m_selectedLevelIndex ? sf::Color::White : sf::Color::Black;

        drawText(m_menuStrings[i], sf::Vector2f(10, 100 + i * 50), lineColor);
    }

    int hintPosY = m_gameEngine->window().getSize().y - 48;

    m_menuText.setCharacterSize(24);
    drawText(m_hint, sf::Vector2f(10, hintPosY));

    m_gameEngine->window().display();
}

void Scene_Menu::doAction(const Action &action)
{
    sDoAction(action);
}

Scene_Menu::~Scene_Menu()
{
}