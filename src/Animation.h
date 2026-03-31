#pragma once

#include <SFML/Graphics.hpp>

#include "Vec2.h"

class Animation
{
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    int m_frameCount = 0;
    int m_currentFrame = 0;
    int m_speed = 0;
    Vec2 m_size;
    std::string m_name;

public:
    Animation();
    Animation(
        const sf::Sprite &sprite,
        int frameCount,
        int currentFrame,
        int speed,
        const Vec2 &size,
        const std::string &name);

    void update();
    void hasEnded();
    std::string &getName() const;
    const Vec2 &getSize() const;
    sf::Sprite &getSprite();
};