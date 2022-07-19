#pragma once

#include "Obstacle.h"
#include "../../Defs.h"
#include "../../Utility/CollisionDetection.h"

namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            namespace Obstacles {
                class Collectable :public Obstacle
                {
                private:
                    double radius, Timer = FlashTimer;
                    string L;
                    Vector2D Center;
                    bool Active = true, Used = false;

                    const sf::Color radiantColor = sf::Color(67, 221, 230);

                public:
                    Collectable(double radius, string L, Vector2D Center);
                    CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override;
                    void draw(Interface& interface) override;
                };
            }
        }
    }
}