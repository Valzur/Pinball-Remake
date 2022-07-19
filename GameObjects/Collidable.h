#pragma once
#include "Ball.h"
#include "GameManager.h"

namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            struct CollisionResponse
            {
                Vector2D collisionPoint;
                Vector2D ballPosition;
                Vector2D ballSpeed;
                CollisionResponse() {};
                CollisionResponse(Vector2D ballSpeed) { this->ballSpeed = ballSpeed; };
            };

            class GameManager;

            class Ball;

            // An interface class that should be implemented by any class that can apply force on the ball upon collision
            class Collidable
            {
            public:
                virtual CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) = 0;  // Simulates a collision with the ball (if any) and returns the contribution of the collision on the ball's acceleration
            };
        }
    }
}
