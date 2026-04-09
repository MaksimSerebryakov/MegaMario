#pragma once

#include "Scene.h"
#include "Entity.h"

#define ACTION_QUIT "QUIT"
#define ACTION_TOGGLE_GRID "TOGGLE_GRID"
#define ACTION_TOGGLE_TEXTURES "TOGGLE_TEXTURES"
#define ACTION_TOGGLE_COLLISIONS "TOGGLE_COLLISIONS"
#define ACTION_UP "UP"
#define ACTION_DOWN "DOWN"
#define ACTION_LEFT "LEFT"
#define ACTION_RIGHT "RIGHT"
#define ACTION_SHOOT "shoot"

#define PLAYER_X_SPEED 4.0
#define PLAYER_JUMP_SPEED 15.0

#define BULLET_LIFESPAN 45

class GameEngine;

class Scene_Play : public Scene
{
    struct PlayerConfig
    {
        float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
        std::string WEAPON;
    };

protected:
    std::string m_levelPath;
    std::shared_ptr<Entity> m_player;
    PlayerConfig m_playerConfig;
    bool m_drawTextures = true;   // Show entities Textures
    bool m_drawCollisions = false; // Debug: show collision bounding boxes
    bool m_drawGrid = false;      // Debug: show grid
    const Vec2 m_gridSize = {64, 64};
    // dummy font as sf::Text doesn't have default constructor
    sf::Font m_font;
    sf::Text m_gridText;
    bool m_stillOnTheGround = false;
    bool m_onTheWall = false;
    bool m_onTheRightWall = false;
    bool m_onTheLeftWall = false;

    void init(const std::string &levelPath);

    void update();
    void onEnd();

    void sDoAction(const Action &action); // System: do Action system
    void sAnimation();                    // System: Animation system
    void sMovement();                     // System: movement system
    void sDebug();                        // System: debug system
    void sEnemySpawner();                 // System: enemy spawner system
    void sCollision();                    // System: Collision system
    void sLifespan();                     // System: Lifespan system

    void solvePlayerTileCollision(std::shared_ptr<Entity> e);
    void solvePlayerWindowCollision();
    void solveBulletTileCollision(
        std::shared_ptr<Entity> tile,
        std::shared_ptr<Entity> bullet);
    void solveBulletWindowCollision();

    void loadLevel(const std::string &filename); // load entities from level config file

    void drawGrid();           // Draw a grid inside level scene
    void drawCollisionBoxes(); // Draw entities Collision boxes
    void drawTextures();       // Draw textures

    void spawnPlayer();
    void spawnBullet();

public:
    Scene_Play(const std::string levelPath, GameEngine *gameEngine = nullptr);

    void sRender();                      // System: render system
    void doAction(const Action &action); // Outer do action func, for game engine user input

    Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);

    ~Scene_Play();
};