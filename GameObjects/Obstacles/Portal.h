#pragma once

#include "../../Utility/CollisionDetection.h"
#include "Obstacle.h"


namespace Valzuroid {
    using namespace Pinball;
    namespace Pinball {
        namespace GameObjects {
            namespace Obstacles {
                class Portal : public Obstacle {
                private:
                    const sf::Color color = sf::Color(67, 221, 230);
                    const double outlineThickness = -2.0f;  // Negative sign means inwards

                    Vector2D Pos1;
                    Vector2D Pos2;
                    double radius = 5;


                    sf::Texture texture;
                    sf::Sprite sprite;
                public:
                    Portal(Vector2D Pos1, Vector2D Pos2, double radius = 35);
                    CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override;
                    void start() override;
                    void draw(Interface& interface) override;
                };
            }
        }
    }
}