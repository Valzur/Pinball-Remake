#pragma once
#include "Obstacle.h"

namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            namespace Obstacles {
                class Kicker : public Obstacle
                {
                private:
                    double x1, x2, x3, y1, y2, y3;
                public:
                    Kicker(double x1, double x2, double x3, double y1, double y2, double y3);
                    CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override;
                    void draw(Interface& interface) override;
                };
            }
        }
    }
}