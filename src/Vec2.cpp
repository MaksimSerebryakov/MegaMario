#include <iostream>
#include <cmath>

#include "Vec2.h"

Vec2::Vec2(float other_x, float other_y)
    : x(other_x),
      y(other_y)
{
    vecLength = sqrtf(x * x + y * y);
}

Vec2::Vec2(const Vec2 &other)
    : Vec2(other.x, other.y) {}

bool Vec2::operator==(const Vec2 &rhs) const
{
    return ((x == rhs.x) && (y == rhs.y));
}
bool Vec2::operator!=(const Vec2 &rhs) const
{
    return !(*this == rhs);
}

Vec2 Vec2::operator+(const Vec2 &rhs) const
{
    return Vec2((x + rhs.x), (y + rhs.y));
}
Vec2 Vec2::operator-(const Vec2 &rhs) const
{
    return Vec2((x - rhs.x), (y - rhs.y));
}
Vec2 Vec2::operator*(const float rhs) const
{
    return Vec2((x * rhs), (y * rhs));
}
Vec2 Vec2::operator/(const float rhs) const
{
    return Vec2((x / rhs), (y / rhs));
}

void Vec2::operator+=(const Vec2 &rhs)
{
    x += rhs.x;
    y += rhs.y;
}
void Vec2::operator-=(const Vec2 &rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}
void Vec2::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
}
void Vec2::operator/=(const float rhs)
{
    x /= rhs;
    y /= rhs;
}

float Vec2::dist(const Vec2 &rhs) const
{
    return sqrtf((rhs.x - x) * (rhs.x - x) + (rhs.y - y) * (rhs.y - y));
}

void Vec2::print() const
{
    std::cout << x << " " << y << std::endl;
}

float Vec2::length() const
{
    return vecLength;
}

Vec2 Vec2::normalise() const
{
    return Vec2(x / vecLength, y / vecLength);
}
