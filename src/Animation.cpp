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
}

const Vec2 &Animation::getSize() const
{
    return m_size;
}