#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

#include "Animation.h"

#define ASSET_STANDING "stand"
#define ASSET_GROUND_TILE "ground"
#define ASSET_BRICK_TILE "brick"
#define ASSET_GREENTUBE_TALL "greenTubeTall"
#define ASSET_RUNNING "running"
#define ASSET_JUMPING "jumping"
#define ASSET_BULLET "bullet"

typedef std::map<std::string, sf::Texture> TextureMap;
typedef std::map<std::string, Animation> AnimationMap;
typedef std::map<std::string, sf::Font> FontMap;

class Assets
{
    TextureMap m_textures;
    AnimationMap m_animations;
    FontMap m_fonts;

public:
    void addFont(const std::string &name, const std::string &path);
    void addAnimation(const std::string &name, Animation animation);
    void addTexture(const std::string &name, const std::string &path);

    sf::Texture &getTexture(const std::string &name);
    const sf::Texture &getTexture(const std::string &name) const;
    sf::Font &getFont(const std::string &name);
    const sf::Font &getFont(const std::string &name) const;
    Animation &getAnimation(const std::string &name);
    const Animation &getAnimation(const std::string &name) const;

    void loadFromFile(const std::string &path);
};