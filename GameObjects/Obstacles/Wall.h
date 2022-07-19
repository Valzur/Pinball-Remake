#pragma once
#include "Obstacle.h"

namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            namespace Obstacles {
                class Wall : public Obstacle
                {
                private:
                    const sf::Color color = sf::Color(54, 79, 107);
                    bool isVertical;
                    Vector2D Center;
                    bool collidedLastFrame = false;
                public:
                    explicit Wall(bool isVertical, Vector2D Center);
                    CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override;
                    void draw(Interface& interface) override;
                };
            }
        }
    }
}