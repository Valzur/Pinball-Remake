#pragma once

#include "../../Utility/CollisionDetection.h"
#include "../../Defs.h"

namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            namespace Obstacles {
                class Lane : public Obstacle {
                private:
                    double length, Timer = LaneTimer;
                    const double width;
                    Vector2D Center;
                    bool Top = false, Bottom = false;

                    const sf::Color outlineColor = sf::Color(54, 79, 107);
                public:
                    Lane(double Length, Vector2D Center, double Width = GlobalWidth);

                    //Setters
                    void SetLength(double Length);
                    void SetCenter(Vector2D Center);

                    //Getters
                    double GetLength() const;
                    Vector2D GetCenter() const;

                    CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override;
                    void draw(Interface& interface)override;
                };
            }
        }
    }
}