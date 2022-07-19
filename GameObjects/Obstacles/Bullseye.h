#pragma once
#include "Obstacle.h"

namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            namespace Obstacles {
                class Bullseye : public Obstacle {
                private:
                    Vector2D Center;
                    double Length;
                    const double width = GlobalWidth;
                    bool isVertical = false, collidedLastFrame = false;
                public:
                    Bullseye(Vector2D Center, double Length, bool isVertical);

                    CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager)override;
                    void draw(Interface& interface)override;
                };
            }
        }
    }
}
