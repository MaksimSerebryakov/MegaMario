#include "Scene_play.h"
#include "Scene_Menu.h"
#include "GameEngine.h"
#include "Physics.h"

float numSign(float num)
{
    return num == 0.0 ? 0.0 : num / std::abs(num);
}

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
    registerAction(sf::Keyboard::Scancode::Space, ACTION_SHOOT);
    registerAction(sf::Keyboard::Scancode::P, ACTION_PAUSE);

    m_gridText.setFont(m_gameEngine->assets().getFont("Lato"));
    m_gridText.setCharacterSize(12);

    loadLevel(levelPath);
}

void Scene_Play::loadLevel(const std::string &filename)
{
    m_entities = EntityManager();
    // TODO : remove, add from config!!
    m_playerConfig.MAXSPEED = 64;

    int gridsInWindow = m_gameEngine->window().getSize().x / (int)m_gridSize.x;

    for (int i = 0; i < 7; i++)
    {
        auto e = m_entities.addEntity(DECORATION_TAG);

        if (i & 1)
        {
            e->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_CLOUD_SKY_ODD), false);
        }
        else
        {
            e->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_CLOUD_SKY_EVEN), false);
        }
        e->addComponent<CTransform>(gridToMidPixel(i * gridsInWindow, 7, e));
    }

    auto bush = m_entities.addEntity(DECORATION_TAG);
    bush->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BUSH), false);
    bush->addComponent<CTransform>(gridToMidPixel(1, 1, bush));

    auto brick = m_entities.addEntity(TILE_TAG);
    brick->addComponent<CBoundingBox>(Vec2(64, 64));
    brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);
    brick->addComponent<CTransform>(gridToMidPixel(6, 6, brick));

    brick = m_entities.addEntity(TILE_TAG);
    brick->addComponent<CBoundingBox>(Vec2(64, 64));
    brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);
    brick->addComponent<CTransform>(gridToMidPixel(1, 1, brick));

    brick = m_entities.addEntity(TILE_TAG);
    brick->addComponent<CBoundingBox>(Vec2(64, 64));
    brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);
    brick->addComponent<CTransform>(gridToMidPixel(4, 2, brick));

    brick = m_entities.addEntity(TILE_TAG);
    brick->addComponent<CBoundingBox>(Vec2(64, 64));
    brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);
    brick->addComponent<CTransform>(gridToMidPixel(4, 3, brick));

    brick = m_entities.addEntity(TILE_TAG);
    brick->addComponent<CBoundingBox>(Vec2(64, 64));
    brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);
    brick->addComponent<CTransform>(gridToMidPixel(7, 2, brick));

    brick = m_entities.addEntity(TILE_TAG);
    brick->addComponent<CBoundingBox>(Vec2(64, 64));
    brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);
    brick->addComponent<CTransform>(gridToMidPixel(7, 3, brick));

    // brick = m_entities.addEntity(TILE_TAG);
    // brick->addComponent<CBoundingBox>(Vec2(64, 64));
    // brick->addComponent<CTransform>(gridToMidPixel(3, 4, brick));
    // brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation("brick"), false);

    brick = m_entities.addEntity(TILE_TAG);
    brick->addComponent<CBoundingBox>(Vec2(64, 64));
    brick->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);
    brick->addComponent<CTransform>(gridToMidPixel(5, 6, brick));

    auto tube = m_entities.addEntity(TILE_TAG);
    tube->addComponent<CBoundingBox>(Vec2(128, 256));
    tube->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_GREENTUBE_TALL), false);
    tube->addComponent<CTransform>(gridToMidPixel(8, 0, tube));

    auto question = m_entities.addEntity(TILE_TAG);
    question->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_QUESTION_ACTIVE), true);
    question->addComponent<CBoundingBox>(
        Vec2(m_gameEngine->assets().getAnimation(ASSET_QUESTION_ACTIVE).getSize().x,
             m_gameEngine->assets().getAnimation(ASSET_QUESTION_ACTIVE).getSize().y));
    question->addComponent<CTransform>(gridToMidPixel(8, 6, question));

    question = m_entities.addEntity(TILE_TAG);
    question->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_QUESTION_ACTIVE), true);
    question->addComponent<CBoundingBox>(
        Vec2(m_gameEngine->assets().getAnimation(ASSET_QUESTION_ACTIVE).getSize().x,
             m_gameEngine->assets().getAnimation(ASSET_QUESTION_ACTIVE).getSize().y));
    question->addComponent<CTransform>(gridToMidPixel(9, 6, question));

    for (int i = 0; i < 100; i++)
    {
        if ((i != 15) && (i != 25) && (i != 26))
        {
            auto e = m_entities.addEntity(TILE_TAG);

            e->addComponent<CBoundingBox>(Vec2(64, 64));
            e->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_GROUND_TILE), false);
            e->addComponent<CTransform>(gridToMidPixel(i, 0, e));
        }
    }
    for (int i = 11; i < 100; i++)
    {
        auto e = m_entities.addEntity(TILE_TAG);

        e->addComponent<CBoundingBox>(Vec2(64, 64));
        e->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BRICK_TILE), false);
        e->addComponent<CTransform>(gridToMidPixel(i, 3, e));
    }

    spawnPlayer();
}

void Scene_Play::returnToTheStart()
{
    m_player->getComponent<CTransform>().pos = gridToMidPixel(4, 6, m_player);

    sf::View view = m_gameEngine->window().getView();
    view.setCenter({m_gameEngine->window().getSize().x / (float)2.0,
                    view.getCenter().y});
    m_gameEngine->window().setView(view);
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
        if (action.name() == ACTION_SHOOT)
        {
            m_player->getComponent<CInput>().shoot = true;
        }
        if (action.name() == ACTION_PAUSE)
        {
            m_paused = !m_paused;
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
        if (action.name() == ACTION_SHOOT)
        {
            m_player->getComponent<CInput>().shoot = false;
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

    sf::RectangleShape pauseRect({(float)m_gameEngine->window().getSize().x,
                                  (float)m_gameEngine->window().getSize().y});
    pauseRect.setFillColor(sf::Color(0, 0, 0, 78));
    pauseRect.setPosition({viewCenterX - pauseRect.getSize().x / 2, 0.0});
    if (m_paused)
    {
        m_gameEngine->window().draw(pauseRect);
    }

    m_gameEngine->window().display();
}

void Scene_Play::sMovement()
{
    Vec2 pVel(0, m_player->getComponent<CTransform>().velocity.y);

    // std::cout << m_player->getComponent<CState>().state << std::endl;

    if (m_player->getComponent<CInput>().shoot)
    {
        spawnBullet();
        m_player->getComponent<CInput>().shoot = false;
    }

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
    if (!m_player->getComponent<CInput>().up && (m_player->getComponent<CState>().state == STATE_AIR))
    {
        if (pVel.y < 0)
        {
            pVel.y = 0;
        }
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

    m_stillOnTheGround = false;
    m_onTheWall = false;
    m_onTheLeftWall = false;
    m_onTheRightWall = false;

    for (auto e : m_entities.getEntities(TILE_TAG))
    {
        if (e->hasComponent<CBoundingBox>())
        {
            solvePlayerTileCollision(e);
            for (auto b : m_entities.getEntities(BULLET_TAG))
            {
                solveBulletTileCollision(e, b);
            }
        }
    }

    if (m_stillOnTheGround)
    {
        m_player->getComponent<CState>().state = STATE_ON_GROUND;
    }
    else
    {
        m_player->getComponent<CState>().state = STATE_AIR;
    }

    solvePlayerWindowCollision();
    solveBulletWindowCollision();
}

void Scene_Play::sAnimation()
{
    // TODO: Think of fixing left-right blinking when on the wall

    // Change player's animation
    if (m_player->hasComponent<CAnimation>())
    {
        auto &playerAnimation = m_player->getComponent<CAnimation>().animation;

        // Save previous direction of animation on X axis
        float scaleX = playerAnimation.getSprite().getScale().x;

        if (m_player->getComponent<CState>().state == STATE_AIR)
        {
            m_player->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_JUMPING), true);
        }
        else if (m_player->getComponent<CInput>().left || m_player->getComponent<CInput>().right)
        {
            if (playerAnimation.getName() != ASSET_RUNNING)
            {
                m_player->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_RUNNING), true);
            }
        }
        else
        {
            if (playerAnimation.getName() != ASSET_STANDING)
            {
                m_player->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_STANDING), true);
            }
        }

        // Set prev animation direction of X axis to save direction after changing player animation
        auto &sprite = playerAnimation.getSprite();
        sprite.setScale({scaleX, sprite.getScale().y});
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

            if (!e->getComponent<CAnimation>().repeat && e->getComponent<CAnimation>().animation.hasEnded())
            {
                e->destroy();
            }
        }
    }
}

void Scene_Play::sLifespan()
{
    for (auto e : m_entities.getEntities())
    {
        if (e->hasComponent<CLifeSpan>())
        {
            if ((--e->getComponent<CLifeSpan>().remaining) <= 0)
            {
                e->destroy();
            }
        }
    }
}

// ************************************
// *----------SYSTEMS ABOVE-----------*
// ************************************

void Scene_Play::solvePlayerTileCollision(std::shared_ptr<Entity> e)
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
                m_stillOnTheGround = true;
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

                // after brick is hit by a player from below, change animation to BOOM
                if (e->getComponent<CAnimation>().animation.getName() == ASSET_BRICK_TILE)
                {
                    e->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BOOM), false);
                    e->removeComponent<CBoundingBox>();
                }
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
            m_stillOnTheGround = true;
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

void Scene_Play::solvePlayerWindowCollision()
{
    float windowLeft = m_gameEngine->window().getView().getCenter().x -
                       m_gameEngine->window().getSize().x / 2;
    float windowBottom = m_gameEngine->window().getView().getCenter().y +
                         m_gameEngine->window().getSize().y / 2;

    if (m_player->getComponent<CTransform>().pos.y +
            m_player->getComponent<CBoundingBox>().halfSize.y >
        windowBottom)
    {
        returnToTheStart();
        return;
    }

    if ((m_player->getComponent<CTransform>().pos.x -
         m_player->getComponent<CBoundingBox>().halfSize.x) < windowLeft)
    {
        m_player->getComponent<CTransform>().pos.x =
            m_player->getComponent<CBoundingBox>().halfSize.x + windowLeft;
    }
}

void Scene_Play::solveBulletTileCollision(std::shared_ptr<Entity> tile,
                                          std::shared_ptr<Entity> bullet)
{
    Vec2 overlap = Physics::getOverlap(tile, bullet);

    if ((overlap.x > 0) && (overlap.y > 0))
    {
        if (bullet->getComponent<CTransform>().velocity.x > 0)
        {
            bullet->getComponent<CTransform>().pos.x =
                tile->getComponent<CTransform>().pos.x - tile->getComponent<CBoundingBox>().halfSize.x -
                bullet->getComponent<CBoundingBox>().halfSize.x;
        }
        else
        {
            bullet->getComponent<CTransform>().pos.x =
                tile->getComponent<CTransform>().pos.x + tile->getComponent<CBoundingBox>().halfSize.x +
                bullet->getComponent<CBoundingBox>().halfSize.x;
        }

        bullet->destroy();
        if (tile->getComponent<CAnimation>().animation.getName() == ASSET_BRICK_TILE)
        {
            // after bullet hit a brick change animation to BOOM
            if (tile->getComponent<CAnimation>().animation.getName() == ASSET_BRICK_TILE)
            {
                tile->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BOOM), false);
                tile->removeComponent<CBoundingBox>();
            }
        }
    }
}

void Scene_Play::solveBulletWindowCollision()
{
    float windowLeft = m_gameEngine->window().getView().getCenter().x -
                       m_gameEngine->window().getSize().x / 2;
    float windowRight = m_gameEngine->window().getView().getCenter().x +
                        m_gameEngine->window().getSize().x / 2;

    auto &bullets = m_entities.getEntities(BULLET_TAG);

    for (auto b : bullets)
    {
        if (((b->getComponent<CTransform>().pos.x -
              b->getComponent<CBoundingBox>().halfSize.x) < windowLeft) ||
            ((b->getComponent<CTransform>().pos.x +
              b->getComponent<CBoundingBox>().halfSize.x) > windowRight))
        {
            b->destroy();
        }
    }
}

void Scene_Play::doAction(const Action &action)
{
    sDoAction(action);
}

void Scene_Play::update()
{
    // If we exit the level, we destroy m_player so after entering the level
    // we need to load it again
    if (m_player == nullptr)
    {
        loadLevel(m_levelPath);
    }

    m_entities.update();

    // std::cout << m_entities.getEntities(PLAYER_TAG).size() << std::endl;

    if (!m_paused)
    {
        sMovement();
        sCollision();
        sLifespan();
        sAnimation();
    }

    sRender();

    m_currentFrame++;
}

Vec2 Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
    float x = entity->getComponent<CAnimation>().animation.getSize().x;
    float y = entity->getComponent<CAnimation>().animation.getSize().y;

    // x = entity->getComponent<CBoundingBox>().size.x;
    // y = entity->getComponent<CBoundingBox>().size.y;

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

void Scene_Play::spawnBullet()
{
    auto bullet = m_entities.addEntity(BULLET_TAG);
    bullet->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_BULLET), false);
    bullet->addComponent<CBoundingBox>(m_gameEngine->assets().getAnimation(ASSET_BULLET).getSize());
    bullet->addComponent<CLifeSpan>(BULLET_LIFESPAN);

    Vec2 bulPos = m_player->getComponent<CTransform>().pos;
    float scale = -m_player->getComponent<CAnimation>().animation.getSprite().getScale().x;

    bullet->addComponent<CTransform>(bulPos, Vec2(1.0, 1.0), Vec2(numSign(scale) * 15.0, 0.0), 0.0);
}

void Scene_Play::spawnPlayer()
{
    // TODO: add reading from config
    auto player = m_entities.addEntity(PLAYER_TAG);

    player->addComponent<CBoundingBox>(Vec2(48, 48));
    player->addComponent<CAnimation>(m_gameEngine->assets().getAnimation(ASSET_JUMPING), true);
    player->addComponent<CTransform>(gridToMidPixel(4, 6, player));
    player->addComponent<CGravity>(GRAVITY_CONST);

    m_player = player;
}

void Scene_Play::onEnd()
{
    m_gameEngine->changeScene(SCENE_MENU, std::make_shared<Scene_Menu>(m_gameEngine));

    m_player = nullptr;
}

Scene_Play::~Scene_Play() {}