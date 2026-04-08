#include <iostream>

#include "Animation.h"

Animation::Animation()
    : m_sprite{sf::Sprite(m_texture)} {}

Animation::Animation(
    const sf::Sprite &sprite,
    int frameCount,
    int currentFrame,
    int speed,
    const Vec2 &size,
    const std::string &name)
    : m_sprite{sf::Sprite(m_texture)},
      m_frameCount{frameCount},
      m_currentFrame{currentFrame},
      m_speed{speed},
      m_size{size},
      m_name{name}
{
    m_sprite = sprite;

    
    m_sprite.setOrigin({size.x / 2, size.y / 2});
}

void Animation::update()
{
    if (m_speed == 0)
    {
        return;
    }
    int textureOffsetX = ((m_currentFrame % m_frameCount) / m_speed) * (int)m_size.x;

    m_sprite.setTextureRect(sf::IntRect(
        {textureOffsetX, 0},
        {(int)m_size.x, (int)m_size.y}));

    m_currentFrame++;
}

const Vec2 Animation::getSize() const
{
    Vec2 v(m_size.x * m_sprite.getScale().x, m_size.y * m_sprite.getScale().y);

    return Vec2(m_size.x * m_sprite.getScale().x, m_size.y * m_sprite.getScale().y);
}

const std::string &Animation::getName() const
{
    return m_name;
}

sf::Sprite &Animation::getSprite()
{
    return m_sprite;
}

bool Animation::hasEnded()
{
    if ((m_currentFrame > 0) && (m_currentFrame % m_frameCount == 0))
    {
        return true;
    }

    return false;
}