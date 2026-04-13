#pragma once

#include <memory>

#include "Entity.h"

/*
    Note!!!
    Those getOverlap functions is used only to detect collision rectangle
    wneh two bounding boxes are not subsets of each other cause I only
    need to detect the start of a collision and instantly solve it

    In this game engine a situation when I need to solve a collision between
    2 objects one of each geometrically includes another is impossible.


    Example: e1 includes e2, so this game engine will not calculate
        the overlap rect correctly, I don't need to process this case for this game!!
        I will change getOverlap() logic in the further projects.
    ____________
   |  e1        |
   |            |
   |    ____    |
   |   | e2 |   |
   |___|____|___|
*/

class Physics
{
public:
    Physics() {}

    static Vec2 getOverlap(std::shared_ptr<Entity> e1,
                           std::shared_ptr<Entity> e2);

    static Vec2 getPreviousOverlap(std::shared_ptr<Entity> e1,
                                   std::shared_ptr<Entity> e2);
};