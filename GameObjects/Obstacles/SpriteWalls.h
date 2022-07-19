#pragma once

#include <iostream>
#include "Obstacle.h"
using namespace std;

namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            namespace Obstacles {
                class SpriteWalls : public Obstacle {
                private:
                    sf::Texture texture;
                    Vector2D position;
                    sf::Sprite sprite;
                public:
                    //Constructors
                    SpriteWalls(string TexturePath, Vector2D SpritePosition);

                    //Configurations
                    void LoadTexture(string path);
                    void SetPosition(Vector2D pos);
                    sf::Sprite GetSprite();
                    CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override;
                    void draw(Interface& interface) override;
                };
            }
        }
    }
}