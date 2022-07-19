#pragma once

#include "Obstacle.h"

namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            namespace Obstacles {
                class Gate : public Obstacle
                {
                private:
                    Vector2D center;
                    double length;
                    double width;
                    bool AllowUp;

                    const sf::Color outlineColor = sf::Color(54, 79, 107);
                    const sf::Color radiantColor = sf::Color(67, 221, 230);

                public:
                    Gate(Vector2D Center, double length, double width, bool AllowUp = true);
                    CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override;
                    void draw(Interface& interface) override;
                };
            }
        }
    }
}