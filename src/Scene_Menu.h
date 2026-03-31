#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Scene.h"

class Scene_Menu : public Scene
{
protected:
    std::string m_title;                    // Game Title in the menu
    std::string m_hint;                     // Control hint text
    std::vector<std::string> m_menuStrings; // Levels names
    std::vector<std::string> m_levelPaths;  // Levels configs paths

    // this is a dummy font for m_menuText, as sf::Text doesn't have default contructor
    sf::Font m_font;
    sf::Text m_menuText;
    size_t m_selectedLevelIndex = 0;

    void init();
    void update();
    void onEnd();

    void sDoAction(const Action &action); // System: Do Action System

    void drawText(const std::string &str, const sf::Vector2f pos, // Draw a string on the screen
                  const sf::Color &color = sf::Color::Black);

public:
    Scene_Menu(GameEngine *gameEngine = nullptr);

    void sRender(); // System: Render System

    void doAction(const Action &action); // Outer do action func, for game engine user input

    ~Scene_Menu();
};
