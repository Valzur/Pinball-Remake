#pragma once
#include "GameObject.h"
#include "../Interface.h"

namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            // An interface class that should be implemented by any class that has a visual representation
            class Drawn : public GameObject
            {
            public:
                virtual void draw(Interface& interface) = 0;  // Uses the interface object to draw itself
            };
        }
    }
}