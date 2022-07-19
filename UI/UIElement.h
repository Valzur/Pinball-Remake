#pragma once
#include "../GameObjects/Drawable.h"

namespace Valzuroid {
	namespace Pinball {
		using namespace GameObjects;
		namespace UI {
			class UIElement : public Drawn
			{
			protected:
				Vector2D position;
			public:
				virtual void updateTick() = 0;
			};
		}
	}
}