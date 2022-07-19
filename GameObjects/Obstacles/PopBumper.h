#pragma once
#include "Bumper.h"

namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            namespace Obstacles {
                class PopBumper : public Bumper {
                private:
                public:
                    PopBumper(Vector2D pos, double rad);
                    CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override;
                    void start() override;
                    void draw(Interface& interface) override;
                };
            }
        }
    }
}