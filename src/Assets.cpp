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

    addTexture("stand", "images/stand.png");
    addTexture("ground", "images/ground.png");
    addTexture("brick", "images/brick.png");
    addTexture("greenTube", "images/greenTube.png");

    sf::Sprite sprite(getTexture("stand"));
    sprite.setTextureRect(sf::IntRect({0, 0}, {22, 24}));
    sprite.setScale({-2.0, 2.0});
    addAnimation(
        "stand",
        Animation(
            sprite,
            2,
            0,
            1,
            Vec2(22.0, 24.0),
            "stand"));

    sprite.setTexture(getTexture("ground"));
    sprite.setTextureRect(sf::IntRect({0, 0}, {16, 16}));
    sprite.setScale({4.0, 4.0});
    addAnimation(
        "ground",
        Animation(
            sprite,
            1,
            0,
            0,
            Vec2(16.0, 16.0),
            "ground"));

    sprite.setTexture(getTexture("brick"));
    sprite.setTextureRect(sf::IntRect({0, 0}, {16, 16}));
    sprite.setScale({4.0, 4.0});
    addAnimation(
        "brick",
        Animation(
            sprite,
            1,
            0,
            0,
            Vec2(16.0, 16.0),
            "brick"));

    sprite.setTexture(getTexture("greenTube"));
    sprite.setTextureRect(sf::IntRect({0, 0}, {32, 64}));
    sprite.setScale({4.0, 4.0});
    addAnimation(
        "greenTube",
        Animation(
            sprite,
            1,
            0,
            1,
            Vec2(32.0, 64.0),
            "greenTube"));
}