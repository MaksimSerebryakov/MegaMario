#include <iostream>

#include "Entity.h"
#include "Components.h"

int main()
{
    Entity e1("test", 0, true);
    Entity e2("test", 1, true);
    Entity e3("test", 2, true);

    e1.addComponent<CTransform>(
        Vec2(4.0, 5.0),
        Vec2(1.0, 1.0),
        Vec2(3.0, 3.0),
        0.5);

    if (e1.hasComponent<CTransform>())
    {
        auto component = e1.getComponent<CTransform>();

        std::cout << component.pos.x << " " << component.pos.y << std::endl;
        std::cout << component.prevPos.x << " " << component.prevPos.y << std::endl;
        std::cout << component.scale.x << " " << component.scale.y << std::endl;
        std::cout << component.velocity.x << " " << component.velocity.y << std::endl;
        std::cout << component.angle << std::endl;

        e1.removeComponent<CTransform>();
    }

    std::cout << "has CTransform: " << e1.hasComponent<CTransform>() << std::endl;

    return 0;
}