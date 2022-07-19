#pragma once

#include "Obstacle.h"
#include "../../Utility/CollisionDetection.h"


namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            namespace Obstacles {
                class Magnet :public Obstacle {
                private:
                    Vector2D Position;
                    double magnetRadius, radius;
                    sf::Texture texture;
                    sf::Sprite sprite;

                    const double outlineThickness = -2.0f;  // Negative sign means inwards

                public:
                    Magnet(Vector2D Position, double Magnetradius, double radius);

                    //Getters
                    double getMagnetRadius()const;
                    double getRadius()const;
                    Vector2D getCenter() const;
                    //Setters
                    void setMagnetRadius(double magnetRadius);
                    void setRadius(double radius);

                    CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override;
                    void start() override;
                    void draw(Interface& interface) override;
                };
            }
        }
    }
}