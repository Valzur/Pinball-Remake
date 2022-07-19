#pragma once

#include "../GameObjects/Ball.h"
#include <cmath>

using namespace std;
using namespace sf;

namespace Valzuroid {
    namespace Pinball {
        using namespace GameObjects;
        namespace Utility {
            class PixelPerfectCollision {
            private:
                Image image;
                Vector2u size;
                Vector2D ballPosition;
            public:
                Vector2D CheckCollision(Ball ball, Sprite sprite);
            };
        }
    }
}