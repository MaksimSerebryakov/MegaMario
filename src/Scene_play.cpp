#include "Scene_play.h"
#include "Scene_Menu.h"
#include "GameEngine.h"

Scene_Play::Scene_Play(const std::string levelPath, GameEngine *gameEngine)
    : Scene(gameEngine),
      m_levelPath{levelPath},
      m_gridText(m_font)
{
    init(levelPath);
}

void Scene_Play::init(const std::string &levelPath)
{
    registerAction(sf::Keyboard::Scancode::Escape, ACTION_QUIT);
    registerAction(sf::Keyboard::Scancode::G, ACTION_TOGGLE_GRID);

    m_gridText.setFont(m_gameEngine->assets().getFont("Lato"));
    m_gridText.setCharacterSize(12);

    loadLevel(levelPath);
}

void Scene_Play::loadLevel(const std::string &filename)
{
}


// Systems
void Scene_Play::sDoAction(const Action &action)
{
    if (action.type() == ACTION_TYPE_START)
    {
        if (action.name() == ACTION_QUIT)
        {
            onEnd();
        }
        if (action.name() == ACTION_TOGGLE_GRID) {
            m_drawGrid = !m_drawGrid;
        }
    }
}

void Scene_Play::sRender()
{
    m_gameEngine->window().clear(sf::Color(27, 191, 250));

    if (m_drawGrid)
    {
        drawGrid();
    }

    m_gameEngine->window().display();
}

// Systems above

void Scene_Play::doAction(const Action &action)
{
    sDoAction(action);
}

void Scene_Play::update()
{
    m_currentFrame++;

    sRender();
}

void Scene_Play::drawGrid()
{
    // sf::View view = m_gameEngine->window().getView();

    // view.setCenter({m_gameEngine->window().getView().getCenter().x + (float)0.2,
    //                 m_gameEngine->window().getView().getCenter().y});

    // m_gameEngine->window().setView(view);

    float leftX = m_gameEngine->window().getView().getCenter().x - width() / 2;
    float rightX = leftX + width() + m_gridSize.x;
    float nextGridX = leftX - ((int)leftX % (int)m_gridSize.x);

    float windowWidth = (float)width();
    float windowHeight = (float)height();

    for (float y = 0.0; y < windowHeight; y += m_gridSize.y)
    {
        drawLine(Vec2(leftX, windowHeight - y), Vec2(rightX, windowHeight - y));

        for (float x = nextGridX; x < rightX; x += m_gridSize.x)
        {
            drawLine(Vec2(x, 0.0), Vec2(x, windowHeight));

            std::string xCell = std::to_string((int)x / (int)m_gridSize.x);
            std::string yCell = std::to_string((int)y / (int)m_gridSize.y);

            m_gridText.setString("(" + xCell + ", " + yCell + ")");
            m_gridText.setPosition({x + 3, windowHeight - y - m_gridSize.y + 2});

            m_gameEngine->window().draw(m_gridText);
        }
    }
}

void Scene_Play::onEnd()
{
    m_gameEngine->changeScene(SCENE_MENU, std::make_shared<Scene_Menu>(m_gameEngine));
}

Scene_Play::~Scene_Play() {}