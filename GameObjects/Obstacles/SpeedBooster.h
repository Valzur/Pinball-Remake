#pragma once
#include "Obstacle.h"
#include "../../Utility/CollisionDetection.h"

using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

namespace Valzuroid {
    using namespace Pinball;
    namespace Pinball {
        namespace GameObjects {
            namespace Obstacles {
                class SpeedBooster : public Obstacle {
                private:
                    const sf::Color outlineColor = sf::Color(54, 79, 107);
                    const double outlineThickness = -2.0f;  // Negative sign means inwards

                    double radius, HitTimer = FlashTimer;
                    Vector2D Center;
                    bool Hit = false;

                    sf::Texture texture;
                    sf::Sprite sprite;
                public:
                    SpeedBooster(double radius, Vector2D Center);
                    CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override;
                    void start() override;
                    void draw(Interface& interface) override;
                };
            }
        }
    }
}