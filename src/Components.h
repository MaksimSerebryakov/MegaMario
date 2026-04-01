#pragma once

#include "Vec2.h"
#include "Animation.h"

#define STATE_JUMPING "jumping"
#define STATE_STANDING "standing"
#define STATE_RUNNING "running"
#define STATE_ON_GROUND "on_ground"
#define STATE_AIR "air"

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
public:
    Vec2 size = {0.0, 0.0};
    Vec2 halfSize = {0.0, 0.0};

    CBoundingBox() {}
    CBoundingBox(const Vec2 &otherSize)
        : size{otherSize},
          halfSize{otherSize.x / 2, otherSize.y / 2} {}
};

class CLifeSpan : public Component
{
public:
    CLifeSpan() {}
};

class CInput : public Component
{
public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;
    bool canShoot = true;
    bool canJump = true;

    CInput() {}
};

class CAnimation : public Component
{
public:
    Animation animation;
    bool repeat = false;

    CAnimation() {}
    CAnimation(const Animation &a, bool r)
        : animation{a},
          repeat{r} {}
};

class CGravity : public Component
{
public:
    float gravity = 0.0;

    CGravity() {}
    CGravity(float g) : gravity{g} {}
};

class CState : public Component
{
public:
    std::string state = STATE_AIR;

    CState() {}
    CState(const std::string &s) : state{s} {}
};