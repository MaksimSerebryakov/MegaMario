#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Scene.h"

class Scene_Menu : public Scene
{
protected:
    std::string m_title;
    std::string m_hint;
    std::vector<std::string> m_menuStrings;
    std::vector<std::string> m_levelPaths;
    // this is a dummy font for m_menuText, as sf::Text doesn't have default contructor
    sf::Font m_font;
    sf::Text m_menuText;
    size_t m_selectedLevelIndex = 0;

    void init();
    void update();
    void onEnd();
    void sDoAction(const Action &action);

    void drawText(const std::string &str, const sf::Vector2f pos,
                  const sf::Color &color = sf::Color::Black);

public:
    Scene_Menu(GameEngine *gameEngine = nullptr);

    void sRender();

    void doAction(const Action &action);

    ~Scene_Menu();
};
