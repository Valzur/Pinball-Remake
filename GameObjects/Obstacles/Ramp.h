
#pragma once
#include "Obstacle.h"
#include "../../Utility/CollisionDetection.h"


namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            namespace Obstacles {
                class Ramp : public Obstacle
                {
                private:
                    const sf::Color color = sf::Color(54, 79, 107);
                    Vector2D Size, Center;
                    double Angle;
                    int FramesTillNextCollision = 0;
                public:
                    Ramp(Vector2D Size, Vector2D Center, double Angle);
                    CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override;
                    void start() override;
                    void draw(Interface& interface) override;
                };
            }
        }
    }
}