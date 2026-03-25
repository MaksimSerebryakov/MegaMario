#pragma once

#include "Vec2.h"

class Component
{
public:
    bool has = false;
};

class CTransform : public Component
{
public:
    Vec2 pos = {0.0, 0.0};
    Vec2 prevPos = {0.0, 0.0};
    Vec2 scale = {1.0, 1.0};
    Vec2 velocity = {0.0, 0.0};
    float angle = 0.0;

    CTransform() {};
    CTransform(const Vec2 &p)
        : pos{p} {}
    CTransform(const Vec2 &p, const Vec2 &s, const Vec2 &v, float a)
        : pos{p}, prevPos{p}, scale{s}, velocity{v}, angle{a} {}
};

class CBoundingBox : public Component
{
};

class CLifeSpan : public Component
{
};

class CInput : public Component
{
};

class CAnimation : public Component
{
};

class CGravity : public Component
{
};

class CState : public Component
{
};