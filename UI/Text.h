#pragma once
#include "UIElement.h"

namespace Valzuroid {
	namespace Pinball {
		using namespace UI;
		namespace UI {
			class Text : public UIElement, public sf::Text
			{
			private:
				sf::Font font;
			public:
				Text(Vector2D position, string text = "", int fontSize = 42, string fontPath = "");

				void updateTick() override;
				void draw(Interface& interface) override;
			};
		}
	}
}