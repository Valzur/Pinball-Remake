#pragma once
#include "../Defs.h"
using namespace std;

namespace Valzuroid {
	namespace Pinball {
		namespace GameObjects {
			class GameObject
			{
			public:
				virtual void start() {};
				virtual void updateTick(double frameTime) {};
				virtual void onMouseButtonDown(sf::Vector2i mousePosition) {};
				virtual void onMouseButtonUp(sf::Vector2i mousePosition) {};
			};
		}
	}
}