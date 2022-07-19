#pragma once

#include <iostream>
#include "Obstacle.h"
#include <cmath>
#include "../GameManager.h"
#include "../../Defs.h"
#include "../../Utility/CollisionDetection.h"

using namespace std;

namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            namespace Obstacles {
                class Bumper : public Obstacle {
                protected:
                    const sf::Color hitColor = sf::Color(67, 221, 230);
                    const sf::Color fillColor = sf::Color(252, 81, 133);
                    const sf::Color outlineColor = sf::Color(54, 79, 107);
                    const double outlineThickness = -2.0f;

                    double hitTimer = FlashTimer;
                    bool Hit = false, AllowHit = true;
                    Vector2D position;
                    double radius;
                    int bscore;
                    BumperType type;

                    sf::Texture texture;
                    sf::Sprite sprite;

                public:
                    Bumper(Vector2D pos, double rad, BumperType type);

                    //Setters
                    void setScorepoints(int x);

                    CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override = 0;
                    void draw(Interface& interface) override = 0;
                };
            }
        }
    }
}