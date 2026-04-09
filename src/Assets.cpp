#include <iostream>

#include "Assets.h"

void Assets::addFont(const std::string &name, const std::string &path)
{
    sf::Font font;

    if (!font.openFromFile(path))
    {
        std::cerr << "Error loading font \"" << name << "\"" << std::endl;
        return;
    }

    m_fonts[name] = font;
}

sf::Font &Assets::getFont(const std::string &name)
{
    return m_fonts[name];
}

const sf::Font &Assets::getFont(const std::string &name) const
{
    return m_fonts.at(name);
}

void Assets::addTexture(const std::string &name, const std::string &path)
{
    sf::Texture texture;

    if (!texture.loadFromFile(path))
    {
        std::cerr << "Error loading font \"" << name << "\"" << std::endl;
        return;
    }

    m_textures[name] = texture;
}

sf::Texture &Assets::getTexture(const std::string &name)
{
    return m_textures[name];
}

const sf::Texture &Assets::getTexture(const std::string &name) const
{
    return m_textures.at(name);
}

void Assets::addAnimation(const std::string &name, Animation animation)
{
    m_animations[name] = animation;
}

Animation &Assets::getAnimation(const std::string &name)
{
    return m_animations[name];
}

const Animation &Assets::getAnimation(const std::string &name) const
{
    return m_animations.at(name);
}

void Assets::loadFromFile(const std::string &path)
{
    // TODO: ipmlement reading config file
    addFont("Lato", "fonts/Lato.ttf");
    addFont("8bit", "fonts/8bit.ttf");

    addTexture(ASSET_STANDING, "images/stand.png");
    addTexture(ASSET_GROUND_TILE, "images/ground.png");
    addTexture(ASSET_BRICK_TILE, "images/brick.png");
    addTexture(ASSET_GREENTUBE_TALL, "images/greenTubeTall.png");
    addTexture(ASSET_RUNNING, "images/running.png");
    addTexture(ASSET_JUMPING, "images/jumping.png");
    addTexture(ASSET_BULLET, "images/bullet.png");

    sf::Sprite sprite(getTexture(ASSET_STANDING));
    sprite.setTextureRect(sf::IntRect({0, 0}, {24, 24}));
    sprite.setScale({-2.0, 2.0});
    addAnimation(
        ASSET_STANDING,
        Animation(
            sprite,
            180,
            0,
            170,
            Vec2(24.0, 24.0),
            ASSET_STANDING));

    sprite.setTexture(getTexture(ASSET_JUMPING));
    sprite.setTextureRect(sf::IntRect({0, 0}, {24, 29}));
    sprite.setScale({-2.0, 2.0});
    addAnimation(
        ASSET_JUMPING,
        Animation(
            sprite,
            1,
            0,
            0,
            Vec2(24.0, 29.0),
            ASSET_JUMPING));

    sprite.setTexture(getTexture(ASSET_RUNNING));
    sprite.setTextureRect(sf::IntRect({0, 0}, {25, 24}));
    sprite.setScale({-2.0, 2.0});
    addAnimation(
        ASSET_RUNNING,
        Animation(
            sprite,
            40,
            0,
            10,
            Vec2(25.0, 24.0),
            ASSET_RUNNING));

    sprite.setTexture(getTexture(ASSET_GROUND_TILE));
    sprite.setTextureRect(sf::IntRect({0, 0}, {16, 16}));
    sprite.setScale({4.0, 4.0});
    addAnimation(
        ASSET_GROUND_TILE,
        Animation(
            sprite,
            1,
            0,
            0,
            Vec2(16.0, 16.0),
            ASSET_GROUND_TILE));

    sprite.setTexture(getTexture(ASSET_BRICK_TILE));
    sprite.setTextureRect(sf::IntRect({0, 0}, {16, 16}));
    sprite.setScale({4.0, 4.0});
    addAnimation(
        ASSET_BRICK_TILE,
        Animation(
            sprite,
            1,
            0,
            0,
            Vec2(16.0, 16.0),
            ASSET_BRICK_TILE));

    sprite.setTexture(getTexture(ASSET_GREENTUBE_TALL));
    sprite.setTextureRect(sf::IntRect({0, 0}, {32, 64}));
    sprite.setScale({4.0, 4.0});
    addAnimation(
        ASSET_GREENTUBE_TALL,
        Animation(
            sprite,
            1,
            0,
            0,
            Vec2(32.0, 64.0),
            ASSET_GREENTUBE_TALL));

    sprite.setTexture(getTexture(ASSET_BULLET));
    sprite.setTextureRect(sf::IntRect({0, 0}, {14, 8}));
    sprite.setScale({2.0, 2.0});
    addAnimation(
        ASSET_BULLET,
        Animation(
            sprite,
            1,
            0,
            0,
            Vec2(14.0, 8.0),
            ASSET_BULLET));
}