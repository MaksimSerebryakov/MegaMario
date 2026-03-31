#pragma once

class Vec2
{
public:
    float x = 0, y = 0, vecLength = 0;

    Vec2() {}
    Vec2(float other_x, float other_y);
    Vec2(const Vec2 &other);

    bool operator==(const Vec2 &rhs) const;
    bool operator!=(const Vec2 &rhs) const;

    Vec2 operator+(const Vec2 &rhs) const;
    Vec2 operator-(const Vec2 &rhs) const;
    Vec2 operator/(const float rhs) const;
    Vec2 operator*(const float rhs) const;

    void operator+=(const Vec2 &rhs);
    void operator-=(const Vec2 &rhs);
    void operator/=(const float rhs);
    void operator*=(const float rhs);

    float dist(const Vec2 &rhs) const;

    float length() const;
    Vec2 normalise() const;

    void print() const;
};