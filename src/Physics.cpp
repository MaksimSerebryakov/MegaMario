#include <cmath>

#include "Physics.h"

Vec2 Physics::getOverlap(std::shared_ptr<Entity> e1,
                         std::shared_ptr<Entity> e2)
{
    Vec2 overlap(0.0, 0.0);

    float dx = std::abs(e1->getComponent<CTransform>().pos.x -
                        e2->getComponent<CTransform>().pos.x);
    float dy = std::abs(e1->getComponent<CTransform>().pos.y -
                        e2->getComponent<CTransform>().pos.y);

    float oX = e1->getComponent<CBoundingBox>().halfSize.x +
               e2->getComponent<CBoundingBox>().halfSize.x - dx;
    float oY = e1->getComponent<CBoundingBox>().halfSize.y +
               e2->getComponent<CBoundingBox>().halfSize.y - dy;

    overlap.x = oX;
    overlap.y = oY;

    return overlap;
}

Vec2 Physics::getPreviousOverlap(std::shared_ptr<Entity> e1,
                                 std::shared_ptr<Entity> e2)
{
    Vec2 overlap(0.0, 0.0);

    float dx = std::abs(e1->getComponent<CTransform>().prevPos.x -
                        e2->getComponent<CTransform>().prevPos.x);
    float dy = std::abs(e1->getComponent<CTransform>().prevPos.y -
                        e2->getComponent<CTransform>().prevPos.y);

    float oX = e1->getComponent<CBoundingBox>().halfSize.x +
               e2->getComponent<CBoundingBox>().halfSize.x - dx;
    float oY = e1->getComponent<CBoundingBox>().halfSize.y +
               e2->getComponent<CBoundingBox>().halfSize.y - dy;

    if (oX > 0)
    {
        overlap.x = oX;
    }
    if (oY > 0)
    {
        overlap.y = oY;
    }

    return overlap;
}