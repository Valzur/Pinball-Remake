#pragma once
#include "../Defs.h"
#include "../GameObjects/Ball.h"
#include <cmath>

namespace Valzuroid {
    namespace Pinball {
        namespace Utility {
            using namespace Valzuroid::Pinball::GameObjects;
            Vector2D CircleCollision(const Ball& ball, Valzuroid::Pinball::Vector2D position, double radius, double collision_time);
            bool BICCollision(Ball& ball, Valzuroid::Pinball::Vector2D position, double radius);
            bool BOCCollision(Ball& ball, Valzuroid::Pinball::Vector2D position, double radius);
            Vector2D Lcollision(const Ball& ball, Valzuroid::Pinball::Vector2D Position, double L, double W, double collision_time);
            bool InRange(double value, double max, double min);
            Vector2D RectangleCollision(Ball& ball, double Length, double Width, double Angle, Vector2D Center);
            CollisionResponse CircleLineCollision(Ball& ball, Vector2D center1, Vector2D center2);
        }
    }
}