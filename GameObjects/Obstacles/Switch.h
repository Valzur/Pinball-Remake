#pragma once

#include <iostream>
#include "Obstacle.h"
#include <cmath>
#include "../GameManager.h"
#include "../../Defs.h"
#include "../../Utility/CollisionDetection.h"

namespace Valzuroid {
	namespace Pinball {
		namespace GameObjects {
			namespace Obstacles {
				class Switch : public Obstacle {
				private:
					const sf::Color usedColor = sf::Color(54, 79, 107);
					const sf::Color unusedColor = sf::Color(67, 221, 230);

					Vector2D Center;
					double Length;
					bool collidedLastFrame, Used = false, Direction = false;

				public:
					explicit Switch(Vector2D Center, double Length);
					CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override;
					void draw(Interface& interface)override;
				};
			}
		}
	}
}