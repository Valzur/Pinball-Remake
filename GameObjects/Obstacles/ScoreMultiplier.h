#pragma once

#include "Bumper.h"
#include "../../Defs.h"

namespace Valzuroid {
	namespace Pinball {
		namespace GameObjects {
			namespace Obstacles {
				class ScoreMultiplier : public Bumper
				{
				private:
					const sf::Color hitColor = sf::Color(252, 81, 133);
					const sf::Color color = sf::Color(67, 221, 230);

					Vector2D Center;
					double Radius;
				public:
					ScoreMultiplier(Vector2D pos, double rad);
					CollisionResponse collideWith(Ball& ball, double collision_time, GameManager& manager) override;
					void start() override;
					void draw(Interface& interface) override;
				};
			}
		}
	}
}