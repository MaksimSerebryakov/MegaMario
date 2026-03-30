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

void Assets::loadFromFile(const std::string &path)
{
    // TODO: ipmlement reading config file
    addFont("Lato", "fonts/Lato.ttf");
    addFont("8bit", "fonts/8bit.ttf");
}