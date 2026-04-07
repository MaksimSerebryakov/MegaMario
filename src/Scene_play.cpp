#include "Scene_play.h"
#include "Scene_Menu.h"
#include "GameEngine.h"
#include "Physics.h"

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
    registerAction(sf::Keyboard::Scancode::T, ACTION_TOGGLE_TEXTURES);
    registerAction(sf::Keyboard::Scancode::C, ACTION_TOGGLE_COLLISIONS);
    registerAction(sf::Keyboard::Scancode::W, ACTION_UP);
    registerAction(sf::Keyboard::Scancode::S, ACTION_DOWN);
    registerAction(sf::Keyboard::Scancode::D, ACTION_RIGHT);
    registerAction(sf::Keyboard::Scancode::A, ACTION_LEFT);

    m_gridText.setFont(m_gameEngine->assets().getFont("Lato"));
    m_gridText.setCharacterSize(12);

    loadLevel(levelPath);
}

void Scene_Play::loadLevel(const std::string &filename)
{
    m_entities = EntityManager();
    // TODO : remove, add from config!!
    m_playerConfig.MAXSPEED = 64;

    spawnPlayer();

    auto brick = m_entities.addEntity(TILE_TAG);
    brick->addComponent<CBoundingBox>(Vec2(64, 64));
    brick->addComponent<CTransform>(gridToMidPixel(6, 6, brick));
    brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);

    brick = m_entities.addEntity(TILE_TAG);
    brick->addComponent<CBoundingBox>(Vec2(64, 64));
    brick->addComponent<CTransform>(gridToMidPixel(1, 1, brick));
    brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);

    brick = m_entities.addEntity(TILE_TAG);
    brick->addComponent<CBoundingBox>(Vec2(64, 64));
    brick->addComponent<CTransform>(gridToMidPixel(4, 2, brick));
    brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);
    brick = m_entities.addEntity(TILE_TAG);
    brick->addComponent<CBoundingBox>(Vec2(64, 64));
    brick->addComponent<CTransform>(gridToMidPixel(4, 3, brick));
    brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);

    brick = m_entities.addEntity(TILE_TAG);
    brick->addComponent<CBoundingBox>(Vec2(64, 64));
    brick->addComponent<CTransform>(gridToMidPixel(7, 2, brick));
    brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);
    brick = m_entities.addEntity(TILE_TAG);
    brick->addComponent<CBoundingBox>(Vec2(64, 64));
    brick->addComponent<CTransform>(gridToMidPixel(7, 3, brick));
    brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);

    // brick = m_entities.addEntity(TILE_TAG);
    // brick->addComponent<CBoundingBox>(Vec2(64, 64));
    // brick->addComponent<CTransform>(gridToMidPixel(3, 4, brick));
    // brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation("brick"), false);

    brick = m_entities.addEntity(TILE_TAG);
    brick->addComponent<CBoundingBox>(Vec2(64, 64));
    brick->addComponent<CTransform>(gridToMidPixel(5, 6, brick));
    brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);

    auto tube = m_entities.addEntity(TILE_TAG);
    tube->addComponent<CBoundingBox>(Vec2(128, 256));
    tube->addComponent<CTransform>(gridToMidPixel(8, 0, tube));
    tube->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_GREENTUBE_TALL), false);

    for (int i = 0; i < 100; i++)
    {
        auto e = m_entities.addEntity(TILE_TAG);

        e->addComponent<CBoundingBox>(Vec2(64, 64));
        e->addComponent<CTransform>(gridToMidPixel(i, 0, e));
        e->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_GROUND_TILE), false);
    }
}

// ************************************
// *-------------SYSTEMS--------------*
// ************************************

void Scene_Play::sDoAction(const Action &action)
{
    // Since we have only 2 Action types now, we can use if/else, not if(action_start), if(action_end)
    if (action.type() == ACTION_TYPE_START)
    {
        if (action.name() == ACTION_QUIT)
        {
            onEnd();
        }
        if (action.name() == ACTION_TOGGLE_GRID)
        {
            m_drawGrid = !m_drawGrid;
        }
        if (action.name() == ACTION_TOGGLE_COLLISIONS)
        {
            m_drawCollisions = !m_drawCollisions;
        }
        if (action.name() == ACTION_TOGGLE_TEXTURES)
        {
            m_drawTextures = !m_drawTextures;
        }
        if (action.name() == ACTION_UP) //&&
                                        //(m_player->getComponent<CState>().state != STATE_AIR))
        {
            m_player->getComponent<CInput>().up = true;
        }
        if (action.name() == ACTION_DOWN)
        {
            m_player->getComponent<CInput>().down = true;
        }
        if (action.name() == ACTION_LEFT)
        {
            m_player->getComponent<CInput>().left = true;
        }
        if (action.name() == ACTION_RIGHT)
        {
            m_player->getComponent<CInput>().right = true;
        }
    }
    else
    {
        if (action.name() == ACTION_UP)
        {
            m_player->getComponent<CInput>().up = false;
        }
        if (action.name() == ACTION_DOWN)
        {
            m_player->getComponent<CInput>().down = false;
        }
        if (action.name() == ACTION_LEFT)
        {
            m_player->getComponent<CInput>().left = false;
        }
        if (action.name() == ACTION_RIGHT)
        {
            m_player->getComponent<CInput>().right = false;
        }
    }
}

void Scene_Play::sRender()
{
    m_gameEngine->window().clear(sf::Color(27, 191, 250));

    auto view = m_gameEngine->window().getView();
    float viewCenterX = std::max(view.getCenter().x, m_player->getComponent<CTransform>().pos.x);
    view.setCenter({viewCenterX, view.getCenter().y});
    m_gameEngine->window().setView(view);

    if (m_drawTextures)
    {
        drawTextures();
    }
    if (m_drawCollisions)
    {
        drawCollisionBoxes();
    }

    if (m_drawGrid)
    {
        drawGrid();
    }

    m_gameEngine->window().display();
}

void Scene_Play::sMovement()
{
    Vec2 pVel(0, m_player->getComponent<CTransform>().velocity.y);

    // std::cout << m_player->getComponent<CState>().state << std::endl;

    if (m_player->getComponent<CInput>().left && (!m_onTheRightWall))
    {
        pVel.x = -PLAYER_X_SPEED;
    }
    if (m_player->getComponent<CInput>().right && (!m_onTheLeftWall))
    {
        pVel.x = PLAYER_X_SPEED;
    }
    if (m_player->getComponent<CInput>().up && (m_player->getComponent<CState>().state != STATE_AIR))
    {
        m_player->getComponent<CState>().state = STATE_AIR;
        pVel.y = -PLAYER_JUMP_SPEED;
    }
    // if (m_player->getComponent<CInput>().up)
    // {
    //     pVel.y = -2.0;
    // }
    // if (m_player->getComponent<CInput>().down && (m_player->getComponent<CState>().state != STATE_ON_GROUND))
    // {
    //     pVel.y = 0.5;
    // }

    if (m_player->getComponent<CState>().state == STATE_ON_GROUND)
    {
        pVel.y = 0;
    }
    // if (m_onTheWall && (m_player->getComponent<CState>().state != STATE_ON_GROUND))
    // {
    //     pVel.x = 0;
    // }
    m_player->getComponent<CTransform>().velocity = pVel;

    for (auto e : m_entities.getEntities())
    {
        if (e->hasComponent<CGravity>())
        {
            if (m_player->getComponent<CState>().state != STATE_ON_GROUND)
            {
                e->getComponent<CTransform>().velocity.y += e->getComponent<CGravity>().gravity;
            }
        }

        if (e->getComponent<CTransform>().velocity.y > m_playerConfig.MAXSPEED)
        {
            e->getComponent<CTransform>().velocity.y = m_playerConfig.MAXSPEED;
        }

        e->getComponent<CTransform>().prevPos = e->getComponent<CTransform>().pos;
        e->getComponent<CTransform>().pos += e->getComponent<CTransform>().velocity;
    }
}

void Scene_Play::sCollision()
{
    m_player->getComponent<CState>().state = STATE_AIR;

    bool stillOnTheGround = false;
    m_onTheWall = false;
    m_onTheLeftWall = false;
    m_onTheRightWall = false;

    for (auto e : m_entities.getEntities(TILE_TAG))
    {
        Vec2 overlap = Physics::getOverlap(m_player, e);
        Vec2 prevOverlap = Physics::getPreviousOverlap(m_player, e);

        if ((overlap.x > 0) && (overlap.y > 0))
        {
            if (prevOverlap.y <= 0)
            {
                m_player->getComponent<CTransform>().velocity.y = 0;

                // Moving down
                if (m_player->getComponent<CTransform>().pos.y >
                    m_player->getComponent<CTransform>().prevPos.y)
                {
                    m_player->getComponent<CState>().state = STATE_ON_GROUND;
                    stillOnTheGround = true;
                    m_player->getComponent<CTransform>().pos.y =
                        e->getComponent<CTransform>().pos.y -
                        e->getComponent<CBoundingBox>().halfSize.y -
                        m_player->getComponent<CBoundingBox>().halfSize.y;
                }
                // Moving up
                if (m_player->getComponent<CTransform>().pos.y <
                    m_player->getComponent<CTransform>().prevPos.y)
                {
                    m_player->getComponent<CTransform>().pos.y =
                        e->getComponent<CTransform>().pos.y +
                        e->getComponent<CBoundingBox>().halfSize.y +
                        m_player->getComponent<CBoundingBox>().halfSize.y;
                }
            }

            if (prevOverlap.x <= 0)
            {
                m_player->getComponent<CTransform>().velocity.x = 0;

                // Moving left to right
                if (m_player->getComponent<CTransform>().pos.x >
                    m_player->getComponent<CTransform>().prevPos.x)
                {
                    m_player->getComponent<CTransform>().pos.x =
                        e->getComponent<CTransform>().pos.x -
                        e->getComponent<CBoundingBox>().halfSize.x -
                        m_player->getComponent<CBoundingBox>().halfSize.x;
                }
                // Moving right to left
                if (m_player->getComponent<CTransform>().pos.x <
                    m_player->getComponent<CTransform>().prevPos.x)
                {
                    m_player->getComponent<CTransform>().pos.x =
                        e->getComponent<CTransform>().pos.x +
                        e->getComponent<CBoundingBox>().halfSize.x +
                        m_player->getComponent<CBoundingBox>().halfSize.x;
                }
            }
        }
        // we moved a player on top of tile and if so we are on the ground. When player moves off tiles, this won't work
        if ((overlap.x >= 0) && (overlap.y == 0))
        {
            if ((prevOverlap.y >= 0) &&
                (m_player->getComponent<CTransform>().pos.y < e->getComponent<CTransform>().pos.y))
            {
                stillOnTheGround = true;
            }
        }

        overlap = Physics::getOverlap(m_player, e);
        prevOverlap = Physics::getPreviousOverlap(m_player, e);

        if ((overlap.x == 0) && (overlap.y > 0))
        {
            if (prevOverlap.x >= 0)
            {
                if (m_player->getComponent<CTransform>().pos.x < e->getComponent<CTransform>().pos.x)
                {
                    m_onTheLeftWall = true;
                }
                if (m_player->getComponent<CTransform>().pos.x > e->getComponent<CTransform>().pos.x)
                {
                    m_onTheRightWall = true;
                }
            }
        }
    }

    if (stillOnTheGround)
    {
        m_player->getComponent<CState>().state = STATE_ON_GROUND;
    }
    else
    {
        m_player->getComponent<CState>().state = STATE_AIR;
    }
}

void Scene_Play::sAnimation()
{
    // TODO: Think of fixing left-right blinking when on the wall

    // Change player's animation
    if (m_player->hasComponent<CAnimation>())
    {
        // TODO: add jumping animation
        if (m_player->getComponent<CTransform>().velocity.x != 0)
        {
            if (m_player->getComponent<CAnimation>().animation.getName() != ASSET_RUNNING)
            {
                m_player->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_RUNNING), true);
            }
        }
        else
        {
            if (m_player->getComponent<CAnimation>().animation.getName() != ASSET_STANDING)
            {
                float scaleX = m_player->getComponent<CAnimation>().animation.getSprite().getScale().x;

                m_player->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_STANDING), true);

                auto &sprite = m_player->getComponent<CAnimation>().animation.getSprite();
                sprite.setScale({scaleX, sprite.getScale().y});
            }
        }
    }

    // Update animations
    for (auto e : m_entities.getEntities())
    {
        if (e->hasComponent<CAnimation>())
        {
            e->getComponent<CAnimation>().animation.update();

            auto &sprite = e->getComponent<CAnimation>().animation.getSprite();

            if (((sprite.getScale().x > 0) &&
                 (e->getComponent<CTransform>().velocity.x > 0)) ||
                ((sprite.getScale().x < 0) &&
                 (e->getComponent<CTransform>().velocity.x < 0)))
            {
                sprite.setScale({sprite.getScale().x * -1, sprite.getScale().y});
            }
        }
    }
}

// ************************************
// *----------SYSTEMS ABOVE-----------*
// ************************************

void Scene_Play::doAction(const Action &action)
{
    sDoAction(action);
}

void Scene_Play::update()
{
    // If we exit the level, we destroy m_playerm so after entering the level
    // we need to load it again
    if (m_player == nullptr)
    {
        loadLevel(m_levelPath);
    }

    m_entities.update();

    sMovement();
    sCollision();
    sAnimation();
    sRender();

    m_currentFrame++;
}

Vec2 Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
    // TODO: uncomment when animation is added
    // float x = entity->getComponent<CAnimation>().animation.getSize().x;
    // float y = entity->getComponent<CAnimation>().animation.getSize().y;

    float x = entity->getComponent<CBoundingBox>().size.x;
    float y = entity->getComponent<CBoundingBox>().size.y;

    x = gridX * m_gridSize.x + x / 2;
    y = height() - gridY * m_gridSize.y - y / 2;

    return Vec2(x, y);
}

void Scene_Play::drawTextures()
{
    for (auto e : m_entities.getEntities())
    {
        if (e->hasComponent<CAnimation>())
        {
            auto sprite = e->getComponent<CAnimation>().animation.getSprite();
            auto pos = e->getComponent<CTransform>().pos;
            sprite.setPosition({pos.x, pos.y});

            m_gameEngine->window().draw(sprite);
        }
    }
}

void Scene_Play::drawCollisionBoxes()
{
    for (auto e : m_entities.getEntities())
    {
        if (e->hasComponent<CBoundingBox>())
        {
            auto &box = e->getComponent<CBoundingBox>();
            auto &position = e->getComponent<CTransform>();
            sf::RectangleShape rect;

            rect.setPosition({position.pos.x, position.pos.y});
            rect.setSize({box.size.x - 1, box.size.y - 1});
            rect.setOrigin({box.halfSize.x, box.halfSize.y});
            rect.setFillColor(sf::Color(0, 0, 0, 0));
            rect.setOutlineColor(sf::Color(255, 255, 255));
            rect.setOutlineThickness(1);

            m_gameEngine->window().draw(rect);
        }
    }
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

void Scene_Play::spawnPlayer()
{
    // TODO: add reading from config
    auto player = m_entities.addEntity(PLAYER_TAG);

    player->addComponent<CBoundingBox>(Vec2(48, 48));
    player->addComponent<CTransform>(gridToMidPixel(4, 6, player));
    player->addComponent<CGravity>(0.5);
    player->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_STANDING), true);

    m_player = player;
}

void Scene_Play::onEnd()
{
    m_gameEngine->changeScene(SCENE_MENU, std::make_shared<Scene_Menu>(m_gameEngine));
    m_player = nullptr;
}

Scene_Play::~Scene_Play() {}