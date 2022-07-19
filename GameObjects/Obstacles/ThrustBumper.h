#pragma once
#include "Bumper.h"
#include "../../Defs.h"

namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            namespace Obstacles {
                class ThrustBumper : public Bumper {
                private:
                public:
                    ThrustBumper(Vector2D pos, double rad);
                    CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override;
                    void start() override;
                    void draw(Interface& interface) override;
                };
            }
        }
    }
}