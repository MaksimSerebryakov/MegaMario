#include <iostream>
#include <fstream>

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
        std::cerr << "Error loading texture \"" << name << "\"" << std::endl;
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
    std::string assetName, textureName, assetPath, animationName, fontName;
    int frameCount, animSpeed;
    float sizeX, sizeY, scaleX, scaleY;

    std::fstream fs(path);

    while (fs >> assetName)
    {
        if (assetName == "Texture")
        {
            fs >> textureName >> assetPath;

            addTexture(textureName, assetPath);
            continue;
        }
        if (assetName == "Animation")
        {
            fs >> animationName >> textureName >> frameCount >> animSpeed >>
                sizeX >> sizeY >> scaleX >> scaleY;

            sf::Sprite sprite(getTexture(textureName));
            sprite.setTextureRect(sf::IntRect({0, 0}, {(int)sizeX, (int)sizeY}));
            sprite.setScale({scaleX, scaleY});
            addAnimation(
                animationName,
                Animation(
                    sprite,
                    frameCount,
                    0,
                    animSpeed,
                    Vec2(sizeX, sizeY),
                    animationName));

            continue;
        }
        if (assetName == "Font")
        {
            fs >> fontName >> assetPath;
            addFont(fontName, assetPath);
        }
    }
}