#pragma once

#include "../Drawable.h"
#include "../Collidable.h"
#include "../../Utility/AudioManager.h"



namespace Valzuroid {
    namespace Pinball {
        using namespace Utility;
        namespace GameObjects {
            namespace Obstacles {
                // An abstract class representing an obstacle
                class Obstacle : public Drawn, public Collidable, public AudioManager
                {

                };
            }
        }
    }
}